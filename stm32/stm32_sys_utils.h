/*
 *  Created on: Dec 30, 2017
 *  Author:     wrscode
 *  File:       stm32_sys_utils.h
 */

#ifndef STM32_SYS_UTILS_H_
#define STM32_SYS_UTILS_H_

#include <cstdint>
#include <type_traits>

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

template<class C>
struct Singleton
{
    inline static C& getInstance(){
        static_assert(std::is_class<C>::value, "This Singleton template working only with Classes!!!");
        static C Instance;
        return Instance;
    }

    ~Singleton(){}

private:
    Singleton(){}

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

}  // namespace Utils
}  // namespace System
}  // namespace stm32

#endif /* STM32_SYS_UTILS_H_ */
