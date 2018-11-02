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

#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Array.h"

#include "Meta/Aliases.h"

#pragma once

namespace Cthulhu
{

template<typename> struct Option;
struct FILE;

namespace FileSystem
{

struct BinaryFile
{
    BinaryFile();

    BinaryFile(FILE* File, const String& Name);

    Array<U8> Data;
    const String Name;

    void Append(const Array<U8> Data);
    void Write(const Array<U8> NewData);
    void Save(const Option<String> Name);
    void Close();

private:
    FILE* RawFile;
};

struct TextFile
{
    TextFile();
    
    TextFile(FILE* File, const String& Name);

    String Content;
    const String Name;

    void Append(const String& Text);
    void Write(const String& NewText);
    void Save(const Option<String> Name);
    void Close();

private:
    FILE* RawFile;
};

}

}

#endif