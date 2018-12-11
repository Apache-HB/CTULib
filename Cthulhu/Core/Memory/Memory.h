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

#include <cstring>
#include <cstdlib>

#include "Meta/Macros.h"

#if defined(OS_WINDOWS) || defined(OS_LINUX)
#   include <malloc.h>
#else
#   include <malloc/malloc.h>
#endif

#pragma once

namespace Cthulhu
{

/**
 * @brief Typesafe memory mangment wrapper for the c-stdlib
 * 
 * @description these were designed to remove the amount of void* casts needed
 * when performing low level allocations in C++. as C++ is more typesafe that C
 * code.
 * 
 * @code{.cpp}
 * 
 * char* Str = malloc(25); 
 * // Fails to compile as void* cannot implicity cast to char*
 * 
 * char* Str = (char*)malloc(25); 
 * // Compiles as the void* is explicitly casted
 * 
 * @endcode
 * 
 * with these templates you can cut useless typing down to a minumum
 * 
 * @code{.cpp}
 * 
 * using namespace Cthulhu::Memory;
 * 
 * char* Str = Alloc<char>(25); 
 * // compiles and has more readable syntax
 * 
 * //or as a better example
 * 
 * Set(Str, 0, 25); 
 * // no need for template arguments as C++17 allows these
 * // to be deduced from the argument types
 * 
 * @endcode
 * 
 */
namespace Memory
{
    /**
     * @brief set the value of a block of memory
     * 
     * @description functionally identical to <a href="http://www.cplusplus.com/reference/cstring/memset/">cstring/memset</a>
     * 
     * @tparam T the type the memory represents
     * @param Memory the pointer to set the value of
     * @param Value the value to set the pointer to
     * @param Len the length of the memory the pointer points to
     * @return T* the Memory param
     */
    template<typename T>
    ALWAYSINLINE T* Set(T* Memory, int Value, size_t Len) 
    { 
        return (T*)memset((void*)Memory, Value, Len); 
    }
    
    /**
     * @brief 
     * 
     * @tparam T 
     * @param From 
     * @param Into 
     * @param Len 
     * @return ALWAYSINLINE* Move 
     */
    template<typename T>
    ALWAYSINLINE T* Move(const T* From, T* Into, size_t Len) 
    { 
        return (T*)memmove((void*)Into, (void*)From, Len); 
    }
    
    /**
     * @brief 
     * 
     * @tparam T 
     * @param From 
     * @param Into 
     * @param Len 
     * @return ALWAYSINLINE* Copy 
     */
    template<typename T>
    ALWAYSINLINE T* Copy(const T* From, T* Into, U32 Len) 
    { 
        return (T*)memcpy((void*)Into, (void*)From, Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Left 
     * @param Right 
     * @param Len 
     * @return ALWAYSINLINE Compare 
     */
    template<typename T>
    ALWAYSINLINE int Compare(const T* Left, const T* Right, U32 Len) 
    { 
        return memcmp((void*)Left, (void*)Right, Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Memory 
     * @param Len 
     * @return ALWAYSINLINE* Zero 
     */
    template<typename T>
    ALWAYSINLINE T* Zero(const T* Memory, U32 Len) 
    {
        return (T*)memset((void*)Memory, 0, Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Data 
     * @param NewLen 
     * @return ALWAYSINLINE* Realloc 
     */
    template<typename T>
    ALWAYSINLINE T* Realloc(T* Data, U32 NewLen) 
    { 
        return (T*)realloc((void*)Data, NewLen); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Len 
     * @return ALWAYSINLINE* Alloc 
     */
    template<typename T>
    ALWAYSINLINE T* Alloc(U32 Len) 
    { 
        return (T*)malloc(Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Data 
     * @return ALWAYSINLINE Free 
     */
    template<typename T>
    ALWAYSINLINE void Free(T* Data) 
    { 
        free((void*)Data); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Data 
     * @param Len 
     * @return T* 
     */
    template<typename T>
    T* Duplicate(const T* Data, U32 Len)
    {
        T* Ret = Alloc<T>(Len);

        Copy(Data, Ret, Len);

        return Ret;
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Data 
     * @param Len 
     * @return ALWAYSINLINE* NewDuplicate 
     */
    template<typename T>
    T* NewDuplicate(const T* Data, U32 Len)
    {
        T* Ret = (T*)new Byte[Len];

        Copy(Data, Ret, Len);

        return Ret;
    }

    /**
     * @brief Get the allocated size of a block of memory
     * 
     * @tparam T the type of the memory
     * @param Block the memory to find the size of
     * @return U32 the allocated size of the block of memory
     */
    template<typename T>
    U32 AllocSize(T* Block)
    {
#if defined(OS_WINDOWS)
        return _msize((void*)Block);
#elif defined(OS_LINUX)
        return malloc_usable_zone((void*)Block);
#else
        return malloc_size((void*)Block);
#endif
    }
}

}