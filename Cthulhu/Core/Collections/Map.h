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
#include "Array.h"

#pragma once

namespace Cthulhu
{

constexpr uint32 MersenePrime = 8191;

namespace Private
{

template<typename TKey, typename TVal>
struct MapPair { TKey Key; TVal Val; };

template<typename TKey, typename TVal>
struct MapItem : Array<MapPair<TKey, TVal>>
{
    using ThisPair = MapPair<TKey, TVal>;
    using Super = Array<MapPair<TKey, TVal>>;

    TVal& operator=(const MapPair<TKey, TVal> Item)
    {
        for(uint64 I = 0; I < Super::Len(); I++)
        {
            if((*this)[I].Key == Item.Key)
            {
                (*this)[I].Val = Item.Val;
                return Item.Val;
            }
        }
        
        Append(Item);

        return Item.Val;
    }
};

} //Private

template<typename T> 
uint64 Hash(const T&);

template<typename TKey, typename TVal>
struct Map
{
    using ItemPair = Private::MapItem<TKey, TVal>;

    ItemPair& operator[](const TKey& Key) const
    {
        return Data[Hash(Key)];
    }

private:
    Array<ItemPair> Data;
};

template<> uint64 Hash(const uint8& Num) { return Num % MersenePrime; }
template<> uint64 Hash(const uint16& Num) { return Num % MersenePrime; }
template<> uint64 Hash(const uint32& Num) { return Num % MersenePrime; }
template<> uint64 Hash(const uint64& Num) { return Num % MersenePrime; }

template<> uint64 Hash(const int8& Num) { return Num % MersenePrime; }
template<> uint64 Hash(const int16& Num) { return Num % MersenePrime; }
template<> uint64 Hash(const int32& Num) { return Num % MersenePrime; }
template<> uint64 Hash(const int64& Num) { return Num % MersenePrime; }

} //Cthulhu
