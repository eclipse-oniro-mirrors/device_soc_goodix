
#include "paw3205db.h"
#include "app_gpiote.h"


#define PAW3205DB_PRODUCT_ID1_ADDR             0x00
#define PAW3205DB_PRODUCT_ID2_ADDR             0x01
#define PAW3205DB_MOTION_STATUS_ADDR           0x02
#define PAW3205DB_DELTA_X_ADDR                 0x03
#define PAW3205DB_DELTA_Y_ADDR                 0x04
#define PAW3205DB_OPERATION_MODE_ADDR          0x05
#define PAW3205DB_CONFIGURATION_ADDR           0x06

#define PAW3205DB_IMAGE_QUALITY_ADDR           0x07
#define PAW3205DB_OPERATION_STATE_ADDR         0x08
#define PAW3205DB_WRITE_PROTECT_ADDR           0x09
#define PAW3205DB_SLEEP1_SETTING_ADDR          0x0A
#define PAW3205DB_ENTER_TIME_ADDR              0x0B
#define PAW3205DB_SLEEP2_SETTING_ADDR          0x0C
#define PAW3205DB_IMAGE_THRESHOLD_ADDR         0x0D
#define PAW3205DB_IMAGE_RECOGNITION_ADDR       0x0E

#define PAW3205DB_SCLK_PIN                      MSIO_PIN_0
#define PAW3205DB_SDIO_PIN                      MSIO_PIN_1

#define BITS_ONE_BYTE                            8

#define LED_SHUTTER_BIT                         0x80
#define SLEEP_1_MODE_BIT                        0x10
#define SLEEP_2_MODE_BIT                        0x08

static paw3205_motion_callback_t s_motion_callback;

static void paw3205db_read_register(uint8_t address, uint8_t *p_data)
{
    uint8_t i = 0;
    uint8_t data = 0;

    ll_msio_set_pin_direction(PAW3205DB_SDIO_PIN, LL_MSIO_DIRECTION_OUTPUT);

    /*read flag*/
    address &= ~0x80;

    i = BITS_ONE_BYTE;
 
    while(i--)
    {
        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_RESET);
        hal_msio_write_pin(PAW3205DB_SDIO_PIN, (msio_pin_state_t)((address >> i) & 0x1));
        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_SET);

    }

    ll_msio_set_pin_direction(PAW3205DB_SDIO_PIN, LL_MSIO_DIRECTION_INPUT);

    i = BITS_ONE_BYTE;

    while(i--)
    {
        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_RESET);

        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_SET);
        data |= (hal_msio_read_pin(PAW3205DB_SDIO_PIN) << i);
    }

    *p_data = data;
}

static void paw3205db_write_register(uint8_t address, uint8_t p_data)
{
    uint8_t i = 0;

    ll_msio_set_pin_direction(PAW3205DB_SDIO_PIN, LL_MSIO_DIRECTION_OUTPUT);
    hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_SET);

    /*write flag*/
    address |= 0x80;
    i = BITS_ONE_BYTE;
    while(i--)
   {
        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_RESET);
        hal_msio_write_pin(PAW3205DB_SDIO_PIN, (msio_pin_state_t)((address >> i) & 0x1));

        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_SET);
    }

    i = BITS_ONE_BYTE;

    while(i--)
    {
        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_RESET);
        hal_msio_write_pin(PAW3205DB_SDIO_PIN, (msio_pin_state_t)((p_data >> i) & 0x1));
        hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_SET);
    }
}
static void app_gpiote_evt_handler(app_gpiote_evt_t *p_evt)
{
    if (p_evt->type == APP_IO_TYPE_AON && p_evt->pin & APP_IO_PIN_2)
    {
        if (s_motion_callback)
        {
            s_motion_callback();
        }
    }
}

void paw3205db_init(paw_cfg_t *p_paw_cfg, paw3205_motion_callback_t motion_callback)
{
    msio_init_t MSIO_Init = MSIO_DEFAULT_CONFIG;
    uint8_t     paw_cfg   = 0x80;

    app_gpiote_param_t    gpiote_param;

    gpiote_param.type        = APP_IO_TYPE_AON;
    gpiote_param.pin         = APP_IO_PIN_2;
    gpiote_param.mode        = APP_IO_MODE_IT_FALLING;
    gpiote_param.pull        = APP_IO_PULLUP; 
    gpiote_param.handle_mode = APP_IO_ENABLE_WAKEUP;
    gpiote_param.io_evt_cb   = app_gpiote_evt_handler;

    app_gpiote_init(&gpiote_param, 1);

    MSIO_Init.pin       = PAW3205DB_SCLK_PIN | PAW3205DB_SDIO_PIN;
    MSIO_Init.direction = MSIO_DIRECTION_OUTPUT;
    MSIO_Init.mode      = MSIO_MODE_DIGITAL;

    hal_msio_init(&MSIO_Init);

    hal_msio_write_pin(PAW3205DB_SCLK_PIN, MSIO_PIN_SET);
    hal_msio_write_pin(PAW3205DB_SDIO_PIN, MSIO_PIN_SET);

    s_motion_callback = motion_callback;

    paw_cfg |= p_paw_cfg->paw_cpi;

    if (p_paw_cfg->power_down)
    {
        paw_cfg |= 0x08;
    }

    if (p_paw_cfg->edge_sen)
    {
        paw_cfg |= 0x40;
    }

    paw3205db_write_register(PAW3205DB_CONFIGURATION_ADDR, paw_cfg);
}

void paw3205db_cfg_set(paw_cfg_t *p_paw_cfg)
{
    uint8_t paw_cfg = 0x00;

    paw_cfg = p_paw_cfg->paw_cpi;

    if (p_paw_cfg->power_down)
    {
        paw_cfg |= 0x08;
    }

    if (p_paw_cfg->edge_sen)
    {
        paw_cfg |= 0x40;
    }

    paw3205db_write_register(PAW3205DB_CONFIGURATION_ADDR, paw_cfg);
}

void paw3205db_sleep_disable(void)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);


    op_mode &= ~(SLEEP_1_MODE_BIT);


    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}

void paw3205db_led_shutter_set(bool is_enable)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);

    if (is_enable)
    {
        op_mode |= LED_SHUTTER_BIT;
    }
    else
    {
        op_mode &= ~(LED_SHUTTER_BIT);
    }

    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}

void paw3205db_sleep_1_mode_set(bool is_enable)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);

    if (is_enable)
    {
        op_mode |= SLEEP_1_MODE_BIT;
    }
    else
    {
        op_mode &= ~(SLEEP_1_MODE_BIT);
    }

    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}


void paw3205db_sleep_2_mode_set(bool is_enable)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);

    if (is_enable)
    {
        op_mode |= SLEEP_1_MODE_BIT;
        op_mode |= SLEEP_2_MODE_BIT;
    }
    else
    {
        op_mode &= ~(SLEEP_2_MODE_BIT);
    }

    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}


void paw3205db_sleep_1_enter(void)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);

    op_mode  = op_mode & 0xf8;
    op_mode |= SLEEP_1_MODE_BIT;
    op_mode |= 0x02;

    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}

void paw3205db_sleep_2_enter(void)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);

    op_mode  = op_mode & 0xe0;
    op_mode |= 0x1c;

    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}

void paw3205db_sleep_wakeup(void)
{
    uint8_t op_mode;

    paw3205db_read_register(PAW3205DB_OPERATION_MODE_ADDR, &op_mode);

    op_mode  = op_mode & 0xf8;
    op_mode |= SLEEP_1_MODE_BIT;
    op_mode |= 0x01;

    paw3205db_write_register(PAW3205DB_OPERATION_MODE_ADDR, op_mode);
}

uint16_t paw3205db_pid_get(void)
{
    uint8_t product_id1 = 0;
    uint8_t product_id2 = 0;
    paw3205db_read_register(PAW3205DB_PRODUCT_ID1_ADDR, &product_id1);
    paw3205db_read_register(PAW3205DB_PRODUCT_ID2_ADDR, &product_id2);
    return ((product_id1 << 4) | (product_id2 >> 4)) & 0xFFF;
}

uint8_t paw3205db_vid_get(void)
{
    uint8_t product_id2 = 0;
    paw3205db_read_register(PAW3205DB_PRODUCT_ID2_ADDR, &product_id2);
    return product_id2 & 0xF;
}

bool paw3205db_motion_occurred(void)
{
    uint8_t motion_state = 0;

    paw3205db_read_register(PAW3205DB_MOTION_STATUS_ADDR, &motion_state);

    return (motion_state & 0x80);
}

int8_t paw3205db_delta_x_get(void)
{
    uint8_t delta_x = 0;

    paw3205db_read_register(PAW3205DB_DELTA_X_ADDR, &delta_x);

    return (int8_t)delta_x;
}

int8_t paw3205db_delta_y_get(void)
{
    uint8_t delta_y = 0;

    paw3205db_read_register(PAW3205DB_DELTA_Y_ADDR, &delta_y);

    return (int8_t)delta_y;
}


