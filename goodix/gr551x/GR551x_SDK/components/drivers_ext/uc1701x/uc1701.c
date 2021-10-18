/**
 *****************************************************************************************
 *
 * @file uc1701.c
 *
 * @brief LCD controller driver of uc170x IC.
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
#include "uc1701_config.h"
#include "uc1701.h"
#include <string.h>

 /*
 * GLOBAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
uint8_t s_lcm_gram[LCM_PAGE_MAX][LCM_XMAX];
uint8_t s_lcm_buffer[LCM_PAGE_MAX][LCM_XMAX];

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
static uint8_t (*s_lcm_memory)[LCM_XMAX] = s_lcm_gram;


/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
 
/**
 *****************************************************************************************
 * @brief Set lcm row index
 *
 * @param[in] row  row index of lcm.
 *****************************************************************************************
 */
static void lcm_set_page(uint8_t row)
{
    uc1701_write_cmd(0xb0 + row); 
}

/**
 *****************************************************************************************
 * @brief Set lcm column index
 *
 * @param[in] col  column index of lcm.
 *****************************************************************************************
 */
static void lcm_set_column(uint8_t col)
{
    uc1701_write_cmd(0x10 + ((col >> 4) & 0xF));           
    uc1701_write_cmd(0x00 + (col & 0xF));   
}

/*
 * GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 */
void lcm_init()   
{   
    uc1701_init();
    
    uc1701_write_cmd(0xe2);//system reset   
    uc1701_delay(200);   

    uc1701_write_cmd(0x24);//SET VLCD RESISTOR RATIO   
    uc1701_write_cmd(0xa2);//BR=1/9   
    uc1701_write_cmd(0xa1);//set seg direction   0xa1
    uc1701_write_cmd(0xc0);//set com direction   
    uc1701_write_cmd(0x2f);//set power control   
    uc1701_write_cmd(0x40);//set scroll line   //display from line 0
    uc1701_write_cmd(0x81);//SET ELECTRONIC VOLUME   
    uc1701_write_cmd(50);

    uc1701_write_cmd(0xaf);//set display enable
}   


void lcm_resume(void)
{
    uc1701_init();
}

void lcm_set_memory(lcm_memory_type_t type)
{
    if(type == MEM_GRAM)
    {
        s_lcm_memory = s_lcm_gram;
    }
    else
    {
        s_lcm_memory = s_lcm_buffer;
    }
}

void lcm_fill(uint8_t data)   
{       
    memset(s_lcm_memory, data, LCM_PAGE_MAX * LCM_XMAX); 
}

void lcm_refresh(void)
{
    uint8_t y = 0;
    for(y = 0; y < LCM_PAGE_MAX; y++)   
    {       
        lcm_set_page(y);
        lcm_set_column(0);
        uc1701_write_buffer(&s_lcm_memory[y][0], LCM_XMAX);
    }
}

void lcm_draw_point(uint8_t x, uint8_t y, uint8_t color)
{
    uint8_t pos, bx, temp = 0;
    if(x > (LCM_XMAX-1) || y > (LCM_YMAX-1))
       return; 
    pos  = y >> 3;
    bx   = y & 0x7;
    temp = 1 << (bx);
    if(color)
        s_lcm_memory[pos][x] |= temp;
    else 
        s_lcm_memory[pos][x] &= ~temp;      
}

uint8_t lcm_read_point(uint8_t x, uint8_t y)
{
    uint8_t pos, bx;
    if(x > (LCM_XMAX-1) || y > (LCM_YMAX-1))
        return 0xff; 
    pos = y >> 3;
    bx  = y & 0x7;
    return ((s_lcm_memory[pos][x] >> bx) & 0x01);
}

void lcm_load_16x32(uint8_t x,uint8_t y_page, const uint8_t(*code16_32)[16],uint8_t index)
{
    memcpy(&s_lcm_memory[y_page][x], code16_32[index*4], 16);
    memcpy(&s_lcm_memory[y_page+1][x], code16_32[index*4+1], 16);
    memcpy(&s_lcm_memory[y_page+2][x], code16_32[index*4+2], 16);
    memcpy(&s_lcm_memory[y_page+3][x], code16_32[index*4+3], 16);
}


