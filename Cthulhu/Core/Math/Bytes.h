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


#if OS_APPLE
#   include <machine/endian.h>
#else
#   include <stdlib.h>
#endif

#pragma once

namespace Cthulhu::Math
{

//TODO: does intel have a builtin function for byteswaps

CTU_INLINE U16 ByteSwap(U16 Data)
{
#if CC_MSVC
    return _byteswap_ushort(Data);
#elif CC_CLANG || CC_GCC
    return __builtin_bswap16(Data);
#else
    return (Data >> 8) | (Data << 8);
#endif
}

CTU_INLINE U32 ByteSwap(U32 Data)
{
#if CC_MSVC
    return _byteswap_ulong(Data);
#elif CC_CLANG || CC_GCC
    return __builtin_bswap32(Data);
#else
    return ((Data >> 24) & 0xff) |
        ((Num << 8) & 0xff0000) |
        ((Num >> 8) & 0xff00) |
        ((Data << 24) & 0xff000000);
#endif
}

CTU_INLINE U64 ByteSwap(U64 Data)
{
#if CC_MSVC
    return _byteswap_uint64(Data);
#elif CC_CLANG || CC_GCC
    return __builtin_bswap64(Data);
#else
    Data = (Data & 0x00000000FFFFFFFF) << 32 | (Data & 0xFFFFFFFF00000000) >> 32;
    Data = (Data & 0x0000FFFF0000FFFF) << 16 | (Data & 0xFFFF0000FFFF0000) >> 16;
    Data = (Data & 0x00FF00FF00FF00FF) << 8 | (Data & 0xFF00FF00FF00FF00) >> 8;
    return Data;
#endif
}

//generic byteswap function to match correct sizes
template<typename T>
CTU_INLINE T GenericByteSwap(T Data)
{
    static_assert(sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8);

    if constexpr(sizeof(T) == 2)
        return ByteSwap((U16)Data);
    else if constexpr(sizeof(T) == 4)
        return ByteSwap((U32)Data);
    else
        return ByteSwap((U64)Data);
}

}