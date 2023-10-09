/*
 * UartParams.hpp
 *
 *  Created on: 28 сент. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_UART_UARTPARAMS_HPP_
#define HK32F030M_WRAPPER_UART_UARTPARAMS_HPP_

#include <hk32f030m_usart.h>

namespace Drivers::Uart {

  enum class Device : uint32_t {
    Usart1 = USART1_BASE
  };
  // Количество бит данных в одной посылке
  enum class DataBits : uint32_t {
    DB_7Bits = USART_WordLength_7b,
    DB_8Bits = USART_WordLength_8b,
    DB_9Bits = USART_WordLength_9b
  };
  // Контроль чётности
  enum class Parity : uint32_t {
    // Отключён
    None = USART_Parity_No,
    // Нечётность
    Odd  = USART_Parity_Odd,
    // Чётность
    Even = USART_Parity_Even
  };
  // Количество стоп-бит
  enum class StopBits : uint32_t {
    // Один стоп-бит
    One  = USART_StopBits_1,
    // Полтора стоп-бита
    OneAndHalf = USART_StopBits_1_5,
    // Два стоб-бита
    Two = USART_StopBits_2
  };

  enum class Mode : uint32_t {
    Rx = USART_Mode_Rx,
    Tx = USART_Mode_Tx,
    RxTx = USART_Mode_Rx | USART_Mode_Tx
  };

  enum class HardwareFlowControl : uint32_t {
    None = USART_HardwareFlowControl_None,
    CTS = USART_HardwareFlowControl_CTS,
    RTS = USART_HardwareFlowControl_RTS,
    RTS_CTS = USART_HardwareFlowControl_RTS_CTS
  };

  struct UartParams {
      uint32_t baudRate;
      DataBits dataBits;
      StopBits stopBits;
      Parity parity;
      Mode mode;
      HardwareFlowControl flowControl;

      operator USART_InitTypeDef() const {
        return USART_InitTypeDef {
          .USART_BaudRate = static_cast<uint32_t>( baudRate ),
          .USART_WordLength = static_cast<uint32_t>( dataBits ),
          .USART_StopBits = static_cast<uint32_t>( stopBits ),
          .USART_Parity = static_cast<uint32_t>( parity ),
          .USART_Mode   = static_cast<uint32_t>( mode ),
          .USART_HardwareFlowControl   = static_cast<uint32_t>( flowControl)
        };
      }
  };

  enum class DePolarity : uint32_t {
    High = USART_DEPolarity_High,
    Low = USART_DEPolarity_Low
  };


}  // namespace Drivers::Uart

#endif /* HK32F030M_WRAPPER_UART_UARTPARAMS_HPP_ */
