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

/**Assertion macros simmilar to C's assert macro
 * https://www.tutorialspoint.com/c_standard_library/c_macro_assert.htm
 * rusts debug_assert! macro
 * https://doc.rust-lang.org/std/macro.debug_assert.html
 * or pythons "assert" keyword
 * https://wiki.python.org/moin/UsingAssertionsEffectively
 * 
 * these asserts are disabled when building a release build
 * when building for debug an assert will exit the program if fired and print to stdout
 * where the error occured
 */

/**Assert an expression to be true and otherwise, print the message and exit with code 25
 * Is disabled when building without CTU_DEBUG, but the expression is still evalulated
 * 
 * @code{.cpp}
 * 
 * int A = 5;
 * int B = 6;
 * 
 * ASSERT(A == B, "A did not equal B, A must equal B");
 * //Errors here
 * 
 * @endcode
 * 
 * @code{.cpp}
 * 
 * bool B = true;
 * 
 * ASSERT(B, "B must be true");
 * //Doesn't error
 * 
 * @endcode
 * 
 * int X = 5;
 * 
 * ASSERT(++X == 6, "X must equal 6");
 * //Expands to if(++X == 6) {...} with CTU_DEBUG
 * //Or
 * //Expands to ++X == 6; without CTU_DEBUG
 * 
 * @code{.cpp}
 * 
 * @param Expr      the boolean expression to be evaluated
 * @param Message   the message to print if the assertion fails
 * 
 */
//ASSERT(Expr, Message)


/**Denotes code paths that should never be reached
 * 
 * @code{.cpp}
 * 
 * int X = 5;
 * 
 * switch(X)
 * {
 *     case 3:
 *         printf("X was 3\n");
 *         break;
 *     case 4:
 *         printf("X was 4\n");
 *         break;
 *     case 5:
 *         printf("X was 5\n");
 *         break;
 *     default:
 *         ASSERT_NO_ENTRY("X must be 3, 4 or 5");
 *         break;
 * }
 * //Assert would fire here
 * 
 * @endcode
 * 
 * @param Message       the message to print if the code was reached
 * 
 */
//ASSERT_NO_ENTRY(Message)

/**Denotes a code path that should only ever be entered once
 * 
 * @code{.cpp}
 * 
 * void Init()
 * {
 *     //Do init'ing stuff
 *     ASSERT_NO_REENTRY("Init should only ever be called once")
 * }
 * 
 * Init();
 * //Fine
 * 
 * Init();
 * //Asserts and exits
 * 
 * @endcode
 * 
 * @param Message       the message to print if the code was called more than once
 * 
 */
//ASSERT_NO_REENTRY(Message)


//move the docs outside this ifdef block because big grey'd out sections make vscode lag alot
#ifdef CTU_DEBUG
#   define ASSERT(Expr, Message) if(!(Expr)) { printf("ASSERT FAILED: "Message" |%s|%d|\n", __FILE__, __LINE__); exit(25); }
#   define ASSERT_NO_ENTRY(Message) { printf("REACHED NO ENTRY: "Message" |%s|%d|\n", __FILE__, __LINE__); exit(25); }
#   define ASSERT_NO_REENTRY(Message) {                                         \
                                        static bool REACHED__##__LINE__ = false; \
                                        if(REACHED__##__LINE__)                   \
                                        {                                          \
                                            printf("REACHED NO REENTRY: "Message" |%s|%d|\n", __FILE__, __LINE__); \
                                            exit(25); \
                                        } \
                                        REACHED__##__LINE__ = true; \
                                       }
#else
#   define ASSERT(Expr, Message) Expr   //just execute the expression without debug
                                        //all C++ compilers *should* optimise it out
                                        //looking at you MSVC

#   define ASSERT_NO_ENTRY(Message)     //Expands to nothing without debug

#   define ASSERT_NO_REENTRY(Message)   //also expands to nothing
#endif
