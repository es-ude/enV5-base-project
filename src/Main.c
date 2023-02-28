#define SOURCE_FILE "MAIN"

#include <pico/stdlib.h>
#include <hardware/watchdog.h>
#include <pico/bootrom.h>
#include "Esp.h"
#include "FreeRtosQueueWrapper.h"
#include "FreeRtosTaskWrapper.h"
#include "Common.h"

#define LED0_PIN 22
#define LED1_PIN 24
#define LED2_PIN 25


void leds_all_on()
{
    gpio_put(LED0_PIN, 1);
    gpio_put(LED1_PIN, 1);
    gpio_put(LED2_PIN, 1);
}

void leds_all_off()
{
    gpio_put(LED0_PIN, 0);
    gpio_put(LED1_PIN, 0);
    gpio_put(LED2_PIN, 0);
}

void mainTask(void) {
    PRINT_DEBUG("LEDs should now turn on\n");
    leds_all_on();
    freeRtosTaskWrapperTaskSleep(1000);
    leds_all_off();
    PRINT_DEBUG("LEDs should now turned off\n");
    printf("you can also print with this, or print a number: %d", 1);
}

// Goes into bootloader mode when 'r' is pressed
_Noreturn void enterBootModeTask(void) {
    while (true) {
        if (getchar_timeout_us(10) == 'r' || !stdio_usb_connected()) {
            reset_usb_boot(0, 0);
        }
        // Watchdog update needs to be performed frequent, otherwise the device
        // will crash
        watchdog_update();
        freeRtosTaskWrapperTaskSleep(1000);
    }
}

void init(void) {
    // First check if we crash last time -> reboot into boot rom mode
    if (watchdog_enable_caused_reboot()) {
        reset_usb_boot(0, 0);
    }
    // init usb, queue and watchdog
    stdio_init_all();
    // waits for usb connection, REMOVE to continue without waiting for
    // connection
    while ((!stdio_usb_connected()))
        ;
    // Checks connection to ESP and initializes
    espInit();
    // Create FreeRTOS task queue
    freeRtosQueueWrapperCreate();
    // enables watchdog to check for reboots
    watchdog_enable(2000, 1);
}

int main() {
    init();
    freeRtosTaskWrapperRegisterTask(enterBootModeTask, "enterBootModeTask");
    freeRtosTaskWrapperRegisterTask(mainTask, "mainTask");

    // Starts FreeRTOS tasks
    freeRtosTaskWrapperStartScheduler();
}