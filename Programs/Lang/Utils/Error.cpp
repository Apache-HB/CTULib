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

#include "Error.h"

using namespace Cthulhu;
using namespace Cthulhu::Lang;
using namespace Cthulhu::Lang::Err;

String Cthulhu::Lang::Err::LevelToTag(Level LVL)
{
    switch(LVL)
    {
        default:
        case Level::Abort:
        case Level::Fatal:
        case Level::Warning:
        case Level::Trivial:
        case Level::Other:
            ;//TODO
    }
}

String Cthulhu::Lang::Err::ColourText(
    const String& Text, 
    Colour C
)
{
    String Ret = Text;
    switch(C)
    {
        default:
        case Colour::Black: 
            Ret.Push("\033[30");
            break;
        case Colour::Red:
            Ret.Push("\033[91m");
            break;
        case Colour::Green:
            Ret.Push("\033[92m");
            break;
        case Colour::Yellow:
            Ret.Push("\033[93m");
            break;
        case Colour::Blue:
            Ret.Push("\033[94m");
            break;
        case Colour::Pink:
            Ret.Push("\033[95m");
            break;
        case Colour::Cyan:
            Ret.Push("\033[96m");
            break;
        case Colour::White:
            Ret.Push("\033[97m");
            break;
    }

    Ret.Append("\033[0m\0");
    return Ret;
}

void Cthulhu::Lang::Err::Error(
    const String& Message, 
    const Location& Loc, 
    Level Severity
)
{

}

String Cthulhu::Lang::Err::Shorten(
    const String& Text,
    U16 NewLen
)
{

}