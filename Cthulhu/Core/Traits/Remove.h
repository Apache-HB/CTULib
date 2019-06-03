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

#pragma once

namespace Cthulhu
{

//remove all references to get the most basic form of a type
template<typename T> struct RemoveReference { using Type = T; };
template<typename T> struct RemoveReference<T&> { using Type = T; };
template<typename T> struct RemoveReference<T&&> { using Type = T; };

//remove all qualifiers such as const or volatile to get the basic type
template<typename T> struct RemoveQualifiers { using Type = T; };
template<typename T> struct RemoveQualifiers<const T> { using Type = T; };
template<typename T> struct RemoveQualifiers<volatile T> { using Type = T; };
template<typename T> struct RemoveQualifiers<const volatile T> { using Type = T; };

}
