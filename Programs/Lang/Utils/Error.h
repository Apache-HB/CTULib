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

#include <Core/Collections/CthulhuString.h>
#include <FileSystem/BufferedFile.h>

namespace Cthulhu::Lang::Err
{

enum class Level
{
    Abort,
    Fatal,
    Warning,
    Trivial,
    Other,
};

String LevelToTag(Level LVL);

enum class Colour
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Pink,
    Cyan,
    White
};

String ColourText(const String& Text, Colour C);

namespace FS = Cthulhu::FileSystem;

struct Location
{
    FS::BufferedFile* File;
    String* FileName;
    U64 Line, Loc, Len;
};

void Error(const String& Message, const Location& Loc, Level Severity);

String Shorten(const String& Text, U16 NewLen);

}