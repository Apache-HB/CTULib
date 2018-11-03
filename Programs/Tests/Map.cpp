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

#include "TestMacros.h"

#include <Core/Serialization/Hashes.h>
#include <Core/Collections/Map.h>
#include <Core/Collections/CthulhuString.h>

using namespace Cthulhu;

int main()
{
    Map<String, U32> TestMap;

    TestMap["A"] = 5;
    TestMap["B"] = 10;

    ASSERT_TEST(TestMap["A"] == 5);
    ASSERT_TEST(TestMap["B"] == 10);

    printf("%lu\n", TestMap["A"]);

    ASSERT_TEST(TestMap.Keys().Len() == 2);

    ASSERT_TEST(TestMap.Values().Len() == 2);
    ASSERT_TEST(TestMap.Items().Len() == 2);
}