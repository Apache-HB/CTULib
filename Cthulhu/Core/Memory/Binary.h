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

#include "Core/Collections/Array.h"

#pragma once

namespace Cthulhu
{

struct Binary
{
    Binary(U32 Size)
        : Length(Size)
        , Cursor(0)
        , Data(new Byte[Size])
    {}

    template<typename T>
    void Write(const T* Bytes)
    {
        U32 WriteLength = Math::Min(sizeof(T), Length - Cursor);
        Memory::Copy(Bytes, Data + Cursor, WriteLength);
        Cursor += WriteLength;
        return WriteLength;
    }

    U32 Seek(U32 To)
    {
        if(To <= 0)
        {
            Cursor = 0;
        }
        else if(To >= Length)
        {
            Cursor = Length;
        }
        else
        {
            Cursor = To;
        }

        return Cursor;
    }

    template<typename T>
    T Read()
    {
        T Ret = *(T*)(Data + Cursor);
        Cursor += sizeof(T);

        return T;
    }

    U32 GetLength() const { return Length; }
    U32 Depth() const { return Cursor; }

private:
    U32 Cursor;
    U32 Length;
    Byte* Data;
};

}