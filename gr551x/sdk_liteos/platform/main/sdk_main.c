/*
 * Copyright (c) 2021 GOODIX.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "los_task.h"
#include "cmsis_os2.h"
#include "gr55xx.h"
#include "main.h"
#include "log_serial.h"
#include "app_log.h"

#define CN_MINISECONDS_IN_SECOND    1000
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
        APP_LOG_ERROR("MainBoot task create failed!!!");
    }
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
        FileSystemInit();
        HardwareRandomInit();
        DeviceManagerStart();
        MainBoot();
        LOS_Start();
    }
    return;  // and should never come here
}

VOID HalDelay(UINT32 ticks)
{
    delay_ms(ticks);
}


