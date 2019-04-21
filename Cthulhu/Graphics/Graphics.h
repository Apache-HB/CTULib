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

#pragma once

#include "Cthulhu/Meta/Macros.h"

#ifdef OS_WINDOWS
#   include <windows.h>
#endif

#ifdef OS_WINDOWS
#   define CTU_GRAPHCS_MAIN(HANDLE, ARGS) int WINAPI wWinMain( \
    HINSTANCE HANDLE, \
    HINSTANCE, \
    PSTR ARGS, \
    int \
)
#else
#   define CTU_GRAPHCS_MAIN(_, ARGS) int main(int, const char** ARGS)
#endif

#ifdef OS_WINDOWS
#   define CTU_GRAPHICS_INIT(HANDLE) Setup(HANDLE);
#else
#   define CTU_GRAPHICS_INIT(_) Setup();
#endif

#if defined(OS_WINDOWS)
#   include "Windows/Graphics.h"
#elif defined(OS_APPLE)
#   include "Darwin/Graphics.h"
#elif defined(OS_LINUX)
#   include "Linux/Graphics.h"
#endif