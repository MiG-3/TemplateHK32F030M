/*
 * AdcDriver.hpp
 *
 *  Created on: 27 сент. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_ADC_ADCDRIVER_HPP_
#define HK32F030M_WRAPPER_ADC_ADCDRIVER_HPP_

#include "AdcParams.hpp"
#include "../Gpio/Gpio.hpp"
#include "../IrqPriority.hpp"
#include <hk32f030m_rcc.h>
#include <Libs/Containers/array_mapping.hpp>
#include <Libs/Utils/DebugAssert.h>
#include <array>

namespace Drivers::Adc {

  using AdcData = std::array<uint16_t, 5> ;

  class AdcDriver {
    public:
      AdcDriver( const Device device, const array_mapping<const Gpio::Gpio>& pins ) :
        _device(device), _pins(pins) {
        DEBUG_ASSERT( IS_ADC_ALL_INSTANCE( regs() ) );
      }

      bool init( const AdcParams& params,  const array_mapping<const ChannelParams>& channels );
      const auto& data() const { return _data; }
      void startConversion() const { ADC_StartOfConversion( regs() ); }
      void stopConversion() const { ADC_StopOfConversion( regs() ); }
      void activateInterrupt(IrqPriority priority);
      bool endOfConversion() const { return ADC_GetFlagStatus(regs(), ADC_FLAG_EOC) == SET; }
      bool endOfSequence() const { return ADC_GetFlagStatus(regs(), ADC_FLAG_EOSEQ) == SET; }
      void isr();

    protected:
      static constexpr uint32_t _readyTimeout { 10u }; //ms
      static constexpr uint32_t _calibrationTimeout { 100u }; //ms

      const Device _device;
      const array_mapping<const Gpio::Gpio>& _pins;
      AdcData  _data;
      uint32_t _calib {0};
      size_t _channelTotal {0};
      size_t _idx {0};

      ADC_TypeDef* regs() const { return reinterpret_cast<ADC_TypeDef*>(_device); }
      void enable() const;
      void disable() const;
      void enableClock() const;
      void disableClock() const;
      IRQn_Type irqType() const;
      bool calibration();
      bool waitingAdcReady();
      bool channelsConfig(const array_mapping<const ChannelParams>& channels);
  };



}  // namespace Drivers::Adc

#endif /* HK32F030M_WRAPPER_ADC_ADCDRIVER_HPP_ */
