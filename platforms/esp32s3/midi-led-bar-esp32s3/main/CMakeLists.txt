
idf_component_register(SRCS "led_strip_encoder.c" "mlb_tusb_midi.c" "mlb_ws2812_led.c" "mlb_ble.c" "app_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES "esp_timer" "driver"
                       PRIV_REQUIRES "esp_timer")
