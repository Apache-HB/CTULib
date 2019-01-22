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

/**
 * type aliases to shorten function signatures while maintaining readability
 */

namespace Cthulhu
{

/**Unsigned long long
 * 
 * always between 0 and +18,446,744,073,709,551,615
 * 
 * 8 bytes, 64 bits
 * 
 */
using U64 = unsigned long long;

/**unsigned long int
 * 
 * always between 0 and +4,294,967,295
 * 
 * 4 bytes, 32 bits
 * 
 */
using U32 = unsigned long int;

/**unsigned short
 * 
 * always between 0 and +65,535
 * 
 * 2 bytes, 16 bits
 */
using U16 = unsigned short;

/**usngined char
 * 
 * always between 0 and +255
 * 
 * 1 byte, 8 bits
 */
using U8 = unsigned char;

using Byte = U8;

/**signed long long
 * 
 * always between −9,223,372,036,854,775,807 and +9,223,372,036,854,775,807
 * 
 * 8 bytes, 64 bits
 */
using I64 = signed long long;

/**signed long
 * 
 * always between −2,147,483,647 and +2,147,483,647
 * 
 * 4 bytes, 32 bits
 */
using I32 = signed long int;

/**signed short
 * 
 * always between −32,767 and +32,767
 * 
 * 2 bytes, 16 bits
 */
using I16 = signed short;

/**signed char
 * 
 * always between -127 and +127
 * 
 * 1 byte, 8 bits
 */
using I8 = signed char;

/**32 bit char, garunteed to be 4 bytes wide
 * 
 * can represent any unicode character
 * 
 */
using C32 = I32;

/**16 bit char, garunteed to be 2 bytes wide
 * 
 */
using C16 = I16;
//          ^^^^
//use I16 rather than char16_t because 
//not all compilers support the full C++11 & C++17 standard
//such as MSVC (as always)

/**8 bit char, garunteed to be 1 byte wide
 * 
 * can represent any standard ascii char
 * 
 */
using C8 = unsigned char;

/**32 bit wide char, unlike wchar_t is always 4 bytes wide
 * 
 */
using WideChar = C32;

/**8 bit char that can represent any standard ascii char
 * 
 */
using AsciiChar = C8;

using F32 = float;

using F64 = double;

using Empty = struct {};

}