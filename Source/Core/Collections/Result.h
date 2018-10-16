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

#if 0

#include "Optional.h"

#pragma once

//TODO document

namespace Cthulhu
{

/**A result class simmilar to rusts io::Result<T, Err> class
 * https://doc.rust-lang.org/std/io/type.Result.html
 * Will only ever store an error or a result, never both for reasons
 * of simplicity
 * 
 * @code{.cpp}
 * 
 * Result<float, float> F = SomeFunction();
 * 
 * if(F.HasErr())
 * {
 *     //Has an error
 * }
 * else
 * {
 *     //Has no error
 * }
 * 
 * @endcode
 * 
 * @param TRes  the type of the return result
 * @param TErr  the type of the error result
 */
template<typename TRes, typename TErr>
class Result
{
    /**
     * The possible result
     */
    TRes Res;
    
    /**
     * is the result valid?
     * True if the result is valid, false if the error is valid
     */
    bool ResValid;


    /**
     * The possible error
     */
    TErr Err;

public:

    /**Create a result with a result value (not another result)
     * 
     */
    Result(TRes InRes)
        : Res(InRes)
        , ResValid(true)
    {}

    /**Create a result with an error 
     * 
     */
    Result(TErr InErr, bool)
        : Err(InErr)
        , ResValid(false)
    {}

    /**Return either the error if there is one, otherwise a preset value
     * 
     */
    TErr ErrorOr(TErr Other) const { return (!ResValid) ? Err : Other; }
    
    /**Return either the result if there is one, or a preset value otherwise
     * 
     */
    TRes ResultOr(TRes Other) const { return (ResValid) ? Res : Other; }

    /**Check if there is a result
     * 
     */
    bool HasRes() const { return ResValid; }
    
    /**Check if there is an error
     * 
     */
    bool HasErr() const { return !ResValid; }

    //TODO: redoc 3-4 examples
    /**Functionally fold the success or error using 2 functions
     * this allows you to handle success or failure in one function call
     * 
     * @code{.cpp}
     * 
     * Result<bool, int> Res = SomeFunction();
     * 
     * Res.Fold([](bool B) {
     *     //Result was valid
     *     //Do something with result here
     * }, [](int I) {
     *     //Result was invalid
     *     //Handle error here
     * });
     * 
     * @endcode
     * 
     * @param ResHandle     the function to execute if theres a result
     * @param ErrHandle     the function to execute if theres an error
     * @param TRet          the return type of the function
     *                      useful for assigning values based on success with more complex 
     *                      logic than ResultOr or ErrorOr can provide
     * 
     */
    template<typename TRet = void>
    TRet Fold(Lambda<TRet(TRes)> ResHandle, Lambda<TRet(TErr)> ErrHandle)
    {
        return (ResValid) ? ResHandle(Res) : ErrHandle(Err);
    }
};

/**Create a Result with valid data, more readable than the raw contructor
 * 
 * @code{.cpp}
 * 
 * Result<bool, float> Function(bool Flag)
 * {
 *     if(Flag)
 *     {
 *         return Pass<bool, float>(true);
 *     }
 *     else
 *     {
 *         return Fail<bool, float>(25.3);
 *     }
 * }
 * 
 * @endcode
 * 
 * @param TRes      The type of result 
 * @param TErr      The type of error
 * @param Res       The value of the result
 * 
 * @return          The constructed result with content
 */
template<typename TRes, typename TErr>
Result<TRes, TErr> Pass(TRes Res) { return Result<TRes, TErr>(Res); }

/**Create a result with an error, more readable than the raw constructor
 * 
 * @code{.cpp}
 * 
 * Result<bool, int> Function(bool Flag)
 * {
 *     if(Flag)
 *     {
 *         return Pass<bool, int>(Flag);
 *     }
 *     else
 *     {
 *         return Fail<bool, int>(25);
 *     }
 * }
 * 
 * auto T = Function(false);
 * 
 * @endcode
 * 
 * @param TRes  the type of result it should have returned
 * @param TErr  the type of the error
 * @param Err   the error to fail with
 * 
 * @return      the result containing the error
 */
template<typename TRes, typename TErr>
Result<TRes, TErr> Fail(TErr Err) { return Result<TRes, TErr>(Err, false); }

}

#endif