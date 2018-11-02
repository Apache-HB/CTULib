#!/bin/bash

mv *.o Build/Binaries/Objects/Cthulhu/

lib_path="Build/Binaries/Libraries/Cthulhu/Cthulhu.a"

if [ -a $lib_path ]; then
    rm -rf "$lib_path"
fi

ar rcs $lib_path Build/Binaries/Objects/Cthulhu/*.o