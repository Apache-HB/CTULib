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

#include "Meta/Macros.h"

#if !defined(OS_WINDOWS)
#	include <unistd.h>
#	include <libgen.h>
#endif

#include "Core/Collections/CthulhuString.h"
#include "Core/Collections/Array.h"
#include "Core/Types/Errno.h"
#include "Core/Collections/Result.h"

#pragma once

/**
 * @brief The namespace for the Cthulhu filespace system
 * 
 */
namespace Cthulhu::FileSystem
{

/**
 * @brief The type of a file
 * 
 */
enum class Type
{
    Text, ///< A text file, such as .txt or .cpp
    Binary ///< A binary file, such as a .o or .a
};

/**
 * @brief the permissions of a file
 * 
 */
enum class Permissions : U16
{
    OwnerRead = (1 << 8), ///< The owner of the file can read from it
    OwnerWrite = (1 << 7), ///< The owner of the file can write to it
    OwnerExecute = (1 << 6), ///< The owner of the file can try to execute the contents of the file
    GroupRead = (1 << 5), ///< The group can read from this file
    GroupWrite = (1 << 4), ///< The group can write to this file
    GroupExecute = (1 << 3), ///< The group can execute this file
    OtherRead = (1 << 2), ///< Other can read from this file
    OtherWrite = (1 << 1), ///< Other can write to this file
    OtherExecute = (1 << 0) ///< Other can execute this file
};

/**
 * @brief The file opening mode
 * 
 */
enum class Mode : U8
{
    ReadText = (1 << 0), ///< Open a file in readonly for text
    WriteText = (1 << 1), ///< Open a file in readwrite for text
    ReadBinary = (1 << 2), ///< Open a file in readonly for binary
    WriteBinary = (1 << 3) ///< Open a file in readwrite for binary
};

/**
 * @brief 
 * 
 * @param Left 
 * @param Right 
 * @return Mode 
 */
inline Mode operator|(const Mode Left, const Mode Right)
{ 
    return static_cast<Mode>(
        static_cast<U8>(Left) | static_cast<U8>(Right)
    ); 
}

/**
 * @brief 
 * 
 * @param Left 
 * @param Right 
 * @return Mode 
 */
inline Mode operator&(const Mode Left, const Mode Right)
{
    return static_cast<Mode>(
        static_cast<U8>(Left) & static_cast<U8>(Right)
    );
}

/**
 * @brief 
 * 
 */
struct FileData
{
    const String* Str;
    const Array<Byte>* Data;
};

/**
 * @brief 
 * 
 * @param Name 
 * @param NewPermissions 
 * @return Errno 
 */
Errno CHMod(const String& Name, Permissions NewPermissions);

/**
 * @brief 
 * 
 * @param Name 
 * @return true 
 * @return false 
 */
bool Exists(const String& Name);

/**
 * @brief 
 * 
 * @param Name 
 * @return Errno 
 */
Errno Delete(const String& Name);

/**
 * @brief 
 * 
 * @param Name 
 * @return Result<U64, Errno> 
 */
Result<U64, Errno> LastEdited(const String& Name);

/**
 * @brief 
 * 
 */
struct File
{
    /**
     * @brief 
     * 
     * @param Name 
     * @param ReadMode 
     * @return Result<File*, Errno> 
     */
    friend Result<File*, Errno> Open(const String& Name, Mode ReadMode);
    
    /**
     * @brief Get the Type object
     * 
     * @return Type 
     */
    Type GetType() const;

    /**
     * @brief 
     * 
     * @return const Array<Byte>* 
     */
    const Array<Byte>* ReadBinary() const;

    /**
     * @brief 
     * 
     * @return const String* 
     */
    const String* ReadText() const;
    
    /**
     * @brief 
     * 
     * @param Data 
     */
    void Write(const String& Data);

    /**
     * @brief 
     * 
     * @param Data 
     */
    void Write(const Array<Byte>& Data);

    /**
     * @brief 
     * 
     * @return const String& 
     */
    const String& Name() const;

    /**
     * @brief 
     * 
     * @param NewName 
     * @return Errno 
     */
    Errno Rename(const String& NewName);    

    /**
     * @brief Destroy the File object
     * 
     */
    ~File();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool Valid() const;

    /**
     * @brief 
     * 
     * @return U64 
     */
    U64 LastModified() const;

    /**
     * @brief Get the Permissions object
     * 
     * @return Permissions 
     */
    Permissions GetPermissions() const;

    /**
     * @brief Construct a new File object
     * 
     * @param Other 
     */
    File(const File& Other);

    /**
     * @brief 
     * 
     * @return String 
     */
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


namespace Private
{

inline String ModeToString(Mode Input)
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

ALWAYSINLINE FILE* WrapFOpen(const char* Path, const char* Mode)
{
#ifdef OS_WINDOWS
	FILE* Ret;
	fopen_s(&Ret, Path, Mode);
	return Ret;
#else
	return fopen(Path, Mode);
#endif
}

inline char* ReadFile(FILE* Ptr)
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

inline Array<Byte> ReadBinaryFile(FILE* Ptr)
{
    Byte* Buffer;
    fseek(Ptr, 0, SEEK_END);
    U32 Len = ftell(Ptr);
    fseek(Ptr, 0, SEEK_CUR);
    
    Buffer = new Byte[Len];

    fread(Buffer, 1, Len, Ptr);
    return Array<Byte>(Buffer, Len);
}

} // namespace

inline Result<File*, Errno> Open(const String& Name, Mode ReadMode)
{
    FILE* Data = fopen(*Name, *Private::ModeToString(ReadMode));

    if(!Data)
        return Fail<File*, Errno>(Errno(errno));

    struct stat Stats;

    if(stat(*Name, &Stats) == 0)
    {
        File* Ret = new File();
        Ret->Real = Data;
        Ret->FileType = bool(ReadMode & (Mode::WriteText | Mode::ReadText)) ? Type::Text : Type::Binary;

#if !defined(OS_WINDOWS)
        Ret->FileName = basename(*Name);
#else
		
#endif

        Memory::Zero<void>(&Ret->Content, Math::Max(sizeof(Array<Byte>), sizeof(String)));

        if(Ret->GetType() == Type::Text)
        {
            Ret->Content.Claim(Private::ReadFile(Data));
        }
        else
        {
            Ret->Bytes = Private::ReadBinaryFile(Data);
        }
        return Pass<File*, Errno>(Ret);
    }

    return Fail<File*, Errno>(Errno(errno));
}

} // Cthulhu
