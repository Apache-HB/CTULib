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

#include "Core/Collections/CthulhuString.h"

#pragma once

namespace Summon
{

enum class Token : char
{
    None = '\0',
    SquareOpen = '[',
    SquareClose = ']',
    Comma = ',',
    Equals = '='
};

struct Lexeme
{
    Cthulhu::uint64 Line;
    Cthulhu::uint64 Loc;
    Token Tok;
    Cthulhu::String& Identifier;
};

class Lexer
{
    const Cthulhu::String Content;

    Cthulhu::uint64 Distance;
    Cthulhu::uint64 Line;
    Cthulhu::uint64 Loc;

    bool EOF;

protected:
    void SkipWhitespace();

public:
    Lexer(const Cthulhu::String& Path);

    const Lexeme Next();
};

}