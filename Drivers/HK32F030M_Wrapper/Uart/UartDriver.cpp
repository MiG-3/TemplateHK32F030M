/*
 * UartDriver.cpp
 *
 *  Created on: 30 сент. 2023 г.
 *      Author: SpitsynAV
 */
#include "UartDriver.hpp"

namespace Drivers::Uart {

  bool UartDriver::init(const UartParams& params, bool useDePin, DePolarity dePolarity) {
    for(const Gpio::Gpio& pin : _uartPins) {
       pin.init();
     }
     return initUart(params, useDePin, dePolarity);
  }

  bool UartDriver::initUart(const UartParams& params, bool useDePin,
      DePolarity dePolarity) const {
     enableClock();
     USART_DeInit( regs() );
     USART_InitTypeDef cfgUart = USART_InitTypeDef(params);
     USART_OverSampling8Cmd( regs(), ENABLE );
     USART_Init( regs(), &cfgUart );
     USART_OverrunDetectionConfig( regs(), USART_OVRDetection_Disable );
     if(useDePin) {
       USART_DECmd( regs(), ENABLE );
       USART_DEPolarityConfig( regs(), static_cast<uint32_t>(dePolarity) );
       USART_SetDEAssertionTime( regs(), 16 );
       USART_SetDEDeassertionTime( regs(), 16 );
     }
     auto irq = irqType();
     NVIC_SetPriority( irq, static_cast<uint8_t>(_irqPriority) );
     NVIC_EnableIRQ( irq );
     USART_ITConfig( regs(), USART_IT_RXNE, ENABLE );
     USART_Cmd( regs(), ENABLE );
     return true;
   }

  bool UartDriver::write(buffer<uint8_t>& txBuf, uint32_t txCount) {
    if (txCount == 0) return false;
    for (uint32_t i = 0; i<txCount; ++i) {
      while( USART_GetFlagStatus( regs(), USART_FLAG_TXE ) == RESET );
      USART_SendData( regs(), txBuf[i] );
    }
    while( USART_GetFlagStatus( regs(), USART_FLAG_TC ) == RESET );
    return true;
  }


  void UartDriver::enableClock() const {
    switch(_device) {
      case Device::Usart1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        break;
      default:
        DEBUG_STOP;
    }
  }

  IRQn_Type UartDriver::irqType() const {
    switch(_device) {
      case Device::Usart1:
        return IRQn_Type::USART1_IRQn;
      default:
        DEBUG_STOP;
        return IRQn_Type::USART1_IRQn;
    }
  }

  void UartDriver::isr() {
    if (USART_GetITStatus( regs(), USART_IT_RXNE ) != RESET) {
      uint8_t data = static_cast<uint8_t>( USART_ReceiveData( regs() ));
      _buf.write(data);
    //////  osSetEventFromIsr(&_rxEvent);
    }

  }

}  // namespace Drivers::Uart




