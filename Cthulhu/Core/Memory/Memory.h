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

#pragma once

//TODO document

namespace Cthulhu
{

/**Typesafe memory mangment wrapper for the c-stdlib
 * 
 * 
 */
namespace Memory
{
    template<typename T>
    ALWAYSINLINE T* Set(T* Memory, int Value, size_t Len) 
    { 
        return (T*)memset((void*)Memory, Value, Len); 
    }
    
    template<typename T>
    ALWAYSINLINE T* Move(const T* From, T* Into, size_t Len) 
    { 
        return (T*)memmove((void*)Into, (void*)From, Len); 
    }
    
    template<typename T>
    ALWAYSINLINE T* Copy(const T* From, T* Into, size_t Len) 
    { 
        return (T*)memcpy((void*)Into, (void*)From, Len); 
    }

    template<typename T>
    ALWAYSINLINE int Compare(const T* Left, const T* Right, size_t Len) 
    { 
        return memcmp((void*)Left, (void*)Right, Len); 
    }

    template<typename T>
    ALWAYSINLINE T* Zero(const T* Memory, size_t Len) 
    {
        return (T*)memset((void*)Memory, 0, Len); 
    }

    template<typename T>
    ALWAYSINLINE T* Realloc(T* Data, size_t NewLen) 
    { 
        return (T*)realloc((void*)Data, NewLen); 
    }

    template<typename T>
    ALWAYSINLINE T* Alloc(size_t Len) 
    { 
        return (T*)malloc(Len); 
    }

    template<typename T>
    ALWAYSINLINE void Free(T* Data) 
    { 
        free((void*)Data); 
    }

    template<typename T>
    ALWAYSINLINE T* Duplicate(const T* Data, size_t Len)
    {
        T* Ret = Alloc<T>(Len);

        Copy(Data, Ret, Len);

        return Ret;
    }

    template<typename T>
    ALWAYSINLINE T* NewDuplicate(const T* Data, U64 Len)
    {
        T* Ret = (T*)new Byte[Len];

        Copy(Data, Ret, Len);

        return Ret;
    }
}

}