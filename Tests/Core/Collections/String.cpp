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

#include <stdio.h>

#define TEST(Expr) if(!(Expr)) { printf("Test failed: " __FILE__ ":%d", __LINE__); exit(1); }

#include <Core/Collections/CthulhuString.h>

using namespace Cthulhu;

void Ctor()
{
    //if these fail then its going to core dump
    String S;
    String S1 = '5';
    String S2 = "AAAA";
    String S3 = S2;
}

void Ops()
{
    // == op
    String S = "CCC";

    //compare against same string
    TEST(S == "CCC");

    //compare against self
    TEST(S == S);

    //shorter string
    TEST(!(S == "CC"));

    //longer string
    TEST(!(S == "CCCC"));

    //against nothing
    TEST(!(S == ""));

    //same length dif content
    TEST(!(S == "AAA"));

    //shorter dif content
    TEST(!(S == "AA"));

    //longer dif content
    TEST(!(S == "AAAAA"));


    // != op
    String A = "SSS";

    //same string
    TEST(!(A != "SSS"));

    //self
    TEST(!(A != A));

    TEST(A != "SS");

    TEST(A != "");

    TEST(A != "SSSS");

    TEST(A != "AA");

    TEST(A != "AAAA");

    // += op

    String S1 = "AAA";

    TEST(S1 == "AAA");
    S1 += "BBB";

    TEST(S1 == "AAABBB");
    
    S1 += 'C';
    TEST(S1 == "AAABBBC");

    // + op

    String S2 = "A";

    TEST(S2 + S2 == "AA");

    TEST(S2 + 'C' == "AC");

    // << op

    String S3 = "A";

    S3 << 5LL;

    TEST(S3 == "A5");
    
    S3 << true;
    TEST(S3 == "A5true");

    S3 << 5.5f;
    TEST(S3 == "A5true5.50");

    // / op
    String S4 = "Path";
    
#ifdef OS_WINDOWS
    TEST(S4 / "File.txt" == "Path\\File.txt");
#else
    TEST(S4 / "File.txt" == "Path/File.txt");
#endif

    // /= op

    String S5 = "Path";
    S5 /= "Thing";
    S5 /= "Dir";
    S5 /= "File.txt";

#ifdef OS_WINDOWS
    TEST(S5 == "Path\\Thing\\Dir\\File.txt");
#else
    TEST(S5 == "Path/Thing/Dir/File.txt");
#endif

    // * op

    String S6 = "A";

    auto* RS1 = *S6;
    //not really sure how to test this

    // [] op

    String S7 = "ABCDEF";

    TEST(S7[0] == 'A');
    TEST(S7[1] == 'B');
    S7[1] = 'C';
    TEST(S7 == "ACCDEF");

    // ""_S op

    TEST("Stuff"_S == "Stuff");

    // begin() end() not really ops but used in for range loops so they go here

    String S8 = "AAAAAAAAAA";

    for(char C : S8)
        TEST(C == 'A');
}

void Funs()
{
    String S1 = "AAA";
    TEST(S1.Len() == 3);

    String S2 = "";

    TEST(S2.IsEmpty());

    String S3 = "AAA";

    //bool()
    TEST(S3);

    String S4 = "AAA";

    TEST(S3.Equals(S4));

    String S5 = "AAA";

    TEST(S5 == "AAA");
    S5.Append("BBB");

    TEST(S5 == "AAABBB");

    S5.Append('C');
    TEST(S5 == "AAABBBC");

    String S6 = "AAA";
    S6.Push('BC');

    TEST(S6 == "BCAAA");

    S6.Push('D');

    TEST(S6 == "DBCAAA");

    String S6 = "Something";

    TEST(S6.StartsWith("Some"));

    TEST(S6.EndsWith("ing"));

    TEST(S6.ValidIndex(3));

    TEST(S6.At(5) == 'h');
}

int main()
{
    Ctor();
    Ops();
    Funs();
}