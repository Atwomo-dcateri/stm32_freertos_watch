#ifndef __OLED_H
#define __OLED_H

#include "stdio.h"
#include "stdint.h"

/* 硬件引脚定义 */
#define GPIOx_OLED_PORT               GPIOB
#define OLED_SCK_PIN                  GPIO_PIN_6
#define OLED_SDA_PIN                  GPIO_PIN_7

#define OLED_SDA_ON()                 HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SDA_PIN, GPIO_PIN_SET)
#define OLED_SDA_OFF()                HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SDA_PIN, GPIO_PIN_RESET)
#define OLED_SCK_ON()                 HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SCK_PIN, GPIO_PIN_SET)
#define OLED_SCK_OFF()                HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SCK_PIN, GPIO_PIN_RESET)
#define OLED_SDA_TOGGLE()             HAL_GPIO_TogglePin(GPIOx_OLED_PORT, OLED_SDA_PIN)
#define OLED_SCK_TOGGLE()             HAL_GPIO_TogglePin(GPIOx_OLED_PORT, OLED_SCK_PIN)



/* 基础操作函数 */

void WriteCmd(void);
void OLED_WR_CMD(uint8_t cmd);
void OLED_WR_DATA(uint8_t data);
void OLED_Init(void);
void OLED_Clear(void);


/* 显示控制函数 */

void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_On(void);

/* 文字显示函数 */

void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t Num_Size);

void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);
void OLED_ClearChar(uint8_t x, uint8_t y, uint8_t Char_Size);

void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size);
void OLED_ClearString(uint8_t x, uint8_t y, uint8_t Str_Len, uint8_t Char_Size);

/*  图像显示函数 */

void OLED_ShowImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *Image);
void OLED_ClearImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h);


#endif
