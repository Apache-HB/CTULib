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

#include "Core/Templates/Traits.h"
#include "Core/Templates/Invoke.h"
#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#pragma once

namespace Cthulhu
{

namespace Private
{

template<typename, typename> struct LambdaCaller;

template<typename TFunctor, typename TRet, typename... TArgs>
struct LambdaCaller<TFunctor, TRet(TArgs...)>
{
    static TRet Call(void* Object, TArgs... Args)
    {
        return Invoke(*(TFunctor*)Object, Forward<TArgs>(Args)...);
    }
};

template<typename, typename> struct LambdaBase;

template<typename TDerived, typename TRet, typename... TArgs>
struct LambdaBase<TDerived, TRet(TArgs...)>
{
    TRet operator()(TArgs... Args) const
    {
        const TDerived* Derived = static_cast<const TDerived*>(this);
        return Callback(Derived->Ptr, Args...);
    }

protected:

    template<typename T>
    void Set(T* Functor)
    {
        Callback = &LambdaCaller<T, TRet(TArgs...)>::Call;
    }

private:

    TRet(*Callback)(void*, TArgs...);
};

} //Private

template<typename TFunctor>
struct Lambda : Private::LambdaBase<Lambda<TFunctor>, TFunctor>
{
    using Super = Private::LambdaBase<Lambda<TFunctor>, TFunctor>;

    friend Super;

    template<typename TFunction>
    Lambda(TFunction& Other)
    {
        Set(&Other);
    }

    template<typename TFunction>
    Lambda(const TFunction& Other)
    {
        Set(&Other);
    }

    template<typename TFunction>
    Lambda(TFunction* Functor)
    {
        Set(Functor);
    }
private:

    template<typename TFunction>
    void Set(TFunction* Function)
    {
        Ptr = (void*)Function;
        Super::Set(Function);
    }

    void* Ptr;
};

}