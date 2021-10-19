/**
 *****************************************************************************************
 *
 * @file ssd1316.c
 *
 * @brief LCD controller driver of ssd13xx IC.
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

/*
 * INCLUDE FILES
 *****************************************************************************************
 */
#include "ssd1316_config.h"
#include "ssd1316.h"
#include <string.h>
#include <stdbool.h>

 /*
 * GLOBAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
uint8_t s_oled_gram[OLED_PAGE_MAX][OLED_XMAX] = {0};
uint8_t s_oled_buffer[OLED_PAGE_MAX][OLED_XMAX] = {0};

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
static uint8_t (*s_oled_memory)[OLED_XMAX] = s_oled_gram;


/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
 
/**
 *****************************************************************************************
 * @brief Set oled row index
 *
 * @param[in] row  row index of oled.
 *****************************************************************************************
 */
static void oled_set_page(uint8_t row)
{
    ssd1316_write_cmd(0xb0 + row); 
}

/**
 *****************************************************************************************
 * @brief Set oled column index
 *
 * @param[in] col  column index of oled.
 *****************************************************************************************
 */
static void oled_set_column(uint8_t col)
{
    ssd1316_write_cmd(0x10 + ((col >> 4) & 0xF));           
    ssd1316_write_cmd(0x00 + (col & 0xF));   
}

/*
 * GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 */
void oled_init()   
{   
    ssd1316_init();

    ssd1316_write_cmd(0xae);  // display off.
    ssd1316_write_cmd(0x00);  // set lower column address.
    ssd1316_write_cmd(0x10);  // set higter column address.
    ssd1316_write_cmd(0x40);  // set display start line.
    ssd1316_write_cmd(0xb0);  // set page address.
    ssd1316_write_cmd(0x81);  // contract control.
    ssd1316_write_cmd(0x60);  // 128.
    ssd1316_write_cmd(0xa1);  // set segment remap.
    ssd1316_write_cmd(0xa6);  // set normal/inverse display.
    ssd1316_write_cmd(0xa8);  // set multiplex radio.
    ssd1316_write_cmd(0x1f);  // 1/32.
    ssd1316_write_cmd(0xc0);  // Com scan direction.
    ssd1316_write_cmd(0xd3);  // set display offset.
    ssd1316_write_cmd(0x00);  //
    ssd1316_write_cmd(0xd5);  // set osc division.
    ssd1316_write_cmd(0x80);
    ssd1316_write_cmd(0xd9);  // set pre-charge period.
    ssd1316_write_cmd(0x22);
    ssd1316_write_cmd(0xda);  // set COM pins.
    ssd1316_write_cmd(0x12);
    ssd1316_write_cmd(0xdb);  // set vcomh.
    ssd1316_write_cmd(0x40);
    ssd1316_write_cmd(0x8d);  // set charge pump enable.
    ssd1316_write_cmd(0x15);  //
    ssd1316_write_cmd(0xaf);  //--turn on oled panel.

    return;
}

void oled_set_memory(oled_memory_type_t type)
{
    if(type == MEM_GRAM)
    {
        s_oled_memory = s_oled_gram;
    }
    else
    {
        s_oled_memory = s_oled_buffer;
    }
    return;
}

void oled_fill(uint8_t data)   
{       
    memset(s_oled_memory, data, OLED_PAGE_MAX * OLED_XMAX);
    return;
}

void oled_refresh(void)
{
    uint8_t y = 0;
    for(y = 0; y < OLED_PAGE_MAX; y++)   
    {       
        oled_set_page(y);
        oled_set_column(0);
        ssd1316_write_buffer(&s_oled_memory[y][0], OLED_XMAX);
    }
    return;
}

void oled_draw_point(uint8_t x, uint8_t y, uint8_t color)
{
    uint8_t pos, bx, temp = 0;
    if(x > (OLED_XMAX - 1) || y > (OLED_YMAX - 1))
       return; 
    pos  = y >> 3;
    bx   = y & 0x7;
    temp = 1 << (bx);
    if(color)
        s_oled_memory[pos][x] |= temp;
    else 
        s_oled_memory[pos][x] &= ~temp;
    return;
}

uint8_t oled_read_point(uint8_t x, uint8_t y)
{
    uint8_t pos, bx;
    if(x > (OLED_XMAX - 1) || y > (OLED_YMAX - 1))
        return 0xff; 
    pos  = y >> 3;
    bx   = y & 0x7;
    return ((s_oled_memory[pos][x] >> bx) & 0x01);
}

void oled_load_16x32(uint8_t x,uint8_t y_page, const uint8_t(*code16_32)[16], uint8_t index)
{
    memcpy(&s_oled_memory[y_page][x], code16_32[index*4], 16);
    memcpy(&s_oled_memory[y_page+1][x], code16_32[index*4+1], 16);
    memcpy(&s_oled_memory[y_page+2][x], code16_32[index*4+2], 16);
    memcpy(&s_oled_memory[y_page+3][x], code16_32[index*4+3], 16);
    return;
}

void oled_set_contrast(uint8_t value)
{
    ssd1316_write_cmd(0x81);     // Set Contrast Control
    ssd1316_write_cmd(value);
    return;
}

void oled_scroll_horizontal(bool left, oled_scroll_speed_t speed)
{
    ssd1316_write_cmd((left == true)? (0x27) : (0x26));
    ssd1316_write_cmd(0x00);
    ssd1316_write_cmd(0x00);
    ssd1316_write_cmd(speed);
    ssd1316_write_cmd(0x03);
    ssd1316_write_cmd(0x00);
    ssd1316_write_cmd(0xff);
    ssd1316_write_cmd(0x2f);
    return;
}

void oled_scroll_slash(bool left, oled_scroll_speed_t speed)
{ 
    ssd1316_write_cmd((left == true)? (0x27) : (0x26));
    ssd1316_write_cmd(0x00);
    ssd1316_write_cmd(0x00);
    ssd1316_write_cmd(speed);
    ssd1316_write_cmd(0x03);
    ssd1316_write_cmd(0x01);
    ssd1316_write_cmd(0x2f);
    return;
}

void oled_stop_scroll(void)
{
    ssd1316_write_cmd(0x2e);
    return;
}

void oled_normal_display(void)
{
    ssd1316_write_cmd(0xa7);
    return;
}

void oled_inverse_display(void)
{
    ssd1316_write_cmd(0xa6);
    return;
}

void oled_start_blink(uint8_t speed)
{
    ssd1316_write_cmd(0x23);
    ssd1316_write_cmd(speed | 0x30);
    return;
}

void oled_stop_blink(void)
{
    ssd1316_write_cmd(0x23);
    ssd1316_write_cmd(0x00);
    return;
}



