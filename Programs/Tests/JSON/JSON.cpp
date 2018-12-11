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

#include "../TestMacros.h"

#include <Core/Serialization/JSON.h>

using namespace Cthulhu;
using namespace Cthulhu::JSON;

int main()
{
    Map<String, Object> Data = 
    {
        { "Name", "Jeff" },
        { "Age", 25LL },
        { "Number", 64.4f }
    };

    Object A(&Data);

    String S = A.DumpObject();

    printf("%s\n", *S);
}