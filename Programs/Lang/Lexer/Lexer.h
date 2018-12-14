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

struct Lexer
{
    

    
    U64 Distance;


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