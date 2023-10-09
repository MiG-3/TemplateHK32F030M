/*
 * Gpio.cpp
 *
 *  Created on: 12 jun 2023
 *      Author: ShtukarevIS
 *      Revised: SpitsynAV
 *      Rev. 1.1 for HK32F030M
 */

#include "Gpio.hpp"
#include <hk32f030m_rcc.h>
#include <Libs/Utils/DebugAssert.h>

namespace Drivers::Gpio {

  void Gpio::init() const {
    enableClock();
    if(static_cast<Mode>(_mode) == Mode::Alternate) {
      GPIO_PinAFConfig(regs(), static_cast<uint16_t>(getSourceLine()), _alternate);
    }
    GPIO_InitTypeDef cfgPin = {
        .GPIO_Pin = _pins,
        .GPIO_Mode = static_cast<GPIOMode_TypeDef>(_mode),
        .GPIO_Speed = static_cast<GPIOSpeed_TypeDef>(_speed),
        .GPIO_OType = static_cast<GPIOOType_TypeDef>(_outputType),
        .GPIO_PuPd = static_cast<GPIOPuPd_TypeDef>(_pull),
        .GPIO_Schmit = static_cast<GPIOSchmit_TypeDef>(_schmitt)
    };
    GPIO_Init(regs(), &cfgPin);
  }

  void Gpio::enableClock() const {
    switch(_portAddr) {
      case GPIOA_BASE:
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        break;
      case GPIOB_BASE:
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
        break;
      case GPIOC_BASE:
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
        break;
      case GPIOD_BASE:
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
        break;
      default:
        DEBUG_STOP;
    }
  }

  SourceLine Gpio::getSourceLine() const {
    switch (static_cast<Pin>(_pins)) {
      case Pin::Pin0:
        return SourceLine::SourseLine0;
      case Pin::Pin1:
        return SourceLine::SourseLine1;
      case Pin::Pin2:
        return SourceLine::SourseLine2;
      case Pin::Pin3:
        return SourceLine::SourseLine3;
      case Pin::Pin4:
        return SourceLine::SourseLine4;
      case Pin::Pin5:
        return SourceLine::SourseLine5;
      case Pin::Pin6:
        return SourceLine::SourseLine6;
      case Pin::Pin7:
        return SourceLine::SourseLine7;
      case Pin::Pin8:
        return SourceLine::SourseLine8;
      case Pin::Pin9:
        return SourceLine::SourseLine9;
      case Pin::Pin10:
        return SourceLine::SourseLine10;
      case Pin::Pin11:
        return SourceLine::SourseLine11;
      case Pin::Pin12:
        return SourceLine::SourseLine12;
      case Pin::Pin13:
        return SourceLine::SourseLine13;
      case Pin::Pin14:
        return SourceLine::SourseLine14;
      case Pin::Pin15:
        return SourceLine::SourseLine15;
      default:
        DEBUG_STOP;//constexprError();
        return SourceLine::SourseLine15;
    }
  }



}


