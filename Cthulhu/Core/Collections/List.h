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

#include <initializer_list>

#pragma once

namespace Cthulhu
{

namespace Private
{

template<typename T>
struct Node
{
    T Content;
    Node* Next;
};

}

template<typename T>
struct List
{
    List();
    List(std::initializer_list<T> InitList);

    List(const List& Other);

    void Push(const T& Item);
    T Pop();

    Private::Node<T>* Front() const;
    Private::Node<T>* Back() const;

private:
    Private::Node<T> Head;
    Private::Node<T> Tail;
};

} //Cthulhu