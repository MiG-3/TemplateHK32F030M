/*
 * ExtiDriver.cpp
 *
 *  Created on: 11 окт. 2023 г.
 *      Author: SpitsynAV
 *      Revision 1.1 for HK32F030M
 */

#include "ExtiDriver.hpp"
#include <hk32f030m_rcc.h>
#include <hk32f030m_syscfg.h>

namespace Drivers::Exti {

  void ExtiDriver::setTriggerCallback(const std::function<void()>& triggerCallback) {
    _triggerCallback = triggerCallback;
  }

  void ExtiDriver::init(){
    /*Configure key EXTI Line to key input Pin*/
    _pin.init();
    /* Включаем тактирование SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Подключаем линию EXTI */
    SYSCFG_EXTILineConfig(getSourcePort(), getSourceLine());
    /* Очищаем флаги прерывания */
    EXTI_ClearITPendingBit( static_cast<uint32_t>(_line) );
    /* Конфигурируем EXTI */
    EXTI_InitTypeDef cfgExti =  {
        .EXTI_Line    = static_cast<uint32_t> (_line),
        .EXTI_Mode    = static_cast<EXTIMode_TypeDef> (_params.mode),
        .EXTI_Trigger = static_cast<EXTITrigger_TypeDef> (_params.trigger),
        .EXTI_LineCmd = ENABLE
    };
    EXTI_Init( &cfgExti );
    interruptDisable();
    /* Устанавливаем приоритет прерывания от линии EXTI */
    auto irq = getIrqType();
    NVIC_SetPriority(irq, static_cast<uint8_t>(_irqPriority));
    /* Включаем прерывание. Не будет работать, пока не разрешим прерывание от линии */
    NVIC_EnableIRQ(irq);
  }

  IRQn_Type ExtiDriver::getIrqType() const {
    switch( _line ){
      case Line::Line0:
        return IRQn_Type::EXTI0_IRQn;
      case Line::Line1:
        return IRQn_Type::EXTI1_IRQn;
      case Line::Line2:
        return IRQn_Type::EXTI2_IRQn;
      case Line::Line3:
        return IRQn_Type::EXTI3_IRQn;
      case Line::Line4:
        return IRQn_Type::EXTI4_IRQn;
      case Line::Line5:
        return IRQn_Type::EXTI5_IRQn;
      case Line::Line6:
        return IRQn_Type::EXTI6_IRQn;
      case Line::Line7:
        return IRQn_Type::EXTI7_IRQn;
      case Line::Line8:
        return IRQn_Type::ADC1_IRQn;
      case Line::Line9:
        return IRQn_Type::USART1_IRQn;
      case Line::Line10:
        return IRQn_Type::I2C1_IRQn;
      case Line::Line11:
        return IRQn_Type::EXTI11_IRQn;
      default:
        return IRQn_Type::EXTI0_IRQn;
    }
  }

  Line ExtiDriver::getLine() const {
    switch (_pin.getPin()) {
      case Gpio::Pin::Pin0:
        return Line::Line0;
      case Gpio::Pin::Pin1:
        return Line::Line1;
      case Gpio::Pin::Pin2:
        return Line::Line2;
      case Gpio::Pin::Pin3:
        return Line::Line3;
      case Gpio::Pin::Pin4:
        return Line::Line4;
      case Gpio::Pin::Pin5:
        return Line::Line5;
      case Gpio::Pin::Pin6:
        return Line::Line6;
      case Gpio::Pin::Pin7:
        return Line::Line7;
      case Gpio::Pin::Pin8:
        return Line::Line8;
      case Gpio::Pin::Pin9:
        return Line::Line9;
      case Gpio::Pin::Pin10:
        return Line::Line10;
      case Gpio::Pin::Pin11:
        return Line::Line11;
      default:
        DEBUG_STOP;
        return Line::Line11;
    }
  }

  uint8_t ExtiDriver::getSourceLine() const {
    switch (_pin.getPin()) {
      case Gpio::Pin::Pin0:
        return EXTI_PinSource0;
      case Gpio::Pin::Pin1:
        return EXTI_PinSource1;
      case Gpio::Pin::Pin2:
        return EXTI_PinSource2;
      case Gpio::Pin::Pin3:
        return EXTI_PinSource3;
      case Gpio::Pin::Pin4:
        return EXTI_PinSource4;
      case Gpio::Pin::Pin5:
        return EXTI_PinSource5;
      case Gpio::Pin::Pin6:
        return EXTI_PinSource6;
      case Gpio::Pin::Pin7:
        return EXTI_PinSource7;
      case Gpio::Pin::Pin8:
        return EXTI_PinSource8;
      case Gpio::Pin::Pin9:
        return EXTI_PinSource9;
      case Gpio::Pin::Pin10:
        return EXTI_PinSource10;
      case Gpio::Pin::Pin11:
        return EXTI_PinSource11;
      case Gpio::Pin::Pin12:
        return EXTI_PinSource12;
      case Gpio::Pin::Pin13:
        return EXTI_PinSource13;
      case Gpio::Pin::Pin14:
        return EXTI_PinSource14;
      case Gpio::Pin::Pin15:
        return EXTI_PinSource15;
      default:
        DEBUG_STOP;
        return EXTI_PinSource15;
    }
  }

  uint8_t ExtiDriver::getSourcePort() const{
    switch (_pin.getPort()) {
      case Gpio::Port::GpioA:
        return EXTI_PortSourceGPIOA;
      case Gpio::Port::GpioB:
        return EXTI_PortSourceGPIOB;
      case Gpio::Port::GpioC:
        return EXTI_PortSourceGPIOC;
      case Gpio::Port::GpioD:
        return EXTI_PortSourceGPIOD;
      default:
        DEBUG_STOP;
        return EXTI_PortSourceGPIOD;
    }
  }

}  // namespace Drivers::Exti


