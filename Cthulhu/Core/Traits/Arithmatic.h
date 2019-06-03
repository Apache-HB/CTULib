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
#include "Traits.h"

#pragma once

namespace Cthulhu
{

//check if a type can be used in arithmatic expressions
template<typename T> struct IsArithmatic : False { static constexpr bool Value = false; };

template<> struct IsArithmatic<float> : True {};
template<> struct IsArithmatic<double> : True {};
template<> struct IsArithmatic<long double> : True {};
template<> struct IsArithmatic<I8> : True {};
template<> struct IsArithmatic<I16> : True {};
template<> struct IsArithmatic<I32> : True {};
template<> struct IsArithmatic<I64> : True {};
template<> struct IsArithmatic<U8> : True {};
template<> struct IsArithmatic<U16> : True {};
template<> struct IsArithmatic<U32> : True {};
template<> struct IsArithmatic<U64> : True {};
template<> struct IsArithmatic<bool> : True {};
template<> struct IsArithmatic<char> : True {};

//overloads of types with qualifiers
template<typename T> struct IsArithmatic<const T> : IsArithmatic<T> {}; 
template<typename T> struct IsArithmatic<volatile T> : IsArithmatic<T> {};
template<typename T> struct IsArithmatic<const volatile T> : IsArithmatic<T> {};

}