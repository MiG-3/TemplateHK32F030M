/*
 * AdcInterrupts.cpp
 *
 *  Created on: 28 сент. 2023 г.
 *      Author: SpitsynAV
 */

#include "AdcList.hpp"

#ifdef __cplusplus
 extern "C" {
#endif

 void ADC1_IRQHandler() {
   Drivers::Adc::AdcList::adc().isr();
 }

#ifdef __cplusplus
}
#endif


