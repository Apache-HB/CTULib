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

#include <stdlib.h>
#include <cstdio>

#include "Build.h"

using Cthulhu::String;
using Cthulhu::Optional;
using Cthulhu::NullOpt;

const Cthulhu::Optional<Cthulhu::String> Summon::GetCompiler()
{
    //always prioritize clang as its the best compiler out of the 3
    if(system("which clang++ > /dev/null 2>&1")) 
    {
        return Optional<String>("clang++");
    }
    else if(system("which g++ > /dev/null 2>&1"))
    {
        return Optional<String>("g++");
    }
    else if(system("MSBUILD.exe"))
    {
        return Optional<String>("MSBUILD.exe");
    }

    return NullOpt<String>();
}