idf_component_register(SRCS "mls_cp_server.c" "mls_tasks.c" "mls_app.c" "app_main.c"

        "mls_ble.c" "mls_buffer.c" "mls_control_protocol.c" "mls_engine.c" "mls_errors.c" "mls_nvs.c"
        "mls_settings.c" "mls_cp_udp_adapter.c" "mls_wifi.c" "mls_ws2812_led.c" "led_strip_encoder.c"

                    INCLUDE_DIRS "."  
                    REQUIRES "esp_timer" "esp_wifi" "driver" 
                    PRIV_REQUIRES "esp_timer" nvs_flash                    
                    )
