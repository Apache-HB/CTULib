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

#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

//check if a type can be used in arithmatic expressions
template<typename T> struct IsArithmatic { static constexpr bool Value = false; };

template<> struct IsArithmatic<float> { static constexpr bool Value = true; };
template<> struct IsArithmatic<double> { static constexpr bool Value = true; };
template<> struct IsArithmatic<long double> { static constexpr bool Value = true; };
template<> struct IsArithmatic<I8> { static constexpr bool Value = true; };
template<> struct IsArithmatic<I16> { static constexpr bool Value = true; };
template<> struct IsArithmatic<I32> { static constexpr bool Value = true; };
template<> struct IsArithmatic<I64> { static constexpr bool Value = true; };
template<> struct IsArithmatic<U8> { static constexpr bool Value = true; };
template<> struct IsArithmatic<U16> { static constexpr bool Value = true; };
template<> struct IsArithmatic<U32> { static constexpr bool Value = true; };
template<> struct IsArithmatic<U64> { static constexpr bool Value = true; };
template<> struct IsArithmatic<bool> { static constexpr bool Value = true; };
template<> struct IsArithmatic<char> { static constexpr bool Value = true; };

//overloads of types with qualifiers
template<typename T> struct IsArithmatic<const          T> { static constexpr bool Value = IsArithmatic<T>; }; 
template<typename T> struct IsArithmatic<      volatile T> { static constexpr bool Value = IsArithmatic<T>; };
template<typename T> struct IsArithmatic<const volatile T> { static constexpr bool Value = IsArithmatic<T>; };

}