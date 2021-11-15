/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

void SystemPeripheralsInit(void);
void HardwareRandomInit(void);
void OSVectorInit(void);
void FileSystemInit(void);
void OHOS_SystemInit(void); // this is the service loader function for OHOS
void WDT_IRQHandler(void);
void BLE_SDK_Handler(void);
void BLE_IRQHandler(void);
void DMA_IRQHandler(void);
void SPI_M_IRQHandler(void);
void SPI_S_IRQHandler(void);
void EXT0_IRQHandler(void);
void EXT1_IRQHandler(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void QSPI0_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
void AES_IRQHandler(void);
void HMAC_IRQHandler(void);
void EXT2_IRQHandler(void);
void RNG_IRQHandler(void);
void PMU_IRQHandler(void);
void PKC_IRQHandler(void);
void XQSPI_IRQHandler(void);
void QSPI1_IRQHandler(void);
void PWR_CMD_IRQHandler(void);
void BLESLP_IRQHandler(void);
void SLPTIMER_IRQHandler(void);
void COMP_IRQHandler(void);
void AON_WDT_IRQHandler(void);
void I2S_M_IRQHandler(void);
void I2S_S_IRQHandler(void);
void ISO7816_IRQHandler(void);
void PRESENT_IRQHandler(void);
void CALENDAR_IRQHandler(void);
void DUAL_TIMER_IRQHandler(void);
void SVC_Handler(void);
void OHOS_SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
