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

template<typename, typename> struct EnumeratedIterator;

template<typename TContainer, typename TElement>
class Iterator
{
protected:
    TContainer& Container;
    U64 Index;
public:
    Iterator(TContainer& InContainer, U64 StartIndex = 0)
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

    EnumeratedIterator<TContainer, TElement> Enumerate() { return EnumeratedIterator<TContainer, TElement>(Container); }
};

template<typename TContainer, typename TElement>
struct EnumeratedIterator : public Iterator<TContainer, TElement>
{
    using Super = Iterator<TContainer, TElement>;

    EnumeratedIterator(TContainer& InContainer, U64 StartIndex = 0)
        : Super(InContainer, StartIndex)
    {}

    EnumeratedIterator begin() const { return EnumeratedIterator<TContainer, TElement>(Super::Container); }
    EnumeratedIterator end() const { return EnumeratedIterator<TContainer, TElement>(Super::Container, Super::Container.Len()); }


    Pair<TElement&, U64> operator*() { return Pair<TElement&, U64>{Super::Container[Super::Index], Super::Index}; }

    Pair<TElement*, U64> operator->() { return Pair<TElement*, U64>{&Super::Container[Super::Index], Super::Index}; }
};

} //Cthulhu
