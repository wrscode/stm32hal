/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_bitband.h
 */

#ifndef STM32F4XX_BITBAND_H_
#define STM32F4XX_BITBAND_H_

#include "stm32f4xx.h"

namespace Stm32f4xx
{
namespace BitBand
{
template<size_t PeriphBaseAddr>
struct PeriphAddr2BBAddr
{
    enum
    {
        BBAddress = ((PERIPH_BB_BASE + (PeriphBaseAddr - PERIPH_BASE) * 32))
    };
};

template<size_t RegisterPeriphAddr>
struct RegPeriphAddr2BBAddr
{
    enum
    {
        BBAddress = ((PERIPH_BB_BASE + (RegisterPeriphAddr - PERIPH_BASE) * 32))
    };
};

template<size_t RegisterPeriphAddr, size_t BitInRegister>
struct BitInRegPeriphAddr2BBAddr
{
    enum
    {
        BBAddress = ((PERIPH_BB_BASE + (RegisterPeriphAddr - PERIPH_BASE) * 32) + (BitInRegister * 4))
    };
};
} // namespace BitBand
} // namespace stm32f4xx

#endif /* STM32F4XX_HBITBAND_H_ */
