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

#include <Core/Collections/Option.h>

#pragma once

namespace Cthulhu::Standard
{

struct Instructions
{
    //Others
    bool MMX, 
         x64, 
         ABM, 
         RDRAND, 
         BMI1, 
         BMI2, 
         ADX, 
         PREFETCHWT1;

    //128 bit SIMD
    bool SSE, 
         SSE2, 
         SSE3, 
         SSSE3, 
         SSE41, 
         SSE42, 
         SSE4a, 
         AES, 
         SHA;

    //256 bit SIMD
    bool AVX, 
         XOP, 
         FMA3, 
         FMA4, 
         AVX2;

    //512 bit SIMD
    bool AVX512F, 
         AVX512CD, 
         AVX512PF, 
         AVX512ER, 
         AVX512VL, 
         AVX512BW, 
         AVX512DQ, 
         AVX512IFMA, 
         AVX512VBMI; 
};

Option<Instructions> CurrentInstructions();

bool Is32Bit();
bool Is64Bit();

enum class CPUVendor : U8
{
     AMD,
     Intel
};

}