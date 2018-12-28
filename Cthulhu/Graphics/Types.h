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

#include "Core/Collections/Array.h"

#pragma once

namespace Cthulhu::Graphics
{

struct Vector
{
    Vector();
    Vector(F32 I);
    Vector(F32 InX, F32 InY, F32 InZ);

    bool operator==(const Vector& Other) const;
    bool operator!=(const Vector& Other) const;

    F32 X, Y, Z;
};

struct Vector2D
{
    Vector2D();
    Vector2D(F32 I);
    Vector2D(F32 InX, F32 InY);

    bool operator==(const Vector2D Other) const;
    bool operator!=(const Vector2D Other) const;

    F32 X, Y;
};

struct Size
{
    Size();
    Size(U32 I);
    Size(U32 W, U32 H);

    bool operator==(const Size Other) const;
    bool operator!=(const Size Other) const;

    U32 Width, Height;
};

struct Point
{
    Point();
    Point(U32 I);
    Point(U32 InX, U32 InY);

    bool operator==(const Point Other) const;
    bool operator!=(const Point Other) const;

    U32 X, Y;
};

struct Dimensions
{
    Dimensions();
    Dimensions(const Point Loc, const Size InSize);
    Dimensions(U32 InWidth, U32 InHeight, U32 InX, U32 InY);

    Point Location() const;
    Size GetSize() const;

    bool operator==(const Dimensions& Other) const;
    bool operator!=(const Dimensions& Other) const;

    void SetLocation(const Point NewLocation);
    void SetSize(const Size NewSize);

    U32 Width, Height;
    U32 X, Y;
};

enum class Orientation : U8
{
    Portrait,
    Landscape,
};

enum class ModifierKeys : U8
{
    Alt = (1 << 0),
    Shift= (1 << 1),
    Control = (1 << 2),
    Special = (1 << 3), //Windows key or command key on mac
    CapsLock = (1 << 4),
    Function = (1 << 5),
    Option = (1 << 6),
    Escape = (1 << 7),
};

inline ModifierKeys operator|=(const ModifierKeys Left, const ModifierKeys Right)
{
    return (ModifierKeys)(((U8)Left) | ((U8)Right));
}

struct Event
{
    struct
#if defined(OS_WINDOWS)
    WindowsWindow* Window;
#elif defined(OS_APPLE)
    MacWindow* Window;
#elif defined(OS_LINUX)
    LinuxWindow* Window;
#endif
    Point MouseLocation;
    U8 KeyPressed;
    ModifierKeys Flags;
};

} // Cthulhu::Graphics
