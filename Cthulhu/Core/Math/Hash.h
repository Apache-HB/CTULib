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

#include "Meta/Aliases.h"

#include "Core/Collections/CthulhuString.h"

#pragma once

namespace Cthulhu::Consts
{
	constexpr U32 MersenePrime = 151;
}

namespace Cthulhu::Utils
{

constexpr CTU_INLINE U32 Hash(I8 Item)  { return Item; }
constexpr CTU_INLINE U32 Hash(I16 Item) { return Item; }
constexpr CTU_INLINE U32 Hash(I32 Item) { return Item; }
constexpr CTU_INLINE U32 Hash(I64 Item) { return static_cast<U32>(Item) ^ Consts::MersenePrime; }
constexpr CTU_INLINE U32 Hash(U8 Item)  { return Item; }
constexpr CTU_INLINE U32 Hash(U16 Item) { return Item; }
constexpr CTU_INLINE U32 Hash(U32 Item) { return Item; }
constexpr CTU_INLINE U32 Hash(U64 Item) { return static_cast<U32>(Item) ^ Consts::MersenePrime; }

CTU_INLINE U32 Hash(const String& Item)
{
    U32 Ret = 0;
    
    for(U32 I = 0; I < Item.Len(); I++)
    {
        Ret ^= Item[I];
    }
    
    return Ret;
}

}