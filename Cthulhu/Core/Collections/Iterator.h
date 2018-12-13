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

#include "Pair.h"

#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

struct Range
{
    Range(I64 Len)
        : CurrentNum(-1)
        , MaxNum(Len)
    {}

    Range(I64 Start, I64 End, I32 InStep = 1)
        : CurrentNum(Start)
        , MaxNum(End)
        , Step(InStep)
    {}

    Range begin() const { return Range(CurrentNum, MaxNum, Step); }
    Range end() const { return Range(MaxNum, MaxNum, Step); }

    Range operator++()
    {
        CurrentNum++;
        return *this;
    }

    Range operator++(int)
    {
        Range Temp(*this);
        CurrentNum++;
        return Temp;
    }

    Range operator--()
    {
        CurrentNum--;
        return *this;
    }

    Range operator--(int)
    {
        Range Temp(*this);
        CurrentNum--;
        return Temp;
    }

    ALWAYSINLINE bool operator!=(const Range& Other) const { return CurrentNum != Other.CurrentNum; }
    ALWAYSINLINE bool operator==(const Range& Other) const { return CurrentNum == Other.CurrentNum; }

private:
    I64 CurrentNum;
    I64 MaxNum;
    I32 Step = 1;
};

} //Cthulhu
