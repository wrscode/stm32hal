/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32_dev_ipin.h
 */

#ifndef STM32_DEV_IGPIN_H_
#define STM32_DEV_IGPIN_H_

#include "stm32_sys.h"

namespace Stm32
{
namespace Device
{
struct IPin
{
    enum class Config : std::size_t
    {
        ModeIn = 0x00000000U,     //
        ModeOut = 0x00000001U,    //

        ModeAlt00 = 0x00000002U,  //
        ModeAlt01 = 0x00000012U,  //
        ModeAlt02 = 0x00000022U,  //
        ModeAlt03 = 0x00000032U,  //
        ModeAlt04 = 0x00000042U,  //
        ModeAlt05 = 0x00000052U,  //
        ModeAlt06 = 0x00000062U,  //
        ModeAlt07 = 0x00000072U,  //
        ModeAlt08 = 0x00000082U,  //
        ModeAlt09 = 0x00000092U,  //
        ModeAlt10 = 0x000000A2U,  //
        ModeAlt11 = 0x000000B2U,  //
        ModeAlt12 = 0x000000C2U,  //
        ModeAlt13 = 0x000000D2U,  //
        ModeAlt14 = 0x000000E2U,  //
        ModeAlt15 = 0x000000F2U,  //

        ModeAnalog = 0x00000003U, //

        ModeBit00 = 0x00000001U,  //
        ModeBit01 = 0x00000002U,  //
        ModeBit02 = 0x00000004U,  //
        ModeBit03 = 0x00000008U,  //
        ModeBit04 = 0x00000010U,  //
        ModeBit05 = 0x00000020U,  //
        ModeBit06 = 0x00000040U,  //
        ModeBit07 = 0x00000080U,  //

        SpeedLow = 0x00000000U,   //
        SpeedMedium = 0x00000100U,   //
        SpeedHigh = 0x00000200U,  //
        SpeedVHigh = 0x00000300U, //

        SpeedBit00 = 0x00000100U, //
        SpeedBit01 = 0x00000200U, //
        SpeedBit02 = 0x00000400U, //
        SpeedBit03 = 0x00000800U, //

        OTypePP = 0x00000000U,    //
        OTypeOD = 0x00001000U,    //

        OTypeBit00 = 0x00001000U, //

        PullNo = 0x00000000U,     //
        PullUp = 0x00010000U,     //
        PullDn = 0x00020000U,     //

        PullBit00 = 0x00010000U,  //
        PullBit01 = 0x00020000U,  //
        PullBit02 = 0x00040000U,  //
        PullBit03 = 0x00080000U,  //
    };

    enum class ActiveState
    {
        Normal, Invert
    };

    virtual ~IPin()
    {
    }

    virtual IPin* open(const Stm32::Device::IPin::Config, Stm32::System::RetCode::Code&) = 0;
    virtual IPin* close(Stm32::System::RetCode::Code&) = 0;

    virtual void setState(Stm32::System::State) = 0;
    virtual void setHigh() = 0;
    virtual void setLow() = 0;
    virtual void setToggle() = 0;

    void operator=(Stm32::System::State State)
    {
        setState(State);
    }
};

constexpr IPin::Config operator|(const IPin::Config& lhs, const IPin::Config& rhs)
{
    return static_cast<IPin::Config>( //
              static_cast<std::underlying_type<IPin::Config>::type>(lhs) //
            | static_cast<std::underlying_type<IPin::Config>::type>(rhs));
}

constexpr IPin::Config operator&(const IPin::Config& lhs, const IPin::Config& rhs)
{
    return static_cast<IPin::Config>( //
              static_cast<std::underlying_type<IPin::Config>::type>(lhs) //
            & static_cast<std::underlying_type<IPin::Config>::type>(rhs));
}

constexpr bool operator&&(const IPin::Config& lhs, const IPin::Config& rhs)
{
    return ((static_cast<std::underlying_type<IPin::Config>::type>(lhs) //
            &  static_cast<std::underlying_type<IPin::Config>::type>(rhs)) //
            == static_cast<std::underlying_type<IPin::Config>::type>(rhs));
}
}  // namespace Device
}  // namespace Stm32

#endif /* STM32_DEV_IGPIN_H_ */
