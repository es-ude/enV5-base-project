#ifndef SENSOR_BOARD_HARDWARE_TEST_HELPER_H
#define SENSOR_BOARD_HARDWARE_TEST_HELPER_H

void connectToNetwork(void);

void connectToMqttBroker(void);

void initializeHardwareTest(void);

_Noreturn void enterBootModeTaskHardwareTest(void);

#endif // SENSOR_BOARD_HARDWARE_TEST_HELPER_H
