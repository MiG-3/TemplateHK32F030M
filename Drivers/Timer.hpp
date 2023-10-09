#ifndef DRIVERS_TIMER_HPP_
#define DRIVERS_TIMER_HPP_

#include <cstdint>

namespace Drivers {

  class TimerApi {
    protected:
      virtual ~TimerApi(){};
    public:
      virtual void set(uint32_t msToWait) = 0;
      virtual void reset() = 0;
      virtual bool expired() const = 0;
      virtual uint32_t remains() const = 0;
      virtual void stop() = 0;
  };

}

#endif
