/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#include <stdio.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"

#include <string.h>
#include "hal_file.h"
#include "utils_file.h"

#define HELLO_TASK_STACK_SIZE   4096
#define HELLO_TASK_PRIO         25
#define LED_GPIO                44

static void *HelloTask(const char *arg)
{
    (void)arg;
    int led_set = 1;

    IoTGpioInit(LED_GPIO);
    IoTGpioSetDir(LED_GPIO, IOT_GPIO_DIR_OUT);

	while (1) {

		printf("hello world!\n");
        led_set = 0x1 ^ led_set;
        IoTGpioSetOutputVal(LED_GPIO, led_set);
		osDelay(1000);
	}
}

void HelloTaskEntry(void)
{
    osThreadAttr_t attr;

    attr.name = "HelloTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = HELLO_TASK_STACK_SIZE;
    attr.priority = HELLO_TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)HelloTask, NULL, &attr) == NULL) {
        printf("[HelloDemo] Falied to create HelloTask!\n");
    }
}

SYS_RUN(HelloTaskEntry);
