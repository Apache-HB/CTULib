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

#include "CPUInfo.h"
#include "Core/Memory/Memory.h"

using namespace Cthulhu;
using namespace Cthulhu::Standard;

#ifdef OS_WINDOWS
#   include <Windows.h>
#   include <intrin.h>
#   define CPUID(Info, X) __cpuidex(Info, X, 0)
#   define XGETBV(X) _xgetbv(X)
#else
#   include <cpuid.h>
#   define CPUID(Info, X) __cpuid_count(X, 0, Info[0], Info[1], Info[2], Info[3])
#define XGETBV(X) [](U32 I) -> U64 { \
    U32 EAX, EDX; \
    __asm__ __volatile__("xgetbv" : "=a"(EAX), "=d"(EDX), "=c"(X)); \
    return ((U64)EDX << 32) | EAX; \
}(X);
#endif

Option<Instructions> Cthulhu::Standard::CurrentInstructions()
{
	I32 Info[4];
	CPUID(Info, 1);
    I32 NIds = Info[0];

    CPUID(Info, 0x80000000);
    U32 NXIds = Info[0];

	//check if the current CPU supports XSave and XStore
	if (Info[2] & (1 << 27) || false)
	{
        Instructions Ret;
        Memory::Zero(&Ret, sizeof(Instructions));
        if (NIds >= 0x00000001)
        {
            CPUID(Info, 0x00000001);
            Ret.MMX = (Info[3] & (1 << 23)) != 0;
            Ret.SSE = (Info[3] & (1 << 25)) != 0;
            Ret.SSE2 = (Info[3] & (1 << 26)) != 0;
            Ret.SSE3 = (Info[2] & (1 << 0)) != 0;

            Ret.SSSE3 = (Info[2] & (1 << 9)) != 0;
            Ret.SSE41 = (Info[2] & (1 << 19)) != 0;
            Ret.SSE42 = (Info[2] & (1 << 20)) != 0;
            Ret.AES = (Info[2] & (1 << 25)) != 0;
            
            Ret.AVX = (Info[2] & (1 << 28)) != 0;
            Ret.FMA3 = (Info[2] & (1 << 12)) != 0;

            Ret.RDRAND = (Info[2] & (1 << 30)) != 0;
        }

        if (NIds >= 0x00000007)
        {
            CPUID(Info, 0x00000007);
            Ret.AVX2 = (Info[1] & (1 << 5)) != 0;

            Ret.BMI1 = (Info[1] & (1 << 3)) != 0;
            Ret.BMI2 = (Info[1] & (1 << 8)) != 0;
            Ret.ADX = (Info[1] & (1 << 19)) != 0;
            Ret.SHA = (Info[1] & (1 << 29)) != 0;
            Ret.PREFETCHWT1 = (Info[2] & (1 << 0)) != 0;

            Ret.AVX512F = (Info[1] & (1 << 16)) != 0;
            Ret.AVX512CD = (Info[1] & (1 << 28)) != 0;
            Ret.AVX512PF = (Info[1] & (1 << 26)) != 0;
            Ret.AVX512ER = (Info[1] & (1 << 27)) != 0;
            Ret.AVX512VL = (Info[1] & (1 << 31)) != 0;
            Ret.AVX512BW = (Info[1] & (1 << 30)) != 0;
            Ret.AVX512DQ = (Info[1] & (1 << 17)) != 0;
            Ret.AVX512IFMA = (Info[1] & (1 << 21)) != 0;
            Ret.AVX512VBMI = (Info[2] & (1 << 1)) != 0;
        }

        if (NXIds >= 0x80000001)
        {
            CPUID(Info, 0x80000001);

            Ret.X64 = (Info[3] & (1 << 29)) != 0;
            Ret.ABM = (Info[2] & (1 << 5)) != 0;
            Ret.SSE4a = (Info[2] & (1 << 6)) != 0;
            Ret.FMA4 = (Info[2] & (1 << 26)) != 0;
            Ret.XOP = (Info[2] & (1 << 11)) != 0;
        }

        return Some(Ret);
	}

	return None<Instructions>();
}

bool Cthulhu::Standard::Supports(ISA InstructionSet)
{
    auto SupportedISA = CurrentInstructions();
    if (SupportedISA)
    {
#define ISC(ISAS) case ISA::ISAS: return S.ISAS;
        auto S = SupportedISA.Get();
        switch (InstructionSet)
        {
        default:
            ISC(MMX);
            ISC(X64);
            ISC(ABM);
            ISC(RDRAND);
            ISC(BMI1);
            ISC(BMI2);
            ISC(ADX);
            ISC(PREFETCHWT1);
            
            ISC(SSE);
            ISC(SSE2);
            ISC(SSE3);
            ISC(SSSE3);
            ISC(SSE41);
            ISC(SSE42);
            ISC(SSE4a);
            ISC(AES);
            ISC(SHA);
            
            ISC(AVX);
            ISC(XOP);
            ISC(FMA3);
            ISC(FMA4);
            ISC(AVX2);

            ISC(AVX512F);
            ISC(AVX512CD);
            ISC(AVX512PF);
            ISC(AVX512ER);
            ISC(AVX512VL);
            ISC(AVX512BW);
            ISC(AVX512DQ);
            ISC(AVX512IFMA);
            ISC(AVX512VBMI);
        }
#undef ISC
    }

    return false;
}

String Cthulhu::Standard::VendorName()
{
	I32 Info[4];
	C8 Name[13];

	CPUID(Info, 0);

	Memory::Copy<C8>(Name + 0, (C8*)&Info[0], 4);
	Memory::Copy<C8>(Name + 4, (C8*)&Info[3], 4);
	Memory::Copy<C8>(Name + 8, (C8*)&Info[2], 4);
	Name[12] = '\0';

	return {Name};
}

CPUVendor Cthulhu::Standard::VendorID()
{
    return (VendorName() == "AuthenticAMD") ? CPUVendor::AMD : CPUVendor::Intel;
}
