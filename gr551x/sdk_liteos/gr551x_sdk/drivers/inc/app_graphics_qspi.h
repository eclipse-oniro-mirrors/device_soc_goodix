/**
 ****************************************************************************************
 *
 * @file    app_graphics_qspi.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of QSPI app library.
 *
 ****************************************************************************************
 * @attention
  #####Copyright (c) 2019 GOODIX
  All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of GOODIX nor the names of its contributors may be used
    to endorse or promote products derived from this software without
    specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************************
 */

#ifndef __APP_GRAPHICS_QSPI_H__
#define __APP_GRAPHICS_QSPI_H__


/** @addtogroup PERIPHERAL Peripheral Driver
  * @{
  */

/** @addtogroup APP_DRIVER APP DRIVER
 *  @{
 */

/** @defgroup APP_QSPI QSPI
  * @brief QSPI APP module driver.
  * @{
  */


#include <stdbool.h>
#include "grx_hal.h"
#include "app_io.h"
#include "app_qspi.h"
#include "app_drv_error.h"
#include "app_drv_config.h"
#if (APP_DRIVER_CHIP_TYPE == APP_DRIVER_GR5526X)
#include "app_qspi_user_config.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAL_QSPI_MODULE_ENABLED
/* Exported functions --------------------------------------------------------*/
/** @addtogroup APP_GRAPHICS_QSPI_DRIVER_FUNCTIONS Functions
  * @{
  */
/**
 ****************************************************************************************
 * @brief  Read data block in Memory mapped Mode(XIP Mode), The Data is ordered by the order in flash/psram device
 *
 * @param[in]  id : QSPI module ID.
 * @param[in]  address : the address of device connected to QSPI, start from 0x000000
 * @param[in]  buffer  : memory pointer to save the read  data
 * @param[in]  length  : the read length in byte
 * @return true/false
 ****************************************************************************************
 */
bool app_qspi_dma_mmap_read_block(app_qspi_id_t id, uint32_t address, uint8_t * buffer, uint32_t length);

/**
 ****************************************************************************************
 * @brief  Special Async API to write QuadSPI Screen from memory mapped device(flash or psram)
 *         Must enable the two micro-defines to enable this API:
 *         QSPI_ASYNC_SCROLL_DRAW_SCREEN_SUPPORT
 *
 * @param[in]  screen_id:       QSPI module ID for screen, MUST config screen qspi to register mode.
 * @param[in]  storage_id:      QSPI module ID for storage, MUST config storage qspi to mmap(xip) mode.
 * @param[in]  p_screen_cmd:    pointer to the screen control command
 * @param[in]  p_screen_info:   pointer to the screen information
 * @param[in]  p_scroll_config: pointer to the scrolling-config
 * @param[in]  is_first_call:   When called in foreground task, please set true
 * @return true/false
 ****************************************************************************************
 */
bool app_qspi_async_draw_screen(app_qspi_id_t screen_id,
                                app_qspi_id_t storage_id,
                                const app_qspi_screen_command_t * const p_screen_cmd,
                                const app_qspi_screen_info_t * const p_screen_info,
                                app_qspi_screen_scroll_t * p_scroll_config,
                                bool is_first_call);

/**
 ****************************************************************************************
 * @brief  Special Async API to write Screen in vertical direction, and veritical lines are organized in linked list.
 *         Must enable the two micro-defines to enable this API:
 *         QSPI_ASYNC_VERI_LINK_DRAW_SCREEN_SUPPORT
 *
 * @param[in]  screen_id:       QSPI module ID for screen, MUST config screen qspi to register mode.
 * @param[in]  storage_id:      QSPI module ID for storage, MUST config storage qspi to mmap(xip) mode.
 * @param[in]  p_screen_cmd:    pointer to the screen control command
 * @param[in]  p_screen_info:   pointer to the screen information
 * @param[in]  p_link_scroll:   pointer to the linked list structure
 * @param[in]  is_first_call:   When called in foreground task, please set true
 * @return true/false
 ****************************************************************************************
 */
bool app_qspi_async_veri_draw_screen(app_qspi_id_t screen_id,
                                          app_qspi_id_t storage_id,
                                          const app_qspi_screen_command_t * const p_screen_cmd,
                                          const app_qspi_screen_info_t * const p_screen_info,
                                          app_qspi_screen_veri_link_scroll_t * p_link_scroll,
                                          bool is_first_call);

/**
 ****************************************************************************************
 * @brief  Special Async API to write one block of the Screen by DMA-LLP, every line of the block is organized in linked list.
 *         Must enable the micro-defines to enable this API:
 *         QSPI_ASYNC_VERI_LINK_DRAW_SCREEN_SUPPORT
 *
 * @param[in]  screen_id:       QSPI module ID for screen, MUST config screen qspi to register mode.
 * @param[in]  storage_id:      QSPI module ID for storage, MUST config storage qspi to mmap(xip) mode.
 * @param[in]  p_screen_cmd:    pointer to the screen control command
 * @param[in]  p_screen_info:   pointer to the screen information
 * @param[in]  p_block_info:    pointer to the block information structure
 * @param[in]  is_first_call:   When first call, please set true(used this flag to decide whether send cmd or not)
 * @return true/false
 * @NOTE  You need to control the CS outsize if (is_one_take_cs) is set true
 * @NOTE  It will generate APP_QSPI_EVT_TX_CPLT event when finish transmission.
 ****************************************************************************************
 */
bool app_qspi_async_llp_draw_block(app_qspi_id_t screen_id,
                                         app_qspi_id_t storage_id,
                                         const app_qspi_screen_command_t *const p_screen_cmd,
                                         const app_qspi_screen_info_t *const p_screen_info,
                                         app_qspi_screen_block_t *p_block_info,
                                         bool is_first_call);
/**
 ****************************************************************************************
 * @brief  Special API to Blit Image from memory mapped device to RAM Buffer
 *         Must enable the two micro-defines to enable this API:
 *         QSPI_BLIT_RECT_IMAGE_SUPPORT
 *
 * @param[in]  storage_id : QSPI module ID for storage, MUST config storage qspi to mmap(xip) mode.
 * @param[in]  p_blit_config : pointer to blit config
 * @param[in]  xfer_type  : pointer to the scrolling-config
 * @return true/false
 ****************************************************************************************
 */
bool app_qspi_mmap_blit_image(app_qspi_id_t storage_id, blit_image_config_t * p_blit_config, blit_xfer_type_e xfer_type);
/** @} */

#ifdef __cplusplus
}
#endif
#endif
#endif
#endif
/** @} */
/** @} */
/** @} */
