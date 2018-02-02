/*
 *  Created on: Jan 14, 2018
 *  Author:     wrscode
 *  File:       stm32_sys_rcode_code.h
 */

#ifndef STM32_SYS_RCODE_CODE_H_
#define STM32_SYS_RCODE_CODE_H_

#include <type_traits>
#include "stm32_sys_utils.h"

namespace Stm32
{
namespace System
{
namespace Status
{

/* struct ICategory ************************************************************************************************ */
struct Category
{
    virtual ~Category() {}
    virtual char const* name() const = 0;
    virtual char const* message(const std::size_t Value) const = 0;
};

template<typename T>
struct isStatusCode: public std::false_type {
};

/* struct GenericCategory ****************************************************************************************** */
struct GenericCategory : public Category
{
    enum class Enum : std::size_t {
        Success = 0,
        DevTimeOut,
        DevBusy,
        WrongArgument,
    };

    GenericCategory(){}
    virtual ~GenericCategory();
    virtual char const* name() const;
    virtual char const* message(const std::size_t Value) const;

    static constexpr std::underlying_type<GenericCategory::Enum>::type EnumCast(const Enum& rhl){
        return static_cast<std::underlying_type<GenericCategory::Enum>::type>(rhl);
    }
};

class Code;
Code MakeStatusCode(GenericCategory::Enum Enum);

template<>
struct isStatusCode<GenericCategory::Enum> : public std::true_type {
};

/* class Code ****************************************************************************************************** */
class Code
{
public:
    Code(std::size_t Code, Category* Category) :
            mValue(Code), mCategory(Category) {
    }

    Code() : Code(GenericCategory::EnumCast(GenericCategory::Enum::Success), &Stm32::System::Utils::Singleton<GenericCategory>::getInstance()){};

    template<typename T, typename = typename std::enable_if<std::is_enum<T>::value && isStatusCode<T>::value, T>::type>
    Code(T Code) {
        *this = MakeCode(Code);
    }

    Code(const Code& rhs) = default;
    Code(Code&& rhs) = default;

    Code& operator=(const Code& rhs) = default;
    Code& operator=(Code&& rhs) = default;

    template<typename T, typename = typename std::enable_if<std::is_enum<T>::value && isStatusCode<T>::value, T>::type>
    bool operator=(const T rhs) {
        *this = MakeCode(rhs);
        return *this;
    }

    virtual ~Code(){}

    void reset() {
        mValue = 0;
        mCategory = nullptr;
    }

    char const* name() const {
        return mCategory->name();
    }

    char const* message() const {
        return mCategory->message(mValue);
    }

    operator bool() {
        return (mValue == 0);
    }

    friend bool operator==(const Code& lhs, const Code& rhs);

private:
    std::size_t mValue;
    Category* mCategory;
};

inline bool operator==(const Code& lhs, const Code& rhs){
    return ((lhs.mValue == rhs.mValue) &&
            (lhs.mCategory == rhs.mCategory));
}

} // namespace RetCode
} // namespace System
} // namespace stm32

#endif /* STM32_SYS_RCODE_CODE_H_ */
