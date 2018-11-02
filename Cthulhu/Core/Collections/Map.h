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
#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#pragma once

namespace Cthulhu
{

const U32 MersenePrime = 8191;

template<typename, typename> struct MapNode;

template<typename TKey, typename TVal>
struct Map
{
    using Node = MapNode<TKey, TVal>;

    Map()
    {
        #warning NO_IMPL()
        NO_IMPL();
    }

    Map(const Map& Other)
    {
        #warning NO_IMPL()
        NO_IMPL();
    }

    Map(const Array<Node> Start)
    {
        for(const auto& I : Start.Iterate())
        {
            Table[Hash(I.First)] = new Node(I.First, I.Second);
        }
    }

    Node& operator[](const TKey& Key) const
    {
        ASSERT(Table[Hash(Key)] != nullptr, "Trying to access an invalid key");
        return Table[Hash(Key)];
    }
    
    TVal Get(const TKey& Key, const TVal& Or) const
    {
        const U32 Hashed = Hash(Key);

        return Table[Hashed] == nullptr ? Or : Table[Hashed]->Val;
    }

    Array<TKey> Keys() const
    {
        Array<TKey> Ret;

        for(const auto* I : Table.Iterate())
        {
            auto* Current = I;

            while(Current != nullptr)
            {
                Ret.Append(Current->Key);
                Current = Current->Next;
            }
        }

        return Ret;
    }

    Array<TVal> Values() const
    {
        Array<TVal> Ret;

        for(const auto* I : Table.Iterate())
        {
            auto* Current = I;

            while(Current != nullptr)
            {
                Ret.Append(Current->Val);
                Current = Current->Next;
            }
        }

        return Ret;
    }

    Array<Pair<TKey, TVal>> Items() const
    {
        Array<Pair<TKey, TVal>> Ret;

        for(const auto* I : Table.Iterate())
        {
            auto Current = I;
        }
    }

private:
    Array<Node*> Table;
};


template<typename TKey, typename TVal>
struct MapNode
{
    TKey Key;
    TVal Val;
    MapNode* Next;

    MapNode(TKey InKey, TVal InVal)
        : Key(InKey)
        , Val(InVal)
        , Next(nullptr)
    {}

    TVal& operator=(const Pair<TKey, TVal> Item)
    {
        if(Key == Item.First)
        {
            Val = Item.Second;
            return Val;
        }
        else if(Next != nullptr)
        {
            return Next = Item;
        }
        else
        {
            Next = new MapNode(Item.First, Item.Second);
            return Next->Val;
        }
    }
    
    ALWAYSINLINE operator TVal() { return Val; }
};

template<typename T> inline U32 Hash(const T&);

template<> inline U32 Hash(const U8& Num)  { return Num % MersenePrime; }
template<> inline U32 Hash(const U16& Num) { return Num % MersenePrime; }
template<> inline U32 Hash(const U32& Num) { return Num % MersenePrime; }
template<> inline U32 Hash(const U64& Num) { return Num % MersenePrime; }

template<> inline U32 Hash(const I8& Num)  { return Num % MersenePrime; }
template<> inline U32 Hash(const I16& Num) { return Num % MersenePrime; }
template<> inline U32 Hash(const I32& Num) { return Num % MersenePrime; }
template<> inline U32 Hash(const I64& Num) { return Num % MersenePrime; }

}
