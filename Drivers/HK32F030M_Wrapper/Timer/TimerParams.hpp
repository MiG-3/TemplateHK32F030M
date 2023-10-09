/*
 * TimerParams.hpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.0 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_TIMER_TIMERPARAMS_HPP_
#define HK32F030M_WRAPPER_TIMER_TIMERPARAMS_HPP_

#include <hk32f030m_tim.h>

namespace Drivers::Timer {

    enum class Device : uint32_t {
      Timer1   = TIM1_BASE, /* Advanced */
      Timer2   = TIM2_BASE, /* General */
      Timer6   = TIM6_BASE, /* Basic */
    };

    enum class Channel : uint16_t {
      Channel1  = TIM_Channel_1,
      Channel2  = TIM_Channel_2,
      Channel3  = TIM_Channel_3,
      Channel4  = TIM_Channel_4
    };

    enum class Polarity : uint16_t {
      Low  = TIM_OCPolarity_Low,
      High = TIM_OCPolarity_High
    };

    enum class NPolarity : uint16_t {
      Low  = TIM_OCNPolarity_Low,
      High = TIM_OCNPolarity_High
    };

    enum class IdleState : uint16_t {
      Low  = TIM_OCIdleState_Reset,
      High = TIM_OCIdleState_Set
    };

    enum class NIdleState : uint16_t {
      Low  = TIM_OCNIdleState_Reset,
      High = TIM_OCNIdleState_Set
    };

}

#endif /* HK32F030M_WRAPPER_TIMER_TIMERPARAMS_HPP_ */
