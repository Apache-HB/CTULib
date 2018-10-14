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

#include "Core/Types/Lambda.h"

using Cthulhu::Lambda;

bool Jeff(Lambda<bool(bool)> Fun) { return Fun(true); }

bool TestLambda()
{
    bool Pass = true;
    
    Lambda<bool(bool)> L = Lambda([](bool B){ return B; })

    //Jeff([Pass](bool B){ return B && Pass; });

    return Pass;
}

int main(int argc, char const *argv[])
{
    bool Pass = true;
    TEST_BLOCK(Pass, TestLambda, "lambda");
    
    TEST_RETURN(Pass, "lambda");
}
