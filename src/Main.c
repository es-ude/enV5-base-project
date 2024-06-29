#define SOURCE_FILE "MAIN"

#include "hardware/watchdog.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include "Common.h"
#include "EnV5HwController.h"
#include "Esp.h"
#include "FreeRtosTaskWrapper.h"
#include "Network.h"

_Noreturn void ledTask(void) {
    while (true) {
        PRINT("LEDs should now turn on");
        env5HwControllerLedsAllOn();
        freeRtosTaskWrapperTaskSleep(2000);
        PRINT("LEDs should now turned off");
        env5HwControllerLedsAllOff();
        freeRtosTaskWrapperTaskSleep(2000);
    }
}

/*! \brief Goes into bootloader mode when 'r' is pressed
 */
_Noreturn void enterBootModeTask(void) {
    while (true) {
        if (getchar_timeout_us(10) == 'r' || !stdio_usb_connected()) {
            PRINT_DEBUG("Boot Mode request detected.");
            reset_usb_boot(0, 0);
        }

        // Watchdog update needs to be performed frequent, otherwise the device will crash
        watchdog_update();
        PRINT_DEBUG("watchdog updated");
        freeRtosTaskWrapperTaskSleep(1000);
    }
}

void initializeHardware(void) {
    env5HwControllerInit();

    // First check if we crash last time -> reboot into boot rom mode
    if (watchdog_enable_caused_reboot()) {
        reset_usb_boot(0, 0);
    }

    stdio_init_all();
    while ((!stdio_usb_connected())) {
        // waits for usb connection, REMOVE to continue without waiting for connection
    }

    espInit(); // initialize ESP32 module

    watchdog_enable(2000, 1); // enables watchdog to check for reboots
}

int main() {
    initializeHardware();

    networkTryToConnectToNetworkUntilSuccessful();

    freeRtosTaskWrapperRegisterTask(enterBootModeTask, "enterBootModeTask", 0, FREERTOS_CORE_0);
    freeRtosTaskWrapperRegisterTask(ledTask, "ledTask", 0, FREERTOS_CORE_1);

    freeRtosTaskWrapperStartScheduler();
}
