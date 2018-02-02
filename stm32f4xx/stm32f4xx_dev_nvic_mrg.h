/*
 *  Created on: Jan 15, 2018
 *  Author:     wrscode
 *  File:       stm32f4xx_dev_nvic_mrg.h
 */

#ifndef STM32F4XX_DEV_NVIC_MRG_H_
#define STM32F4XX_DEV_NVIC_MRG_H_

#include "stm32_sys.h"
#include "stm32f4xx.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Nvic
{
    void setIrq(const IRQn_Type IrqNumber, const Stm32::System::State NewState);
    void setIrqHandler(const IRQn_Type IrqNumber, Stm32::System::IrqService::IrqService* Device = nullptr);
    void setIrqPriority(const IRQn_Type IrqNumber, const std::size_t PreemptPriority = 0U, const std::size_t SubPriority = 0U);
}
} // Device
} // Stm32f4xx

#endif /* STM32F4XX_DEV_NVIC_MRG_H_ */
