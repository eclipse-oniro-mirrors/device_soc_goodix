/**
 ****************************************************************************************
 *
 * @file uc1701_config.c
 *
 * @brief uc1701 config Implementation.
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
#include "uc1701_config.h"
#include "gr55xx_delay.h"


/*-----------------------------------DRIVER_TYPE_SW_IO------------------------------------*/
#ifdef DISPLAY_DRIVER_TYPE_SW_IO

static inline void uc1701_send_byte(uint8_t data) 
{   
    uint8_t i;
    for(i=0; i<8; i++)   
    {   
        SCK_LOW;
        if (data & 0x80)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        data <<= 0x01;
        SCK_HIGH;
    }
}   

void uc1701_write_cmd(uint8_t cmd)
{
    SEND_CMD;
    CS_LOW;
    uc1701_send_byte(cmd);
    CS_HIGH;
}

void uc1701_write_data(uint8_t data)
{
    SEND_DATA;
    CS_LOW;
    uc1701_send_byte(data);
    CS_HIGH;
}

void uc1701_write_buffer(uint8_t *p_data, uint16_t length)
{
    uint16_t i;
    if (p_data == NULL || length <= 0)
        return ;

    SEND_DATA;
    CS_LOW;
    for (i=0; i<length; i++)
    {
       uc1701_send_byte(*p_data++); 
    }
    CS_HIGH;
}

void uc1701_init()
{
    gpio_init_t GPIO_InitStruct = GPIO_DEFAULT_CONFIG;

    GPIO_InitStruct.mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.pin  = GPIO_PIN_5;            //CMD_DATA_SEL
    hal_gpio_init(GPIO0, &GPIO_InitStruct);

    GPIO_InitStruct.pin  = GPIO_PIN_6;            //SCK
    hal_gpio_init(GPIO0, &GPIO_InitStruct);
    GPIO_InitStruct.pin  = GPIO_PIN_7;            //SDA
    hal_gpio_init(GPIO0, &GPIO_InitStruct);

    GPIO_InitStruct.pin  = GPIO_PIN_1;            //CS_SEL
    hal_gpio_init(GPIO1, &GPIO_InitStruct);
}
#endif
/*-----------------------------------DRIVER_TYPE_SW_IO------------------------------------*/


/*-----------------------------------DRIVER_TYPE_HW_SPI------------------------------------*/
#ifdef DISPLAY_DRIVER_TYPE_HW_SPI

static spi_handle_t SPIMHandle;
static dma_handle_t TXDMAHandle;
static volatile uint8_t  master_tx_done = 0;
static volatile uint8_t  master_rx_done = 0;

static inline void uc1701_send_byte(uint8_t data) 
{   
    hal_spi_transmit(&SPIMHandle, &data, 1, 5000);
}   

void uc1701_write_cmd(uint8_t cmd)
{
    SEND_CMD;
    CS_LOW;
    uc1701_send_byte(cmd);
    CS_HIGH;
}

void uc1701_write_data(uint8_t data)
{
    SEND_DATA;
    CS_LOW;
    uc1701_send_byte(data);
    CS_HIGH;
}

void uc1701_write_buffer(uint8_t *p_data, uint16_t length)
{
    if (p_data == NULL || length <= 0)
        return ;
    
    SEND_DATA;
    CS_LOW;
  
    master_tx_done = 0;
    hal_spi_transmit_dma(&SPIMHandle, p_data, length);
    while(master_tx_done == 0);
    
    CS_HIGH;
}


void hal_spi_msp_init(spi_handle_t *hspi)
{
    gpio_init_t GPIO_InitStructure;

    NVIC_ClearPendingIRQ(SPI_M_IRQn);
    NVIC_EnableIRQ(SPI_M_IRQn);

    NVIC_ClearPendingIRQ(DMA_IRQn);
    hal_nvic_enable_irq(DMA_IRQn);

    GPIO_InitStructure.mode = DISPLAY_SPIM_GPIO_MUX;
    GPIO_InitStructure.pin = DISPLAY_SPIM_CLK_PIN | DISPLAY_SPIM_MOSI_PIN;
    GPIO_InitStructure.mux = DISPLAY_SPIM_GPIO_MUX;
    hal_gpio_init(DISPLAY_SPIM_GPIO_PORT, &GPIO_InitStructure);

    /* Configure the DMA handler for Transmission process */
    
    hspi->p_dmatx = &TXDMAHandle;
    TXDMAHandle.p_parent = hspi;
    hspi->p_dmatx->channel           = DMA_Channel0;
    hspi->p_dmatx->init.direction     = DMA_MEMORY_TO_PERIPH;
    hspi->p_dmatx->init.src_increment = DMA_SRC_INCREMENT;
    hspi->p_dmatx->init.dst_increment = DMA_DST_NO_CHANGE;
    if (hspi->init.data_size <= SPI_DATASIZE_8BIT)
    {
        hspi->p_dmatx->init.src_data_alignment = DMA_SDATAALIGN_BYTE;
        hspi->p_dmatx->init.dst_data_alignment = DMA_DDATAALIGN_BYTE;
    }
    else if (hspi->init.data_size <= SPI_DATASIZE_16BIT)
    {
        hspi->p_dmatx->init.src_data_alignment = DMA_SDATAALIGN_HALFWORD;
        hspi->p_dmatx->init.dst_data_alignment = DMA_DDATAALIGN_HALFWORD;
    }
    else
    {
        hspi->p_dmatx->init.src_data_alignment = DMA_SDATAALIGN_WORD;
        hspi->p_dmatx->init.dst_data_alignment = DMA_DDATAALIGN_WORD;
    }
    hspi->p_dmatx->init.mode          = DMA_NORMAL;
    hspi->p_dmatx->init.priority      = DMA_PRIORITY_LOW;

    hspi->p_dmarx->channel            = DMA_Channel1;
    hspi->p_dmarx->init.direction     = DMA_PERIPH_TO_MEMORY;
    hspi->p_dmarx->init.src_increment = DMA_SRC_NO_CHANGE;
    hspi->p_dmarx->init.dst_increment = DMA_DST_INCREMENT;
    if (hspi->init.data_size <= SPI_DATASIZE_8BIT)
    {
        hspi->p_dmarx->init.src_data_alignment = DMA_SDATAALIGN_BYTE;
        hspi->p_dmarx->init.dst_data_alignment = DMA_DDATAALIGN_BYTE;
    }
    else if (hspi->init.data_size <= SPI_DATASIZE_16BIT)
    {
        hspi->p_dmarx->init.src_data_alignment = DMA_SDATAALIGN_HALFWORD;
        hspi->p_dmarx->init.dst_data_alignment = DMA_DDATAALIGN_HALFWORD;
    }
    else
    {
        hspi->p_dmarx->init.src_data_alignment = DMA_SDATAALIGN_WORD;
        hspi->p_dmarx->init.dst_data_alignment = DMA_DDATAALIGN_WORD;
    }
    hspi->p_dmarx->init.mode          = DMA_NORMAL;
    hspi->p_dmarx->init.priority      = DMA_PRIORITY_LOW;

    hal_dma_init(hspi->p_dmatx);
    hal_dma_init(hspi->p_dmarx);
}

void uc1701_init(void)
{
    gpio_init_t GPIO_InitStruct = GPIO_DEFAULT_CONFIG;
    GPIO_InitStruct.mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.pin  = DISPLAY_CMD_AND_DATA_PIN;             
    hal_gpio_init(DISPLAY_SPIM_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.pin  = DISPLAY_SPIM_CS0_PIN;
    hal_gpio_init(DISPLAY_SPIM_GPIO_PORT, &GPIO_InitStruct);
  
    SPIMHandle.p_instance              = SPIM;
    SPIMHandle.init.data_size          = SPI_DATASIZE_8BIT;
    SPIMHandle.init.clock_polarity     = SPI_POLARITY_HIGH;
    SPIMHandle.init.clock_phase        = SPI_PHASE_2EDGE;
    SPIMHandle.init.baudrate_prescaler = SystemCoreClock / DISPLAY_SPI_HW_CLOCK;
    SPIMHandle.init.ti_mode            = SPI_TIMODE_DISABLE;
    SPIMHandle.init.slave_select       = SPI_SLAVE_SELECT_0;
    hal_spi_init(&SPIMHandle);
}

 void SPI_M_IRQHandler(void)
{
    hal_spi_irq_handler(&SPIMHandle);
}

void DMA_IRQHandler(void)
{
    hal_dma_irq_handler(SPIMHandle.p_dmatx);
    hal_dma_irq_handler(SPIMHandle.p_dmarx);
}

void hal_spi_tx_cplt_callback(spi_handle_t *hspi)
{
    master_tx_done = 1;
}

void hal_spi_abort_cplt_callback(spi_handle_t *hspi)
{
    printf("This is Abort complete Callback.\r\n");
}

#endif
/*-----------------------------------DRIVER_TYPE_HW_SPI------------------------------------*/



void uc1701_delay(uint16_t time)
{
    delay_ms(time);
}
