#!/bin/bash

if [ "command -v clang++" ]; then
    echo "clang++"
elif [ "command -v g++" ]; then
    echo "g++"
else
    echo "You have neither clang++ or g++ installed, so compiling C++ is not possible"
    exit 1
fi