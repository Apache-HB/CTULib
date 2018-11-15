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
        : Real(Memory::Alloc<T>(sizeof(T) * DefaultSlack))
    {}

    Array(const Array& Other)
        : Real(Memory::Duplicate<T>(Other, Other.Allocated))
        , Allocated(Other.Allocated)
        , Length(Other.Length)
    {}

    Array(const T* Ptr, U32 PtrLen)
        : Real(Ptr)
        , Allocated(PtrLen)
        , Length(PtrLen)
    {}
    
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

    static const U32 DefaultSlack = 32;

private:

    void Resize(U32 NewSize)
    {
        T* Temp = Real;
        Real = new T[NewSize];

        
        for(U32 I = 0; I < Math::Min(Length, NewSize); I++)
        {
            Real[I] = Temp[I];
        }
        
        delete[] Temp;
        Allocated = NewSize;
    }

    T* Real;
    U32 Length{0}, Allocated{DefaultSlack};
    U16 Slack{DefaultSlack};
};

}


/*
template<typename T>
struct Array
{
    Array() 
        : Length(0)
    {
        Real = Memory::Alloc<T>(sizeof(T) * Slack);
        Allocated = Slack;
    }

    Array(T* Ptr, U32 PtrLen) 
        : Real(Ptr)
        , Length(PtrLen)
        , Allocated(PtrLen)
    {}

    Array(const Array& Other) 
        : Real(Memory::Duplicate<T>(Other.Real, Other.Allocated))
        , Length(Other.Length)
        , Allocated(Other.Allocated)
    {}

    ALWAYSINLINE U32 Len() const { return Length; }
    ALWAYSINLINE U32 RealSize() const { return Allocated; }

    ALWAYSINLINE U16 GetSlack() const { return Slack; }
    ALWAYSINLINE void SetSlack(U16 NewSlack) { Slack = NewSlack; }

    Array& operator=(const Array& Other) = delete;

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

    Array operator+(const T& Item) const
    {
        Array Ret(*this);
        Ret.Append(Item);

        return Ret;
    }

    Array operator+(const Array& Other) const
    {
        Array Ret(*this);
        Ret.Append(Other);

        return Ret;
    }

    void Append(const T& Item)
    {
        if(Length + 1 >= Allocated)
        {
            Resize(Allocated + DefaultSlack);
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

    ALWAYSINLINE T Pop()
    {
        ASSERT(Length >= 0, "Popping an item off an empty array will break it");
        return Real[--Length];
    }

    ALWAYSINLINE bool ValidIndex(U32 Index) const { return Index <= Length; }

    ALWAYSINLINE T& operator[](U32 Index) const
    {
        ASSERT(ValidIndex(Index), "Array out of bounds in operator[]");
        return Real[Index];
    }

    const Option<T> At(U32 Index) const 
    {
        return ValidIndex(Index) ? Some(Real[Index]) : None<T>();
    }

    void Cut(U32 Amount)
    {
        ASSERT(Amount < Length, "Trying to cut beyond the end of the array");
        Real += sizeof(T) * Amount;
    }

    ALWAYSINLINE void Drop(U32 Amount)
    {
        ASSERT(Amount < Length, "Trying to drop beyond the back of the array");
        Length -= Amount;
    }

    Array SubSection(U32 From, U32 To) const
    {
        Array Ret = *this;
        
        Ret.Cut(From);
        Ret.Drop(Len() - To);

        return Ret;
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

    Iterator<Array<T>, T> Iterate()
    {
        return Iterator<Array<T>, T>(*this);
        //have to be explicit with the return signature because
        //type inference doesnt know how to turn a non-const object
        //into a const object when implicity told to do so
    }

    const Iterator<Array<T>, T> ConstIterate() const
    {
        return Iterator<Array<T>, T>(*this);
    }

    ALWAYSINLINE T* Raw() const { return Real; }
    ALWAYSINLINE T* operator*() const { return Real; }

    void Resize(U32 NewSize)
    {
        ASSERT(NewSize > Length, "Trying to unallocate objects in array, would probably break something");
        
        T* Temp = Real;
        
        Real = Memory::Alloc<T>(sizeof(T) * NewSize);
        
        for(U32 I = 0; I < Length; I++)
        {
            Real[I] = Temp[I];
        }
        
        Allocated = NewSize;
    }

    ~Array()
    {
        for(U32 I = 0; I < Length; I++)
        {
            Real[I].~T();
        }

        Memory::Free<T>(Real);
    }

private:

    U32 Length, Allocated;
    T* Real;
    U16 Slack{DefaultSlack};
};
*/

/*Array()
    {
        Construct((T*)new Byte[DefaultSlack * sizeof(T)], 0);
        Memory::Zero<T>(Real, Allocated * sizeof(T));
    }

    Array(const Array& Other)
    {
        Construct(Memory::NewDuplicate(Other.Real, Other.Allocated * sizeof(T)), Other.Length);
    }

    Array(T* Data, U32 PtrLen)
    {
        Construct(Data, PtrLen * sizeof(T));
    }

    Array(std::initializer_list<T> InitList)
    {
        Construct(InitList.begin(), InitList.size());
    }

    Array(U32 Times, Lambda<T(U32)> Generator)
    {
        Slack = DefaultSlack;
        Allocated = Times + DefaultSlack;
        Length = Times;

        Real = (T*)new Byte[Allocated * sizeof(T)];
        
        for(U32 I = 0; I < Times; I++)
        {
            Real[I] = Generator(I);
        }
        
    }

    Array& operator=(const Array& Other)
    {
        //printf("[%llu]\n", Other[0]);
        Construct(Other.Real, Other.Length, 0);
    }

    ALWAYSINLINE U32 Len() const { return Length; }

    bool ValidIndex(U32 Index) const { return Index <= Length; }

    Option<T> At(U32 Index) const { return ValidIndex(Index) ? Some(Real[Index]) : None<T>(); }

    ALWAYSINLINE T& operator[](U32 Index) const
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

        const U32 OldLen = Length;
        Length += Other.Len();

        
        for(U32 I = 0; I < OldLen; I++)
        {
            Real[I + OldLen] = Other[I];
        }
    }

    ALWAYSINLINE T Pop() 
    {
        ASSERT(Length > 0, "Trying to pop a value off of an empty array");
        return Real[--Length];
    }

    Array Section(U32 From, U32 To) const
    {
        T* Temp = Memory::NewDuplicate<T>(Real + sizeof(T) * From, To - From);

        return Array(Temp, To - From);
    }

    Option<U32> Find(const T& Item) const
    {
        for(U32 I = 0; I < Length; I++)
        {
            if(Real[I] == Item)
                return Some(I);
        }

        return None<U32>();
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
            {
                Ret += Real[I];
            }
        }
        
        return Ret;
    }

    Array Map(Lambda<T(const T&)> Transform) const
    {
        Array Ret;
        
        for(U32 I = 0; I < Length; I++)
        {
            Ret += Transform(Real[I]);
        }
        
        return Ret;
    }

    Iterator<Array<T>, T> Iterate() { return Iterator<Array<T>, T>(*this); }

    Array Reverse() const
    {
        Array Ret;
        
        for(U32 I = Length - 1; I >= 0; I--)
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

    void Construct(T* Data, U32 InitialLen, U32 ExtraSlack = DefaultSlack)
    {
        Real = Data;
        Length = InitialLen;
        Allocated = InitialLen;
        Slack = ExtraSlack;
    }

    void Expand(U32 ExtraLen)
    {
        Allocated += ExtraLen + Slack;
        T* Temp = Real;
        Real = (T*)new Byte[Allocated * sizeof(T)];
        
        Memory::Copy<T>(Temp, Real, Length);
        
        delete[] (Byte*)Temp;
    }

    T* Real;
    U32 Length;
    U32 Allocated;
    U32 Slack;*/
