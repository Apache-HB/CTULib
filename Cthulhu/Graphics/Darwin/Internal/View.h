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

#pragma once

#include "Graphics/Darwin/Window.h"

#import <Cocoa/Cocoa.h>

@interface CthulhuView : NSView
{
    NSTrackingArea* TrackingArea;
    @public Cthulhu::Graphics::MacWindow* Handle;
    @private Cthulhu::Graphics::ModifierKeys CurrentKeys;
             Cthulhu::String PressedKeys;
             NSPoint MouseLocation;
}

- (void)updateTrackingAreas;

@end
