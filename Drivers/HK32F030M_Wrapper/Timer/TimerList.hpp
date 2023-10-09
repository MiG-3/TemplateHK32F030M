/*
 * TimerList.hpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_TIMER_TIMERLIST_HPP_
#define HK32F030M_WRAPPER_TIMER_TIMERLIST_HPP_

//#include "MsIrqTimer.hpp"
#include "HalTimebase.hpp"

namespace Drivers::Timer {

  class TimerList {
    public:
      static HalTimebase&  halTimebase();
      static MsTimer&  tim2();
    private:
      explicit TimerList(){}
  };

}

#endif /* HK32F030M_WRAPPER_TIMER_TIMERLIST_HPP_ */
