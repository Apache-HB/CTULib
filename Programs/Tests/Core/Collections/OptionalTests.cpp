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

//Not actually optional, just testing the optional class :p

#include "TestUtils.h"

#include "Core/Collections/Optional.h"
#include "Core/Collections/CthulhuString.h"

using Cthulhu::Optional;
using Cthulhu::NullOpt;
using Cthulhu::String;

bool TestConstructors()
{
    bool Pass = true;

    Optional<bool> BoolOpt = NullOpt<bool>();

    TEST_ASSERT(Pass, !BoolOpt.Or(false));
    
    Optional<float> FOpt(5.3);

    TEST_ASSERT(Pass, FOpt);

    Optional<String> StrOpt("Name jeff");

    TEST_ASSERT(Pass, StrOpt.Or("Not jeff") == "Name jeff");

    return true;
}

bool TestFunctions()
{
    bool Pass = true;
    Optional<String> AnotherStr = NullOpt<String>();

    TEST_ASSERT(Pass, AnotherStr.Fold<bool>(
        [](String Str) -> bool {
            return false;
        }, []() -> bool {
            return true;
        })
    );

    //is nullopt, so wont be valid
    TEST_ASSERT(Pass, !AnotherStr.Valid());

    return Pass;
}

int main(int argc, char const *argv[])
{
    bool Pass = true;

    TEST_BLOCK(Pass, TestConstructors, "Optional constructor");

    TEST_BLOCK(Pass, TestFunctions, "Optional function");

    TEST_RETURN(Pass, "Optional");
}
