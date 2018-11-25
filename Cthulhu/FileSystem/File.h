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

#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Array.h"
#include "Core/Memory/Unique.h"
#include "Core/Types/Errno.h"

#pragma once

namespace Cthulhu::FileSystem
{

enum class Mode : U8
{
    Read,
    ReadPlus,
    Write,
    WritePlus,
    Append,
    AppendPlus
};

struct TextFile
{
    TextFile(const String& Name, Mode OpenMode);
    ~TextFile();

    const String& Name() const;
    Errno Rename(const String& NewName);

    const String& Content() const;
    bool Write(const String& NewData);

private:
    Mode FileMode;
    String FileName;
    String FileContent;
    FILE* Real;
};

bool Exists(const String& Path);
bool IsWriteable(const String& Path);
bool IsReadable(const String& Path);
bool IsExecutable(const String& Path);

struct BinaryFile
{
    BinaryFile(const String& Name, Mode OpenMode = Mode::Read);
    ~BinaryFile();

    const String& Name() const;
    Errno Rename(const String& NewName);

    const Array<Byte>& Content() const;
    bool Write(const Array<Byte>& NewData);

    Byte operator[](U32 Index) const;

private:
    Mode FileMode;
    String FileName;
    Array<Byte> FileContent;
    FILE* Real;
};

}

