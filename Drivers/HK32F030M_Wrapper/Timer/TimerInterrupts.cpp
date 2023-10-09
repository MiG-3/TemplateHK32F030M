/*
 * TimerInterrupts.cpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
 */

#include "TimerList.hpp"

#ifdef __cplusplus
 extern "C" {
#endif

 void TIM6_IRQHandler(void) {
   Drivers::Timer::TimerList::halTimebase().isr();
 }

#ifdef __cplusplus
}
#endif
