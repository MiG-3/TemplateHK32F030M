/*
 * HalTimebaseTimer.hpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_TIMER_HALTIMEBASE_HPP_
#define HK32F030M_WRAPPER_TIMER_HALTIMEBASE_HPP_

#include "MsIrqTimer.hpp"

namespace Drivers::Timer {

  class HalTimebase {
    public:
      HalTimebase(Device device, IrqPriority irqPriority) :  _timer(device, irqPriority) {};
      bool init() {
        if( !_timer.init(1) )
          return false;
        _timer.setUpdateCallback([this]{ _uwTick++; });
        _timer.start();
        return true;
      }

      inline uint32_t getTick() const { return _uwTick; }
      inline bool isr() { return _timer.isr(); }
      void delay(uint32_t wait) {
        uint32_t tickstart = getTick();
        if (wait < _maxDelay)
          wait++;
        while ((getTick() - tickstart) < wait) { }
      }

    private:
      inline static constexpr uint32_t _maxDelay {0xFFFFFFFF};
      MsIrqTimer _timer;
      volatile uint32_t _uwTick {0};
  };

}  // namespace Drivers::Timer

#endif /* HK32F030M_WRAPPER_TIMER_HALTIMEBASE_HPP_ */
