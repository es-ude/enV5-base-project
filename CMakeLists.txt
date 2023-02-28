cmake_minimum_required(VERSION 3.13)
include(helpers.cmake)

if (DEBUG_OUTPUT)
    add_definitions(-DDEBUG_MODE)
endif ()

if (UNIT_TEST)
    message(NOTICE "INFO: Building Unit tests")

    project(enV5 C CXX ASM)

    include(CTest)

    add_subdirectory(extern/elastic-ai.runtime.enV5/extern/unity)
    add_subdirectory(test/unit)

else ()
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

    include(extern/elastic-ai.runtime.enV5/extern/pico-sdk/pico_sdk_init.cmake)

    project(enV5 C CXX ASM)

    add_subdirectory(extern/elastic-ai.runtime.enV5/extern/elastic-ai.runtime.c)
    pico_sdk_init()


    add_subdirectory(extern/elastic-ai.runtime.enV5/extern/freeRTOS)

    # libraries from the elastic-ai.runtime.enV5 repo
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/adxl345b)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/atCommands)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/broker)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/env5)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/esp)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/flash)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/fpgaConfig)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/freeRtos)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/gpio)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/i2c)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/middleware)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/network)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/pac193x)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/sht3x)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/spi)
    add_subdirectory(extern/elastic-ai.runtime.enV5/src/uart)

#    include_src() # you still need to include your own sources

    if (TARGET tinyusb_device)
        add_subdirectory(test/hardware)

        add_executable(main src/Main.c src/Main.c) # creates executable
        target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src)
        target_link_libraries(main
                pico_stdlib
                freeRtosUtils
                esp_lib
                uart_lib
                )
        make_to_output_file(main)
    elseif (PICO_ON_DEVICE)
        message(WARNING "not building Project because TinyUSB submodule is not initialized in the SDK")
    endif ()
endif ()
