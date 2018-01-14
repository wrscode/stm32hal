/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_dev_cfg_gpio.h
 */

#ifndef STM32F4XX_DEV_CFG_GPIO_H_
#define STM32F4XX_DEV_CFG_GPIO_H_

#include "stm32f4xx.h"
#include <cstdint>

namespace Stm32f4xx
{
namespace Device
{
namespace Config
{
namespace Gpio
{
#ifndef GPIOA_BASE
#define GPIOA_BASE      0x0000U
#endif

#ifndef GPIOB_BASE
#define GPIOB_BASE      0x0000U
#endif

#ifndef GPIOC_BASE
#define GPIOC_BASE      0x0000U
#endif

#ifndef GPIOD_BASE
#define GPIOD_BASE      0x0000U
#endif

#ifndef GPIOE_BASE
#define GPIOE_BASE      0x0000U
#endif

#ifndef GPIOF_BASE
#define GPIOF_BASE      0x0000U
#endif

#ifndef GPIOG_BASE
#define GPIOG_BASE      0x0000U
#endif

#ifndef GPIOH_BASE
#define GPIOH_BASE      0x0000U
#endif

#ifndef GPIOI_BASE
#define GPIOI_BASE      0x0000U
#endif

#ifndef GPIOJ_BASE
#define GPIOJ_BASE      0x0000U
#endif

#ifndef GPIOK_BASE
#define GPIOK_BASE      0x0000U
#endif

template<char Letter>
struct Structure ;

template<>
struct Structure<'A'>
{
    enum
    {
        BaseAddress = GPIOA_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 0,//
    };
};

template<>
struct Structure<'B'>
{
    enum
    {
        BaseAddress = GPIOB_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 1U,//
    };
};

template<>
struct Structure<'C'>
{
    enum
    {
        BaseAddress = GPIOC_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 2U,//
    };
};

template<>
struct Structure<'D'>
{
    enum
    {
        BaseAddress = GPIOD_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 3U,//
    };
};

template<>
struct Structure<'E'>
{
    enum
    {
        BaseAddress = GPIOE_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 4U,//
    };
};

template<>
struct Structure<'F'>
{
    enum
    {
        BaseAddress = GPIOF_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 5U,//
    };
};

template<>
struct Structure<'G'>
{
    enum
    {
        BaseAddress = GPIOG_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 6U,//
    };
};

template<>
struct Structure<'H'>
{
    enum
    {
        BaseAddress = GPIOH_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 7U,//
    };
};

template<>
struct Structure<'I'>
{
    enum
    {
        BaseAddress = GPIOI_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 8U,//
    };
};

template<>
struct Structure<'J'>
{
    enum
    {
        BaseAddress = GPIOJ_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 9U,//
    };
};

template<>
struct Structure<'K'>
{
    enum
    {
        BaseAddress = GPIOK_BASE, //
        ClockEnableRegAddress = RCC_BASE + 0x30U,//
        ClockEnableBitNumber = 10U,//
    };
};
} // namespace Gpio
} // namespace Config
} // namespace Device
} // namespace stm32f4xx

#endif /* STM32F4XX_DEV_CFG_GPIO_H_ */
