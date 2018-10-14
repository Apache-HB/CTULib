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

#include "TestUtils.h"

#include "Core/Collections/Result.h"

using Cthulhu::Result;
using Cthulhu::Pass;
using Cthulhu::Fail;

bool TestConstructors()
{
    bool TestPass = true;

    TEST_ASSERT(TestPass, (Fail<int, int>(5).HasErr()));

    TEST_ASSERT(TestPass, (Pass<int, int>(25).HasRes()));

    return TestPass;
}

int main(int argc, char const *argv[])
{
    bool TestPass = true;

    TEST_BLOCK(TestPass, TestConstructors, "result constructors");
    
    TEST_RETURN(TestPass, "Result");
}
