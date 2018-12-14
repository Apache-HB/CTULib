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



#if 0

#include "../Lexer/Lexer.h"

#include <Core/Collections/Option.h>
#include <Core/Collections/Array.h>
#include <Core/Collections/Map.h>

#pragma once

namespace Cthulhu::Lang
{

struct Import
{
    Buffer<String, 32> Path;
    Array<String> Exposes;
};

enum class Integral : U8
{
    I8, I16, I32, I64, I128,
    U8, U16, U32, U64, U128,
    Float, Bool, String, Char
};

enum class TypeType : U8
{
    Structure, Enum, Integral
};

struct Type
{
    bool Array;
    Type* Of;

    TypeType ThisType;

    union
    {
        Integral Scalar;
        Map<String, Type> Structure; 
        //also the enum structure
    };
};

struct Arg
{
    String Name;
    Type ArgType;
};

enum class ExprKind : U8
{
    If, ElseIf, Else, Branch,
    For, While, Operation, Val
};

struct Expr;

struct BoolExpr
{
    Expr* Left;
    Expr* Right;

    Keyword Operator;
};

struct IfStmt 
{
    BoolExpr* Cond;
    //If this is nullptr then its actually an else stmt
    Expr* Body;
    IfStmt* Else;
    //if this isnt null then the next thing could be either an else if or an else
};

struct BranchStmt
{
    Expr* Cond;
    //can be null if the stmt looks like 
    /**
     * 
     * branch {
     *     x == 5 => print("five");
     *     x == 7 => print("seven");
     * }
     * 
     * but if the stmt looks like
     * 
     * branch(x) {
     *     5 => print("five");
     *     7 => print("seven");
     * }
     * 
     */

    Map<Expr, Expr> Paths;
};

struct FuncCall
{
    Buffer<String, 32> Path;
    Type* CallingFrom;
    Array<Expr> Args;
    Map<String, Expr> KWArgs;
};

struct Expr
{
    ExprKind Kind;
    Expr* NextExpr;

    union
    {
        Integral Val;
        IfStmt If;
        Keyword Operator;
    };
};

struct Function
{
    String Name;
    Array<Arg> Args;
    Type ReturnType;

    Expr Body;
};

struct Variable
{
    const String Name;
    Type VarType;
    Expr Assignment;
};

struct Object
{
    Array<Function> Functions;
    Array<Variable> Variables;
    Function Constructor;
};

struct BaseTree
{
    Array<Import> Imports;
    Array<Object> Classes;
    Array<Variable> Variables;
    Array<Function> Functions;
};

struct Program
{
    
};

}

#endif