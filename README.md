# Introduction

## Todo

* list all prerequisites
* figure out why failing tests are reported as succeeded (tests actually fail according to log output)
* add working main
  * blinking LEDs do not work for some reason
* extend Readme
* figure out how the _elastic-ai.runtime.enV5_ can be used as a dependency without having to add each src directory
  * alternatively: write a macro that adds each directory from the submodule src directory

This project explains how to use the _elastic-ai.runtime.enV5_ as a submodule for further development.
Although the _elastic-ai.runtime.enV5_ project is more automated, this project requires more steps to set up.

## Prerequisites

* cmake >= 3.13
* python3
* ninja-build

```bash
git submodule update --init --recursive
```

## Project structure

This project contains various folders:
* `extern`: stores external git submodules, i.e. the elastic-ai.runtime.enV5
* `out`: stores unit test executables, as well as _.uf2_ binary files for the enV5
* `src`: contains _Main.c_, helpers and your source code
* `test`: contains unit tests and hardware tests in their respective folders

## Clion specific settings

Clion automatically detects targets and adds them to the configurations in the upper right corner. These can be build
via one of the profiles. There are three profiles in total:

* `Debug`: build targets for the RP2040 with debug logs
* `Release`: build targets for the RP2040 without debug logs
* `Unit Test`: regular unit test executables

By default, the `Release` and `Unit Test` profiles are disabled. This is because CMake will otherwise fail during the 
initial configuration. Switching the profiles also "fixes" include paths, so if you have a unit test open, Clion will 
not recognize the inclusion of the unity.h file, as it is only included under the `Unit Test` profile. 

## How to build a binary

```bash
cmake -B cmake-build-debug -D DEBUG_OUTPUT:BOOL=ON -G Ninja .
cmake --build cmake-build-debug -j 4 --target main
```

## How to build an integration Test

```bash
cmake -B cmake-build-debug -D DEBUG_OUTPUT:BOOL=ON -G Ninja .
cmake --build cmake-build-debug -j 4 --target hardware-test_MQTTPublish
```

If you omit the `--target` flag, cmake will build every hardware target.

## How to build and run a unit test

```bash
cmake -B cmake-build-test/test/unit -D UNIT_TEST:BOOL=ON -D CMAKE_BUILD_TYPE=DEBUG -G Ninja .
cmake --build cmake-build-test/test/unit -j 4 --clean-first
ctest --test-dir cmake-build-test/test/unit --output-on-failure
```