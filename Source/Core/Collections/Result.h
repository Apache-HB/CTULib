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
        , ErrValid(false)
    {}

    /**Create a result with an error 
     * 
     */
    Result(TErr InErr)
        : Err(InErr)
        , ErrValid(true)
        , ResValid(false)
    {}

    /**
     * 
     */
    TErr ErrorOr(TErr Other) const { return (ErrValid) ? Err : Other; }
    
    /**
     * 
     */
    TRes ResultOr(TRes Other) const { return (ResValid) ? Res : Other; }

    /**
     * 
     */
    bool HasRes() const { return ResValid; }
    
    /**
     * 
     */
    bool HasErr() const { return !ResValid; }

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
     * 
     */
    void Fold(void(*ResHandle)(TRes), void(*ErrHandle)(TErr))
    {
        (ResValid) ? ResHandle(Res) : ErrHandle(Err);
    }
};

/**
 * 
 */
template<typename TRes, typename TErr>
Result<TRes, TErr> Pass(TRes Res) { return Result<TRes, TErr>(Res); }

/**
 * 
 */
template<typename TRes, typename TErr>
Result<TRes, TErr> Fail(TErr Err) { return Result<TRes, TErr>(Err); }

}