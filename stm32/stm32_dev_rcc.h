/*
 *  Created on: Jan 14, 2018
 *  Author:     wrscode
 *  File:       stm32_dev_rcc.h
 */

#ifndef STM32_DEV_RCC_H_
#define STM32_DEV_RCC_H_

namespace Stm32
{
namespace Device
{
namespace Rcc
{
enum class ClockType
{
    HCLK = 0,
    PCLK1,
    PCLK2,
};
} // namespace Rcc
} // namespace Device
} // namespace Stm32

#endif /* STM32_DEV_RCC_H_ */
