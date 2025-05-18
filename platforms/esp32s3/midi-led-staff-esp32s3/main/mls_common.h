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

#include <sys/types.h>
#include <sys/socket.h>

#include "driver/gpio.h"
#include "driver/rmt_tx.h"

#include "esp_log.h"
#include "esp_timer.h"
#include "esp_chip_info.h"
#include "esp_system.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "sdkconfig.h"
#include "tinyusb.h"

#include "mls_config.h"

extern const char *TAG;

#endif // __common_h__
