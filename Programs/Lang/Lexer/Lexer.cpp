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

#include "Lexer.h"

using namespace Cthulhu::Lang;

using TType = Token::Type;

Token Lexer::ParseIdent()
{
    char C = File.Next();

    while(Utils::IsAlnum(C))
    {
        Buf.Push(C);
        C = File.Next();
    }
    File.Push(C);

    Keyword Ret = KeywordType();

    if(Ret == Keyword::NoKw)
    {
        auto Tok = Token(TType::Ident);
        Buf.Push('\0');
        Tok.Str = new String(*Buf);
        Buf.Pop();

        return Tok;
    }
    else
    {
        auto Tok = Token(TType::Key);
        Tok.Key = Ret;

        return Tok;
    }
}

Token Lexer::ParseKeyword()
{
    char C = File.Next();

    Keyword Key;

    while((Key = OperatorType()) != Keyword::NoOp)
    {
        C = File.Next();
        Buf.Push(C);
    }
}

Token Lexer::GetNext()
{
    char C = File.Next();

    Buf.Wipe();
    Buf.Push(C);

    if(Utils::IsEOF(C))
    {
        return Token(TType::End);
    }

    if(C == '/' && File.Peek() == '*')
    {
        //is a comment
        C = File.Next();

        while(C != '*' || File.Peek() != '/')
        {
            C = File.Next();
            if(Utils::IsEOF(C))
            {
                return Token(TType::End);
            }
        }
    }

    if(C == ' ')
    {
        while(Utils::IsSpace(C))
        {
            C = File.Next();
        }
    }

    Buf.Push(C);

    if(Utils::IsAlpha(C))
    {
        return ParseIdent();
    }
    else if(Utils::IsNum(C))
    {
        return ParseNumber();
    }
    else if(C == '"' || C == '\'')
    {
        return ParseString();
    }
    else if(Utils::IsEOF(C))
    {
        return Token(TType::End);
    }
    else
    {
        return ParseKeyword();
    }
}

Token Lexer::Next()
{
    Token Ret = Current;
    
    Current = Look1;
    Look1 = Look2;
    Look2 = GetNext();

    return Ret;
}

Token Lexer::Peek() const
{
    return Current;
}

Token Lexer::Peek2() const
{
    return Look1;
}

Token Lexer::Peek3() const 
{
    return Look2;
}

/*

#include <stdio.h>
#include <unistd.h>

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
    else if(Type == LexType::FString)
        delete Format;
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

#define KW(...)

#define OP(O, S) if(CString::Compare(Buf->Data(), S) == 0) { Buf->Pop(); return Keyword::O; }
#   include "Keywords.inc"
#undef OP

#undef KW

    Buf->Pop();

    return Keyword::None;
}

Keyword Lexer::IsKeyword(Buffer<char, 512>* Buf)
{
    Buf->Push('\0');

#define OP(...)

#define KW(W, S) if(CString::Compare(Buf->Data(), S) == 0) { Buf->Pop(); return Keyword::W; }
#   include "Keywords.inc"
#undef KW

#undef OP

    Buf->Pop();

    return Keyword::None;
}

void Lexer::ParseOperator()
{
    char C;
    
    while(IsOperator(&Buf) != Keyword::None)
    {
        Buf.Push(File.Peek());
        C = File.Next();
    }

    File.Push(C);

    Buf.Pop();
}

Lexeme Lexer::Next()
{
    auto Temp = CurrentLex;
    
    CurrentLex = NextLex;
    NextLex = Next2Lex;
    Next2Lex = LexNext();

    return Temp;
}

void Lexer::ParseHexString()
{
    Buffer<char, 32> HexBuf;

    char C = File.Next();

    if(C != 'x')
    {
        Buf.Push(C);
        return;
    }

    while(ValidHex(C))
    {
        HexBuf.Push(C);
    }

    Utils::ParseHex(*HexBuf).Fold<void>([this](I64 Hex){
        Buf.Push((char)Hex);
    }, []{
        //Warn here
    });
}

void Lexer::ParseEscapedChar()
{
    char C = File.Next();

    if(C == '{')
    {
        Buf.Push('{');
    }
    else if(C == '0')
    {
        ParseHexString();
        return;
        //Is hex char
    }
    
    char ToPush = '\0';

    switch(C)
    {
        case '\'': ToPush = '\'';    break;
        case '"': ToPush = '"';      break;
        case '\\': ToPush = '\\';    break;
        case 'a': ToPush = '\a';     break;
        case 'b': ToPush = '\b';     break;
        case 'f': ToPush = '\f';     break;
        case 'n': ToPush = '\n';     break;
        case 'r': ToPush = '\r';     break;
        case 't': ToPush = '\t';     break;
        case 'v': ToPush = '\v';     break;
        case '0': ParseHexString(); return;
        case '{': ToPush = '{';      break;
        default:
            //Warn about unrecognised escape sequence
            Buf.Push('\\');
            Buf.Push(C);
    }
};

Lexeme Lexer::ParseFString()
{
    char C = File.Next();
    Buf.Push(C);

    U64 InitialLoc = Distance;

    if(C == '\\')
    {
        ParseEscapedChar();
    }
    else if(C == '"')
    {
        return Lexeme();
    }
    else if(C == '{')
    {

    }
}

Lexeme Lexer::LexNext()
{
    char C = File.Next();

    if(Utils::IsEOF(C) || FoundEOF)
    {
        FoundEOF = true;
        return Lexeme(LexType::End);
    }

    printf("N2 = %c%c\n", C, File.Peek());

    //Is a comment
    if(C == '(' && File.Peek() == '*')
    {
        //Discard the '('
        File.Next();
        printf("Found Comment\n");
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

        printf("End Comment\n");
    }

    char N = File.Peek();

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
    else if(C == 'f' && N == '"' || N == '\'')
    {
        //Is an f-string like python
        Buf.Wipe();
        File.Next(); //discard the "
        return ParseFString(N);
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

            File.Push(C);

            return Ret;
        }
        else
        {
            auto Ret = Lexeme(LexType::Ident);
            Ret.Ident = new String(*Buf);

            printf("Ident = %s\n", Ret.Ident->CStr());

            File.Push(C);

            printf("C = %c\n", C);

            return Ret;
        }
    }
    else if(Utils::IsSpace(C))
    {
        //If its a space, recurse to drop a character and return a new Lexeme
        return Next();
    }
    else if(C == '\'' || C == '"')
    {
        //Is a single char
        return ParseString(C);
    }
    else
    {
        //Is something like a symbol, '[]{}()!@#$...'
        Buf.Wipe();
        Buf.Push(C);

        ParseOperator();

        auto Ret = Lexeme(LexType::Keyword);
        Ret.Key = IsOperator(&Buf);

        switch(Ret.Key)
        {
            case Keyword::Or2: Ret.Key = Keyword::Or;   break;
            case Keyword::And2: Ret.Key = Keyword::And; break;
            case Keyword::Not2: Ret.Key = Keyword::Not; break;
            default: break;
        }

        if(Ret.Key == Keyword::None)
            return Lexeme(LexType::End);

        printf("Op = %hhu\n", Ret.Key);

        printf("C = %c\n", C);

        return Ret;
    }

    return Lexeme(LexType::End);
}

Lexeme Lexer::Peek() const
{
    return CurrentLex;
}

Lexeme Lexer::Peek2() const
{
    return NextLex;
}

Lexeme Lexer::Peek3() const
{
    return Next2Lex;
}

*/