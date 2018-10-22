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

#include <initializer_list>

#include "Meta/Aliases.h"
#include "Meta/Assert.h"
#include "Option.h"

#pragma once

namespace Cthulhu
{

template<typename T>
struct Array
{
    Array();

    Array(uint64 Times, T Item)
        : Length(Times)
        , Allocated(Times)
        , Slack(32)
    {
        Real = new T[Times];
        
        for(uint64 I = 0; I < Times; I++)
        {
            Real[I] = Item;
        }
    }

    /**claims ptr as its own, dont use ptr directly once constructed
     * 
     */
    Array(const T* Ptr, uint64 PtrLength)
        : Real(Ptr)
        , Length(PtrLength)
        , Allocated(PtrLength)
        , Slack(32)
    {
        ASSERT(Ptr != nullptr, "Trying to copy from a raw pointer that was nullptr");
    }

    Array(const Array& Other)
        : Slack(32)
    {
        Construct(Other.Real, Other.Length);
    }

    Array(const Array* Other)
        : Slack(32)
    {
        ASSERT(Other != nullptr, "Attempting to construct an array from nullptr");
        Construct(Other->Real, Other->Length);
    }

    Array(std::initializer_list<T> InitList)
        : Slack(32)
    {
        Construct(InitList.begin(), InitList.size());
    }

    Array(uint64 Times, Lambda<T(uint64)> Block)
        : Slack(32)
        , Length(Times)
        , Allocated(32)
        , Real(new T[Times])
    {
        for(uint64 I = 0; I < Times; I++)
        {
            Real[I] = Block(I);
        }
    }

    uint64 Len() const { return Length; }

    bool ValidIndex(uint64 Index) const { return 0 <= Index && Index <= Length; }

    Option<T> At(uint64 Index) const { return (ValidIndex(Index)) ? Some<T>(Real[Index]) : None<T>(); }

    T& operator[](uint64 Index) const
    {
        ASSERT(ValidIndex(Index), "Accessing array at invalid index is undefined");
        return Real[Index];
    }

    void Append(const T& Item)
    {
        if(++Length >= Allocated)
        {
            Resize(Allocated + 1);
        }
        Real[Length] = Item;
    }

    void Append(const Array& Other)
    {
        if(Length + Other >= Allocated)
        {
            Resize(Allocated + Other);
        }
        const uint64 OldLength = Length;

        Length += Other;
        
        for(uint64 I = OldLength; I < Other.Length; I++)
        {
            Real[I] = Other[I - OldLength];
        }
    }

    Array Section(uint64 From, uint64 To) const;

    bool Has(const T& Item) const
    {
        for(uint64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item) return true;
        }

        return false;
    }

    Option<uint64> FindFirst(const T& Item) const
    {
        for(uint64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item) return Some(I);
        }

        return None<uint64>();
    }

    Option<uint64> FindLast(const T& Item) const
    {
        for(uint64 I = Length - 1; I >= 0; I--)
        {
            if(Real[I] == Item) return Some(I);
        }
        
        return None<uint64>();
    }
    
    uint64 Count(const T& Item) const
    {
        uint64 Ret = 0;
        
        for(uint64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item) Ret++;
        }

        return Ret;
    }

    Array Filter(Lambda<bool(const T&)> Block)
    {
        Array Ret;
        
        for(uint64 I = 0; I < Length; I++)
        {
            const T& Item = Real[I];
            if(Block(Item)) Ret += Item;
        }

        return Ret;
    }
    
    template<typename TCollector = Array<T>, typename TReturn = T>
    TCollector Map(Lambda<T(const T&)> Block)
    {
        TCollector Ret;

        for(uint64 I = 0; I < Length; I++)
        {
            Ret += Block(Real[I]);
        }

        return Ret;
    }

    ~Array() { delete[] Real; }

private:

    void Construct(const T* NewContent, uint64 PtrLength)
    {
        Length = PtrLength;
        Allocated = PtrLength + Slack;

        Real = new T[Allocated];

        for(uint64 I = 0; I < Length; I++)
        {
            Real[I] = NewContent[I];
        }
    }

    void Resize(uint64 NewSize)
    {
        Allocated = NewSize + Slack;

        T* Temp = Real;
        Real = new T[Allocated];
        
        for(uint64 I = 0; I < Length; I++)
        {
            Real[I] = Temp[I];
        }
        
        delete[] Temp;
    }

    T* Real;
    uint64 Length;
    uint64 Allocated;
    uint64 Slack;
};

}


#if 0

#include "Optional.h"
#include "Iterator.h"

#include "Core/Types/Lambda.h"

#include "Core/Memory/Memory.h"

#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#pragma once

namespace Cthulhu
{

//TODO: document
//TODO: actually complete

template<typename T>
class Array
{

    T* Real = nullptr;

    uint32 Length, Allocated, Slack;

protected:

    void Resize(uint32 NewSize)
    {
        Allocated = NewSize + Slack;
        if(Length < NewSize)
        {
            Length = NewSize;
        }

        T* Temp = Real;
        Real = new T[Allocated];

        for(uint32 I = 0; I < Length; I++)
        {
            Real[I] = Temp[I];
        }
        delete[] Temp;
    }

    void Construct(const T* Data, uint32 PtrLen)
    {
        Length = PtrLen;
        Allocated = Length + Slack;
        Real = new T[Allocated];

        for(uint32 I = 0; I < PtrLen; I++)
        {
            Real[I] = Data[I];
        }
    }

public:

    Array()
    {
        Real = new T[Slack];
        Length = 0;
        Allocated = Slack;
    }

    ALWAYSINLINE Array(const Array& Other)
        : Slack(32)
    {
        Construct(Other.Real, Other.Length);
    }

    ALWAYSINLINE Array(const Array* Other)
        : Slack(32)
    {
        if(Other) 
        { 
            Construct(Other->Real, Other->Length); 
        } 
        else
        {
            Real = new T[32];
            Length = 0;
            Slack = 32;
            Allocated = 32;
        }
    }

    Array(T* Ptr, uint32 PtrLen)
        : Slack(32)
    {
        Length = PtrLen;
        Allocated = PtrLen;
        Real = Ptr;
    }
    
    Array(uint32 InLen, Lambda<T(int)> Predicate)
        : Slack(32)
    {
        Real = new T[InLen + Slack];
        Allocated = Slack + InLen;
        Length = InLen;
        
        for(int I = 0; I < InLen; I++)
        {
            Real[I] = Predicate(I);
        }
    }

    Array(std::initializer_list<T> Init)
        : Slack(32)
    {
        Construct(Init.begin(), (uint32)Init.size());
    }

    ALWAYSINLINE ~Array()
    {
        delete[] Real;
    }

    Array& operator=(const Array& Other)
    {
        Construct(Other.Real, Other.Length);
    }

    bool ValidIndex(int Index) const { return 0 <= Index && Index <= Length; }

    ALWAYSINLINE const T operator[](uint32 Index) const { return Real[Index]; }
    ALWAYSINLINE T& operator[](uint32 Index) { return Real[Index]; }
    ALWAYSINLINE Optional<T> At(uint32 Index) { return (ValidIndex(Index)) ? Optional<T>(Real[Index]) : NullOpt<T>(); }

    ALWAYSINLINE uint32 Len() const { return Length; }
    ALWAYSINLINE uint32 Space() const { return Allocated; }
    ALWAYSINLINE uint32 CurrentSlack() const { return Allocated - Length; }
    ALWAYSINLINE void SetSlack(uint32 NewSlack) { Slack = NewSlack; }
    ALWAYSINLINE uint32 GetSlack() const { return Slack; }

    Array& Append(const T Item)
    {
        if(Length + 1 >= Allocated)
        {
            Resize(Length);
        }
        Real[Length++] = Item;

        return *this;
    }

    Array& Append(const Array& Other)
    {
        for(int I = 0; I < Other.Len(); I++)
        {//TODO: optimize
            Append(Other[I]);
        }
        return *this;
    }

    Array& Push(const T& Item)
    {
        if(Length + 1 >= Allocated)
        {
            Resize(Length);
        }
        Memory::Memmove(Real, Real + sizeof(T), Length);
        Real[0] = Item;
        Length++;
        return *this;
    }

    Optional<T> Extract(int Index)
    {
        if(ValidIndex(Index))
        {
            T Item = Real[Index];
            Memory::Memmove(Real + (sizeof(T) * Index+1), Real + (sizeof(T) * Index), (Len() - 1) * sizeof(T));
            return Optional<T>(Item);
        }
        else
        {
            return NullOpt<T>();
        }
    }

    ALWAYSINLINE T Pop() { return Real[Length--]; }

    ALWAYSINLINE ArrayIterator<Array, T> Iterate() { return ArrayIterator<Array, T>(*this); }
    ALWAYSINLINE const ArrayIterator<Array, T> Iterate() const { return ArrayIterator<Array, T>(*this); }

    ALWAYSINLINE T& Front() { return Real[0]; }
    ALWAYSINLINE const T& Front() const { return Real[0]; }

    ALWAYSINLINE T& Back() { return Real[Length]; }
    ALWAYSINLINE const T& Back() const { return Real[Length]; }

    int Count(const T Item) const
    {
        int Num = 0;
        for(int I = 0; I < Length; I++)
        {
            if(Real[I] == Item) Num++;
        }
        return Num;
    }

    Optional<int> Find(const T Item) const
    {        
        for(int I = 0; I < Length; I++)
        {
            if(Real[I] == Item) { return Optional<int>(I); }
        }
        return NullOpt<int>();
    }

    bool Has(const T Item) const
    {
        for(int I = 0; I < Length; I++)
        {
            if(Real[I] == Item) return true;
        }
        return false;
    }
};

}

#endif