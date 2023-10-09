/*
 * AdcDriver.cpp
 *
 *  Created on: 27 сент. 2023 г.
 *      Author: SpitsynAV
 */

#include "AdcDriver.hpp"

#include "../Timer/HalTimer.hpp"

namespace Drivers::Adc {

  bool AdcDriver::init( const AdcParams& params, const array_mapping<const ChannelParams>& channels ) {
      disable();
      /* Clear Data Buffer */
      for(auto& val : _data)  val = 0;
      /* Init Pins */
      for (const Gpio::Gpio& pin : _pins) {
        if( pin.getMode() == Gpio::Mode::Analog ) {
          pin.init();
        } else {
          DEBUG_STOP;
          return false;
        }
      }
      enableClock();
      ADC_DeInit( regs() );
      ADC_ClockModeConfig( regs(), static_cast<uint32_t>(params.clkMode) );
      ADC_InitTypeDef  cfgAdc = ADC_InitTypeDef(params);
      ADC_Init( regs(), &cfgAdc );
      if( !channelsConfig(channels) || !calibration() ) { return false; }
      _idx = 0;
      enable();
      return waitingAdcReady();
  }

  void AdcDriver::activateInterrupt(IrqPriority priority) {
    ADC_ITConfig( regs(), ADC_IT_EOC, ENABLE );
    ADC_ITConfig( regs(), ADC_IT_EOSEQ, ENABLE );
    NVIC_InitTypeDef nvic = {
        .NVIC_IRQChannel = static_cast<uint8_t>(irqType()),
        .NVIC_IRQChannelPriority = static_cast<uint8_t>(priority),
        .NVIC_IRQChannelCmd = ENABLE
    };
    NVIC_Init(&nvic);
    NVIC_ClearPendingIRQ( irqType() );
  }

  void AdcDriver::isr() {
    if(ADC_GetITStatus( regs(), ADC_IT_EOC ) == SET) {
      _data[_idx] = ADC_GetConversionValue( regs() );
      ADC_ClearITPendingBit( regs(), ADC_IT_EOC );
      _idx++;
      if(_idx >= _channelTotal) {
        _idx = 0;
      }
    }
    if(ADC_GetITStatus( regs(), ADC_IT_EOSEQ ) == SET) {
      _idx = 0;
      ADC_ClearITPendingBit( regs(), ADC_IT_EOSEQ );
    }
  }

  void AdcDriver::enable() const {
    ADC_Cmd(regs(), ENABLE);
  }

  void AdcDriver::disable() const {
    ADC_Cmd(regs(), DISABLE);
  }


  void AdcDriver::enableClock() const {
    switch(_device) {
      case Device::Adc1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);;
        break;
      default:
        DEBUG_STOP;
    }
  }

  void AdcDriver::disableClock() const {
    switch(_device) {
      case Device::Adc1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, DISABLE);;
        break;
      default:
        DEBUG_STOP;
    }
  }

  IRQn_Type AdcDriver::irqType() const {
    switch (_device) {
      case Device::Adc1:
        return IRQn_Type::ADC1_IRQn;
      default:
        DEBUG_STOP;
        return IRQn_Type::ADC1_IRQn;
    }
  }

  bool AdcDriver::calibration(){
    _calib = ADC_GetCalibrationFactor( regs() );
    return _calib != 0;
  }

  bool AdcDriver::waitingAdcReady() {
    Timer::HalTimer timer {_readyTimeout};
    while (ADC_GetFlagStatus( regs(), ADC_FLAG_ADRDY) == RESET) {
      if(timer.expired()) {
        DEBUG_STOP;
        return false;
      }
    }
    return true;
  }

  bool AdcDriver::channelsConfig(const array_mapping<const ChannelParams>& channels) {
    if( channels.size() > _data.size() ) {
      DEBUG_STOP;
      return false;
    }
    for(const auto& channel : channels) {
      ADC_ChannelConfig( regs(), static_cast<uint32_t>(channel.channel),
          static_cast<uint32_t>(channel.sampling));
      if(channel.channel == Channel::Channel_VrefInt) {
        ADC_VrefintCmd( regs(), ENABLE);
      }
    }
    _channelTotal = channels.size();
    return true;
  }

}  // namespace Drivers::Adc
