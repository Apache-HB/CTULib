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

#pragma once

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