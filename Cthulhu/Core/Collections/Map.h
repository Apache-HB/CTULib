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
#include "Core/Memory/Block.h"

#pragma once

namespace Cthulhu
{

namespace Utils
{

constexpr U32 MersenePrime = 8191;

template<typename T> constexpr inline U32 Hash(const T&);

template<> constexpr inline U32 Hash(const U8& Num)  { return Num % MersenePrime; }
template<> constexpr inline U32 Hash(const U16& Num) { return Num % MersenePrime; }
template<> constexpr inline U32 Hash(const U32& Num) { return Num % MersenePrime; }
template<> constexpr inline U32 Hash(const U64& Num) { return Num % MersenePrime; }

template<> constexpr inline U32 Hash(const I8& Num)  { return Num % MersenePrime; }
template<> constexpr inline U32 Hash(const I16& Num) { return Num % MersenePrime; }
template<> constexpr inline U32 Hash(const I32& Num) { return Num % MersenePrime; }
template<> constexpr inline U32 Hash(const I64& Num) { return Num % MersenePrime; }

} // Utils

template<typename, typename> 
struct MapNode;

template<typename TKey, typename TVal>
struct Map
{
    using Node = MapNode<TKey, TVal>;

    Map()
    {
        Data.Wipe();
    }
    
    Map(const Array<Pair<TKey, TVal>> Start)
    {
        Data.Wipe();
        for(const auto& I : Start.ConstIterate())
        {
            Add(I.First, I.Second);
        }
    }

    Map(std::initializer_list<Pair<TKey, TVal>> InitList)
    {
        Data.Wipe();
        for(const auto& I : InitList)
        {
            Add(I.First, I.Second);
        }
    }

    void Add(const TKey& Key, const TVal& Value)
    {
        const U32 Hashed = Utils::Hash(Key);

        if(Data[Hashed] == nullptr)
        {
            Data[Hashed] = new Node(Key, Value);
        }
        else
        {
            Data[Hashed]->Assign(Pair<TKey, TVal>{ Key, Value });
        }
    }

    TVal& operator[](const TKey& Key)
    {
        Node* Item = Extract(Key);

        if(Item == nullptr)
        {
            TVal NewVal;
            Add(Key, NewVal);
        }

        return Extract(Key)->Val;
    }

    TVal Get(const TKey& Key, const TVal& Or) const
    {
        const U32 Hashed = Utils::Hash(Key);

        return (Data[Hashed] == nullptr) ? Or : Data[Hashed]->Val;
    }

    void Remove(const TKey& Key);

    Array<TKey*> Keys() const
    {
        Array<TKey*> Ret;

        Node* Current = nullptr;

        const U32 Len = Data.Len()-1;

        for(
            U32 I = 0; 
            I > Len; 
            I++, 
            Current = Data[I]
        )
        {
            while(Current != nullptr) 
            {
                Ret.Append(&Current->Key);
                Current = Current->Next;
            }
        }
        
        return Ret;
    }

    Array<TVal*> Values() const
    {
        Array<TVal*> Ret;

        Node* Current = nullptr;

        for(U32 I = 0; I < Data.Len(); I++, Current = Data[I])
        {
            while(Current != nullptr)
            {
                Ret.Append(&Current->Val);
                Current = Current->Next;
            }
        }

        return Ret;
    }
    
    using MapPair = Pair<TKey*, TVal*>;

    Array<MapPair> Items() const
    {
        Array<MapPair> Ret;

        Node* Current = nullptr;

        for(U32 I = 0; I < Data.Len(); I++, Current = Data[I])
        {
            while(Current != nullptr)
            {
                Ret.Append({ &Current->Key, &Current->Val });
                Current = Current->Next;
            }
        }

        return Ret;
    }

    bool HasKey(const TKey& Key) const
    {
        const U32 Hashed = Utils::Hash(Key);

        Node* Current = Data[Hashed];

        while(Current != nullptr)
        {
            if(Current->Key == Key)
            {
                return true;
            }
            else
            {
                Current = Current->Next;
            }
        }

        return false;
    }

    Map(const Map& Other) = default;

private:

    Node* Extract(const TKey& Key) const
    {
        Node* Current = Data[Utils::Hash(Key)];

        while(Current != nullptr)
        {
            if(Current->Key == Key)
            {
                return Current;
            }
            else
            {
                Current = Current->Next;
            }
        }

        return nullptr;
    }

    void FreeNodes(Node* Base)
    {
        if(Base != nullptr)
        {
            FreeNodes(Base->Next);

            delete Base;
        }
    }

    Block<Node*, Utils::MersenePrime> Data;

public:

    ~Map()
    {
        for(U32 I = 0; I < Data.Len(); I++)
        {
            FreeNodes(Data[I]);
        }
    }
};

template<typename TKey, typename TVal>
struct MapNode
{
    TKey Key;
    TVal Val;
    MapNode* Next;

    MapNode(const TKey& K, const TVal& V)
        : Key(K)
        , Val(V)
        , Next(nullptr)
    {}

    TVal& Assign(const Pair<TKey, TVal> Item)
    {
        if(Key == Item.First)
        {
            Val = Item.Second;
            return Val;
        }
        else if(Next != nullptr)
        {
            return Next->Assign(Item);
        }
        else
        {
            Next = new MapNode(Item.First, Item.Second);
            return Next->Val;
        }
    }
};

} // Cthulhu



/*
template<typename, typename> struct MapNode;

template<typename TKey, typename TVal>
struct Map
{
    using Node = MapNode<TKey, TVal>;

    Map()
    {
        Memory::Zero<Node*>(Table, sizeof(Node*) * TableSize);
    }

    Map(const Map& Other)
    {
        Memory::Copy<Node*>(Other.Table, Table, sizeof(Node*) * TableSize);
    }

    Map(const Array<Pair<TKey, TVal>> Start)
    {
        Memory::Zero<Node*>(Table, sizeof(Node*) * TableSize);
        
        for(const auto& I : Start.Iterate())
        {
            Table[Hash(I.First)] = new Node(I.First, I.Second);
        }
    }

    Map(std::initializer_list<Pair<TKey, TVal>> InitList)
    {
        Memory::Zero<Node*>(Table, sizeof(Node*) * TableSize);

        for(auto& I : InitList)
        {
            Table[Hash(I.First)] = new Node(I.First, I.Second);
        }
    }

    void Add(const TKey& Key, const TVal& Value)
    {
        U32 Hashed = Hash(Key);

        if(Table[Hashed] == nullptr)
        {
            Table[Hashed] = new Node(Key, Value);
        }
        else
        {
            Table[Hashed]->Assign(Pair<TKey, TVal>{Key, Value});
        }
    }

    TVal& operator[](const TKey& Key)
    {
        Node* Item = Extract(Key);
        
        if(Item == nullptr)
        {
            TVal NewVal;
            Add(Key, NewVal);
        }
        
        return Extract(Key)->Val;
    }
    
    TVal Get(const TKey& Key, const TVal& Or) const
    {
        const U32 Hashed = Hash(Key);

        return Table[Hashed] == nullptr ? Or : Table[Hashed]->Val;
    }

    void Remove(const TKey& Key)
    {
        const U32 Hashed = Hash(Key);

        Node* Current = Table[Hashed];

        if(Current != nullptr)
        {
            Table[Hashed] = Current->Next;

            delete Current;
        }
    }

    Array<TKey*> Keys() const
    {
        Array<TKey*> Ret;

        for(U32 I = 0; I < TableSize; I++)
        {
            Node* Current = Table[I];

            while(Current != nullptr)
            {
                Ret.Append(&Current->Key);
                Current = Current->Next;
            }
        }

        return Ret;
    }
    
    Array<TVal*> Values() const
    {
        Array<TVal*> Ret;

        for(U32 I = 0; I < TableSize; I++)
        {
            Node* Current = Table[I];

            while(Current != nullptr)
            {
                Ret.Append(&Current->Val);
                Current = Current->Next;
            }
        }

        return Ret;
    }

    using MapPair = Pair<TKey*, TVal*>;

    
    Array<MapPair> Items() const
    {
        Array<MapPair> Ret;

        for(U32 I = 0; I < TableSize; I++)
        {
            Node* Current = Table[I];
            while(Current != nullptr)
            {
                Ret.Append(MapPair{ &Current->Key, &Current->Val });
                Current = Current->Next;
            }
        }

        return Ret;
    }

    bool HasKey(const TKey& Key) const
    {
        return Table[Hash(Key)] != nullptr;
    }

private:

    Node* Extract(const TKey& Key) const
    {
        Node* It = Table[Hash(Key)];

        //printf("[%x]\n", It);

        while(It != nullptr)
        {
            //printf("perhaps at %x\n", It);
            
            //printf("a %s b %s\n", *Key, *It->Key);

            if(It->Key == Key)
            {
                //printf("found at: %x\n", It);
                return It;
            }
            else
            {
                It = It->Next;
            }
        }
        //printf("Ret null %x\n", It);
        return nullptr;
    }

    const U32 TableSize = MersenePrime;

    //TODO: fixed size array
    Node** Table = Memory::Alloc<Node*>(sizeof(Node*) * TableSize);
    //Array<Node*> Table;

    void FreeNodes(Node* Base)
    {
        if(Base != nullptr)
        {
            if(Base->Next != nullptr)
            {
                FreeNodes(Base->Next);
            }
            
            delete Base;
            //delete this but free the table itself 
            //because nodes are allocated with new
            //but the table is malloc'd
        }
    }

public:
    
    ~Map()
    {
        for(U32 I = 0; I < TableSize; I++)
        {
            //free all items in the table
            FreeNodes(Table[I]);
        }
        //free the table itself
        Memory::Free(Table);
    }

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

    TVal& Assign(const Pair<TKey, TVal> Item)
    {
        if(Key == Item.First)
        {
            Val = Item.Second;
            return Val;
        }
        else if(Next != nullptr)
        {
            return Next->Assign(Item);
        }
        else
        {
            Next = new MapNode(Item.First, Item.Second);
            return Next->Val;
        }
    }
    
    ALWAYSINLINE operator TVal() { return Val; }
};
*/