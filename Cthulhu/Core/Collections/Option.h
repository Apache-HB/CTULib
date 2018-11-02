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

#include "Core/Types/Lambda.h"

#pragma once

namespace Cthulhu
{

template<typename T>
struct Option
{
    template<typename TOpt>
    friend Option<TOpt> Some(TOpt Real);

    template<typename TOpt>
    friend Option<TOpt> None();

    bool Valid() const { return IsSet; }
    operator bool() const { return IsSet; }

    const T Get() const { ASSERT(Valid(), "Attempting to Get() unset content is undefined behaviour"); return Content; }
    T Get() { ASSERT(Valid(), "Attempting to Get() unset content is undefined behaviour"); return Content; }

    T Or(T Other) { return (Valid()) ? Content : Other; }

    template<typename TRet>
    TRet Fold(Lambda<TRet(T)> WhenValid, Lambda<TRet()> Otherwise) const
    {
        return (IsSet) ? WhenValid(Content) : Otherwise();
    }

private:
    T Content;
    bool IsSet;
    
    Option()
        : IsSet(false)
    {}

    Option(T Item)
        : Content(Item)
        , IsSet(true)
    {}
};

template<typename TOpt>
Option<TOpt> Some(TOpt Input) { return Option<TOpt>(Input); }

template<typename TOpt>
Option<TOpt> None() { return Option<TOpt>(); }

} // Cthulhu

