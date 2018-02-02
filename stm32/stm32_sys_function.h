/*
 *  Created on: Jan 13, 2018
 *  ArgsTypesuthor:     wrscode
 *  File:       stm32_sys_function.h
 */

#ifndef STM32_SYS_FUNCTION_H_
#define STM32_SYS_FUNCTION_H_

#include <utility>

namespace Stm32
{
namespace System
{
template<typename RetType, typename ... ArgsTypes>
class Function
{
    using StubFunction_t = RetType (*)(void*, ArgsTypes&&...);

private:
    Function(void* Object, StubFunction_t StubFunction) noexcept :
        mObject(Object), mStubFunction(StubFunction)
        {
        }

public:
    Function() :
        mObject(nullptr), mStubFunction(DummyFunction)
        {
        }

    Function(const Function&) = default;

    Function(Function&&) = default;

    Function& operator=(const Function& rhs) = default;

    Function& operator=(Function&& rhs) = default;

    RetType operator()(ArgsTypes ... Args) const
    {
        return mStubFunction(mObject, std::forward<ArgsTypes>(Args)...);
    }

    bool operator==(const Function& rhs) const noexcept
    {
        return ((mObject == rhs.mObject) && (mStubFunction == rhs.mStubFunction));
    }

    bool operator!=(const Function& rhs) const noexcept
    {
        return !operator==(rhs);
    }

    template<RetType (* const FunctionPointer)(ArgsTypes...)>
    static Function bind() noexcept
    {
        return Function(nullptr, StubFunction<FunctionPointer>);
    }

    template<class C, RetType (C::*MethodPointer)(ArgsTypes...)>
    static Function bind(C * const ObjectPtr) noexcept
    {
        return Function(ObjectPtr, StubClassMethod<C, MethodPointer>);
    }

    template<class C, RetType (C::*ConstMethodPointer)(ArgsTypes...) const>
    static Function bind(C const* const ObjectPtr) noexcept
    {
        return Function(const_cast<C* const >(ObjectPtr), StubConstClassMethod<C, ConstMethodPointer>);
    }

    void reset()
    {
        mObject = nullptr;
        mStubFunction = DummyFunction;
    }

private:
    template<RetType (*FunctionPointer)(ArgsTypes...)>
    static RetType StubFunction(void*, ArgsTypes&&... args)
    {
        return FunctionPointer(::std::forward<ArgsTypes>(args)...);
    }

    template<class C, RetType (C::*MethodPointer)(ArgsTypes...)>
    static RetType StubClassMethod(void* Obj, ArgsTypes&&... args)
    {
        return (static_cast<C*>(Obj)->*MethodPointer)(::std::forward<ArgsTypes>(args)...);
    }

    template<class C, RetType (C::*ConstMethodPointer)(ArgsTypes...) const>
    static RetType StubConstClassMethod(void* Obj, ArgsTypes&&... args)
    {
        return (static_cast<C const* const >(Obj)->*ConstMethodPointer)(::std::forward<ArgsTypes>(args)...);
    }

    static RetType DummyFunction(void* Obj, ArgsTypes&&... args)
    {
        (void)Obj;
        return RetType();
    }

private:
    void* mObject;
    StubFunction_t mStubFunction;
};

} // namespace System
} // namespace STM32

#endif /* STM32_SYS_FUNCTION_H_ */
