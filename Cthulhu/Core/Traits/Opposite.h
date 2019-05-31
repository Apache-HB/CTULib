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

#include "IsSame.h"

#pragma once

namespace Cthulhu
{

//switch between signed and unsigned types

template<typename T> struct Opposite {};

template<> struct Opposite<U8>  { using Type = I8;  };
template<> struct Opposite<U16> { using Type = I16; };
template<> struct Opposite<U32> { using Type = I32; };
template<> struct Opposite<U64> { using Type = I64; };

template<> struct Opposite<I8>  { using Type = U8;  };
template<> struct Opposite<I16> { using Type = U16; };
template<> struct Opposite<I32> { using Type = U32; };
template<> struct Opposite<I64> { using Type = U64; };


//force a type to be signed
template<typename T> struct Signed {};

template<> struct Signed<U8>  { using Type = I8;  };
template<> struct Signed<U16> { using Type = I16; };
template<> struct Signed<U32> { using Type = I32; };
template<> struct Signed<U64> { using Type = I64; };
template<> struct Signed<I8>  { using Type = I8;  };
template<> struct Signed<I16> { using Type = I16; };
template<> struct Signed<I32> { using Type = I32; };
template<> struct Signed<I64> { using Type = I64; };

//force a type to be unsigned
template<typename T> struct Unsigned {};

template<> struct Unsigned<I8>  { using Type = U8;  };
template<> struct Unsigned<I16> { using Type = U16; };
template<> struct Unsigned<I32> { using Type = U32; };
template<> struct Unsigned<I64> { using Type = U64; };
template<> struct Unsigned<U8>  { using Type = U8;  };
template<> struct Unsigned<U16> { using Type = U16; };
template<> struct Unsigned<U32> { using Type = U32; };
template<> struct Unsigned<U64> { using Type = U64; };

template<typename T> struct IsUnsigned : Same<Unsgined<T>, T> {};
template<typename T> struct IsSigned : Same<Signed<T>, T> {};

}