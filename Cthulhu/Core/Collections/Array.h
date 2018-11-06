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

#include <vector>

#include "Option.h"
//Option<T>

#include "Iterator.h"
//Iterator<T>

#include "Core/Memory/Memory.h"

#include "Meta/Aliases.h"
#include "Meta/Assert.h"

#pragma once

namespace Cthulhu
{

constexpr U64 DefaultSlack = 32;

template<typename T>
struct Array
{
    Array()
    {
        Construct((T*)new Byte[DefaultSlack * sizeof(T)], 0);
        Memory::Set<T>(Real, NULL, Allocated * sizeof(T));
        //use NULL not nullptr because NULL can cast to int and nullptr cant
    }

    Array(const Array& Other)
    {
        Construct(Memory::NewDuplicate(Other.Real, Other.Allocated * sizeof(T)), Other.Length);
    }

    Array(T* Data, U64 PtrLen)
    {
        Construct(Data, PtrLen * sizeof(T));
    }

    Array(std::initializer_list<T> InitList)
    {
        Construct(InitList.begin(), InitList.size());
    }

    Array(U64 Times, Lambda<T(U64)> Generator)
    {
        Slack = DefaultSlack;
        Allocated = Times + DefaultSlack;
        Length = Times;

        Real = (T*)new Byte[Allocated * sizeof(T)];
        
        for(U64 I = 0; I < Times; I++)
        {
            Real[I] = Generator(I);
        }
        
    }

    Array& operator=(const Array& Other)
    {
        Construct(Memory::NewDuplicate<T>(Other.Real, sizeof(T) * Other.Length), Other.Length);
    }

    ALWAYSINLINE U64 Len() const { return Length; }

    bool ValidIndex(U64 Index) const { return Index <= Length; }

    Option<T> At(U64 Index) const { return ValidIndex(Index) ? Some(Real[Index]) : None<T>(); }

    ALWAYSINLINE T& operator[](U64 Index) const
    {
        ASSERT(ValidIndex(Index), "taking item from invalid index in operator[]");
        return Real[Index];
    }

    Array operator+(const T& Item)
    {
        Array Ret = *this;
        Ret.Append(Item);

        return Ret;
    }

    Array operator+(const Array& Other)
    {
        Array Ret = *this;
        Ret.Append(Other);

        return Ret;
    }

    Array& operator+=(const T& Item)
    {
        Append(Item);
        return *this;
    }

    Array& operator+=(const Array& Other)
    {
        Append(Other);
        return *this;
    }

    void Append(const T& Item)
    {
        if(Length >= Allocated)
        {
            Expand(1);
        }

        Real[Length++] = Item;
    }

    void Append(const Array& Other)
    {
        if(Length + Other.Len() >= Allocated)
        {
            Expand(Other.Len());
        }

        const U64 OldLen = Length;
        Length += Other.Len();

        
        for(U64 I = 0; I < OldLen; I++)
        {
            Real[I + OldLen] = Other[I];
        }
    }

    ALWAYSINLINE T Pop() 
    {
        ASSERT(Length > 0, "Trying to pop a value off of an empty array");
        return Real[--Length];
    }

    Array Section(U64 From, U64 To) const
    {
        T* Temp = Memory::NewDuplicate<T>(Real + sizeof(T) * From, To - From);

        return Array(Temp, To - From);
    }

    Option<U64> Find(const T& Item) const
    {
        for(U64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item)
                return Some(I);
        }

        return None<U64>();
    }

    ALWAYSINLINE bool Has(const T& Item) const
    {
        return Find(Item).Valid();
    }

    U64 Count(const T& Item) const
    {
        U64 Ret = 0;
        
        for(U64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item)
                Ret++;
        }
        
        return Ret;
    }

    Array Filter(Lambda<bool(const T&)> Block) const
    {
        Array Ret;
        
        for(U64 I = 0; I < Length; I++)
        {
            if(Block(Real[I]))
            {
                Ret += Real[I];
            }
        }
        
        return Ret;
    }

    Array Map(Lambda<T(const T&)> Transform) const
    {
        Array Ret;
        
        for(U64 I = 0; I < Length; I++)
        {
            Ret += Transform(Real[I]);
        }
        
        return Ret;
    }

    Iterator<Array<T>, T> Iterate() { return Iterator<Array<T>, T>(*this); }

    Array Reverse() const
    {
        Array Ret;
        
        for(U64 I = Length - 1; I >= 0; I--)
        {
            Ret += Real[I];
        }
        
        return Ret;
    }

    ~Array() 
    { 
        delete[] reinterpret_cast<Byte*>(Real); 
    }

private:

    void Construct(T* Data, U64 InitialLen, U64 ExtraSlack = DefaultSlack)
    {
        Real = Data;
        Length = InitialLen;
        Allocated = InitialLen;
        Slack = ExtraSlack;
    }

    void Expand(U64 ExtraLen)
    {
        Allocated += ExtraLen + Slack;
        T* Temp = Real;
        Real = (T*)new Byte[Allocated * sizeof(T)];
        
        Memory::Copy<T>(Temp, Real, Length);
        
        delete[] (Byte*)Temp;
    }

    T* Real;
    U64 Length;
    U64 Allocated;
    U64 Slack;
};

}
