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

#include <Meta/Assert.h>

#include "Error.h"

using namespace Cthulhu;
using namespace Cthulhu::Lang;

void Print(const String& Message, ErrorLevel Level)
{

}

String ColourFor(Colour Val)
{
    switch(Val)
    {
        case Colour::Black: return "\033[30m{0}\033[0m\0";
        case Colour::Red: return "\033[91m{0}\033[0m\0";
        case Colour::Green: return "\033[92m{0}\033[0m\0";
        case Colour::Yellow: return "\033[93m{0}\033[0m\0";
        case Colour::Blue: return "\033[94m{0}\033[0m\0";
        case Colour::Pink: return "\033[95m{0}\033[0m\0";
        case Colour::Cyan: return "\033[96m{0}\033[0m\0";
        case Colour::White: return "\033[97m{0}\033[0m\0";
        default: 
            ASSERT_NO_ENTRY("Invalid colour");
    }
}