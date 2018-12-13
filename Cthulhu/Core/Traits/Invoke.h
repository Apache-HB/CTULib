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

#include "Traits.h"
#include "Forward.h"

#pragma once

//TODO: document

namespace Cthulhu
{

/**
 * @brief invoke a callable object such as a lambda
 * 
 * @tparam TObject the type of the object to call
 * @tparam TArgs the types of the arguments
 * @param Object the object to call
 * @param Args the args to call the object with
 * @return auto the return value of Object
 */
template<typename TObject, typename... TArgs>
ALWAYSINLINE auto Invoke(TObject&& Object, TArgs&&... Args)
{
    return Forward<TObject>(Object)(Forward<TArgs>(Args)...);
}

}