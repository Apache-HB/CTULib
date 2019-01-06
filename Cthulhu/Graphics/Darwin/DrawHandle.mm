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

#include "DrawHandle.h"

#import <Cocoa/Cocoa.h>

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

#define PTH(A) ((NSBezierPath*)A)
#define IMG(A) ((NSImage*)A)
#define RCT(A) ((NSRect*)A)

NSColor* ColourToNS(Colour& C)
{
    float R = ((float)C.R) / 255, 
          G = ((float)C.G) / 255,
          B = ((float)C.B) / 255,
          A = ((float)C.A) / 255;
    
    return [NSColor colorWithCalibratedRed:R green:G blue:B alpha:A];
}

void MacDrawHandle::DrawRect(const Dimensions& Dim, Colour Col)
{

}

void MacDrawHandle::DrawPath(Path& ThePath)
{
    [ColourToNS(ThePath.PathColour) setFill];
    [PTH(ThePath.Native()) stroke];
    [PTH(ThePath.Native()) fill];
}

void MacDrawHandle::DrawImage(Image& Img, U32 X, U32 Y)
{

}
