/*
 * IrqPriority.hpp
 *
 *  Created on: 23 ���. 2019 �.
 *      Author: ShtukarevIS
 */

#ifndef HK32F030M_WRAPPER_IRQPRIORITY_HPP_
#define HK32F030M_WRAPPER_IRQPRIORITY_HPP_

#ifdef USE_FREERTOS
#include <Configs/FreeRTOSConfig.h>
#else
#include <cstdint>
#endif
namespace Drivers {

  enum class IrqPriority : uint8_t {
    High = 0,
    Medium = 1,
    Low = 2,
#ifdef USE_FREERTOS
    UseFreeRtos = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
#endif
  };

}

#endif /* HK32F030M_WRAPPER_IRQPRIORITY_HPP_ */
