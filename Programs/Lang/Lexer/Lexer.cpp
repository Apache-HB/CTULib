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

#include <stdio.h>

#include <Core/Collections/Option.h>

#include "Lexer.h"

using namespace Cthulhu;
using namespace Cthulhu::Lang;

Lexeme::Lexeme(LexType LType)
    : Type(LType)
{}

Lexeme::~Lexeme()
{
    if(Type == LexType::String)
        delete Ident;
}

Lexer::Lexer(FastFile InFile)
    : Line(0)
    , Distance(0)
    , RealDistance(0)
    , File(InFile)
{
    CurrentLex = LexNext();
    NextLex = LexNext();
    Next2Lex = LexNext();
}

namespace 
{

bool ValidHex(char C)
{
    return C >= '0' && C <= 'F';
}

}

Lexeme Lexer::ParseNum(Buffer<char, 512>* NumBuf, char& C)
{
    bool IsFloat = C == '.';

    while(true)
    {
        C = File.Next();
        
        if(C == '.')
        {
            if(IsFloat)
            {
                //more than one error in a number, error
            }
            IsFloat = true;
            NumBuf->Push('.');
            C = File.Next();
        }
        
        if(Utils::IsNum(C))
        {
            NumBuf->Push(C);
        }
        else
        {
            break;
        }
    }

    NumBuf->Push('\0');

    if(IsFloat)
    {
        auto Num = Utils::ParseFloat(NumBuf->Data());
        return Num.Fold<Lexeme>([](float Num){
            auto Ret = Lexeme(LexType::Float);
            Ret.F = Num;

            printf("Float = %f\n", Num);

            return Ret;
        }, []{
            printf("Float = Bad\n");

            return Lexeme(LexType::End);
        });
    }
    else
    {
        auto Num = Utils::ParseInt(NumBuf->Data());

        return Num.Fold<Lexeme>([](I64 Num){
            auto Ret = Lexeme(LexType::Int);
            Ret.Num = Num;

            printf("Int = %lld\n", Num);

            return Ret;
        }, []{
            printf("Int = Bad\n");
            return Lexeme(LexType::End);
        });
    }
}

Keyword Lexer::IsOperator(Buffer<char, 512>* Buf)
{
    Buf->Push('\0');

    printf("OpBuf = %s\n", Buf->Data());

#define KW(...)

#define OP(O, S) if(CString::Compare(Buf->Data(), S) == 0) return Keyword::O;
#   include "Keywords.inc"
#undef OP

#undef KW

    Buf->Pop();

    return Keyword::None;
}

Keyword Lexer::IsKeyword(Buffer<char, 512>* Buf)
{
    Buf->Push('\0');

    printf("KWBuf = %s\n", Buf->Data());

#define OP(...)

#define KW(W, S) if(CString::Compare(Buf->Data(), S) == 0) return Keyword::W;
#   include "Keywords.inc"
#undef KW

#undef OP

    Buf->Pop();

    return Keyword::None;
}

void Lexer::ParseOperator()
{
    while(IsOperator(&Buf) != Keyword::None)
    {
        Buf.Push(File.Peek());
    }
}

Lexeme Lexer::Next()
{
    auto Temp = CurrentLex;
    
    CurrentLex = NextLex;
    NextLex = Next2Lex;
    Next2Lex = LexNext();

    return Temp;
}

Lexeme Lexer::LexNext()
{
    char C = File.Next();

    if(Utils::IsEOF(C) || FoundEOF)
    {
        FoundEOF = true;
        return Lexeme(LexType::End);
    }

    //Is a comment
    if(C == '(' && File.Peek() == '*')
    {
        //Discard the '('
        File.Next();

        while(true)
        {
            C = File.Next();
            if(C == '*' && File.Peek() == ')')
            {
                //Get rid of the ')'
                File.Next();
                break;
            }
        }
    }

    if(Utils::IsNum(C)) //is a number
    {
        Buf.Wipe();        
        if(C == '0')
        {
            C = File.Next();
            //Might be a sepcial number format
            //such as hex '0x...' or bits '0b...'
            if(C == 'x')
            {
                C = File.Next();
                while(ValidHex(C))
                {
                    Buf.Push(C);
                    C = File.Next();
                }

                Buf.Push('\0');
                auto Num = Utils::ParseHex(*Buf);

                return Num.Fold<Lexeme>([](I64 Val) {
                    auto Ret = Lexeme(LexType::Int);
                    Ret.Num = Val;
                    printf("Hex = %lld\n", Val);
                    return Ret;
                }, []{
                    printf("Hex = Bad\n");
                    return Lexeme(LexType::End);
                });
            }
            else if(C == 'b')
            {
                C = File.Next();
                while(C == '0' || C == '1')
                {
                    Buf.Push(C);
                    C = File.Next();
                }

                Buf.Push('\0');
                auto Num = Utils::ParseBits(*Buf);

                return Num.Fold<Lexeme>([](I64 Val){
                    auto Ret = Lexeme(LexType::Int);
                    Ret.Num = Val;

                    printf("Bit = %lld\n", Val);
                    return Ret;
                }, []{
                    printf("Bit = Bad\n");
                    return Lexeme(LexType::End);
                });
            }
            else if(C == '.')
            {   
                Buf.Push('0');
                Buf.Push('.');
                return ParseNum(&Buf, C);
                //Is a decimal
            }
            else 
            {
                //Is an error (no leading zeros allowed on numbers)
            }
        }
        else
        {
            Buf.Push(C);
            return ParseNum(&Buf, C);
        }
            
    }
    else if(Utils::IsAlpha(C) || C == '_')
    {
        //Is an identifier or keyword
        Buf.Wipe();

        Buf.Push(C);
        C = File.Next();

        while(Utils::IsAlnum(C) || C == '_')
        {
            Buf.Push(C);
            C = File.Next();
        }

        auto A = IsKeyword(&Buf);

        if(A != Keyword::None)
        {
            auto Ret = Lexeme(LexType::Keyword);
            Ret.Key = A;

            printf("Keyword = %hhu\n", A);

            return Ret;
        }
        else
        {
            auto Ret = Lexeme(LexType::Ident);
            Ret.Ident = new String(*Buf);

            printf("Ident = %s\n", Ret.Ident->CStr());

            return Ret;
        }
    }
    else if(Utils::IsSpace(C))
    {
        //If its a space, recurse to drop a character and return a new Lexeme
        return Next();
    }
    else
    {
        //Is something like a symbol, '[]{}()!@#$...'
        Buf.Wipe();
        Buf.Push(C);

        //TODO: this seems hacky
        Buf[1] = '\0';

        printf("Buf = %c%c\n", Buf.Data()[0], Buf.Data()[1]);

        ParseOperator();

        auto Ret = Lexeme(LexType::Keyword);
        Ret.Key = IsOperator(&Buf);

        return Ret;

        //TODO: Make operator lexing work proplery
    }

    return Lexeme(LexType::End);
}

Lexeme Lexer::Peek() const
{

}

Lexeme Lexer::Peek2() const
{

}

