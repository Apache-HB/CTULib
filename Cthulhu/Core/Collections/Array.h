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
#include "Iterator.h"
#include "Meta/Assert.h"
#include "Core/Memory/Memory.h"
#include "Option.h"

#pragma once

namespace Cthulhu
{

template<typename T>
struct Array
{
    Array()
        : Length(32)
        , Allocated(32)
        , Slack(32)
        , Real(new T[Slack])
    {}

    //init an array with a size
    Array(U64 Size, bool ZeroMemory = false)
        : Length(Size)
        , Allocated(Size)
        , Slack(32)
        , Real(new T[Size])
    {
        if(ZeroMemory)
            Memory::Zero<T>(Real, Length * sizeof(T));
    }

    Array(U64 Times, T Item)
        : Length(Times)
        , Allocated(Times)
        , Slack(32)
    {
        Real = new T[Times];
        
        for(U64 I = 0; I < Times; I++)
        {
            Real[I] = Item;
        }
    }

    /**claims ptr as its own, dont use ptr directly once constructed
     * 
     */
    Array(T* Ptr, U64 PtrLength)
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

    Array(U64 Times, Lambda<T(U64)> Block)
        : Slack(32)
        , Length(Times)
        , Allocated(32)
        , Real(new T[Times])
    {
        for(U64 I = 0; I < Times; I++)
        {
            Real[I] = Block(I);
        }
    }

    U64 Len() const { return Length; }

    bool ValidIndex(U64 Index) const { return 0 <= Index && Index <= Length; }

    Option<T> At(U64 Index) const { return (ValidIndex(Index)) ? Some<T>(Real[Index]) : None<T>(); }

    T& operator[](U64 Index) const
    {
        ASSERT(ValidIndex(Index), "Accessing array at invalid index is undefined");
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
        
        const U64 OldLength = Length;
        Length += Other;
        
        for(U64 I = OldLength; I < Other.Length; I++)
        {
            Real[I] = Other[I - OldLength];
        }
    }

    Array Section(U64 From, U64 To) const;

    bool Has(const T& Item) const
    {
        for(U64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item) return true;
        }

        return false;
    }

    Option<U64> FindFirst(const T& Item) const
    {
        for(U64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item) return Some(I);
        }

        return None<U64>();
    }

    Option<U64> FindLast(const T& Item) const
    {
        for(U64 I = Length - 1; I >= 0; I--)
        {
            if(Real[I] == Item) return Some(I);
        }
        
        return None<U64>();
    }
    
    U64 Count(const T& Item) const
    {
        U64 Ret = 0;
        
        for(U64 I = 0; I < Length; I++)
        {
            if(Real[I] == Item) Ret++;
        }

        return Ret;
    }

    Array Filter(Lambda<bool(const T&)> Block)
    {
        Array Ret;
        
        for(U64 I = 0; I < Length; I++)
        {
            const T& Item = Real[I];
            
            if(Block(Item)) 
                Ret += Item;
        }

        return Ret;
    }
    
    template<typename TCollector = Array<T>, typename TReturn = T>
    TCollector Map(Lambda<void(TCollector*, const T&)> Block)
    {
        TCollector Ret;

        for(U64 I = 0; I < Length; I++)
        {
            Block(&Ret, Real[I]);
        }

        return Ret;
    }

    Iterator<Array<T>, T> Iterate() { return Iterator<Array<T>, T>(*this); }

    ~Array() { delete[] Real; }

private:

    void Construct(const T* NewContent, U64 PtrLength)
    {
        Length = PtrLength;
        Allocated = PtrLength + Slack;

        Real = new T[Allocated];

        for(U64 I = 0; I < Length; I++)
        {
            Real[I] = NewContent[I];
        }
    }

    void Resize(U64 NewSize)
    {
        Allocated = NewSize + Slack;

        T* Temp = Real;
        Real = new T[Allocated];
        
        for(U64 I = 0; I < Length; I++)
        {
            Real[I] = Temp[I];
        }
        
        delete[] Temp;
    }

    T* Real;
    U64 Length;
    U64 Allocated;
    U64 Slack;
};

} //Cthulhu
