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

#pragma once

//TODO: document

namespace Cthulhu
{

template<typename T>
class SharedContent
{
    uint32 Refs;
    T* Content;
};

/**
 * 
 */
template<typename T>
class SharedPtr
{
    /**Shared content
     * should never be null
     */
    SharedContent<T>* Content;
public:
    SharedPtr(T* Item)
        : Content(new SharedContent<T>{1, Item})
    {}

    SharedPtr(const SharedPtr& Other)
        : Content(Other.Content)
    {
        Content->Refs++;
    }

    SharedPtr(const SharedPtr* Other)
        : Content(Other->Content)
    {
        Content->Refs++;
    }

    ~SharedPtr()
    {
        Content->Refs--;
        if(Content->Refs <= 0)
        {
            delete Content->Content;
            delete Content;
        }
    }

    T operator*() const { return *Content->Content; }
    T* operator->() const { return Content->Content; }

    int Refs() const { return Content->Refs; }
};

}