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

#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Meta/Macros.h"

#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Array.h"
#include "Core/Types/Errno.h"
#include "Core/Collections/Result.h"
//#include "Core/Types/Date.h"

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
    OwnerRead = (1 << 8),
    OwnerWrite = (1 << 7),
    OwnerExecute = (1 << 6),
    GroupRead = (1 << 5),
    GroupWrite = (1 << 4),
    GroupExecute = (1 << 3),
    OtherRead = (1 << 2),
    OtherWrite = (1 << 1),
    OtherExecute = (1 << 0)
};

enum class Mode : U8
{
    ReadText = (1 << 0),
    WriteText = (1 << 1),
    ReadBinary = (1 << 2),
    WriteBinary = (1 << 3)
};

inline Mode operator|(const Mode Left, const Mode Right)
{ 
    return static_cast<Mode>(
        static_cast<U8>(Left) | static_cast<U8>(Right)
    ); 
}

inline Mode operator&(const Mode Left, const Mode Right)
{
    return static_cast<Mode>(
        static_cast<U8>(Left) & static_cast<U8>(Right)
    );
}

struct FileData
{
    const String* Str;
    const Array<Byte>* Data;
};

Errno CHMod(const String& Name, Permissions NewPermissions);
bool Exists(const String& Name);
Errno Delete(const String& Name);

Result<U64, Errno> LastEdited(const String& Name);

struct File
{
    friend Result<File*, Errno> Open(const String& Name, Mode ReadMode);
    Type GetType() const;

    const Array<Byte>* ReadBinary() const;
    const String* ReadText() const;
    
    void Write(const String& Data);
    void Write(const Array<Byte>& Data);

    const String& Name() const;
    Errno Rename(const String& NewName);    

    ~File();

    bool Valid() const;

    U64 LastModified() const;
    Permissions GetPermissions() const;

    File(const File& Other);

    String AbsolutePath() const;

private:

    File(const String& Path, Mode ReadMode);
    File(FILE* RealFile);
    File(){}

    FILE* Real;

    String FileName;
    //use stat() for all this
    Type FileType;

    Permissions FilePermissions;

    U64 Epoch;

    union
    {
        String Content;
        Array<Byte> Bytes;
    };
};


namespace 
{

String ModeToString(Mode Input)
{
    switch(Input)
    {
        case Mode::ReadText: return "r+";
        case Mode::WriteText: return "w+";
        case Mode::ReadBinary: return "rb+";
        case Mode::WriteBinary: return "wb+";
        default:
            ASSERT_NO_ENTRY("Bad File mode");
    }    
}

char* ReadFile(FILE* Ptr)
{
    fseek(Ptr, 0, SEEK_END);
    U32 Len = ftell(Ptr);
    fseek(Ptr, 0, SEEK_SET);
    char* Buffer = new char[Len+1];

    U32 I = 0;
    char C;
    while((C = fgetc(Ptr)) != EOF)
    {
        Buffer[I++] = C;
    }

    Buffer[Len] = '\0';

    return Buffer;
}

Array<Byte> ReadBinaryFile(FILE* Ptr)
{
    Byte* Buffer;
    fseek(Ptr, 0, SEEK_END);
    U32 Len = ftell(Ptr);
    fseek(Ptr, 0, SEEK_CUR);
    
    Buffer = new Byte[Len];

    fread(Buffer, 1, Len, Ptr);
    return Array<Byte>(Buffer, Len);
}

}

inline Result<File*, Errno> Open(const String& Name, Mode ReadMode)
{
    FILE* Data = fopen(*Name, *ModeToString(ReadMode));

    if(!Data)
        return Fail<File*, Errno>(Errno(errno));

    struct stat Stats;

    if(stat(*Name, &Stats) == 0)
    {
        File* Ret = new File();
        Ret->Real = Data;
        Ret->FileType = bool(ReadMode & (Mode::WriteText | Mode::ReadText)) ? Type::Text : Type::Binary;

        Ret->FileName = basename(*Name);

        Memory::Zero<void>(&Ret->Content, Math::Max(sizeof(Array<Byte>), sizeof(String)));

        if(Ret->GetType() == Type::Text)
        {
            Ret->Content.Claim(ReadFile(Data));
        }
        else
        {
            Ret->Bytes = ReadBinaryFile(Data);
        }
        return Pass<File*, Errno>(Ret);
    }

    return Fail<File*, Errno>(Errno(errno));
}

}

/*
FILE* Data = fopen(*Name, *ModeToString(ReadMode));
    
    if(Data == nullptr)
    {
        return Fail<File*, Errno>(Errno(errno));
    }

    struct stat Stats;
    
    if(stat(*Name, &Stats) == 0)
    {
        File* Ret = new File();
        Ret->Real = Data;
        Ret->FilePermissions = (Permissions)Stats.st_mode;
        Ret->Epoch = Stats.st_atimespec.tv_sec;
        return Pass<File*, Errno>(Ret);
    }
    else
    {
        return Fail<File*, Errno>(Errno(errno));
    }*/