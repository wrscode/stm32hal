/*
 *  Created on: Dec 17, 2017
 *  Author:     wrscode
 *  File:       stm32f_timer.h
 */

#ifndef STM32_SYS_TIMER_H_
#define STM32_SYS_TIMER_H_

#include <cstdint>
#include <limits>

namespace Stm32
{
namespace System
{
namespace Chrono
{
enum
{
    TimeMaxDelay = std::numeric_limits<std::size_t>::max()
};

inline std::size_t GetTime()
{
    extern volatile std::size_t SystemTime;
    return SystemTime;
}

inline void IncrementTime()
{
    extern volatile std::size_t SystemTime;
    ++SystemTime;
}

} // namespace Chrono
} // namespace System
} // namespace Stm32

#endif /* STM32_SYS_TIMER_H_ */
