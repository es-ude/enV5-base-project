#define SOURCE_FILE "BLINKLED"

#include <hardware/spi.h>

#include "hardware/watchdog.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "Common.h"
#include "EnV5HwConfiguration.h"
#include "EnV5HwController.h"
#include "Esp.h"
#include "FreeRtosTaskWrapper.h"
#include "FpgaConfigurationHandler.h"
#include "Flash.h"


spiConfiguration_t spiToFlashConfig = {.sckPin = FLASH_SPI_CLOCK,
                                       .misoPin = FLASH_SPI_MISO,
                                       .mosiPin = FLASH_SPI_MOSI,
                                       .baudrate = FLASH_SPI_BAUDRATE,
                                       .spiInstance = FLASH_SPI_MODULE,
                                       .csPin = FLASH_SPI_CS};

flashConfiguration_t flashConfig = {
    .spiConfiguration = &spiToFlashConfig,
};

size_t blinkSlowLength = 85540;

void downloadLedFile(){
    int32_t startSector = 0;

    fpgaConfigurationHandlerError_t error =
        fpgaConfigurationHandlerDownloadConfigurationViaUsb(&flashConfig, startSector);

    if (error != FPGA_RECONFIG_NO_ERROR) {
        PRINT("Error 0x%02X occurred during download.", error);
        return;
    }
    PRINT("Download Successful!\n");
}

/*! \brief Goes into bootloader mode when 'r' is pressed
 */
_Noreturn void enterBootModeTask(void) {
    while (true) {
        if (getchar_timeout_us(10) == 'r') {
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

    espInit(); // initialize ESP32 module

    flashInit(&flashConfig);

    watchdog_enable(10000, 1);
    PRINT_DEBUG("DONE");
}

int main() {
    initializeHardware();

    downloadLedFile();
    env5HwControllerFpgaPowersOn();

    freeRtosTaskWrapperRegisterTask(enterBootModeTask, "enterBootModeTask", 0, FREERTOS_CORE_0);

    freeRtosTaskWrapperStartScheduler();
}

