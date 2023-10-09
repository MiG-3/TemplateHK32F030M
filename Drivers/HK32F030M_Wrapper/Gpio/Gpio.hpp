/*
 * Gpio.hpp
 *
 *  Created on: 12 jun 2023
 *      Author: ShtukarevIS
 *      Revised: SpitsynAV
 *      Rev. 1.1 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_GPIO_GPIO_HPP_
#define HK32F030M_WRAPPER_GPIO_GPIO_HPP_

#include "GpioParams.hpp"

namespace Drivers::Gpio {

  class Gpio {
    public:
      constexpr Gpio(Port port, Pin pins, Mode mode, Speed speed, OutputType output,
          Pull pull, SchmittTrigger schmitt = SchmittTrigger::Enable,
          AlternateFunction af = AlternateFunction::AF0) :
          _portAddr(static_cast<uint32_t>(port)),
          _pins(static_cast<uint16_t>(pins)),
          _mode(static_cast<uint8_t>(mode)),
          _speed(static_cast<uint8_t>(speed)),
          _outputType(static_cast<uint8_t>(output)),
          _pull(static_cast<uint8_t>(pull)),
          _schmitt(static_cast<uint8_t>(schmitt)),
          _alternate(static_cast<uint8_t>(af))
      {

      }
      void init() const;
      SourceLine getSourceLine() const;

      inline void high() const {
        GPIO_SetBits( regs(), _pins );
      }

      inline void low() const {
        GPIO_ResetBits( regs(), _pins );
      }

      inline bool read() const {
        return static_cast<bool> (GPIO_ReadInputDataBit( regs(), _pins ));
      }

      inline void write(bool state) const {
       state ? high() : low();
      }

      constexpr Pin getPin() const{
        return static_cast<Pin>(_pins);
      }

      constexpr Port getPort() const{
        return static_cast<Port>(_portAddr);
      }

      constexpr Mode getMode() const {
        return static_cast<Mode>(_mode);
      }

      static inline constexpr void write(Port port, uint16_t mask, uint16_t data) {
        GPIO_TypeDef* reg = reinterpret_cast<GPIO_TypeDef*>(port);
        WRITE_REG( reg->BRR, (~data) & mask);
        WRITE_REG( reg->BSRR, data & mask);
      }
      static inline uint16_t read( Port port) {
        GPIO_TypeDef* reg = reinterpret_cast<GPIO_TypeDef*>(port);
        return GPIO_ReadInputData(reg);
      }

    private:
      void enableClock() const;
      inline GPIO_TypeDef* regs() const {
        return reinterpret_cast<GPIO_TypeDef*>(_portAddr);
      }
      uint32_t _portAddr;
      uint16_t _pins;
      uint8_t _mode;
      uint8_t _speed;
      uint8_t _outputType;
      uint8_t _pull;
      uint8_t _schmitt;
      uint8_t _alternate;
  };

}

#endif /* HK32F030M_WRAPPER_GPIO_GPIO_HPP_ */
