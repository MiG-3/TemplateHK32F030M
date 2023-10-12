/*
 * ExtiParams.hpp
 *
 *  Created on: 11 окт. 2023 г.
 *      Author: SpitsynAV
 *      Revision 1.1 for HK32F030M
 */

#ifndef HK32F030M_WRAPPER_EXTI_EXTIPARAMS_HPP_
#define HK32F030M_WRAPPER_EXTI_EXTIPARAMS_HPP_


#include <hk32f030m_exti.h>
///////////#include <stm32g0xx_ll_system.h>

namespace Drivers::Exti {

/*    enum class SourcePort : uint32_t {
      SourcePortA = LL_EXTI_CONFIG_PORTA,
      SourcePortB = LL_EXTI_CONFIG_PORTB,
      SourcePortC = LL_EXTI_CONFIG_PORTC,
      SourcePortD = LL_EXTI_CONFIG_PORTD,
    };*/

/*    enum class SourceLine : uint32_t {
      SourseLine0    = LL_EXTI_CONFIG_LINE0,
      SourseLine1    = LL_EXTI_CONFIG_LINE1,
      SourseLine2    = LL_EXTI_CONFIG_LINE2,
      SourseLine3    = LL_EXTI_CONFIG_LINE3,
      SourseLine4    = LL_EXTI_CONFIG_LINE4,
      SourseLine5    = LL_EXTI_CONFIG_LINE5,
      SourseLine6    = LL_EXTI_CONFIG_LINE6,
      SourseLine7    = LL_EXTI_CONFIG_LINE7,
      SourseLine8    = LL_EXTI_CONFIG_LINE8,
      SourseLine9    = LL_EXTI_CONFIG_LINE9,
      SourseLine10   = LL_EXTI_CONFIG_LINE10,
      SourseLine11   = LL_EXTI_CONFIG_LINE11,
      SourseLine12   = LL_EXTI_CONFIG_LINE12,
      SourseLine13   = LL_EXTI_CONFIG_LINE13,
      SourseLine14   = LL_EXTI_CONFIG_LINE14,
      SourseLine15   = LL_EXTI_CONFIG_LINE15
    };*/

    enum class Line : uint32_t {
      Line0    = EXTI_Line0,
      Line1    = EXTI_Line1,
      Line2    = EXTI_Line2,
      Line3    = EXTI_Line3,
      Line4    = EXTI_Line4,
      Line5    = EXTI_Line5,
      Line6    = EXTI_Line6,
      Line7    = EXTI_Line7,
      Line8    = EXTI_Line8,
      Line9    = EXTI_Line9,
      Line10   = EXTI_Line10,
      Line11   = EXTI_Line11
    };

    enum class Mode : uint8_t {
      Interrupt         = EXTI_Mode_Interrupt,
      Event             = EXTI_Mode_Event
    };

    enum class Trigger : uint8_t {
      Rising           = EXTI_Trigger_Rising,
      Falling          = EXTI_Trigger_Falling,
      RisingAndFalling = EXTI_Trigger_Rising_Falling
    };

    struct ExtiParams {
      Mode    mode;
      Trigger trigger;
    };

}  // namespace Driver:: Exti

#endif /* HK32F030M_WRAPPER_EXTI_EXTIPARAMS_HPP_ */
