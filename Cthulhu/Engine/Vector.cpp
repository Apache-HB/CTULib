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

#include "Vector.h"
#include "Core/Collections/Array.h"

using namespace Cthulhu;
using namespace Cthulhu::Engine;

String Utils::ToString(const Vector<2> Vec)
{
    return String("X = {0}, Y = {1}").ArrayFormat({ Utils::ToString(Vec.X), Utils::ToString(Vec.Y) });
}

String Utils::ToString(const Vector<3> Vec)
{
    return String("X = {0}, Y = {1}, Z = {2}").ArrayFormat({ 
        Utils::ToString(Vec.X),
        Utils::ToString(Vec.Y),
        Utils::ToString(Vec.Z)
    });
}

String Utils::ToString(const Vector<4> Vec)
{
    return String("X = {0}, Y = {1}, Z = {2}, A = {3}").ArrayFormat({
        Utils::ToString(Vec.X),
        Utils::ToString(Vec.Y),
        Utils::ToString(Vec.Z),
        Utils::ToString(Vec.A)
    });
}