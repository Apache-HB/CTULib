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

#include <Graphics/Window.h>
#include <Graphics/View.h>

using namespace Cthulhu::Graphics;

int main(int argc, const char* argv[])
{
    //make window
    Window W{{100, 100, 400, 400}};

    View V = View({100, 100, 400, 400});

    V.MouseUp([](Event){
        printf("MouseUp\n");
    });

    V.MouseDown([](Event){
        printf("MouseDown\n");
    });

    V.KeyUp([](Event){
        printf("KeyUp\n");
    });

    V.KeyDown([](Event){
        printf("KeyDown\n");
    });

    W.SetView(&V);
    W.SetTitle("Name jeff");
    W.Display();

    //Run event loop
    Run([]{});
}