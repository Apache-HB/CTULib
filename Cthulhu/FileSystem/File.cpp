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

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "File.h"

#if !defined(OS_WINDOWS)
#	include <libgen.h>
#	include <unistd.h>
#endif

using namespace Cthulhu;
using namespace Cthulhu::FileSystem;

Errno FileSystem::CHMod(const String& Name, Permissions NewPermissions)
{
    return chmod(*Name, (mode_t)NewPermissions) == 0 ? Errno::None : Errno(errno);
}

bool FileSystem::Exists(const String& Name)
{
    return access(*Name, F_OK) != -1;
}

Errno FileSystem::Delete(const String& Name)
{
    return remove(*Name) == 0 ? Errno::None : Errno(errno);
}

Result<U64, Errno> FileSystem::LastEdited(const String& Name)
{
    struct stat Result;
    
    if(stat(*Name, &Result) == 0)
    {
        U64 Ret = Result.st_mtimespec.tv_sec;
        return Pass<U64, Errno>(Ret);
    }

    return Fail<U64, Errno>(Errno(errno));
}

File::File(const File& Other)
    : FileName(Other.FileName)
    , FileType(Other.FileType)
    , Real(Other.Real)
    , Epoch(Other.Epoch)
    , FilePermissions(Other.FilePermissions)
{
    if(FileType == Type::Binary)
    {
        Bytes = Other.Bytes;
    }
    else
    {
        Content = Other.Content;
    }
}

File::File(const String& Path, Mode ReadMode)
    : FileType(ReadMode == Mode::ReadText || ReadMode == Mode::WriteText ? Type::Text : Type::Binary)
#if !defined(OS_WINDOWS)
	, FileName(basename(*Path))
    , Real(fopen(Path.CStr(), Private::ModeToString(ReadMode).CStr()))
#endif
{
#if defined(OS_WINDOWS)
	_splitpath_s<0, 0, 256, 256>(
		nullptr,nullptr,
		nullptr,
		Path.CStr(),
		nullptr
	);
	//TODO: impl for windows stuff
#endif
    Memory::Zero<String>(&Content, sizeof(String));

    if(FileType == Type::Binary)
    {
        Byte* Buffer;
        fseek(Real, 0, SEEK_END);
        U32 Len = ftell(Real);
        fseek(Real, 0, SEEK_CUR);
        
        Buffer = new Byte[Len];

        fread(Buffer, sizeof(Byte), Len, Real);
        Bytes = Array<Byte>(Buffer, Len);
    }
    else
    {
        fseek(Real, 0, SEEK_END);
        U32 Len = ftell(Real);
        fseek(Real, 0, SEEK_SET);
        char* Buffer = new char[Len+1];

        U32 I = 0;
        char C;
        while((C = fgetc(Real)) != EOF)
        {
            Buffer[I++] = C;
        }

        Buffer[Len] = '\0';

        Content.Claim(Buffer);
    }
}

File::File(FILE* RealFile)
{
    Real = RealFile;
}

Type File::GetType() const
{
    return FileType;
}

const String* File::ReadText() const
{
    ASSERT(FileType == Type::Text, "Trying to read a binary file as text");

    return &Content;
}

const Array<Byte>* File::ReadBinary() const
{
    ASSERT(FileType == Type::Binary, "Trying to read a text file as binary");

    return &Bytes;
}

void File::Write(const String& Data)
{
    ASSERT(FileType == Type::Text, "Trying to write text to a binary file");
    fprintf(Real, "%s", Data.CStr());

    Content = Data;
}

void File::Write(const Array<Byte>& Data)
{
    ASSERT(FileType == Type::Binary, "Trying to write binary to a text file");
    fwrite(Data.Data(), sizeof(Byte), sizeof(Data.Data()), Real);

    Bytes = Data;
}

const String& File::Name() const
{
    return FileName;
}

String File::AbsolutePath() const
{
    char* Path = realpath(*FileName, nullptr);

    String Ret = Path;
    free(Path);

    return Ret;
}

Errno File::Rename(const String& NewName)
{
    bool Pass = rename(FileName.CStr(), NewName.CStr()) == 0;

    if(Pass)
    {
        FileName = NewName;
        return Errno::None;
    }

    return Errno(errno);
}

U64 File::LastModified() const
{
    return Epoch;
}

Permissions File::GetPermissions() const
{
    return FilePermissions;
}

File::~File()
{
    fclose(Real);
}

bool File::Valid() const 
{ 
    return Real != nullptr; 
}

