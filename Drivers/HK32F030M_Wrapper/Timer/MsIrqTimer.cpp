/*
 * MsIrqTimer.cpp
 *
 *  Created on: 27 ���. 2022 �.
 *      Author: SpitsynAV
*      Revision 1.0 for HK32F030M
 */

#include "MsIrqTimer.hpp"
#include <hk32f030m_misc.h>

namespace Drivers::Timer {


  bool MsIrqTimer::init( uint16_t ms ) const {
    if( !MsTimer::init( ms ) ) return false;
    /* �������� ���������� ���������� ������� � ����������� */
    NVIC_SetPriority(getIrqType(), static_cast<uint8_t>(_irqPriority));
    NVIC_EnableIRQ(getIrqType());
    return true;
  }


  IRQn_Type MsIrqTimer::getIrqType() const {
    switch(_device) {
      case Device::Timer2:
        return IRQn_Type::TIM2_IRQn;
      case Device::Timer6:
        return IRQn_Type::TIM6_IRQn;
      default:
        DEBUG_STOP;
        return IRQn_Type::HardFault_IRQn;
    }
  }

} //Drivers::Timer




