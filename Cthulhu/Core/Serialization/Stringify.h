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
#include "Core/Collections/Array.h"
#include "Core/Collections/Map.h"

#pragma once

namespace Cthulhu
{

template<typename T>
String ToString(const Array<T>& Arr)
{
    String Ret = "[ ";
    
    for(const auto& I : Arr)
    {
        Ret += ToString(I);
        Ret += ", ";
    }

    Ret.Drop(2);
    Ret += " ]";
    return Ret;
}

template<typename TKey, typename TVal>
String ToString(const Map<TKey, TVal>& InMap)
{
    String Ret = "{\n";

    for(const auto& I : InMap.Items())
    {
        Ret += ToString(I.First);
        Ret += ": ";
        Ret += ToString(I.Second);
        Ret += ",\n";
    }

    Ret.Drop(2);
    Ret += "\n}";
    return Ret;
}

String ToString(const String& Item)
{
    return Item;
}

}