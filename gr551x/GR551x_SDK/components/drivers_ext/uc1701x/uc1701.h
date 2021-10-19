/**
 *****************************************************************************************
 *
 * @file uc1701.h
 *
 * @brief LCD controller driver of uc170x IC API.
 *
 *****************************************************************************************
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
 *****************************************************************************************
 */
 
#ifndef _UC1701_H
#define _UC1701_H

#include <stdint.h>

/**
 * @defgroup UC1701_MAROC Defines
 * @{
 */
#define  LCM_XMAX        102           /**< LCM Max Pixel of X coordinate. */
#define  LCM_YMAX        64            /**< LCM Max Pixel of Y coordinate. */
#define  LCM_PAGE_MAX    8             /**< LCM Max Page of Y coordinate. */

/**
 * @defgroup UC1701_ENUM Enumerations
 * @{
 */
 /**@brief LCM Memory type. */
typedef enum
{
    MEM_GRAM,                         /**< GRAM Memory. */
    MEM_BUF,                          /**< Buffer Memory. */
} lcm_memory_type_t;
/** @} */

/**
 * @defgroup UC1701_EXTRERN Extern_Variable 
 * @{
 */
extern uint8_t s_lcm_gram[LCM_PAGE_MAX][LCM_XMAX];   /**< Gram memory define. */
extern uint8_t s_lcm_buffer[LCM_PAGE_MAX][LCM_XMAX]; /**< Buffer memory define. */
/** @} */

/**
 * @defgroup UC1701_FUNCTION Functions
 * @{
 */

/**
 *****************************************************************************************
 * @brief Initialize lcm.
 *****************************************************************************************
 */
void lcm_init(void);

/**
 *****************************************************************************************
 * @brief Resume lcm.
 *****************************************************************************************
 */
void lcm_resume(void);

/**
 *****************************************************************************************
 * @brief Set the memory type of lcm.
 *
 * @param[in] type:  Memory type.
 *****************************************************************************************
 */
void lcm_set_memory(lcm_memory_type_t type);

/**
 *****************************************************************************************
 * @brief Fill Data to Lcm memory.
 *
 * @param[in] data:  Fill data.
 *****************************************************************************************
 */
void lcm_fill(uint8_t data);

/**
 *****************************************************************************************
 * @brief Refresh the memory data to lcm.
 *****************************************************************************************
 */
void lcm_refresh(void);

/**
 *****************************************************************************************
 * @brief Draw a point to lcm memory.
 *
 * @param[in] x: X coordinate.
 * @param[in] y: Y coordinate.
 * @param[in] color: The color of the point.
 *****************************************************************************************
 */
void lcm_draw_point(uint8_t x, uint8_t y, uint8_t color);

/**
 *****************************************************************************************
 * @brief Read a point from lcm memory.
 *
 * @param[in] x: X coordinate.
 * @param[in] y: Y coordinate.
 *
 * @return The color of the read point.(Return 0xff:error)
 *****************************************************************************************
 */
uint8_t lcm_read_point(uint8_t x, uint8_t y);

/**
 *****************************************************************************************
 * @brief Load modulus data of 16x32 to lcm memory
 * @note  Modulus way: Column line, Reverse, Low in the first, Each Line outputs 16 bytes
 *
 * @param[in] x:      X coordinate.
 * @param[in] y_page: Y Page.
 * @param[in] code16_32: Point of the modulus data.
 * @param[in] index: Index of the modulus array.
 *****************************************************************************************
 */
void lcm_load_16x32(uint8_t x,uint8_t y_page, const uint8_t(*code16_32)[16], uint8_t index);

/**
 *****************************************************************************************
 * @brief Used for wake-up devices after deep sleep.
 *
 * @return void
 *****************************************************************************************
 */
void lcm_resume(void);
#endif
