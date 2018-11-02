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

#if 0

#include <initializer_list>
#include "Array.h"
#include "Pair.h"
#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

const U64 MersenePrime = 8191;

namespace Private
{

template<typename TKey, typename TVal>
struct MapNode
{
    TKey Key;
    TVal Value;
    MapNode* Next;

    MapNode(TKey InKey, TVal Val) 
        : Key(InKey)
        , Value(Val)
        , Next(nullptr)
    {}

    TVal& operator=(const Pair<TKey, TVal> Item)
    {
        if(Key == Item.First)
        {
            Value = Item.Second;
            return Value;
        }
        else if(!!Next)
        {
            return Next = Item;
        }
        else
        {
            Next = new MapNode(Item.First, Item.Second);
            return Next->Value;
        }
    }

    operator TVal() { return Value; }
};

} //Private


template<typename TKey, typename TVal>
struct Map
{
    using Node = Private::MapNode<TKey, TVal>;

    Map()
        : Table(Array<Node*>(MersenePrime, true))
    {}

    Map(std::initializer_list<Pair<TKey, TVal>> InitList)
        : Table(Array<Node*>(MersenePrime, true))
    {
        for(auto& I : InitList)
        {
            Table[Hash(I.First)] = new Node(I.First, I.Second);
        }     
    }

    Map(Array<Pair<TKey, TVal>> Start)
        : Table(Array<Node*>(MersenePrime, true))
    {
        for(auto& I : Start.Iterate())
        {
            Table[Hash(I.First)] = new Node(I.First, I.Second);
        }
    }

    Node& operator[](const TKey& Key) const
    {
        ASSERT(Table[Hash(Key)] != nullptr, "Trying to access a null element");
        return *Table[Hash(Key)];
    }

    TVal Get(const TKey& Key, const TVal Or)
    {
        Node* Hashed = Table[Hash(Key)];
        
        if(Hashed == nullptr)
        {
            return Or;
        }
        
        return Hashed->Value;
    }

    Array<TKey> Keys()
    {
        Array<TKey> Ret;

        for(auto&& I : Table.Iterate())
        {
            auto Current = I;
            while(!!Current)
            {
                Ret.Append(Current->Key);
                Current = Current->Next;
            }
        }

        return Ret;
    }

    Array<TVal> Values()
    {
        Array<TVal> Ret;
        
        for(auto&& I : Table.Iterate())
        {
            auto Current = I;

            while(!!Current)
            {
                Ret.Append(Current->Value);
                Current = Current->Next;
            }
        }

        return Ret;
    }

    Array<Pair<TKey*, TVal*>> Items()
    {
        Array<Pair<TKey*, TVal*>> Ret;

        for(auto&& I : Table.Iterate())
        {
            auto Current = I;
            while(Current != nullptr)
            {
                Ret.Append(Pair<TKey*, TVal*>({ &Current->Key, &Current->Value}));
                Current = Current->Next;
            }
        }

        return Ret;
    }

private:
    Array<Node*> Table;
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

} //Cthulhu

#endif