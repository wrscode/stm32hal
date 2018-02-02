/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       Stm32f4xx_uart.h
 */

#ifndef STM32F4XX_UXART_UART_H_
#define STM32F4XX_UXART_UART_H_

#include "stm32_dev_ipin.h"
#include "stm32_dev_uxart_iuart.h"
#include "stm32_sys_irqservice.h"
#include "stm32f4xx_dev_cfg_uxart.h"
#include "stm32f4xx_dev_int_uxart.h"
#include "stm32f4xx_dev_nvic_mrg.h"
#include "stm32f4xx_bitband.h"
#include <cstdint>

namespace Stm32f4xx
{
namespace Device
{
namespace Uxart
{
template<const size_t UxartNumber,     //
        const char TxGpioL = 'X', //
        const char TxPinN = 0U,   //
        const Stm32::Device::IPin::SettingsEnum TxCfg = Stm32::Device::IPin::SettingsEnum::ModeIn, //
        const char RxGpioL = 'X', //
        const char RxPinN = 0U,   //
        const Stm32::Device::IPin::SettingsEnum RxCfg = Stm32::Device::IPin::SettingsEnum::ModeIn, //
        const char CtsGpioL = 'X', //
        const char CtsPinN = 0U,  //
        const Stm32::Device::IPin::SettingsEnum CtsCfg = Stm32::Device::IPin::SettingsEnum::ModeIn, //
        const char RtsGpioL = 'X', //
        const char RtsPinN = 0U,  //
        const Stm32::Device::IPin::SettingsEnum RtsCfg = Stm32::Device::IPin::SettingsEnum::ModeIn> //
class Uart: public Stm32::Device::Uxart::IUart, public Stm32::System::IrqService::IrqService
{
private:
    enum
    {
        BaseAddress = Stm32f4xx::Device::Config::Uxart::Structure<UxartNumber>::BaseAddress, //
        IrqNumber = Stm32f4xx::Device::Config::Uxart::Structure<UxartNumber>::IrqNumber, //
        BitBandAddress = Stm32f4xx::BitBand::PeriphAddr2BBAddr<BaseAddress>::BBAddress, //
        ClockType = Stm32f4xx::Device::Config::Uxart::Structure<UxartNumber>::ClockType, //, //
    };

public:
    Uart()
            : mTxPtr(nullptr), mTxSize(0U), mTxTimeOut(Stm32::System::Chrono::TimeMaxDelay), //
            mTxCount(0U), mTxTickTime(0), //
            mRxPtr(nullptr), mRxSize(0U), mRxTimeOut(Stm32::System::Chrono::TimeMaxDelay), //
            mRxCount(0U), mRxTickTime(0), //
            mCbTxCompleted(), mCbTxTimeOut(), mCbTxError(), mCbCompleted(), mCbRxTimeOut(), mCbRxError()
    {
    }

    virtual ~Uart()
    {
    }

    virtual void open(const std::size_t BaudRate, const Stm32::Device::Uxart::IUart::SettingsEnum Config,
            Stm32::System::Status::Code& Code)
    {
        Rcc::Uxart<UxartNumber>::setClock(Stm32::System::State::Enable);

        mTxPin.open(TxCfg, Code);
        if (!Code)
        {
            return;
        }

        mRxPin.open(RxCfg, Code);
        if (!Code)
        {
            return;
        }

        mCtsPin.open(CtsCfg, Code);
        if (!Code)
        {
            return;
        }

        mRtPin.open(RtsCfg, Code);
        if (!Code)
        {
            return;
        }

        //disable
        mBBInstance->cr1.ue = RESET;

        //stop bit
        mBBInstance->cr2.stop[0] = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::_Bit01) ? //
                SET : RESET;

        mBBInstance->cr2.stop[1] = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::_Bit02) ? //
                SET : RESET;

        mBBInstance->cr2.linen = RESET;

        mBBInstance->cr2.clken = RESET;

        //parity
        mBBInstance->cr1.pce = ((Config && Stm32::Device::Uxart::IUart::SettingsEnum::ParityEven) || //
                (Config && Stm32::Device::Uxart::IUart::SettingsEnum::ParityOdd)) ? SET : RESET;

        mBBInstance->cr1.ps = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::ParityOdd) ? //
                SET : RESET;

        //word length
        mBBInstance->cr1.m = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::WordLength9B) ? //
                SET : RESET;

        mBBInstance->cr1.te = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::ModeTx) ? //
                SET : RESET;

        mBBInstance->cr1.re = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::ModeRx) ? //
                SET : RESET;

        mBBInstance->cr3.rtse = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::HWCtrlRts) ? //
                SET : RESET;

        mBBInstance->cr3.ctse = (Config && Stm32::Device::Uxart::IUart::SettingsEnum::HWCtrlCts) ? //
                SET : RESET;

        mBBInstance->cr3.scen = RESET;

        mBBInstance->cr3.hdsel = RESET;

        mBBInstance->cr3.iren = RESET;

        std::size_t Sampling
            { 0U };
        if (Config && Stm32::Device::Uxart::IUart::SettingsEnum::OverSampling8x)
        {
            mBBInstance->cr1.over8 = SET;
            Sampling = 8U;
        } else
        {
            mBBInstance->cr1.over8 = RESET;
            Sampling = 16U;
        }

        std::size_t ClockFrequency = //
                Rcc::SysClock::getFrequency(static_cast<Stm32::Device::Rcc::ClockType>(ClockType), Code);
        if (!Code)
        {
            return;
        }

        mInstance->BRR = Inside::Uxart::CalcValueOfBRR(ClockFrequency, BaudRate, Sampling);

        //enable
        mBBInstance->cr1.ue = SET;

        return;
    }

    virtual void close(Stm32::System::Status::Code& RCode)
    {
        mTxPin.close(RCode);
        if (!RCode)
        {
            return;
        }

        mRxPin.close(RCode);
        if (!RCode)
        {
            return;
        }

        mCtsPin.close(RCode);
        if (!RCode)
        {
            return;
        }

        mRtPin.close(RCode);
        if (!RCode)
        {
            return;
        }

        Rcc::Uxart<UxartNumber>::setClock(Stm32::System::State::Disable);

        return;
    }

    virtual void setIrq(const Stm32::System::State NewState)
    {
        Nvic::setIrqHandler(static_cast<IRQn_Type>(IrqNumber), this);
        Nvic::setIrq(static_cast<IRQn_Type>(IrqNumber), NewState);
        return;
    }

    virtual void setIrqPriority(const std::size_t PreemptPriority, const std::size_t SubPriority)
    {
        Nvic::setIrqPriority(static_cast<IRQn_Type>(IrqNumber), PreemptPriority, SubPriority);
        return;
    }

    virtual void setCallBacks(const Stm32::Device::Uxart::IUart::CallBackEnum Type,
            const Stm32::Device::Uxart::IUart::CallBackFunction& NewCallBack)
    {
        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::TxCompleted)
        {
            mCbTxCompleted = NewCallBack;
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::TxTimeOut)
        {
            mCbTxTimeOut = NewCallBack;
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::TxError)
        {
            mCbTxError = NewCallBack;
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::RxCompleted)
        {
            mCbCompleted = NewCallBack;
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::RxTimeOut)
        {
            mCbRxTimeOut = NewCallBack;
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::RxError)
        {
            mCbRxError = NewCallBack;
        }

        return;
    }

    virtual void rstCallBacks(const Stm32::Device::Uxart::IUart::CallBackEnum Type)
    {

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::TxCompleted)
        {
            mCbTxCompleted.reset();
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::TxTimeOut)
        {
            mCbTxTimeOut.reset();
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::TxError)
        {
            mCbTxError.reset();
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::RxCompleted)
        {
            mCbCompleted.reset();
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::RxTimeOut)
        {
            mCbRxTimeOut.reset();
        }

        if (Type && Stm32::Device::Uxart::IUart::CallBackEnum::RxError)
        {
            mCbRxError.reset();
        }

        return;
    }

    virtual void setTxTimeOut(const std::size_t TimeOut)
    {
        mTxTimeOut = TimeOut;
    }

    virtual void setRxTimeOut(const std::size_t TimeOut)
    {
        mRxTimeOut = TimeOut;
    }

    virtual std::size_t getTxCount() const
    {
        return mTxCount;
    }

    virtual std::size_t getRxCount() const
    {
        return mRxCount;
    }

    virtual void writeBlock(void *DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& Code)
    {
        if (DataPtr == nullptr || DataSize == 0x00U)
        {
            Code = Stm32::System::Status::MakeStatusCode(Stm32::System::Status::GenericCategory::Enum::WrongArgument);
            return;
        }

        mTxPtr = reinterpret_cast<std::uint8_t*>(DataPtr);
        mTxSize = DataSize;
        mTxCount = 0U;
        mTxTickTime = Stm32::System::Chrono::GetTime();

        if (mBBInstance->cr1.m != RESET) // 9b word length
        {
            if (mBBInstance->cr1.pce != RESET) // parity enable
            {
                for (; mTxCount < mTxSize; mTxCount += 1, mTxPtr += 1)
                {
                    /* Wait for TXE */
                    while (mBBInstance->sr.txe == RESET)
                    {
                        if (CheckTxIsTickTimeOut())
                        {
                            goto errorTimeOut;
                        }
                    }
                    mInstance->DR = (*reinterpret_cast<std::uint16_t*>(mTxPtr)) & 0x01FFU;
                }
            } else  // parity disable
            {
                for (; mTxCount < mTxSize; mTxCount += 1, mTxPtr += 2)
                {
                    /* Wait for TXE */
                    while (mBBInstance->sr.txe == RESET)
                    {
                        if (CheckTxIsTickTimeOut())
                        {
                            goto errorTimeOut;
                        }
                    }
                    mInstance->DR = (*reinterpret_cast<std::uint16_t*>(mTxPtr)) & 0x01FFU;
                }
            }
        } else // 8b word length
        {
            for (; mTxCount < mTxSize; mTxCount += 1, mTxPtr += 1)
            {
                /* Wait for TXE */
                while (mBBInstance->sr.txe == RESET)
                {
                    if (CheckTxIsTickTimeOut())
                    {
                        goto errorTimeOut;
                    }
                }
                mInstance->DR = *mTxPtr & 0xFFU;
            }
        }

        /* Wait for TC */
        while (mBBInstance->sr.tc == RESET)
        {
            if (CheckTxIsTickTimeOut())
            {
                goto errorTimeOut;
            }
        }

        return;

        errorTimeOut: //
        Code = Stm32::System::Status::MakeStatusCode(Stm32::System::Status::GenericCategory::Enum::DevTimeOut);
    }

    virtual void readBlock(void *DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& Code)
    {
        if (DataPtr == nullptr || DataSize == 0x00U)
        {
            Code = Stm32::System::Status::MakeStatusCode(Stm32::System::Status::GenericCategory::Enum::WrongArgument);
            return;
        }

        mRxPtr = reinterpret_cast<std::uint8_t*>(DataPtr);
        mRxSize = DataSize;
        mRxCount = 0U;
        mRxTickTime = Stm32::System::Chrono::GetTime();

        if (mBBInstance->cr1.m != RESET) // 9b word length
        {
            if (mBBInstance->cr1.pce != RESET) // parity enable
            {
                for (; mRxCount < mRxSize; mRxCount += 1, mRxPtr += 1)
                {
                    /* Wait for RXNE */
                    while (mBBInstance->sr.rxne == RESET)
                    {
                        if (CheckRxIsTickTimeOut())
                        {
                            goto errorTimeOut;
                        }
                    }
                    *(reinterpret_cast<std::uint16_t*>(mRxPtr)) = mInstance->DR & 0x00FFU;
                }
            } else // parity disable
            {
                for (; mRxCount < mRxSize; mRxCount += 1, mRxPtr += 2)
                {
                    /* Wait for RXNE */
                    while (mBBInstance->sr.rxne == RESET)
                    {
                        if (CheckRxIsTickTimeOut())
                        {
                            goto errorTimeOut;
                        }
                    }
                    *(reinterpret_cast<std::uint16_t*>(mRxPtr)) = mInstance->DR & 0x01FFU;
                }
            }
        } else // 8b word length
        {
            for (; mRxCount < mRxSize; mRxCount += 1, mRxPtr += 1)
            {
                /* Wait for RXNE */
                while (mBBInstance->sr.rxne == RESET)
                {
                    if (CheckRxIsTickTimeOut())
                    {
                        goto errorTimeOut;
                    }
                }
                *(reinterpret_cast<std::uint8_t*>(mRxPtr)) = mInstance->DR & 0xFFU;
            }
        }

        errorTimeOut: //
        Code = Stm32::System::Status::MakeStatusCode(Stm32::System::Status::GenericCategory::Enum::DevTimeOut);
    }

    virtual void writeNoBlock(void *DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& Code)
    {
        if (DataPtr == nullptr || DataSize == 0x00U)
        {
            Code = Stm32::System::Status::MakeStatusCode(Stm32::System::Status::GenericCategory::Enum::WrongArgument);
            return;
        }

        mTxPtr = reinterpret_cast<std::uint8_t*>(DataPtr);
        mTxSize = DataSize;
        mTxCount = 0U;
        mTxTickTime = Stm32::System::Chrono::GetTime();

        mBBInstance->cr1.tcie = RESET; //disable transmit complete interrupt
        mBBInstance->cr1.txeie = SET; //enable transmit interrupt

        //    return Stm32::TYPE::Status(Stm32::TYPE::Status::Code::Ok);
    }

    virtual void readNoBlock(void *DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& Code)
    {
        if (DataPtr == nullptr || DataSize == 0x00U)
        {
            Code = Stm32::System::Status::MakeStatusCode(Stm32::System::Status::GenericCategory::Enum::WrongArgument);
            return;
        }

        mRxPtr = reinterpret_cast<std::uint8_t*>(DataPtr);
        mRxSize = DataSize;
        mRxCount = 0U;
        mRxTickTime = Stm32::System::Chrono::GetTime();

        //    mBBInstance->cr3.eie = UTILS::State::Set; //enable frame, noise, overrun interrupt
        //    mBBInstance->cr1.peie = UTILS::State::Set; //enable parity error interrupt
        mBBInstance->cr1.rxneie = SET; //enable register not empty interrupt

        //    return Stm32::TYPE::Status(Stm32::TYPE::Status::Code::Ok);
    }

    virtual void irqHandler()
    {
        /* UART in mode Receiver -------------------------------------------------*/
        if ((mBBInstance->sr.rxne != RESET) && //
                (mBBInstance->cr1.rxneie != RESET))
        {
            if (CheckRxIsTickTimeOut())
            {
                mBBInstance->cr1.rxneie = RESET;
                //            mBBInstance->cr1.peie = UTILS::State::Reset;
                //            mBBInstance->cr3.eie = UTILS::State::Reset;
                mCbRxTimeOut(this);
                return;
            }

            if (mBBInstance->cr1.m != RESET) // 9b word length
            {
                if (mBBInstance->cr1.pce != RESET) // parity enable
                {
                    *(reinterpret_cast<std::uint16_t*>(mRxPtr)) = mInstance->DR & 0x00FFU;
                    mRxPtr += 1;
                } else
                {
                    *(reinterpret_cast<std::uint16_t*>(mRxPtr)) = mInstance->DR & 0x01FFU;
                    mRxPtr += 2;
                }
            } else
            { // 8b word length
                *(reinterpret_cast<std::uint8_t*>(mRxPtr)) = mInstance->DR & 0xFFU;
                mRxPtr += 1;
            }

            mRxCount++;
            mRxTickTime = Stm32::System::Chrono::GetTime();
            if (mRxSize <= mRxCount)
            {
                mBBInstance->cr1.rxneie = RESET;
                //            mBBInstance->cr1.peie = UTILS::State::Reset;
                //            mBBInstance->cr3.eie = UTILS::State::Reset;
                mCbCompleted(this);
                return;
            }
            return;
        }

        /* UART in mode Transmitter ------------------------------------------------*/
        if ((mBBInstance->sr.txe != RESET) && //
                (mBBInstance->cr1.txeie != RESET))
        {
            if (CheckTxIsTickTimeOut())
            {
                mBBInstance->cr1.txeie = RESET;
                mCbTxTimeOut(this);
                return;
            }

            if (mBBInstance->cr1.m != RESET) // 9b word length
            {
                if (mBBInstance->cr1.pce != RESET) // parity enable
                {
                    mInstance->DR = (*reinterpret_cast<std::uint16_t*>(mTxPtr)) & 0x01FFU;
                    mTxPtr += 1;
                } else  // parity disable
                {
                    mInstance->DR = (*reinterpret_cast<std::uint16_t*>(mTxPtr)) & 0x01FFU;
                    mTxPtr += 2;
                }
            } else // 8b word length
            {
                mInstance->DR = *mTxPtr & 0xFFU;
                mTxPtr += 1;
            }

            mTxCount += 1;
            mTxTickTime = Stm32::System::Chrono::GetTime();
            if (mTxSize <= mTxCount)
            {
                mBBInstance->cr1.txeie = RESET;
                mBBInstance->cr1.tcie = SET;
            }
            return;
        }

        /* UART in mode Transmitter end --------------------------------------------*/
        if ((mBBInstance->sr.tc != RESET) && //
                (mBBInstance->cr1.tcie != RESET))
        {
            mBBInstance->cr1.tcie = RESET;

            if (CheckTxIsTickTimeOut())
            {
                mCbTxTimeOut(this);
                return;
            }

            mCbTxCompleted(this);
            return;
        }
    }

private:
    inline bool CheckRxIsTickTimeOut()
    {
        if (mRxTimeOut != Stm32::System::Chrono::TimeMaxDelay)
        {
            if (mRxTimeOut < (Stm32::System::Chrono::GetTime() - mRxTickTime))
            {
                return true;
            }
        }
        return false;
    }

    inline bool CheckTxIsTickTimeOut()
    {
        if (mTxTimeOut != Stm32::System::Chrono::TimeMaxDelay)
        {
            if (mTxTimeOut < (Stm32::System::Chrono::GetTime() - mTxTickTime))
            {
                return true;
            }
        }
        return false;
    }

private:
    static const Stm32::System::Utils::ConversionAddressToPointerType<BaseAddress, USART_TypeDef> mInstance;
    static const Stm32::System::Utils::ConversionAddressToPointerType<BitBandAddress,
            Stm32f4xx::Device::Inside::Uxart::BitBand_t> mBBInstance;

    std::uint8_t* mTxPtr;
    std::size_t mTxSize;
    std::size_t mTxTimeOut;
    volatile std::size_t mTxCount;
    volatile std::size_t mTxTickTime;

    std::uint8_t* mRxPtr;
    std::size_t mRxSize;
    std::size_t mRxTimeOut;
    volatile std::size_t mRxCount;
    volatile std::size_t mRxTickTime;

    using UartCbkFunction = Stm32::Device::Uxart::IUart::CallBackFunction;

    UartCbkFunction mCbTxCompleted;
    UartCbkFunction mCbTxTimeOut;
    UartCbkFunction mCbTxError;
    UartCbkFunction mCbCompleted;
    UartCbkFunction mCbRxTimeOut;
    UartCbkFunction mCbRxError;

    Stm32f4xx::Device::Pin<TxGpioL, TxPinN> mTxPin;
    Stm32f4xx::Device::Pin<RxGpioL, RxPinN> mRxPin;
    Stm32f4xx::Device::Pin<CtsGpioL, CtsPinN> mCtsPin;
    Stm32f4xx::Device::Pin<RtsGpioL, RtsPinN> mRtPin;
};

template< //
        const size_t UxartNumber, //
        const char TxGpioL,  //
        const char TxPinN,   //
        const Stm32::Device::IPin::SettingsEnum TxCfg, //
        const char RxGpioL,  //
        const char RxPinN,   //
        const Stm32::Device::IPin::SettingsEnum RxCfg, //
        const char CtsGpioL, //
        const char CtsPinN,  //
        const Stm32::Device::IPin::SettingsEnum CtsCfg,  //
        const char RtsGpioL, const char RtsPinN,  //
        const Stm32::Device::IPin::SettingsEnum RtsCfg>
const Stm32::System::Utils::ConversionAddressToPointerType<
        Uart<UxartNumber, TxGpioL, TxPinN, TxCfg, RxGpioL, RxPinN, RxCfg, CtsGpioL, CtsPinN, CtsCfg, RtsGpioL, RtsPinN,
                RtsCfg>::BaseAddress, USART_TypeDef> Uart<UxartNumber, TxGpioL, TxPinN, TxCfg, RxGpioL, RxPinN, RxCfg,
        CtsGpioL, CtsPinN, CtsCfg, RtsGpioL, RtsPinN, RtsCfg>::mInstance;

template< //
        const size_t UxartNumber, //
        const char TxGpioL,  //
        const char TxPinN,   //
        const Stm32::Device::IPin::SettingsEnum TxCfg, //
        const char RxGpioL,  //
        const char RxPinN,   //
        const Stm32::Device::IPin::SettingsEnum RxCfg, //
        const char CtsGpioL, //
        const char CtsPinN,  //
        const Stm32::Device::IPin::SettingsEnum CtsCfg,  //
        const char RtsGpioL, const char RtsPinN,  //
        const Stm32::Device::IPin::SettingsEnum RtsCfg>
const Stm32::System::Utils::ConversionAddressToPointerType<
        Uart<UxartNumber, TxGpioL, TxPinN, TxCfg, RxGpioL, RxPinN, RxCfg, CtsGpioL, CtsPinN, CtsCfg, RtsGpioL, RtsPinN,
                RtsCfg>::BitBandAddress, Stm32f4xx::Device::Inside::Uxart::BitBand_t> Uart<UxartNumber, TxGpioL, TxPinN,
        TxCfg, RxGpioL, RxPinN, RxCfg, CtsGpioL, CtsPinN, CtsCfg, RtsGpioL, RtsPinN, RtsCfg>::mBBInstance;

} // namespace Uxart
} // namespace Device
} // namespace Stm32f4xx

#endif /* STM32F4XX_UXART_UART_H_ */

