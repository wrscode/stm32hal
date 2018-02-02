/*
 *  Created on: Jan 15, 2018
 *  Author:     wrscode
 *  File:       stm32f4xx_dev_nvic_mrg.cpp
 */

#include "stm32f4xx_dev_nvic_mrg.h"

namespace Stm32f4xx
{
namespace Device
{
namespace Nvic
{
extern "C" inline __attribute__((always_inline)) void Wrapper(void* Obj)
{
    static_cast<Stm32::System::IrqService::IrqService*>(Obj)->irqHandler();
}

static void* WWDGIrqPointer
    { nullptr };

static void* PVDIrqPointer
    { nullptr };

static void* TAMP_STAMPIrqPointer
    { nullptr };

static void* RTC_WKUPIrqPointer
    { nullptr };

static void* FLASHIrqPointer
    { nullptr };

static void* RCCIrqPointer
    { nullptr };

static void* EXTI0IrqPointer
    { nullptr };

static void* EXTI1IrqPointer
    { nullptr };

static void* EXTI2IrqPointer
    { nullptr };

static void* EXTI3IrqPointer
    { nullptr };

static void* EXTI4IrqPointer
    { nullptr };

static void* DMA1_Stream0IrqPointer
    { nullptr };

static void* DMA1_Stream1IrqPointer
    { nullptr };

static void* DMA1_Stream2IrqPointer
    { nullptr };

static void* DMA1_Stream3IrqPointer
    { nullptr };

static void* DMA1_Stream4IrqPointer
    { nullptr };

static void* DMA1_Stream5IrqPointer
    { nullptr };

static void* DMA1_Stream6IrqPointer
    { nullptr };

static void* ADCIrqPointer
    { nullptr };

static void* EXTI9_5IrqPointer
    { nullptr };

static void* TIM1_BRK_TIM9IrqPointer
    { nullptr };

static void* TIM1_UP_TIM10IrqPointer
    { nullptr };

static void* TIM1_TRG_COM_TIM11IrqPointer
    { nullptr };

static void* TIM1_CCIrqPointer
    { nullptr };

static void* TIM2IrqPointer
    { nullptr };

static void* TIM3IrqPointer
    { nullptr };

static void* TIM4IrqPointer
    { nullptr };

static void* I2C1_EVIrqPointer
    { nullptr };

static void* I2C1_ERIrqPointer
    { nullptr };

static void* I2C2_EVIrqPointer
    { nullptr };

static void* I2C2_ERIrqPointer
    { nullptr };

static void* SPI1IrqPointer
    { nullptr };

static void* SPI2IrqPointer
    { nullptr };

static void* USART1IrqPointer
    { nullptr };

static void* USART2IrqPointer
    { nullptr };

static void* EXTI15_10IrqPointer
    { nullptr };

static void* RTC_AlarmIrqPointer
    { nullptr };

static void* OTG_FS_WKUPIrqPointer
    { nullptr };

static void* DMA1_Stream7IrqPointer
    { nullptr };

static void* SDIOIrqPointer
    { nullptr };

static void* TIM5IrqPointer
    { nullptr };

static void* SPI3IrqPointer
    { nullptr };

static void* DMA2_Stream0IrqPointer
    { nullptr };

static void* DMA2_Stream1IrqPointer
    { nullptr };

static void* DMA2_Stream2IrqPointer
    { nullptr };

static void* DMA2_Stream3IrqPointer
    { nullptr };

static void* DMA2_Stream4IrqPointer
    { nullptr };

static void* OTG_FSIrqPointer
    { nullptr };

static void* DMA2_Stream5IrqPointer
    { nullptr };

static void* DMA2_Stream6IrqPointer
    { nullptr };

static void* DMA2_Stream7IrqPointer
    { nullptr };

static void* USART6IrqPointer
    { nullptr };

static void* I2C3_EVIrqPointer
    { nullptr };

static void* I2C3_ERIrqPointer
    { nullptr };

static void* FPUIrqPointer
    { nullptr };

static void* SPI4IrqPointer
    { nullptr };

extern "C" void WWDG_IRQHandler(void)
{
    Wrapper(WWDGIrqPointer);
}
extern "C" void PVD_IRQHandler(void)
{
    Wrapper(PVDIrqPointer);
}
extern "C" void TAMP_STAMP_IRQHandler(void)
{
    Wrapper(TAMP_STAMPIrqPointer);
}
extern "C" void RTC_WKUP_IRQHandler(void)
{
    Wrapper(RTC_WKUPIrqPointer);
}
extern "C" void FLASH_IRQHandler(void)
{
    Wrapper(FLASHIrqPointer);
}
extern "C" void RCC_IRQHandler(void)
{
    Wrapper(RCCIrqPointer);
}
extern "C" void EXTI0_IRQHandler(void)
{
    Wrapper(EXTI0IrqPointer);
}
extern "C" void EXTI1_IRQHandler(void)
{
    Wrapper(EXTI1IrqPointer);
}
extern "C" void EXTI2_IRQHandler(void)
{
    Wrapper(EXTI2IrqPointer);
}
extern "C" void EXTI3_IRQHandler(void)
{
    Wrapper(EXTI3IrqPointer);
}
extern "C" void EXTI4_IRQHandler(void)
{
    Wrapper(EXTI4IrqPointer);
}
extern "C" void DMA1_Stream0_IRQHandler(void)
{
    Wrapper(DMA1_Stream0IrqPointer);
}
extern "C" void DMA1_Stream1_IRQHandler(void)
{
    Wrapper(DMA1_Stream1IrqPointer);
}
extern "C" void DMA1_Stream2_IRQHandler(void)
{
    Wrapper(DMA1_Stream2IrqPointer);
}
extern "C" void DMA1_Stream3_IRQHandler(void)
{
    Wrapper(DMA1_Stream3IrqPointer);
}
extern "C" void DMA1_Stream4_IRQHandler(void)
{
    Wrapper(DMA1_Stream4IrqPointer);
}
extern "C" void DMA1_Stream5_IRQHandler(void)
{
    Wrapper(DMA1_Stream5IrqPointer);
}
extern "C" void DMA1_Stream6_IRQHandler(void)
{
    Wrapper(DMA1_Stream6IrqPointer);
}
extern "C" void ADC_IRQHandler(void)
{
    Wrapper(ADCIrqPointer);
}
extern "C" void EXTI9_5_IRQHandler(void)
{
    Wrapper(EXTI9_5IrqPointer);
}
extern "C" void TIM1_BRK_TIM9_IRQHandler(void)
{
    Wrapper(TIM1_BRK_TIM9IrqPointer);
}
extern "C" void TIM1_UP_TIM10_IRQHandler(void)
{
    Wrapper(TIM1_UP_TIM10IrqPointer);
}
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    Wrapper(TIM1_TRG_COM_TIM11IrqPointer);
}
extern "C" void TIM1_CC_IRQHandler(void)
{
    Wrapper(TIM1_CCIrqPointer);
}
extern "C" void TIM2_IRQHandler(void)
{
    Wrapper(TIM2IrqPointer);
}
extern "C" void TIM3_IRQHandler(void)
{
    Wrapper(TIM3IrqPointer);
}
extern "C" void TIM4_IRQHandler(void)
{
    Wrapper(TIM4IrqPointer);
}
extern "C" void I2C1_EV_IRQHandler(void)
{
    Wrapper(I2C1_EVIrqPointer);
}
extern "C" void I2C1_ER_IRQHandler(void)
{
    Wrapper(I2C1_ERIrqPointer);
}
extern "C" void I2C2_EV_IRQHandler(void)
{
    Wrapper(I2C2_EVIrqPointer);
}
extern "C" void I2C2_ER_IRQHandler(void)
{
    Wrapper(I2C2_ERIrqPointer);
}
extern "C" void SPI1_IRQHandler(void)
{
    Wrapper(SPI1IrqPointer);
}
extern "C" void SPI2_IRQHandler(void)
{
    Wrapper(SPI2IrqPointer);
}
extern "C" void USART1_IRQHandler(void)
{
    Wrapper(USART1IrqPointer);
}
extern "C" void USART2_IRQHandler(void)
{
    Wrapper(USART2IrqPointer);
}
extern "C" void EXTI15_10_IRQHandler(void)
{
    Wrapper(EXTI15_10IrqPointer);
}
extern "C" void RTC_Alarm_IRQHandler(void)
{
    Wrapper(RTC_AlarmIrqPointer);
}
extern "C" void OTG_FS_WKUP_IRQHandler(void)
{
    Wrapper(OTG_FS_WKUPIrqPointer);
}
extern "C" void DMA1_Stream7_IRQHandler(void)
{
    Wrapper(DMA1_Stream7IrqPointer);
}
extern "C" void SDIO_IRQHandler(void)
{
    Wrapper(SDIOIrqPointer);
}
extern "C" void TIM5_IRQHandler(void)
{
    Wrapper(TIM5IrqPointer);
}
extern "C" void SPI3_IRQHandler(void)
{
    Wrapper(SPI3IrqPointer);
}
extern "C" void DMA2_Stream0_IRQHandler(void)
{
    Wrapper(DMA2_Stream0IrqPointer);
}
extern "C" void DMA2_Stream1_IRQHandler(void)
{
    Wrapper(DMA2_Stream1IrqPointer);
}
extern "C" void DMA2_Stream2_IRQHandler(void)
{
    Wrapper(DMA2_Stream2IrqPointer);
}
extern "C" void DMA2_Stream3_IRQHandler(void)
{
    Wrapper(DMA2_Stream3IrqPointer);
}
extern "C" void DMA2_Stream4_IRQHandler(void)
{
    Wrapper(DMA2_Stream4IrqPointer);
}
extern "C" void OTG_FS_IRQHandler(void)
{
    Wrapper(OTG_FSIrqPointer);
}
extern "C" void DMA2_Stream5_IRQHandler(void)
{
    Wrapper(DMA2_Stream5IrqPointer);
}
extern "C" void DMA2_Stream6_IRQHandler(void)
{
    Wrapper(DMA2_Stream6IrqPointer);
}
extern "C" void DMA2_Stream7_IRQHandler(void)
{
    Wrapper(DMA2_Stream7IrqPointer);
}
extern "C" void USART6_IRQHandler(void)
{
    Wrapper(USART6IrqPointer);
}
extern "C" void I2C3_EV_IRQHandler(void)
{
    Wrapper(I2C3_EVIrqPointer);
}
extern "C" void I2C3_ER_IRQHandler(void)
{
    Wrapper(I2C3_ERIrqPointer);
}
extern "C" void FPU_IRQHandler(void)
{
    Wrapper(FPUIrqPointer);
}
extern "C" void SPI4_IRQHandler(void)
{
    Wrapper(SPI4IrqPointer);
}

void setIrq(const IRQn_Type IrqNumber, const Stm32::System::State NewState)
{
    if (NewState == Stm32::System::State::Enable)
    {
        NVIC_EnableIRQ(IrqNumber);
    } else
    {
        NVIC_DisableIRQ(IrqNumber);
    }
}

void setIrqHandler(const IRQn_Type IrqNumber, Stm32::System::IrqService::IrqService* Device)
{
    switch (IrqNumber)
    {
        case WWDG_IRQn:
            WWDGIrqPointer = Device;
            break;
        case PVD_IRQn:
            PVDIrqPointer = Device;
            break;
        case TAMP_STAMP_IRQn:
            TAMP_STAMPIrqPointer = Device;
            break;
        case RTC_WKUP_IRQn:
            RTC_WKUPIrqPointer = Device;
            break;
        case FLASH_IRQn:
            FLASHIrqPointer = Device;
            break;
        case RCC_IRQn:
            RCCIrqPointer = Device;
            break;
        case EXTI0_IRQn:
            EXTI0IrqPointer = Device;
            break;
        case EXTI1_IRQn:
            EXTI1IrqPointer = Device;
            break;
        case EXTI2_IRQn:
            EXTI2IrqPointer = Device;
            break;
        case EXTI3_IRQn:
            EXTI3IrqPointer = Device;
            break;
        case EXTI4_IRQn:
            EXTI4IrqPointer = Device;
            break;
        case DMA1_Stream0_IRQn:
            DMA1_Stream0IrqPointer = Device;
            break;
        case DMA1_Stream1_IRQn:
            DMA1_Stream1IrqPointer = Device;
            break;
        case DMA1_Stream2_IRQn:
            DMA1_Stream2IrqPointer = Device;
            break;
        case DMA1_Stream3_IRQn:
            DMA1_Stream3IrqPointer = Device;
            break;
        case DMA1_Stream4_IRQn:
            DMA1_Stream4IrqPointer = Device;
            break;
        case DMA1_Stream5_IRQn:
            DMA1_Stream5IrqPointer = Device;
            break;
        case DMA1_Stream6_IRQn:
            DMA1_Stream6IrqPointer = Device;
            break;
        case ADC_IRQn:
            ADCIrqPointer = Device;
            break;
        case EXTI9_5_IRQn:
            EXTI9_5IrqPointer = Device;
            break;
        case TIM1_BRK_TIM9_IRQn:
            TIM1_BRK_TIM9IrqPointer = Device;
            break;
        case TIM1_UP_TIM10_IRQn:
            TIM1_UP_TIM10IrqPointer = Device;
            break;
        case TIM1_TRG_COM_TIM11_IRQn:
            TIM1_TRG_COM_TIM11IrqPointer = Device;
            break;
        case TIM1_CC_IRQn:
            TIM1_CCIrqPointer = Device;
            break;
        case TIM2_IRQn:
            TIM2IrqPointer = Device;
            break;
        case TIM3_IRQn:
            TIM3IrqPointer = Device;
            break;
        case TIM4_IRQn:
            TIM4IrqPointer = Device;
            break;
        case I2C1_EV_IRQn:
            I2C1_EVIrqPointer = Device;
            break;
        case I2C1_ER_IRQn:
            I2C1_ERIrqPointer = Device;
            break;
        case I2C2_EV_IRQn:
            I2C2_EVIrqPointer = Device;
            break;
        case I2C2_ER_IRQn:
            I2C2_ERIrqPointer = Device;
            break;
        case SPI1_IRQn:
            SPI1IrqPointer = Device;
            break;
        case SPI2_IRQn:
            SPI2IrqPointer = Device;
            break;
        case USART1_IRQn:
            USART1IrqPointer = Device;
            break;
        case USART2_IRQn:
            USART2IrqPointer = Device;
            break;
        case EXTI15_10_IRQn:
            EXTI15_10IrqPointer = Device;
            break;
        case RTC_Alarm_IRQn:
            RTC_AlarmIrqPointer = Device;
            break;
        case OTG_FS_WKUP_IRQn:
            OTG_FS_WKUPIrqPointer = Device;
            break;
        case DMA1_Stream7_IRQn:
            DMA1_Stream7IrqPointer = Device;
            break;
        case SDIO_IRQn:
            SDIOIrqPointer = Device;
            break;
        case TIM5_IRQn:
            TIM5IrqPointer = Device;
            break;
        case SPI3_IRQn:
            SPI3IrqPointer = Device;
            break;
        case DMA2_Stream0_IRQn:
            DMA2_Stream0IrqPointer = Device;
            break;
        case DMA2_Stream1_IRQn:
            DMA2_Stream1IrqPointer = Device;
            break;
        case DMA2_Stream2_IRQn:
            DMA2_Stream2IrqPointer = Device;
            break;
        case DMA2_Stream3_IRQn:
            DMA2_Stream3IrqPointer = Device;
            break;
        case DMA2_Stream4_IRQn:
            DMA2_Stream4IrqPointer = Device;
            break;
        case OTG_FS_IRQn:
            OTG_FSIrqPointer = Device;
            break;
        case DMA2_Stream5_IRQn:
            DMA2_Stream5IrqPointer = Device;
            break;
        case DMA2_Stream6_IRQn:
            DMA2_Stream6IrqPointer = Device;
            break;
        case DMA2_Stream7_IRQn:
            DMA2_Stream7IrqPointer = Device;
            break;
        case USART6_IRQn:
            USART6IrqPointer = Device;
            break;
        case I2C3_EV_IRQn:
            I2C3_EVIrqPointer = Device;
            break;
        case I2C3_ER_IRQn:
            I2C3_ERIrqPointer = Device;
            break;
        case FPU_IRQn:
            FPUIrqPointer = Device;
            break;
        case SPI4_IRQn:
            SPI4IrqPointer = Device;
            break;

        default:
            break;
    }
}

void setIrqPriority(const IRQn_Type IrqNumber, const std::size_t PreemptPriority, const std::size_t SubPriority)
{
    NVIC_SetPriority(IrqNumber, //
            NVIC_EncodePriority(NVIC_GetPriorityGrouping(), PreemptPriority, SubPriority));
}

} // Nvic
} // Device
} // Stm32f4xx

