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

#include "Limits.h"

#include <mmintrin.h>

#pragma once

namespace Cthulhu::Math::SIMD
{

//Represents a 64 bit wide vector
using Vec64 = union alignas(8)
{
    F32 MF32[2];
    F64 MF64;
    
    I8  MI8[8];
    I16 MI16[4];
    I32 MI32[2];
    I64 MI64;
    
    U8  MU8[8];
    U16 MU16[4];
    U32 MU32[2];
    U64 MU64;
};

static_assert(sizeof(Vec64) == 8);

using Vec128 = union alignas(16)
{
    F32 MF32[4];
    F64 MF64[2];
    
    I8  MI8[16];
    I16 MI16[8];
    I32 MI32[4];
    I64 MI64[2];
    
    U8  MU8[16];
    U16 MU16[8];
    U32 MU32[4];
    U64 MU64[2];
};

static_assert(sizeof(Vec128) == 16);

using Vec256 = union alignas(32)
{
    F32 MF32[8];
    F64 MF64[4];

    I8  MI8[32];
    I16 MI16[16];
    I32 MI32[8];
    I64 MI64[4];

    U8  MU8[32];
    U16 MU16[16];
    U32 MU32[8];
    U64 MU64[4];
};

static_assert(sizeof(Vec256) == 32);

using Vec512 = union alignas(64)
{
    F32 MF32[16];
    F64 MF64[8];
    
    I8  MI8[64];
    I16 MI16[32];
    I32 MI32[16];
    I64 MI64[8];

    U8  MU8[64];
    U16 MU16[32];
    U32 MU32[16];
    U64 MU64[8];
};

static_assert(sizeof(Vec512) == 64);

namespace Private
{
    I32 SaturatedAdd(I32 L, I32 R)
    {
        I32 C = L + R;
        if (C < L)
            C = Limits<I32>::Max();
        return C;
    }
}

namespace MMX
{
    //unsigned addition
    Vec64 AddU8(Vec64& Left, Vec64& Right)
    {
        //TODO: is there another instruction set that supports 8 bit unsigned addition without saturation?
        return {
            Left.MU8[0] + Right.MU8[0],
            Left.MU8[1] + Right.MU8[1],
            Left.MU8[2] + Right.MU8[2],
            Left.MU8[3] + Right.MU8[3],
            Left.MU8[4] + Right.MU8[4],
            Left.MU8[5] + Right.MU8[5],
            Left.MU8[6] + Right.MU8[6],
            Left.MU8[7] + Right.MU8[7]
        };
    }

    Vec64 AddU16(Vec64& Left, Vec64& Right)
    {
        //TODO: is there another instruction set that supports 16 bit unsigned addition without saturation?
        return {
            Left.MU16[0] + Right.MU16[0],
            Left.MU16[1] + Right.MU16[1],
            Left.MU16[2] + Right.MU16[2],
            Left.MU16[3] + Right.MU16[3]
        };
    }

    Vec64 AddU32(Vec64& Left, Vec64& Right)
    {
        //TODO: is there another instruction set that supports 32 bit unsigned addition without saturation?
        return { 
            Left.MU32[0] + Right.MU32[1],
            Left.MU32[1] + Right.MU32[1] 
        };
    }

    //signed addition
    Vec64 AddI8(Vec64& Left, Vec64& Right)
    {
        return _mm_add_pi8(Left, Right);
    }

    Vec64 AddI16(Vec64& Left, Vec64& Right)
    {
        return _mm_add_pi16(Left, Right);
    }

    Vec64 AddI32(Vec64& Left, Vec64& Right)
    {
        return _mm_add_pi32(Left, Right);
    }

    Vec64 AddSU8(Vec64& Left, Vec64& Right)
    {
        return _mm_adds_pu8(Left, Right);
    }

    Vec64 AddSU16(Vec64& Left, Vec64& Right)
    {
        return _mm_adds_pu16(Left, Right);
    }

    Vec64 AddSU32(Vec64& Left, Vec64& Right)
    {
        return _m_paddusw(Left, Right);
    }

    //saturated signed addition
    Vec64 AddSI8(Vec64& Left, Vec64& Right)
    {
        return _mm_adds_pi8(Left, Right);
    }

    Vec64 AddSI16(Vec64& Left, Vec64& Right)
    {
        return _mm_adds_pi16(Left, Right);
    }

    Vec64 AddSI32(Vec64& Left, Vec64& Right)
    {
        return {
            Private::SaturatedAdd(Left.MI32[0], Right.MI32[0]),
            Private::SaturatedAdd(Left.MI32[1], Right.MI32[1])
        };
    }

    // ==
    Vec64 Equal8(Vec64& Left, Vec64& Right) 
    {
        return _mm_cmpeq_pi8(Left, Right);
    }

    Vec64 Equal16(Vec64& Left, Vec64& Right)
    {
        return _mm_cmpeq_pi16(Left, Right);
    }

    Vec64 Equal32(Vec64& Left, Vec64& Right)
    {
        return _mm_cmpeq_pi32(Left, Right);
    }

    //signed subtraction
    Vec64 SubI8(Vec64& Left, Vec64& Right)
    {
        return _mm_sub_pi8(Left, Right);
    }

    Vec64 SubI16(Vec64& Left, Vec64& Right)
    {
        return _mm_sub_pi16(Left, Right);
    }

    Vec64 SubI32(Vec64& Left, Vec64& Right)
    {
        return _mm_sub_pi32(Left, Right);
    }

    //unsigned subtraction
    Vec64 SubU8(Vec64& Left, Vec64& Right);
    Vec64 SubU16(Vec64& Left, Vec64& Right);
    Vec64 SubU32(Vec64& Left, Vec64& Right);

    //signed saturated subtraction
    Vec64 SubSI8(Vec64& Left, Vec64& Right);
    Vec64 SubSI16(Vec64& Left, Vec64& Right);
    Vec64 SubSI32(Vec64& Left, Vec64& Right);

    //unsigned saturated subtraction
    Vec64 SubSU8(Vec64& Left, Vec64& Right);
    Vec64 SubSU16(Vec64& Left, Vec64& Right);
    Vec64 SubSU32(Vec64& Left, Vec64& Right);

    Vec64 MulU8(Vec64& Left, Vec64& Right);
    Vec64 MulU16(Vec64& Left, Vec64& Right);
    Vec64 MulU32(Vec64& Left, Vec64& Right);

    //bitwise operators
    // Left & Right
    Vec64 BitAnd(Vec64& Left, Vec64& Right)
    {
        return _mm_and_si64(Left, Right);
    }
   
    // Left | Right
    Vec64 BitOr(Vec64& Left, Vec64& Right)
    {
        return _mm_or_si64(Left, Right);
    }

    // Left ^ Right
    Vec64 BitXor(Vec64& Left, Vec64& Right)
    {
        return _mm_xor_si64(Left, Right);
    }

    // ~Data
    Vec64 BitNot(Vec64& Data)
    {
        return { ~Data.MU64 };
    }

    //shift left shifting in 0
    Vec64 ZShiftLeft8(Vec64& Data)
    {
        return {
            Data.MU8[0] << 1,
            Data.MU8[1] << 1,
            Data.MU8[2] << 1,
            Data.MU8[3] << 1,

            Data.MU8[4] << 1,
            Data.MU8[5] << 1,
            Data.MU8[6] << 1,
            Data.MU8[7] << 1
        };
    }

    Vec64 ZShiftLeft16(Vec64& Data)
    {
        return _mm_sll_pi16(Data, _mm_setr_pi16(1, 1, 1, 1));
    }

    Vec64 ZShiftLeft32(Vec64& Data)
    {
        return _mm_sll_pi32(Data, _mm_setr_pi32(1, 1));
    }

    //shift right shifting in 0
    Vec64 ZShiftRight8(Vec64& Data)
    {
        return {
            Data.MU8[0] >> 1,
            Data.MU8[1] >> 1,
            Data.MU8[2] >> 1,
            Data.MU8[3] >> 1,

            Data.MU8[4] >> 1,
            Data.MU8[5] >> 1,
            Data.MU8[6] >> 1,
            Data.MU8[7] >> 1
        };
    }

    Vec64 ZShiftRight16(Vec64& Data)
    {
        return _mm_srl_pi16(Data, _mm_setr_pi16(1, 1, 1, 1));
    }

    Vec64 ZShiftRight32(Vec64& Data)
    {
        return _mm_srl_pi32(Data, _mm_setr_pi32(1, 1, 1, 1));
    }

    //shift left by Count
    Vec64 LeftBy8(Vec64& Data, Vec64& Count)
    {
        
    }

    Vec64 LeftBy16(Vec64& Data, Vec64& Count)
    {
        return _mm_sll_pi16(Data, Count);
    }

    Vec64 LeftBy32(Vec64& Data, Vec64& Count)
    {
        return _mm_sll_pi32(Data, Count);
    }

    //shift right by Count
    Vec64 RightBy8(Vec64& Data, Vec64& Count)
    {

    }

    Vec64 RightBy16(Vec64& Data, Vec64& Count)
    {

    }

    Vec64 RightBy32(Vec64& Data, Vec64& Count)
    {

    }

    //apply bitwise not to Left then Bitwide AND Left with right
    Vec64 NotAnd(Vec64& Left, Vec64& Right);

    //copy the lower half of Vec and 0 the rest
    Vec64 Lower32And0(Vec64& Vec);

    //copy the lower half of vec and leave the rest unitialized
    Vec64 Lower32(Vec64& Vec);

    //set x87 register state to clear, must be called after MMX calculations are done
    void Empty()
    {
        _m_empty();
    }

    Vec64 Zero()
    {
        return _mm_setzero_si64();
    }
    
    Vec64 From64(U64 Data);
    Vec64 From32(U32 A, U32 B);
    Vec64 From16(U16 A, U16 B, U16 C, U16 D);
    Vec64 From8(U8 A, U8 B, U8 C, U8 D, U8 E, U8 F, U8 G, U8 H);
}

namespace SSE
{
}

namespace SSE2
{
}

namespace SSE3
{
}

namespace SSSE3
{
}

namespace SSE41
{
}

namespace SSE42
{
}

namespace SSE4A
{
}

namespace FMA
{
}

namespace AVX
{
}

}