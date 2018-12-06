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

#include "TestMacros.h"

#include <Core/Serialization/Hashes.h>
#include <Core/Serialization/Stringify.h>
#include <Core/Collections/Map.h>
#include <Core/Collections/Array.h>

#include <Core/Serialization/JSON.h>

using namespace Cthulhu;

int main()
{
    setbuf(stdout, NULL);

    //test const char* constructor
    String A = "A";

    //test operator*
    char* T = *A;

    //test operator[]
    ASSERT_TEST(A[0] == 'A');

    //test operator+=(char) and Append(char)
    A += 'B';

    ASSERT_TEST(A[0] == 'A' && A[1] == 'B');

    //test operator+=(String&) and Append(String&)
    A += "CD";

    //printf("%s\n", *A);

    //test Len()
    ASSERT_TEST(A.Len() == 4);

    //test char constructor
    String B = 'A';

    //test default constructor
    String C;

    //test copy constructor
    String D = A;
    D = "BCCD";
    ASSERT_TEST(D == "BCCD");

    //test IsEmpty() and operator bool()
    ASSERT_TEST(C.IsEmpty());
    ASSERT_TEST((bool)C);

    //test operator==(String&)
    ASSERT_TEST(D == "BCCD");

    //test operator!=(String&)
    ASSERT_TEST(D != "SDASDASD");
    ASSERT_TEST(D != "");
    ASSERT_TEST(D != "A");
    ASSERT_TEST(D != "ABCC");

    //test Push(char)
    B.Push('C');
    
    ASSERT_TEST(B == "CA");

    //test Push(String&)
    B.Push("CC");

    ASSERT_TEST(B == "CCCA");

    //test StartsWith(String&)
    ASSERT_TEST(B.StartsWith("CC"));
    ASSERT_TEST(!B.StartsWith("AAAAAAAAA"));
    ASSERT_TEST(B.StartsWith("C"));
    ASSERT_TEST(!B.StartsWith("c"));
    ASSERT_TEST(!B.StartsWith('D'));

    //printf("%s\n", *B);
    ASSERT_TEST(B.EndsWith("CA"));
    ASSERT_TEST(!B.EndsWith("HJGJGGASD"));

    ASSERT_TEST(B.ValidIndex(2));
    ASSERT_TEST(!B.ValidIndex(6));

    ASSERT_TEST(B.At(2) == 'C');
    ASSERT_TEST(B.At(6) == '\0');

    auto Sub = B.SubString(1, 2);

    String E = "abcdefjhgshdfjksdf";

    auto C1 = E.Cut(2);
    auto C2 = E.Cut(3);

    //printf("%s %x\n", *Sub, *Sub);
    //printf("%s %x\n", *B, *B);

    ASSERT_TEST(Sub == "CC");
    ASSERT_TEST(B.Find("CC").Valid());
    ASSERT_TEST(B.Find("CC").Get() == 0);

    ASSERT_TEST(B.Lower() == "ccca");
    ASSERT_TEST(String("abcdef").Upper() == "ABCDEF");

    ASSERT_TEST(String("bbb").Drop(2) == "b");
    //ASSERT_TEST(String("aaa").Cut(2) == "a");

    ASSERT_TEST(String("  name  ").Trim() == "name");
    ASSERT_TEST(String("aaanameaaa").Trim("aaa") == "name");
    String Temp = "myaaanameaaajeff";
    //printf("%s\n", *Temp);
    String Rep = Temp.Replace("aaa", ' ');
    //printf("%s\n", *Rep);

    ASSERT_TEST(Rep == "my name jeff");

    Map<String, String> FmtArgs = {
        { "name", "jeff" }
    };

    //ASSERT_TEST(String("my name is {name}").Format(FmtArgs) == "my name is jeff");

    Array<String> FmtArr = {
        "first", "middle", "last"
    };

    String Fmt = String("my name is {0}.{1}.{2}").ArrayFormat(FmtArr);

    ASSERT_TEST(Fmt == "my name is first.middle.last");

    return 0;
}