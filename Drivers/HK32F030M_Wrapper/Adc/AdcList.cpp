/*
 * AdcList.cpp
 *
 *  Created on: 28 сент. 2023 г.
 *      Author: SpitsynAV
 */

#include "AdcList.hpp"

namespace Drivers::Adc {

  using namespace Gpio;

  constexpr Gpio::Gpio adc1Pin [] {
      { Port::GpioD, Pin::Pin2, Mode::Analog, Speed::High, OutputType::PushPull, Pull::None },
/*      { Port::GpioB, Pin::Pin4, Mode::Analog, Speed::High, OutputType::PushPull, Pull::None },
      { Port::GpioB, Pin::Pin5, Mode::Analog, Speed::High, OutputType::PushPull, Pull::None }*/
  };
  constexpr array_mapping<const Gpio::Gpio> adc1PinArr(adc1Pin, arraysize(adc1Pin));

  AdcDriver& AdcList::adc() {
    static AdcDriver adc1(Device::Adc1, adc1PinArr);
    return adc1;
  }

}  // namespace Drivers::Adc



