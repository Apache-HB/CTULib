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

#include "Cthulhu/Meta/Aliases.h"
#include "Cthulhu/Meta/Assert.h"

#pragma once

namespace Cthulhu
{

template<typename T, U32 Size>
struct Buffer
{
    constexpr Buffer() : Index(0) {}
    
    void Push(T Item)
    {
        Real[Index++] = Item;
    }

    T Pop()
    {
        return Real[--Index];
    }

    CTU_INLINE U32 Length() const { return Index; }
    CTU_INLINE T* Data() const { return Real; }
    CTU_INLINE T* operator*() const { return Real; }
    CTU_INLINE void Wipe() { Index = 0; }

    CTU_INLINE T& operator[](U32 Index) const 
    { 
        ASSERT(Index <= Size, "Accessing buffer out of bounds");
        return Real[Index]; 
    }

    CTU_INLINE ~Buffer() { delete[] Real; }
private:
    T* Real = new T[Size];
    U32 Index;
};

}