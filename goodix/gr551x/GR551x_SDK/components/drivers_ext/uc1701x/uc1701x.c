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
#include "lcm.h"
#include <string.h>



 /*
 * GLOBAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
//uint8_t m_lcm_gram[LCM_PAGE_MAX][LCM_XMAX];
//uint8_t m_lcm_buffer[LCM_PAGE_MAX][LCM_XMAX];



 /*
 * GLOBAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
static int  uc1701x_lcm_init(void);
static void uc1701x_lcm_resume(void);
static void uc1701x_lcm_suspend(void);
static void uc1701x_lcm_draw_point(uint16_t x, uint16_t y, uint16_t color);
static uint16_t uc1701x_lcm_read_point(uint16_t x, uint16_t y);
static void uc1701x_lcm_backlight(int mode);
static void uc1701x_lcm_refresh(void);
static void uc1701x_lcm_fill(uint16_t data);
static void uc1701x_lcm_render(uint8_t *p_map);
static void uc1701x_lcm_set_buffer(lcm_memory_type_t mode);

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */          
#define UC1701X_LCM_HEIGHT 64    /**< LCM Max Pixel of Y coordinate. */
#define UC1701X_LCM_WIDTH  102   /**< LCM Max Pixel of X coordinate. */
#define UC1701X_LCM_PAGE_MAX 8   /**< LCM Max Page of Y coordinate. */
#define SPI_TRANS_DMA_BLOCK_SIZE  511

static uint8_t s_framebuffer_map[UC1701X_LCM_PAGE_MAX][UC1701X_LCM_WIDTH];
static uint8_t s_framebuffer_draw[UC1701X_LCM_PAGE_MAX][UC1701X_LCM_WIDTH];
lcm_def_t uc1701x_lcm_opt = 
{
     {
        .lcm_height = UC1701X_LCM_HEIGHT,
        .lcm_width = UC1701X_LCM_WIDTH,
        .lcm_color_depth = 1,
     },
 
    .lcm_init = uc1701x_lcm_init,
    .lcm_suspend = uc1701x_lcm_suspend,
    .lcm_resmue = uc1701x_lcm_resume, 
    .lcm_draw_point = uc1701x_lcm_draw_point,
    .lcm_read_point = uc1701x_lcm_read_point,
    .lcm_fill_color = uc1701x_lcm_fill,
    .lcm_backlight = uc1701x_lcm_backlight,
    .lcm_refresh = uc1701x_lcm_refresh,
    .lcm_render = uc1701x_lcm_render,
    .lcm_set_buffer = uc1701x_lcm_set_buffer,
    
    .p_freambuffer_draw = (void *)s_framebuffer_draw,
    .p_freambuffer_map = (void *)s_framebuffer_map,
    .p_current_framebuffer = (void *)s_framebuffer_draw,
};




/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
//static uint8_t (*m_lcm_memory)[UC1701X_LCM_WIDTH] = m_framebuffer_draw;


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
static int uc1701x_lcm_init(void)
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
    return 0;
}

static void uc1701x_lcm_resume(void)
{
    uc1701_init();
}

static void uc1701x_lcm_suspend(void)
{
    //uc1701_init();
}


static void uc1701x_lcm_set_buffer(lcm_memory_type_t type)
{
    if(type == MEM_GRAM)
    {
        uc1701x_lcm_opt.p_current_framebuffer = s_framebuffer_draw;
    }
    else
    {
        uc1701x_lcm_opt.p_current_framebuffer = s_framebuffer_map;
    }
}

static void uc1701x_lcm_fill(uint16_t data)   
{       
    memset(uc1701x_lcm_opt.p_current_framebuffer, (uint8_t)data, LCM_PAGE_MAX * LCM_XMAX); 
}

static void uc1701x_lcm_refresh(void)
{
    uint8_t (*s_lcm_memory)[UC1701X_LCM_WIDTH] = uc1701x_lcm_opt.p_current_framebuffer;
    uint8_t y = 0;
    for(y = 0; y < UC1701X_LCM_PAGE_MAX; y++)   
    {       
        lcm_set_page(y);
        lcm_set_column(0);
        uc1701_write_buffer(&s_lcm_memory[y][0], LCM_XMAX);
    }
}

static void uc1701x_lcm_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t (*s_lcm_memory)[UC1701X_LCM_WIDTH] = uc1701x_lcm_opt.p_current_framebuffer;
    uint8_t pos, bx, temp = 0;
    if(x > (UC1701X_LCM_WIDTH-1) || y > (UC1701X_LCM_HEIGHT-1))
       return; 
    pos  = y >> 3;
    bx   = y & 0x7;
    temp = 1 << (bx);
    if(color)
        s_lcm_memory[pos][x] |= temp;
    else 
        s_lcm_memory[pos][x] &= ~temp;      
}

static uint16_t uc1701x_lcm_read_point(uint16_t x, uint16_t y)
{
    uint8_t (*s_lcm_memory)[UC1701X_LCM_WIDTH] = uc1701x_lcm_opt.p_current_framebuffer;
    uint8_t pos, bx;
    if(x > (UC1701X_LCM_WIDTH-1) || y > (UC1701X_LCM_HEIGHT-1))
        return 0xff; 
    pos = y >> 3;
    bx  = y & 0x7;
    return ((s_lcm_memory[pos][x] >> bx) & 0x01);
}



static void uc1701x_lcm_backlight(int mode)
{
}

static void uc1701x_lcm_render(uint8_t *p_map)
{
}
