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
#include "Deleter.h"

#pragma once

namespace Cthulhu
{

namespace Private
{

template<typename T>
struct SharedContent
{
    T* Content;
    uint64 Refs;
};

} //Private

template<typename T, typename TDeleter = Deleter<T>>
struct Shared
{
    Shared(T* InContent)
        : Content(new SharedContent<T>({ Content, 1 }))
    {}

    T* Take()
    {
        //increment the refs here so that even once all shared pointers go out of scope
        //it doesnt trigger the deleter so the pointer is still valid
        Content->Refs++;
        return Content->Content;
    }

    Shared(const Shared& Other)
    {
        Content = Other.Content;
        Content->Refs++;
    }

    Shared(const Shared* Other)
    {
        Content = Other->Content;
        Content->Refs++;
    }

    const T operator*() const { *Content->Content; }
    T operator*() { return *Content->Content; }

    const T* operator->() const { return Content->Content; }
    T* operator->() { return Content->Content; }

    ~Shared()
    {
        if(--Content->Refs == 0)
        {
            TDeleter::Delete(Content->Content);
            delete Content;
        }
    }

    Shared(const Shared&&) = delete;

private:
    Private::SharedContent<T>* Content;
};

template<typename T>
struct Sharable
{
    Sharable()
        : Contnet(new Content({ this, 1 }))
    {}

    Shared<T> SharedThis() const { return Content; }

private:
    Private::SharedContent<T>* Content;
};

}

#if 0

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

#endif