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

    void Add(const TKey& Key, const TVal& Value)
    {
        Node* ToAdd = new Node(Key, Value);

        U32 Hashed = Hash(Key);

        if(Table[Hashed] == nullptr)
        {
            Table[Hashed] = ToAdd;
        }
        else
        {
            Node* Current = Table[Hashed];
            
            while(Current != nullptr) 
                Current = Current->Next;
            
            Current->Next = ToAdd;
        }
    }

    TVal& operator[](const TKey& Key)
    {
        Node* Item = Retrive(Key);
        
        if(Item == nullptr)
        {
            TVal NewVal;
            Add(Key, NewVal);
        }

        return Retrive(Key)->Val;
    }
    
    TVal Get(const TKey& Key, const TVal& Or)
    {
        const U32 Hashed = Hash(Key);

        return Table[Hashed] == nullptr ? Or : Table[Hashed]->Val;
    }

    //TODO: this mangles shit
    Array<TKey> Keys()
    {
        Array<TKey> Ret;

        for(Node* I : Table.Iterate())
        {
            Node* Current = I;

            while(Current != nullptr)
            {
                Ret += Current->Key;
                Current = Current->Next;
            }
        }

        return Ret;
    }

    //TODO: this mangles shit
    Array<TVal> Values()
    {
        Array<TVal> Ret;

        for(Node* I : Table.Iterate())
        {
            Node* Current = I;

            while(Current != nullptr)
            {
                Ret.Append(Current->Val);
                Current = Current->Next;
            }
        }

        return Ret;
    }

    //TODO: this mangles shit
    Array<Pair<TKey, TVal>> Items()
    {
        Array<Pair<TKey, TVal>> Ret;

        for(Node* I : Table.Iterate())
        {
            Node* Current = I;
            while(Current != nullptr)
            {
                Ret.Append(Pair<TKey, TVal>{ Current->Key, Current->Val });
                Current = Current->Next;
            }
        }

        return Ret;
    }

private:

    Node* Retrive(const TKey& Key) const
    {
        Node* It = Table[Hash(Key)];

        while(It != nullptr)
        {
            if(It->Key == Key)
            {
                return It;
            }
            else
            {
                It = It->Next;
            }
        }

        return nullptr;
    }

    //TODO: fixed size array
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
