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

#include "Meta/Assert.h"
#include "Deleter.h"

#pragma once

namespace Cthulhu
{

template<typename T, typename TDeleter = Deleter<T>>
struct Unique
{
    Unique(T* Input = nullptr)
        : Raw(Input)
    {}

    T* Take() 
    {
        T* Ret = Raw;
        Raw = nullptr;
        return Ret;
    }

    CTU_INLINE const T* operator->() const { return Raw; }
    CTU_INLINE T* operator->() { return Raw; }

    CTU_INLINE const T operator*() const { ASSERT(Valid(), "Attempting to deref a null pointer"); return *Raw; }
    CTU_INLINE T operator*() { ASSERT(Valid(), "Attempting to deref a null pointer"); return *Raw; }

    CTU_INLINE bool Valid() const { return Raw != nullptr; }

    CTU_INLINE operator bool() const { return Raw != nullptr; }

    ~Unique()
    {
        TDeleter::Delete(Raw);
    }

    Unique(const Unique&) = delete;
    Unique(const Unique&&) = delete;
    Unique(const Unique*) = delete;

private:

    T* Raw;
};

}



#if 0

//TODO: document

namespace Cthulhu
{

template<typename T>
class UniquePtr
{
    T* Raw;
public:
    UniquePtr(T* Data)
        : Raw(Data)
    {}

    ~UniquePtr(){ delete Raw; }

    bool Valid() const { return Raw != nullptr; }
    operator bool() const { return Raw != nullptr; }

    T operator*() const { return *Raw; }
    T* operator->() const { return Raw; }

    T* Take()
    {
        T* Ret = Raw;
        Raw = nullptr;
        return Ret;
    }
};

}

#endif