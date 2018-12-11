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

#include "Meta/Assert.h"

#include "JSON.h"

using namespace Cthulhu;
using namespace Cthulhu::JSON;

Object::Object()
{
    ObjectType = Type::Map;
    MappedObjects = new Map<String, Object>();
}

Object::Object(Type T)
{
    ObjectType = T;
    switch(T)
    {
        case Type::Map:
            MappedObjects = new Map<String, Object>();
            break;
        case Type::Array:
            ObjectList = new Array<Object>();
            break;
        case Type::Int:
            IntVal = 0;
            break;
        case Type::Float:
            FloatVal = 0.f;
            break;
        case Type::String:
            StringVal = new String();
            break;
        case Type::Bool:
            BoolVal = false;
            break;
        
        case Type::Null: break;
        
        default:
            ASSERT_NO_ENTRY("Bad json type");
    }
}

Object::Object(Map<String, Object>* Data)
    : ObjectType(Type::Map)
    , MappedObjects(Data)
{}

Object::Object(Array<Object>* Data)
    : ObjectType(Type::Array)
    , ObjectList(Data)
{}

Object::Object(String* Str)
    : ObjectType(Type::String)
    , StringVal(Str)
{}

Object::Object(I64 Num)
    : ObjectType(Type::Int)
    , IntVal(Num)
{}

Object::Object(float Num)
    : ObjectType(Type::Float)
    , FloatVal(Num)
{}

Object::Object(bool Val)
    : ObjectType(Type::Bool)
    , BoolVal(Val)
{}

Object::Object(TNull)
    : ObjectType(Type::Null)
{}

Object::~Object()
{
    switch(ObjectType)
    {
        case Type::Map:
            delete MappedObjects;
            break;
        case Type::Array:
            delete ObjectList;
            break;
        case Type::String:
            delete StringVal;
            break;
        default: break;
    }
}

Object Object::operator[](const String& Key) const
{
    if(ObjectType == Type::Map)
        return MappedObjects->Get(Key, Object());
    return Object();
}

Object Object::operator[](I64 Index) const
{
    if(ObjectType == Type::Array)
        return ObjectList->At(Index).Or(Object());
    return Object();
}

void Object::Append(Object& Item)
{
    ASSERT(ObjectType == Type::Array, "Trying to append to something that isnt an array");

    ObjectList->Append(Item);
}

Object& Object::operator=(const Object& Other)
{
    Clear();

    ObjectType = Other.ObjectType;

    switch(Other.ObjectType)
    {
        case Type::Array:
            ObjectList = Other.ObjectList;
            break;
        case Type::Map:
            MappedObjects = Other.MappedObjects;
            break;
        case Type::String:
            StringVal = Other.StringVal;
            break;
        case Type::Int:
            IntVal = Other.IntVal;
            break;
        case Type::Bool:
            BoolVal = Other.BoolVal;
            break;
        default: break;
    }

    return *this;
}

Object& Object::operator=(Map<String, Object>* Data)
{
    Clear();
    ObjectType = Type::Map;
    MappedObjects = Data;
    return *this;
}

Object& Object::operator=(Array<Object>* Data)
{
    Clear();
    ObjectType = Type::Array;
    ObjectList = Data;
    return *this;
}

Object& Object::operator=(String* Data)
{
    Clear();
    ObjectType = Type::String;
    StringVal = Data;
    return *this;
}

Object& Object::operator=(I64 Num)
{
    Clear();
    ObjectType = Type::Int;
    IntVal = Num;
    return *this;
}

Object& Object::operator=(float Num)
{
    Clear();
    ObjectType = Type::Float;
    FloatVal = Num;
    return *this;
}

Object& Object::operator=(bool Val)
{
    Clear();
    ObjectType = Type::Bool;
    BoolVal = Val;
    return *this;
}

Object& Object::operator=(TNull)
{
    Clear();
    ObjectType = Type::Null;
    return *this;
}

Object::operator Map<String, Object>() const
{
    ASSERT(ObjectType == Type::Map, "Trying to cast a non map type to a map");

    return *MappedObjects;
}

Object::operator Array<Object>() const
{
    ASSERT(ObjectType == Type::Array, "Trying to cast a non array type to an array");

    return *ObjectList;
}

Object::operator String() const
{
    ASSERT(ObjectType == Type::String, "Trying to cast a non string type to a string");

    return *StringVal;
}

Object::operator I64() const
{
    ASSERT(ObjectType == Type::Int, "Trying to cast a non int type to an int");

    return IntVal;
}

Object::operator float() const
{
    ASSERT(ObjectType == Type::Float, "Trying to cast a non float type to a float");

    return FloatVal;
}

Object::operator bool() const
{
    ASSERT(ObjectType == Type::Bool, "Trying to cast a non bool type to a bool");

    return BoolVal;
}

void Object::Clear()
{
    switch(ObjectType)
    {
        case Type::Array:
            delete ObjectList;
            break;
        case Type::Map:
            delete MappedObjects;
            break;
        case Type::String:
            delete StringVal;
            break;
        default: break;
    }
}

bool Object::StructureEquals(const Object& Other) const
{
    NO_IMPL();
    return false;
}

namespace
{

String ObjectToString(const Object&);

String MapToJSON(const Map<String, Object>& Data)
{
    String Ret = "{";

    for(const auto& I : Data.Items().ConstIterate())
    {
        Ret += '"';
        Ret += *I.First;
        Ret += "\": ";
        Ret += ObjectToString(*I.Second);
        Ret += ", ";
    }

    Ret.Drop(2);
    Ret += "}";

    return Ret;
}

String ArrayToJSON(const Array<Object>& Data)
{
    String Ret = "[";

    for(U32 I = 0; I < Data.Len(); I++)
    {
        Ret.Append(ObjectToString(Data[I]) + String(", "));
    }
    
    Ret.Drop(2);
    Ret += "]";

    return Ret;
}

String ObjectToString(const Object& Data)
{
    switch(Data.ItemType())
    {
        case Type::Int: return Utils::ToString((I64)Data);
        case Type::Float: return Utils::ToString((float)Data);
        case Type::Bool: return Utils::ToString((bool)Data);
        case Type::Null: return "null";
        case Type::Array: return ArrayToJSON((Array<Object>)Data);
        case Type::Map: return MapToJSON((Map<String, Object>)Data);
        case Type::String: return (String)Data;
        default:
            ASSERT_NO_ENTRY("Invalid JSON object type");
    }
}

}

String Object::DumpObject() const
{
    return ObjectToString(*this);
}

String ToString(const Object& Data)
{
    return ObjectToString(Data);
}