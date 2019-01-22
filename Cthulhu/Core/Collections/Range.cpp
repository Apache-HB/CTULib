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

#include "Range.h"

using namespace Cthulhu;

Array<I64> Range::ToArray() const 
{
    return Array<I64>(static_cast<U32>(End), [this](U32 I){ return I - End; });
}

String Utils::ToString(const Range& Data)
{
    return String("{ Start: {0}, End: {1}, Index: {2}").ArrayFormat({
        ToString(Data.Start),
        ToString(Data.End),
        ToString(Data.Idx)
    });
}