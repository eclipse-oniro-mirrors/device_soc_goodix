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
#ifndef __GPIO_GR55XX_H
#define __GPIO_GR55XX_H

#include "app_io.h"
#include "app_gpiote.h"
#include "gpio/gpio_core.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

struct Gr55xxGpioPortConfig {
    app_io_mode_t mode;
    app_io_pull_t pull;
    GpioIrqFunc   irqFunc;
    app_handle_mode_t handleMode;
    void         *arg;
};

struct Gr55xxGpioCntlr {
    struct GpioCntlr cntlr;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__GPIO_GR55XX_H*/
