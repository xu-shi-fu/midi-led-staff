// mls_config.h

#ifndef __mls_config_h__
#define __mls_config_h__

#define mls_ENABLE_TUSB_MIDI 0 // 0='no';1='yes'

#define RMT_LED_STRIP_GPIO_NUM GPIO_NUM_6 // 设置用于输出的 GPIO 口

#define CP_RX_BUFFER_SIZE (256 * 4)
#define CP_TX_BUFFER_SIZE 256
#define CP_RX_BLOCK_ARRAY_CAPACITY 16
#define CP_TX_BLOCK_ARRAY_CAPACITY 16

#define CP_VERSION_MAJOR 1
#define CP_VERSION_MINOR 0

#endif // __mls_config_h__
