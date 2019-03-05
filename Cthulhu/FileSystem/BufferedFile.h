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

#include "Core/Traits/IsPOD.h"

#include <stdio.h>

#pragma once

namespace Cthulhu::FileSystem
{

struct BufferedFile
{
    BufferedFile(const String& Name);

    ~BufferedFile() { fclose(Real); }

    CTU_INLINE C8 Next();

    CTU_INLINE C8 Peek() const;

    CTU_INLINE void Close();

    CTU_INLINE bool Valid() const;

    CTU_INLINE void Push(char C);

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

        Array<Byte> Bytes = { Ret, Length };

        return Bytes;
    }

    U32 Size() const;

    CTU_INLINE U32 CurrentDepth() const;

    U64 Seek(U64 NewLocation);

    void Write(Array<Byte> Data);

private:
    FILE* Real;
};

}