/**
 *****************************************************************************************
 *
 * @file gh30x_i2c_api.c
 *
 * @brief Implementation of gh30x function supporting I2C interface.
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

#include "gr55xx_hal.h"
#include "gh30x_driver.h"

i2c_handle_t gh30x_i2c_handle;

void hal_gh30x_gsensor_i2c_init(void)
{
    gh30x_i2c_handle.p_instance             = I2C0;
    gh30x_i2c_handle.init.speed             = I2C_SPEED_400K;
    gh30x_i2c_handle.init.own_address       = 0x55;
    gh30x_i2c_handle.init.addressing_mode   = I2C_ADDRESSINGMODE_7BIT;
    gh30x_i2c_handle.init.general_call_mode = I2C_GENERALCALL_DISABLE;

    hal_i2c_deinit(&gh30x_i2c_handle);
    hal_i2c_init(&gh30x_i2c_handle);
    return;
}

uint8_t hal_gh30x_i2c_write(uint8_t device_id, const uint8_t* data, uint16_t data_length)
{
    hal_status_t status = HAL_OK;

    status = hal_i2c_master_transmit(&gh30x_i2c_handle, device_id, (uint8_t*)data, data_length, 1000);
    return status ? 0: 1;
}

uint8_t hal_gh30x_i2c_read(uint8_t device_id, const uint8_t* cmd, uint16_t cmd_length, uint8_t* data, uint16_t data_length)
{
    hal_status_t status = HAL_OK;

    status = hal_i2c_master_transmit(&gh30x_i2c_handle, device_id, (uint8_t*)cmd, cmd_length, 1000);
    if(HAL_OK == status)
    {
        status = hal_i2c_master_receive(&gh30x_i2c_handle, device_id, data, data_length, 1000);
    }
    return status ? 0: 1;
}

uint8_t hal_gsensor_i2c_write_reg(uint8_t device_id, uint8_t reg_addr, uint8_t data)
{
    hal_status_t status = HAL_OK;

    status = hal_i2c_mem_write(&gh30x_i2c_handle, device_id, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, sizeof(data), 1000);
    return status ? 0: 1;
}

uint8_t hal_gsensor_i2c_write_mutli_reg(uint8_t device_id, uint8_t reg_addr, uint8_t *data, uint8_t data_length)
{
    hal_status_t status = HAL_OK;

    uint8_t length = data_length > 31? 31: data_length;
    status = hal_i2c_mem_write(&gh30x_i2c_handle, device_id, reg_addr, I2C_MEMADD_SIZE_8BIT, data, length, 1000);;
    return status ? 0: 1;
}

uint8_t hal_gsensor_i2c_read_reg(uint8_t device_id, uint8_t reg_addr)
{
    uint8_t data = 0;

    hal_i2c_mem_read(&gh30x_i2c_handle, device_id, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, sizeof(data), 1000);
    return data;
}

uint8_t hal_gsensor_i2c_read_mutli_reg(uint8_t device_id, uint8_t reg_addr, uint8_t *data, uint16_t data_length)
{
    hal_status_t status = HAL_OK;

    status = hal_i2c_mem_read(&gh30x_i2c_handle, device_id, reg_addr, I2C_MEMADD_SIZE_8BIT, data, data_length, 1000);
    return status;
}
