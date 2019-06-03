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

//check if 2 types are the same
template<typename A, typename B> struct Same : False {};
template<typename T> struct Same<T, T> : True {};

template<typename T> struct IsDecimal : False {};

//check if a type is decimal only (no floating point)
template<> struct IsDecimal<U8> : True {};
template<> struct IsDecimal<U16> : True {};
template<> struct IsDecimal<U32> : True {};
template<> struct IsDecimal<U64> : True {};

template<> struct IsDecimal<I8> : True {};
template<> struct IsDecimal<I16> : True {};
template<> struct IsDecimal<I32> : True {};
template<> struct IsDecimal<I64> : True {};

//check if a type is floating point type
template<typename T> struct IsFloat : False {};

template<> struct IsFloat<F32> : True {};
template<> struct IsFloat<F64> : True {};
}