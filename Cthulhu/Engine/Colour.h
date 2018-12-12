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

#include "Core/Collections/CthulhuString.h"
#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

namespace Engine
{

constexpr U8 RGB = 0;
constexpr U8 RGBA = 1;

template<I8>
struct Colour{};

template<>
struct Colour<RGB>
{
    U8 Red, Green, Blue;
};

template<>
struct Colour<RGBA>
{
    U8 Red, Green, Blue;
    float Alpha;
};

} // Graphics

namespace Utils
{
    String ToString(const Engine::Colour<Engine::RGB> Col);
    String ToString(const Engine::Colour<Engine::RGBA> Col);
} //Utils

} // Cthulhu