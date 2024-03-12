cmake_minimum_required(VERSION 3.21...3.24)
include(${CMAKE_CURRENT_LIST_DIR}/helper.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if (DEBUG_OUTPUT)
    # enable PRINT_DEBUG macro
    add_definitions(-DDEBUG_MODE)
endif ()

if (UNIT_TEST)
    message(NOTICE "INFO: Building for local machine")

    project(enV5 C CXX ASM)

    # enable test execution via CMake
    include(CTest)

    load_enV5()

    # setup unit-tests
    enV5_init_unit_tests()

    # add your own unit-tests
    add_subdirectory(test/unit)
else ()
    message(NOTICE "INFO: Building for enV5 hardware (Type: ${CMAKE_BUILD_TYPE})")

    # include pico-sdk
    set(PICO_SDK_FETCH_FROM_GIT on)
    include(pico_sdk_import.cmake)

    project(enV5 C CXX ASM)

    load_enV5()

    # initialize pico-sdk
    pico_sdk_init()

    if (TARGET tinyusb_device)
        # load libraries from runtime.enV5
        enV5_init()

        # add your own hardware tests
        add_subdirectory(test/hardware)

        # add your own main target
        add_subdirectory(src)
    elseif (PICO_ON_DEVICE)
        message(WARNING "not building Project because TinyUSB submodule is not initialized in the SDK")
    endif ()
endif ()
