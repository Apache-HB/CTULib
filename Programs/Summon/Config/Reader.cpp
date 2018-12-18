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

#include <FileSystem/FastFile.h>

#include "Reader.h"

using namespace Cthulhu;
using namespace Cthulhu::Build;
namespace FS = Cthulhu::FileSystem;

namespace
{

void SkipWhitespace(FS::FastFile* Data)
{
    char C = Data->Peek();

    while(Utils::IsSpace(C))
    {
        Data->Next();
        C = Data->Peek();
    }
}

String ParseTag(FS::FastFile* Data, Lambda<bool(char)> Term)
{
    String Ret;
    char C = Data->Peek();
    while(Term(C))
    {
        Ret += C;
        C = Data->Next();

        if(Utils::IsEOF(C))
            break;
    }

    return Ret.Cut(1).Trim();
}

Map<String, String>* ParseFields(FS::FastFile* Data)
{
    Map<String, String>* Ret = new Map<String, String>();

    while(true)
    {
        SkipWhitespace(Data);
        String Tag = ParseTag(Data, [](char C) { return C != '='; });
        Data->Next();
        String Val = ParseTag(Data, [](char C) { return !Utils::IsNewline(C); });
        Ret->Add(Tag, Val);
        //printf("Tag: %s, Val: %s\n", *Tag, *Val);
        if(Utils::IsEOF(Data->Peek()))
            break;
    }
    //printf("Return\n");
    return Ret;
}

Config ParseConfig(FS::FastFile* Data)
{
    char C = Data->Peek();
    Config Ret{ new ConfigT() };
    //printf("In ParseConfig\n");
    while(true)
    {
        //printf("In loop\n");
        SkipWhitespace(Data);
        //printf("Skip whitespace\n");
        Data->Next();
        String Tag = ParseTag(Data, [](char C){ return C != ']'; });
        //printf("ParseTag\n");
        printf("Tag: %s\n", *Tag);
        SkipWhitespace(Data);

        auto Fields = ParseFields(Data);
        //printf("ParseField\n");
        printf("Fields: %s\n", *Utils::ToString<String, String>(*Fields));
        Ret.Data->Add(Tag, Fields);

        C = Data->Peek();

        if(Utils::IsEOF(C))
            break;
    }

    return Ret;

}

}

Config Cthulhu::Build::ReadConfig(const String& Path)
{
    FS::FastFile Data = FS::FastFile(Path);
    //printf("In ReadConfig\n");
    Config Ret = ParseConfig(&Data);

    printf("\n");
    return Ret;
}