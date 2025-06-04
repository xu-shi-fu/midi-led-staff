// mls_common_esp.h

#ifndef __mls_common_esp_h__
#define __mls_common_esp_h__

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

#include "mls_common_std.h"
#include "mls_common_mls.h"

#endif // __mls_common_esp_h__
