#!/bin/bash

lib_path="Build/Binaries/Libraries/Cthulhu/Cthulhu.a"

mkdir -p Build/Binaries/Objects/Cthulhu
mkdir -p Build/Binaries/Libraries/Cthulhu

mv *.o Build/Binaries/Objects/Cthulhu/

rm -rf "$lib_path"

ar rcs $lib_path Build/Binaries/Objects/Cthulhu/*.o