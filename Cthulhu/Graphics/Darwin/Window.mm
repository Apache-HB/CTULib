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

#include "Internal/Window.h"
#include "Internal/View.h"
#include "Graphics/Darwin/Path.h"
#include "Window.h"

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

#define WND(A) ((CthulhuWindow*)A)

MacWindow::MacWindow(
    const Dimensions& Dim,
    const String& Title
)
{
    Handle = [
        [CthulhuWindow alloc]
        initWithContentRect:NSMakeRect(Dim.X, Dim.Y, Dim.Width, Dim.Height)
            styleMask:NSWindowStyleMaskResizable | NSWindowStyleMaskClosable | NSWindowStyleMaskTitled
            backing:NSBackingStoreBuffered
            defer:NO
    ];

    [WND(Handle) setTitle:[NSString stringWithUTF8String:Title.CStr()]];

    CthulhuView* View = [[CthulhuView alloc] init];

    [WND(Handle) setContentView:View];
    [WND(Handle) setAcceptsMouseMovedEvents:YES];

    [WND(Handle) setHandle:this];
}

void MacWindow::Display()
{
    [WND(Handle) orderFrontRegardless];
    [WND(Handle) setRestorable:NO];
}

void MacWindow::SetDimensions(const Dimensions& Dim)
{
    [WND(Handle) setFrame:NSMakeRect(Dim.X, Dim.Y, Dim.Width, Dim.Height)
        display:YES
        animate:NO
    ];
}

Dimensions MacWindow::GetDimensions() const
{
    NSRect Ret = [WND(Handle) frame];
    return { 
        static_cast<U32>(Ret.origin.x), 
        static_cast<U32>(Ret.origin.y), 
        static_cast<U32>(Ret.size.width), 
        static_cast<U32>(Ret.size.height) 
    };
}

void MacWindow::Resize(const Size NewSize)
{
    SetDimensions({ Location(), NewSize });
}

Graphics::Size MacWindow::GetSize() const
{
    Dimensions Ret = GetDimensions();

    return { Ret.Width, Ret.Height };
}

void MacWindow::Move(const Point NewLocation)
{
    SetDimensions({ NewLocation, GetSize() });
}

Graphics::Point MacWindow::Location() const
{
    Dimensions Ret = GetDimensions();

    return { Ret.X, Ret.Y };
}

String MacWindow::Name() const
{
    return [[WND(Handle) title] UTF8String];
}

void MacWindow::Rename(const String& NewName)
{
    [WND(Handle) setTitle:[NSString stringWithUTF8String:NewName.CStr()]];
}

void MacWindow::TriggerRedraw()
{
    [WND(Handle).contentView setNeedsDisplay:YES];
}

#if 0

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

#define WINDOW(X) ((CTUWindow*)X)
#define VIEW(X) ((CTUView*)X)

namespace
{

Event NSToEvent(NSEvent* InEvent)
{

}

Graphics::Point NSToPoint(NSPoint& Point)
{
    return { static_cast<U32>(Point.x), static_cast<U32>(Point.y) };
}

}

@implementation CTUWindow

@synthesize Window;
@synthesize MouseLocation;

- (instancetype)initWithWindow:(const Dimensions*)size window:(MacWindow*)inWindow
{
    [super initWithContentRect:NSMakeRect(size->X, size->Y, size->Width, size->Height)
        styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
        backing:NSBackingStoreBuffered
        defer:NO
    ];

    MouseLocation = NSMakePoint(0, 0);

    Window = inWindow;

    auto* View = [CTUView newWithWindow:size window:inWindow];

    [self setContentView:View];
    [self setInitialFirstResponder:View];
    [self setNextResponder:View];
    [self makeFirstResponder:View];

    return self;
}

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

- (BOOL)isMovable
{
    return YES;
}

- (void)mouseDown:(NSEvent*)event
{
    Window->OnLeftMouseDown(NSToEvent(event));
}

- (void)mouseUp:(NSEvent*)event
{
    Window->OnLeftMouseUp(NSToEvent(event));
}



- (void)rightMouseDown:(NSEvent*)event
{
    Window->OnRightMouseDown(NSToEvent(event));
}

- (void)rightMouseUp:(NSEvent*)event
{
    Window->OnRightMouseUp(NSToEvent(event));
}



- (void)otherMouseDown:(NSEvent*)event
{
    Window->OnOtherMouseDown(NSToEvent(event));
}

- (void)otherMouseUp:(NSEvent*)event
{
    Window->OnOtherMouseUp(NSToEvent(event));
}



- (void)mouseMoved:(NSEvent*)event
{
    NSPoint OldLocation = MouseLocation;
    MouseLocation = [event locationInWindow];

    Window->OnMouseMove(NSToEvent(event), NSToPoint(OldLocation), NSToPoint(MouseLocation));
}

@end



@implementation CTUView

@synthesize Window;
@synthesize LastTick;

+ (instancetype)newWithWindow:(const Dimensions*)size window:(MacWindow*)inWindow
{
    auto Device = MTLCreateSystemDefaultDevice();

    auto* Ret = [
        [CTUView alloc]
        initWithFrame:CGRectMake(size->X, size->Y, size->Width, size->Height)
            device:Device
    ];

    Ret.Window = inWindow;

    timespec Temp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &Temp);
    Ret.LastTick = Temp;

    return Ret;
}

- (void)keyDown:(NSEvent*)event
{

}

- (void)keyUp:(NSEvent*)event
{

}

- (void)drawRect:(CGRect)rect
{
    timespec Now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &Now);

    U64 Diff = (Now.tv_sec - LastTick.tv_sec) * 1000000 + (Now.tv_nsec - LastTick.tv_nsec) / 1000;

    LastTick = Now;

    F64 RealDiff = (F64)Diff;

    printf("%lf\n", RealDiff / 1000000);

    Window->Tick(RealDiff / 1000000);
}

@end



@implementation CTUDelegate

@synthesize Window;

+ (instancetype)newWithWindow:(const Dimensions*)size window:(MacWindow*)inWindow
{
    auto* Ret = [[CTUDelegate alloc] init];

    Ret.Window = inWindow;

    [WINDOW(inWindow->Native()) setDelegate:Ret];

    return Ret;
}

@end

MacWindow::~MacWindow()
{
    [WINDOW(Handle) dealloc];
}

namespace
{
const Graphics::Dimensions DefaultSize = {0, 0, 400, 400};
}

MacWindow::MacWindow()
{
    Handle = [
        [CTUWindow alloc]
        initWithContentRect:NSMakeRect(100, 100, 400, 400)
        styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
        backing:NSBackingStoreBuffered
        defer:NO
    ];

    WINDOW(Handle).MouseLocation = NSMakePoint(0, 0);
    WINDOW(Handle).Window = this;

    [WINDOW(Handle) makeKeyAndOrderFront:nil];

    //[CTUDelegate newWithWindow:&DefaultSize window:this];
}

MacWindow::MacWindow(const String& Name)
{
    Handle = [
        [CTUWindow alloc]
        initWithWindow:&DefaultSize
            window:this
    ];
    
    [CTUDelegate newWithWindow:&DefaultSize window:this];

    Rename(Name);
}

MacWindow::MacWindow(const Dimensions& Size)
{
    Handle = [
        [CTUWindow alloc]
        initWithWindow:&Size
            window:this
    ];
    
    [CTUDelegate newWithWindow:&Size window:this];
}

void MacWindow::Rename(const String& NewName)
{
    [WINDOW(Handle) setTitle:[
        NSString stringWithUTF8String:NewName.CStr()]
    ];
}

String MacWindow::Title() const
{
    return { [[WINDOW(Handle) title] UTF8String] };
}

Dimensions MacWindow::GetDimensions() const
{
    return {
        Location(),
        GetSize()
    };
}

void MacWindow::SetDimensions(const Dimensions& NewSize)
{
    [WINDOW(Handle) setFrame:NSMakeRect(
        NewSize.X,
        NewSize.Y,
        NewSize.Width,
        NewSize.Height
    ) display:YES];
}

void MacWindow::Resize(const Graphics::Size NewSize)
{
    SetDimensions({ Location(), NewSize });
}

Graphics::Size MacWindow::GetSize() const
{
    NSSize OutSize = [WINDOW(Handle) frame].size;

    return {
        static_cast<U32>(OutSize.height),
        static_cast<U32>(OutSize.width)
    };
}

void MacWindow::Move(const Point NewLocation)
{
    SetDimensions({ NewLocation, GetSize() });
}

Graphics::Point MacWindow::Location() const
{
    NSPoint OutPoint = [WINDOW(Handle) frame].origin;

    return {
        static_cast<U32>(OutPoint.x),
        static_cast<U32>(OutPoint.y)
    };
}

void MacWindow::Hide()
{
    [WINDOW(Handle) orderOut:nil];
}

void MacWindow::Display()
{
    [WINDOW(Handle) makeKeyAndOrderFront:nil];
}

void MacWindow::HackToFront()
{
    [WINDOW(Handle) orderFrontRegardless];
}

void MacWindow::SetMinSize(const Graphics::Size NewSize)
{
    [WINDOW(Handle) setMinSize:NSMakeSize(NewSize.Width, NewSize.Height)];
}

Graphics::Size MacWindow::MinSize() const
{
    NSSize Out = [WINDOW(Handle) minSize];

    return {
        static_cast<U32>(Out.width),
        static_cast<U32>(Out.height)
    };
}

void MacWindow::SetMaxSize(const Graphics::Size NewSize)
{
    [WINDOW(Handle) setMaxSize:NSMakeSize(NewSize.Width, NewSize.Height)];
}

Graphics::Size MacWindow::MaxSize() const
{
    NSSize Out = [WINDOW(Handle) maxSize];

    return {
        static_cast<U32>(Out.width),
        static_cast<U32>(Out.height)
    };
}


#endif