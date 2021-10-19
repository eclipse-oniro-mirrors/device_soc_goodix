#ifndef __PAW3205DB_H__
#define __PAW3205DB_H__

#include "gr55xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    CPI_600  = 0,
    CPI_800  = 1,
    CPI_1000 = 2,
    CPI_1200 = 3,
    CPI_1600 = 4,
} paw_cpi_t;

typedef struct
{
    bool        edge_sen;       /**< True: edge-sensitive, False: level-sensitive. */
    bool        power_down;
    paw_cpi_t   paw_cpi;
} paw_cfg_t;

typedef void (*paw3205_motion_callback_t)(void);

void paw3205db_init(paw_cfg_t *p_paw_cfg, paw3205_motion_callback_t motion_callback);
uint16_t paw3205db_pid_get(void);
uint8_t paw3205db_vid_get(void);
void paw3205db_cfg_set(paw_cfg_t *p_paw_cfg);
void paw3205db_sleep_disable(void);
void paw3205db_led_shutter_set(bool is_enable);
void paw3205db_sleep_1_mode_set(bool is_enable);
void paw3205db_sleep_2_mode_set(bool is_enable);
void paw3205db_sleep_1_enter(void);
void paw3205db_sleep_2_enter(void);
void paw3205db_sleep_wakeup(void);
bool paw3205db_motion_occurred(void);
int8_t paw3205db_delta_x_get(void);
int8_t paw3205db_delta_y_get(void);
#endif
