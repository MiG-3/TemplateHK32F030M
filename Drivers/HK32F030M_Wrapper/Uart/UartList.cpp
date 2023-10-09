/*
 * UartList.cpp
 *
 *  Created on: 3 окт. 2023 г.
 *      Author: SpitsynAV
 */

#include "UartList.hpp"
#include <Libs/Containers/array_mapping.hpp>

namespace Drivers::Uart {

  constexpr Gpio::Gpio usart1gpio [] {
      {Gpio::Port::GpioA, Gpio::Pin::Pin3, Gpio::Mode::Alternate, Gpio::Speed::High,
          Gpio::OutputType::PushPull, Gpio::Pull::None, Gpio::SchmittTrigger::Enable, Gpio::AlternateFunction::AF1},
      {Gpio::Port::GpioD, Gpio::Pin::Pin6, Gpio::Mode::Alternate, Gpio::Speed::High,
          Gpio::OutputType::PushPull, Gpio::Pull::None, Gpio::SchmittTrigger::Enable, Gpio::AlternateFunction::AF1},
  };

  UartDriver& UartList::uart1() {
    static array_mapping<const Gpio::Gpio> usart1gpioArr(usart1gpio, arraysize(usart1gpio));
    static UartDriver usart1(Device::Usart1, usart1gpioArr, IrqPriority::Medium/*UseFreeRtos*/);
    return usart1;
  }

}


