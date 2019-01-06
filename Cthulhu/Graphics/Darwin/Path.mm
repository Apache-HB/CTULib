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

#include "Path.h"
#include "Core/Memory/Memory.h"

#import <Cocoa/Cocoa.h>

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

#define PTH(A) ((NSBezierPath*)A)

MacPath::MacPath(const Point P)
{
    Handle = [NSBezierPath bezierPath];
    [PTH(Handle) moveToPoint:NSMakePoint(P.X, P.Y)];
    PathColour = { 255, 255, 255, 255 };
}

void MacPath::LineTo(const Point Loc)
{
    [PTH(Handle) lineToPoint:NSMakePoint(Loc.X, Loc.Y)];
}

void MacPath::CurveTo(const Point Loc, const Point Ctrl1, const Point Ctrl2)
{
    [PTH(Handle) curveToPoint:NSMakePoint(Loc.X, Loc.Y)
        controlPoint1:NSMakePoint(Ctrl1.X, Ctrl1.Y)
        controlPoint2:NSMakePoint(Ctrl2.X, Ctrl2.Y)
    ];
}

void MacPath::Close()
{
    [PTH(Handle) closePath];
}
