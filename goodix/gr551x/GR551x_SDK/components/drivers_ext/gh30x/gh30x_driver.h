/**
 *****************************************************************************************
 *
 * @file gh30x_driver.h
 *
 * @brief gh30x interface function definition.
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

#ifndef __GH30X_DRIVER_H__
#define __GH30X_DRIVER_H__

#include <stdint.h>

void hal_gh30x_gsensor_spi_init(void);
void hal_gh30x_spi_cs_ctrl(uint8_t level);
uint8_t hal_gh30x_spi_write(uint8_t *data, uint16_t data_length);
uint8_t hal_gh30x_spi_read(uint8_t *data, uint16_t data_length);
uint8_t hal_gsensor_spi_write_reg(uint8_t reg_addr, uint8_t data);
uint8_t hal_gsensor_spi_write_mutli_reg(uint8_t reg_addr, uint8_t *data, uint8_t data_length);
uint8_t hal_gsensor_spi_read_reg(uint8_t reg_addr);
uint8_t hal_gsensor_spi_read_mutli_reg(uint8_t reg_addr, uint8_t *data, uint16_t data_length);

void hal_gh30x_gsensor_i2c_init(void);
uint8_t hal_gh30x_i2c_write(uint8_t device_id, const uint8_t* data, uint16_t data_length);
uint8_t hal_gh30x_i2c_read(uint8_t device_id, const uint8_t* cmd, uint16_t cmd_length, uint8_t* data, uint16_t data_length);
uint8_t hal_gsensor_i2c_write_reg(uint8_t device_id, uint8_t reg_addr, uint8_t data);
uint8_t hal_gsensor_i2c_write_mutli_reg(uint8_t device_id, uint8_t reg_addr, uint8_t *data, uint8_t data_length);
uint8_t hal_gsensor_i2c_read_reg(uint8_t device_id, uint8_t reg_addr);
uint8_t hal_gsensor_i2c_read_mutli_reg(uint8_t device_id, uint8_t reg_addr, uint8_t *data, uint16_t data_length);

#endif // __GH30X_DRIVER_H__
