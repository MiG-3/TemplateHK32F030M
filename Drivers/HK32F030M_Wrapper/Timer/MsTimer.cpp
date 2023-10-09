/*
 * MsTimer.cpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
*      Revision 1.0 for HK32F030M
 */

#include "MsTimer.hpp"
#include <hk32f030m_rcc.h>

namespace Drivers::Timer {

  bool MsTimer::init( uint16_t ms ) const {
    if( ms == 0 || !(_device == Device::Timer2 || _device == Device::Timer6) ) {
      DEBUG_STOP;
      return false;
    }
    /* Turn on the timer clock */
    uint32_t clk = enableClock();
    /* Calculate the value of the prescaler register to generate a frequency of 1kHz (1ms) */
    uint32_t prescaler;
    uint8_t div1 = 0;
    do {
      div1++;
      prescaler =  (clk / _msFreq - 1) / div1;
    } while( (prescaler > UINT16_MAX) || ( ms * div1 == 1 ) );
    if( (ms*div1-1) > UINT16_MAX )
      return false;
    TIM_TimeBaseInitTypeDef cfgTim = {
        .TIM_Prescaler = static_cast<uint16_t>( prescaler ),
        .TIM_CounterMode   = TIM_CounterMode_Up,
        .TIM_Period    =  static_cast<uint16_t>( ms*div1-1 ),
        .TIM_ClockDivision    = TIM_CKD_DIV1,
        .TIM_RepetitionCounter  = 0
    };
    TIM_TimeBaseInit( regs(), &cfgTim );
    TIM_ClearFlag( regs(), TIM_FLAG_Update );
    return true;
  }

  uint32_t MsTimer::enableClock() const {
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




