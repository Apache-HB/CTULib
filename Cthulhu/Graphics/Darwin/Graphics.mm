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

#include <Cocoa/Cocoa.h>

#include "Internal/ApplicationDelegate.h"
#include "Graphics/Darwin/Internal/View.h"
#include "Graphics/Darwin/Internal/Globals.h"

#include "Graphics.h"

#include <time.h>

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

void Cthulhu::Graphics::Setup()
{
    ASSERT_NO_REENTRY("Calling Graphics::Setup() more than once is uneccasery");
    //this initializes the global shared application, this has to be done 
    //before any other NS stuff is done
    [NSApplication sharedApplication];
}

void Cthulhu::Graphics::Run(Lambda<void(MainLoopEvent)> Callback)
{
    //register the callback for event handling
    EventHandler = Callback;

    //set the application delegate to ensure the window focuses
    CthulhuApplicationDelegate* AppDelegate = [[CthulhuApplicationDelegate alloc] init];
    [NSApp setDelegate:AppDelegate];

    //run the app (this is blocking)
    [NSApp run];
    
}
