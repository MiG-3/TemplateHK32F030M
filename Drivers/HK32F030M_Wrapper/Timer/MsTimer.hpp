/*
 * MsTimer.hpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
*      Revision 1.0 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_TIMER_MSTIMER_HPP_
#define HK32F030M_WRAPPER_TIMER_MSTIMER_HPP_

#include "TimerParams.hpp"
#include <Libs/Utils/DebugAssert.h>

namespace Drivers::Timer {
  /* For General purpose and Basic Timers with 16-bit counter:
   * TIM2, TIM6
   */
  class MsTimer {
    public:
      MsTimer(Device device) : _device(device) { };
      virtual ~MsTimer(){}
      virtual bool init( uint16_t ms ) const;  //period in ms

      inline void start() const {
        TIM_ClearFlag( regs(), TIM_FLAG_Update );
        TIM_Cmd( regs(), ENABLE);
      }

      inline void stop() const {
        TIM_ClearFlag( regs(), TIM_FLAG_Update );
        TIM_Cmd( regs(), DISABLE);
      }

      inline void setTRGOUpdate() const {
        TIM_SelectOutputTrigger(regs(), TIM_TRGOSource_Update);
      }

    protected:
      const Device _device;
      static constexpr uint16_t _msFreq = 1000;
      static constexpr uint32_t _mcsFreq = 1000000;

      TIM_TypeDef* regs() const { return reinterpret_cast<TIM_TypeDef*>(_device);}
      uint32_t enableClock() const;
  };

} //Drivers::Timer

#endif /* HK32F030M_WRAPPER_TIMER_MSTIMER_HPP_ */
