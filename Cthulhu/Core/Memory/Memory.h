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

#if OS_APPLE
#   include <malloc/malloc.h>
#else
#   include <malloc.h>
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
     * @tparam T    the type the memory represents
     * @param Memory    the pointer to set the value of
     * @param Value     the value to set the pointer to
     * @param Len       the length of the memory the pointer points to
     * @return T*       the Memory param
     */
    template<typename T>
    CTU_INLINE T* Set(T* Memory, int Value, size_t Len) 
    { 
        return (T*)memset((void*)Memory, Value, Len); 
    }
    
    /**
     * @brief move memory from one location to another
     * 
     * @tparam T    the type of the memory to move
     * @param From  the memory location to take from
     * @param Into  the memory location to move to
     * @param Len   the length of the data to move
     * @return T*   the location of the moved memory
     */
    template<typename T>
    CTU_INLINE T* Move(const T* From, T* Into, size_t Len) 
    { 
        return (T*)memmove((void*)Into, (void*)From, Len); 
    }
    
    /**
     * @brief copy memory from one location to another
     * 
     * @tparam T    the type of the memory to copy
     * @param From  the location to copy memory from
     * @param Into  the location to copy memory to
     * @param Len   the length of the memory to copy
     * @return T* a pointer to the copies memory
     */
    template<typename T>
    CTU_INLINE T* Copy(const T* From, T* Into, U32 Len) 
    { 
        return (T*)memcpy((void*)Into, (void*)From, Len); 
    }

    /**
     * @brief compare memory between two different pointers
     * 
     * @tparam T    the type of memory to compare
     * @param Left  the left memory to compare
     * @param Right the right memory to compare
     * @param Len   the amount of memory to compare
     * @return I32  the difference between the first 2 non-equal bytes
     *              if 0 then the memory is equal
     */
    template<typename T>
    CTU_INLINE I32 Compare(const T* Left, const T* Right, U32 Len) 
    { 
        return (I32)memcmp((void*)Left, (void*)Right, Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Memory 
     * @param Len 
     * @return CTU_INLINE* Zero 
     */
    template<typename T>
    CTU_INLINE T* Zero(const T* Memory, U32 Len) 
    {
        return (T*)memset((void*)Memory, 0, Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Data 
     * @param NewLen 
     * @return CTU_INLINE* Realloc 
     */
    template<typename T>
    CTU_INLINE T* Realloc(T* Data, U32 NewLen) 
    { 
        return (T*)realloc((void*)Data, NewLen); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Len 
     * @return CTU_INLINE* Alloc 
     */
    template<typename T>
    CTU_INLINE T* Alloc(U32 Len) 
    { 
        return (T*)malloc(Len); 
    }

    /**
     * @brief 
     * 
     * @tparam T 
     * @param Data 
     * @return CTU_INLINE Free 
     */
    template<typename T>
    CTU_INLINE void Free(T* Data) 
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
     * @brief   duplicate the memory of a type without invoking copy
     *          or move constructors. this can be dangerous but also 
     *          very useful for certain applications 
     * 
     * @tparam T    the type of variable to duplicate
     * @param Data  the data to copy
     * @param Len   the length of the data in bytes to copy
     * @return T*   a pointer to the copied object. 
     *              this needs to be Free'd later to avoid memory leaks
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
     * @tparam T    the type of the memory
     * @param Block the memory to find the size of
     * @return U32  the allocated size of the block of memory
     */
    template<typename T>
    U32 AllocSize(T* Block)
    {
#if defined(OS_WINDOWS)
        return _msize((void*)Block);
#elif defined(OS_LINUX)
        return malloc_usable_size((void*)Block);
#else
        return malloc_size((void*)Block);
#endif
    }
}

}