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

#include "Meta/Assert.h"
#include "Lexer.h"
#include "Core/Collections/Option.h"
#include "../Utils/Error.h"

using namespace Cthulhu;
using namespace Cthulhu::Lang;

using LType = Lexeme::Type;

Lexer::Lexer(FS::BufferedFile InFile, const String& InFileName)
    : File(InFile)
    , FileName(InFileName)
{
    NextLex0 = GetNextLexeme();
    NextLex1 = GetNextLexeme();
    NextLex2 = GetNextLexeme();
}

Lexer::Lexer(const String& InFileName)
    : File(InFileName)
    , FileName(InFileName)
{
    NextLex0 = GetNextLexeme();
    NextLex1 = GetNextLexeme();
    NextLex2 = GetNextLexeme();
}

Lexeme Lexer::Next()
{

}

Lexeme Lexer::Peek1() const
{

}

Lexeme Lexer::Peek2() const
{

}

char Lexer::NChar()
{
    char R = File.Next();
    Distance++;
    if(Utils::IsNewline(R))
    {
        Column = 0;
        Line++;
    }
    else
    {
        Column++;
    }

    return R;
}

Lexeme Lexer::GetNextLexeme()
{
    char C = NChar();

    //if C is / then it might be the start of a comment
    if(C == '/')
    {
        char P = File.Peek();
        //if the next char is a / then its a single line comment
        if(P == '/')
        {
            C = NChar();
            while(!Utils::IsNewline(C))
                C = NChar();
        }
        //if the next char is a * then its a block comment
        else if(P == '*')
        {
            C = NChar();
            
            U8 Depth = 1; 
            while(Depth <= 0)
            {
                if(C == '/' && File.Peek() == '*')
                    Depth++;
                else if(C == '*' && File.Peek() == '/')
                    Depth--;
                C = NChar();
            }
        }
        //if the next char is an = then its a /= operator
        else if(C == '=')
        {
            NChar();

            Lexeme Ret;
            Ret.Line = Line-2;
            Ret.Column = Column-2;
            Ret.LexType = LType::Keyword;
            Ret.Keyword = KW::DivEq;

            return Ret;
        }
        //otherwise its just a / operator
        else
        {
            Lexeme Ret;
            Ret.Line = Line-1;
            Ret.Column = Column-1;
            Ret.LexType = LType::Keyword;
            Ret.Keyword = KW::Div;

            return Ret;
        }

        return GetNextLexeme();
    }

    //If its the end of the file then return an eof lexeme
    if(Utils::IsEOF(C) || ReachedEOF)
    {
        ReachedEOF = true;
        
        Lexeme Ret;
        Ret.LexType = LType::End;
        
        return Ret;
    }

    //skip all the spaces as those arent needed
    while(Utils::IsSpace(C))
        C = NChar();

    Buf.Wipe();
    //if its a character it could be a keyword or an identifier
    if(Utils::IsAlpha(C))
    {
        Buf.Push(C);
        C = NChar();

        while(Utils::IsAlnum(C) || C == '_')
        {
            Buf.Push(C);
            C = NChar();
        }

        Buf.Push('\0');
    }
    //if its a number then its an integer or a float
    else if(Utils::IsNum(C))
    {
        Buf.Push(C);
        C = NChar();

        bool IsFloat = false;
        while(Utils::IsAlnum(C) || C == '.')
        {
            Buf.Push(C);
            if(C == '.')
                IsFloat = true;
        }

        Buf.Push('\0');
        if(IsFloat)
        {
            Option<F32> Ret = Utils::ParseFloat(*Buf);

            if(Ret.Valid())
            {

            }

            Err::Error(
                "Invalid floating point number", 
                { &File, &FileName, Line, Distance, Column - CString::Length(*Buf)}, 
                Err::Level::Fatal
            );
        }
        else
        {
            Option<I64> Num = Utils::ParseInt(*Buf);
        }
    }
    //if its a quote then it must be a string
    else if(C == '\'' || C == '"') 
    {

    }
    //otherwise its a special character, so must be an operator
    else
    {

    }
}
