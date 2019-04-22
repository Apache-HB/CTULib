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

#include <stdio.h>

#include "Cthulhu/Core/Collections/Array.h"
#include "BufferedFile.h"

using namespace Cthulhu;
using namespace Cthulhu::FileSystem;

BufferedFile::BufferedFile(const String& Name)
#if defined(OS_LINUX) || defined(OS_APPLE)
    : FileType(FType::Disk)
    , Real(fopen(*Name, "r"))
#endif
{
#if defined(OS_WINDOWS)
	fopen_s(&Real, *Name, "r");
#endif
    if(Real)
        fputs("\n", Real);

    FileType = FType::Disk;
}

BufferedFile::BufferedFile(Array<U8>* Data)
    : FileType(FType::Memory)
    , Arr(Data)
    , Cursor(0)
{}


C8 BufferedFile::Peek() const
{
    if(FileType == FType::Disk)
    {
        //Take the next char
        C8 Ret = fgetc(Real);
        //Push the char back onto the file
        ungetc(Ret, Real);
        //Return the taken char
        return Ret;
    }
    else
    {
        return Arr->At(Cursor + 1).Or(-1);
    }
}

U32 BufferedFile::Size() const
{
    if(FileType == FType::Disk)
    {
        //seek to end
        U32 Depth = CurrentDepth();
        fseek(Real, 0, SEEK_END);
        const U32 Ret = ftell(Real);

        //seek back
        fseek(Real, Depth, SEEK_SET);

        return Ret;
    }
    else
    {
        return Arr->Len();
    }
}

U64 BufferedFile::Seek(U64 NewLocation)
{
    if(FileType == FType::Disk)
    {
        fseek(Real, (long)NewLocation, SEEK_SET);
        return ftell(Real);
    }
    else
    {
        return Cursor = NewLocation;
    }
}

void BufferedFile::Write(Array<Byte> Data)
{
    if(FileType == FType::Disk)
    {
        fwrite(Data.Data(), sizeof(Byte), Data.Len(), Real);
    }
    else
    {
        Arr->Append(Data);
        Cursor += Data.Len();
    }
}