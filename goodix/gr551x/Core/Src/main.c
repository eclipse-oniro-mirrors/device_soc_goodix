/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdint.h"
#include "user_app.h"
#include "user_periph_setup.h"
#include "gr55xx_sys.h"
#include "custom_config.h"
#include "log_serial.h"
#include "app_rng.h"

uint16_t g_random_seed[8] = {0x1234, 0x5678, 0x90AB, 0xCDEF, 0x1468, 0x2345, 0x5329, 0x2411};
#define RNG_PARAM           {APP_RNG_TYPE_POLLING, {RNG_SEED_FR0_S0, RNG_LFSR_MODE_59BIT, RNG_OUTPUT_LFSR, RNG_POST_PRO_NOT}}


void hi_watchdog_enable(void){};
void hi_watchdog_disable(void){};

/* Initialize ble stack. */
void BLE_StackInit (void)
{
    //InitBtStack();
}

/* Initialize system peripherals. */
void SystemPeripheralsInit(void)
{
    bsp_log_init();    
    app_periph_init();
    printf("GR551x system start!!!\r\n");
}

/* Initialize Hardware RNG peripherals. */
void HardwareRandomInit(void)
{
    app_rng_params_t params_t = RNG_PARAM;
    app_rng_init(&params_t, NULL);
}

int HardwareRandomGet(uint32_t *p_random)
{   
    int ret = 0;

    ret = app_rng_gen_sync(g_random_seed, p_random);
    if (ret != 0) {
        return -1;
    }

    return 0;
} 

/**
  * @brief  The application entry point.
  * @retval int
  */
extern void OHOS_Boot(void);
int main(void)
{
    OHOS_Boot();
    while(1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
