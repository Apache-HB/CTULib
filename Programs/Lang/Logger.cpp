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

#include <stdio.h>

#include "Logger.h"

using namespace Cthulhu;
using namespace Cthulhu::Lang;

namespace 
{ 

static const char* ToTag(Level Tag)
{
    switch(Tag)
    {
        default:
        case Level::Fatal:
            return "\x1B[31mFatal: \x1B[0m";
        case Level::Warning:
            return "\x1B[33mWarning: \x1B[0m";
        case Level::Note:
            return "\x1B[35mNote: \x1B[0m";
        case Level::Debug:
            return "\x1B[32mDebug: \x1B[0m";
    }
}

}

void Cthulhu::Lang::Log(const Channel& InChannel, const String& Message)
{
    printf("%s%s\n", ToTag(InChannel.ThisLevel), *Message);
}