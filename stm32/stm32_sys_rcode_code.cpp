/*
 *  Created on: Feb 2, 2018
 *  Author:     wrscode
 *  File:       stm32_sys_rcode_code.cpp
 */

#include "stm32_sys_rcode_code.h"

namespace Stm32
{
namespace System
{
namespace Status
{

GenericCategory::~GenericCategory()
{
}

char const* GenericCategory::name() const
{
    return "GenericCategory";
}

char const* GenericCategory::message(const std::size_t Value) const
{

    switch (static_cast<Enum>(Value))
    {
        case Enum::Success:     return "Success";
        case Enum::DevTimeOut:  return "DevTimeOut";
        case Enum::DevBusy:     return "DevBusy";
        case Enum::WrongArgument:  return "WrongArgument";

        default:
            return "Unknown";
    }
}

Code MakeStatusCode(GenericCategory::Enum Enum)
{
    return Code(static_cast<std::size_t>(Enum), &Stm32::System::Utils::Singleton<GenericCategory>::getInstance());
}

} // namespace RetCode
} // namespace System
} // namespace stm32
