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

//a bunch of hash functions for different classes

#include "Core/Collections/Map.h"

#include "Core/Collections/CthulhuString.h"

#pragma once


namespace Cthulhu
{

template<> U32 Hash<String>(const String& Item)
{
    U32 Ret = 0;

    for(U32 I = 0; I < Item.Len(); I++)
    {
        Ret ^= Item[I];
    }

    return Ret % MersenePrime;
}

} // Cthulhu
