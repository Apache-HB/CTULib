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

#include "Types.h"

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

Vector::Vector()
    : X(0)
    , Y(0)
    , Z(0)
{}

Vector::Vector(F32 I)
    : X(I)
    , Y(I)
    , Z(I)
{}

Vector::Vector(F32 InX, F32 InY, F32 InZ)
    : X(InX)
    , Y(InY)
    , Z(InZ)
{}

bool Vector::operator==(const Vector& Other) const
{
    return X == Other.X && Y == Other.Y && Z == Other.Z;
}

bool Vector::operator!=(const Vector& Other) const
{
    return X != Other.X && Y != Other.Y && Z != Other.Z;
}

Vector2D::Vector2D()
    : X(0)
    , Y(0)
{}

Vector2D::Vector2D(F32 I)
    : X(I)
    , Y(I)
{}

Vector2D::Vector2D(F32 InX, F32 InY)
    : X(InX)
    , Y(InY)
{}

bool Vector2D::operator==(const Vector2D Other) const
{
    return X == Other.X && Y == Other.Y;
}

bool Vector2D::operator!=(const Vector2D Other) const
{
    return X != Other.X && Y != Other.Y;
}

Size::Size()
    : Width(0)
    , Height(0)
{}

Size::Size(U32 I)
    : Width(I)
    , Height(I)
{}

Size::Size(U32 W, U32 H)
    : Width(W)
    , Height(H)
{}

bool Size::operator==(const Size Other) const
{
    return Width == Other.Width && Height == Other.Height;
}

bool Size::operator!=(const Size Other) const
{
    return Width != Other.Width && Height != Other.Height;
}

Point::Point()
    : X(0)
    , Y(0)
{}

Point::Point(U32 I)
    : X(I)
    , Y(I)
{}

Point::Point(U32 InX, U32 InY)
    : X(InX)
    , Y(InY)
{}

bool Point::operator==(const Point Other) const
{
    return X == Other.X && Y == Other.Y;
}

bool Point::operator!=(const Point Other) const
{
    return X != Other.X && Y != Other.Y;
}

Dimensions::Dimensions()
    : Width(0)
    , Height(0)
    , X(0)
    , Y(0)
{}

Dimensions::Dimensions(const Point Loc, const Size InSize)
    : Width(InSize.Width)
    , Height(InSize.Height)
    , X(Loc.X)
    , Y(Loc.Y)
{}

Dimensions::Dimensions(U32 InWidth, U32 InHeight, U32 InX, U32 InY)
    : Width(InWidth)
    , Height(InHeight)
    , X(InX)
    , Y(InY)
{}

Point Dimensions::Location() const
{
    return { X, Y };
}

Size Dimensions::GetSize() const
{
    return { Width, Height };
}

bool Dimensions::operator==(const Dimensions& Other) const
{
    return (
        Width == Other.Width && 
        Height == Other.Height &&
        X == Other.X && 
        Y == Other.Y
    );
}

bool Dimensions::operator!=(const Dimensions& Other) const
{
    return (
        Width != Other.Width && 
        Height != Other.Height &&
        X != Other.X && 
        Y != Other.Y
    );
}

void Dimensions::SetLocation(const Point NewLocation)
{
    X = NewLocation.X;
    Y = NewLocation.Y;
}

void Dimensions::SetSize(const Size NewSize)
{
    Width = NewSize.Width;
    Height = NewSize.Height;
}
