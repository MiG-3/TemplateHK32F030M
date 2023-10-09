/*
 * UartDriver.hpp
 *
 *  Created on: 28 сент. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_UART_UARTDRIVER_HPP_
#define HK32F030M_WRAPPER_UART_UARTDRIVER_HPP_

#include "UartParams.hpp"
#include "../IrqPriority.hpp"
#include "../Gpio/Gpio.hpp"
#include <Libs/Containers/array_mapping.hpp>
#include <Libs/Containers/RingBuffer.hpp>
#include <Libs/Containers/buffer.hpp>

namespace Drivers::Uart {

  class UartDriver {
    public:
      UartDriver(const Device device, const array_mapping<const Gpio::Gpio>& uartPins,
           IrqPriority irqPriority) :
        _device(device),
        _uartPins(uartPins),
        _irqPriority(irqPriority),
        _buf(){/*osCreateEvent(&_rxEvent);*/}
      bool init(const UartParams& params, bool useDePin = false,
          DePolarity dePolarity = DePolarity::Low);



      bool write (buffer<uint8_t>& txBuf, uint32_t txCount);

//      bool read  (buffer<uint8_t>& rxBuf, uint32_t bytesToRead, uint32_t timeoutMs) override;
      void isr();

      inline void startExchange() { USART_Cmd( regs(), ENABLE ); }
      inline void stopReceive() {
        /* Выключаем прерывания USART на прием */
        USART_ITConfig( regs(), USART_IT_RXNE, DISABLE );
      }
      inline void startReceive() {
        /* Включаем прерывания USART на прием */
        USART_ITConfig( regs(), USART_IT_RXNE, ENABLE );
      }
      inline void swapTxRx() const { USART_SWAPPinCmd(regs(), ENABLE); }


    protected:
      USART_TypeDef* regs() const { return reinterpret_cast<USART_TypeDef*>(_device); }
      bool initUart(const UartParams& params, bool useDePin, DePolarity dePolarity) const;
      void enableClock() const;
      IRQn_Type irqType() const;
 /////     uint32_t readBytes(buffer<uint8_t>& rxBuf, uint32_t remainToRead);

      const Device _device;
      const array_mapping<const Gpio::Gpio>& _uartPins;
      const IrqPriority _irqPriority;
/////      OsEvent _rxEvent;

      RingBuffer<64, uint8_t> _buf;
  };

}  // namespace Drivers::Uart

#endif /* HK32F030M_WRAPPER_UART_UARTDRIVER_HPP_ */
