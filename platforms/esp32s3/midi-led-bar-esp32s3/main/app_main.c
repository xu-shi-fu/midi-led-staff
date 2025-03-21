/*
 * SPDX-FileCopyrightText: 2019 Ha Thach (tinyusb.org)
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2022-2024 Espressif Systems (Shanghai) CO LTD
 */

#include "mlb_ble.h"
#include "mlb_tusb_midi.h"
#include "mlb_ws2812_led.h"
#include "mlb_engine.h"
#include "mlb_wifi.h"
#include "mlb_settings.h"
#include "mlb_nvs.h"
#include "mlb_udp.h"

const char *TAG = "MIDI-LED-BAR";

////////////////////////////////////////////////////////////////////////////////
// tasks

static TaskHandle_t task_handle_led = NULL;
static TaskHandle_t task_handle_ble = NULL;
static TaskHandle_t task_handle_midi = NULL;
static TaskHandle_t task_handle_engine = NULL;
static TaskHandle_t task_handle_wifi = NULL;
static TaskHandle_t task_handle_udp = NULL;

void run_idle_loop()
{
    while (1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void mlb_task_ble(void *p)
{
    mlb_ble_loop();
    run_idle_loop();
}

void mlb_task_led(void *p)
{
    mlb_led_loop();
    run_idle_loop();
}

void mlb_task_midi(void *p)
{
    mlb_midi_loop();
    run_idle_loop();
}

void mlb_task_engine(void *p)
{
    mlb_engine_loop();
    run_idle_loop();
}

void mlb_task_wifi(void *p)
{
    mlb_wifi_loop();
    run_idle_loop();
}

void mlb_task_udp(void *p)
{
    mlb_udp_loop(true);
    run_idle_loop();
}

////////////////////////////////////////////////////////////////////////////////

void app_main(void)
{
    mlb_nvs_init();
    mlb_settings_init();
    mlb_ble_init();
    mlb_wifi_init();
    mlb_udp_init();
    mlb_led_init();
    mlb_midi_init();
    mlb_engine_init();

    uint32_t stack_depth = 16 * 1024;

    xTaskCreate(mlb_task_ble, "task-ble", stack_depth, NULL, 1, &task_handle_ble);
    xTaskCreate(mlb_task_led, "task-led", stack_depth, NULL, 1, &task_handle_led);
    xTaskCreate(mlb_task_engine, "task-engine", stack_depth, NULL, 1, &task_handle_engine);
    xTaskCreate(mlb_task_wifi, "task-wifi", stack_depth, NULL, 1, &task_handle_wifi);
    xTaskCreate(mlb_task_udp, "task-udp", stack_depth, NULL, 1, &task_handle_udp);
    xTaskCreate(mlb_task_midi, "task-midi", stack_depth, NULL, 1, &task_handle_midi);
}
