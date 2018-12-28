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

#include "Hash.h"
#include "Core/Collections/Map.h"
#include "Core/Collections/CthulhuString.h"
#include "Core/Types/Types.h"
#include "Core/Collections/Result.h"

#include "FileSystem/File.h"

/**
 * @brief 
 * 
 */
namespace Cthulhu::JSON
{

/**
 * @brief all the types a json object can be
 * 
 */
enum class Type : U8
{
    Map, ///< a map of names to subobjects
    Array, ///< an array of values
    Int, ///< an integer value
    Float, ///< a floating point value
    String, ///< a string
    Bool, ///< a true/false boolean value
    Null, ///< a nothing
};

struct Object
{
    Object();
    Object(Type T);

    Object(Map<String, Object>* Data);
    Object(Array<Object>* Data);
    Object(String* Str);
    Object(I64 Num);
    Object(float Num);
    Object(bool Val);
    Object(TNull);

    Object operator[](const String& Key) const;
    Object operator[](I64 Index) const;

    ALWAYSINLINE Type ItemType() const { return ObjectType; }

    void Append(Object& Item);

    Object& operator=(const Object& Other);
    Object& operator=(Map<String, Object>* Data);
    Object& operator=(Array<Object>* Data);
    Object& operator=(String* Data);
    Object& operator=(I64 Num);
    Object& operator=(float Num);
    Object& operator=(bool Val);
    Object& operator=(TNull);

    operator Map<String, Object>() const;
    operator Array<Object>() const;
    operator String() const;
    operator I64() const;
    operator float() const;
    operator bool() const;

    ~Object();

    friend String ToString(const Object& Data);

    String DumpObject() const;

private:
    
    void Clear();

    bool StructureEquals(const Object& Other) const;

    Type ObjectType;

    union
    {
        //All non-trivial types are pointers so the constructors
        //and destructors dont break stuff
        Map<String, Object>* MappedObjects;
        Array<Object>* ObjectList;
        String* StringVal;
        I64 IntVal;
        float FloatVal;
        bool BoolVal;
    };
};

enum class ErrorType : U8
{
    Depth,
    BadToken,
    Overflow,
    Malformed
};

struct ParseError
{
    I64 Distance;
    I64 Line;
    ErrorType ErrType;
};

Result<Object, ParseError> Parse(const String& Data);
Result<Object, ParseError> Load(const String& Path);

FileSystem::File* Dump(const Object& Data, const String& Path);

} // Cthulhu::JSON
