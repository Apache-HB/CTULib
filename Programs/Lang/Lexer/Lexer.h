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

#include <FileSystem/BufferedFile.h>
#include <Core/Memory/Buffer.h>

namespace FS = Cthulhu::FileSystem;

#pragma once

namespace Cthulhu::Lang
{

enum class KW
{
#define KW(A, _) A,
#define OP(A, _) A,
#   include "Keywords.inc"
#undef KW
#undef OP
};

struct Lexeme
{
    U64 Line;
    U16 Column;
    
    const String* FileName;

    enum class Type
    {
        Float,
        Int,
        Bool,
        Str,
        Ident,
        Keyword,
        End
    };

    Type LexType;

    union
    {
        KW Keyword;
        I64 Num;
        bool Val;
        F64 Float;
        String* Str;
    };
};

struct Lexer
{
    Lexer(FS::BufferedFile InFile, const String& InFileName);
    Lexer(const String& InFileName);

    Lexeme Next();
    Lexeme Peek1() const;
    Lexeme Peek2() const;

    bool Valid() const { return File.Valid(); }

private:

    Lexeme GetNextLexeme();

    char NChar();

    U64 Distance = 0;
    U64 Line = 0;
    U16 Column = 0;

    FS::BufferedFile File;
    Buffer<char, 256> Buf;
    String FileName;

    Lexeme NextLex0, NextLex1, NextLex2;
    bool ReachedEOF = false;
};

}