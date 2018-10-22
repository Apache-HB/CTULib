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

#pragma once

namespace Cthulhu
{

template<typename TContainer, typename TElement>
struct Iterator
{
    TContainer& Container;
    uint64 Index;
public:
    Iterator(TContainer& InContainer, uint64 StartIndex = 0)
        : Container(InContainer)
        , Index(StartIndex)
    {}

    Iterator begin() const { return Iterator<TContainer, TElement>(Container); }
    Iterator end() const { return Iterator<TContainer, TElement>(Container, Container.Len()); }

    Iterator operator++()
    {
        Index++;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator Temp(*this);
        Index++;
        return Temp;
    }

    Iterator operator--()
    {
        Index--;
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator Temp(*this);
        Index--;
        return Temp;
    }

    TElement& operator*() { return Container[Index]; }

    TElement* operator->() { return &Container[Index]; }

    bool operator!=(const Iterator& Other) { return Index != Other.Index; }
    bool operator==(const Iterator& Other) { return Index == Other.Index; }
};

}

#if 0

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

#endif