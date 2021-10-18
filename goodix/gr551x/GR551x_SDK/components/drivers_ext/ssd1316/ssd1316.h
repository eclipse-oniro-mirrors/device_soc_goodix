/**
 *****************************************************************************************
 *
 * @file ssd1316.h
 *
 * @brief LCD controller driver of ssd13xx IC API.
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
 
#ifndef _SSD1316_H_
#define _SSD1316_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup SSD1316_MAROC Defines
 * @{
 */
#define  OLED_XMAX       128           /**< OLED Max Pixel of X coordinate. */
#define  OLED_YMAX       32            /**< OLED Max Pixel of Y coordinate. */
#define  OLED_PAGE_MAX   4             /**< OLED Max Page of Y coordinate.  */

/**
 * @defgroup SSD1316_ENUM Enumerations
 * @{
 */
 /**@brief OLED Memory type. */
typedef enum
{
    MEM_GRAM,                         /**< GRAM Memory. */
    MEM_BUF,                          /**< Buffer Memory. */
} oled_memory_type_t;
/** @} */

 /**@brief OLED Scroll speed. */
typedef enum 
{
  SCROLL_6FRAMES     = 0x00,
  SCROLL_32FRAMES    = 0x01,
  SCROLL_64FRAMES    = 0x02,
  SCROLL_128FRAMES   = 0x03,
  SCROLL_3FRAMES     = 0x04,
  SCROLL_4FRAMES     = 0x05,
  SCROLL_5FRAMES     = 0x06,
  SCROLL_2FRAMES     = 0x07,
} oled_scroll_speed_t;
/** @} */

/**
 * @defgroup SSD1316_EXTRERN Extern_Variable 
 * @{
 */
extern uint8_t s_oled_gram[OLED_PAGE_MAX][OLED_XMAX];   /**< Gram memory define. */
extern uint8_t s_oled_buffer[OLED_PAGE_MAX][OLED_XMAX]; /**< Buffer memory define. */
/** @} */

/**
 * @defgroup SSD1316_FUNCTION Functions
 * @{
 */

/**
 *****************************************************************************************
 * @brief Initialize oled.
 *****************************************************************************************
 */
void oled_init(void);

/**
 *****************************************************************************************
 * @brief Set the memory type of Oled.
 *
 * @param[in] type:  Memory type.
 *****************************************************************************************
 */
void oled_set_memory(oled_memory_type_t type);

/**
 *****************************************************************************************
 * @brief Fill Data to Oled memory.
 *
 * @param[in] data:  Fill data.
 *****************************************************************************************
 */
void oled_fill(uint8_t data);

/**
 *****************************************************************************************
 * @brief Refresh the memory data to oled.
 *****************************************************************************************
 */
void oled_refresh(void);

/**
 *****************************************************************************************
 * @brief Draw a point to oled memory.
 *
 * @param[in] x: X coordinate.
 * @param[in] y: Y coordinate.
 * @param[in] color: The color of the point.
 *****************************************************************************************
 */
void oled_draw_point(uint8_t x, uint8_t y, uint8_t color);

/**
 *****************************************************************************************
 * @brief Read a point from oled memory.
 *
 * @param[in] x: X coordinate.
 * @param[in] y: Y coordinate.
 *
 * @return The color of the read point.(Return 0xff:error)
 *****************************************************************************************
 */
uint8_t oled_read_point(uint8_t x, uint8_t y);

/**
 *****************************************************************************************
 * @brief Load modulus data of 16x32 to oled memory
 * @note  Modulus way: Column line, Reverse, Low in the first, Each Line outputs 16 bytes
 *
 * @param[in] x:      X coordinate.
 * @param[in] y_page: Y Page.
 * @param[in] code16_32: Point of the modulus data.
 * @param[in] index: Index of the modulus array.
 *****************************************************************************************
 */
void oled_load_16x32(uint8_t x,uint8_t y_page, const uint8_t(*code16_32)[16], uint8_t index);

/**
 *****************************************************************************************
 * @brief Set the contrast of the display. with a valid range from 0x01 to 0xFF.
 *
 * @param[in] value:      Contrast step value.
 *****************************************************************************************
 */
void oled_set_contrast(uint8_t value);

/**
 *****************************************************************************************
 * @brief Continuous horizontal scroll setup.
 *
 * @param[in] left:       Scroll direction.
 * @param[in] speed:      Scroll speed.
 *****************************************************************************************
 */
void oled_scroll_horizontal(bool left, oled_scroll_speed_t speed);

/**
 *****************************************************************************************
 * @brief Continuous vertical and horizontal scroll setup.
 *
 * @param[in] left:       Scroll direction.
 * @param[in] speed:      Scroll speed.
 *****************************************************************************************
 */
void oled_scroll_slash(bool left, oled_scroll_speed_t speed);

/**
 *****************************************************************************************
 * @brief Stop scrolling.
 *****************************************************************************************
 */
void oled_stop_scroll(void);

/**
 *****************************************************************************************
 * @brief Normal display.
 * @note  0 in RAM: OFF in display panel.
 *        1 in RAM: ON in display panel.
 *****************************************************************************************
 */
void oled_normal_display(void);

/**
 *****************************************************************************************
 * @brief Inverse display.
 * @note  0 in RAM: OFF in display panel.
 *        1 in RAM: ON in display panel.
 *****************************************************************************************
 */
void oled_inverse_display(void);

/**
 *****************************************************************************************
 * @brief Enable Blinking mode.
 * @note  Once Blinking Mode is enabled, contrast decrease gradually to all pixels OFF and
 *        than contrast increase gradually to normal display. this process loop continuously
 *        until the Blinking mode is disabled.
 * @param[in] speed:      Time interval for each fade stup(a valid range from 0x01 to 0xF).
 *                        0000b : 8 Frames
 *                        0001b : 16 Frames
 *                        0010b : 24 Frames
 *                        ......
 *                        1111b : 128 Frames
 *****************************************************************************************
 */
void oled_start_blink(uint8_t speed);

/**
 *****************************************************************************************
 * @brief Disable Blinking mode.
 *****************************************************************************************
 */
void oled_stop_blink(void);

#endif
