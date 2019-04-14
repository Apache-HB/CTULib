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

#include "Core/Collections/Array.h"
#include "BufferedFile.h"

using namespace Cthulhu;
using namespace Cthulhu::FileSystem;

BufferedFile::BufferedFile(const String& Name)
#if defined(OS_LINUX) || defined(OS_APPLE)
    : Real(fopen(*Name, "r"))
#endif
{
#if defined(OS_WINDOWS)
	fopen_s(&Real, *Name, "r");
#endif
    if(Real)
        fputs("\n", Real);
}

C8 BufferedFile::Peek() const
{
    //Take the next char
    char Ret = fgetc(Real);
    //Push the char back onto the file
    ungetc(Ret, Real);
    //Return the taken char
    return Ret;
}

U32 BufferedFile::Size() const
{
    //seek to end
    U32 Depth = CurrentDepth();
    fseek(Real, 0, SEEK_END);
    const U32 Ret = ftell(Real);

    //seek back
    fseek(Real, Depth, SEEK_SET);

    return Ret;
}

U64 BufferedFile::Seek(U64 NewLocation)
{
    fseek(Real, (long)NewLocation, SEEK_SET);
    return ftell(Real);
}

void BufferedFile::Write(Array<Byte> Data)
{
    fwrite(Data.Data(), sizeof(Byte), Data.Len(), Real);
}