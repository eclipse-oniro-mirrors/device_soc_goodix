/**
 ****************************************************************************************
 *
 * @file ssd1316_config.c
 *
 * @brief ssd1316 config Implementation.
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
#include "ssd1316_config.h"
#include "gr55xx_delay.h"


/*-----------------------------------DRIVER_TYPE_SW_IO------------------------------------*/
#ifdef DISPLAY_DRIVER_TYPE_SW_IO
#include "ssd1316_i2c_soft.h"


void ssd1316_write_cmd(uint8_t cmd)
{
    SSD_UserI2cWriteByteWithStart(SSD1316_I2C_ADDRESS >> 1);
    SSD_UserI2cWriteByte(0x00);
    SSD_UserI2cWriteByteWithStop(cmd);
    return;
}

void ssd1316_write_data(uint8_t data)
{
    SSD_UserI2cWriteByteWithStart(SSD1316_I2C_ADDRESS >> 1);
    SSD_UserI2cWriteByte(0x40);
    SSD_UserI2cWriteByteWithStop(data);
}

void ssd1316_write_buffer(uint8_t *p_data, uint16_t length)
{
    uint16_t count;
    if (p_data == NULL || length <= 0)
        return ;

    SSD_UserI2cWriteByteWithStart(SSD1316_I2C_ADDRESS >> 1);
    SSD_UserI2cWriteByte(0x40);
    for(count = 0; count < length - 1; count++)
    {
        SSD_UserI2cWriteByte(*p_data++);
    }
    SSD_UserI2cWriteByteWithStop(*p_data);
    return;
}

void ssd1316_init()
{
    SSD_UserI2cConfig(USER_I2C_BAUDRATE_100K);
    return;
}

#endif
/*-----------------------------------DRIVER_TYPE_SW_IO------------------------------------*/


/*-----------------------------------DRIVER_TYPE_HW_I2C------------------------------------*/
#ifdef DISPLAY_DRIVER_TYPE_HW_I2C
static i2c_handle_t I2CHandle;
static dma_handle_t TXDMAHandle;
static volatile uint8_t  master_tx_done = 0;

void ssd1316_write_cmd(uint8_t cmd)
{
    uint8_t buffer[2] = {0x00, 0x00};
    
    buffer[1] = cmd;
    hal_i2c_master_transmit(&I2CHandle, SSD1316_I2C_ADDRESS, buffer, sizeof(buffer), 5000);
    return;
}

void ssd1316_write_data(uint8_t data)
{
    uint8_t buffer[2] = {0x40, 0x00};
    
    buffer[1] = data;
    hal_i2c_master_transmit(&I2CHandle, SSD1316_I2C_ADDRESS, buffer, sizeof(buffer), 5000);
    return;
}

void ssd1316_write_buffer(uint8_t *p_data, uint16_t length)
{
    if (p_data == NULL || length <= 0)
        return ;

    master_tx_done = 0;
    hal_i2c_transmit_dma(&SPIMHandle, SSD1316_I2C_ADDRESS, p_data, length);
    while(master_tx_done == 0);
    return;
}

void hal_i2c_msp_init(i2c_handle_t *hi2c)
{
    gpio_init_t GPIO_InitStruct;

    GPIO_InitStructure.mode = DISPLAY_I2C_GPIO_MUX;
    GPIO_InitStructure.pin = DISPLAY_I2C_CLK_PIN | DISPLAY_I2C_MOSI_PIN;
    GPIO_InitStructure.mux = DISPLAY_I2C_GPIO_MUX;
    hal_gpio_init(DISPLAY_I2C_GPIO_PORT, &GPIO_InitStructure);

    /* Configure the DMA handler for Transmission process */
    TXDMAHandle.channel                  = DMA_Channel0;
    TXDMAHandle.init.src_request         = DMA_REQUEST_MEM;
    TXDMAHandle.init.dst_request         = (hi2c->p_instance == I2C0) ? DMA_REQUEST_I2C0_TX : DMA_REQUEST_I2C1_TX;
    TXDMAHandle.init.direction           = DMA_MEMORY_TO_PERIPH;
    TXDMAHandle.init.src_increment       = DMA_SRC_INCREMENT;
    TXDMAHandle.init.dst_increment       = DMA_DST_NO_CHANGE;
    TXDMAHandle.init.src_data_alignment  = DMA_SDATAALIGN_BYTE;
    TXDMAHandle.init.dst_data_alignment  = DMA_DDATAALIGN_BYTE;
    TXDMAHandle.init.mode                = DMA_NORMAL;
    TXDMAHandle.init.priority            = DMA_PRIORITY_LOW;

    hal_dma_deinit(&TXDMAHandle);
    hal_dma_init(&TXDMAHandle);

    /* Associate the initialized DMA handle to the I2C handle */
    __HAL_LINKDMA(hi2c, p_dmatx, TXDMAHandle);
    
    NVIC_ClearPendingIRQ(I2C0_IRQn);
    NVIC_EnableIRQ(I2C0_IRQn);

    NVIC_ClearPendingIRQ(DMA_IRQn);
    hal_nvic_enable_irq(DMA_IRQn);
    return;
}

void ssd1316_init(void)
{
    I2CHandle.p_instance             = I2C0;
    I2CHandle.init.speed             = I2C_SPEED_400K;
    I2CHandle.init.own_address       = 0x55;
    I2CHandle.init.addressing_mode   = I2C_ADDRESSINGMODE_7BIT;
    I2CHandle.init.general_call_mode = I2C_GENERALCALL_DISABLE;

    hal_i2c_deinit(&I2CHandle);
    hal_i2c_init(&I2CHandle);
    return;
}

void I2C0_IRQHandler(void)
{
    hal_i2c_irq_handler(&I2CHandle);
}

void I2C1_IRQHandler(void)
{
    hal_i2c_irq_handler(&I2CHandle);
}

void DMA_IRQHandler(void)
{
    hal_dma_irq_handler(i2c_handle.p_dmatx);
}

void hal_i2c_master_tx_cplt_callback(i2c_handle_t *hi2c)
{
    master_tx_done = 1;
}

void hal_i2c_mem_tx_cplt_callback(i2c_handle_t *hi2c)
{
    master_tx_done = 1;
}

void hal_i2c_abort_cplt_callback(i2c_handle_t *hi2c)
{
    printf("This is Abort complete Callback.\r\n");
}

#endif
/*-----------------------------------DRIVER_TYPE_HW_I2C------------------------------------*/

void ssd1316_delay(uint16_t time)
{
    delay_ms(time);
}
