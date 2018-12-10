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

namespace Cthulhu
{

/**
 * @brief A type to represent a pair of values
 * 
 * @description cuts down on boilerplate code as you can do
 * 
 * @code{.cpp}
 * 
 * using Person = Pair<String, I32>;
 * 
 * @endcode
 * 
 * instead of
 * 
 * @code{.cpp}
 * 
 * struct Person
 * {
 *     String First;
 *     I32 Second;
 * };
 * 
 * @endcode
 * 
 * @tparam TFirst the first item in the pair
 * @tparam TSecond the second item in the pair
 */
template<typename TFirst, typename TSecond>
struct Pair
{
    TFirst First;
    TSecond Second;
};

/**
 * @brief A type that represents a trio of values 
 * 
 * @description as most libraries have a disturbing lack of this type
 * allows you to further cut down on boilerplate code with using statements instead of structs
 * 
 * @code{.cpp}
 * 
 * using Human = Triplet<String, I32, float>;
 * //                    ^^^^^^  ^^^  ^^^^^
 * // Name --------------/       |    |
 * // Age -----------------------/    |
 * // Gender -------------------------/
 * 
 * @endcode
 * 
 * instead of 
 * 
 * @code{.cpp}
 * 
 * using Human = Pair<String, Pair<I32, float>>;
 * 
 * // or
 * 
 * struct Human
 * {
 *     String Name;
 *     I32 Age;
 *     float Gender;
 * };
 * 
 * @endcode
 * 
 * @tparam TFirst the first type 
 * @tparam TSecond the second type
 * @tparam TThird the third type
 */
template<
    typename TFirst,
    typename TSecond,
    typename TThird
>
struct Triplet
{
    TFirst First;
    TSecond Second;
    TThird Third;
};

} //Cthulhu