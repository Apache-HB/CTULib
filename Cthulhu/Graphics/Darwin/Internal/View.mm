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

#include "Window.h"

#include "View.h"

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

//so many things need to return YES that its quicker to have a macro
#define RYES(Func) - (BOOL)Func { return YES; }

ModifierKeys ModFromNS(NSEventModifierFlags Flags)
{
    ModifierKeys Ret{};

    if(Flags & NSEventModifierFlagCapsLock)
        Ret |= ModifierKeys::CapsLock;

    if(Flags & NSEventModifierFlagShift)
        Ret |= ModifierKeys::Shift;

    if(Flags & NSEventModifierFlagControl)
        Ret |= ModifierKeys::Control;

    if(Flags & NSEventModifierFlagOption)
        Ret |= ModifierKeys::Option;

    if(Flags & NSEventModifierFlagCommand)
        Ret |= ModifierKeys::Special;

    if(Flags & NSEventModifierFlagFunction)
        Ret |= ModifierKeys::Function;

    return Ret;
}

Event EventFromNS(NSEvent* Evt)
{   
    //Get the mouse location
    const NSPoint MouseLoc = [Evt locationInWindow];
    const Graphics::Point MouseLocation = { static_cast<U32>(MouseLoc.x), static_cast<U32>(MouseLoc.y) };

    //Get all the keys pressed
    const String KeysPressed = 
        ([Evt type] == NSEventTypeKeyDown || [Evt type] == NSEventTypeKeyUp) 
        ? [[Evt charactersIgnoringModifiers] UTF8String]
        : "";

    //get all modifier flags (option, ctrl, shift, etc)
    const ModifierKeys Flags = ModFromNS([Evt modifierFlags]);

    return { MouseLocation, KeysPressed, Flags };
}

@implementation CthulhuView

//all these RYES functions return YES, the macro is there so theres less to type
RYES(wantsUpdateLayer);
RYES(isOpaque);
RYES(canBecomeKeyView);
RYES(acceptsFirstResponder);

- (id)init
{
    //init the class
    self = [super init];
    TrackingArea = nil;
    [self updateTrackingAreas];
    //make sure all the tracking areas are cleaned up
    CurrentKeys = (ModifierKeys)0;
    MouseLocation = NSMakePoint(0, 0);
    //set these to some arbitrary default values
    return self;
}

- (void)dealloc
{
    //clean everything up
    [TrackingArea release];
    [super dealloc];
}

- (void)updateTrackingAreas
{
    if(TrackingArea != nil) 
    {
        [self removeTrackingArea:TrackingArea];
        [TrackingArea release];
    }

    NSTrackingAreaOptions Options = 
        NSTrackingMouseEnteredAndExited |
		NSTrackingActiveInKeyWindow |
		NSTrackingCursorUpdate |
		NSTrackingInVisibleRect;

    TrackingArea = [
        [NSTrackingArea alloc] 
        initWithRect:[self bounds]
            options:Options
            owner:self
            userInfo:nil
    ];

    [self addTrackingArea:TrackingArea];
    [super updateTrackingAreas];
}

- (void)drawRect:(NSRect)rect
{
    [[NSColor windowBackgroundColor] setFill];
    NSRectFill(self.bounds);
    auto Temp = MacDrawHandle();
    Handle->Draw(Temp);
}

- (void)keyDown:(NSEvent*)event
{
    //dont send repeat events from stuff like holding the key down for more than
    //a few seconds at a time
    if(![event isARepeat])
        Handle->KeyDown(EventFromNS(event));
}

- (void)keyUp:(NSEvent*)event
{
    Handle->KeyUp(EventFromNS(event));
}

- (void)mouseEntered:(NSEvent*)event
{
    Handle->MouseEntered(EventFromNS(event));
}

- (void)mouseExited:(NSEvent*)event
{
    Handle->MouseExited(EventFromNS(event));
}

- (void)mouseMoved:(NSEvent*)event
{
    NSPoint LastPoint = MouseLocation;
    MouseLocation = [event locationInWindow];
    Handle->MouseMoved(EventFromNS(event), 
        { static_cast<U32>(LastPoint.x), static_cast<U32>(LastPoint.y) }, 
        { static_cast<U32>(MouseLocation.x), static_cast<U32>(MouseLocation.y) }
    );
}

- (void)mouseDown:(NSEvent*)event
{
    Handle->MouseDown(EventFromNS(event));
}

- (void)mouseUp:(NSEvent*)event
{
    Handle->MouseUp(EventFromNS(event));
}

- (void)rightMouseDown:(NSEvent*)event
{
    Handle->MouseDown(EventFromNS(event));
}

- (void)rightMouseUp:(NSEvent*)event
{
    Handle->MouseUp(EventFromNS(event));
}

- (void)otherMouseDown:(NSEvent*)event
{
    Handle->MouseDown(EventFromNS(event));
}

- (void)otherMouseUp:(NSEvent*)event
{
    Handle->MouseUp(EventFromNS(event));
}

- (void)flagsChanged:(NSEvent*)event
{
    ModifierKeys Temp = CurrentKeys;
    CurrentKeys = ModFromNS([event modifierFlags]);
    
    //if currentkeys is greater than the last value then that means
    //that more flags are now active, meaning a key has been pressed
    //so we then call KeyDown instead of KeyUp
    if(Temp < CurrentKeys)
    {
        Handle->KeyDown(EventFromNS(event));
    }
    else
    {
        Handle->KeyUp(EventFromNS(event));
    }
}

@end

#undef RYES