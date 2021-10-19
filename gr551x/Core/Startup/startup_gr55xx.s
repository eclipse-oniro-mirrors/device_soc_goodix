/**************************************************************************//**
 * @file     startup_gr55xx.s
 * @brief    CMSIS Cortex-M ARMv7-M based Core Device Startup File for
 *           Device GR55xx
 * @version  V1.00
 * @date     12. June 2018
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2016-2018, Shenzhen Huiding Technology Co., Ltd

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
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
   ---------------------------------------------------------------------------*/

  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

.global  SystemInit
.global  main_init

/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
  ldr   sp, =_estack     /* set stack pointer */
  bl  SystemInit

  //bl __libc_init_array

/* Call the application's entry point.*/
  bl  main_init
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None     
 * @retval None       
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  
  /* External Interrupts */
  .word     WDT_IRQHandler                   
  .word     BLE_SDK_Handler                  
  .word     BLE_IRQHandler                 
  .word     DMA_IRQHandler                 
  .word     SPI_M_IRQHandler               
  .word     SPI_S_IRQHandler               
  .word     EXT0_IRQHandler                  
  .word     EXT1_IRQHandler                  
  .word     TIMER0_IRQHandler                
  .word     TIMER1_IRQHandler 
  .word     DUAL_TIMER_IRQHandler
  .word     QSPI0_IRQHandler
  .word     UART0_IRQHandler      
  .word     UART1_IRQHandler
  .word     I2C0_IRQHandler
  .word     I2C1_IRQHandler
  .word     AES_IRQHandler
  .word     HMAC_IRQHandler
  .word     EXT2_IRQHandler
  .word     RNG_IRQHandler
  .word     PMU_IRQHandler
  .word     PKC_IRQHandler
  .word     XQSPI_IRQHandler
  .word     QSPI1_IRQHandler
  .word     PWR_CMD_IRQHandler
  .word     BLESLP_IRQHandler
  .word     SLPTIMER_IRQHandler
  .word     COMP_IRQHandler
  .word     AON_WDT_IRQHandler
  .word     I2S_M_IRQHandler
  .word     I2S_S_IRQHandler
  .word     ISO7816_IRQHandler
  .word     PRESENT_IRQHandler
  .word     CALENDAR_IRQHandler

                      
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* As they are weak aliases, any function with the same name will override 
* this definition.
* 
*******************************************************************************/
   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      MemManage_Handler
   .thumb_set MemManage_Handler,Default_Handler

   .weak      BusFault_Handler
   .thumb_set BusFault_Handler,Default_Handler

   .weak      UsageFault_Handler
   .thumb_set UsageFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      DebugMon_Handler
   .thumb_set DebugMon_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler              

   .weak      WDT_IRQHandler                   
   .thumb_set WDT_IRQHandler,Default_Handler      


   .weak      BLE_SDK_Handler      
   .thumb_set BLE_SDK_Handler,Default_Handler

   .weak      BLE_IRQHandler            
   .thumb_set BLE_IRQHandler,Default_Handler

   .weak      DMA_IRQHandler                  
   .thumb_set DMA_IRQHandler,Default_Handler

   .weak      SPI_M_IRQHandler         
   .thumb_set SPI_M_IRQHandler,Default_Handler

   .weak      SPI_S_IRQHandler      
   .thumb_set SPI_S_IRQHandler,Default_Handler

   .weak      EXT0_IRQHandler         
   .thumb_set EXT0_IRQHandler,Default_Handler

   .weak      EXT1_IRQHandler         
   .thumb_set EXT1_IRQHandler,Default_Handler

   .weak      TIMER0_IRQHandler         
   .thumb_set TIMER0_IRQHandler,Default_Handler 

   .weak      TIMER1_IRQHandler         
   .thumb_set TIMER1_IRQHandler,Default_Handler

   .weak      DUAL_TIMER_IRQHandler         
   .thumb_set DUAL_TIMER_IRQHandler,Default_Handler

   .weak      QSPI0_IRQHandler               
   .thumb_set QSPI0_IRQHandler,Default_Handler

   .weak      UART0_IRQHandler               
   .thumb_set UART0_IRQHandler,Default_Handler

   .weak      UART1_IRQHandler               
   .thumb_set UART1_IRQHandler,Default_Handler

   .weak      I2C0_IRQHandler               
   .thumb_set I2C0_IRQHandler,Default_Handler 

   .weak      I2C1_IRQHandler              
   .thumb_set I2C1_IRQHandler,Default_Handler

   .weak      AES_IRQHandler               
   .thumb_set AES_IRQHandler,Default_Handler

   .weak      HMAC_IRQHandler               
   .thumb_set HMAC_IRQHandler,Default_Handler

   .weak      EXT2_IRQHandler      
   .thumb_set EXT2_IRQHandler,Default_Handler

   .weak      RNG_IRQHandler   
   .thumb_set RNG_IRQHandler,Default_Handler

   .weak      PMU_IRQHandler                  
   .thumb_set PMU_IRQHandler,Default_Handler

   .weak      PKC_IRQHandler                  
   .thumb_set PKC_IRQHandler,Default_Handler

   .weak      XQSPI_IRQHandler                  
   .thumb_set XQSPI_IRQHandler,Default_Handler

   .weak      QSPI1_IRQHandler   
   .thumb_set QSPI1_IRQHandler,Default_Handler

   .weak      PWR_CMD_IRQHandler            
   .thumb_set PWR_CMD_IRQHandler,Default_Handler

   .weak      BLESLP_IRQHandler            
   .thumb_set BLESLP_IRQHandler,Default_Handler

   .weak      SLPTIMER_IRQHandler      
   .thumb_set SLPTIMER_IRQHandler,Default_Handler

   .weak      COMP_IRQHandler   
   .thumb_set COMP_IRQHandler,Default_Handler

   .weak      AON_WDT_IRQHandler            
   .thumb_set AON_WDT_IRQHandler,Default_Handler

   .weak      I2S_M_IRQHandler            
   .thumb_set I2S_M_IRQHandler,Default_Handler
   
   .weak      I2S_S_IRQHandler            
   .thumb_set I2S_S_IRQHandler,Default_Handler

   .weak      ISO7816_IRQHandler   
   .thumb_set ISO7816_IRQHandler,Default_Handler

   .weak      PRESENT_IRQHandler   
   .thumb_set PRESENT_IRQHandler,Default_Handler

   .weak      CALENDAR_IRQHandler   
   .thumb_set CALENDAR_IRQHandler,Default_Handler


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
  

