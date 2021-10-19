#ifndef __SSD1316_I2C_SOFT_H__
#define __SSD1316_I2C_GPIO_API_H__

#include "gr55xx_ll_aon_gpio.h"

#define USER_I2C_BAUDRATE_400K              400000u
#define USER_I2C_BAUDRATE_200K              200000u
#define USER_I2C_BAUDRATE_100K              100000u

#define USER_I2C_ACK_BIT                     0x01
#define USER_I2C_ACK                          0x00
#define USER_I2C_NACK                         0x01
#define USER_I2C_BUSY_BIT                    0x02
#define USER_I2C_UNDEF_BIT                   0x80
#define USER_I2C_DEFAULT                     USER_I2C_ACK

void SSD_UserI2cConfig(uint32_t BaudRate);
uint8_t SSD_UserI2cReadByteWithStart(uint8_t dev_addr);
uint8_t SSD_UserI2cReadByte(uint8_t *data);
uint8_t SSD_UserI2cReadByteWithStop(uint8_t *data);
uint8_t SSD_UserI2cWriteByteWithStart(uint8_t dev_addr);
uint8_t SSD_UserI2cWriteByte(uint8_t data);
uint8_t SSD_UserI2cWriteByteWithStop(uint8_t data);

#endif
