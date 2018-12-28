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

#include "View.h"
#include "Window.h"

#import <MetalKit/MetalKit.h>
#import <Cocoa/Cocoa.h>
#import <Metal/MTLDevice.h>

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

@interface CTUView : MTKView
{
    @public MacView* ThisView;
}

@property(nonatomic) MacView* ThisView;

- (void)setView:(MacView*)newView;

@end

@interface CTUWindow : NSWindow
{
    @public MacWindow* Window;
}

@property(nonatomic) MacWindow* Window;

- (void)setWindow:(MacWindow*)newWindow;

@end
