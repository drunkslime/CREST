# CREST

A REST API engine built on C programming language for shits 'n giggles

Status - WIP

## Build

### Requirements

* C, CMake, gcc

* ```libmicrohttpd``` library. You can download it [here](https://www.gnu.org/software/libmicrohttpd/).

### Windows

Compile using cmake

```sh
cmake --build .
```

Run ```bin/CREST.exe```

### Linux

To build, run ```scripts/build-linux.sh```

To execute, run ```scripts/run-linux.sh [PORT]```

To clean, run ```scripts/run-clean.sh```

NOTE: In order for any scripts located in the ```scripts/``` directory to work, only execute them from local root (```CREST/```)
