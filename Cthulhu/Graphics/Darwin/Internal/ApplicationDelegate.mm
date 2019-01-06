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

#include <signal.h>

#include "ApplicationDelegate.h"
#include "Graphics/Darwin/Internal/Globals.h"


void Handler(int)
{
    //tell the user that we crashed, the kind of crash doesnt matter
    EventHandler(MainLoopEvent::Crash);
}

@implementation CthulhuApplicationDelegate

+ (void)focusApp
{
    NSRunningApplication* App = [NSRunningApplication runningApplicationsWithBundleIdentifier:@"com.apple.dock"][0];
    [App activateWithOptions:NSApplicationActivateIgnoringOtherApps];
    //force dock to take focus, this is needed otherwise TransformProcessType will fail
    
    [NSThread sleepForTimeInterval:0.02];
    //give the OS some time to catch up because apple is funny like that
    
    ProcessSerialNumber SerialNumber = { 0, kCurrentProcess };
    (void)TransformProcessType(&SerialNumber, kProcessTransformToForegroundApplication);
    //register the current application as a foreground proccess

    [NSThread sleepForTimeInterval:0.02];
    //give the OS some more time to catch up

    [[NSRunningApplication currentApplication] activateWithOptions:NSApplicationActivateIgnoringOtherApps];
    //now make the current app take focus
}

- (void)applicationDidFinishLaunching:(NSNotification*)notify
{
    NSString* BundleName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"];
    //if were not running in a bundle, force the app to focus (BundleName is nil if not bundled)
    if(BundleName == nil)
        [CthulhuApplicationDelegate focusApp];

    //Register callbacks for the crash handler
    struct sigaction Action;
    Action.sa_handler = Handler;
    sigemptyset(&Action.sa_mask);
    Action.sa_flags = 0;
    
    sigaction(SIGTERM, &Action, nullptr);
    sigaction(SIGSEGV, &Action, nullptr);
    sigaction(SIGTRAP, &Action, nullptr);
    sigaction(SIGBUS, &Action, nullptr);
    //everything has finished init'ing, let the user start doing stuff
    EventHandler(MainLoopEvent::Launch);
}

@end
