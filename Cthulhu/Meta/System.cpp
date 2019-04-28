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


#include <stdlib.h>

#include "System.h"
#include "Core/Collections/Array.h"

#if OS_LINUX || OS_APPLE
#   include <unistd.h>
#endif

#if OS_WINDOWS
#   include <windows.h>
#   include <stdio.h>
#   include <direct.h>
#endif

using namespace Cthulhu;
using namespace Cthulhu::System;

U32 CoreCount()
{
#if OS_WINDOWS
    SYSTEM_INFO Info;
    GetSystemInfo(&Info);
    return Info.dwNumberOfProcessors;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

U64 TotalRam()
{
#if !OS_WINDOWS
    const U32 Pages = sysconf(_SC_PHYS_PAGES),
              PageSize = sysconf(_SC_PAGE_SIZE);
    
    return Pages * PageSize;
#else
    MEMORYSTATUSEX Status;
    Status.dwLength = sizeof(Status);
    GlobalMemoryStatusEx(&Status);
    return Status.ullTotalPhys;
#endif
}

bool FunctionExists(const String& Name)
{
    Array<String> Temp = { *Name };
    return system(*String("which {0} > /dev/null 2>&1").ArrayFormat(Temp));
}

bool HasCommandPromt()
{
    return system(nullptr);
}

String Exec(const String& Command)
{
#if OS_WINDOWS
    FILE* Temp = _popen(*Command, "r");
#else
    FILE* Temp = popen(*Command, "r");
#endif
    String Ret;

    char C[64];

    while(fgets(C, sizeof(C), Temp) != nullptr)
    {
        Ret += C;
    }

#if OS_WINDOWS
    _pclose(Temp);
#else
    pclose(Temp);
#endif

    return Ret;
}

Option<String> CurrentDirectory()
{
    char* Path = new char[1024];

#if OS_WINDOWS
    if(_getcwd(Path, 1024) != nullptr)
#else
    if(getcwd(Path, 1024) != nullptr)
#endif
    {
        String Temp = Path;
        delete[] Path;
        return Some(Temp);
    }
    else
    {
        delete[] Path;
        return None<String>();
    }
}