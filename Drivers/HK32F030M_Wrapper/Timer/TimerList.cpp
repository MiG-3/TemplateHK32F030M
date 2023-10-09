/*
 * TimerList.cpp
 *
 *  Created on: 14 jun 2023
 *      Author: SpitsynAV
 */

#include "TimerList.hpp"

namespace Drivers::Timer {

  HalTimebase& TimerList::halTimebase() {
    static HalTimebase tim6(Device::Timer6, {IrqPriority::Low});
    return tim6;
  }

  MsTimer& TimerList::tim2() {
    static MsTimer tim2(Device::Timer2);
    return tim2;
  }

}
