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

#include "Core/Collections/CthulhuString.h"

#pragma once

namespace Cthulhu::Lang
{

enum class Level
{
    Fatal,
    Warning,
    Note,
    Debug,
};

struct Channel
{
    String Name;
    Level ThisLevel;
};

void Log(const Channel& InChannel, const String& Message);

extern Channel Fatal =   { "Fatal", Level::Fatal     };
extern Channel Warning = { "Warning", Level::Warning };
extern Channel Note =    { "Note", Level::Note       };
extern Channel Debug =   { "Debug", Level::Debug     };

}