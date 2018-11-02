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
        : Real(reinterpret_cast<T*>(new Byte[DefaultSlack * sizeof(T)]))
        , Length(0)
        , Allocated(DefaultSlack)
        , Slack(DefaultSlack)
    {}

    Array(T* Data, U64 DataLen)
        : Real(Data)
        , Length(DataLen)
        , Allocated(DataLen)
        , Slack(DefaultSlack)
    {}

    Array(U64 StartLength, bool Zero = false)
        : Real(reinterpret_cast<T*>(new Byte[StartLength * sizeof(T)]))
        , Length(StartLength)
        , Allocated(StartLength)
        , Slack(DefaultSlack)
    {
        if(Zero)    
            Memory::Zero<T>(Real, StartLength * sizeof(T));
    }

    Array(U64 Times, Lambda<T(U64)> Block)
        : Real(reinterpret_cast<T*>(new Byte[Times * sizeof(T)]))
        , Length(Times)
        , Allocated(Times)
        , Slack(DefaultSlack)
    {
        for(U64 I = 0; I < Times; I++)
        {
            Real[I] = Block(I);
        }
    }

    Array& operator=(const Array& Other)
    {
        Length = Other.Length;
        Allocated = Other.Allocated;
        Slack = DefaultSlack;

        Real = reinterpret_cast<T*>(new Byte[Allocated * sizeof(T)]);
        Memory::Copy<T>(Other.Real, Real, Length * sizeof(T));

        return *this;
    }

    U64 Len() const { return Length; }

    bool ValidIndex(U64 Index) const { return Index <= Length; }

    Option<T> At(U64 Index) const { return ValidIndex(Index) ? Some(Real[Index]) : None<T>(); }

    T& operator[](U64 Index) const
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
            Resize(Allocated + 1);
        }

        Real[Length++] = Item;
    }

    void Append(const Array& Other)
    {
        if(Length + Other.Len() >= Allocated)
        {
            Resize(Allocated + Other.Len());
        }

        const U64 OldLen = Length;
        Length += Other.Len();

        
        for(U64 I = 0; I < OldLen; I++)
        {
            Real[I + OldLen] = Other[I];
        }
    }

    T Pop() 
    {
        ASSERT(Length > 0, "Trying to pop a value off of an empty array");
        return Real[--Length];
    }

    Array Section(U64 From, U64 To) const
    {
        #warning NO_IMPL()
        NO_IMPL();
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

    bool Has(const T& Item) const
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
        #warning NO_IMPL()
        NO_IMPL();
    }

    Array Map(Lambda<T(const T&)> Transform) const
    {
        #warning NO_IMPL()
        NO_IMPL();
    }

    Iterator<Array<T>, T> Iterate() { return Iterator<Array<T>, T>(*this); }

    Array Reverse() const
    {
        #warning NO_IMPL()
        NO_IMPL();
    }

    ~Array() { delete[] Real; }

private:

    void Resize(U64 PtrLen)
    {
        Allocated = PtrLen + Slack;
        Byte* Temp = reinterpret_cast<Byte*>(Real);

        //reinterpret cast it to avoid calling constructors and stuff
        Byte* NewReal = new Byte[Allocated * sizeof(T)];
        
        for(U64 I = 0; I < Length * sizeof(T); I++)
        {
            NewReal[I] = Temp[I];
        }
        
        delete[] Temp;

        Real = reinterpret_cast<T*>(NewReal);
    }

    T* Real;
    U64 Length;
    U64 Allocated;
    U64 Slack;
};

}
