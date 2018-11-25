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
#include <unistd.h>
#include <errno.h>

#include "File.h"

#include "Meta/Assert.h"

using namespace Cthulhu;
using namespace Cthulhu::FileSystem;

namespace
{

const char* ToRawString(Mode Val)
{
    switch(Val)
    {
        case Mode::Read: return "r";
        case Mode::Write: return "w";
        case Mode::Append: return "a";
        case Mode::ReadPlus: return "r+";
        case Mode::WritePlus: return "w+";
        case Mode::AppendPlus: return "a+";
        default:
            ASSERT_NO_ENTRY("Invalid file open mode");
    }
}

const char* ToStringBinaryMode(Mode Val)
{
    switch(Val)
    {
        case Mode::Read: return "rb";
        case Mode::Write: return "wb";
        case Mode::Append: return "ab";
        case Mode::ReadPlus: return "rb+";
        case Mode::WritePlus: return "wb+";
        case Mode::AppendPlus: return "ab+";
        default:
            ASSERT_NO_ENTRY("Invalid file open mode");
    }
}

}

TextFile::TextFile(const String& Name, Mode OpenMode)
    : Real(fopen(Name.CStr(), ToRawString(OpenMode)))
    , FileName(Name)
    , FileMode(OpenMode)
{
    fseek(Real, 0, SEEK_END);
    U32 Len = ftell(Real);
    fseek(Real, 0, SEEK_CUR);

    char* Buffer = new char[Len + 1];
    fread(Buffer, Len, 1, Real);

    FileContent = Buffer;

    delete[] Buffer;
}

TextFile::~TextFile()
{
    fclose(Real);
}

const String& TextFile::Name() const
{
    return FileName;
}

Errno TextFile::Rename(const String& NewName)
{
    bool Success = rename(*FileName, *NewName) == 0;

    if(Success)
    {
        FileName = NewName;
        return Errno::None;
    }
    else
    {
        return Errno(errno);
    }
}

const String& TextFile::Content() const
{
    return FileContent;
}

bool TextFile::Write(const String& NewData) 
{
    switch(FileMode)
    {
        case Mode::Read: case Mode::ReadPlus:
            return false;
        case Mode::Write: case Mode::WritePlus:
            fprintf(Real, "%s", *NewData);
            FileContent = NewData;
            return true;
        case Mode::Append: case Mode::AppendPlus:
            fprintf(Real, "%s", *NewData);
            FileContent += NewData;
            return true;
        default:
            ASSERT_NO_ENTRY("Invalid file mode");
    }
}

bool Exists(const String& Path)
{
    return access(*Path, F_OK) != -1;
}

bool IsWritable(const String& Path)
{
    return access(*Path, W_OK) != -1;
}

bool IsReadable(const String& Path)
{
    return access(*Path, R_OK) != -1;
}

bool IsExecutable(const String& Path)
{
    return access(*Path, X_OK) != -1;
}

BinaryFile::BinaryFile(const String& Name, Mode OpenMode)
    : Real(fopen(*Name, ToStringBinaryMode(OpenMode)))
    , FileName(Name)
    , FileMode(OpenMode)
{
    fseek(Real, 0, SEEK_END);
    U32 Len = ftell(Real);
    fseek(Real, 0, SEEK_CUR);

    Byte* Buffer = new Byte[Len];
    fread(Buffer, Len, 1, Real);

    FileContent = Array<Byte>(Buffer, Len);
}

BinaryFile::~BinaryFile()
{
    fclose(Real);
}

const String& BinaryFile::Name() const
{
    return FileName;
}

Errno BinaryFile::Rename(const String& NewName)
{
    bool Pass = rename(*FileName, *NewName);

    if(Pass)
    {
        FileName = NewName;
        return Errno::None;
    }
    else
    {
        return Errno(errno);
    }
}

const Array<Byte>& BinaryFile::Content() const
{
    return FileContent;
}

bool BinaryFile::Write(const Array<Byte>& NewData)
{
    switch(FileMode)
    {
        case Mode::Read: case Mode::ReadPlus:
            return false;
        case Mode::Write: case Mode::WritePlus:
            fwrite(*NewData, NewData.Len() * sizeof(Byte), 1, Real);
            FileContent = NewData;
            return true;
        case Mode::Append: case Mode::AppendPlus:
            FileContent.Append(NewData);
            fwrite(*FileContent, FileContent.Len() * sizeof(Byte), 1, Real);
            return true;
        default:
            ASSERT_NO_ENTRY("Invalid file mode");
    }
}

Byte BinaryFile::operator[](U32 Index) const
{
    return FileContent[Index];
}
