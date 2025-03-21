// common.h

#ifndef __common_h__
#define __common_h__

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "driver/gpio.h"
#include "driver/rmt_tx.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "esp_log.h"
#include "esp_timer.h"
#include "esp_chip_info.h"
// #include "esp_flash.h"
#include "esp_system.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"
#include "tinyusb.h"

extern const char *TAG;

#define MLB_ENABLE_TUSB_MIDI 0 // 0='no';1='yes'

#endif // __common_h__
