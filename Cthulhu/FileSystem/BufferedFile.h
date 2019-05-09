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

#include <Core/Collections/CthulhuString.h>
#include <Core/Collections/Array.h>

#include "Core/Traits/IsPOD.h"

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

    ~BufferedFile();

    CTU_INLINE C8 Next() 
    { 
        return fgetc(Real);
    }

    C8 Peek() const;

    CTU_INLINE void Close() 
    {
        fclose(Real); 
        Real = nullptr;
    }

    CTU_INLINE bool Valid() const 
    { 
        return Real != nullptr;
    }

    CTU_INLINE void Push(C8 C) 
    { 
        ungetc(C, Real);
    }

    template<typename T>
    T Read()
    {
        static_assert(IsDecimal<T>::Value || IsPOD<T>::Value, "T needs to be an integer or POD type");
        
        T Ret;
        fread(&Ret, sizeof(T), 1, Real);
        return Ret;
    }

    Array<Byte> ReadBytes(U32 Length)
    {
        U8* Ret = new U8[Length];
        fread(Ret, sizeof(U8), Length, Real);
        return { Ret, Length };
    }

    U32 Size() const;

    CTU_INLINE U32 CurrentDepth() const 
    { 
        return ftell(Real);
    }

    template<typename T>
    CTU_INLINE U32 ReadN(T* Data, U32 Len)
    {
        U32 Max = Size();
        U32 Depth = CurrentDepth();
        Byte* Out = (Byte*)Data;

        U32 I = 0;
        while(Depth++ < Max && Len-- > 0)
        {
            Out[I++] = Next();
        }

        return I;
    }
    
    U64 Seek(U64 NewLocation);

    void Write(Array<Byte> Data);

    BufferedFile& Claim(BufferedFile* Other)
    {
        Close();
        Real = Other->Real;
        Other->Real = nullptr;

        return *this;
    }

private:
    FILE* Real;
};

}