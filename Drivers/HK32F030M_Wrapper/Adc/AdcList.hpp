/*
 * AdcList.hpp
 *
 *  Created on: 28 сент. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_ADC_ADCLIST_HPP_
#define HK32F030M_WRAPPER_ADC_ADCLIST_HPP_

#include "AdcDriver.hpp"

namespace Drivers::Adc {

  class AdcList {
    public:
      static AdcDriver&  adc();
    private:
      explicit AdcList(){}
  };

}  // namespace Drivers::Adc



#endif /* HK32F030M_WRAPPER_ADC_ADCLIST_HPP_ */
