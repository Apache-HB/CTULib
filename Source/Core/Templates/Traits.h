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

#include "Meta/Macros.h"

#pragma once

//TODO: document

namespace Cthulhu
{

template<typename T>
struct IsPointer { static const bool Value = false; };

template<typename T> struct IsPointer<                  T*>    { static const bool Value = true; };
template<typename T> struct IsPointer<const             T*>    { static const bool Value = true; };
template<typename T> struct IsPointer<volatile          T*>    { static const bool Value = true; };
template<typename T> struct IsPointer<const volatile    T*>    { static const bool Value = true; };

template<typename T> struct IsPointer<const             T>      { static const bool Value = false; };
template<typename T> struct IsPointer<volatile          T>      { static const bool Value = false; };
template<typename T> struct IsPointer<const volatile    T>      { static const bool Value = false; };

template<typename T> struct RemoveReference         { using Type = T; };
template<typename T> struct RemoveReference<T&>     { using Type = T; };
template<typename T> struct RemoveReference<T&&>    { using Type = T; };

template<typename T>
ALWAYSINLINE T&& Forward(typename RemoveReference<T>::Type& Obj)
{
    return (T&&)Obj;
}

template<typename T>
ALWAYSINLINE T&& Forward(typename RemoveReference<T>::Type&& Obj)
{
    return (T&&)Obj;
}

template<typename T> struct RemoveQualifiers { using Type = T; };
template<typename T> struct RemoveQualifiers<const T> { using Type = T; };
template<typename T> struct RemoveQualifiers<volatile T> { using Type = T; };
template<typename T> struct RemoveQualifiers<const volatile T> { using Type = T; };


template<typename T> 
struct DecayNonReference
{
    using Type = typename RemoveQualifiers<T>::Type;
};

template<typename TRet, typename... TArgs>
struct DecayNonReference<TRet(TArgs...)>
{
    using Type = TRet(*)(TArgs...);
};

template<typename T>
struct Decay
{
    using Type = typename DecayNonReference<typename RemoveReference<T>::Type>::Type;
};

}