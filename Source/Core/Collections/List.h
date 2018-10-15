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

#include "Array.h"

#pragma once

namespace Cthulhu
{

template<typename T>
struct Link
{
    T Current;
    Link* Next;
    Link* Last;
};

template<typename T>
class List
{
    Link<T>* Head;
    Link<T>* Tail;
public:
    List() {}
    List(const T& Start)
    {
        Head = new Link<T>{ Start, nullptr, nullptr };
        Tail = Head;
    }

    List(Array<T> Arr)
    {
        for(T&& Each : Arr.Iterate())
        {
            Push(Each);
        }
    }

    ~List() 
    {
        Link<T>* Current = Tail;
        while(Tail)
        {
            Current = Tail->Next;
            delete Current;
        }
    }

    void Push(T& Item)
    {
        if(!Head)
        {
            Head = new Link<T>{ Item, nullptr, nullptr };
            Tail = Head;
        }
        else
        {
            Link<T>* Next = new Link<T>{ Item, nullptr, Head };
            Head->Next = Next;
            Head = Next;
        }
    }

    Optional<T> Pop()
    {
        if(!Head)
        {
            return NullOpt<T>();
        }

        T Ret = Head->Current;
        Link<T>* Last = Head->Last;
        delete Head;
        Head = Last;
        return Optional<T>(Ret);
    }

};

}