/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_rcc.h
 */

#ifndef STM32F4XX_RCC_H_
#define STM32F4XX_RCC_H_

#include <stm32f4xx_bitband.h>
#include <stm32f4xx_dev_cfg_gpio.h>
#include "stm32_sys.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Rcc
{
template<char Letter> /* GPIO */
struct Gpio
{
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

} // namespace Rcc
} // namespace Device
} // namespace STM32F4XX

#endif /* STM32F4XX_RCC_H_ */
