/*
 *  Created on: Dec 17, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_uxart_cfg.h
 */

#ifndef STM32F4XX_DEV_CFG_UXART_H_
#define STM32F4XX_DEV_CFG_UXART_H_

#include "stm32f4xx.h"
#include "../stm32/stm32_dev_rcc.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Config
{
namespace Uxart
{
template<size_t UxartNumber>
struct Structure {
    enum
    {
        BaseAddress = 0U, //
        IrqNumber = 0U, //
        ClockEnableRegAddress = 0U, //
        ClockEnableBitNumber = 0U, //
        ClockType = 0U, //
    };
};

template<>
struct Structure<1>
{
    enum
    {
        BaseAddress = USART1_BASE,//
        IrqNumber = USART1_IRQn, //
        ClockEnableRegAddress = RCC_BASE + 0x44U,//
        ClockEnableBitNumber = 4U,//
        ClockType = (unsigned int)Stm32::Device::Rcc::ClockType::PCLK2, //
    };
};
} // namespace Uxart
} // namespace Config
} // namespace Device
} // namespace Stm32f4xx

#endif /* STM32F4XX_DEV_CFG_UXART_H_ */
