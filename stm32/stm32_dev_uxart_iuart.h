/*
 *  Created on: Dec 23, 2017
 *  Author:     wrscode
 *  File:       stm32_dev_uxart_iuart.h
 */

#ifndef STM32_DEV_UXART_IUART_H_
#define STM32_DEV_UXART_IUART_H_

#include "stm32_sys.h"

namespace Stm32
{
namespace Device
{
namespace Uxart
{
struct IUart
{
    enum class SettingsEnum : std::size_t //
        {
        _BitEmp = 0x00000000U, //
        _Bit00 = 0x00000001U,  //
        _Bit01 = 0x00000002U,  //
        _Bit02 = 0x00000004U,  //
        _Bit03 = 0x00000008U,  //
        _Bit04 = 0x00000010U,  //
        _Bit05 = 0x00000020U,  //
        _Bit06 = 0x00000040U,  //
        _Bit07 = 0x00000080U,  //
        _Bit08 = 0x00000100U,  //
        _Bit09 = 0x00000200U,  //

        WordLength8B = _BitEmp, //
        WordLength9B = _Bit00,  //

        StopBits1 = _BitEmp,           //
        StopBits0p5 = _Bit01,          //
        StopBits1p5 = _Bit01 | _Bit02, //
        StopBits2 = _Bit02,            //

        ParityNone = _BitEmp, //
        ParityEven = _Bit03,  //
        ParityOdd = _Bit04,   //

        HWCtrlNone = _BitEmp, //
        HWCtrlRts = _Bit05,   //
        HWCtrlCts = _Bit06,   //

        ModeRx = _Bit07, //
        ModeTx = _Bit08, //

        OverSampling16x = _BitEmp, //
        OverSampling8x = _Bit09,   //
    };

    enum class CallBackEnum
        : std::size_t //
        {
            TxCompleted = 0x00000001U, //
        TxTimeOut = 0x00000002U, //
        TxError = 0x00000004U, //
        RxCompleted = 0x00000008U, //
        RxTimeOut = 0x00000010U, //
        RxError = 0x00000020U, //
    };

    using CallBackFunction = Stm32::System::Function<void, Stm32::Device::Uxart::IUart*>;

    virtual ~IUart()
    {
    }

    virtual void open(std::size_t BaudRate, SettingsEnum Config,
            Stm32::System::Status::Code& RCode) = 0;
    virtual void close(Stm32::System::Status::Code& RCode) = 0;

    virtual void setIrq(Stm32::System::State NewState) = 0;
    virtual void setIrqPriority(const std::size_t PreemptPriority,
            const std::size_t SubPriority) = 0;

    virtual void setCallBacks(CallBackEnum Type, const CallBackFunction& NewCallBack) = 0;
    virtual void rstCallBacks(CallBackEnum Type) = 0;

    virtual void setTxTimeOut(const std::size_t TimeOut = Stm32::System::Chrono::TimeMaxDelay) = 0;
    virtual void setRxTimeOut(const std::size_t TimeOut = Stm32::System::Chrono::TimeMaxDelay) = 0;

    virtual std::size_t getTxCount() const = 0;
    virtual std::size_t getRxCount() const = 0;

    virtual void writeBlock(void* DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& RCode) = 0;
    virtual void readBlock(void* DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& RCode) = 0;

    virtual void writeNoBlock(void* DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& RCode) = 0;
    virtual void readNoBlock(void* DataPtr, const std::size_t DataSize, Stm32::System::Status::Code& RCode) = 0;
};

/* IUart::Config */
constexpr std::underlying_type<IUart::SettingsEnum>::type SettingsEnumCast(const IUart::SettingsEnum& rhs)
{
    return static_cast<std::underlying_type<IUart::SettingsEnum>::type>(rhs);
}

constexpr IUart::SettingsEnum SettingsEnumCast(const std::underlying_type<IUart::SettingsEnum>::type& rhs)
{
    return static_cast<IUart::SettingsEnum>(rhs);
}

constexpr IUart::SettingsEnum operator|(const IUart::SettingsEnum& lhs, const IUart::SettingsEnum& rhs)
{
    return SettingsEnumCast(SettingsEnumCast(lhs) | SettingsEnumCast(rhs));
}

constexpr IUart::SettingsEnum operator&(const IUart::SettingsEnum& lhs, const IUart::SettingsEnum& rhs)
{
    return SettingsEnumCast(SettingsEnumCast(lhs) && SettingsEnumCast(rhs));
}

constexpr bool operator&&(const IUart::SettingsEnum& lhs, const IUart::SettingsEnum& rhs)
{
    return ((SettingsEnumCast(lhs) & SettingsEnumCast(rhs)) == SettingsEnumCast(rhs));
}

/* IUart::CallBackType */
constexpr std::underlying_type<IUart::CallBackEnum>::type CallBackEnumCast(const IUart::CallBackEnum& rhs)
{
    return static_cast<std::underlying_type<IUart::CallBackEnum>::type>(rhs);
}

constexpr IUart::CallBackEnum CallBackEnumCast(const std::underlying_type<IUart::CallBackEnum>::type& rhs)
{
    return static_cast<IUart::CallBackEnum>(rhs);
}

constexpr IUart::CallBackEnum operator|(const IUart::CallBackEnum& lhs, const IUart::CallBackEnum& rhs)
{
    return CallBackEnumCast(CallBackEnumCast(lhs) | CallBackEnumCast(rhs));
}

constexpr IUart::CallBackEnum operator&(const IUart::CallBackEnum& lhs, const IUart::CallBackEnum& rhs)
{
    return CallBackEnumCast(CallBackEnumCast(lhs) & CallBackEnumCast(rhs));
}

constexpr bool operator&&(const IUart::CallBackEnum& lhs, const IUart::CallBackEnum& rhs)
{
    return ((CallBackEnumCast(lhs) & CallBackEnumCast(rhs)) == CallBackEnumCast(rhs));
}

} // namespace Uxart
} // namespace Device
} // namespace Stm32

#endif /* STM32_DEV_UXART_IUART_H_ */
