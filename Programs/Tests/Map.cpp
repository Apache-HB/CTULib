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

#include <vector>

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

    auto Keys = TestMap.Keys();

    String F = *Keys[0];

    ASSERT_TEST(TestMap.Keys().Len() == 2);

    ASSERT_TEST(TestMap.Values().Len() == 2);
    ASSERT_TEST(TestMap.Items().Len() == 2);

    Map<U32, String> Numbers = {
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" }
    };

    ASSERT_TEST(Numbers[0] == "zero");
    ASSERT_TEST(Numbers[10] == "ten");

    I32 Loop = 0;

    for(auto& A : Numbers.Keys())
        ;
    
    Loop = 0;

    for(auto A : Numbers.Values())
        ;

    Loop = 0;

    for(const auto& I : Numbers.Items())
    {
        if(Loop == 0)
        {
            ASSERT_TEST(*I.First == 0);
            ASSERT_TEST(*I.Second == "zero");
        }
        else if(Loop == 1)
        {
            ASSERT_TEST(*I.First == 1);
            ASSERT_TEST(*I.Second == "one");
        }
        else if(Loop == 2)
        {
            ASSERT_TEST(*I.First == 2);
            ASSERT_TEST(*I.Second == "two");
        }
        else if(Loop == 3)
        {
            ASSERT_TEST(*I.First == 3);
            ASSERT_TEST(*I.Second == "three");
        }
        else if(Loop == 4)
        {
            ASSERT_TEST(*I.First == 4);
            ASSERT_TEST(*I.Second == "four");
        }
        else if(Loop == 5)
        {
            ASSERT_TEST(*I.First == 5);
            ASSERT_TEST(*I.Second == "five");
        }
        else if(Loop == 6)
        {
            ASSERT_TEST(*I.First == 6);
            ASSERT_TEST(*I.Second == "six");
        }
        else if(Loop == 7)
        {
            ASSERT_TEST(*I.First == 7);
            ASSERT_TEST(*I.Second == "seven");
        }
        else if(Loop == 8)
        {
            ASSERT_TEST(*I.First == 8);
            ASSERT_TEST(*I.Second == "eight");
        }
        else if(Loop == 9)
        {
            ASSERT_TEST(*I.First == 9);
            ASSERT_TEST(*I.Second == "nine");
        }
        else if(Loop == 10)
        {
            ASSERT_TEST(*I.First == 10);
            ASSERT_TEST(*I.Second == "ten");
        }
        else
        {
            ASSERT_TEST(false);
        }

        Loop++;
    }

}