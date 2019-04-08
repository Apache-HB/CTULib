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

/**
 * @mainpage Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn
 * 
 * @section _1 What is this?
 * 
 * I got tired of some of the lacking elements in the C++
 * standard library such as lackluster string functions,
 * strange naming schemes and unreadable source code. 
 * So I decided to write my own stanrdard library to fix
 * some of these issues.
 * 
 * @section Why should I use this?
 * 
 * This library is not for everyone. But if you are used to
 * the java/python/C# standard library then this library may
 * provide functions you are more familliar with and hide some
 * of the nastyness that the C++ stdlib leaves exposed.
 * 
 * @section Quickstart guide
 * 
 * To use this library you must first get the source on your machine.
 * 
 * @subsection Cloning
 * Firstly clone the repo from github onto local
 * @code{.sh}
 * git clone https://github.com/Apache-HB/CTULib.git --depth 1
 * @endcode
 * into a folder of your choice (3rdparty, extern) inside your project.
 * 
 * @subsection Dependancy
 * The second option is to use git submodule add
 * @code{.sh}
 * git submodule add https://github.com/Apache-HB/CTULib.git 
 * @endcode
 * 
 * @section Building
 * To build the library navigate to its root directory `CTULib`
 * then run 
 * @code{.sh}
 * mkdir Build
 * cd Build
 * cmake .. [options]
 * make
 * @endcode
 * 
 * @section _2 Using the library
 * Firstly add the header files to the include path
 * this can be done with cmake 
 * @code{.cmake}
 * include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3RDParty/CTULib/Cthulhu)
 * @endcode
 * or directly
 * @code{.sh}
 * -L/3RDParty/CTULib/Cthulhu
 * @endcode
 * You then need to link to the binaries that were generated before
 * this can be done with either 
 * @code{.cmake}
 * target_link_libraries(ProjectName ${CMAKE_CURRENT_SOURCE_DIR}/3RDParty/CTULib/Build/libCthulhuCore.a)
 * @endcode
 * for cmake or 
 * @code{.sh}
 * -D/3RDParty/CTULib/Build/libCthulhuCore.a
 * @endcode
 * directly on the command line
 * 
 * And thats it!
 * So until the great old ones return you can code happily.
 */

#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Array.h"
#include "Core/Collections/Option.h"
#include "Core/Collections/Result.h"
#include "Core/Collections/Map.h"
#include "Core/Collections/Range.h"
#include "Core/Collections/Pair.h"