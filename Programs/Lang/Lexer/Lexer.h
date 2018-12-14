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

#include "Utils/FastFile/FastFile.h"

#pragma once

namespace Cthulhu::Lang
{

#define KW(V, _) V,
#define OP(V, _) V,

enum class Keyword : U8
{
#include "Keywords.inc"
};

#undef KW
#undef OP

struct Token
{
    enum class Type : U8
    {
        Ident,
        String, 
        FString,
        Int,
        Float,
        Key,
        End,
    };

    U64 Line;
    U64 Depth;
    
    Type TokType;

    Token(){}

    Token(Type InType)
        : TokType(InType)
    {}

    Token(U64 L, U64 D, Type InType)
        : Line(L)
        , Depth(D)
        , TokType(InType)
    {}

    union
    {
        String* Str;
        I64 Int;
        float Float;
        Keyword Key;
    };

    ~Token()
    {
        if( TokType == Type::String || 
            TokType == Type::FString || 
            TokType == Type::Ident)
            delete Str;
    }
};

struct Lexer
{
    Lexer(FastFile InFile)
        : File(InFile)
        , Distance(0)
        , Line(0)
        , Depth(0)
    {
        Current = GetNext();
        Look1 = GetNext();
        Look2 = GetNext();
    }

    Token Next();
    Token Peek() const;
    Token Peek2() const;
    Token Peek3() const;

private:
    char NextChar();

    Keyword KeywordType() const;
    Keyword OperatorType() const;
    
    I64 ParseHex() const;
    I64 ParseBits() const;
    I64 ParseInt() const;

    double ParseFloat() const;

    Token ParseString();
    Token ParseIdent();
    Token ParseNumber();
    Token ParseKeyword();

    Token GetNext();
    //2 token lookahead
    Token Current, Look1, Look2;

    U64 Distance;
    U64 Line;
    U16 Depth;

    mutable Buffer<char, 512> Buf;

    FastFile File;
};

}


/*

#include <Meta/Aliases.h>
#include <Core/Collections/CthulhuString.h>
#include <Core/Memory/Buffer.h>
#include <Core/Collections/Array.h>
#include <Core/Collections/Map.h>

#include "../Utils/FastFile/FastFile.h"

#pragma once

namespace Cthulhu::Lang
{

#define KW(V, _) V,
#define OP(V, _) V,

enum class Keyword : U8
{
    None,
#   include "Keywords.inc"
};

#undef KW
#undef OP

enum class LexType : U8
{
    Ident,
    Keyword,
    Float,
    Int,
    String,
    FString,
    End,
};

struct FString
{
    String Template;
    Array<String> Args;
};

struct Lexeme
{
    U64 Line;
    U16 Distance;

    LexType Type;

    union
    {
        String* Ident;
        FString* Format;
        Keyword Key;
        float F;
        I64 Num;
    };


    Lexeme() : Type(LexType::Int) {}
    Lexeme(LexType LType);
    ~Lexeme();
};

namespace Consts
{
    constexpr char FormatPrefix = 'f';
}

struct Lexer
{
    Lexeme Next();
    Lexeme Peek() const;
    Lexeme Peek2() const;
    Lexeme Peek3() const;

    Lexer(FastFile InFile);

    U64 CurrentLine() const { return Line; }
    U16 CurrentDistance() const { return Distance; }
    U64 GetRealDistance() const { return RealDistance; }

private:
    void ParseHexString(char C);
    void ParseEscapedChar(char C);

    Lexeme LexNext();
    void ParseOperator();
    static Keyword IsOperator(Buffer<char, 512>* Buf);
    static Keyword IsKeyword(Buffer<char, 512>* Buf);

    Lexeme ParseFString();

    Lexeme ParseNum(Buffer<char, 512>* NumBuf, char& C);

    Lexeme CurrentLex;
    Lexeme NextLex;
    Lexeme Next2Lex;

    U64 Line;
    U16 Distance;
    U64 RealDistance;
    FastFile File;

    Buffer<char, 512> Buf;

    bool FoundEOF = false;
};

}*/