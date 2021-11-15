/**************************************************************************//**
 * @file     gr551x.ld
 * @brief    Linker script for GR551X Device
 * @version  V1.00
 * @date     10. September 2021
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

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);	/* end of "RAM" Ram type memory */

_Min_Heap_Size = 0x800;	  /* required amount of heap  */
_Min_Stack_Size = 0x2000;	/* required amount of stack */

/* Memories definition */
MEMORY
{
  FPB_RAM (xrw)   : ORIGIN = 0x30004000,   LENGTH = 0x20
  RAM     (xrw)   : ORIGIN = 0x00804400,   LENGTH = 239K
  FLASH   (rx)    : ORIGIN = 0x01002000,   LENGTH = 972K
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

   /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);

    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

	   __zinitcall_bsp_start = .;
	  KEEP (*(.zinitcall.bsp0.init))
	  KEEP (*(.zinitcall.bsp1.init))
	  KEEP (*(.zinitcall.bsp2.init))
	  KEEP (*(.zinitcall.bsp3.init))
	  KEEP (*(.zinitcall.bsp4.init))
	  __zinitcall_bsp_end = .;
	  __zinitcall_device_start = .;
	  KEEP (*(.zinitcall.device0.init))
	  KEEP (*(.zinitcall.device1.init))
	  KEEP (*(.zinitcall.device2.init))
	  KEEP (*(.zinitcall.device3.init))
	  KEEP (*(.zinitcall.device4.init))
	  __zinitcall_device_end = .;
	  __zinitcall_core_start = .;
	  KEEP (*(.zinitcall.core0.init))
	  KEEP (*(.zinitcall.core1.init))
	  KEEP (*(.zinitcall.core2.init))
	  KEEP (*(.zinitcall.core3.init))
	  KEEP (*(.zinitcall.core4.init))
	  __zinitcall_core_end = .;
	  __zinitcall_sys_service_start = .;
	  KEEP (*(.zinitcall.sys.service0.init))
	  KEEP (*(.zinitcall.sys.service1.init))
	  KEEP (*(.zinitcall.sys.service2.init))
	  KEEP (*(.zinitcall.sys.service3.init))
	  KEEP (*(.zinitcall.sys.service4.init))
	  __zinitcall_sys_service_end = .;
	  __zinitcall_sys_feature_start = .;
	  KEEP (*(.zinitcall.sys.feature0.init))
	  KEEP (*(.zinitcall.sys.feature1.init))
	  KEEP (*(.zinitcall.sys.feature2.init))
	  KEEP (*(.zinitcall.sys.feature3.init))
	  KEEP (*(.zinitcall.sys.feature4.init))
	  __zinitcall_sys_feature_end = .;
	  __zinitcall_run_start = .;
	  KEEP (*(.zinitcall.run0.init))
	  KEEP (*(.zinitcall.run1.init))
	  KEEP (*(.zinitcall.run2.init))
	  KEEP (*(.zinitcall.run3.init))
	  KEEP (*(.zinitcall.run4.init))
	  __zinitcall_run_end = .;
	  __zinitcall_app_service_start = .;
	  KEEP (*(.zinitcall.app.service0.init))
	  KEEP (*(.zinitcall.app.service1.init))
	  KEEP (*(.zinitcall.app.service2.init))
	  KEEP (*(.zinitcall.app.service3.init))
	  KEEP (*(.zinitcall.app.service4.init))
	  __zinitcall_app_service_end = .;
	  __zinitcall_app_feature_start = .;
	  KEEP (*(.zinitcall.app.feature0.init))
	  KEEP (*(.zinitcall.app.feature1.init))
	  KEEP (*(.zinitcall.app.feature2.init))
	  KEEP (*(.zinitcall.app.feature3.init))
	  KEEP (*(.zinitcall.app.feature4.init))
	  __zinitcall_app_feature_end = .;
	  __zinitcall_test_start = .;
	  KEEP (*(.zinitcall.test0.init))
	  KEEP (*(.zinitcall.test1.init))
	  KEEP (*(.zinitcall.test2.init))
	  KEEP (*(.zinitcall.test3.init))
	  KEEP (*(.zinitcall.test4.init))
	  __zinitcall_test_end = .;
	  __zinitcall_exit_start = .;
	  KEEP (*(.zinitcall.exit0.init))
	  KEEP (*(.zinitcall.exit1.init))
	  KEEP (*(.zinitcall.exit2.init))
	  KEEP (*(.zinitcall.exit3.init))
	  KEEP (*(.zinitcall.exit4.init))
	  __zinitcall_exit_end = .;

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH

  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH


  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);
  __etext = .;

  /* Initialized data sections into "RAM" Ram type memory */
  .data :
  {
    . = ALIGN(4);
    __data_start__ = . ;    /* create a global symbol at data start */
    KEEP (*(.vector))  /* make the vector at the data begining, and it will meet the needs of VTOR  */
    . = ALIGN(4);
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */
    *(RAM_CODE)        /* .RamFunc sections */
    *(.ramfunc)        /* .RamFunc sections */
    *(TINY_RAM_SPACE) 
    . = ALIGN(4);
    __data_end__ = . ;/* define a global symbol at data end */
  } >RAM AT> FLASH

  /* Uninitialized data section into "RAM" Ram type memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */ 
    __bss_start__ = .;  /* define a global symbol at bss start */
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    __bss_end__ = .;  /* define a global symbol at bss end */
  } >RAM

  /* User_heap_stack section, used to check that there is enough "RAM" Ram  type memory left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM
  
   . = ALIGN(16);
  __los_heap_addr_start__ = .;
  __los_heap_addr_end__ = ORIGIN(RAM) + LENGTH(RAM) - _Min_Stack_Size - _Min_Heap_Size - 1;

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
 
  .fpb :
  {
    . = ALIGN(0x100);
    *(FPB)            
  } >FPB_RAM AT> FLASH

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
