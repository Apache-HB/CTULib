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

#include "Option.h"
#include "Array.h"
#include "Map.h"
#include "Iterator.h"

#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

struct String
{
    String(const char* Data = "");
    String(const String& Other);

    String& operator=(const String& Other);

    ~String();

    U32 Len() const;

    bool IsEmpty() const;
    operator bool() const;

    bool operator==(const String& Other) const;
    bool operator!=(const String& Other) const;

    String& operator+=(const String& Other);
    String& operator+=(const char Other);

    String operator+(const String& Other) const;
    String operator+(const char Other) const;

    String& operator<<(I64 Num);
    String& operator<<(double Num);
    String& operator<<(bool Val);

    void Append(const String& Other);

    //push to front of string
    void Push(const String& Other);
    void Push(char Other);

    char* operator*() const;
    char* Raw() const;

    bool StartsWith(const String& Pattern) const;
    bool EndsWith(const String& Pattern) const;

    bool ValidIndex(U32 Index) const;

    char& operator[](U32 Index) const;

    char At(U32 Index) const;

    String SubSection(U32 Start, U32 End) const;

    Option<U32> Find(const String& Pattern) const;

    String Upper() const;
    String Lower() const;

    void Trim(const String& Pattern = " ");
    String Replace(const String& Search, const String& Substitute) const;

    String Format(const Array<String>& Args) const;
    String Format(const Map<String, String>& Args) const;

    //cut from front
    void Cut(U32 Amount);

    //drop from back
    void Drop(U32 Amount);

    bool Has(const String& Pattern) const;

    Iterator<Array<char>, char> Iterate();

    String Reversed() const;

private:
    char* Real;
};

namespace CString
{
    //dup
    char* Duplicate(const char* Data);
    char* Duplicate(const char* Data, U32 Limit);
    
    //cpy
    char* Copy(const char* From, char* Into);
    char* Copy(const char* From, char* Into, U32 Limit);
    
    char* Merge(const char* Left, const char* Right);

    //cat
    char* Concat(char* From, const char* Into);
    char* Concat(char* From, const char* Into, U32 Limit);

    //cmp
    int Compare(const char* Left, const char* Right);
    int Compare(const char* Left, const char* Right, U32 Limit);
    
    //strstr
    char* Section(const char* Needle, char* Haystack);

    //len
    U32 Length(const char* Content);

    char* Reverse(const char* Content);
}

namespace StringUtils
{
    String Padding(const String& Text, U32 Repeat);
    Option<I64> ParseInt(const String& Text);
    Option<double> ParseDouble(const String& Text);
    Option<bool> ParseBool(const String& Text);

    String ToString(I64 Num);
    String ToString(double Num);
    String ToString(bool Val);
}

namespace StringConstants
{
    const String PathSeperator();
    const String Whitespace();
    const String UpperCase();
    const String LowerCase();
    const String OctDigits();
    const String HexDigits();
    const String Digits();
    const String Chars();
    const String Punctuation();
    const String Printable();
}

} //Cthulhu
