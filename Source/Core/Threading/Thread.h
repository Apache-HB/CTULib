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

#include <thread>

#include "Core/Memory/UniquePtr.h"
#include "Core/Collections/Array.h"
#include "Core/Collections/Pair.h"

#include "Meta/Macros.h"

#pragma once

#if 0

namespace Cthulhu
{

struct ThreadResult
{
    const int ID;
    const void* Result;
    ThreadResult(void* InResult, int ItemID)
        : Result(InResult)
        , ID(ItemID)
    {}

    bool operator==(const int Other) const { return ID == Other; }
};

struct ThreadItem
{
    const int ID;
    Lambda<void*()> Callable;
    ThreadQueue(Lambda<void*()> Callback, int ItemID)
        : Callable(Callback)
        , ID(ItemID)
    {}

    ThreadQueue(int ItemID)
        : Callable([]{})
        , ID(ItemID)
    {}

    bool operator==(const int Other) const { return ID == Other; }
};

class Thread
{
    UniquePtr<std::thread> ThisThread;

    using FunctionQueue = Array<ThreadItem>;
    using DataQueue = Array<ThreadResult>;

    std::mutex QueueMutex;
    FunctionQueue Queue;

    std::mutex CompletedMutex;
    DataQueue Completed;

public:
    Thread()
        : ThisThread(nullptr)
    {
        const auto ThreadRunner = [this]
        {
            while(Queue.Len() != 0)
            {
                const auto Item = Queue.Pop();
                //push the called function and the item uuid onto the stack
                //is also POD, so use init list syntax
                const auto ToAdd = ThreadResult(Item.Callable(), Item.ID);
                Completed.Append(ToAdd);
            }
        };

        ThisThread = UniquePtr<std::thread>(new std::thread(ThreadRunner));
    }

    int AddItem(Lambda<void*()> Function);

private:
    
    bool Prioritize(int ID)
    {
        Optional<int> Index = Queue.Find(ID);
    }

public:

    template<typename T>
    T AwaitItem(int ID)
    {
        Optional<int> Location = Completed.Find(ID);
        
        Location.WhenInvalid([]{
            bool IsQueued = Prioritize(ID);
            if(IsQueued)
            {
                return AwaitItem(ID);
            }
            else
            {
                ASSERT_NO_ENTRY("Tried to await an item with and invalid ID");
            }
        });

        return Completed[Location.Or(-1)];
    }

    Thread(const Thread&&) = delete;
};

}

#endif