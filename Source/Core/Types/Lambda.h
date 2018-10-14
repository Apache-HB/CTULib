/**   Copyright 2018 Elliot Haisley Brown
 *
 *  Licensed under the (modified) Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      https://github.com/Apache-HB/CTULib/blob/master/LICENSE
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "Core/Traits/Traits.h"
#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#pragma once

namespace Cthulhu
{

template<typename> class Lambda;

template<typename TRet, typename... TArgs>
struct Lambda<TRet(TArgs...)>
{
    Lambda()
        : ObjectPtr(nullptr)
        , StubPtr(nullptr)
    {}

    template<typename T, TRet(T::*TMethod)(TArgs...)>
    Lambda(T* Object)
        : ObjectPtr(Object)
        , StubPtr(&MethodStub<T, TMethod>)
    {}

    template<typename T, TRet(T::*TMethod)(TArgs...)>
    static Lambda FromMethod(T* Object)
    {
        Lambda Ret;
        Ret.ObjectPtr = Object;
        Ret.StubPtr = &MethodStub<T, TMethod>;
        return Ret;
    }

    TRet operator()(TArgs... Args) const
    {
        return (*StubPtr)(ObjectPtr, Args...);
    }

private:
    using StubType = TRet(*)(void*, TArgs...);

    void* ObjectPtr;
    StubType StubPtr;

    template<typename T, TRet(T::*TMethod)(TArgs...)>
    static void MethodStub(void* InObjectPtr, TArgs&&... Args)
    {
        T* Object = static_cast<T*>(InObjectPtr);
        return (Object->*TMethod)(Args...);
    }
};

}