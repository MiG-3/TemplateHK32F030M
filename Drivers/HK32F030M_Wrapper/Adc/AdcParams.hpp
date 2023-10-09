/*
 * AdcParams.hpp
 *
 *  Created on: 26 сент. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_ADC_ADCPARAMS_HPP_
#define HK32F030M_WRAPPER_ADC_ADCPARAMS_HPP_

#include <hk32f030m_adc.h>

namespace Drivers::Adc {

  enum class Device : uint32_t {
    Adc1   = ADC1_BASE,
  };

  enum class ClockMode : uint32_t {
    Asynk    = ADC_ClockMode_AsynClk,
    SynkDiv2 = ADC_ClockMode_SynClkDiv2,
    SynkDiv4 = ADC_ClockMode_SynClkDiv4,
  };


  enum class TriggerEdge : uint32_t {
    None = ADC_ExternalTrigConvEdge_None,
    Rising  = ADC_ExternalTrigConvEdge_Rising,
    Falling  = ADC_ExternalTrigConvEdge_Falling,
    RisingFalling  = ADC_ExternalTrigConvEdge_RisingFalling
  };

  enum class TriggerSources : uint32_t {
    Timer1TriggerOut = ADC_ExternalTrigConv_T1_TRGO,
    Timer1Channel4  = ADC_ExternalTrigConv_T1_CC4,
    Timer1Channel1  = ADC_ExternalTrigConv_T1_CC1,
    Timer1Channel2  = ADC_ExternalTrigConv_T1_CC2,
    Timer1Channel3  = ADC_ExternalTrigConv_T1_CC3,
    Timer2TriggerOut = ADC_ExternalTrigConv_T2_TRGO,
    Timer6TriggerOut = ADC_ExternalTrigConv_T6_TRGO,
    PinTriggerOut = ADC_ExternalTrigConv_IO_TRGO
  };

  enum class DataAlignment : uint32_t {
    Right = ADC_DataAlign_Right,
    Left  = ADC_DataAlign_Left
  };

  enum class ScanDirection : uint32_t {
    Upward   = ADC_ScanDirection_Upward,
    Backward = ADC_ScanDirection_Backward
  };

  struct AdcParams {
      ClockMode  clkMode;
      bool continuousMode;
      TriggerEdge  triggerEdge;
      TriggerSources triggerSource;
      DataAlignment  alignment;
      ScanDirection  direction;

      operator ADC_InitTypeDef() const {
        return ADC_InitTypeDef {
          .ADC_ContinuousConvMode = continuousMode ? ENABLE : DISABLE,
          .ADC_ExternalTrigConvEdge = static_cast<uint32_t>( triggerEdge ),
          .ADC_ExternalTrigConv = static_cast<uint32_t>( triggerSource ),
          .ADC_DataAlign = static_cast<uint32_t>( alignment ),
          .ADC_ScanDirection   = static_cast<uint32_t>( direction )
        };
      }
  };

  enum class Channel : uint32_t{
    Channel0  = ADC_Channel_0,
    Channel1  = ADC_Channel_1,
    Channel2  = ADC_Channel_2,
    Channel3  = ADC_Channel_3,
    Channel4  = ADC_Channel_4,
    Channel_VrefInt    = ADC_Channel_Vrefint
  };

  enum class SamplingTime : uint32_t {
    Cycle_1_5   = ADC_SampleTime_1_5Cycles,
    Cycle_7_5   = ADC_SampleTime_7_5Cycles,
    Cycle_13_5  = ADC_SampleTime_13_5Cycles,
    Cycle_28_5  = ADC_SampleTime_28_5Cycles,
    Cycle_41_5  = ADC_SampleTime_41_5Cycles,
    Cycle_55_5  = ADC_SampleTime_55_5Cycles,
    Cycle_71_5  = ADC_SampleTime_71_5Cycles,
    Cycle_239_5 = ADC_SampleTime_239_5Cycles,
  };

  struct ChannelParams {
      Channel       channel;
      SamplingTime  sampling;
  };


}  // namespace Drivers::Adc

#endif /* HK32F030M_WRAPPER_ADC_ADCPARAMS_HPP_ */
