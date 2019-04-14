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

#define STR(X) #X
#define TEST(Expr) if(!(Expr)) { printf("Test failed: " __FILE__ ":" STR(__LINE__)); exit(1); }

#include <Core/Collections/CthulhuString.h>

void CTor()
{

}

void Ops()
{

}

int main()
{
    TEST(false);
}