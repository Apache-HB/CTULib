#pragma once
#include "Macros.h"

#include <Core/Collections/Map.h>

using namespace Cthulhu;

void MapTest()
{
    Map<String, String> Thing = {
        { "Name", "Jeff" },
        { "Thing", "Other thing" },
        { "3", "4" },
        { "5", "6" }
    };

    for(auto Each : Thing.Items())
    {
        printf("%s: %s\n", Each.First.CStr(), Each.Second.CStr());
    }
}