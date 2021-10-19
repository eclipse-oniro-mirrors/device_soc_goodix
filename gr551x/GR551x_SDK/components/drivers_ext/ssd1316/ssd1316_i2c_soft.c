#include "ssd1316_i2c_soft.h"
#include "gr55xx_hal.h"
#include "system_sdk.h"

#define I2C_READ_BIT            0x01
#define I2C_WRITE_BIT           0x00

static volatile uint32_t i2c_baud_rate = USER_I2C_BAUDRATE_100K;

__STATIC_INLINE void sda_input_output_set(uint8_t mode) {
    ll_gpio_init_t GPIO_InitStruct;
    ll_gpio_struct_init(&GPIO_InitStruct);
    GPIO_InitStruct.pin = LL_GPIO_PIN_5;    // Set 1 pin or serval pins.
    GPIO_InitStruct.mode = mode;
    GPIO_InitStruct.pull = LL_GPIO_PULL_DOWN;
    ll_gpio_init(GPIO0, &GPIO_InitStruct);
}

static void i2c_delay(void)
{
    switch (i2c_baud_rate){
        case (USER_I2C_BAUDRATE_400K):
            sys_delay_us(1);
            break;
        case (USER_I2C_BAUDRATE_200K):
            sys_delay_us(2);
            break;
        case (USER_I2C_BAUDRATE_100K):
            sys_delay_us(4);
            break;
        default :
            sys_delay_us(4);
            break;
    }
}

static void i2c_start(void)
{
    sda_input_output_set(LL_AON_GPIO_MODE_OUTPUT);

    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_5);
    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
    sys_delay_us(1);
    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_5);
    sys_delay_us(1);
    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
    sys_delay_us(1);
}

static void i2c_stop(void)
{
    sda_input_output_set(LL_GPIO_MODE_OUTPUT);

    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_5);
    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
    sys_delay_us(1);
    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_5);
    sys_delay_us(1);
}

static void i2c_send_ack(void)
{
    sda_input_output_set(LL_GPIO_MODE_OUTPUT);

    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_5);
    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
    i2c_delay();
    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
    i2c_delay();
}

static void i2c_send_nack(void)
{
    sda_input_output_set(LL_GPIO_MODE_OUTPUT);

    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_5);
    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
    i2c_delay();
    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
    i2c_delay();
}

static uint8_t i2c_receive_ack(void)
{
    uint8_t ret = USER_I2C_ACK;
//    sda_input_output_set(LL_GPIO_MODE_INPUT);

    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
    i2c_delay();
    if (ll_gpio_is_input_pin_set(GPIO0, LL_GPIO_PIN_5))
        ret = USER_I2C_NACK;
    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
    i2c_delay();

    return ret;
}

static void i2c_write_byte(uint8_t data)
{
    uint8_t idx;
    sda_input_output_set(LL_GPIO_MODE_OUTPUT);

    for (idx = 0; idx < 8; idx++){
        if (data & (0x80 >> idx))
            ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_5);
        else
            ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_5);
        ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
        i2c_delay();
        ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
        i2c_delay();
    }
    sda_input_output_set(LL_GPIO_MODE_INPUT);
    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
}

static uint8_t i2c_read_byte(void)
{
    uint8_t idx, ret;
    sda_input_output_set(LL_GPIO_MODE_INPUT);

    ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
    for (idx = 0; idx < 8; idx++){
        ret <<= 1;
        ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6);
        i2c_delay();
        if (ll_gpio_is_input_pin_set(GPIO0, LL_GPIO_PIN_5))
            ret |= 1;
        else
            ret &= ~1;
        ll_gpio_reset_output_pin(GPIO0, LL_GPIO_PIN_6);
        i2c_delay();
    }

    return ret;
}

static void i2c_send_address_with_write(uint8_t dev_addr)
{
    i2c_write_byte((dev_addr << 1) | I2C_WRITE_BIT);
}

static void i2c_send_address_with_read(uint8_t dev_addr)
{
    i2c_write_byte((dev_addr << 1) | I2C_READ_BIT);
}

void SSD_UserI2cConfig(uint32_t BaudRate)
{
    gpio_init_t GPIO_InitStruct;
    GPIO_InitStruct.mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.mux  = GPIO_MUX_7;
    GPIO_InitStruct.pull = APP_IO_NOPULL;
    GPIO_InitStruct.pin  = GPIO_PIN_5 | GPIO_PIN_6;
    hal_gpio_init(GPIO0, &GPIO_InitStruct);

    SystemCoreSetClock(CPLL_S64M_CLK);

    ll_gpio_set_output_pin(GPIO0, LL_GPIO_PIN_6 | LL_GPIO_PIN_5);
    i2c_baud_rate = BaudRate;
}

uint8_t SSD_UserI2cWriteByteWithStart(uint8_t dev_addr)
{
    uint8_t status = USER_I2C_DEFAULT;
    uint32_t retry;

    retry = 200;
    while(retry-- > 0 && !ll_gpio_is_output_pin_set(GPIO0, LL_GPIO_PIN_5));
    if(retry == 0)
    {
        status |= USER_I2C_BUSY_BIT;
    }

    i2c_start();
    i2c_send_address_with_write(dev_addr);
    status |= i2c_receive_ack();

    return status;
}

uint8_t SSD_UserI2cWriteByte(uint8_t data)
{
    uint8_t status = USER_I2C_DEFAULT;

    i2c_write_byte(data);
    status |= i2c_receive_ack();
    return status;
}

uint8_t SSD_UserI2cWriteByteWithStop(uint8_t data)
{
    uint8_t status = USER_I2C_DEFAULT;

    i2c_write_byte(data);
    status |= i2c_receive_ack();
    i2c_stop();
    return status;
}

uint8_t SSD_UserI2cReadByteWithStart(uint8_t dev_addr)
{
    uint8_t status = USER_I2C_DEFAULT;

    i2c_start();
    i2c_send_address_with_read(dev_addr);
    status |= i2c_receive_ack();

    return status;
}

uint8_t SSD_UserI2cReadByte(uint8_t *data)
{
    uint8_t status = USER_I2C_DEFAULT;

    *data = i2c_read_byte();
    i2c_send_ack();

    return status;
}

uint8_t SSD_UserI2cReadByteWithStop(uint8_t *data)
{
    uint8_t status = USER_I2C_NACK;

    *data = i2c_read_byte();
    i2c_send_nack();
    i2c_stop();

    return status;
}
