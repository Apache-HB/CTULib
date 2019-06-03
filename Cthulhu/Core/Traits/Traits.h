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

#include "Meta/Macros.h"

#pragma once

//TODO: document

namespace Cthulhu
{

struct False 
{ 
    static constexpr bool Value = false; 
    constexpr operator bool() const { return false; } 
};

struct True
{
    static constexpr bool Value = true;
    constexpr operator bool() const { return true; }
};

/**
 * @brief compile time meta-template to check if a type is a pointer
 * 
 * @tparam T the object to check for a pointer on
 */
template<typename T>
struct IsPointer : False {};

template<typename T> struct IsPointer<T*> : True {};

template<typename T> struct IsPointer<const T> : IsPointer<T> {};
template<typename T> struct IsPointer<volatile T> : IsPointer<T> {};
template<typename T> struct IsPointer<const volatile T> : IsPointer<T> {};

}