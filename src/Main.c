#define SOURCE_FILE "MAIN"

#include "Common.h"
#include "Esp.h"
#include "FreeRtosQueueWrapper.h"
#include "FreeRtosTaskWrapper.h"
#include "Network.h"

#include <hardware/watchdog.h>
#include <pico/bootrom.h>
#include <pico/stdlib.h>

/* region LED HANDLER */

#define LED0_PIN 22
#define LED1_PIN 24
#define LED2_PIN 25

void led_init(uint8_t gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
}

void leds_init() {
    led_init(LED0_PIN);
    led_init(LED1_PIN);
    led_init(LED2_PIN);
}

void leds_all_on() {
    gpio_put(LED0_PIN, 1);
    gpio_put(LED1_PIN, 1);
    gpio_put(LED2_PIN, 1);
}

void leds_all_off() {
    gpio_put(LED0_PIN, 0);
    gpio_put(LED1_PIN, 0);
    gpio_put(LED2_PIN, 0);
}

/* endregion LED HANDLER */

_Noreturn void ledTask(void) {
    while (true) {
        PRINT("LEDs should now turn on");
        leds_all_on();
        freeRtosTaskWrapperTaskSleep(2000);
        PRINT("LEDs should now turned off");
        leds_all_off();
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

void init(void) {
    // First check if we crash last time -> reboot into boot rom mode
    if (watchdog_enable_caused_reboot()) {
        reset_usb_boot(0, 0);
    }

    // init usb
    stdio_init_all();
    // waits for usb connection, REMOVE to continue without waiting for connection
    while ((!stdio_usb_connected())) {}

    // Checks connection to ESP and initialize ESP
    espInit();

    // create freeRTOS task queue
    freeRtosQueueWrapperCreate();

    // enables watchdog to check for reboots
    watchdog_enable(2000, 1);
}

int main() {
    // initialize hardware
    init();
    leds_init();

    networkTryToConnectToNetworkUntilSuccessful();

    // add freeRTOS tasks
    freeRtosTaskWrapperRegisterTask(enterBootModeTask, "enterBootModeTask", 0, FREERTOS_CORE_0);
    freeRtosTaskWrapperRegisterTask(ledTask, "ledTask", 0, FREERTOS_CORE_1);

    // starts freeRTOS tasks
    freeRtosTaskWrapperStartScheduler();
}
