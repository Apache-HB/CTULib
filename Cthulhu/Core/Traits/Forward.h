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
#include "Remove.h"

#pragma once

namespace Cthulhu
{

/**
 * @brief forward types to add references
 * 
 * @tparam T the type to forward
 * @param Obj the argument to forward
 * @return T&& the forwarded type
 */
template<typename T>
CTU_INLINE T&& Forward(typename RemoveReference<T>::Type& Obj)
{
    return (T&&)Obj;
}

template<typename T>
CTU_INLINE T&& Forward(typename RemoveReference<T>::Type&& Obj)
{
    return (T&&)Obj;
}

}