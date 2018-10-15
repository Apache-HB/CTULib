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

#include "Core/Collections/Result.h"
#include "File.h"

#pragma once


//TODO implement
namespace Cthulhu
{

/**
 * 
 */
enum class FileError : char
{
    None = 0,
    NotFound = 1,
    Busy = 2,
    TooLong = 3,
    Permission = 4,
};

enum class FileMode : char
{
    Read = 0,
    Write = 1,
    ReadWrite = 2,
    Append = 3,
    Create = 4,
};

/**
 * 
 */
namespace FileSystem
{
    /**Open a file if it can and return the file handle
     * 
     * @code{.cpp}
     * 
     * Result<File, FileError> F = FileSystem::Open("Some"/"Text"/"File.txt");
     * 
     * if(F.HasErr())
     * {
     *     //The file failed to open
     * }
     * else
     * {
     *     //The file opened properly
     * }
     * 
     * @endcode
     * 
     * @param Path  the path to the file to be opened
     * @param Mode  the mode to open the file in
     * 
     * @return      A pair of the file if it opened and an error if something went wrong
     * 
     * @see FileError, File, Result, String
     */
    Result<File, FileError> Open(const String& Path, FileMode Mode = FileMode::Read);

    bool Exists(const String& Path);

    FileError Create(const String& Path);

    FileError Delete(const String& Path);

    FileError Move(const String& Path, const String& NewPath);

    const String Read(const String& Path);
};

}