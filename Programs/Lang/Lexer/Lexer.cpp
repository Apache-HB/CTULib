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
#include <Core/Memory/Buffer.h>

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
    CurrentLex = Next();
    NextLex = Next();
    Next2Lex = Next();
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
    bool IsFloat = false;

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

Lexeme Lexer::Next()
{
    char C = File.Next();

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
    else if(Utils::IsEOF(C))
    {
        return Lexeme(LexType::End);
    }

    if(Utils::IsNum(C)) //is a number
    {
        Buffer<char, 512> NumBuf;
        
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
                    NumBuf.Push(C);
                    C = File.Next();
                }

                NumBuf.Push('\0');
                auto Num = Utils::ParseHex(*NumBuf);

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
                    NumBuf.Push(C);
                    C = File.Next();
                }

                NumBuf.Push('\0');
                auto Num = Utils::ParseBits(*NumBuf);

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
                NumBuf.Push('0');
                NumBuf.Push('.');
                return ParseNum(&NumBuf, C);
                //Is a decimal
            }
            else 
            {
                //Is an error (no leading zeros allowed on numbers)
            }
        }
        else
        {
            NumBuf.Push(C);
            return ParseNum(&NumBuf, C);
        }
            
    }
    else if(Utils::IsAlpha(C))
    {

    }
    else
    {

    }

    return Lexeme();
}

Lexeme Lexer::Peek() const
{

}

Lexeme Lexer::Peek2() const
{

}

