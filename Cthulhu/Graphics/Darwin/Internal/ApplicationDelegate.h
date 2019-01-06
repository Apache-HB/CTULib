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

#import <Cocoa/Cocoa.h>

/**overloaded application delegate that fixes some of apples 
 * library "qwerks" (they cant code for shit so other people have to fix it for them)
 */
@interface CthulhuApplicationDelegate : NSObject<NSApplicationDelegate> {}

/**force this application into focus
 * mac by default is fucking stupid and doesnt do this for you, so you have to 
 * beat it over the head until it works 
 */
+ (void)focusApp;

@end

