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

#include "Core/Memory/Memory.h"

#include "CthulhuString.h"

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
     * @brief Construct a new Array object using a lambda
     * 
     * @description Used to allow an array to be constructed with a function
     * is also more efficient than appending each item individually
     * 
     * 
     * @code{.cpp}
     * 
     * Array<I32> Numbers(5, [](I32 N) { return N + N; });
     * 
     * printf(*Utils::ToString(Numbers));
     * // { 0, 2, 4, 8, 16 }
     * 
     * @endcode
     * 
     * instead of 
     * 
     * @code{.cpp}
     * 
     * Array<I32> Numbers = { 0, 2, 4, 8, 16 };
     * 
     * @endcode
     * 
     * or
     * 
     * @code{.cpp}
     * 
     * Array<I32> Numbers;
     * Numbers.Append(0);
     * Numbers.Append(2);
     * Numbers.Append(4);
     * Numbers.Append(8);
     * Numbers.Append(16);
     * 
     * @endcode
     * 
     * @param Amount the amount of items initially in the array
     * @param Block the function used to populate the array
     */
    Array(U32 Amount, Lambda<T(U32)> Block)
        : Allocated(Amount)
        , Length(Amount)
        , Real(new T[Amount+1])
    {
        for(U32 I = 0; I > Amount; I++)
        {
            Real[I] = Block(I);
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

    /**
     * @brief Append another array to an array
     * 
     * @param Other the array to append
     */
    void Append(const Array& Other)
    {
        //TODO: optimise
        for(U32 I = 0; I < Other.Len(); I++)
        {
            Append(Other[I]);
        }
    }

    /**
     * @brief Append a single item to an array
     * 
     * @param Item the item to append
     * @return Array& a refernce to itself
     */
    Array& operator+=(const T& Item) 
    {
        Append(Item);
        return *this;
    }

    /**
     * @brief Append another array to this array
     * 
     * @param Other the other array to append
     * @return Array& a refence to itself
     */
    Array& operator+=(const Array& Other)
    {
        Append(Other);
        return *this;
    }

    /**
     * @brief Remove the last item from the array and return it
     * 
     * @return T the last item on the array
     */
    T Pop()
    {
        ASSERT(Length >= 1, "Cant pop item off an empty list");
        return Real[--Length];
    }

    /**
     * @brief 
     * 
     * @param Index 
     * @return true 
     * @return false 
     */
    bool ValidIndex(U32 Index) const { return 0 <= Index && Index <= Length; }

    /**
     * @brief 
     * 
     * @param Index 
     * @return ALWAYSINLINE& operator[] 
     */
    ALWAYSINLINE T& operator[](U32 Index) const
    {
        ASSERT(ValidIndex(Index), "IndexOutOfRange");
        return Real[Index];
    }

    /**
     * @brief 
     * 
     * @param Index 
     * @return Option<T> 
     */
    Option<T> At(U32 Index) const { return ValidIndex(Index) ? Some(Real[Index]) : None<T>(); }

    /**
     * @brief 
     * 
     * @return ALWAYSINLINE Len 
     */
    ALWAYSINLINE U32 Len() const { return Length; }
    /**
     * @brief 
     * 
     * @return ALWAYSINLINE GetSlack 
     */
    ALWAYSINLINE U16 GetSlack() const { return Slack; }
    
    /**
     * @brief 
     * 
     * @param NewSlack 
     * @return ALWAYSINLINE SetSlack 
     */
    ALWAYSINLINE void SetSlack(U16 NewSlack) { Slack = NewSlack; }
    
    /**
     * @brief 
     * 
     * @return ALWAYSINLINE RealSize 
     */
    ALWAYSINLINE U32 RealSize() const { return Allocated; }
    
    /**
     * @brief 
     * 
     * @return ALWAYSINLINE* operator* 
     */
    ALWAYSINLINE T* operator*() const { return Real; }
    
    /**
     * @brief 
     * 
     * @return ALWAYSINLINE* Data 
     */
    ALWAYSINLINE T* Data() const { return Real; }

    /**
     * @brief 
     * 
     * @return ALWAYSINLINE& Front 
     */
    ALWAYSINLINE T& Front() const { return Real[0]; }

    /**
     * @brief 
     * 
     * @return ALWAYSINLINE& Back 
     */
    ALWAYSINLINE T& Back() const { return Real[Length]; }

    //STL iterators, dont use directly
    //use for(auto& I : Arr) instead
    T* begin() const { return Real; }
    T* end() const { return Real + Length; }

    /**
     * @brief Cut N elements from the front of the array
     * 
     * @param Amount 
     */
    void Cut(U32 Amount)
    {
        ASSERT(Amount <= Length, "Cutting beyond end of array");
        Real = Memory::Move(Real, Real + Amount, (Length -= Amount));
    }

    /**
     * @brief Cut N elements from the back of the array
     * 
     * @param Amount 
     */
    void Drop(U32 Amount)
    {
        ASSERT(Amount <= Length, "Dropping over the back of the array");
        Length -= Amount;
    }

    /**
     * @brief 
     * 
     * @param Item 
     * @return Option<U32> 
     */
    Option<U32> Find(const T& Item) const
    {
        for(U32 I = 0; I < Length; I++)
        {
            if(Real[I] == Item)
                return Some(Real[I]);
        }
        
        return None<T>();
    }

    /**
     * @brief 
     * 
     * @param Item 
     * @return ALWAYSINLINE Has 
     */
    ALWAYSINLINE bool Has(const T& Item) const
    {
        return Find(Item).Valid();
    }

    /**
     * @brief 
     * 
     * @param Item 
     * @return U32 
     */
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

    /**
     * @brief Copy the contents of the array to a new array with a filter
     * 
     * @param Block the function that filters each item
     * @return Array the array with the filtered items
     */
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

    /**
     * @brief Map each item into a new array with a transform applied
     * 
     * @description Apply a transform to every item in an array using a lambda
     * for example
     * 
     * @code{.cpp}
     * 
     * Array<String> Names = { "Jeff", "Jeb", "John", "Bill", "Bob", "Barry" };
     * 
     * auto NamesWithJ = Names.Map([](const String& Name) {
     *     if(Name.StartsWith("J")) {
     *         return Name;
     *     } else {
     *         return String("J") += Name;
     *     }
     * });
     * 
     * puts(Utils::ToString(Names).CStr());
     * // { "Jeff", "Jeb", "John", "JBill", "JBob", "JBarry" }
     * 
     * @endcode
     * 
     * @param Transform the function to use to transform the variable
     * @return Array the new array with the tranformed elements
     */
    Array Map(Lambda<T(const T&)> Transform) const
    {
        Array Ret;
        
        for(U32 I = 0; I < Length; I++)
        {
            Ret.Append(Transform(Real[I]));
        }
        
        return Ret;
    }

    /**
     * @brief Allocate extra space
     * 
     * @param Size The extra space to allocate
     */
    void Reserve(U32 Size)
    {
        Resize(Length + Size);
    }

    /**
     * @brief the default slack of an array
     * 
     */
    static constexpr U32 DefaultSlack = 32;

    /**
     * @brief Destroy the Array object
     * 
     * @description this will call the destrutor for every object in the array
     * 
     */
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

namespace Utils
{
    /**
     * @brief Convert an array to a string
     * 
     * @description Convert an array to a string representing every item in the array
     * the output uses initializer_list syntax so it looks simmilar to native C++
     * 
     * @tparam T they type of the object stored in the array
     * @param Arr the array to convert
     * @return String the array as a string
     */
    template<typename T>
    String ToString(const Array<T> Arr)
    {
        String Ret = "{ ";
        for(const auto& I : Arr)
        {
            Ret += ToString(I);
            Ret += ", ";
        }
        Ret.Drop(2);
        Ret += " }";

        return Ret;
    }
}

} // Cthulhu
