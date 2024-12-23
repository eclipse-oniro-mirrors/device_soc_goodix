/**
 ****************************************************************************************
 *
 * @file gui_font5_7.c
 *
 * @brief Function of show 5*7 ascii
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
 *****************************************************************************************
 */

/*
 * INCLUDE FILES
 *****************************************************************************************
 */
#include "gui_font5_7.h"
#include "gui_font_macro.h"
#include "gui_color.h"
#include "gui_basic.h"

#if  FONT5x7_EN==1

/**@brief 5*7 ascii define. */
const uint8_t s_ascii_font5_7[][8] = {
/* space */  
  {
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  !  */
 ,{
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   ________,
   X_______,
   ________}


/*  "  */
 ,{
   X_X_____,
   X_X_____,
   X_X_____,
   ________,
   ________,
   ________,
   ________,
   ________}

/* #  */
 ,{
   _X_X____,
   _X_X____,
   XXXXX___,
   _X_X____,
   XXXXX___,
   _X_X____,
   _X_X____,
   ________}

/*  $  */
 ,{
   __X_____,
   _XXXX___,
   X_X_____,
   _XXX____,
   __X_X___,
   XXXX____,
   __X_____}

/*  %  */
 ,{
   XX______,
   XX__X___,
   ___X____,
   __X_____,
   _X______,
   X__XX___,
   ___XX___,
   ________}

/*  &  */
 ,{
   _XX_____,
   X__X____,
   X_X_____,
   _X______,
   X_X_X___,
   X__X____,
   _XX_X___,
   ________}

/*  '  */
 ,{
   XX______,
   _X______,
   X_______,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  (  */
 ,{
   __X_____,
   _X______,
   X_______,
   X_______,
   X_______,
   _X______,
   __X_____,
   ________}

/*  )  */
 ,{
   X_______,
   _X______,
   __X_____,
   __X_____,
   __X_____,
   _X______,
   X_______,
   ________}

/*  *  */
 ,{
   ________,
   _X_X____,
   __X_____,
   XXXXX___,
   __X_____,
   _X_X____,
   ________,
   ________}

 ,{
   ________,
   __X_____,
   __X_____,
   XXXXX___,
   __X_____,
   __X_____,
   ________,
   ________}

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   XX______,
   _X______,
   X_______}

 ,{
   ________,
   ________,
   ________,
   XXXXX___,
   ________,
   ________,
   ________,
   ________}

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   XX______,
   XX______,
   ________}

 ,{
   ________,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   X_______,
   ________,
   ________}

/* 0 */
 ,{
   _XXX____,
   X___X___,
   X__XX___,
   X_X_X___,
   XX__X___,
   X___X___,
   _XXX____,
   ________}

/* 1 */
 ,{
   __X_____,
   _XX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   _XXX____,
   ________}

/* 2 */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   __XX____,
   _X______,
   X_______,
   XXXXX___,
   ________}

/* 3 */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   __XX____,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* 4 */
 ,{
   ___X____,
   __XX____,
   _X_X____,
   X__X____,
   XXXXX___,
   ___X____,
   ___X____,
   ________}

/* 5 */
 ,{
   XXXXX___,
   X_______,
   XXXX____,
   ____X___,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* 6 */
 ,{
   __XX____,
   _X______,
   X_______,
   XXXX____,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* 7 */
 ,{
   XXXXX___,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   _X______,
   _X______,
   ________}

/* 8 */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   _XXX____,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* 9 */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   _XXXX___,
   ____X___,
   ___X____,
   _XX_____,
   ________}

/* ':' 3a */
 ,{
   ________,
   XX______,
   XX______,
   ________,
   XX______,
   XX______,
   ________,
   ________}

/* ';' 3b */
 ,{
   ________,
   ________,
   XX______,
   XX______,
   ________,
   XX______,
   _X______,
   X_______}


/* '<' 3c */
 ,{
   ___X____,
   __X_____,
   _X______,
   X_______,
   _X______,
   __X_____,
   ___X____,
   ________}

/* '=' 3d */
 ,{
   ________,
   ________,
   XXXXX___,
   ________,
   XXXXX___,
   ________,
   ________,
   ________}

/* '>' */
 ,{
   X_______,
   _X______,
   __X_____,
   ___X____,
   __X_____,
   _X______,
   X_______,
   ________}

/* '?' */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   ___X____,
   __X_____,
   ________,
   __X_____,
   ________}

/* @ */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   _XX_X___,
   X_X_X___,
   X_X_X___,
   _XXX____,
   ________}

/* A */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   XXXXX___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* B */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   ________}

/* C */
 ,{
   _XXX____,
   X___X___,
   X_______,
   X_______,
   X_______,
   X___X___,
   _XXX____,
   ________}

/* D */
 ,{
   XXX_____,
   X__X____,
   X___X___,
   X___X___,
   X___X___,
   X__X____,
   XXX_____,
   ________}

/* E */
 ,{
   XXXXX___,
   X_______,
   X_______,
   XXXX____,
   X_______,
   X_______,
   XXXXX___,
   ________}

/* F */
 ,{
   XXXXX___,
   X_______,
   X_______,
   XXXX____,
   X_______,
   X_______,
   X_______,
   ________}

/* G */
 ,{
   _XXX____,
   X___X___,
   X_______,
   X_______,
   X__XX___,
   X___X___,
   _XXXX___,
   ________}

/* H */
 ,{
   X___X___,
   X___X___,
   X___X___,
   XXXXX___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* I */
 ,{
   XXX_____,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   XXX_____,
   ________}

/* J */
 ,{
   __XXX___,
   ___X____,
   ___X____,
   ___X____,
   ___X____,
   X__X____,
   _XX_____,
   ________}

/* K */
 ,{
   X___X___,
   X__X____,
   X_X_____,
   XX______,
   X_X_____,
   X__X____,
   X___X___,
   ________}

/* L */
 ,{
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   XXXXX___,
   ________}

/* M */
 ,{
   X___X___,
   XX_XX___,
   X_X_X___,
   X_X_X___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* N */
 ,{
   X___X___,
   X___X___,
   XX__X___,
   X_X_X___,
   X__XX___,
   X___X___,
   X___X___,
   ________}

/* O */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* P */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X_______,
   X_______,
   X_______,
   ________}

/* Q */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   X___X___,
   X_X_X___,
   X__X____,
   _XX_X___,
   ________}

/* R */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X_X_____,
   X__X____,
   X___X___,
   ________}

/* S */
 ,{
   _XXX____,
   X___X___,
   X_______,
   _XXX____,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* T */
 ,{
   XXXXX___,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* U */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* V */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   ________}

/* W */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X_X_X___,
   X_X_X___,
   X_X_X___,
   _X_X____,
   ________}

/* X */
 ,{
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   _X_X____,
   X___X___,
   X___X___,
   ________}

/* Y */
 ,{
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* Z */
 ,{
   XXXXX___,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   X_______,
   XXXXX___,
   ________}

/* 5b */
 ,{
   XXX_____,
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   XXX_____,
   ________}

/* 5c */
 ,{
   ________,
   X_______,
   _X______,
   __X_____,
   ___X____,
   ____X___,
   ________,
   ________}

/* 5d */
 ,{
   XXX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   XXX_____,
   ________}

/* 5e */
 ,{
   __X_____,
   _X_X____,
   X___X___,
   ________,
   ________,
   ________,
   ________,
   ________}

/* 5f */
 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   XXXXX___}

/* 60 */
 ,{
   X_______,
   _X______,
   __X_____,
   ________,
   ________,
   ________,
   ________,
   ________}

/* a */
 ,{
   ________,
   ________,
   _XXX____,
   ____X___,
   _XXXX___,
   X___X___,
   _XXXX___,
   ________}

/* b */
 ,{
   X_______,
   X_______,
   X_XX____,
   XX__X___,
   X___X___,
   X___X___,
   XXXX____,
   ________}

/* c */
 ,{
   ________,
   ________,
   _XX_____,
   X__X____,
   X_______,
   X__X____,
   _XX_____,
   ________}

/* d */
 ,{
   ____X___,
   ____X___,
   _XX_X___,
   X__XX___,
   X___X___,
   X___X___,
   _XXXX___,
   ________}

/* e */
 ,{
   ________,
   ________,
   _XXX____,
   X___X___,
   XXXXX___,
   X_______,
   _XXX____,
   ________}

/* f */
 ,{
   __X_____,
   _X_X____,
   _X______,
   XXX_____,
   _X______,
   _X______,
   _X______,
   ________}

/* g */
 ,{
   ________,
   ________,
   _XXXX___,
   X___X___,
   X___X___,
   _XXXX___,
   ____X___,
   _XXX____}

/* h */
 ,{
   X_______,
   X_______,
   X_XX____,
   XX__X___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* i */
 ,{
   _X______,
   ________,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   ________}

/* j */
 ,{
   __X_____,
   ________,
   _XX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   XX______}

/* k */
 ,{
   X_______,
   X_______,
   X__X____,
   X_X_____,
   XX______,
   X_X_____,
   X__X____,
   ________}

/* l */
 ,{
   XX______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   XXX_____,
   ________}

/* m */
 ,{
   ________,
   ________,
   XX_X____,
   X_X_X___,
   X_X_X___,
   X___X___,
   X___X___,
   ________}

/* n */
 ,{
   ________,
   ________,
   X_XX____,
   XX_X____,
   X__X____,
   X__X____,
   X__X____,
   ________}

/* o */
 ,{
   ________,
   ________,
   _XX_____,
   X__X____,
   X__X____,
   X__X____,
   _XX_____,
   ________}

/* p */
 ,{
   ________,
   ________,
   XXX_____,
   X__X____,
   X__X____,
   XXX_____,
   X_______,
   X_______}

/* q */
 ,{
   ________,
   ________,
   _XXX____,
   X__X____,
   X__X____,
   _XXX____,
   ___X____,
   ___X____}

/* r */
 ,{
   ________,
   ________,
   _X_X____,
   _XX_____,
   _X______,
   _X______,
   _X______,
   ________}

/* s */
 ,{
   ________,
   ________,
   _XXX____,
   X_______,
   _XX_____,
   ___X____,
   XXX_____,
   ________}

/* t */
 ,{
   _X______,
   _X______,
   XXX_____,
   _X______,
   _X______,
   _X______,
   _XX_____,
   ________}

/* u */
 ,{
   ________,
   ________,
   X__X____,
   X__X____,
   X__X____,
   X__X____,
   _XXX____,
   ________}

/* v */
 ,{
   ________,
   ________,
   X___X___,
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   ________}

/* w */
 ,{
   ________,
   ________,
   X___X___,
   X___X___,
   X_X_X___,
   X_X_X___,
   _X_X____,
   ________}

/* X */
 ,{
   ________,
   ________,
   X___X___,
   _X_X____,
   __X_____,
   _X_X____,
   X___X___,
   ________}

/* y */
 ,{
   ________,
   ________,
   X__X____,
   X__X____,
   X__X____,
   _XXX____,
   ___X____,
   _XX_____}

/* z */
 ,{
   ________,
   ________,
   XXXXX___,
   ___X____,
   __X_____,
   _X______,
   XXXXX___,
   ________}

/* 0x7b */
 ,{
   __X_____,
   _X______,
   _X______,
   X_______,
   _X______,
   _X______,
   __X_____,
   ________}

/* 0x7c */
 ,{
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   ________}

/* 0x7d */
 ,{
   X_______,
   _X______,
   _X______,
   __X_____,
   _X______,
   _X______,
   X_______,
   ________}

/* 0x7e */
 ,{
   _XX_X___,
   X__X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}
   
/* 0x7f */
 ,{
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   ________}
   
};

/*
 * GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 */
uint8_t gui_put_char5_7(uint16_t x, uint16_t y, uint8_t ch)
{  
    uint8_t   i;
    if( x>(GUI_DISPLAY_X_MAX-8) )
        return(0);
    if( y>(GUI_DISPLAY_Y_MAX-8) ) 
        return(0);
    if( (ch<0x20) || (ch>0x7f) ) 
        ch = 0x20;

    ch -= 0x20; 
    for(i=0; i<8; i++)
    {  
        gui_point_color(x, y, s_ascii_font5_7[ch][i], 6);
        y++;                                                                    
    }

    return(1);
}



void  gui_put_string5_7(uint16_t x, uint16_t y, char *p_str)
{  
    while(1)
    { 
        if( (*p_str)=='\0' ) break;
        if( gui_put_char5_7(x, y, *p_str++)==0 ) break;
        x += 6;                            
    }
}

void gui_put_num5_7(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t mode)
{
    uint8_t t,temp;
    uint8_t enshow = 0;
    for(t=0; t<len; t++)
    {
        temp = (num/gui_pow(10,len-t-1))%10;
        if (enshow==0&&t<(len-1))
        {
            if (temp==0)
            {
                if(mode)
                {
                  gui_put_char5_7(x+6*t, y, '0');
                }
                continue;
            }   else enshow=1;
        }
        gui_put_char5_7(x+6*t, y, temp+'0');
    }
}

#endif