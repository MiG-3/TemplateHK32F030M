/*
 * UartInterrupts.cpp
 *
 *  Created on: 3 ���. 2023 �.
 *      Author: SpitsynAV
 */

#include "UartList.hpp"

extern "C" {
void USART1_IRQHandler() {
  Drivers::Uart::UartList::uart1().isr();
}

}


