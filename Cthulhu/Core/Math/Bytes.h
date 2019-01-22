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
#include "Meta/Macros.h"


#if defined(CC_CLANG) || defined(CC_GCC)
#   include <endian.h>
#else
#   include <stdlib.h>
#endif

#pragma once

namespace Cthulhu::Math
{

ALWAYSINLINE U16 ByteSwap(U16 Data)
{
#if defined(CC_MSVC)
    return _byteswap_ushort(Data);
#elif defined(CC_CLANG) || defined(CC_GCC)
    return __builtin_bswap16(Data);
#else
    NO_IMPL();
#endif
}

ALWAYSINLINE U32 ByteSwap(U32 Data)
{
#if defined(CC_MSVC)
    return _byteswap_ulong(Data);
#elif defined(CC_CLANG) || defined(CC_GCC)
    return __builtin_bswap32(Data);
#else
    NO_IMPL();
#endif
}

ALWAYSINLINE U64 ByteSwap(U64 Data)
{
#if defined(CC_MSVC)
    return _byteswap_uint64(Data);
#elif defined(CC_CLANG) || defined(CC_GCC)
    return __builtin_byteswap64(Data);
#else
    NO_IMPL();
#endif
}

}