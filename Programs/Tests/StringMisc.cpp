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
#include <Core/Collections/Option.h>

#include "TestMacros.h"

using namespace Cthulhu;

int main()
{
    ASSERT_TEST(Utils::Padding('a', 5) == "aaaaa");
    ASSERT_TEST(Utils::ParseInt("25").Get() == 25);
    ASSERT_TEST(!Utils::ParseInt("2.5").Valid());
    ASSERT_TEST(Utils::ParseFloat("25.5").Get() == 25.5);
    ASSERT_TEST(Utils::ParseBool("true").Get());
    ASSERT_TEST(!Utils::ParseBool("false").Get());

    ASSERT_TEST(Utils::ToString(25LL) == "25");
    //ASSERT_TEST(Utils::ToString(25.5f) == "25.5");
    ASSERT_TEST(Utils::ToString(true) == "true");
    ASSERT_TEST(Utils::ToString(false) == "false");

    ASSERT_TEST(Utils::HexToString(0x0111) == "0x0111");

    ASSERT_TEST(Utils::IsSpace(' '));
    ASSERT_TEST(Utils::IsUpper('A'));
    ASSERT_TEST(Utils::IsLower('a'));

    printf("end\n");
}
