#include <stdio.h>
#include "gr55xx.h"
#include "log_serial.h"
#include "app_log.h"

static uint8_t s_uart_tx_buffer[UART_TX_BUFF_SIZE];
static bool uart_initialized = false;

void bsp_uart_init(void)
{
    uint32_t ret;
    app_uart_tx_buf_t uart_buffer;
    app_uart_params_t uart_param;

    uart_buffer.tx_buf       = s_uart_tx_buffer;
    uart_buffer.tx_buf_size  = UART_TX_BUFF_SIZE;

    uart_param.id                   = LOG_UART_ID;
    uart_param.init.baud_rate       = LOG_UART_BAUDRATE;
    uart_param.init.data_bits       = UART_DATABITS_8;
    uart_param.init.stop_bits       = UART_STOPBITS_1;
    uart_param.init.parity          = UART_PARITY_NONE;
    uart_param.init.hw_flow_ctrl    = UART_HWCONTROL_NONE;
    uart_param.init.rx_timeout_mode = UART_RECEIVER_TIMEOUT_ENABLE;
    uart_param.pin_cfg.rx.type      = LOG_UART_RX_IO_TYPE;
    uart_param.pin_cfg.rx.pin       = LOG_UART_RX_PIN;
    uart_param.pin_cfg.rx.mux       = LOG_UART_RX_PINMUX;
    uart_param.pin_cfg.rx.pull      = LOG_UART_RX_PULL;
    uart_param.pin_cfg.tx.type      = LOG_UART_TX_IO_TYPE;
    uart_param.pin_cfg.tx.pin       = LOG_UART_TX_PIN;
    uart_param.pin_cfg.tx.mux       = LOG_UART_TX_PINMUX;
    uart_param.pin_cfg.tx.pull      = LOG_UART_TX_PULL;
    uart_param.use_mode.type        = APP_UART_TYPE_INTERRUPT;
    app_uart_init(&uart_param, NULL, &uart_buffer);

    uart_initialized = true;
}

void bsp_uart_send(uint8_t *p_data, uint16_t length)
{
    if (uart_initialized != true) {
        return;
    }

    app_uart_transmit_async(LOG_UART_ID, p_data, length);
}

void bsp_uart_flush(void)
{
    app_uart_flush(LOG_UART_ID);
}

void bsp_log_init(void)
{
    app_log_init_t  log_init;

    log_init.filter.level                 = APP_LOG_LVL_DEBUG;
    log_init.fmt_set[APP_LOG_LVL_ERROR]   = APP_LOG_FMT_ALL & (~APP_LOG_FMT_TAG);
    log_init.fmt_set[APP_LOG_LVL_WARNING] = APP_LOG_FMT_LVL;
    log_init.fmt_set[APP_LOG_LVL_INFO]    = APP_LOG_FMT_LVL;
    log_init.fmt_set[APP_LOG_LVL_DEBUG]   = APP_LOG_FMT_LVL;

    bsp_uart_init();
    app_log_init(&log_init, bsp_uart_send, bsp_uart_flush);
    app_assert_init();
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
	return 0;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    bsp_uart_send(ptr, len);
	return len;
}

