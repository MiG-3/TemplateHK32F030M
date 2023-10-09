/*
 * UartList.hpp
 *
 *  Created on: 3 окт. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_UART_UARTLIST_HPP_
#define HK32F030M_WRAPPER_UART_UARTLIST_HPP_

#include "UartDriver.hpp"

namespace Drivers::Uart {

  class UartList {
    public:
      static UartDriver& uart1();
  };

}



#endif /* HK32F030M_WRAPPER_UART_UARTLIST_HPP_ */
