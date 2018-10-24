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

#ifdef __OBJC__
#   include <Foundation/Foundation.h>
#endif

#include "CthulhuString.h"
#include "Array.h"
#include "Map.h"
#include "Option.h"
#include "Iterator.h"

#include "Meta/Assert.h"

#include "Core/Math/Math.h"
#include "Core/Memory/Memory.h"

//TODO: lets get rid of this
#include <string>

using Cthulhu::Option;
using Cthulhu::Array;
using Cthulhu::Map;
using Cthulhu::String;
using Cthulhu::Iterator;

using Cthulhu::uint32;
using Cthulhu::int64;
using Cthulhu::Math::Min;

Cthulhu::String::String()
    : Real(CString::Duplicate(""))
{}

Cthulhu::String::String(const char* Input)
    : Real(CString::Duplicate(Input))
{}

Cthulhu::String::String(const String& Other)
    : Real(CString::Duplicate(*Other))
{}


#ifdef __OBJC__

Cthulhu::String::String(NSString* Other)
    : Real([Other UTF8String])
{}

#endif

Cthulhu::String& Cthulhu::String::operator=(const String& Other)
{
    delete[] Real;
    Real = CString::Duplicate(*Other);
    return *this;
}

Cthulhu::String::~String()
{
    delete[] Real;
}

uint32 Cthulhu::String::Len() const { return CString::Length(Real); }

bool Cthulhu::String::IsEmpty() const { return CString::Length(Real) == 0; }

Cthulhu::String::operator bool() const { return CString::Length(Real) == 0; }

bool Cthulhu::String::operator==(const String& Other) const
{
    return CString::Compare(Real, *Other) == 0;
}

bool Cthulhu::String::operator!=(const String& Other) const
{
    return CString::Compare(Real, *Other) != 0;
}

String& Cthulhu::String::operator+=(const String& Other)
{
    Append(Other.Real);
    return *this;
}

String& Cthulhu::String::operator+=(const char* Other)
{
    Append(Other);
    return *this;
}

String& Cthulhu::String::operator+=(const char Other)
{
    const uint32 ThisLen = Len();
    
    char* Ret = Memory::Alloc<char>(ThisLen + 2);
    CString::Copy(Real, Ret);

    Ret[ThisLen] = Other;
    Ret[ThisLen + 1] = '\0';

    delete[] Real;
    Real = Ret;

    return *this;
}

String Cthulhu::String::operator+(const String& Other) const
{
    String Ret = Real;
    Ret += Other;

    return Ret;
}

String Cthulhu::String::operator+(const char* Other) const
{
    String Ret = Real;
    Ret += Other;

    return Ret;
}

String Cthulhu::String::operator+(const char Other) const
{
    String Ret = Real;
    Ret += Other;

    return Ret;
}


String& Cthulhu::String::operator<<(uint64 Num)
{
    Append(StringUtils::ToString(Num));

    return *this;
}

String& Cthulhu::String::operator<<(double Num)
{
    Append(StringUtils::ToString(Num));
    
    return *this;
}

String& Cthulhu::String::operator<<(bool Num)
{
    Append(StringUtils::ToString(Num));

    return *this;
}


void Cthulhu::String::Append(const String& Other)
{
    CString::Concat(Real, Other.Real);
}

char* Cthulhu::String::operator*() const { return Real; }

bool Cthulhu::String::StartsWith(const String& Pattern) const
{
    return CString::CompareN(Real, Pattern.Real, Pattern.Len()) == 0;
}

bool Cthulhu::String::EndsWith(const String& Pattern) const
{
    const uint32 PatternLen = Pattern.Len(),
                 ThisLen = Len();

    if(PatternLen >= ThisLen)
        return Memory::Compare<char>(Pattern.Real, Real + (PatternLen - ThisLen), ThisLen);
    
    return false;
}

bool Cthulhu::String::ValidIndex(uint32 Index) const
{
    return 0 <= Index && Index <= CString::Length(Real);
}

char& Cthulhu::String::operator[](uint32 Index) { return Real[Index]; }

char Cthulhu::String::At(uint32 Index) const 
{
    return ValidIndex(Index) ? Real[Index] : '\0';
}

String Cthulhu::String::Section(uint32 Start, uint32 End) const
{
    char* Temp = CString::DuplicateN(Real, End);
    Temp[Start] = '\0';

    String Ret = Temp;
    delete[] Temp;

    return Ret;
}

Option<uint32> Cthulhu::String::Find(const String& Pattern) const
{
    const uint32 ThisLen = Len();

    if(Pattern.Len() > ThisLen) return None<uint32>();
    
    for(uint32 I = 0; I < ThisLen; I++)
    {
        if(CString::Compare(Real + I, Pattern.Real)) 
            return Some(I);
    }
    
    return None<uint32>();
}

String Cthulhu::String::Lower() const
{
    char* Ret = CString::Duplicate(Real);
    
    while(*Ret)
    {
        if(65 >= *Ret && *Ret <= 90)
            *Ret += 32;
    }

    String Temp = Ret;
    delete[] Ret;

    return Temp;
}

String Cthulhu::String::Upper() const
{
    char* Ret = CString::Duplicate(Real);
    
    while(*Ret)
    {
        if(97 >= *Ret && *Ret <= 122)
            *Ret -= 32;
    }

    String Temp = Ret;
    delete[] Ret;

    return Temp;
}

String Cthulhu::String::Trim(const String& Pattern) const
{
    String Ret = Real;

    const uint32 Length = Pattern.Len();

    while(Ret.StartsWith(Pattern)) Ret.Drop(Length);

    while(Ret.EndsWith(Pattern)) Ret.Cut(Length);

    return Ret;
}

String Cthulhu::String::Replace(const String& Search, const String& Substitute) const
{
    uint32  I = 0, 
            Count = 0,
            SearchLen = Search.Len(),
            SubLen = Substitute.Len();
    
    for(uint32 I = 0; Real[I] != '\0'; I++)
    {
        if(CString::Section(&Real[I], Search.Real) == &Real[I])
        {
            Count++;
            I += SearchLen - 1;
        }
    }
    
    char* Result = new char[Len() + (Count * (SubLen - SearchLen)) + 1];
    I = 0;

    char* Temp = CString::Duplicate(Real);
    
    while(*Temp)
    {
        if(CString::Section(Temp, Search.Real) == Temp)
        {
            CString::Copy(&Result[I], Substitute.Real);
            I += SubLen;
            Temp += SearchLen;
        }
        else
        {
            Result[I++] = *Temp++;
        }
    }

    Result[I] = '\0';
    String Ret = Temp;

    delete[] Temp;

    return Ret;
}

String Cthulhu::String::Format(const Array<String>& Args) const
{
    String Ret = Real;

    const uint64 ArgLen = Args.Len();

    for(uint64 I = 0; I < ArgLen; I++)
    {
        const String ToFind = (String("{") << I) + "}";
        Ret = Ret.Replace(ToFind, Args[I]);
    }

    return Ret;
}

String Cthulhu::String::Format(const Map<String, String>& Args) const
{
    NO_IMPL();

    //String Ret = Real;
    
    /*for(auto&& Entry : Args.Items())
    {
        const String ToFind = String("{") + Entry->Key + "}";
        Ret = Ret.Replace(ToFind, Entry->Value);
    }*/

    //return Ret;
}

void Cthulhu::String::Cut(uint32 Amount)
{
    uint32 Length = Len();
    
    if(Amount >= Length)
    {
        delete[] Real;
        Real = CString::Duplicate("");
    }
    else
    {
        Real[Length - Amount] = '\0';
    }
}

void Cthulhu::String::Drop(uint32 Amount)
{
    if(Amount >= Len())
    {
        delete[] Real;
        Real = CString::Duplicate("");
    }
    else
    {
        Real += Amount;
    }
}

Iterator<String, char> Cthulhu::String::Iterate()
{
    return Iterator<String, char>(*this);
}

bool Cthulhu::String::Has(const String& Pattern) const
{
    return Find(Pattern).Valid();
}

Option<double> Cthulhu::String::Double() const
{
    int Flag = 1,
        Loc = 0,
        Index = 0;
    
    double Res = 0;

    while(Real[Index] == ' ') { Index++; }

    char C;

    while(Real[Index] == '+' || Real[Index] == '-')
    {
        C = Real[Index];
        
        if(C == '-')
        {
            Flag *= -1;
        }
        
        Index++;
    }

    bool Decimal = false;

    while((C = Real[Index++]))
    {
        if(C == '.')
        {
            if(Decimal)
                return None<double>();
            
            Loc = Index;
            Decimal = true;
            continue;
        }

        if(C < '0' && '9' < C)
            return None<double>();

        Res *= 10;
        Res += C - '0';
    }

    Loc = Len() - Loc;

    double Ret = Res;
    
    //shift the decimal place to the corrent location
    for(int I = 0; I < Loc; I++)
    {
        Ret *= 0.1;
    }
    
    Ret *= Flag;

    return Some(Ret);
}

Option<int64> Cthulhu::String::Int() const
{
    int64 Ret = 0;
    
    int Index = 0, 
        Sign = 1;

    while(Real[Index] == ' ') { Index++; }

    while(Real[Index] == '-')
    {
        Index++;
        Sign *= -1;
    }

    char C;

    while((C = Real[Index++]))
    {
        if(C < '0' || '9' < C)
            return None<int64>();

        Ret *= 10;
        Ret += C - '0';
    }

    return Some(Ret * Sign);
}

Option<bool> Cthulhu::String::Bool() const
{
    String Temp = Lower();
    
    if(Temp == "true" || Temp == "yes" || Temp == "y" || Temp == "t")
        return Some(true);

    if(Temp == "false" || Temp == "no" || Temp == "n" || Temp == "f")
        return Some(false);

    return None<bool>();
}






String Cthulhu::StringUtils::Padding(const String& Pattern, uint32 Repeat)
{
    String Ret;
    
    for(uint32 I = 0; I < Repeat; I++)
    {
        Ret += Pattern;
    }

    return Ret;
}

String Cthulhu::StringUtils::Padding(const char Character, uint32 Repeat)
{
    const uint32 WithTerminal = Repeat+1;
    
    char* Ret = new char[WithTerminal];
    Memory::Set<char>(Ret, Character, Repeat);
    Ret[WithTerminal] = '\0';

    String Str(Ret);
    delete[] Ret;
    
    return Str;
}

String Cthulhu::StringUtils::ToString(double Value)
{
    return std::to_string(Value).c_str();
}

String Cthulhu::StringUtils::ToString(uint64 Value)
{
    return std::to_string(Value).c_str();
}

String Cthulhu::StringUtils::ToString(bool Value)
{
    return Value ? "true" : "false";
}





char* Cthulhu::CString::Duplicate(const char* Other)
{
    //figure out the length of the string and allocate a new block
    //of memory with enough space for the original and a null terminal
    uint32 Len = CString::Length(Other);
    char* Ret = new char[Len+1];
    
    //copy the string over
    Memory::Copy<char>(Other, Ret, Len);
    
    //add the null terminal
    Ret[Len+1] = '\0';
    
    //and then return it
    return Ret;
}

char* Cthulhu::CString::DuplicateN(const char* Other, uint32 Limit)
{
    uint32 Len = Min(CString::Length(Other), Limit);

    char* Ret = new char[Len+1];

    Memory::Copy<char>(Other, Ret, Len);

    Ret[Len+1] = '\0';

    return Ret;
}

char* Cthulhu::CString::Copy(const char* From, char* To)
{
    uint32 I = 0;
    
    while(From[I]) { To[I] = From[I]; I++; }
    
    return To;
}

char* Cthulhu::CString::CopyN(const char* From, char* To, uint32 Limit)
{
    uint32 I = 0;

    while(From[I] && Limit) 
    {
        To[I] = From[I];
        Limit--;
    }

    return To;
}

char* Cthulhu::CString::Merge(const char* First, const char* Second)
{
    uint32  FirstLen = CString::Length(First),
            SecondLen = CString::Length(Second);

    uint32 CombinedLen = FirstLen + SecondLen + 1;

    char* Ret = new char[CombinedLen];

    Memory::Copy<char>(First, Ret, FirstLen);
    Memory::Copy<char>(Second, Ret + FirstLen, SecondLen);

    Ret[CombinedLen] = '\0';

    return Ret;
}

char* Cthulhu::CString::Concat(char* Into, const char* From)
{
    const uint32    FirstLen = CString::Length(Into),
                    SecondLen = CString::Length(From);
    

    const uint32 WholeLen = FirstLen + SecondLen + 1;

    char* Ret = new char[WholeLen];

    Memory::Copy<char>(Into, Ret, FirstLen);
    Memory::Copy<char>(From, Ret + FirstLen + 1, SecondLen);

    delete[] Into;

    Into = Ret;

    return Ret;
}

char* Cthulhu::CString::ConcatN(char* Into, const char* From, uint32 Limit)
{
    const uint32 FirstLen = CString::Length(Into),
                 OtherLen = Min<uint32>(CString::Length(From), Limit);

    const uint32 WholeLen = FirstLen + OtherLen + 1;

    char* Ret = new char[WholeLen];

    Memory::Copy<char>(Into, Ret, FirstLen);
    Memory::Copy<char>(From, Ret + FirstLen + 1, OtherLen);

    delete[] Into;

    Into = Ret;

    return Ret;
}

int Cthulhu::CString::Compare(const char* First, const char* Other)
{
    while(*First && (*First == *Other))
    {
        First++;
        Other++;
    }

    return *First - *Other;
}

int Cthulhu::CString::CompareN(const char* First, const char* Second, uint32 Limit)
{
    while(Limit && *First && (*First == *Second))
    {
        First++;
        Second++;
        Limit--;
    }

    if(Limit == 0)
    {
        return 0;
    }

    return *First - *Second;
}

char* Cthulhu::CString::Section(char* Haystack, const char* Needle)
{
    uint32 NeedleLen = CString::Length(Needle);
    
    while(*Haystack)
    {
        if(*Haystack == *Needle)
        {
            if(CString::CompareN(Haystack, Needle, NeedleLen) == 0)
                return Haystack;
        }

        Haystack++;
    }

    return nullptr;
}

uint32 Cthulhu::CString::Length(const char* Content)
{
    uint32 Len = 0;

    while(Content[Len]) { Len++; }

    return Len-1; 
}

#if 0

//TODO remove imports
#include <cstring>
#include <string>

#include "CthulhuString.h"

#include "Array.h"
#include "Optional.h"

#include "Core/Memory/Memory.h"

using Cthulhu::Optional;
using Cthulhu::Array;
using Cthulhu::String;
using Cthulhu::int64;

//TODO document



Cthulhu::String::String()
    : Real(String::Strdup("\0"))
{}

Cthulhu::String::String(const char* Content)
    : Real(String::Strdup(Content))
{}

Cthulhu::String::String(const String& Other)
    : Real(String::Strdup(Other.Real))
{}

Cthulhu::String::String(const String* Other)
    : Real(String::Strdup(Other->Real))
{}

Cthulhu::String& Cthulhu::String::operator=(const String& Other)
{
    delete[] Real;
    
    Real = String::Strdup(Other.Real);
    return *this;
}

Cthulhu::String::~String()
{
    delete[] Real;
}

int Cthulhu::String::Len() const
{
    return String::Strlen(Real);
}

bool Cthulhu::String::IsEmpty() const
{
    return Len() == 0;
}

Cthulhu::String::operator bool() const
{
    return IsEmpty();
}

bool Cthulhu::String::ValidIndex(int Index) const
{
    return 0 <= Index && Index >= Len();
}

bool Cthulhu::String::operator==(const String& Other) const
{
    return String::Strcmp(Real, Other.Real) == 0;
}

bool Cthulhu::String::operator!=(const String& Other) const
{
    return !(String::Strcmp(Real, Other.Real) == 0);
}

Cthulhu::String Cthulhu::String::operator+(const String& Other) const
{
    String Temp(*this);
    Temp.Append(Other);
    return Temp;
}

Cthulhu::String Cthulhu::String::operator+(const char* Str) const
{
    String Temp(*this);
    Temp.Append(Str);
    return Temp;
}

Cthulhu::String Cthulhu::String::operator+(const char C) const
{
    String Temp(*this);
    Temp.Append(C);
    return Temp;
}

Cthulhu::String Cthulhu::String::operator+=(const String& Other)
{
    Append(Other);
    return *this;
}

Cthulhu::String Cthulhu::String::operator+=(const char* Str)
{
    Append(Str);
    return *this;
}

Cthulhu::String Cthulhu::String::operator+=(const char C)
{
    Append(C);
    return *this;
}

Cthulhu::String& Cthulhu::String::operator<<(int64 I)
{
    Append(ToString(I));
    return *this;
}

Cthulhu::String& Cthulhu::String::operator<<(const float F)
{
    Append(ToString(F));
    return *this;
}

Cthulhu::String& Cthulhu::String::operator<<(const bool B)
{
    Append(ToString(B));
    return *this;
}

Cthulhu::String& Cthulhu::String::operator<<(double D)
{
    Append(ToString(D));
    return *this;
}

Cthulhu::String Cthulhu::String::operator/(const String& Other) const
{
    String Temp(*this);
    Temp.Append(String::PathSeperator());
    Temp.Append(Other);
    return Temp;
}

Cthulhu::String& Cthulhu::String::operator/=(const String& Other)
{
    Append(String::PathSeperator());
    Append(Other);
    return *this;
}

char& Cthulhu::String::operator[](int Index)
{
    return Real[Index];
}

const char Cthulhu::String::operator[](int Index) const
{
    return Real[Index];
}

char Cthulhu::String::At(int Index) const
{
    return ValidIndex(Index) ? Real[Index] : '\0';
}

const char* Cthulhu::String::operator*() const
{
    return Real;
}

const char* Cthulhu::String::Raw() const 
{
    return Real;
}

void Cthulhu::String::Append(const String& Other)
{
    char* NewStr = new char[Len() + Other.Len() + 1];
    NewStr[0] = '\0';
    String::Strcat(NewStr, Real);
    String::Strcat(NewStr, Other.Real);
    delete[] Real;
    Real = NewStr;
}

void Cthulhu::String::Append(const char* Str)
{
    char* NewStr = new char[Len() + String::Strlen(Str) + 1];
    NewStr[0] = '\0';
    String::Strcat(NewStr, Real);
    String::Strcat(NewStr, Str);
    delete[] Real;
    Real = NewStr;
}

void Cthulhu::String::Append(const char C)
{
    int Len = Strlen(Real);
    char* Buffer = new char[Len + 2];
    String::Strcpy(Buffer, Real);
    Buffer[Len] = C;
    Buffer[Len + 1] = '\0';
    delete[] Real;
    Real = Buffer;
}

Cthulhu::String Cthulhu::String::Pop(int Length)
{
    int Index = Len() - Length;
    if(ValidIndex(Index))
    {
        char* Ret = new char[Length+1];
        String::Strncpy(Ret, Real + Index, Length);
        String Temp(Ret);
        delete[] Ret;
        Real[Index] = '\0';
        return Temp;
    }
    return String("");
}

void Cthulhu::String::Trim(const String& Pattern)
{
    TrimFront(Pattern);
    TrimBack(Pattern);
}

void Cthulhu::String::TrimFront(const String& Pattern)
{
    while(StartsWith(Pattern))
    {
        Real += Pattern.Len();
    }
}

void Cthulhu::String::TrimBack(const String& Pattern)
{
    while(EndsWith(Pattern))
    {
        Real[Len() - Pattern.Len()] = '\0';
    }
}

Cthulhu::String Cthulhu::String::SubStr(int Start, int End) const
{
    char* Ret = new char[End - Start];
    Memory::Memcpy(Real + Start, Ret, sizeof(char) * Start - End);
    Ret[End] = '\0';
    String Res(Ret);
    delete[] Ret;
    return Res;
}

//for some reason the compiler doesnt like it when i do `using Cthulhu::Map`
//so i guess we're stuck with having to use the namespace
//Cthulhu::String Cthulhu::String::Format(const Cthulhu::Map<String, String> Args) const
//{
//    return *this;
//}

Cthulhu::String Cthulhu::String::Format(const Array<String> Args) const
{
    String Ret = Real;
    for(int I = 0; I < Args.Len(); I++)
    {
        String Search = "{";
        Search << (int64)I;
        Search += "}";

        Ret.Replace(Search, Args[I]);
    }
    
    return Ret;
}

Cthulhu::String Cthulhu::String::Upper() const
{
    String Ret;

    for(int I = 0; I < Len(); I++)
    {
        char C = Real[I];
        if(C >= 'a' && C <= 'z')
            C -= 32;
        Ret.Append(C);
    }
    return Ret;
}

Cthulhu::String Cthulhu::String::Lower() const
{
    String Ret;
    
    for(int I = 0; I < Len(); I++)
    {
        char C = Real[I];
        
        if(C >= 'A' && C <= 'Z')
            C += 32;
        
        Ret.Append(C);
    }
    return Ret;
}

Array<Cthulhu::String> Cthulhu::String::Chunked(int Size) const
{
    Array<String> Arr;
    for(int I = 0; I < Len(); I++)
    {
        if(I % Size == 0) Arr.Append(SubStr(I - Size, I));
    }
    return Arr;
}

Array<Cthulhu::String> Cthulhu::String::Split(const String& Delim) const
{
    Array<String> Arr;
    
    for(int I = 0; I < Len(); I++)
    {
        if(Strcmp(Real + I, Delim.Real)) Arr.Append(SubStr(I, I + Delim.Len()));
    }
    return Arr;
}

Optional<int> Cthulhu::String::Find(const String& Pattern) const
{
    if(Pattern.Len() > Len()) NullOpt<int>();

    for(int I = 0; I < Len(); I++)
    {
        if(Strcmp(Real + I, Pattern.Real)) return Optional<int>(I);
    }

    return NullOpt<int>();
}

bool Cthulhu::String::Has(const String& Pattern) const
{
    return Find(Pattern).Valid();
}

void Cthulhu::String::Replace(const String& Search, const String& Substitute)
{
    int I, Count = 0;
    int SearchLen = Search.Len();
    int SubLen = Substitute.Len();

    for(int I = 0; Real[I] != '\0'; I++)
    {
        if(Strstr(&Real[I], Search.Real) == &Real[I])
        {
            Count++;
            I += SearchLen - 1;
        }
    }

    char* Result = new char[Len() + (Count * (SubLen - SearchLen)) + 1];
    I = 0;

    char* Temp = Real;
    while(*Temp)
    {
        if(Strstr(Temp, Search.Real) == Temp)
        {
            Strcpy(&Result[I], Substitute.Real);
            I += SubLen;
            Temp += SearchLen;
        }
        else
        {
            Result[I++] = *Temp++;
        }
    }
    Result[I] = '\0';
    delete[] Real;
    Real = Result;
}

bool Cthulhu::String::StartsWith(const String& Other) const
{
    //Strncmp returns "difference" between the strings, so 0 means no difference
    return String::Strncmp(Other.Real, Real, Other.Len()) == 0;
}

bool Cthulhu::String::EndsWith(const String& Other) const
{
    int OLen = Other.Len();
    int TLen = Len();
    if(OLen >= TLen)
    {
        return Memory::Memcmp(Other.Real, Real + (OLen - TLen), TLen) == 0;
    }
    return false;
}

Cthulhu::String Cthulhu::String::Map(Lambda<const char(const char)> Transform) const
{
    String Ret;
    
    for(int I = 0; I < Len(); I++)
    {
        Ret.Append(Transform(Real[I]));
    }

    return Ret;
}

Cthulhu::String Cthulhu::String::Filter(Cthulhu::Lambda<bool(const char)> Predicate) const
{
    String Ret;
    
    for(int I = 0; I < Len(); I++)
    {
        if(Predicate(Real[I])) Ret.Append(Real[I]);
    }
    return Ret;
}

Array<char> Cthulhu::String::CharArray() const
{
    char* Chars = Strdup(Real);

    //Array(char*, int);
    //claims the pointer as its own, so instead of giving it Real
    //we copy Real and give it the copy so this string is stll usable
    //Move semantics really are a pain, arent they?
    Array<char> Ret(Chars, Strlen(Chars));

    return Ret;
}

Optional<double> Cthulhu::String::ParseFloat() const
{
    int Flag = 1;
    int Loc, Index = 0;
    double Res = 0;

    char C;
    
    while(Real[Index] == ' ') { Index++; }
    while(Real[Index] == '+' || Real[Index] == '-')
    {
        C = Real[Index];
        if(C == '-')
        {
            Flag *= -1;
        }
        Index++;
    }

    bool Decimal = false;
    while((C = Real[Index++]))
    {
        if(C == '.') 
        {  
            if(Decimal) 
                return NullOpt<double>();
            Loc = Index; 
            Decimal = true; 
            continue; 
        }

        if(C < '0' && '9' < C)
            return NullOpt<double>();
        Res *= 10;
        Res += C - '0';
    }

    Loc = Len() - Loc;

    double Ret = Res;

    for(int I = 0; I < Loc; I++)
    {
        Ret *= 0.1;
    }
    Ret *= Flag;
    return Optional<double>(Ret);
}

Optional<bool> Cthulhu::String::ParseBool() const
{   
    String Temp = Lower();
    if(
        Temp == "true"  ||
        Temp == "yes"   || 
        Temp == "y"     || 
        Temp == "t"
    ) { return Optional<bool>(true); }

    if(
        Temp == "false" ||
        Temp == "no"    ||
        Temp == "n"     ||
        Temp == "f"
    ) { return Optional<bool>(false); }

    return NullOpt<bool>();
}

Optional<int64> Cthulhu::String::ParseInt() const
{
    int64 Ret = 0;
    int Index = 0;
    int Sign = 1;
    char C;
    
    while(Real[Index] == ' ') { Index++; }
    
    while(Real[Index] == '-')
    {
        Index++;
        Sign *= -1;
    }

    while((C = Real[Index++]))
    {
        if(C < '0' || '9' < C)
            return Optional<int64>();
        Ret *= 10;
        Ret += C - '0';
    }
    return Optional<int64>(Ret);
}

Cthulhu::String Cthulhu::String::ToString(bool B)
{
    return B ? "true" : "false";
}

Cthulhu::String Cthulhu::String::ToString(float F)
{       
    return std::to_string(F).c_str();
}           //this seems to be implemented in assembly, so it'll be faster
            //than anything i could do

Cthulhu::String Cthulhu::String::ToString(double D)
{
    return std::to_string(D).c_str();
}

Cthulhu::String Cthulhu::String::ToString(int64 I)
{
    return std::to_string(I).c_str();
}

Cthulhu::String Cthulhu::String::PathSeperator()
{
#if defined(OS_WINDOWS)
    return "\\";
#elif defined(OS_APPLE) || defined(OS_LINUX)
    return "/";
#endif
}

Cthulhu::String Cthulhu::String::Whitespace()
{
    return " \n\r\t\x0b\x0c";
}

Cthulhu::String Cthulhu::String::UpperCase()
{
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

Cthulhu::String Cthulhu::String::LowerCase()
{
    return "abcdefghijklmnopqrstuvwxyz";
}

Cthulhu::String Cthulhu::String::OctDigits()
{
    return "01234567";
}

Cthulhu::String Cthulhu::String::Digits()
{
    return "0123456789";
}

Cthulhu::String Cthulhu::String::HexDigits()
{
    return "0123456789abcdefABCDEF";
}

Cthulhu::String Cthulhu::String::Chars()
{
    return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

char* Cthulhu::String::Strcpy(char* Dest, const char* Source)
{
    return strcpy(Dest, Source);
}

char* Cthulhu::String::Strncpy(char* Dest, const char* Source, int Len)
{
    return strncpy(Dest, Source, Len);
}

char* Cthulhu::String::Strcat(char* Dest, const char* Source)
{
    return strcat(Dest, Source);
}

char* Cthulhu::String::Strncat(char* Dest, const char* Source, int Len)
{
    return strncat(Dest, Source, Len);
}

int Cthulhu::String::Strcmp(const char* First, const char* Second)
{
    return strcmp(First, Second);
}

int Cthulhu::String::Strncmp(const char* First, const char* Second, int Len)
{
    return strncmp(First, Second, Len);
}

const char* Cthulhu::String::Strchr(const char* Source, int Character)
{
    return strchr(Source, Character);
}

char* Cthulhu::String::Strchr(char* Source, int Character)
{
    return strchr(Source, Character);
}

int Cthulhu::String::Strcspn(const char* First, const char* Second)
{
    return strcspn(First, Second);
}

const char* Cthulhu::String::Strpbrk(const char* First, const char* Second)
{
    return strpbrk(First, Second);
}

char* Cthulhu::String::Strpbrk(char* First, const char* Second)
{
    return strpbrk(First, Second);
}

const char* Cthulhu::String::Strrchr(const char* First, int Character)
{
    return strrchr(First, Character);
}

char* Cthulhu::String::Strrchr(char* First, int Character)
{
    return strrchr(First, Character);
}

int Cthulhu::String::Strspn(const char* First, const char* Second)
{
    return strspn(First, Second);
}

const char* Cthulhu::String::Strstr(const char* First, const char* Second)
{
    return strstr(First, Second);
}

char* Cthulhu::String::Strstr(char* First, const char* Second)
{
    return strstr(First, Second);
}

int Cthulhu::String::Strlen(const char* Str)
{
    return strlen(Str);
}

char* Cthulhu::String::Strdup(const char* Str)
{
    int32 Len = Strlen(Str);
    char* Ret = new char[Len + 1];
    Memory::Memcpy(Str, Ret, sizeof(char) * Len + 1);
    return Ret;
}

#endif