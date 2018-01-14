/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_dev_int_gpio.h
 */

#ifndef STM32F4XX_DEV_INT_GPIO_H_
#define STM32F4XX_DEV_INT_GPIO_H_

#include "stm32f4xx.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Inside
{
namespace Gpio
{
typedef struct GpioBitBand_t
{
    volatile uint32_t mode[32];
    volatile uint32_t otype[32];
    volatile uint32_t speed[32];
    volatile uint32_t pull[32];
    volatile uint32_t idr[32];
    volatile uint32_t odr[32];
    volatile uint32_t bsr[16];
    volatile uint32_t brr[16];
    volatile uint32_t lock[32];
    volatile uint32_t alt[64];
} GpioBitBand_t;
} // namespace Gpio
} // namespace Inside
} // namespace Device
} // namespace stm32f4xx

#endif /* STM32F4XX_DEV_INT_GPIO_H_ */
