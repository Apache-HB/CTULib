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
#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Optional.h"

#include "Utils/Build.h"

#include <cstdio>
#include <stdlib.h>

using Cthulhu::Array;
using Cthulhu::String;
using Cthulhu::Optional;

int Main(Array<String> Args)
{
    if(Args.Len() > 2)
    {
        printf("No tome provided\nExiting...\n");
        exit(5);
    }

    

    Optional<String> Compiler = Summon::GetCompiler();

    Compiler.Fold<void>([](String Compiler) {

    }, []{
        printf("No compiler installed to the command line\nExiting...\n");
        exit(5);
    });

    return 0;
}

int main(int argc, char const *argv[])
{
    return Main(Array<String>(argc, [argv](int argc) -> String { return argv[argc]; }));
}
