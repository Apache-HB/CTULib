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
/*              Cthulhu::String constructors                      */
/*================================================================*/

Cthulhu::String::String()
    : Real(CString::Duplicate(""))
{}

Cthulhu::String::String(char Letter)
    : Real(new char[2]()) // do []() to use the default constructor that zeros the chars
    , Length(1)
{
    Real[0] = Letter;
}

Cthulhu::String::String(const char* Data)
    : Real(CString::Duplicate(Data))
    , Length(CString::Length(Data))
{}

Cthulhu::String::String(const String& Other)
    : Real(CString::Duplicate(Other.Real))
    , Length(Other.Length)
{}

/*================================================================*/
/*              Cthulhu::String destructors                       */
/*================================================================*/

Cthulhu::String::~String()
{
    delete[] Real;
}

/*================================================================*/
/*              Cthulhu::String member functions                  */
/*================================================================*/

U32 Cthulhu::String::Len() const
{
    return Length;
}

bool Cthulhu::String::IsEmpty() const
{
    return Length == 0;
}

void Cthulhu::String::Append(const String& Other)
{
    char* Temp = CString::Merge(Real, Other.Real);

    delete[] Real;

    Real = Temp;

    Length += Other.Length;
}

void Cthulhu::String::Append(char Other)
{
    char* Temp = new char[Length + 2];
    CString::Copy(Real, Temp);

    Temp[Length] = Other;
    Temp[++Length] = '\0';

    delete[] Real;
    Real = Temp;
}

void Cthulhu::String::Push(const String& Other)
{
    char* Temp = CString::Merge(Other.Real, Real);

    delete[] Real;

    Real = Temp;

    Length += Other.Length;
}

void Cthulhu::String::Push(char Other)
{
    char* Temp = new char[Length + 2];

    Temp[0] = Other;

    CString::Copy(Real, Temp+1);

    delete[] Real;
    Real = Temp;

    Length++;
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
    const U32 PatternLen = Pattern.Len();

    if(PatternLen <= Length)
        return Memory::Compare<char>(Pattern.Real, Real + (Length - PatternLen), PatternLen) == 0;

    return false;
}

bool Cthulhu::String::ValidIndex(U32 Index) const
{
    return Index <= Length;
}

char Cthulhu::String::At(U32 Index) const
{
    return ValidIndex(Index) ? Real[Index] : '\0';
}

String Cthulhu::String::SubString(U32 Start, U32 End) const
{
    String Temp = *this;

    Temp.Cut(Start);

    Temp.Drop(Temp.Len() - End);

    return Temp;
}

Option<U32> Cthulhu::String::Find(const String& Pattern) const
{
    if(Pattern.Len() > Length) 
        return None<U32>();

    for(U32 I = 0; I < Length; I++)
        if(CString::Compare(Real + I, Pattern.Real))
            return Some(I);

    return None<U32>();
}

String Cthulhu::String::Upper() const
{
    String Temp(*this);

    for(U32 I = 0; I < Temp.Len(); I++)
        if(Utils::IsLower(Temp[I]))
            Temp[I] -= 32;
    
    return Temp;
}

String Cthulhu::String::Lower() const
{
    String Temp(*this);

    for(U32 I = 0; I < Temp.Len(); I++)
        if(Utils::IsUpper(Temp[I]))
            Temp[I] += 32;
    
    return Temp;
}

String Cthulhu::String::Trim(const String& Pattern)
{
    String Ret = Real;

    while(Ret.StartsWith(Pattern))
        Ret.Cut(Pattern.Len());
    
    while(Ret.EndsWith(Pattern))
        Ret.Drop(Pattern.Len());

    return Ret;
}

String Cthulhu::String::Replace(const String& Search, const String& Substitute) const
{
    U32 Idx = 0,
        Count = 0,
        SearchLen = Search.Len(),
        SubLen = Substitute.Len();

    for(U32 I = 0; Real[I] != '\0'; I++)
    {
        if(CString::Section(Real + I, Search.Real) == Real + I)
        {
            Count++;
            Idx += SearchLen - 1;
        }
    }

    char* Result = new char[Length + (Count * (SubLen - SearchLen)) + 1];
    Idx = 0;

    char* Temp = CString::Duplicate(Real);

    while(*Temp)
    {
        if(CString::Section(Result + Idx, Substitute.Real) == Temp)
        {
            CString::Copy(Result + Idx, Substitute.Real);
            Idx += SubLen;
            Temp += SearchLen;
        }
        else
        {
            Result[Idx++] = *Temp++;
        }
    }

    Result[Idx] = '\0';
    String Ret = Temp;

    delete[] Temp;
    delete[] Result;

    return Ret;

}

String Cthulhu::String::Format(Array<String>& Args) const
{
    String Ret = Real;

    const auto Iter = Args.Iterate().Enumerate();

    for(const auto& I : Iter)
    {
        String Temp = "{";
        Temp << (I64)I.Second;
        Temp += "}";
        Ret = Ret.Replace(Temp, I.First);
    }

    return Ret;
}

String Cthulhu::String::Format(Map<String, String>& Args) const
{
    String Ret = Real;

    const auto Iter = Args.Items().Iterate();

    for(const auto& I : Iter)
    {
        String Temp = "{";
        Temp << (I64)I.Second;
        Temp += "}";
        Ret = Ret.Replace(Temp, I.First);
    }

    return Ret;
}

//cut from front
String& Cthulhu::String::Cut(U32 Amount)
{
    ASSERT(Amount <= Length, "Trying to cut beyond the end of the string");
    Real += Amount;
    Length -= Amount;

    return *this;
}

//drop from back
String& Cthulhu::String::Drop(U32 Amount)
{
    ASSERT(Amount <= Length, "Trying to drop behind the end of the string");
    Real[Length - Amount] = '\0';
    Length -= Amount;

    return *this;
}

bool Cthulhu::String::Has(const String& Pattern) const
{
    return Find(Pattern).Valid();
}

bool Cthulhu::String::Has(char Item) const
{
    for(U32 I = 0; I < Length; I++)
    {
        if(Real[I] == Item)
            return true;
    }
    
    return false;
}

Iterator<Array<char>, char> Cthulhu::String::Iterate() const
{
    Array Ret(CString::Duplicate(Real), Length);

    return Ret.Iterate();
}

String Cthulhu::String::Reversed() const
{
    char* Temp = CString::Reverse(Real);

    String Ret(Temp);

    delete[] Temp;

    return Ret;
}

/*================================================================*/
/*              Cthulhu::String operator overloads                */
/*================================================================*/

String& Cthulhu::String::operator=(const String& Other)
{
    delete[] Real;
    Real = CString::Duplicate(Other.Real);
    Length = Other.Length;

    return *this;
}

char& Cthulhu::String::operator[](U32 Index) const
{
    ASSERT(ValidIndex(Index), "Trying to access string out of range with operator[]");
    return Real[Index];
}

char* Cthulhu::String::operator*() const
{
    return Real;
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
    String Ret(Real);

    Ret.Append(Other);

    return Ret;
}

String Cthulhu::String::operator+(char Other) const
{
    String Ret(Real);

    Ret.Append(Other);

    return Ret;
}

String& Cthulhu::String::operator<<(I64 Num)
{
    Append(Utils::ToString(Num));

    return *this;
}

String& Cthulhu::String::operator<<(float Num)
{
    Append(Utils::ToString(Num));

    return *this;
}

String& Cthulhu::String::operator<<(bool Val)
{
    Append(Utils::ToString(Val));

    return *this;
}

/*================================================================*/
/*              Cthulhu::CString functions                        */
/*================================================================*/

char* Cthulhu::CString::Duplicate(const char* Data)
{
    const U32 Len = Length(Data);

    char* Ret = new char[Len+1];
    Ret[Len] = '\0';

    Copy(Data, Ret);

    return Ret;
}

char* Cthulhu::CString::Duplicate(const char* Data, U32 Limit)
{
    const U32 Len = Math::Min(Length(Data), Limit) + 1;

    char* Ret = new char[Len];

    Copy(Data, Ret, Limit);
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
    for(U32 I = 0; From[I] && Limit; I++, Limit--)
    {
        Into[I] = From[I];
    }

    return Into;
}

char* Cthulhu::CString::Merge(const char* Left, const char* Right)
{
    const U32 LeftLen = Length(Left),
              RightLen = Length(Right),
              TotalLen = RightLen + LeftLen;

    char* Ret = new char[TotalLen+1];

    Memory::Copy(Left, Ret, LeftLen);
    Memory::Copy(Right, Ret + LeftLen, RightLen);

    Ret[TotalLen] = '\0';

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

I32 Cthulhu::CString::Compare(const char* Left, const char* Right)
{
    while(*Left && (*Left == *Right))
    {
        Left++;
        Right++;
    }

    return *Left - *Right;
}

I32 Cthulhu::CString::Compare(const char* Left, const char* Right, U32 Limit)
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

//strstr
char* Cthulhu::CString::Section(char* Haystack, char* Needle)
{
    return strstr(Haystack, Needle);

    // const I32 Len = Length(Needle);
    // char* Ref = Haystack;

    // while(*Haystack && *Ref)
    // {
    //     if(*Haystack++ == *Ref)
    //         Ref++;
    //     if(!*Ref)
    //         return Haystack - Len;
    //     if(Len == (Ref - Needle))
    //         Ref = Needle;
    // }

    // return nullptr;
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
    const U32 Len = Length(Content);

    char* Ret = new char[Len+1];

    U32 Index = 0;

    for(int I = Len - 1; I >= 0; I--)
    {
        Ret[Index++] = Content[I];
    }
    
    Ret[Len] = '\0';

    return Ret;
}

/*================================================================*/
/*              Cthulhu::Utils string functions                   */
/*================================================================*/

String Cthulhu::Utils::Padding(const String& Text, U32 Repeat)
{
    String Ret;

    for(U32 I = 0; I < Repeat; I++)
        Ret += Text;
    
    return Ret;
}

Option<I64> Cthulhu::Utils::ParseInt(const String& Text)
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

Option<float> Cthulhu::Utils::ParseFloat(const String& Text)
{
    char* Real = *Text;

    int Flag = 1,
        Loc = 0,
        Index = 0;
    
    float Res = 0;

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
                return None<float>();
            
            Loc = Index;
            Decimal = true;
            continue;
        }

        if(C < '0' && '9' < C)
            return None<float>();

        Res *= 10;
        Res += C - '0';
    }

    Loc = Text.Len() - Loc;

    float Ret = Res;
    
    //shift the decimal place to the corrent location
    for(int I = 0; I < Loc; I++)
    {
        Ret *= 0.1;
    }
    
    Ret *= Flag;

    return Some(Ret);
}

Option<bool> Cthulhu::Utils::ParseBool(const String& Text)
{
    String Temp = Text.Lower();
    
    if(Temp == "true" || Temp == "yes" || Temp == "y" || Temp == "t")
        return Some(true);

    if(Temp == "false" || Temp == "no" || Temp == "n" || Temp == "f")
        return Some(false);

    return None<bool>();
}

String Cthulhu::Utils::ToString(I64 Num)
{
    String Ret;

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

    String Temp(Ret.Reversed());

    if(Negative)
        Temp.Push('-');

    return Temp;
}

String Cthulhu::Utils::ToString(float Num)
{
    //TODO: implement dragon4 at some point
}

String Cthulhu::Utils::ToString(bool Val)
{
    return Val ? "true" : "false";
}

namespace
{

char HexChar(I64 Num)
{
    Num &= 15;
    return Num > 10 ? Num + 48 : Num + 55;
}

} // namespace

String Cthulhu::Utils::HexToString(I64 HexNum)
{
    char* Temp = new char[8];
    
    for(U32 I = 0; I < 8; I++)
    {
        Temp[7 - I] = HexChar(HexNum);
        HexNum >>= 4;
    }
    
    String Ret = Temp;

    delete[] Temp;

    return Ret;
}

String Cthulhu::Utils::FastToString(float Num)
{
    Num *= 100;
    String Ret = Utils::ToString((I64)Num);

    String Temp = Ret.SubString(Ret.Len() - 2, Ret.Len());

    Ret.Drop(2);
    Ret += '.';
    Ret += Temp;

    return Ret;
}

bool Cthulhu::Utils::IsSpace(char C)
{
    return Consts::Whitespace()->Has(C);
}

bool Cthulhu::Utils::IsUpper(char C)
{
    return Consts::UpperCase()->Has(C);
}

bool Cthulhu::Utils::IsLower(char C)
{
    return Consts::LowerCase()->Has(C);
}

/*================================================================*/
/*              Cthulhu::Consts string functions                  */
/*================================================================*/

namespace
{

const String PathSeperatorString = 
#ifdef OS_WINDOWS
    "\\"
#else
    "/"
#endif
;

const String WhitespaceString = " \n\r\t\x0b\x0c";
const String UpperCaseString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const String LowerCaseString = "abcdefghijklmnopqrstuvwxyz";
const String OctDigitsString = "01234567";
const String HexDigitsString = "0123456789abcdefABCDEF";
const String DigitsString = "0123456789";
const String CharsString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const String PunctionationString = "!\"#$%%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
const String PrintableString = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c";

}

const String* Cthulhu::Consts::PathSeperator()
{
    return &PathSeperatorString;
}

const String* Cthulhu::Consts::Whitespace()
{
    return &WhitespaceString;
}

const String* Cthulhu::Consts::UpperCase()
{
    return &UpperCaseString;
}

const String* Cthulhu::Consts::LowerCase()
{
    return &LowerCaseString;
}

const String* Cthulhu::Consts::OctDigits()
{
    return &OctDigitsString;
}

const String* Cthulhu::Consts::HexDigits()
{
    return &HexDigitsString;
}

const String* Cthulhu::Consts::Digits()
{
    return &DigitsString;
}

const String* Cthulhu::Consts::Chars()
{
    return &CharsString;
}

const String* Cthulhu::Consts::Punctuation()
{
    return &PunctionationString;
}

const String* Cthulhu::Consts::Printable()
{
    return &PrintableString;
}
