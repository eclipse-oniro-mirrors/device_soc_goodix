#ifndef __LOG_SERIAL_H
#define __LOG_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "app_io.h"
#include "app_uart.h"

#define LOG_UART_ID                     APP_UART_ID_0
#define LOG_UART_BAUDRATE               115200
#define LOG_UART_TX_IO_TYPE             APP_IO_TYPE_NORMAL
#define LOG_UART_RX_IO_TYPE             APP_IO_TYPE_NORMAL
#define LOG_UART_TX_PIN                 APP_IO_PIN_10
#define LOG_UART_RX_PIN                 APP_IO_PIN_11
#define LOG_UART_TX_PINMUX              APP_IO_MUX_2
#define LOG_UART_RX_PINMUX              APP_IO_MUX_2
#define LOG_UART_TX_PULL                APP_IO_PULLUP
#define LOG_UART_RX_PULL                APP_IO_PULLUP

/**< Size of app uart tx buffer. */
#define UART_TX_BUFF_SIZE               0x2000    

void bsp_log_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __LOG_SERIAL_H */
