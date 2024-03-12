################## hardwareTestHelper ##################
add_library(hardware-testHelper HardwaretestHelper.c)
target_link_libraries(hardware-testHelper
        pico_stdlib
        common_lib
        esp_lib
        network_lib
        freeRtosUtils)
target_include_directories(hardware-testHelper PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(hardware-testHelper PRIVATE DEBUG)
pico_enable_stdio_usb(hardware-testHelper 1)
pico_enable_stdio_uart(hardware-testHelper 0)

################## test_MQTTPublish ##################
add_executable(hardware-test_MQTTPublish HardwaretestMqttPublish.c)
target_link_libraries(hardware-test_MQTTPublish
        common_lib
        pico_stdlib
        freeRtosUtils
        hardware-testHelper)
target_compile_definitions(hardware-test_MQTTPublish PRIVATE DEBUG)
create_enV5_executable(hardware-test_MQTTPublish)