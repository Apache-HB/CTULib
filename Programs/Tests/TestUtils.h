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

#include <stdio.h>

//tiny testing framework, (just a few macros) to make testing this stuff 
//relativley easy

#define TEST_ASSERT(pass, expr) if(!(expr)) { pass = false; printf("Failed test %s at %d\n", __FILE__, __LINE__); }

#define TEST_BLOCK(pass, name, msg) if(!(name())) { pass = false; printf("Failed " msg " tests %s at %d\n", __FILE__, __LINE__); }

#define TEST_RETURN(pass, msg) if(pass) { return 0; } else { printf(msg" tests failed\n"); return 1; }