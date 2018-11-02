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

#include "Map.h"
//Map<T, K> Array<T> Option<T> Iterator<TC, T> Memory::* 

#include "Core/Math/Math.h"
//Math::Min Math::Max

#include "CthulhuString.h"

using namespace Cthulhu;
using namespace Cthulhu::Math;

/*================================================================*/
/*              Cthulhu::String Member functions                  */
/*================================================================*/

Cthulhu::String::String(const char* Data)
    : Real(CString::Duplicate(Data))
{}

Cthulhu::String::String(const String& Other)
    : Real(CString::Duplicate(Other.Real))
{}

String& Cthulhu::String::operator=(const String& Other)
{
    delete[] Real;
    Real = CString::Duplicate(Other.Real);
    
    return *this;
}

U32 Cthulhu::String::Len() const
{
    return CString::Length(Real);
}

bool Cthulhu::String::IsEmpty() const
{
    return Real[0] == '\0';
}

Cthulhu::String::operator bool() const
{
    return IsEmpty();
}

bool Cthulhu::String::operator==(const String& Other) const
{
    return CString::Compare(Real, Other.Real) == 0;
}

bool Cthulhu::String::operator!=(const String& Other) const
{
    return CString::Compare(Real, Other.Real) != 0;
}

String& Cthulhu::String::operator+=(const String& Other)
{
    Append(Other);
    return *this;    
}

String& Cthulhu::String::operator+=(char Other)
{
    Append(Other);
    return *this;
}


String Cthulhu::String::operator+(const String& Other) const
{
    String Temp = *this;

    Temp += Other;

    return Temp;
}

String Cthulhu::String::operator+(char Other) const
{
    String Temp = *this;

    Temp += Other;

    return Temp;
}


String& Cthulhu::String::operator<<(I64 Num)
{
    Append(StringUtils::ToString(Num));

    return *this;
}

String& Cthulhu::String::operator<<(double Num)
{
    Append(StringUtils::ToString(Num));

    return *this;
}

String& Cthulhu::String::operator<<(bool Val)
{
    Append(StringUtils::ToString(Val));

    return *this;
}


void Cthulhu::String::Append(const String& Other)
{
    char* Temp = CString::Merge(Real, Other.Real);

    delete[] Real;

    Real = Temp;
}

void Cthulhu::String::Append(char Other)
{
    const U32 ThisLen = Len();

    char* Ret = new char[ThisLen + 2];
    CString::Copy(Real, Ret);

    Ret[ThisLen] = Other;
    Ret[ThisLen+1] = '\0';

    delete[] Real;
    Real = Ret;
}

void Cthulhu::String::Push(const String& Other)
{
    char* Temp = CString::Merge(Other.Real, Real);

    delete[] Real;

    Real = Temp;
}

void Cthulhu::String::Push(char Other)
{
    const U32 Length = Len();
    char* Temp = new char[Length+2];

    Temp[0] = Other;

    CString::Copy(Real, Temp+1);

    delete[] Real;
    Real = Temp;
}


char* Cthulhu::String::operator*() const
{
    return Real;
}

char* Cthulhu::String::CStr() const
{
    return Real;
}


bool Cthulhu::String::StartsWith(const String& Pattern) const
{
    return CString::Compare(Real, *Pattern, Pattern.Len()) == 0;
}

bool Cthulhu::String::EndsWith(const String& Pattern) const
{
    const U32 PatternLen = Pattern.Len(),
                 ThisLen = Len();

    if(PatternLen >= ThisLen)
        return Memory::Compare<char>(Pattern.Real, Real + (PatternLen - ThisLen), ThisLen);
    
    return false;
}


bool Cthulhu::String::ValidIndex(U32 Index) const
{
    return 0 <= Index && Index <= CString::Length(Real);
}


char& Cthulhu::String::operator[](U32 Index) const
{
    ASSERT(ValidIndex(Index), "Trying to access string at invalid index");
    return Real[Index];
}

char Cthulhu::String::At(U32 Index) const
{
    return (ValidIndex(Index)) ? Real[Index] : '\0';
}


String Cthulhu::String::SubString(U32 Start, U32 End) const
{
    char* Temp = CString::Duplicate(Real, End);
    Temp[Start] = '\0';

    String Ret = Temp;
    delete[] Temp;

    return Ret;
}


Option<U32> Cthulhu::String::Find(const String& Pattern) const
{
    const U32 ThisLen = Len();

    if(Pattern.Len() > ThisLen) return None<U32>();
    
    for(U32 I = 0; I < ThisLen; I++)
    {
        if(CString::Compare(Real + I, Pattern.Real)) 
            return Some(I);
    }
    
    return None<U32>();
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


void Cthulhu::String::Trim(const String& Pattern)
{
    const U32 PatternLen = Pattern.Len();

    while(StartsWith(Pattern)) 
        Cut(PatternLen);

    while(EndsWith(Pattern)) 
        Drop(PatternLen);
}

String Cthulhu::String::Replace(const String& Search, const String& Substitute) const
{
    U32  I = 0, 
         Count = 0,
         SearchLen = Search.Len(),
         SubLen = Substitute.Len();
    
    for(U32 I = 0; Real[I] != '\0'; I++)
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
    #warning NO_IMPL
    NO_IMPL();
    
    // String Ret = Real;

    // auto Iter = Args.Iterate().Enumerate();

    // for(const auto& I : Iter)
    // {
    //     String Temp = "{";
    //     Temp << (I64)I.Second;
    //     Temp += "}";
    //     Ret = Ret.Replace(Temp, I.First);
    // }
    
    // return Ret;
}

String Cthulhu::String::Format(const Map<String, String>& Args) const
{
    #warning NO_IMPL
    NO_IMPL();
    
    // String Ret = Real;

    // auto Iter = Args.Items().Iterate();

    // for(const auto& I : Iter)
    // {
    //     String Temp = "{";
    //     Temp += *I.First;
    //     Temp += "}";
    //     Ret = Ret.Replace(Temp, *I.Second);
    // }

    // return Ret;
}


void Cthulhu::String::Cut(U32 Amount)
{
    ASSERT(Amount < Len(), "Trying to cut off more string that can be cut off");
    Real += Amount;
}

void Cthulhu::String::Drop(U32 Amount)
{
    ASSERT(Amount < Len(), "Trying to drop off more string than there is");
    Real[Len() - Amount] = '\0';
}


bool Cthulhu::String::Has(const String& Pattern) const
{
    return Find(Pattern).Valid();
}


Iterator<Array<char>, char> Cthulhu::String::Iterate() const
{
    #warning NO_IMPL
    NO_IMPL();
    //char* Str = CString::Duplicate(Real);

    //Array<char> Ret(Str, Len());

    //return Iterator<Array<char>, char>(Ret);
}


String Cthulhu::String::Reversed() const
{
    char* Rev = CString::Reverse(Real);

    String Ret = Rev;

    delete[] Rev;

    return Ret;
}


Cthulhu::String::~String()
{
    delete[] Real;
}


/*================================================================*/
/*                Cthulhu::CString Functions                      */
/*================================================================*/

char* Cthulhu::CString::Duplicate(const char* Data)
{
    const U32 Len = CString::Length(Data) + 1;

    char* Ret = new char[Len];
    Ret[Len-1] = '\0';

    CString::Copy(Data, Ret);

    return Ret;
}

char* Cthulhu::CString::Duplicate(const char* Data, U32 Limit)
{
    const U32 Len = Math::Min(CString::Length(Data), Limit) + 1;

    char* Ret = new char[Len];

    CString::Copy(Data, Ret, Limit);
    Ret[Len] = '\0';

    return Ret;
}

char* Cthulhu::CString::Copy(const char* From, char* Into)
{
    U32 I = 0;

    while(From[I]) { Into[I] = From[I]; I++; }

    Into[I] = '\0';

    return Into;
}

char* Cthulhu::CString::Copy(const char* From, char* Into, U32 Limit)
{
    U32 I = 0;

    while(From[I] && Limit)
    {
        Into[I] = From[I];
        Limit--;
        I++;
    }

    return Into;
}

char* Cthulhu::CString::Merge(const char* Left, const char* Right)
{
    const U32 LeftLen = CString::Length(Left),
                 RightLen = CString::Length(Right),
                 TotalLen = RightLen + LeftLen + 1;
    
    char* Ret = new char[TotalLen];

    Memory::Copy(Left, Ret, LeftLen);
    Memory::Copy(Right, Ret + LeftLen, RightLen);

    Ret[TotalLen-1] = '\0';

    return Ret;
}

char* Cthulhu::CString::Concat(const char* From, char* Into)
{
    while(*From)
    {
        *Into++ = *From++;
    }

    return Into;
}

char* Cthulhu::CString::Concat(const char* From, char* Into, U32 Limit)
{
    while(*From && Limit)
    {
        *Into++ = *From++;
        Limit--;
    }

    return Into;
}

int Cthulhu::CString::Compare(const char* Left, const char* Right)
{
    while(*Left && (*Left == *Right))
    {
        Left++;
        Right++;
    }

    return *Left - *Right;
}

int Cthulhu::CString::Compare(const char* Left, const char* Right, U32 Limit)
{
    while(Limit && *Left && (*Left == *Right))
    {
        Left++;
        Right++;
        Limit--;
    }

    if(Limit == 0)
    {
        return 0;
    }

    return *Left - *Right;
}

char* Cthulhu::CString::Section(const char* Needle, char* Haystack)
{
    U32 NeedleLen = CString::Length(Needle);
    
    while(*Haystack)
    {
        if(*Haystack == *Needle)
        {
            if(CString::Compare(Haystack, Needle, NeedleLen) == 0)
                return (char*)Needle;
        }

        Haystack++;
    }

    return nullptr;
}

U32 Cthulhu::CString::Length(const char* Content)
{
    U32 Len = 0;

    while(Content[Len])
        Len++;

    return Len;
}

char* Cthulhu::CString::Reverse(const char* Content)
{
    const U32 Len = CString::Length(Content);

    char* Ret = new char[Len+1];
    U32 Index = 0;

    for(int I = Len - 1; I >= 0; I--)
        Ret[Index++] = Content[I];

    Ret[Index] = '\0';

    return Ret;
}

/*================================================================*/
/*                Cthulhu::StringUtils Functions                  */
/*================================================================*/

String Cthulhu::StringUtils::Padding(const String& Text, U32 Repeat)
{
    String Ret;

    while(Repeat--)
    {
        Ret += Text;
    }

    return Ret;
}

Option<I64> Cthulhu::StringUtils::ParseInt(const String& Text)
{
    char* Real = *Text;
    I64 Ret = 0;
    
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
            return None<I64>();

        Ret *= 10;
        Ret += C - '0';
    }

    return Some(Ret * Sign);
}

Option<double> Cthulhu::StringUtils::ParseDouble(const String& Text)
{
    char* Real = *Text;

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

    Loc = Text.Len() - Loc;

    double Ret = Res;
    
    //shift the decimal place to the corrent location
    for(int I = 0; I < Loc; I++)
    {
        Ret *= 0.1;
    }
    
    Ret *= Flag;

    return Some(Ret);
}

Option<bool> Cthulhu::StringUtils::ParseBool(const String& Text)
{
    String Temp = Text.Lower();
    
    if(Temp == "true" || Temp == "yes" || Temp == "y" || Temp == "t")
        return Some(true);

    if(Temp == "false" || Temp == "no" || Temp == "n" || Temp == "f")
        return Some(false);

    return None<bool>();
}

String Cthulhu::StringUtils::ToString(I64 Num)
{
    String Ret = "";

    bool Negative = false;

    if(Num < 0)
    {
        Num = -Num;
        Negative = true;
    }

    while(Num != 0)
    {
        I64 Rem = Num % 10;
        Ret += Rem + '0';
        Num /= 10;
    }

    Ret = Ret.Reversed();

    if(Negative)
        Ret.Push('-');

    return Ret;
}

String Cthulhu::StringUtils::ToString(double Num)
{
    #warning NO_IMPL
    NO_IMPL();
}

String Cthulhu::StringUtils::ToString(bool Val)
{
    return Val ? "true" : "false";
}

/*================================================================*/
/*                Cthulhu::StringConstants Functions              */
/*================================================================*/

namespace
{

static const String PathSeperatorString = 
#ifdef OS_WINDOWS
    "\\";
#else
    "/";
#endif

static const String WhitespaceString = " \n\r\t\x0b\x0c";
static const String UpperCaseString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const String LowerCaseString = "abcdefghijklmnopqrstuvwxyz";
static const String OctDigitsString = "01234567";
static const String HexDigitsString = "0123456789abcdefABCDEF";
static const String DigitsString = "0123456789";
static const String CharsString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const String PunctionationString = "!\"#$%%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
static const String PrintableString = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c";

}

const String& Cthulhu::StringConstants::PathSeperator()
{
    return PathSeperatorString;
}

const String& Cthulhu::StringConstants::Whitespace()
{
    return WhitespaceString;
}

const String& Cthulhu::StringConstants::UpperCase()
{
    return UpperCaseString;
}

const String& Cthulhu::StringConstants::LowerCase()
{
    return LowerCaseString;
}

const String& Cthulhu::StringConstants::OctDigits()
{
    return OctDigitsString;
}

const String& Cthulhu::StringConstants::HexDigits()
{
    return HexDigitsString;
}

const String& Cthulhu::StringConstants::Digits()
{
    return DigitsString;
}

const String& Cthulhu::StringConstants::Chars()
{
    return CharsString;
}

const String& Cthulhu::StringConstants::Punctuation()
{
    return PunctionationString;
}

const String& Cthulhu::StringConstants::Printable()
{
    return PrintableString;
}

