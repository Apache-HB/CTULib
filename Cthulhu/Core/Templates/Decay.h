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

#include "Remove.h"

#pragma once

namespace Cthulhu
{

/**
 * @brief decay a type that isnt a reference to the base type
 * 
 * @see Decay
 * 
 * @tparam T the type to decay
 */
template<typename T> 
struct DecayNonReference { using Type = typename RemoveQualifiers<T>::Type; };

/**
 * @brief decay a function pointer to its base types
 * 
 * @tparam TRet the return type of the function pointer
 * @tparam TArgs the argument types
 */
template<typename TRet, typename... TArgs>
struct DecayNonReference<TRet(TArgs...)> { using Type = TRet(*)(TArgs...); };

/**
 * @brief Decay a type to its most basic type
 * 
 * @description this means removing `const` `volatile` `&` references and `*` pointers
 * 
 * @code{.cpp}
 * 
 * Decay<I32*>::Type; // I32
 * Decay<volatile String>::Type; // String
 * 
 * @endcode
 * 
 * @tparam T the type to decay
 */
template<typename T>
struct Decay
{
    using Type = typename DecayNonReference<typename RemoveReference<T>::Type>::Type;
};

}