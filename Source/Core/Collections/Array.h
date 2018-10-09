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

#include "Optional.h"
#include "Iterator.h"

#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#pragma once

namespace Cthulhu
{

//TODO: document

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

        for(int I = 0; I < Length; I++)
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

        for(int I = 0; I < PtrLen; I++)
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
    
    Array(uint32 InLen, T(*Predicate)(int))
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
        {
            Append(Other[I]);
        }
        return *this;
    }

    ALWAYSINLINE Optional<T> Pop()
    {
        return (Length == 0) ? Optional<T>(Real[Length--]) : NullOpt<T>();
    }

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