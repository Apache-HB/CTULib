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

#include "Cthulhu/Meta/Macros.h"

#pragma once

#if defined(OS_WINDOWS)
#   include "Windows/Image.h"
#elif defined(OS_APPLE)
#   include "Darwin/Image.h"
#elif defined(OS_LINUX)
#   include "Linux/Image.h"
#endif

#if 0
namespace Cthulhu::Graphics
{

struct Image
{
    Image(U8* Bytes, U32 DataWidth, U32 DataHeight);
    Image(U8 Colour[3], U32 DataWidth, U32 DataHeight);

    void SetPixel(U32 X, U32 Y, U8 Colour[3]);
    U8* GetPixel(U32 X, U32 Y);

    U32 GetWidth() const { return Height; }
    U32 GetHeight() const { return Width; }
    U8* Real() const { return Data; }
private:
    U8* Data;
    U32 Width, Height;
};

}

#endif