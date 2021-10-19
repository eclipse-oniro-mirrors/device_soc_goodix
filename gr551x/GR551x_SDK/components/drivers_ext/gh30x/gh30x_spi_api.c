/**
 *****************************************************************************************
 *
 * @file gh30x_spi_api.c
 *
 * @brief Implementation of gh30x function supporting SPI interface.
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

#include <string.h>
#include "gr55xx_hal.h"
#include "gh30x_driver.h"

spi_handle_t gh30x_spi_handle;

void hal_gh30x_gsensor_spi_init(void)
{
    gh30x_spi_handle.p_instance              = SPIM;
    gh30x_spi_handle.init.data_size          = SPI_DATASIZE_8BIT;
    gh30x_spi_handle.init.clock_polarity     = SPI_POLARITY_LOW;
    gh30x_spi_handle.init.clock_phase        = SPI_PHASE_1EDGE;
    gh30x_spi_handle.init.baudrate_prescaler = SystemCoreClock / 2000000;
    gh30x_spi_handle.init.ti_mode            = SPI_TIMODE_DISABLE;
    gh30x_spi_handle.init.slave_select       = SPI_SLAVE_SELECT_0;

    hal_spi_deinit(&gh30x_spi_handle);
    hal_spi_init(&gh30x_spi_handle);
}

uint8_t hal_gh30x_spi_write(uint8_t *data, uint16_t data_length)
{
    hal_status_t status = HAL_OK;

    status = hal_spi_transmit(&gh30x_spi_handle, data, data_length, 1000);
    return status ? 0: 1;
}

uint8_t hal_gh30x_spi_read(uint8_t *data, uint16_t data_length)
{
    hal_status_t status = HAL_OK;

    status = hal_spi_receive(&gh30x_spi_handle, data, data_length, 1000);
    return status ? 0: 1;
}

void hal_gh30x_spi_cs_ctrl(uint8_t level)
{
    return;
}

uint8_t hal_gsensor_spi_write_reg(uint8_t reg_addr, uint8_t data)
{
    hal_status_t status = HAL_OK;
    uint8_t buffer[2];

    buffer[0] = reg_addr;
    buffer[1] = data;
    status = hal_spi_transmit(&gh30x_spi_handle, buffer, sizeof(buffer), 1000);
    return status ? 0: 1;
}

uint8_t hal_gsensor_spi_write_mutli_reg(uint8_t reg_addr, uint8_t *data, uint8_t data_length)
{
    hal_status_t status = HAL_OK;
    uint8_t buffer[256];

    buffer[0] = reg_addr;
    memcpy(&buffer[1], data, data_length);
    status = hal_spi_transmit(&gh30x_spi_handle, buffer, data_length + 1, 1000);
    return status ? 0: 1;
}

uint8_t hal_gsensor_spi_read_reg(uint8_t reg_addr)
{
    uint8_t data;

    hal_spi_transmit_receive(&gh30x_spi_handle, &reg_addr, &data, 2, 1000);
    return data;
}

uint8_t hal_gsensor_spi_read_mutli_reg(uint8_t reg_addr, uint8_t *data, uint16_t data_length)
{
    hal_status_t status = HAL_OK;

    status = hal_spi_transmit_receive(&gh30x_spi_handle, &reg_addr, data, data_length + 1, 1000);
    return status ? 0: 1;
}
