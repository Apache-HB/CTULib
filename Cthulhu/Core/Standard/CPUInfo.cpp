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

Option<Instructions> CurrentInstructions()
{
    I32 Info[4];
    CPUID(Info, 1);

    //check if the current CPU supports XSave and XStore
    if(Info[2] & (1 << 27) || false)
    {
        Instructions Ret;
    }

    return None<Instructions>();
}