# C build-tool

It is a light waitght tool to help you start and easily compile your C projects.

## Install

```console
$ git clone http://github.com/trmaa/ctool.git
$ cd ctool
$ gcc main.c -o c
$ ./c -n c installl
```

## How to

```
USAGE: c <opts> <callbacks>
Opts:
	-n name of the binary
	-f flags for libraries
	-h help
Callbacks:
	init: create a default C project
	clean: remove old binaries
	compile: compile C files at src/
	link: link binaries at objects/
	build: compile and link
	install: make the program runable from the shell
	run: run the program
```
