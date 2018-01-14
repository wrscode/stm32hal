/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_dev_gpio_pin.h
 */

#ifndef STM32F4XX_DEV_GPIO_PIN_H_
#define STM32F4XX_DEV_GPIO_PIN_H_

#include "../stm32/stm32_dev_ipin.h"
#include "stm32f4xx_dev_cfg_gpio.h"
#include "stm32f4xx_dev_int_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_bitband.h"

namespace Stm32f4xx
{
namespace Device
{
template<char Letter, size_t PinNr, Stm32::Device::IPin::ActiveState AState = Stm32::Device::IPin::ActiveState::Normal>
struct Pin: public Stm32::Device::IPin
{
    enum
    {
         Pin1xBit00 = PinNr, //

         Pin2xBit00 = (2 * PinNr) + 0, //
         Pin2xBit01 = (2 * PinNr) + 1, //

         Pin4xBit00 = (4 * PinNr) + 0, //
         Pin4xBit01 = (4 * PinNr) + 1, //
         Pin4xBit02 = (4 * PinNr) + 2, //
         Pin4xBit03 = (4 * PinNr) + 3, //

         GpioBaseAddress = Device::Config::Gpio::Structure<Letter>::BaseAddress,
         GpioBitBandAddress = BitBand::PeriphAddr2BBAddr<GpioBaseAddress>::BBAddress,
    };

    static_assert(GpioBaseAddress, "MCU dosen't support this GPIO !!!");
    static_assert(PinNr <= 15, "Wrong number of pin in GPIO port!!!");

    /* ************************************************************** */
    static const Stm32::System::Utils::ConversionAddressToPointerType<GpioBaseAddress, GPIO_TypeDef> mInstance;
    static const Stm32::System::Utils::ConversionAddressToPointerType<GpioBitBandAddress, Stm32f4xx::Device::Inside::Gpio::GpioBitBand_t> mBBInstance;
    /* ************************************************************** */

public:
    explicit Pin()
    {
    }

    ~Pin()
    {
    }

    Pin(const Pin&) = delete;
    Pin(Pin&&) = delete;

    Pin& operator=(const Pin&) = delete;
    Pin& operator=(Pin&&) = delete;

    void operator=(Stm32::System::State State)
    {
        setState(State);
    }

    inline Stm32::Device::IPin* operator->()
    {
        return this;
    }

    virtual Stm32::Device::IPin* open(const Stm32::Device::IPin::Config Config, Stm32::System::RetCode::Code& Code)
    {
        Rcc::Gpio<Letter>::setClock(Stm32::System::State::Enable);

        mBBInstance->mode[Pin2xBit00] = (Config && Stm32::Device::IPin::Config::ModeBit00) ? 0x01U : 0x00U;
        mBBInstance->mode[Pin2xBit01] = (Config && Stm32::Device::IPin::Config::ModeBit01) ? 0x01U : 0x00U;

        mBBInstance->alt[Pin4xBit00] = (Config && Stm32::Device::IPin::Config::ModeBit04) ? 0x01U : 0x00U;
        mBBInstance->alt[Pin4xBit01] = (Config && Stm32::Device::IPin::Config::ModeBit05) ? 0x01U : 0x00U;
        mBBInstance->alt[Pin4xBit02] = (Config && Stm32::Device::IPin::Config::ModeBit06) ? 0x01U : 0x00U;
        mBBInstance->alt[Pin4xBit03] = (Config && Stm32::Device::IPin::Config::ModeBit07) ? 0x01U : 0x00U;

        mBBInstance->speed[Pin2xBit00] = (Config && Stm32::Device::IPin::Config::SpeedBit00) ? 0x01U : 0x00U;
        mBBInstance->speed[Pin2xBit01] = (Config && Stm32::Device::IPin::Config::SpeedBit01) ? 0x01U : 0x00U;

        mBBInstance->otype[Pin1xBit00] = (Config && Stm32::Device::IPin::Config::OTypeBit00) ? 0x01U : 0x00U;

        mBBInstance->pull[Pin2xBit00] = (Config && Stm32::Device::IPin::Config::PullBit00) ? 0x01U : 0x00U;
        mBBInstance->pull[Pin2xBit01] = (Config && Stm32::Device::IPin::Config::PullBit01) ? 0x01U : 0x00U;

        return this;
    }

    virtual Stm32::Device::IPin* close(Stm32::System::RetCode::Code& Code)
    {
        Rcc::Gpio<Letter>::setClock(Stm32::System::State::Disable);
        return this;
    }

    inline virtual void setState(Stm32::System::State State)
    {
        if (AState == Stm32::Device::IPin::ActiveState::Normal)
        {
            if (State != Stm32::System::State::Disable)
            {
                mBBInstance->bsr[Pin1xBit00] = 0x01U;
            } else
            {
                mBBInstance->brr[Pin1xBit00] = 0x01U;
            }
        } else
        {
            if (State != Stm32::System::State::Disable)
            {
                mBBInstance->brr[Pin1xBit00] = 0x01U;
            } else
            {
                mBBInstance->bsr[Pin1xBit00] = 0x01U;
            }
        }
    }

    inline virtual bool getState()
    {
        if (AState == Stm32::Device::IPin::ActiveState::Normal)
        {
            return mBBInstance->idr[Pin1xBit00];
        } else
        {
            return !mBBInstance->idr[Pin1xBit00];
        }
    }

    inline virtual void setHigh()
    {
        if (AState == Stm32::Device::IPin::ActiveState::Normal)
        {
            mBBInstance->bsr[Pin1xBit00] = 0x01U;
        } else
        {
            mBBInstance->brr[Pin1xBit00] = 0x01U;
        }
    }

    inline virtual void setLow()
    {
        if (AState == Stm32::Device::IPin::ActiveState::Normal)
        {
            mBBInstance->brr[Pin1xBit00] = 0x01U;
        } else
        {
            mBBInstance->bsr[Pin1xBit00] = 0x01U;
        }
    }

    inline virtual void setToggle()
    {
        mBBInstance->odr[Pin1xBit00] = !mBBInstance->odr[Pin1xBit00];
    }
};

template<char Letter, size_t Pin, Stm32::Device::IPin::ActiveState AState>
const Stm32::System::Utils::ConversionAddressToPointerType< //
        Device::Pin<Letter, Pin, AState>::GpioBaseAddress, GPIO_TypeDef> //
        Device::Pin<Letter, Pin, AState>::mInstance;

template<char Letter, size_t Pin, Stm32::Device::IPin::ActiveState AState>
const Stm32::System::Utils::ConversionAddressToPointerType< //
        Device::Pin<Letter, Pin, AState>::GpioBitBandAddress, Stm32f4xx::Device::Inside::Gpio::GpioBitBand_t> //
        Device::Pin<Letter, Pin, AState>::mBBInstance;

}  // namespace Device
}  // namespace stm32f4xx

#endif /* STM32F4XX_DEV_HGPIO_HPIN_H_ */

