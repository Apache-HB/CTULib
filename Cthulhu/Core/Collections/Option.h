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

#include "CthulhuString.h"
#include "Cthulhu/Core/Types/Lambda.h"
#include "Cthulhu/Meta/Assert.h"

#pragma once

namespace Cthulhu
{

/**A template that represents an optional or nullable type
 * Using this template makes a return type more explicit as 
 * you no longer need to return an arbitrary value such as -1
 * 
 * @tparam T    the type this option has
 */
template<typename T>
struct Option
{
    /**
     * @brief A named constructor for making an option type with a value
     * 
     * @tparam TOpt the type of the Option to create
     * @param Real the data to store in the Option
     * @return Option<TOpt> the created Option with data
     */
    template<typename TOpt>
    friend Option<TOpt> Some(TOpt Real);

    /**
     * @brief A named constructor for making an option type without a value
     * 
     * @tparam TOpt the type the option should have
     * @return Option<TOpt> the created empty Option
     */
    template<typename TOpt>
    friend Option<TOpt> None();

    /**
     * @brief Check if the option has data
     * 
     * @return true the option has data in it
     * @return false the option is empty
     */
    bool Valid() const { return IsSet; }

    /**
     * @brief Check if the option has data
     * identical to Valid
     * 
     * @see Valid()
     * 
     * @return true the option has data
     * @return false the option is empty
     */
    operator bool() const { return IsSet; }

    /**
     * @brief Get the data as readonly from the option
     * will fire an assert if the option is empty
     * 
     * @return const T the readonly data of this object
     */
    const T Get() const { ASSERT(Valid(), "Attempting to Get() unset content is undefined behaviour"); return Content; }

    /**
     * @brief Get the data from the option
     * will fire an assert if the option is empty
     * 
     * @return T the data of this object
     */
    T Get() { ASSERT(Valid(), "Attempting to Get() unset content is undefined behaviour"); return Content; }

    /**
     * @brief get the data if its valid, otherwise return a default value
     * 
     * @param Other the data to fallback to return
     * @return T the data if its valid, otherwise Other
     */
    T Or(T Other) { return Valid() ? Content : Other; }

    /**
     * @brief functionally fold the option using lambdas
     * simmilar to the option class from <a href="https://github.com/gojuno/koptional">this kotlin repo</a>
     * 
     * @tparam TRet the type the function will return
     * @param WhenValid the function that is called when the data exists
     * @param Otherwise the function this is called when the option is empty
     * @return TRet the return value of either WhenValid or Otherwise
     */
    template<typename TRet>
    TRet Fold(Lambda<TRet(T)> WhenValid, Lambda<TRet()> Otherwise) const
    {
        return (IsSet) ? WhenValid(Content) : Otherwise();
    }

private:
    T Content;
    bool IsSet;
    
    Option()
        : IsSet(false)
    {}

    Option(T Item)
        : Content(Item)
        , IsSet(true)
    {}
};

template<typename TOpt>
Option<TOpt> Some(TOpt Input) { return Option<TOpt>(Input); }

template<typename TOpt>
Option<TOpt> None() { return Option<TOpt>(); }

namespace Utils
{
    template<typename T>
    String ToString(const Option<T> Item)
    {
        return Item.Valid() ? String("Some({})").Replace("{}", ToString(Item.Get())) : String("None()");
    }
}

} // Cthulhu

