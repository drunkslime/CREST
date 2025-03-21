#!/bin/bash

ls bin/ > /dev/null 2>&1 || mkdir bin/
if [ "$(ls | grep CMakeCache.txt)" == 0 ]
    then cmake --build .
    else cmake . && cmake --build .
fi
