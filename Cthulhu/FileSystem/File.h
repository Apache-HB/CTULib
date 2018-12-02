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

#pragma once

namespace Cthulhu::FileSystem
{

enum class Type
{
    Text,
    Binary
};

enum class Permissions : U16
{
    OwnerRead = (1 << 0),
    OwnerWrite = (1 << 1),
    OwnerExecute = (1 << 2),
    GroupRead = (1 << 3),
    GroupWrite = (1 << 4),
    GroupExecute = (1 << 5),
    OtherRead = (1 << 6),
    OtherWrite = (1 << 7),
    OtherExecute = (1 << 8)
};

enum class Mode : U8
{
    Read,
    Write,
    ReadBinary,
    WriteBinary
};

struct File
{
    const String& Read() const;
    bool Write(const String& Data);
    bool Write(const Array<Byte>& Data);

    const String& Name() const;
    bool Rename(const String& NewName);

private:
    String Name;

    Type Type;

    Permissions FilePermissions;

    union
    {
        String Content;
        Array<Byte> Bytes;
    };
};

}