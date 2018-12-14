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

#include "Array.h"

#pragma once

namespace Cthulhu
{

struct Range;

namespace Utils
{
    String ToString(const Range& Data);
}

struct Range
{
    constexpr Range(I64 Len)
        : Start(0)
        , End(Len+1)
        , Idx(0)
    {}

    constexpr Range(I64 First, I64 Last)
        : Start(First)
        , End(Last+1)
        , Idx(First)
    {
        ASSERT(Last > First, "Trying to make a range with a negative difference");
    }

    constexpr Range begin() const { return { Start, End }; }
    constexpr Range end() const { return { Start, End, End }; }

    ALWAYSINLINE constexpr bool operator==(const Range& Other) const { return Idx == Other.Idx; }
    ALWAYSINLINE constexpr bool operator!=(const Range& Other) const { return Idx != Other.Idx; }

    ALWAYSINLINE constexpr I64 operator*() const { return Idx; }

    constexpr Range& operator++() { Idx++; return *this; }

    Array<I64> ToArray() const;

    friend String Utils::ToString(const Range& Data);

private:
    constexpr Range(I64 First, I64 Last, I64 Index)
        : Start(First)
        , End(Last)
        , Idx(Index)
    {}

    I64 Start, End, Idx;
};

} //Cthulhu
