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

#include "FileSystem/FileSystem.h"

#include "Lex.h"

namespace FS = Cthulhu::FileSystem;

using Cthulhu::String;

Summon::Lexer::Lexer(const Cthulhu::String& Path)
    : Content(FS::Read(Path))
    , Distance(0)
    , Line(0)
    , Loc(0)
    , EOF(false)
{}

void Summon::Lexer::SkipWhitespace()
{
    while(String::Whitespace().Has(Content[(int)Distance]))
    {
        if(Content[(int)Distance] == '\0')
        {
            EOF = true;
        }
        Distance++;
    }
}

const Summon::Lexeme Summon::Lexer::Next()
{
    
}