/*
 *  Created on: Jan 14, 2018
 *  Author:     wrscode
 *  File:       stm32_sys_rcode_code.h
 */

#ifndef STM32_SYS_RCODE_CODE_H_
#define STM32_SYS_RCODE_CODE_H_

namespace Stm32
{
namespace System
{
namespace RetCode
{
class Code
{
public:


    operator bool() {
        return true;
    }
};
} // namespace RetCode
} // namespace System
} // namespace stm32

#endif /* STM32_SYS_RCODE_CODE_H_ */
