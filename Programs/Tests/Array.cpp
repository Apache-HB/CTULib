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
#include <Core/Collections/CthulhuString.h>

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

    Array<U64> First;
    First.Append(5ULL);
    First.Append(10ULL);

    Array<U64> Second;
    Second.Append(15ULL);
    Second.Append(20ULL);

    Array<U64> Both = First + Second;

    ASSERT_TEST(Both.Len() == 4);

    ASSERT_TEST(Both[0] == 5);
    ASSERT_TEST(Both[1] == 10);
    ASSERT_TEST(Both[2] == 15);
    ASSERT_TEST(Both[3] == 20);

    Both.Pop();

    ASSERT_TEST(Both.Len() == 3);

    Array<String> StrFirst;

    //FIXME: this now triggers heap-use-after-free
    StrFirst.Append("Name");
    StrFirst.Append("is");

    Array<String> StrSecond;

    StrSecond.Append("Jeff");
    StrSecond.Append("Funnymeme");

    //printf("[%x]\n", *StrFirst[0]);

    String SFF = StrFirst[0];
    String SSF = StrSecond[0];

    ASSERT_TEST(SFF == "Name");
    ASSERT_TEST(SSF == "Jeff");

    ASSERT_TEST(StrFirst.Len() == 2);
    ASSERT_TEST(StrSecond.Len() == 2);

    Array<String> Third = StrFirst + StrSecond;

    ASSERT_TEST(Third[0] == StrFirst[0]);
    ASSERT_TEST(Third.Len() == 4);
}