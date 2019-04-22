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

#include "Meta/Macros.h"
#include "Meta/Aliases.h"

#ifdef OS_WINDOWS
#   include <windows.h>
#elif _POSIX_C_SOURCE >= 199309
#   include <time.h>
#else
#   include <unistd.h>
#endif

#pragma once

namespace Cthulhu
{

void SleepMS(I32 Millis)
{
#if OS_WINDOWS
    Sleep(Millis);
#elif _POSIX_C_SOURCE >= 199309
    struct timespec T;
    T.tv_sec = Millis / 1000;
    T.tv_nsec = (Millis % 1000) / 1000000;
    nanosleep(&T, nullptr);
#else
    usleep(Millis);
#endif
}

}