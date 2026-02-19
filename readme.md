# C build-tool

It is a light waitght tool to help you start and easily build your C projects.

## Install

```console
$ git clone http://github.com/trmaa/ctool.git
$ cd ctool
$ gcc main.c -o c
$ ./c -n c install
```

## How to

```
USAGE: c <opts> <callbacks>
Opts:
        -n name of the binary
        -i -I flag for gcc
        -f lib flags
        -h help
Callbacks:
        init: create a default C project
        clean: remove old binaries
        compile: compile C files at src/
        link: link binaries at objects/
        build: compile and link
        install: make the program runable from the shell
```

## Example of use

```console
$ tree
├── fsim
│   ├── fsim
│   └── shaders
│       └── main.glsl
├── include
│   ├── camera.h
│   ├── main.h
│   ├── raylib.h
│   └── window.h
└── src
    ├── camera.c
    ├── main.c
    └── window.c
$ c -n fsim/fsim -i include -f -lraylib build
Compiling: gcc -c *.c -Iinclude
        camera.c
        window.c
        main.c
Linking: gcc *.o -lraylib
        camera.o
        main.o
        window.o
Done in 573 ms.
$
```
