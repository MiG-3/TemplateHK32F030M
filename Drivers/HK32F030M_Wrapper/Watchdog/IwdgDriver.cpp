/*
 * IwdgDriver.cpp
 *
 *  Created on: 16 jun 2023
 *      Author: SpitsynAV
 *      Revision 1.1 for HK32F030M
 */

#include "IwdgDriver.hpp"
#include <Libs/Utils/DebugAssert.h>
#include <hk32f030m_rcc.h>

namespace Drivers::Watchdog {

  /*  Watchdog window ~(Prescaler/Flsi)*Counter second, Flsi=114kHz */
  bool IwdgDriver::init( IwdgParams params ) const {
    if(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET) {
      uint32_t cnt = _timeoutLsi;
      /* Enable the LSI OSC */
      RCC_LSICmd(ENABLE);
      /* Wait till LSI is ready */
      while ( (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)  && cnt ){ cnt--; };
      if( cnt == 0 ) {
        DEBUG_STOP;
        return false;
      }
    }
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(static_cast<uint8_t>(params.prescaler));
    /*  Counter Value between Min_Data=0 and Max_Data=0x0FFF */
    if( params.counter <= 0x0FFF) {
      IWDG_SetReload(params.counter);
      IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
      IWDG_ReloadCounter();
      return true;
    } else {
      DEBUG_STOP;
      return false;
    }
  }

}  // namespace Drivers::Watchdog
