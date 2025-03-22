#!/bin/bash

./scripts/clean-linux.sh
ls "build/" > /dev/null 2>&1 || mkdir "build/"
cd "build/" || exit
if [ "$(ls | grep CMakeCache.txt)" == 0 ]
    then cmake --build .
    else cmake .. && cmake --build .
fi