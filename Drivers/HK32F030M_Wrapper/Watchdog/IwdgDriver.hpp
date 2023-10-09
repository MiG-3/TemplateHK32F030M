/*
 * IwdgDriver.hpp
 *
 *  Created on: 16 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.1 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_WATCHDOG_IWDGDRIVER_HPP_
#define HK32F030M_WRAPPER_WATCHDOG_IWDGDRIVER_HPP_

#include "IwdgParams.hpp"

namespace Drivers::Watchdog {

  class IwdgDriver {
    public:
      constexpr IwdgDriver() {}
      bool init( IwdgParams params ) const;
      inline void start() const { IWDG_Enable(); }
      inline void feed()  const { IWDG_ReloadCounter(); }
    protected:
      inline static constexpr uint32_t  _timeoutLsi {0x3FFFFF};
  };

}  // namespace Drivers::Watchdog

#endif /* HK32F030M_WRAPPER_WATCHDOG_IWDGDRIVER_HPP_ */
