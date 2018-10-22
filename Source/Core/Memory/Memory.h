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

namespace Memory
{
    template<typename T>
    ALWAYSINLINE T* Set(T* Memory, int Value, size_t Len) { return (T*)memset((void*)Memory, Value, Len); }
    
    template<typename T>
    ALWAYSINLINE T* Move(const T* Source, T* Dest, size_t Len) { return (T*)memmove((void*)Dest, (void*)Source, Len); }
    
    template<typename T>
    ALWAYSINLINE T* Copy(const T* Source, T* Dest, size_t Len) { return (T*)memcpy((void*)Dest, (void*)Source, Len); }

    template<typename T>
    ALWAYSINLINE int Compare(const T* Source, const T* Other, size_t Len) { return memcmp((void*)Source, (void*)Other, Len); }

    template<typename T>
    ALWAYSINLINE void* Zero(const T* Source, size_t Len) { return Memset(Source, 0, Len); }

    template<typename T>
    ALWAYSINLINE T* Duplicate(const T* Source, size_t Len)
    {
        T* Ret = (T*)malloc(Len);

        Memcpy(Source, Ret, Len);

        return Ret;
    }

    template<typename T>
    ALWAYSINLINE T* Realloc(T* Source, size_t NewLen) { return (T*)realloc((void*)Source, NewLen); }

    template<typename T>
    ALWAYSINLINE T* Alloc(size_t Len) { return (T*)malloc(Len); }

    template<typename T>
    ALWAYSINLINE void Free(T* Data) { free((void*)Data); }
}

}