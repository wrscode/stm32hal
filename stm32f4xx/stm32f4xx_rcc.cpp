/*
 *  Created on: Jan 14, 2018
 *  Author:     wrscode
 *  File:       stm32f4xx_rcc.cpp
 */

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_hal_rcc.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Rcc
{
std::size_t SysClock::getFrequency(Stm32::Device::Rcc::ClockType Type, Stm32::System::RetCode::Code& Code)
{
    typedef Stm32::Device::Rcc::ClockType rClockType;

    switch (Type)
    {
        case rClockType::HCLK:
            return HAL_RCC_GetHCLKFreq();

        case rClockType::PCLK1:
            return  HAL_RCC_GetPCLK1Freq();

        case rClockType::PCLK2:
            return HAL_RCC_GetPCLK2Freq();

        default:
            return 0U;
    }
}
} // namespace HRCC
} // namespace Device
} // namespace STM32F4XX
