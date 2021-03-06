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
#include "Arithmatic.h"
#include "Logic.h"

#pragma once

namespace Cthulhu
{

//check if a type is POD (PlainOldData)
template<typename T>
struct IsPOD : Or<__is_pod(T) || __is_enum(T), IsArithmatic<T>::Value, IsPointer<T>::Value>{}; 
//                ^^^^^^^^       ^^^^^^^^^
//these are some magic things that compilers have without #including anything 

}