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

#include "Exit.h"

using namespace Cthulhu;
using namespace Cthulhu::Standard;

namespace Private
{

void ExitStub(U16){}

}

Cthulhu::Lambda<void(U16)> Cthulhu::Standard::ExitCallback = ::Private::ExitStub;

void Cthulhu::Standard::OnExit(Cthulhu::Lambda<void(U16)> Function)
{
    ExitCallback = Function;
}

void Cthulhu::Standard::Exit(U16 Code)
{
    ExitCallback(Code);
    //exit?
}