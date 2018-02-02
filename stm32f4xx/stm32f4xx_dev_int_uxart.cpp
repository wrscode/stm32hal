/*
 *  Created on: Dec 26, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_uxart_int.cpp
 */

#include <stm32f4xx_dev_int_uxart.h>

namespace Stm32f4xx
{
namespace Device
{
namespace Inside
{
namespace Uxart
{
#define SAMPLING16_DIV(_PCLK_, _BAUD_)                  (((_PCLK_)*25U)/(4U*(_BAUD_)))
#define SAMPLING16_DIVMANT(_PCLK_, _BAUD_)              (SAMPLING16_DIV((_PCLK_), (_BAUD_))/100U)
#define SAMPLING16_DIVFRAQ(_PCLK_, _BAUD_)              (((SAMPLING16_DIV((_PCLK_), (_BAUD_)) - (SAMPLING16_DIVMANT((_PCLK_), (_BAUD_)) * 100U)) * 16U + 50U) / 100U)
// UART BRR = mantissa + overflow + fraction
// = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU)
#define SAMPLING16_BRR(_PCLK_, _BAUD_)                  (((SAMPLING16_DIVMANT((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (SAMPLING16_DIVFRAQ((_PCLK_), (_BAUD_)) & 0xF0U)) + \
                                                        (SAMPLING16_DIVFRAQ((_PCLK_), (_BAUD_)) & 0x0FU))

#define SAMPLING8_DIV(_PCLK_, _BAUD_)                   (((_PCLK_)*25U)/(2U*(_BAUD_)))
#define SAMPLING8_DIVMANT(_PCLK_, _BAUD_)               (SAMPLING8_DIV((_PCLK_), (_BAUD_))/100U)
#define SAMPLING8_DIVFRAQ(_PCLK_, _BAUD_)               (((SAMPLING8_DIV((_PCLK_), (_BAUD_)) - (SAMPLING8_DIVMANT((_PCLK_), (_BAUD_)) * 100U)) * 8U + 50U) / 100U)
// UART BRR = mantissa + overflow + fraction
// = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U)
#define SAMPLING8_BRR(_PCLK_, _BAUD_)                   (((SAMPLING8_DIVMANT((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((SAMPLING8_DIVFRAQ((_PCLK_), (_BAUD_)) & 0xF8U) << 1U)) + \
                                                        (SAMPLING8_DIVFRAQ((_PCLK_), (_BAUD_)) & 0x07U))

std::uint32_t CalcValueOfBRR(const std::size_t Clock, const std::size_t BaudRate, const std::size_t Mult)
{
    if (Mult == 8)
    {
        return SAMPLING8_BRR(Clock, BaudRate);
    } else
    {
        return SAMPLING16_BRR(Clock, BaudRate);
    }
}

} // namespace Uxart
} // namespace Inside
} // namespace Device
} // namespace Stm32f4xx
