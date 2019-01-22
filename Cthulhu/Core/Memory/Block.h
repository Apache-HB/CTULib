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

#include "Memory.h"
#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

/**
 * @brief A fixed size block of memory
 * 
 * @tparam T The type of item to be stored in the memory
 * @tparam Size the amount of items to have space for
 */
template<typename T, U32 Size>
struct Block
{
    /**
     * @brief construct a new block of data
     * 
     */
    constexpr Block()
    {
        Real = new T[Size];
    }
    
    /**
     * @brief Construct a new Block object
     * 
     * shallow copy the data from another block
     * 
     * @param Other The block to copy from
     */
    Block(const Block& Other)
    {
        Real = Other.Real;
    }
    
    /**
     * @brief 
     * 
     * @param Index 
     * @return T& 
     */
    T& operator[](U32 Index) const
    {
        ASSERT(Index <= Size, "Accessing block out of range");
        return Real[Index];
    }

    void Wipe()
    {
        Memory::Zero(Real, Size * sizeof(T));
    }

    constexpr U32 Len() const { return Size; }

private:
    T* Real;

public:

    ~Block()
    {
        delete[] Real;
    }

    template<typename TO, U32 TSize>
    friend void Swap(Block<TO, TSize>& Right, Block<TO, TSize>& Left)
    {
        T* Temp = Right.Real;
        Right.Real = Left.Real;
        Left.Real = Temp;
    }

};

} // Cthulhu