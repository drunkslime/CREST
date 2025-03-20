#!/bin/bash

ls build/ 2>1 > /dev/null || mkdir build/
gcc -o build/crest -lmicrohttpd src/*.c || echo "1"
