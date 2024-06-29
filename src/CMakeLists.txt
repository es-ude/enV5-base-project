# add your own executable
add_executable(main
        ${CMAKE_CURRENT_LIST_DIR}/Main.c)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(main
        pico_stdlib
        freeRtosUtils
        esp_lib
        espBroker_lib
        network_lib
        http_lib
        uart_interface)
create_enV5_executable(main)
