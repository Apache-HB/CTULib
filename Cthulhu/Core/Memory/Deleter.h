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

#pragma once

namespace Cthulhu
{

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
struct Deleter
{
    /**
     * @brief 
     * 
     * @param Item 
     */
    CTU_INLINE static void Delete(T* Item)
    {
        delete Item;
    }
};

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
struct Deleter<T[]>
{
    /**
     * @brief delete an array allocated with new[]
     * 
     * @param Item the array to delete
     */
    CTU_INLINE static void Delete(T* Item)
    {
        delete[] Item;
    }
};

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
struct Freeer
{
    /**
     * @brief free memory that was allocated using Memory::Alloc instead of new
     * 
     * @param Item the item to free
     */
    static void Delete(T* Item)
    {
        if(Item) Memory::Free<T>(Item);
    }
};

}