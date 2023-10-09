/*
 * IwdgParams.hpp
 *
 *  Created on: 16 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.0 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_WATCHDOG_IWDGPARAMS_HPP_
#define HK32F030M_WRAPPER_WATCHDOG_IWDGPARAMS_HPP_

#include <hk32f030m_iwdg.h>

namespace Drivers::Watchdog {

  enum class Prescaler : uint8_t {
    Div4   = IWDG_Prescaler_4,
    Div8   = IWDG_Prescaler_8,
    Div16  = IWDG_Prescaler_16,
    Div32  = IWDG_Prescaler_32,
    Div64  = IWDG_Prescaler_64,
    Div128 = IWDG_Prescaler_128,
    Div256 = IWDG_Prescaler_256
  };

  struct IwdgParams {
      Prescaler prescaler;
      uint16_t  counter;
  };

}  // namespace Drivers::Watchdog

#endif /* HK32F030M_WRAPPER_WATCHDOG_IWDGPARAMS_HPP_ */
