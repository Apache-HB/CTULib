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

#include <Core/Collections/Array.h>

using namespace Cthulhu;

int main()
{
    Array<U64> Test;
    Test.Append(5ULL);
    Test.Append(25ULL);

    ASSERT_TEST(Test.Len() == 2);

    ASSERT_TEST(Test[0] == 5ULL);
    ASSERT_TEST(Test[1] == 25ULL);

    U64 E = Test.Pop();
    ASSERT_TEST(E == 25ULL);

    Array<U64> Another;
    Another.Append(9999ULL);

    Another.Append(Test);

    ASSERT_TEST(Another.Len() == 2);

    Another.Append(95ULL);

    ASSERT_TEST(Another[2] == 95ULL);

    Array Temp = Test + Another;

    printf("yeet|%llu|\n", Temp.Len());
    printf("|%llu|%llu|%llu|%llu|\n", Temp[0], Temp[1], Temp[2], Temp[3]);

    //TEST_FAIL: double free from `Array Temp = Test + Another` going out of 
    //scope and calling the destructor
    ASSERT_TEST(Temp.Len() == 3);
}