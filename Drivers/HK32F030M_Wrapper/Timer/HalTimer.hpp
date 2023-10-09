/*
 * HalTimer.hpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.0 for HK32F030M
 */


#ifndef HK32F030M_WRAPPER_HALTIMER_HPP_
#define HK32F030M_WRAPPER_HALTIMER_HPP_

#include "TimerList.hpp"
#include "../../Timer.hpp"

namespace Drivers::Timer {

    class HalTimer : public TimerApi {
      public:
        HalTimer(uint32_t msToWait) {
          set( msToWait);
        }
        void set(uint32_t msToWait) override {
          _msToWait = msToWait;
          reset();
        }
        void reset() override {
          _start = now();
          _stopped = false;
        }
        bool expired() const override {
          return _stopped || (timePassed() >= _msToWait);
        }
        uint32_t remains() const override {
          auto remains = _msToWait - timePassed();
          return expired() ? 0 : remains;
        }
        void stop() override { _stopped = true; }
        uint32_t secondsPassed() const { return timePassed() / 1000; }
        uint32_t minutesPassed() const { return timePassed() / 60000; }

      private:
        uint32_t timePassed() const { return now() - _start; }
        uint32_t now() const { return TimerList::halTimebase().getTick(); }
        uint32_t _msToWait{0};
        uint32_t _start{0};
        bool _stopped {false};
    };

}

#endif /* HK32F030M_WRAPPER_HALTIMER_HPP_ */
