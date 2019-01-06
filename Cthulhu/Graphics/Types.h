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

    Size operator+(const Size Other) const { return { Width + Other.Width, Height + Other.Height }; }
    Size operator+=(const Size Other) { Width += Other.Width; Height += Other.Height; return *this; }

    Size operator-(const Size Other) const { return { Width - Other.Width, Height - Other.Height }; }
    Size operator-=(const Size Other) { Width -= Other.Width; Height -= Other.Height; return *this; }

    Size operator*(const Size Other) const { return { Width * Other.Width, Height * Other.Height }; }
    Size operator*=(const Size Other) { Width *= Other.Width; Height *= Other.Height; return *this; }

    Size operator/(const Size Other) const { return { Width / Other.Width, Height / Other.Height }; }
    Size operator/=(const Size Other) { Width /= Other.Width; Height /= Other.Height; return *this; }

    U32 Width, Height;
};

struct Point
{
    Point();
    Point(U32 I);
    Point(U32 InX, U32 InY);

    bool operator==(const Point Other) const;
    bool operator!=(const Point Other) const;

    Point operator+(const Point Other) const { return { X + Other.X, Y + Other.Y }; }
    Point operator+=(const Point Other) { X += Other.X; Y += Other.Y; return *this; }
    
    Point operator-(const Point Other) const { return { X - Other.X, Y - Other.Y }; }
    Point operator-=(const Point Other) { X -= Other.X; Y -= Other.Y; return *this; }
    
    Point operator*(const Point Other) const { return { X * Other.X, Y * Other.Y }; }
    Point operator*=(const Point Other) { X *= Other.X; Y *= Other.Y; return *this; }
    
    Point operator/(const Point Other) const { return { X / Other.X, Y / Other.Y }; }
    Point operator/=(const Point Other) { X /= Other.X; Y /= Other.Y; return *this; }
    

    U32 X, Y;
};

struct Dimensions
{
    Dimensions();
    Dimensions(const Point Loc, const Size InSize);
    Dimensions(U32 InX, U32 InY, U32 InWidth, U32 InHeight);

    Point Location() const;
    Size GetSize() const;

    bool operator==(const Dimensions& Other) const;
    bool operator!=(const Dimensions& Other) const;

    Dimensions operator+(const Dimensions Other) const 
    { 
        return 
        { 
            X + Other.X,
            Y + Other.Y,
            Width + Other.Width,
            Height + Other.Height
        }; 
    }

    Dimensions operator+=(const Dimensions Other) 
    { 
        X += Other.X;
        Y += Other.Y;
        Width += Other.Width;
        Height += Other.Height;
        
        return *this;
    }
    
    Dimensions operator-(const Dimensions Other) const 
    { 
        return 
        {
            X - Other.X,
            Y - Other.Y,
            Width - Other.Width,
            Height - Other.Height
        }; 
    }

    Dimensions operator-=(const Dimensions Other) 
    { 
        X -= Other.X;
        Y -= Other.Y;
        Width -= Other.Width;
        Height -= Other.Height;
        
        return *this;
    }
    
    Dimensions operator*(const Dimensions Other) const 
    { 
        return 
        { 
            X * Other.X,
            Y * Other.Y,
            Width * Other.Width,
            Height * Other.Height
        }; 
    }

    Dimensions operator*=(const Dimensions Other) 
    { 
        X *= Other.X;
        Y *= Other.Y;
        Width *= Other.Width;
        Height *= Other.Height;
        
        return *this;
    }
    
    Dimensions operator/(const Dimensions Other) const 
    { 
        return 
        { 
            X / Other.X,
            Y / Other.Y,
            Width / Other.Width,
            Height / Other.Height
        }; 
    }

    Dimensions operator/=(const Dimensions Other) 
    { 
        X /= Other.X;
        Y /= Other.Y;
        Width /= Other.Width;
        Height /= Other.Height;
        
        return *this;
    }

    void SetLocation(const Point NewLocation);
    void SetSize(const Size NewSize);

    U32 Width, Height;
    U32 X, Y;
};

enum class ModifierKeys : U8
{
    Alt = (1 << 0), ///< alt key(left or right)
    Shift = (1 << 1), ///< shift key (left or right)
    Control = (1 << 2), ///< ctrl key
    Special = (1 << 3), ///< Windows key or command key on mac
    CapsLock = (1 << 4), ///< capslock key
    Function = (1 << 5), ///< function key
    Option = (1 << 6), ///< option key (left or right)
    Escape = (1 << 7), ///< escape key
};

inline ModifierKeys operator|=(ModifierKeys &Left, const ModifierKeys Right)
{
    return Left = (ModifierKeys)((U8)Left | (U8)Right);
}

struct Event
{
    Point MouseLocation;
    const String KeysPressed;
    ModifierKeys Flags;
};

/** different main loop event types
 * 
 */
enum class MainLoopEvent
{
    Launch, ///< The application has just launched
    RequestAbout, ///< User has requested the applications about screen
    RequestQuit, ///< User has either told the main application to quit, or has closed the main window
    ApplicationFocus, ///< The application has been selected by the user
    ApplicationDefocus, ///< The user has clicked off the application and has focused another application
    MouseEntered, ///< The mouse has entered the main application window
    MouseExited, ///< The mouse has exited the main application window
    Crash, ///< The application has crashed (segfault, sigabort, etc)
    Tick, ///< The application has ticked
};

enum class PowerMode : U8
{
    Unknown, ///< Couldnt find out OS battery status
    OnBattery, ///< Has a battery and is using it
    Charging, ///< Is plugged into power and is charging
    Charged, ///< Is plugged into power and is fully charged
    NoBattery, ///< Doesnt have a battery (most desktops)
};

struct Colour
{
    U8 R = 0, 
       G = 0, 
       B = 0, 
       A = 255;
};

} // Cthulhu::Graphics
