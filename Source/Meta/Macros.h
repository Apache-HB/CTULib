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

/**This switch detects the operating system using OS predefines
 * it is used for many things such as the platform specific path seperator
 * @see String::PathSeperator()
 */

#if defined(_WIN32) || defined(_WIN64)
#   define OS_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
#   define OS_APPLE 1
#elif defined(__linux__) || defined(__unix__)
#   define OS_LINUX 1
#else
#   error "Unrecognised target platform"
#endif


/**This is a compiler switch to detect which compiler is being used
 * as every compile has compiler specific stuff, such as __forceinline or 
 * __attribute__((always_inline)) because whoever wrote these things doesnt
 * know how to follow standards
 */

#if defined(_MSC_VER)
#   define ALWAYSINLINE __forceinline
#   define CC_MSVC 1
#elif defined(__clang__)
#   define ALWAYSINLINE __attribute__((always_inline))
#   define CC_CLANG 1
#elif defined(__GUNC__) || defined(__GUNG__)
#   define ALWAYSINLINE inline
#   define CC_GCC 1
#elif defined(__INTEL_COMPILER)
#   define ALWAYSINLINE __forceinline
#   define CC_INTEL 1
#else
#   error "Unrecognised compiler"
#endif

#define WITH_CTHULHU 1