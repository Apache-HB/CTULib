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

#if 0

#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Array.h"
#include "Core/Collections/Map.h"

#include "Core/Types/Types.h"

#pragma once

namespace Cthulhu::JSON
{

enum class Error : U8
{
    Depth = 0,
    Parse = 1
};

enum class Type : U8
{
    Null = 0,
    Object = 1,
    Array = 2,
    Bool = 3,
    Int = 4,
    Float = 5,
    String = 6
};

struct Object
{
    Object(){};

    Object(const Object& Other);

    Object(I64);
    Object(bool);
    Object(double);
    Object(String);
    Object(Array<Object>);
    Object(Map<String, Object>);
    Object(Type ObjectType, String RawValue);
    Object(TNull);

    ~Object();

    Object& operator=(const Object& Other);

    Object& operator=(I64);
    Object& operator=(bool);
    Object& operator=(double);
    Object& operator=(String);
    Object& operator=(Array<Object>);
    Object& operator=(Map<String, Object>);
    Object& operator=(TNull);

    Object& operator[](String& Name);
    Object& operator[](I64 Index);

    Object& operator()(String& Name);
    Object& operator()(I64 Name);

    String ToString(U32 Indent) const;

    Type GetType() const { return ContentType; }

    operator String() const;
    operator I64() const;
    operator double() const;
    operator bool() const;
    operator Map<String, Object>() const;
    operator Array<Object>() const;

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

    String Raw;
};

Object Load(String Content, U32 MaxDepth = 0);
String Dump(Object& Data, U32 Indent = 0);

}

#endif