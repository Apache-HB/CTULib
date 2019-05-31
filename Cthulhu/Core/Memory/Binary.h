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
        : Step(64)
        , Cursor(0)
        , Length(0)
        , Data(new Byte[64]())
    {}

    Binary(U32 Size)
        : Step(64)
        , Cursor(0)
        , Length(Size)
        , Data(new Byte[Size]())
    {}

    void Close() 
    {
        delete[] Data;
    }

    template<typename T>
    U32 Write(const T* Bytes)
    {
        EnsureSize(sizeof(T));
        
        Memory::Copy((Byte*)Bytes, Data + Cursor, sizeof(T));
        Cursor += sizeof(T);
        return Cursor;
    }

    U32 Write(const Byte* Bytes, U32 Size)
    {
        EnsureSize(Size);

        Memory::Copy(Bytes, Data + Cursor, Size);
        Cursor += Size;
        return Cursor;
    }

    U32 Seek(U32 To)
    {
        if(To > Length)
        {
            Byte* Temp = Data;
            U32 Len = To + Step;
            Data = new Byte[Len]();
            Memory::Copy(Temp, Data, Length);
            Length = Len;
        }

        if(To <= 0)
        {
            Cursor = 0;
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

        return Ret;
    }

    U32 ReadN(Byte* Out, U32 Len)
    {        
        U32 D = 0;

        while(Len < Length && Len > 0)
        {
            Out[D] = Data[D + Cursor];
            Cursor++;
            D++;
            Len--;
        }

        return D;
    }

    U32 GetLength() const { return Length; }
    U32 Depth() const { return Cursor; }

    U32 Step;

    const Byte* GetData() const { return Data; }

    Byte* TakeData() const { return Data; }
    
    void GiveData(Byte* NewData, U32 NewLen) 
    { 
        Data = NewData; 
        Length = NewLen;
    }
private:

    void EnsureSize(U32 Extra)
    {
        if(Cursor + Extra > Length)
        {
            U32 Original = Length;
            while(Cursor + Extra > Length)
            {
                Length += Step;
            }

            Length += Extra;

            Byte* Temp = Data;
            Data = new Byte[Length]();
            Memory::Copy(Temp, Data, Original);
            delete[] Temp;
        }
    }

    U32 Cursor;
    U32 Length;
    Byte* Data;
};

}