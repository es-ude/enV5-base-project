# enV5 Base Project

This project explains how to use the [elastic-ai.runtime.enV5](https://github.com/es-ude/elastic-ai.runtime.enV5) as a submodule for further development.
Although the _elastic-ai.runtime.enV5_ project is more automated, this project requires more steps to set up.

## Setup

### Prerequisites

|                Purpose |             Tool |   Version |
|-----------------------:|-----------------:|----------:|
| Build Script Generator |            CMake | \>\= 3.13 |
|      Embedded Compiler | arm-non-eabi-gcc |           |
|             Build Tool |            Ninja |           |
|       Bitfile Flashing |          Python3 |           |

### Local Setup

1. Install all required tools (see Prerequisites)
2. Clone the repo to your local machine
3. Initialize all submodules with

```bash
git submodule update --init --recursive
```

4. Open the project in your preferred C/C++ IDE
5. **OPTIONAL** Create a virtual Python3 environment
6. **OPTIONAL** Install Python3 dependencies from _elastic-ai.runtime.enV5/bitfile_scripts/requirements.txt_

### Clion specific settings

Clion automatically detects targets and adds them to the configurations in the upper right corner.
These can be build via one of the profiles.
There are three profiles in total:

* `Debug`: build targets for the RP2040 with debug logs
* `Release`: build targets for the RP2040 without debug logs
* `Unit Test`: regular unit test executables

By default, the `Release` and `Unit Test` profiles are disabled.
This is because CMake will otherwise fail during the initial configuration.
Switching the profiles also "fixes" include paths, so if you have a unit test open, Clion will not recognize the
inclusion of the unity.h file, as it is only included under the `Unit Test` profile.

## Project structure

This project contains various folders:

* `extern`: stores external git submodules, i.e. the _elastic-ai.runtime.enV5_
* `out`: stores unit test executables, as well as _.uf2_ binary files for the enV5
* `src`: contains _Main.c_, helpers and your source code
* `test`: contains unit tests and hardware tests in their respective folders

## Build via CLI

### How to build a binary

```bash
cmake -B cmake-build-debug -DDEBUG_OUTPUT:BOOL=ON -G Ninja .
cmake --build cmake-build-debug -j 4 --target main
```

If you omit the `--target` flag, cmake will build every hardware target.
If you omit the `-DDEBUG_OUTPUT:BOOL=ON`, than the `PRINT_DEBUG` Macro will be disabled.

### How to build an integration Test

```bash
cmake -B cmake-build-debug -DDEBUG_OUTPUT:BOOL=ON -G Ninja .
cmake --build cmake-build-debug -j 4 --target hardware-test_MQTTPublish
```

If you omit the `--target` flag, cmake will build every hardware target.
If you omit the `-DDEBUG_OUTPUT:BOOL=ON`, than the `PRINT_DEBUG` Macro will be disabled.

### How to build and run the unit tests

```bash
cmake -B cmake-build-test/test/unit -DUNIT_TEST:BOOL=ON -DDEBUG_OUTPUT:BOOL=ON -DCMAKE_BUILD_TYPE=DEBUG -G Ninja .
cmake --build cmake-build-test/test/unit -j 4 --clean-first
ctest --test-dir cmake-build-test/test/unit --output-on-failure
```

If you omit the `-DDEBUG_OUTPUT:BOOL=ON`, than the `PRINT_DEBUG` Macro will be disabled.

## Quickfix

### Update all submodules to the latest release

```bash
git submodule update --init --recursive --remote
```
