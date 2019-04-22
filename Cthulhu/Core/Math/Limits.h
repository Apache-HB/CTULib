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

namespace Cthulhu::Math
{

template<typename T>
struct Limits
{
    static constexpr T Max();
    static constexpr T Min();
};

template<> 
struct Limits<I8>
{
    static constexpr I8 Max() { return 127; }
    static constexpr I8 Min() { return -127; }
};

template<> 
struct Limits<I16>
{
    static constexpr I16 Max() { return 32767; }
    static constexpr I16 Min() { return -32767; }
};

template<> 
struct Limits<I32>
{
    static constexpr I32 Max() { return 2147483647; }
    static constexpr I32 Min() { return -2147483647; }
};

template<> 
struct Limits<I64>
{
    static constexpr I64 Max() { return 9223372036854775807LL; }
    static constexpr I64 Min() { return -9223372036854775807LL; }
};

template<> 
struct Limits<U8>
{
    static constexpr U8 Max() { return 255; }
    static constexpr U8 Min() { return 0; }
};

template<> 
struct Limits<U16>
{
    static constexpr U16 Max() { return 65535; }
    static constexpr U16 Min() { return 0; }
};

template<> 
struct Limits<U32>
{
    static constexpr U32 Max() { return 4294967295; }
    static constexpr U32 Min() { return 0; }
};

template<> 
struct Limits<U64>
{
    static constexpr U64 Max() { return 18446744073709551615ULL; }
    static constexpr U64 Min() { return 0; }
};

} // Cthulhu::Math
