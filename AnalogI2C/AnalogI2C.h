#ifndef _AnalogI2c_H
#define _AanlogI2c_H

#include "gpio.h"

#ifndef PEXT
#define PEXT extern
#endif

//#define I2C_GPIO_APBxClock_FUN RCC_AHB1PeriphClockCmd
//#define I2C_GPIO_CLK           RCC_APB2Priph_GPIOB

#define I2C_SCL_PORT             GPIOB
#define I2C_SCL_PIN              GPIO_PIN_10
#define I2C_SDA_PORT             GPIOB
#define I2C_SDA_PIN              GPIO_PIN_11

#define I2C_WR 0
#define I2C_RD 1


#define I2C_SCL_1()               HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_SET)
#define I2C_SCL_0()               HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_RESET)
#define I2C_SDA_1()               HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_SET)
#define I2C_SDA_0()               HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_RESET)
#define I2C_SDA_READ()            HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN)

/* STM32 I2C 快速模式 */
#define I2C_Speed                 400000//最快400kHz


extern void I2C_GPIO_Config(void);
extern void i2c_Delay(void);
extern void i2c_Start(void);
extern void i2c_Stop(void);
extern void i2c_SendByte(uint8_t ucByte);
extern uint8_t i2c_Readbyte(void);
extern uint8_t i2c_ReadByte(void);
extern uint8_t i2c_WaitAck(void);
extern void i2c_NAck(void);
extern void i2c_Ack(void);
extern uint8_t i2c_CheckDevice(uint8_t _Address);


#endif
