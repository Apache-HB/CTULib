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

#include "Traits.h"

#pragma once

namespace Cthulhu
{

//compile time logic

//Not<expr> is equivilent to !expr
template<typename T> struct Not { static constexpr bool Value = !T::Value; };

//equivilent to ||
template<bool...> struct Or;

template<bool TLeft, bool... TRight>
struct OrValue
{
    static constexpr bool Value = Or<TRight...>::Value;
};

template<bool... T>
struct OrValue<true, T...> : True {};

template<bool TLeft, bool... TRight>
struct Or<TLeft, TRight...> : OrValue<TLeft, TRight...> {};

template<>
struct Or<> : False {};


//equivilent to &&
template<typename... T>
struct And;

template<bool TLeft, typename... TRight>
struct AndValue
{
    static constexpr bool Value = And<TRight...>::Value;
};

template<typename... T>
struct AndValue<false, T...> : False {};

template<typename TLeft, typename... TRight>
struct And<TLeft, TRight...> : AndValue<TLeft::Value, TRight...> {};

template<>
struct And<> : False {};

}