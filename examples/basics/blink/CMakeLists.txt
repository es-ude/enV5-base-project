add_executable(blink BlinkLed.c)
create_enV5_executable(blink)
target_link_libraries(blink
        pico_stdlib
        freeRtosUtils
        esp_lib
        espBroker_lib
        network_lib
        http_lib
        uart_interface
        enV5_hw_configuration
        fpga_configuration_handler
        flash_lib)
