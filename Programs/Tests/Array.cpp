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

    for(U64 I = 0; I < 999; I++)
    {
        First.Append(I);
    }

    Array<U64> Second;
    Second.Append(15ULL);
    Second.Append(20ULL);

    First.Append(Second);

    Array<String> StrFirst;

    //FIXME: segfaults oh boy
    StrFirst.Append("Name");
    StrFirst.Append("is");

    Array<String> BigArr;
    
    for(I64 I = 0; I < 500; I++)
    {
        BigArr.Append(*(String("Num=") << I));
    }
    
    Array<String> StrSecond;

    StrSecond.Append("Jeff");
    StrSecond.Append("Funnymeme");

    String SFF = StrFirst[0];
    String SSF = StrSecond[0];

    ASSERT_TEST(SFF == "Name");
    ASSERT_TEST(SSF == "Jeff");

    ASSERT_TEST(StrFirst.Len() == 2);
    ASSERT_TEST(StrSecond.Len() == 2);

    Array<String> Temp = { "one", "two", "three", "four" };

    I32 Loop = 0;

    for(String& I : Temp)
    {
        if(Loop == 0)
        {
            ASSERT_TEST(I == "one");
        }
        else if(Loop == 1)
        {
            ASSERT_TEST(I == "two");
        }
        else if(Loop == 2)
        {
            ASSERT_TEST(I == "three");
        }
        else if(Loop == 3)
        {
            ASSERT_TEST(I == "four");
        }
        else 
        {
            ASSERT_TEST(false);
        }
        Loop++;
    }

    ASSERT_TEST(Loop == Temp.Len());
}