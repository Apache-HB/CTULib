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

#include "Core/Types/Lambda.h"
#include "Meta/Assert.h"

#pragma once

namespace Cthulhu
{

template<typename TRes, typename TErr>
struct Result
{
    template<typename TORes, typename TOErr>
    friend Result<TORes, TOErr> Pass(TORes Value);

    template<typename TORes, typename TOErr>
    friend Result<TORes, TOErr> Fail(TOErr Error);

    bool Valid() const { return !HasError; }
    operator bool() const { return !HasError; }

    TRes Value() const { ASSERT(!HasError, "Attempting to take a value when there was no value"); return Val; }
    TErr Error() const { ASSERT(HasError, "Attempting to take an error when there was no error"); return Err; }

    template<typename TRet>
    TRet Fold(Lambda<TRet(TRes)> Success, Lambda<TRet(TErr)> Fail) const
    {
        return (HasError) ? Success(Val) : Fail(Err);
    }

private:
    //TODO: make this work with stuff that doesnt have default constructors
    //TODO: also make it work with stuff with non-trivial destructors
    Result(TRes Input)
        : Val(Input)
        , HasError(false)
        , Err()
    {}

    //The flag is here to stop clashing contructor signatures
    //ie
    //Result<int, int> would cause problems because it wouldnt know which
    //constructor to choose, so the flag is there to alleviate that
    Result(TErr InError, char)
        : Err(InError)
        , HasError(true)
        , Val()
    {}

    bool HasError;
    TRes Val;
    TErr Err;
};

template<typename TORes, typename TOErr>
Result<TORes, TOErr> Pass(TORes Value) { return Result<TORes, TOErr>(Value); }

template<typename TORes, typename TOErr>
Result<TORes, TOErr> Fail(TOErr Error)    
{
    return Result<TORes, TOErr>(Error, '\0');
    //                                 ^^^^
    //the char there is dead and is only needed to distinguish constructors
    //when TRes is the same type as TErr
}

} //Cthulhu
