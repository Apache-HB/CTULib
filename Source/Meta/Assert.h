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

#ifdef CTU_DEBUG
#   define ASSERT(Expr, Message) if(!(Expr)) { printf("ASSERT FAILED: "Message" |%s|%d|\n", __FILE__, __LINE__); exit(25); }
#   define ASSERT_NO_ENTRY(Message) { printf("REACHED NO ENTRY: "Message" |%s|%d|\n", __FILE__, __LINE__); exit(25); }
#else
#   define ASSERT(Expr, Message) Expr
#endif
