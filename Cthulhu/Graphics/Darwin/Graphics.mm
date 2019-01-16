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
















#if 0

#include "Graphics.h"

using namespace Cthulhu;

@implementation CTUAppDelegate

@synthesize Callback;

+ (instancetype)newWithLambda:(Lambda<void()>*)callback
{
    auto* App = [CTUAppDelegate alloc];
    App.Callback = callback;
    return App;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notify
{
    ProcessSerialNumber Serial = { 0, kCurrentProcess };
    TransformProcessType(&Serial, kProcessTransformToForegroundApplication);

    self.Callback->Apply();
}

@end

void Cthulhu::Graphics::Run(Lambda<void()> Callback)
{
    [NSApp setDelegate:[CTUAppDelegate newWithLambda:&Callback]];
    [NSApp run];
}

@interface TWindow : NSWindow
{
    MacWindow* Window;
}

@property(nonatomic) MacWindow* Window;

+ (instancetype)newWithWindow/*:(MacWindow*)window dimensions*/:(const Dimensions)size;

@end

@implementation TWindow 

@synthesize Window;

+ (instancetype)newWithWindow/*:(MacWindow*)window dimensions*/:(const Dimensions)size
{
    TWindow* Ret = [
        [TWindow alloc]
        initWithContentRect:NSMakeRect(size.X, size.Y, size.Width, size.Height)
            styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
            backing:NSBackingStoreBuffered
            defer:NO
    ];

    return Ret;
}

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

@end

@interface TView : MTKView
{
    MacWindow* Window;
}

@property(nonatomic) MacWindow* Window;

@end

@implementation TView

@synthesize Window;

@end

@interface TAppDelegate : NSObject<NSApplicationDelegate>
@end

@implementation TAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notify
{
    //ProcessSerialNumber Serial = { 0, kCurrentProcess };
    //TransformProcessType(&Serial, kProcessTransformToForegroundApplication);
}

@end

void Cthulhu::Graphics::Test()
{
    auto* Window = [TWindow newWithWindow:{100, 100, 400, 400}];

    /*auto* Window = [
        [TWindow alloc]
        initWithContentRect:NSMakeRect(0, 0, 400, 400)
            styleMask:NSWindowStyleMaskResizable | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable
            backing:NSBackingStoreBuffered
            defer:NO
    ];*/

    [Window setTitle:@"Name jeff"];

    auto* View = [
        [TView alloc]
        initWithFrame:NSMakeRect(0, 0, 400, 400)
    ];

    //[Window makeFirstResponder:View];

    [Window makeKeyAndOrderFront:nil];

    [NSApp setDelegate:[TAppDelegate new]];
    [NSApp run];
}

#endif