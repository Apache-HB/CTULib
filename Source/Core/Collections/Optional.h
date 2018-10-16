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

#include "Meta/Macros.h"
#include "Core/Types/Lambda.h"

#pragma once

namespace Cthulhu
{

/**A template to represent an optional or "nullable" type
 * useful for representing success without setting global variables
 * 
 * This struct has no option to take the content directly as
 * this would promote unsafe code that may have undefined behaviour
 * 
 * @code{.cpp}
 * 
 * Optional<bool> Fun() { return NullOpt<bool>(); }
 * 
 * Fun().Valid();
 * //false
 * 
 * Optional<bool> AnotherFun() { return Optional<bool>(false); }
 * 
 * AnotherFun().Valid();
 * //true
 * 
 * AnotherFun().Or(true);
 * //false
 * 
 * @endcode
 * 
 */
template<typename T>
class Optional
{
    /**The content held inside this optional
     * 
     */
    T Content;

    /**Determines whether the content is set or not
     * false if not set
     * true otherwise
     * this prevents undefined behaviour from accessing an unset object
     */
    bool IsValid;

public:

    /**Construct an optional with data in it
     * 
     * @param InContent the content to store in the optional
     * 
     */
    Optional(T InContent)
        : Content(InContent)
        , IsValid(true)
    {}

    /**Construct an empty optional that holds no data and isnt valid
     * 
     */
    Optional()
        : IsValid(false)
    {}
    
    /**Fetch the data from the current optional, 
     * or the provided data if the data isnt set
     * 
     * @code{.cpp}
     * 
     * Optional<bool> B = Optional<bool>(true);
     * Optional<bool> C = NullOpt<bool>();
     * 
     * B.Or(false);
     * // true
     * 
     * C.Or(false);
     * // false
     * 
     * @endcode
     * 
     * @param Other the data to return if the content isnt valid
     * 
     * @return  content if its valid, otherwise the Other argument
     */
    T Or(T Other) const { return (IsValid) ? Content : Other; }

    /**Overloaded bool() cast
     * 
     * @code{.cpp}
     * 
     * Optional<float> F = SomeFunction();
     * 
     * if(F)
     * {
     *     //F has content
     * }
     * else
     * {
     *     //F has no content
     * }
     * 
     * @endcode
     * 
     * @return bool is the content valid or not
     * 
     */
    ALWAYSINLINE operator bool() const { return IsValid; }

    /**Checks if the object is valid or not
     * 
     * Optional<float> F = SomeFunction();
     * 
     * bool IsValid = F.Valid();
     * 
     * if(IsValid)
     * {
     *     //Content is valid
     * }
     * else
     * {
     *     //Content isnt valid
     * }
     * 
     * @return bool is the content valid or not
     */
    ALWAYSINLINE bool Valid() const { return IsValid; }

    void WhenValid(Lambda<void(T)> Callback) const { if(IsValid) Callback(Content); }

    void WhenInvalid(Lambda<void()> Callback) const { if(!IsValid) Callback(); }

    //TODO: redoc with 3-4 examples
    /**Functionally fold the result between 2 functions
     * 
     * @code{.cpp}
     * 
     * Optional<float> F = SomeFunction();
     * 
     * F.Fold([](float F){
     *     //there is content
     *     //do something with the content
     * }, [](){
     *     //there was no content
     *     //do something else
     * });
     * 
     * @endcode
     * 
     * @param WhenValid the function to execute when the optional has content
     * @param Otherwise the function to execute when the optional is empty
     * @param TRet      the return type of the fold
     * 
     */
    template<typename TRet = void>
    TRet Fold(Lambda<TRet(T)> WhenValid, Lambda<TRet()> Otherwise)
    {
        return (IsValid) ? WhenValid(Content) : Otherwise();
    }
};

/**Returns a empty optional of any type
 * equivilent to Optional<T>();
 * 
 * @code{.cpp}
 * 
 * Optional<bool> B = NullOpt<bool>();
 * 
 * B.Valid();
 * // false
 * 
 * @endcode
 * 
 * @param T the type of the optional
 * 
 * @return the empty optional
 */
template<typename T>
Optional<T> NullOpt() { return Optional<T>(); }

}

#endif