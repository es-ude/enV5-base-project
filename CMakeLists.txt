cmake_minimum_required(VERSION 3.13)
include(helpers.cmake)
include(extern/elastic-ai.runtime.enV5/enV5_init.cmake)

if (DEBUG_OUTPUT)
    add_definitions(-DDEBUG_MODE)
endif ()

if (UNIT_TEST)
    message(NOTICE "INFO: Building Unit tests")

    project(enV5 C CXX ASM)

    include(CTest)

    include_unity()
    add_subdirectory(test/unit)

else ()
    message(NOTICE "INFO: Building for enV5")
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

    # inlcude pico-sdk from enV5
    include(extern/elastic-ai.runtime.enV5/extern/pico-sdk/pico_sdk_init.cmake)
    add_subdirectory(extern/elastic-ai.runtime.enV5/extern/freeRTOS/Kernel/portable/ThirdParty/GCC/RP2040 FREERTOS_KERNEL)

    project(enV5 C CXX ASM)

    # initialize pico-sdk
    pico_sdk_init()

    # include enV5 libraries
    enV5_init()

#    include_src() # you still need to include your own sources

    if (TARGET tinyusb_device)
        add_subdirectory(test/hardware)

        add_executable(main src/Main.c) # creates executable
        target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src)
        target_link_libraries(main
                pico_stdlib
                freeRtosUtils
                esp_lib
                uart_lib)
        make_to_output_file(main)
    elseif (PICO_ON_DEVICE)
        message(WARNING "not building Project because TinyUSB submodule is not initialized in the SDK")
    endif ()
endif ()
