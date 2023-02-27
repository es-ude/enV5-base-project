# Introduction

This project explains how to use the _elastic-ai.runtime.enV5_ as a submodule for further development.
Although the _elastic-ai.runtime.enV5_ project is more automated, this project requires more steps to set up.

```bash
git submodule update --init --recursive
```

## Project structure

This project contains various folders:
- `extern`: stores external git submodules, i.e. the elastic-ai.runtime.enV5
- `out`: stores unit test executables, as well as _.uf2_ binary files for the enV5
- `src`: contains _Main.c_, helpers and your source code
- `test`: contains unit tests and hardware tests in their respective folders

## How to build a binary

```bash
cmake -B cmake-build-debug -D DEBUG_OUTPUT:BOOL=ON -G Ninja .
```

## How to build and run a unit test

```bash
cmake -B cmake-build-test/test/unit -D UNIT_TEST:BOOL=ON -D CMAKE_BUILD_TYPE=DEBUG -G Ninja .
cmake --build cmake-build-test/test/unit -j 4 --clean-first
ctest --test-dir cmake-build-test/test/unit --output-on-failure
```