/*
 * MsIrqTimer.hpp
 *
 *  Created on: 27 окт. 2022 г.
 *      Author: SpitsynAV
*      Revision 1.0 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_TIMER_MSIRQTIMER_HPP_
#define HK32F030M_WRAPPER_TIMER_MSIRQTIMER_HPP_

#include "MsTimer.hpp"
#include "../IrqPriority.hpp"
#include <functional>

namespace Drivers::Timer {
  /* For General purpose and Basic Timers with 16-bit counter:
   * TIM2, TIM6
   */
  class MsIrqTimer : public MsTimer {
    public:
      MsIrqTimer(Device device, IrqPriority irqPriority) :
        MsTimer(device), _irqPriority(irqPriority) {} ;
      virtual ~MsIrqTimer(){}
      virtual bool init( uint16_t ms ) const override;  // период вызова прерывания в мс

      inline void start() const {
        TIM_ITConfig(regs(), TIM_IT_Update, ENABLE);
        MsTimer::start();
      }

      inline void stop() const{
        TIM_ITConfig(regs(), TIM_IT_Update, DISABLE);
        MsTimer::stop();
      }

      inline bool isr() {
        if (TIM_GetITStatus(regs(), TIM_IT_Update) != RESET){
          if(_updateCallback) _updateCallback();
          TIM_ClearITPendingBit(regs(), TIM_IT_Update);
          return true;
        }
        return false;
      }

      void setUpdateCallback(const std::function<void()>& updateCallback) {
        _updateCallback = updateCallback;
      }

      IRQn_Type getIrqType() const;
    protected:
      const IrqPriority _irqPriority;
      std::function<void()> _updateCallback;
  };

} //Drivers::Timer

#endif /* HK32F030M_WRAPPER_TIMER_MSIRQTIMER_HPP_ */
