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

namespace Cthulhu::JSON
{

enum class Type : U8
{
    Object,
    Array,
    Bool,
    Null,
    Int,
    Float,
    String
};

struct Object
{
    Object();
    ~Object();

    Object& operator=(const Object& Other);

    Object& operator=(I64);
    Object& operator=(bool);
    Object& operator=(double);
    Object& operator=(String);
    Object& operator=(Array<Object>);
    Object& operator=(Map<String, Object>);

    Object& operator[](String& Name);
    Object& operator[](I64 Index);

private:

    Type ContentType;

    union
    {
        String Str;
        I64 Int;
        double Float;
        bool Bool;
        Map<String, Object> SubObjects;
        Array<Object> ArrayObjects;
    };
};

}