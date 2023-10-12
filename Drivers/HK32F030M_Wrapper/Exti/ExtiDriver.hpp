/*
 * ExtiDriver.hpp
 *
 *  Created on: 11 окт. 2023 г.
 *      Author: SpitsynAV
 *      Revision 1.1 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_EXTI_EXTIDRIVER_HPP_
#define HK32F030M_WRAPPER_EXTI_EXTIDRIVER_HPP_

#include "ExtiParams.hpp"
#include "../Gpio/Gpio.hpp"
#include "../IrqPriority.hpp"
#include <Libs/Utils/DebugAssert.h>
#include <functional>

namespace Drivers::Exti {

  class ExtiDriver{
    public:
      ExtiDriver(const Gpio::Gpio& pin, const ExtiParams& params, IrqPriority irqPriority) :
        _pin(pin), _params(params), _line (getLine()), _irqPriority(irqPriority) { }
      void init();
      inline bool getPinState() const { return _pin.read(); }

      inline bool isr() const {
        if( EXTI_GetITStatus( static_cast<uint32_t>(_line) ) == SET) {
          if( _triggerCallback ) _triggerCallback();
          EXTI_ClearITPendingBit( static_cast<uint32_t>(_line) );
          return true;
        }
        return false;
      }

      void setTriggerCallback(const std::function<void()>& triggerCallback);
      void interruptEnable()  const { EXTI->IMR |=  static_cast<uint32_t>(_line); }
      void interruptDisable() const { EXTI->IMR &= ~static_cast<uint32_t>(_line); }

    protected:
      const Gpio::Gpio&     _pin;
      const ExtiParams      _params;
      const Line            _line;
      const IrqPriority     _irqPriority;

      std::function<void()> _triggerCallback;

      IRQn_Type getIrqType() const;
      Line getLine() const;
      uint8_t getSourceLine() const;
      uint8_t getSourcePort() const;

  };

}  // namespace Driver::Exti



#endif /* HK32F030M_WRAPPER_EXTI_EXTIDRIVER_HPP_ */
