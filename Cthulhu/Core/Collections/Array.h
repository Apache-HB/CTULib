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

#pragma once

namespace Cthulhu
{

/**
 * @brief A dynamically sized array
 * 
 * @description A dynamically sized slacked array, rather than exponential
 * 
 * @tparam T the type of object to store in the array
 */
template<typename T>
struct Array
{
    /**
     * @brief Default constructor for an array
     * 
     */
    Array()
        : Real(new T[DefaultSlack])
        , Length(0)
        , Allocated(DefaultSlack)
    {}

    /**
     * @brief Copy constructor for an array
     * 
     * @descrption perform a deep copy of all elements in an array
     * 
     * @param Other the array to copy the data from
     */
    Array(const Array& Other)
        : Real(Memory::NewDuplicate<T>(Other.Data(), Other.Allocated))
        , Allocated(Other.Allocated)
        , Length(Other.Length)
    {}

    /**
     * @brief Construct a new Array object from a raw pointer and its length
     * 
     * @description Allows an array to "claim" a pointer as its own data
     *              This makes the pointer unusable once it has been claimed 
     *              by the array
     * 
     * @param Ptr the raw pointer to claim
     * @param PtrLen the length of the raw pointer
     */
    Array(T* Ptr, U32 PtrLen)
        : Real(Ptr)
        , Allocated(PtrLen)
        , Length(PtrLen)
    {}
    
    /**
     * @brief Construct a new Array object from an initializer_list
     * 
     * @description enable initializer_list syntax to make arrays easier to type
     * so instead of 
     * @code{.cpp}
     * 
     * Array<String> Names;
     * Names.Append("Jeb");
     * Names.Append("Bob");
     * Names.Append("Bill");
     * 
     * @endcode
     * the user can type 
     * @code{.cpp}
     * 
     * Array<String> Names = { "Jeb", "Bob", "Bill" };
     * 
     * @endcode
     * instead
     * 
     * @param InitList the initalizer list to use
     */
    Array(std::initializer_list<T> InitList)
        : Allocated(InitList.size())
        , Length(0)
        , Real(new T[InitList.size()+1])
    {
        for(auto& I : InitList)
        {
            Append(I);
        }
    }

    /**
     * @brief push an item to the back of the array
     * 
     * @description simmilar to <a href="http://www.cplusplus.com/reference/vector/vector/push_back/">vector::push_back</a> or rusts
     * <a href="https://doc.rust-lang.org/std/vec/struct.Vec.html#method.push">vec::push</a>
     * 
     * @param Item the item to push
     */
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


    //STL iterators, dont use directly
    //use for(auto& I : Arr) instead
    T* begin() const { return Real; }
    T* end() const { return Real + Length; }

    //cut from back
    void Cut(U32 Amount)
    {
        ASSERT(Amount <= Length, "Cutting beyond end of array");
        Real = Memory::Move(Real, Real + Amount, (Length -= Amount));
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

    ~Array()
    {
        delete[] Real;
    }

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

    T* Real;
    U32 Length, Allocated;
    U16 Slack{DefaultSlack};
};

}
