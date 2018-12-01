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

#include "Core/Math/Math.h"
//Math::Min

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

template<typename T>
struct Array
{
    Array()
        : Real(new T[DefaultSlack])
        , Length(0)
        , Allocated(DefaultSlack)
    {}

    Array(const Array& Other)
        : Real(Memory::NewDuplicate<T>(Other.Data(), Other.Allocated))
        , Allocated(Other.Allocated)
        , Length(Other.Length)
    {}

    Array(T* Ptr, U32 PtrLen)
        : Real(Ptr)
        , Allocated(PtrLen)
        , Length(PtrLen)
    {}
    
    Array(std::initializer_list<T> InitList)
        : Allocated(InitList.size()+1)
        , Length(0)
        , Real(new T[InitList.size()+1])
    {
        for(auto& I : InitList)
        {
            Append(I);
        }
    }

    void Append(const T& Item)
    {        
        if(Length + 1 >= Allocated)
        {
            Resize(Length + DefaultSlack);
        }

        Real[Length++] = Item;
    }

    void Append(const Array& Other)
    {
        //TODO: optimise
        for(U32 I = 0; I < Other.Len(); I++)
        {
            Append(Other[I]);
        }
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

    T Pop()
    {
        ASSERT(Length >= 1, "Cant pop item off an empty list");
        return Real[--Length];
    }

    bool ValidIndex(U32 Index) const { return 0 <= Index && Index <= Length; }

    ALWAYSINLINE T& operator[](U32 Index) const
    {
        ASSERT(ValidIndex(Index), "IndexOutOfRange");
        return Real[Index];
    }

    Option<T> At(U32 Index) const { return ValidIndex(Index) ? Some(Real[Index]) : None<T>(); }

    ALWAYSINLINE U32 Len() const { return Length; }
    ALWAYSINLINE U16 GetSlack() const { return Slack; }
    ALWAYSINLINE void SetSlack(U16 NewSlack) { Slack = NewSlack; }
    ALWAYSINLINE U32 RealSize() const { return Allocated; }
    ALWAYSINLINE T* operator*() const { return Real; }
    ALWAYSINLINE T* Data() const { return Real; }

    Iterator<Array<T>, T> Iterate() { return Iterator<Array<T>, T>(*this); }
    const Iterator<Array<T>, T> ConstIterate() const { return Iterator<Array<T>, T>(*this); }

    //cut from back
    void Cut(U32 Amount)
    {
        //TODO: this doesnt work you muppet
        ASSERT(Amount <= Length, "Cutting beyond end of array");
        Real += (sizeof(T) * Amount);
        Length -= Amount;
    }

    //drop from back
    void Drop(U32 Amount)
    {
        ASSERT(Amount <= Length, "Dropping over the back of the array");
        Length -= Amount;
    }

    Option<U32> Find(const T& Item) const
    {
        for(U32 I = 0; I < Length; I++)
        {
            if(Real[I] == Item)
                return Some(Real[I]);
        }
        
        return None<T>();
    }

    ALWAYSINLINE bool Has(const T& Item) const
    {
        return Find(Item).Valid();
    }

    U32 Count(const T& Item) const
    {
        U32 Ret = 0;

        for(U32 I = 0; I < Length; I++)
        {
            if(Real[I] == Item)
                Ret++;
        }
        
        return Ret;
    }

    Array Filter(Lambda<bool(const T&)> Block) const
    {
        Array Ret;
        
        for(U32 I = 0; I < Length; I++)
        {
            if(Block(Real[I]))
                Ret.Append(Real[I]);
        }
        
        return Ret;
    }

    Array Map(Lambda<T(const T&)> Transform) const
    {
        Array Ret;
        
        for(U32 I = 0; I < Length; I++)
        {
            Ret.Append(Transform(Real[I]));
        }
        
        return Ret;
    }

    void Reserve(U32 Size)
    {
        Resize(Length + Size);
    }

    static const U32 DefaultSlack = 32;

private:

    void Resize(U32 NewSize)
    {
        //TODO: test this more
        Allocated = NewSize;

        //figure out how much to copy
        Length = Math::Min(Length, NewSize);
        
        T* Temp = new T[NewSize];

        for(U32 I = 0; I < Length; I++)
        {
            Temp[I] = Real[I];
        }

        delete[] Real;

        Real = Temp;
    }

    // {
    //     T* Temp = Real;
    //     Real = new T[NewSize];
        
    //     const U32 NewLen = Math::Min(Length, NewSize);
        
    //     for(U32 I = 0; I < NewLen; I++)
    //     {
    //         Real[I] = Temp[I];
    //     }
        
    //     delete[] Temp;
    //     Allocated = NewSize;
    //     Length = NewLen;
    // }

    T* Real;
    U32 Length, Allocated;
    U16 Slack;
};

}
