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

#include "Size.h"

#pragma once

namespace Cthulhu::Standard
{

template<typename T>
struct InitList
{
    using Type = T;
    
    ALWAYSINLINE constexpr InitList() noexcept
        : Front(nullptr)
        , Length(0)
    {}

    ALWAYSINLINE constexpr TSize Size() const noexcept { return Length; }

    ALWAYSINLINE constexpr const T* begin() const noexcept { return Front; }

    ALWAYSINLINE constexpr const T* End() const noexcept { return Front + Length; }

private:
    const T* Front;
    TSize Length;

    ALWAYSINLINE constexpr InitList(const T* Begin, TSize Len) noexcept
        : Front(Begin)
        , Length(Len)
    {}
};

} //Cthulhu::Standard