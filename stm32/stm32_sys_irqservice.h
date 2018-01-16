/*
 *  Created on: Jan 15, 2018
 *  Author:     wrscode
 *  File:       stm32f4xx_sys_irqservice.h
 */

#ifndef STM32_SYS_IRQSERVICE_H_
#define STM32_SYS_IRQSERVICE_H_

namespace Stm32
{
namespace System
{
namespace IrqService
{
struct IrqService
{
    virtual ~IrqService()
    {
    }
    virtual void irqHandler() = 0;
};
}
} // System
} // Stm32

#endif /* STM32_SYS_IRQSERVICE_H_ */
