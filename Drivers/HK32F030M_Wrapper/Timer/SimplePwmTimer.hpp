/*
 * SimplePwmTimer.hpp
 *
 *  Created on: 16 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.0 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_TIMER_SIMPLEPWMTIMER_HPP_
#define HK32F030M_WRAPPER_TIMER_SIMPLEPWMTIMER_HPP_

#include "TimerParams.hpp"
#include "../Gpio/Gpio.hpp"

namespace Drivers::Timer {

    /* For Advanced and General purpose Timers with 16-bit counter:
     * TIM1, TIM2
     */

    class SimplePwmTimer {
      public:
        constexpr SimplePwmTimer(Device device, Channel channel) :
                  _device(device), _channel(channel) {}
        constexpr SimplePwmTimer(Device device, const Gpio::Gpio& pin, Channel channel) :
    _device(device), _pin(&pin), _channel(channel) {}
        bool init( uint16_t freq, Polarity pol, IdleState idle ) const ;
        /* duty 0..100% */
        void setDuty(uint8_t duty) const;

        inline void start() const {
          TIM_Cmd( regs(), ENABLE);
        }

        inline void stop() const {
          setDuty(0);
          TIM_Cmd( regs(), DISABLE);
        }

      private:
        const Device _device;
        const Gpio::Gpio* _pin {nullptr};
        const Channel _channel;

        TIM_TypeDef* regs() const { return reinterpret_cast<TIM_TypeDef*>(_device);}
        uint32_t enableClock() const;
    };

} //Drivers::Timer


#endif /* HK32F030M_WRAPPER_TIMER_SIMPLEPWMTIMER_HPP_ */
