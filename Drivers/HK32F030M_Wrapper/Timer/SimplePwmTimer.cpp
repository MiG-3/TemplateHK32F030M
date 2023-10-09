/*
 * SimplePwmTimer.cpp
 *
 *  Created on: 16 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.0 for HK32F030M
 */

#include "SimplePwmTimer.hpp"
#include <Libs/Utils/DebugAssert.h>

namespace Drivers::Timer {

  bool SimplePwmTimer::init( uint16_t freq, Polarity pol, IdleState idle ) const {
    if( freq == 0 || !(_device == Device::Timer1 || _device == Device::Timer2) ) {
      DEBUG_STOP;
      return false;
    }
    if( _pin != nullptr ) { _pin->init(); }
    /* Turn on the timer clock */
    uint32_t clk = enableClock();
    /* Calculate the value of the prescaler register to generate a frequency */
    uint32_t tmp =  (clk / freq / 100) - 1;
    if( (clk == 0) || (tmp > UINT16_MAX) ) { return false; }
    uint16_t prescaler = uint16_t(tmp);
    TIM_TimeBaseInitTypeDef cfgTim = {
        .TIM_Prescaler = static_cast<uint16_t>( prescaler ),
        .TIM_CounterMode = TIM_CounterMode_Up,
        .TIM_Period = 99,
        .TIM_ClockDivision = TIM_CKD_DIV1,
        .TIM_RepetitionCounter = 0
    };
    TIM_TimeBaseInit( regs(), &cfgTim );
    TIM_OCInitTypeDef cfgOc = {
        .TIM_OCMode       = TIM_OCMode_PWM1,
        .TIM_OutputState  = TIM_OutputState_Enable,
        .TIM_OutputNState = TIM_OutputNState_Disable,
        .TIM_Pulse       = 0,
        .TIM_OCPolarity  = static_cast<uint16_t>(pol),
        .TIM_OCNPolarity = TIM_OCNPolarity_Low,
        .TIM_OCIdleState = static_cast<uint16_t>(idle),
        .TIM_OCNIdleState = TIM_OCNIdleState_Reset
    };
    switch (_channel) {
      case Channel::Channel1:
        TIM_OC1Init( regs(), &cfgOc);
        TIM_OC1PreloadConfig( regs(), TIM_OCPreload_Enable );
        break;
      case Channel::Channel2:
        TIM_OC2Init( regs(), &cfgOc);
        TIM_OC2PreloadConfig( regs(), TIM_OCPreload_Enable );
        break;
      case Channel::Channel3:
        TIM_OC3Init( regs(), &cfgOc);
        TIM_OC3PreloadConfig( regs(), TIM_OCPreload_Enable );
        break;
      case Channel::Channel4:
        TIM_OC4Init( regs(), &cfgOc);
        TIM_OC4PreloadConfig( regs(), TIM_OCPreload_Enable );
        break;
      default:
        DEBUG_STOP;
        return false;
    }
    return true;
  }

  void SimplePwmTimer::setDuty(uint8_t duty) const {
    if( duty > 99 ) duty = 99;
    switch (_channel) {
      case Channel::Channel1:
        TIM_SetCompare1( regs(), duty );
        break;
      case Channel::Channel2:
        TIM_SetCompare2( regs(), duty );
        break;
      case Channel::Channel3:
        TIM_SetCompare3( regs(), duty );
        break;
      case Channel::Channel4:
        TIM_SetCompare4( regs(), duty );
        break;
      default:
        DEBUG_STOP;
    }
  }


  uint32_t SimplePwmTimer::enableClock() const {
    RCC_ClocksTypeDef clocks{};
    RCC_GetClocksFreq(&clocks);
    auto pclkTimFreq = clocks.PCLK_Frequency * ( clocks.PCLK_Frequency == clocks.HCLK_Frequency ? 1 : 2);
    uint32_t rccTim {};
    switch(_device) {
      case Device::Timer2:
        rccTim = RCC_APB1Periph_TIM2;
        break;
      case Device::Timer6:
        rccTim = RCC_APB1Periph_TIM6;
        break;
      default:
        DEBUG_STOP;
        return 0;
    }
    RCC_APB1PeriphClockCmd(rccTim, ENABLE);
    return pclkTimFreq;
  }




} //Drivers::Timer




