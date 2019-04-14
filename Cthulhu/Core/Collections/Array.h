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

#include "Core/Traits/IsPOD.h"
#include "Core/Traits/IsSame.h"

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
        : Allocated((U32)InitList.size())
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
     *
     * @code{.cpp}
     * Array<U32> Arr = { 5, 6, 7 };
     *
     * Arr.Append(8);
     *
     * //Arr = { 5, 6, 7, 8 };
     * @endcode
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
     *
     * @code{.cpp}
     *
     * Array<U32> Arr = { 10, 20, 30 };
     * Array<U32> Other = { 30, 20, 10 };
     *
     * Arr.Append(Other);
     *
     * //Arr = { 10, 20, 30, 30, 20, 10 };
     * @endcode
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
     *
     * @code{.cpp}
     *
     * Array<U32> Arr = { 5, 10, 15 };
     *
     * Arr += 20;
     *
     * //Arr = { 5, 10, 15, 20 };
     * @endcode
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
     *
     * @code{.cpp}
     *
     * Array<U32> Arr = { 5, 10, 15 };
     * Array<U32> Other = { 20, 25, 30 };
     *
     * Arr += Other;
     * 
     * //Arr = { 5, 10, 15, 20, 25, 30 };
     *
     * @endcode
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
     *
     * @code{.cpp}
     *
     * Array<U32> Arr = { 5, 10, 15 };
     *
     * U32 I = Arr.Pop();
     *
     * //I = 15
     * @endcode
     */
    T Pop()
    {
        ASSERT(Length >= 1, "Cant pop item off an empty list");
        return Real[--Length];
    }

    /**
     * @brief Check if an index would be inside the arrays bounds
     * 
     * @param Index The index to check
     * @return true the index is in range
     * @return false the index is out of range
     */
    bool ValidIndex(U32 Index) const { return 0 <= Index && Index <= Length; }

    /**
     * @brief Get an item from an array by index
     * 
     * @param Index the index to get from
     * @return T& the iten at that index
     */
    CTU_INLINE T& operator[](U32 Index) const
    {
        ASSERT(ValidIndex(Index), "IndexOutOfRange");
        return Real[Index];
    }

    /**
     * @brief Get an item from an array if its in range
     * 
     * @param Index The index to get from
     * @return Option<T> Some<T> if index is in range or None<T> if its out of range
     */
    Option<T> At(U32 Index) const { return ValidIndex(Index) ? Some(Real[Index]) : None<T>(); }

    /**
     * @brief Get the length of an array
     * 
     * @return U32 the length of the array
     */
    CTU_INLINE U32 Len() const { return Length; }
    
    /**
     * @brief get the slack the array has
     * 
     * @return U16 the current slack
     */
    CTU_INLINE U16 GetSlack() const { return Slack; }
    
    /**
     * @brief set the slack the array uses
     * 
     * @param NewSlack the slack to use instead
     */
    CTU_INLINE void SetSlack(U16 NewSlack) { Slack = NewSlack; }
    
    /**
     * @brief get the allocated size of the array
     * 
     * @return U32 the actual amount of elements the array can fit
     */
    CTU_INLINE U32 RealSize() const { return Allocated; }
    
    /**
     * @brief get the raw pointer the array has
     * 
     * @return T* the raw pointer
     */
    CTU_INLINE T* operator*() const { return Real; }
    
    /**
     * @brief get the ray pointer the array has
     * 
     * @return T* the raw pointer
     */
    CTU_INLINE T* Data() const { return Real; }

    /**
     * @brief get the first element in the array
     * 
     * @return T& a reference to the first element
     */
    CTU_INLINE T& Front() const { ASSERT(Len() > 0, "An empty array has no front"); return Real[0]; }

    /**
     * @brief get the last item in the array
     * 
     * @return T& a reference to the last element
     */
    CTU_INLINE T& Back() const { ASSERT(Len() > 0, "An empty array has no back"); return Real[Length]; }

    //STL iterators, dont use directly
    //use for(auto& I : Arr) instead
    T* begin() const { return Real; }
    T* end() const { return Real + Length; }

    /**
     * @brief Cut N elements from the front of the array
     * 
     * @param Amount the amount of elements to remove from the front
     */
    void Cut(U32 Amount)
    {
        ASSERT(Amount <= Length, "Cutting beyond end of array");
        Real = Memory::Move(Real, Real + Amount, (Length -= Amount));
    }

    /**
     * @brief Cut N elements from the back of the array
     * 
     * @param Amount the amount of elements to drop from the back
     */
    void Drop(U32 Amount)
    {
        ASSERT(Amount <= Length, "Dropping over the back of the array");
        Length -= Amount;
    }

    /**
     * @brief Find the first occurence of a value
     * 
     * @param Item the item to search for
     * @return Option<U32> the index of the item if the array contained the item
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
     * @brief check if an array contains an item
     * 
     * @param Item the item to check for existence
     * @return true if the array contains the item
     * @return false if the array does not contain the item
     */
    CTU_INLINE bool Has(const T& Item) const
    {
        return Find(Item).Valid();
    }

    /**
     * @brief count the number of occurences of an element in an array
     * 
     * @param Item the item to count
     * @return U32 the number of times the item occured
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
     * @brief claim the raw pointer
     * this makes the array unusable after that and doing any other operations
     * is undefined behaviour and will more than likley crash
     * 
     * @return T* the arrays raw data
     */
    T* Claim()
    {
        T* Ret = Real;
        Real = nullptr;
        return Ret;
    }

    /**
     * @brief the default slack of an array
     * @description this value is used to resize the array
     *              everytime the internal array size gets 
     *              bigger than the internally allocated size.
     */
    static constexpr U32 DefaultSlack = 32;

    /**
     * @brief Destroy the Array object
     * 
     * @description this will call the destrutor for every object in the array
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

/**
 * @brief take any trivial item and turn it into a byte array
 * 
 * this can be helpful to serialize blocks of memory without having to worry about
 * messing with `reinterpret_cast` or accidentally editing memory
 * 
 * @tparam T 
 * @param Data 
 * @return Array<Byte> 
 */
template<typename T>
Array<Byte> RawBytes(T Data)
{
    static_assert(IsDecimal<T>::Value || IsFloat<T>::Value || IsPOD<T>::Value, "T must be a decimal, float or POD type");

    Byte* Bytes = new Byte[sizeof(T)];
    Memory::Copy<T>(&Data, Bytes, sizeof(T));
    Array<Byte> Ret = { Bytes, sizeof(T) };

    return Ret;
}

} // Cthulhu
