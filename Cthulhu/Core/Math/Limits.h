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

template<typename T>
struct Limits
{
    static T Max();
    static T Min();
};

template<> 
struct Limits<I8>
{
    static I8 Max() { return 127; }
    static I8 Min() { return -128; }
};

template<> 
struct Limits<I16>
{
    static I16 Max() { return 32767; }
    static I16 Min() { return -32768; }
};

template<> 
struct Limits<I32>
{
    static I32 Max() { return 2147483647; }
    static I32 Min() { return -2147483648; }
};

template<> 
struct Limits<I64>
{
    static I64 Max() { return 9223372036854775807LL; }
    static I64 Min() { return -9223372036854775807LL; }
};

template<> 
struct Limits<U8>
{
    static U8 Max() { return 255; }
    static U8 Min() { return 0; }
};

template<> 
struct Limits<U16>
{
    static U16 Max() { return 65535; }
    static U16 Min() { return 0; }
};

template<> 
struct Limits<U32>
{
    static U32 Max() { return 4294967295; }
    static U32 Min() { return 0; }
};

template<> 
struct Limits<U64>
{
    static U64 Max() { return 18446744073709551615ULL; }
    static U64 Min() { return 0; }
};

}
