/*
 *  Created on: Dec 30, 2017
 *  Author:     wrscode
 *  File:       stm32_sys_utils.h
 */

#ifndef STM32_SYS_UTILS_H_
#define STM32_SYS_UTILS_H_

#include <cstdint>

namespace Stm32
{
namespace System
{
namespace Utils
{
template<std::size_t Address, typename PointerType>
struct ConversionAddressToPointerType
{
    PointerType* operator->() const
    {
        return reinterpret_cast<PointerType*>(Address);
    }

    PointerType& operator*() const
    {
        return (*reinterpret_cast<PointerType*>(Address));
    }
};
}  // namespace Utils
}  // namespace System
}  // namespace stm32

#endif /* STM32_SYS_UTILS_H_ */
