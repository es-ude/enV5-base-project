cmake_minimum_required(VERSION 3.13)
include(extern/elastic-ai.runtime.enV5/enV5_init.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if (DEBUG_OUTPUT)
    add_definitions(-DDEBUG_MODE)
endif ()

if (UNIT_TEST)
    message(NOTICE "INFO: Building for local machine")

    project(enV5 C CXX ASM)

    enV5_init_unit_tests()

    # add your own unit-tests
    add_subdirectory(test/unit)
else ()
    message(NOTICE "INFO: Building for enV5")

    # include pico-sdk
    include(extern/elastic-ai.runtime.enV5/extern/pico-sdk/pico_sdk_init.cmake)

    project(enV5 C CXX ASM)

    # initialize pico-sdk
    pico_sdk_init()

    # include enV5 libraries
    enV5_init()

    if (TARGET tinyusb_device)
        # add your own hardware tests
        add_subdirectory(test/hardware)

        # add your own executable
        add_executable(main
                src/Main.c
                src/NetworkConfiguration.c)
        target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src)
        target_link_libraries(main
                pico_stdlib
                freeRtosUtils
                esp_lib
                network_lib
                http_lib
                uart_interface)
        create_enV5_executable(main)
    elseif (PICO_ON_DEVICE)
        message(WARNING "not building Project because TinyUSB submodule is not initialized in the SDK")
    endif ()
endif ()
