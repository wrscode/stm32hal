/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_dev_gpio_pin.h
 */

#ifndef STM32F4XX_DEV_GPIO_PIN_NULL_H_
#define STM32F4XX_DEV_GPIO_PIN_NULL_H_

#include "../stm32/stm32_dev_ipin.h"
#include "stm32f4xx_dev_cfg_gpio.h"
#include "stm32f4xx_dev_int_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_bitband.h"

namespace Stm32f4xx
{
namespace Device
{
template<>
struct Pin<'X', 0, Stm32::Device::IPin::ActiveStateEnum::Normal>: public Stm32::Device::IPin
{

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
        USED(State);
    }

    inline Stm32::Device::IPin* operator->()
    {
        return this;
    }

    virtual Stm32::Device::IPin* open(const Stm32::Device::IPin::SettingsEnum Config, Stm32::System::Status::Code& Code)
    {
        USED(Config);
        USED(Code);
        return this;
    }

    virtual Stm32::Device::IPin* close(Stm32::System::Status::Code& Code)
    {
        USED(Code);
        return this;
    }

    inline virtual void setState(Stm32::System::State State)
    {
        USED(State);
    }

    inline virtual bool getState()
    {
        return true;
    }

    inline virtual void setHigh()
    {
    }

    inline virtual void setLow()
    {
    }

    inline virtual void setToggle()
    {
    }
};
}  // namespace Device
}  // namespace stm32f4xx

#endif /* STM32F4XX_DEV_GPIO_PIN_NULL_H_ */

