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

#include "Config/Reader.h"

namespace BLD = Cthulhu::Build;

int main(int argc, char const *argv[])
{
    printf("%s\n", argv[1]);
    auto Cfg = BLD::ReadConfig(argv[1]);
    for(const auto& I : Cfg.Data->Items())
    {
        printf("[%s]\n", I.First->CStr());

        auto Iter = **I.Second;

        for(const auto& A : Iter.Items())
        {
            printf("%s = %s\n", A.First->CStr(), A.Second->CStr());
        }
    }

    return 0;
}
