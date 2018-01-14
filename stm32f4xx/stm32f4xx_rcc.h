/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_rcc.h
 */

#ifndef STM32F4XX_RCC_H_
#define STM32F4XX_RCC_H_

#include "stm32f4xx_bitband.h"
#include "stm32f4xx_dev_cfg_gpio.h"
#include "stm32f4xx_dev_cfg_uxart.h"
#include "stm32_sys.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Rcc
{
/* GPIO ************************************************************************************************************ */
template<char Letter>
struct Gpio
{
    static_assert(Device::Config::Gpio::Structure<Letter>::ClockEnableRegAddress != 0U, "GPIO clock config wrong !!!");

private:
    enum
    {
        ClkEnBBAddr = Stm32f4xx::BitBand::BitInRegPeriphAddr2BBAddr< //
                Device::Config::Gpio::Structure<Letter>::ClockEnableRegAddress, //
                Device::Config::Gpio::Structure<Letter>::ClockEnableBitNumber>::BBAddress
    };

    static const Stm32::System::Utils::ConversionAddressToPointerType<ClkEnBBAddr, volatile std::uint32_t> mClockEnable;

public:
    static void setClock(const Stm32::System::State& NewState)
    {
        *mClockEnable = (Stm32::System::State::Enable == NewState) ? 0x01U : 0x00U;
    }
};

template<char Letter>
const Stm32::System::Utils::ConversionAddressToPointerType< //
        Gpio<Letter>::ClkEnBBAddr, volatile std::uint32_t> Gpio<Letter>::mClockEnable;

/* UXART *********************************************************************************************************** */
template<size_t Number>
struct Uxart
{
    static_assert(Device::Config::Uxart::Structure<Number>::ClockEnableRegAddress != 0U, "UXART clock config wrong !!!");

private:
    enum
    {
        ClkEnBBAddr = Stm32f4xx::BitBand::BitInRegPeriphAddr2BBAddr< //
                Device::Config::Uxart::Structure<Number>::ClockEnableRegAddress, //
                Device::Config::Uxart::Structure<Number>::ClockEnableBitNumber>::BBAddress
    };

    static const Stm32::System::Utils::ConversionAddressToPointerType<ClkEnBBAddr, volatile std::uint32_t> mClockEnable;

public:
    static void setClock(const Stm32::System::State& NewState)
    {
        *mClockEnable = (Stm32::System::State::Enable == NewState) ? 0x01U : 0x00U;
    }
};

template<size_t Number>
const Stm32::System::Utils::ConversionAddressToPointerType< //
        Uxart<Number>::ClkEnBBAddr, volatile std::uint32_t> Uxart<Number>::mClockEnable;

} // namespace Rcc
} // namespace Device
} // namespace STM32F4XX

#endif /* STM32F4XX_RCC_H_ */
