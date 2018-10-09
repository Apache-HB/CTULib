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

#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#pragma once

//TODO document

namespace Cthulhu
{

template<typename TContainer, typename TElement>
class ArrayIterator
{
    TContainer& Container;
    uint32 Index;
public:
    ArrayIterator(TContainer& InContainer, uint32 StartIndex = 0)
        : Container(InContainer)
        , Index(StartIndex)
    {}

    ALWAYSINLINE ArrayIterator begin() const { return ArrayIterator<TContainer, TElement>(Container); }
    ALWAYSINLINE ArrayIterator end() const { return ArrayIterator<TContainer, TElement>(Container, Container.Len()); }

    ArrayIterator& operator++()
    {
        Index++;
        return *this;
    }

    ArrayIterator& operator++(int)
    {
        ArrayIterator& Temp(*this);
        Index++;
        return Temp;
    }

    ArrayIterator& operator--()
    {
        Index--;
        return *this;
    }

    ArrayIterator& operator--(int)
    {
        ArrayIterator& Temp(*this);
        Index--;
        return Temp;
    }

    ALWAYSINLINE TElement& operator*() { return Container[Index]; }

    ALWAYSINLINE TElement* operator->() { return &Container[Index]; }

    ALWAYSINLINE friend bool operator!=(const ArrayIterator& Left, const ArrayIterator& Right) { return Left.Index == Right.Index; }

    ALWAYSINLINE friend bool operator==(const ArrayIterator& Left, const ArrayIterator& Right) { return Left.Index == Right.Index; }
};

}