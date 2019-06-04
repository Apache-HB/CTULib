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
    Binary()
        : Step(0)
        , Cursor(0)
        , MaxLength(64)
        , Length(0)
        , Data(new Byte[64]())
    {}

    template<typename T>
    T Read()
    {
        EnsureSize(sizeof(T));
        T Ret;
        Ret = *(T*)(Data + Cursor);
        MoveCursor(Cursor + sizeof(T));
        
        return Ret;
    }

    U32 ReadN(Byte* Ptr, U32 Len)
    {
        EnsureSize(Len);

        Memory::Copy(Data + Cursor, Ptr, Len);
        MoveCursor(Cursor + Len);

        return Tell();
    }

    template<typename T>
    U32 Write(const T Object)
    {
        EnsureSize(sizeof(T));

        Memory::Copy((Byte*)&Object, Data + Cursor, sizeof(T));
        MoveCursor(Cursor + sizeof(T));

        return Tell();
    }

    U32 WriteN(Byte* Ptr, U32 Len)
    {
        EnsureSize(Len);

        Memory::Copy(Ptr, Data + Cursor, Len);
        MoveCursor(Cursor + Len);

        return Tell();
    }

    U32 Seek(U32 Depth)
    {
        MoveCursor(Depth);
        return Tell();
    }

    U32 Tell() const
    {
        return Cursor;
    }

    U32 Step;

    U32 Len() const
    {
        return Length;
    }

    U32 RealLength() const
    {
        return MaxLength;
    }

    Byte* GetData() const
    {
        return Data;
    }

    void Reserve(U32 Slack)
    {
        EnsureSize(Slack);
    }

    void Cleanup()
    {
        delete[] Data;
    }

protected:

    // ensure we have enough extra size to fit Extra
    void EnsureSize(U32 Extra)
    {
        if(Cursor + Extra > MaxLength)
        {
            MaxLength = MaxLength + Extra + Step;

            Byte* Temp = Data;
            Data = new Byte[MaxLength]();
            Memory::Copy(Temp, Data, Length);
            delete[] Temp;
        }
    }

    void MoveCursor(U32 Location)
    {
        if(Location > MaxLength)
        {
            EnsureSize(Location - MaxLength);
            Length = Location;
        }

        Cursor = Location;
    }

private:
    U32 Cursor;
    U32 MaxLength;
    U32 Length;
    Byte* Data;
};

}