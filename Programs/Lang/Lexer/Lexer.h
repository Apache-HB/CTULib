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

#include <Meta/Aliases.h>
#include <Core/Collections/CthulhuString.h>
#include "../Utils/FastFile/FastFile.h"

#pragma once

namespace Cthulhu::Lang
{

struct Lexeme
{
    U64 Line;
    U16 Distance;

    String Ident;

    union
    {
        float F;
        I64 Num;
    };
};

struct Lexer
{
    Lexeme Next();
    Lexeme Peek() const;
    Lexeme Peek2() const;

    Lexer(FastFile InFile);

    U64 CurrentLine() const;
    U16 CurrentDistance() const;
    U64 GetRealDistance() const;

private:
    Lexeme Current;
    Lexeme Next;
    Lexeme Next2;

    U64 Line;
    U16 Distance;
    U64 RealDistance;
    FastFile File;
};

}