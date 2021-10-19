/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Provide a task example.
 */

#include "los_task.h"
#include "los_interrupt.h"
#include "los_compiler.h"
#include "los_arch_interrupt.h"
#include "cmsis_os2.h"
#include "gr55xx.h"
#include "log_serial.h"
#include "core_cm4.h"
#include "app_log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define CN_MINISECONDS_IN_SECOND  1000

extern void WDT_IRQHandler(void);
extern void BLE_SDK_Handler(void);
extern void BLE_IRQHandler(void);
extern void DMA_IRQHandler(void);
extern void SPI_M_IRQHandler(void);
extern void SPI_S_IRQHandler(void);
extern void EXT0_IRQHandler(void);
extern void EXT1_IRQHandler(void);
extern void TIMER0_IRQHandler(void);
extern void TIMER1_IRQHandler(void);
extern void DUAL_TIMER_IRQHandle(void);
extern void QSPI0_IRQHandler(void);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void AES_IRQHandler(void);
extern void HMAC_IRQHandler(void);
extern void EXT2_IRQHandler(void);
extern void RNG_IRQHandler(void);
extern void PMU_IRQHandler(void);
extern void PKC_IRQHandler(void);
extern void XQSPI_IRQHandler(void);
extern void QSPI1_IRQHandler(void);
extern void PWR_CMD_IRQHandler(void);
extern void BLESLP_IRQHandler(void);
extern void SLPTIMER_IRQHandler(void);
extern void COMP_IRQHandler(void);
extern void AON_WDT_IRQHandler(void);
extern void I2S_M_IRQHandler(void);
extern void I2S_S_IRQHandler(void);
extern void ISO7816_IRQHandler(void);
extern void PRESENT_IRQHandler(void);
extern void CALENDAR_IRQHandler(void);
void DUAL_TIMER_IRQHandle(void) {};
extern void SVC_Handler(void);

extern void FileSystemInit(void);

void OSVectorInit(void)
{
    uint32_t *p_vector = (uint32_t *)SCB->VTOR;
    p_vector[SVCall_IRQn + OS_SYS_VECTOR_CNT]  = SVC_Handler;
    OsSetVector(WDT_IRQn, (HWI_PROC_FUNC)WDT_IRQHandler);
    OsSetVector(BLE_SDK_IRQn, (HWI_PROC_FUNC)BLE_SDK_Handler);
    OsSetVector(BLE_IRQn, (HWI_PROC_FUNC)BLE_IRQHandler);
    OsSetVector(DMA_IRQn, (HWI_PROC_FUNC)DMA_IRQHandler);
    OsSetVector(SPI_M_IRQn, (HWI_PROC_FUNC)SPI_M_IRQHandler);
    OsSetVector(SPI_S_IRQn, (HWI_PROC_FUNC)SPI_S_IRQHandler);
    OsSetVector(EXT0_IRQn, (HWI_PROC_FUNC)EXT0_IRQHandler);
    OsSetVector(EXT1_IRQn, (HWI_PROC_FUNC)EXT1_IRQHandler);
    OsSetVector(TIMER0_IRQn, (HWI_PROC_FUNC)TIMER0_IRQHandler);
    OsSetVector(TIMER1_IRQn, (HWI_PROC_FUNC)TIMER1_IRQHandler);
    OsSetVector(DUAL_TIMER_IRQn, (HWI_PROC_FUNC)DUAL_TIMER_IRQHandle);
    OsSetVector(QSPI0_IRQn, (HWI_PROC_FUNC)QSPI0_IRQHandler);
    OsSetVector(UART0_IRQn, (HWI_PROC_FUNC)UART0_IRQHandler);
    OsSetVector(UART1_IRQn, (HWI_PROC_FUNC)UART1_IRQHandler);
    OsSetVector(I2C0_IRQn, (HWI_PROC_FUNC)I2C0_IRQHandler);
    OsSetVector(I2C1_IRQn, (HWI_PROC_FUNC)I2C1_IRQHandler);
    OsSetVector(AES_IRQn, (HWI_PROC_FUNC)AES_IRQHandler);
    OsSetVector(HMAC_IRQn, (HWI_PROC_FUNC)HMAC_IRQHandler);
    OsSetVector(EXT2_IRQn, (HWI_PROC_FUNC)EXT2_IRQHandler);
    OsSetVector(RNG_IRQn, (HWI_PROC_FUNC)RNG_IRQHandler);
    OsSetVector(PMU_IRQn, (HWI_PROC_FUNC)PMU_IRQHandler);
    OsSetVector(PKC_IRQn, (HWI_PROC_FUNC)PKC_IRQHandler);
    OsSetVector(XQSPI_IRQn, (HWI_PROC_FUNC)XQSPI_IRQHandler);
    OsSetVector(QSPI1_IRQn, (HWI_PROC_FUNC)QSPI1_IRQHandler);
    OsSetVector(PWR_CMD_IRQn, (HWI_PROC_FUNC)PWR_CMD_IRQHandler);
    OsSetVector(BLESLP_IRQn, (HWI_PROC_FUNC)BLESLP_IRQHandler);
    OsSetVector(SLPTIMER_IRQn, (HWI_PROC_FUNC)SLPTIMER_IRQHandler);
    OsSetVector(COMP_EXT_IRQn, (HWI_PROC_FUNC)COMP_IRQHandler);
    OsSetVector(AON_WDT_IRQn, (HWI_PROC_FUNC)AON_WDT_IRQHandler);
    OsSetVector(I2S_M_IRQn, (HWI_PROC_FUNC)I2S_M_IRQHandler);
    OsSetVector(I2S_S_IRQn, (HWI_PROC_FUNC)I2S_S_IRQHandler);
    OsSetVector(ISO7816_IRQn, (HWI_PROC_FUNC)ISO7816_IRQHandler);
    OsSetVector(PRESENT_IRQn, (HWI_PROC_FUNC)PRESENT_IRQHandler);
    OsSetVector(CALENDAR_IRQn, (HWI_PROC_FUNC)CALENDAR_IRQHandler);
    
    NVIC_SetPriorityGrouping(0x3);
}

VOID HalDelay(UINT32 ticks)
{
    delay_ms(ticks);
}

/**
 * @brief Convert miniseconds to system ticks
 * @param ms Indicates the mimiseconds to convert
 * @return Returns the corresponding ticks of specified time
 */
uint32_t Time2Tick(uint32_t ms)
{
    uint64_t ret;
    ret = ((uint64_t)ms * osKernelGetTickFreq()) / CN_MINISECONDS_IN_SECOND;
    return (uint32_t)ret;
}

/**
 * @brief we make the sleep function as someone need this
 *
 */
void sleep(int seconds)
{
    for (int i = 0; i < seconds; i++) {
        LOS_TaskDelay(Time2Tick(CN_MINISECONDS_IN_SECOND));
    }

    return;
}
/*
 * @brief Make the OHOS_SystemInit as a task to load the all the service initialization,
 *        and you could modify the stacksize and prior if the default could not satisfy
 */
extern void OHOS_SystemInit(void); // this is the service loader function for OHOS

#define CN_MAINBOOT_TASK_STACKSIZE  0X4000
#define CN_MAINBOOT_TASK_PRIOR      2
#define CN_MAINBOOT_TASK_NAME       "MainBoot"
static void MainBoot(void)
{
    UINT32 uwRet;
    UINT32 taskID;
    TSK_INIT_PARAM_S stTask = {0};

    stTask.pfnTaskEntry = (TSK_ENTRY_FUNC)OHOS_SystemInit;
    stTask.uwStackSize = CN_MAINBOOT_TASK_STACKSIZE;
    stTask.pcName = CN_MAINBOOT_TASK_NAME;
    stTask.usTaskPrio = CN_MAINBOOT_TASK_PRIOR; /* Os task priority is 6 */
    uwRet = LOS_TaskCreate(&taskID, &stTask);
    if (uwRet != LOS_OK) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>MainBoot task create failed!!!");
    }
}

int GetDevUdid( char* udid, int udidLen)
{
    uint8_t uid[16];

    if (sys_device_uid_get(uid))
    {
        return -1;
    }

    udid[0] = uid[3];
    udid[1] = uid[4];
    udid[2] = uid[5];
    udid[3] = uid[6];
    udid[4] = uid[10];
    udid[5] = uid[13];
    udid[6] = uid[14];
    udid[7] = uid[15];
    return 0;
}

/***
 * @brief This is the ohos entry, and you could call this in your main funciton after the
 *        necessary hardware has been initialized.
 */
void OHOS_Boot(void)
{
    UINT32 ret; 
    ret = LOS_KernelInit();
    if (ret == LOS_OK) {
        OSVectorInit();
        SystemPeripheralsInit();
        HardwareRandomInit();
        FileSystemInit();
        MainBoot();
        LOS_Start();
    }
    return;  // and should never come here
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


