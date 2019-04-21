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

#include <Cthulhu/Core/Collections/CthulhuString.h>
#include <Cthulhu/Core/Collections/Array.h>

#include "Cthulhu/Core/Traits/IsPOD.h"

#include <stdio.h>

#pragma once

namespace Cthulhu::FileSystem
{

struct BufferedFile
{
    /** 
     *
     */
    BufferedFile(const String& Name);
    
    /**
     *
     */
    BufferedFile(Array<U8>* Data);

    ~BufferedFile() 
    { 
        if(FileType == FType::Disk)
        {
            if (Real) 
                fclose(Real);
        }
        else
        {
            delete Arr;
        }
    }

    CTU_INLINE C8 Next() 
    { 
        if(FileType == FType::Disk)
        {
            return fgetc(Real);
        }
        else
        {
            return Arr->At(Cursor++).Or(-1);
        }
    }

    C8 Peek() const;

    CTU_INLINE void Close() 
    {
        if(FileType == FType::Disk)
        {
            fclose(Real); 
        }
        else
        {
            delete Real;
        }
        Real = nullptr;
    }

    CTU_INLINE bool Valid() const 
    { 
        if(FileType == FType::Disk)
        {
            return Real != nullptr;
        }
        else
        {
            return true;
        }
    }

    CTU_INLINE void Push(C8 C) 
    { 
        if(FileType == FType::Disk)
        {
            ungetc(C, Real);
        }
        else
        {
            Arr->Append(C);
            Cursor++;
        }
    }

    template<typename T>
    T Read()
    {
        static_assert(IsDecimal<T>::Value || IsPOD<T>::Value, "T needs to be an integer or POD type");
        
        if(FileType == FType::Disk)
        {
            T Ret;
            fread(&Ret, sizeof(T), 1, Real);
            return Ret;
        }
        else
        {
            return *reinterpret_cast<T*>(Arr->Data() + Cursor);
        }
    }

    Array<Byte> ReadBytes(U32 Length)
    {
        U8* Ret = new U8[Length];
        if(FileType == FType::Disk)
        {
            fread(Ret, sizeof(U8), Length, Real);
        }
        else
        {
            Memory::Copy<Byte>(Arr->Data() + Cursor, Ret, Length);
            Cursor += Length;
        }

        return { Ret, Length };
    }

    U32 Size() const;

    CTU_INLINE U32 CurrentDepth() const 
    { 
        if(FileType == FType::Disk)
        {
            return ftell(Real);
        }
        else
        {
            return Cursor;
        }
    }

    U64 Seek(U64 NewLocation);

    void Write(Array<Byte> Data);

    BufferedFile& Claim(BufferedFile* Other)
    {
        Close();
        FileType = Other->FileType;
        if(FileType == FType::Disk)
        {
            Real = Other->Real;
            Other->Real = nullptr;
        }
        else
        {
            Arr = Other->Arr;
            Cursor = Other->Cursor;
            Other->Arr = nullptr;
        }

        return *this;
    }

    //what type of file is this
    enum FType : U8
    {
        // this is a real file that exists on the computers drive
        Disk,
        // this file is actually fake and is stored in memory
        Memory
    };

    FType Type() const { return FileType; }

private:

    FType FileType;
    union
    {
        FILE* Real;
        struct
        {
            Array<U8>* Arr;
            U32 Cursor;
        };
    };
};

}