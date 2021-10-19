/**
 ****************************************************************************************
 *
 * @file uc1701_config.h
 *
 * @brief Header file - uc1701_config.h
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

#ifndef _UC1701_CONFIG_H_
#define _UC1701_CONFIG_H_

#include "gr55xx_hal.h"
#include "boards.h"


#define CS_HIGH	   ll_gpio_set_output_pin(DISPLAY_SPIM_GPIO_PORT, DISPLAY_SPIM_CS0_PIN)   /**< set cs pin to high. */
#define CS_LOW	   ll_gpio_reset_output_pin(DISPLAY_SPIM_GPIO_PORT, DISPLAY_SPIM_CS0_PIN) /**< set cs pin to low. */
#define SEND_CMD   ll_gpio_reset_output_pin(GPIO0, DISPLAY_CMD_AND_DATA_PIN)              /**< set cmd pin to high. */
#define SEND_DATA  ll_gpio_set_output_pin(GPIO0, DISPLAY_CMD_AND_DATA_PIN)                /**< set cmd pin to low. */

#ifdef DISPLAY_DRIVER_TYPE_SW_IO

#define SCK_HIGH   ll_gpio_set_output_pin(GPIO0, DISPLAY_SPIM_CLK_PIN)                    /**< set sck pin to high. */
#define SCK_LOW    ll_gpio_reset_output_pin(GPIO0, DISPLAY_SPIM_CLK_PIN)                  /**< set sck pin to low. */
#define SDA_HIGH   ll_gpio_set_output_pin(GPIO0, DISPLAY_SPIM_MOSI_PIN)                   /**< set sda pin to high. */
#define SDA_LOW    ll_gpio_reset_output_pin(GPIO0, DISPLAY_SPIM_MOSI_PIN)                 /**< set sda pin to low. */

#endif


/**
 * @defgroup UC1701_CONFIG_FUNCTION Functions
 * @{
 */
/**
 *****************************************************************************************
 * @brief Uc1701 init(config gpio spi).
 *****************************************************************************************
 */
void uc1701_init(void);

/**
 *****************************************************************************************
 * @brief Write data buffer to uc1701.
 *
 * @param[in] p_data: The pointer of the data.
 * @param[in] length: The length of write data.
 *****************************************************************************************
 */
void uc1701_write_buffer(uint8_t *p_data, uint16_t length);

/**
 *****************************************************************************************
 * @brief Write one data to uc1701.
 *
 * @param[in] data:  Data to write.
 *****************************************************************************************
 */
void uc1701_write_data(uint8_t data);

/**
 *****************************************************************************************
 * @brief Write cmd to uc1701.
 *
 * @param[in] cmd:  Cmd to write.
 *****************************************************************************************
 */
void uc1701_write_cmd(uint8_t cmd);

/**
 *****************************************************************************************
 * @brief Uc1701 delay function. 
 *
 * @param[in] time:  Delay time.
 *****************************************************************************************
 */
void uc1701_delay(uint16_t time);

#endif


