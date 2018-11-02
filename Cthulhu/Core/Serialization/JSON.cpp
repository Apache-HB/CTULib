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

#include "Core/Memory/Unique.h"

#include "Hashes.h"
#include "JSON.h"

using namespace Cthulhu;
using namespace Cthulhu::JSON;

Cthulhu::JSON::Object::~Object()
{

}

Cthulhu::JSON::Object::Object(const Object& Other)
{
    *this = Other;
}

Cthulhu::JSON::Object::Object(I64 Val)
{
    ContentType = Type::Int;
    Int = Val;
}

Cthulhu::JSON::Object::Object(bool Val)
{
    ContentType = Type::Bool;
    Bool = Val;
}

Cthulhu::JSON::Object::Object(double Val)
{
    ContentType = Type::Float;
    Float = Val;
}

Cthulhu::JSON::Object::Object(String Val)
{
    ContentType = Type::String;
    Str = Val;
}

Cthulhu::JSON::Object::Object(Array<Object> Val)
{
    ContentType = Type::Array;
    ArrayObjects = Val;
}

Cthulhu::JSON::Object::Object(Map<String, Object> Val)
{
    ContentType = Type::Object;
    SubObjects = Val;
}

Cthulhu::JSON::Object::Object(Type ObjectType, String RawValue)
{
    ContentType = ObjectType;
    Raw = RawValue;
}

Cthulhu::JSON::Object::Object(TNull)
{
    ContentType = Type::Null;
}

Object& Cthulhu::JSON::Object::operator=(const Object& Other)
{
    ContentType = Other.ContentType;
        
    switch(Other.ContentType)
    {
        case Type::Object:
            SubObjects = Other.SubObjects;
            return *this;
        case Type::Array:
            ArrayObjects = Other.ArrayObjects;
            return *this;
        case Type::Bool:
            Bool = Other.Bool;
            return *this;
        case Type::Null:
            return *this;
        case Type::Int:
            Int = Other.Int;
            return *this;
        case Type::Float:
            Float = Other.Float;
            return *this;
        case Type::String:
            Str = Other.Str;
            return *this;
        default:
            SEGFAULT();
            printf("%hhu\n", Other.ContentType);
            ASSERT_NO_ENTRY("Object didnt have a type");
            return *this;
    }
}

Object& Cthulhu::JSON::Object::operator=(I64 Val)
{
    ContentType = Type::Int;
    Int = Val;

    return *this;
}

Object& Cthulhu::JSON::Object::operator=(bool Val)
{
    ContentType = Type::Bool;
    Bool = Val;
    return *this;
}

Object& Cthulhu::JSON::Object::operator=(double Val)
{
    ContentType = Type::Float;
    Float = Val;

    return *this;
}

Object& Cthulhu::JSON::Object::operator=(String Val)
{
    ContentType = Type::String;
    Str = Val;

    return *this;
}

Object& Cthulhu::JSON::Object::operator=(Array<Object> Val)
{
    ContentType = Type::Array;
    ArrayObjects = Val;

    return *this;
}

Object& Cthulhu::JSON::Object::operator=(Map<String, Object> Val)
{
    ContentType = Type::Object;
    SubObjects = Val;

    return *this;
}

Object& Cthulhu::JSON::Object::operator=(TNull)
{
    ContentType = Type::Null;
    return *this;
}

Object& Cthulhu::JSON::Object::operator[](String& Name)
{
    if(ContentType == Type::Object)
    {
        return SubObjects[Name].Value;
    }

    ASSERT_NO_ENTRY("trying to take a object from something that isnt an object");
}

Object& Cthulhu::JSON::Object::operator[](I64 Index)
{
    if(ContentType == Type::Array)
    {
        return ArrayObjects[Index];
    }

    ASSERT_NO_ENTRY("Trying to access an indexed array that isnt an index");
}

Cthulhu::JSON::Object::operator String() const
{
    return Str;
}

Cthulhu::JSON::Object::operator I64() const
{
    return Int;
}

Cthulhu::JSON::Object::operator double() const
{
    return Float;
}

Cthulhu::JSON::Object::operator bool() const
{
    return Bool;
}

Cthulhu::JSON::Object::operator Map<String, Object>() const
{
    return SubObjects;
}

Cthulhu::JSON::Object::operator Array<Object>() const
{
    return ArrayObjects;
}


Object Cthulhu::JSON::Load(String Content, U32 MaxDepth)
{

}

namespace
{

using ObjectMap = Map<String, Object>;

String DumpMap(Unique<ObjectMap>, U32, U32);
String DumpArray(Array<Object>&, U32, U32);

String DumpObject(Object& Data, U32 Indent, U32 Initial)
{
    switch(Data.GetType())
    {
        case Type::Object: {
            Unique<ObjectMap> Temp(new ObjectMap(Data));
            String Ret = DumpMap(Temp, Indent, Initial);
            return Ret;
        }

        case Type::Array: {
            Array<Object> Temp = Data;
            return DumpArray(Temp, Indent, Initial);
        }
        
        case Type::Bool: return StringUtils::ToString((bool)Data);
        case Type::Null: return "null";
        case Type::Int: return StringUtils::ToString((I64)Data);
        case Type::Float: return StringUtils::ToString((double)Data);
        
        case Type::String: {
            Array<String> Ret = Array<String>();
            Ret.Append(Data);
            return String("\"{0}\"").Format(Ret);
        }

        default: 
            ASSERT_NO_ENTRY("Object had no type");
            return "";
    }
}

String DumpMap(Unique<ObjectMap> Data, U32 Indent, U32 Initial)
{
    String Ret = "{\n";

    printf("Yeet\n");

    for(auto& Item : Data->Items().Iterate())
    {
        printf("Yet\n");
        Array<String> Args = {
            StringUtils::Padding(" ", Indent),
            Item.First,
            DumpObject(Item.Second, Indent + Initial, Initial)
        };

        printf("Bob\n");

        Ret += String("{0}\"{1}\": {2},\n").Format(Args);
    }

    printf("Yot\n");

    Ret.Drop(2);

    Ret += "\n";
    Ret += StringUtils::Padding(" ", Indent);
    Ret += "}";

    printf("Yort\n");

    return Ret;
}

String DumpArray(Array<Object>& Data, U32 Indent, U32 Initial)
{
    String Ret = "[\n";
    for(auto& I : Data.Iterate())
    {
        Ret += StringUtils::Padding(" ", Indent);
        Ret += DumpObject(I, Indent + Initial, Initial);
        Ret += ",\n";
    }

    Ret.Drop(2);
    Ret += "\n";
    Ret += StringUtils::Padding(" ", Indent);
    Ret += "]";

    return Ret;
}

}

String Cthulhu::JSON::Dump(Object& Data, U32 Indent)
{
    String Ret = "{\n";
    Ret += StringUtils::Padding(" ", Indent);
    Ret += DumpObject(Data, Indent, Indent);
    Ret += "}\n";
    return Ret;
}

String Cthulhu::JSON::Object::ToString(U32 Indent) const
{
    
}