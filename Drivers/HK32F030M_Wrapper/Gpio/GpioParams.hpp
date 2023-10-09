/*
 * GpioParams.hpp
 *
 *  Created on: 12 jun 2023
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_GPIO_GPIOPARAMS_HPP_
#define HK32F030M_WRAPPER_GPIO_GPIOPARAMS_HPP_

#include <hk32f030m_gpio.h>

namespace Drivers::Gpio {

  enum class Port : uint32_t {
    GpioA = GPIOA_BASE,
    GpioB = GPIOB_BASE,
    GpioC = GPIOC_BASE,
    GpioD = GPIOD_BASE
  };


  enum class Pin : uint16_t {
    Pin0   = GPIO_Pin_0,
    Pin1   = GPIO_Pin_1,
    Pin2   = GPIO_Pin_2,
    Pin3   = GPIO_Pin_3,
    Pin4   = GPIO_Pin_4,
    Pin5   = GPIO_Pin_5,
    Pin6   = GPIO_Pin_6,
    Pin7   = GPIO_Pin_7,
    Pin8   = GPIO_Pin_8,
    Pin9   = GPIO_Pin_9,
    Pin10  = GPIO_Pin_10,
    Pin11  = GPIO_Pin_11,
    Pin12  = GPIO_Pin_12,
    Pin13  = GPIO_Pin_13,
    Pin14  = GPIO_Pin_14,
    Pin15  = GPIO_Pin_15
  };

  constexpr Pin operator|(Pin p1, Pin p2) {
    return static_cast<Pin>(static_cast<uint32_t>(p1) | static_cast<uint32_t>(p2));
  }


  enum class Mode : uint8_t {
    Input     = GPIO_Mode_IN,
    Output    = GPIO_Mode_OUT,
    Alternate = GPIO_Mode_AF,
    Analog    = GPIO_Mode_AN
  };

  enum class Speed : uint8_t {
    Low  = GPIO_Speed_2MHz,
    High = GPIO_Speed_10MHz
  };

  enum class OutputType : uint8_t {
    PushPull  = GPIO_OType_PP,
    OpenDrain = GPIO_OType_OD
  };

  enum class Pull : uint8_t {
    None = GPIO_PuPd_NOPULL,
    Down = GPIO_PuPd_DOWN,
    Up   = GPIO_PuPd_UP
  };

  enum class AlternateFunction : uint8_t {
    AF0 = GPIO_AF_0,
    AF1 = GPIO_AF_1,
    AF2 = GPIO_AF_2,
    AF3 = GPIO_AF_3,
    AF4 = GPIO_AF_4,
    AF5 = GPIO_AF_5,
    AF6 = GPIO_AF_6,
    AF7 = GPIO_AF_7
  };

  enum class SchmittTrigger : uint8_t {
    Disable = GPIO_Schmit_Disable,
    Enable  = GPIO_Schmit_Enable
  };

  enum class SourceLine : uint8_t {
    SourseLine0  = GPIO_PinSource0,
    SourseLine1  = GPIO_PinSource1,
    SourseLine2  = GPIO_PinSource2,
    SourseLine3  = GPIO_PinSource3,
    SourseLine4  = GPIO_PinSource4,
    SourseLine5  = GPIO_PinSource5,
    SourseLine6  = GPIO_PinSource6,
    SourseLine7  = GPIO_PinSource7,
    SourseLine8  = GPIO_PinSource8,
    SourseLine9  = GPIO_PinSource9,
    SourseLine10 = GPIO_PinSource10,
    SourseLine11 = GPIO_PinSource11,
    SourseLine12 = GPIO_PinSource12,
    SourseLine13 = GPIO_PinSource13,
    SourseLine14 = GPIO_PinSource14,
    SourseLine15 = GPIO_PinSource15
  };

}  // namespace Drivers::Gpio

#endif /* HK32F030M_WRAPPER_GPIO_GPIOPARAMS_HPP_ */
