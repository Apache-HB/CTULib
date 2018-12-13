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

#include "Logic.h"
#include "IsPOD.h"

#pragma once

namespace Cthulhu
{

namespace Private
{
    template<typename T, bool IsEnum = __is_enum(T)>
    struct TrivialDestructor
    {
        static constexpr bool Value = true;
    };

    template<typename T>
    struct TrivialDestructor<T, false>
    {
        static constexpr bool Value = __has_trivial_destructor(T);
    };
}

template<typename T>
struct IsTriviallyDestructable
{
    static constexpr bool Value = Private::TrivialDestructor<T>::Value;
};

template<typename T>
struct IsTriviallyCopyable
{
    static constexpr bool Value = Or<__has_trivial_copy(T), IsPOD<T>>::Value;
};

template<typename T>
struct IsTriviallyAssignable
{
    static constexpr bool Value = Or<__has_trivial_assign(T), IsPOD<T>>::Value;
};

template<typename T>
struct IsTrivial
{
    static constexpr bool Value = And<IsTriviallyDestructable<T>, IsTriviallyCopyable<T>, IsTriviallyAssignable<T>>::Value;
};

}