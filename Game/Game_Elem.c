/*
 * @file    Game_Elem.c
 *  
 * @author  NJ
 * @date    2026-03-27
 * 
 */

#include "Game_Elem.h"
#include "mpu6050.h"


#define size 4

/**
  * @brief  在指定位置显示一个 4x4 像素的小球
  * @param  
  *     @arg x: 0-124
  *     @arg y: 0-60
  * @retval None
  */
void OLED_ShowDot(uint8_t x, uint8_t y) {

    uint8_t Start_Page = y / 8;

    _Bool page = (Start_Page * 8 + 8 - y <  size);

    uint8_t num = 0;

    if (page)
    {
        OLED_Set_Pos(x, Start_Page);

        for (uint8_t i = 0; i < size; i++)
        {
            num = dot[i] << (y - Start_Page * 8);
            OLED_WR_DATA(num);
        }

        OLED_Set_Pos(x, Start_Page + 1);
        
        for (uint8_t i = 0; i < size; i++)
        {
            num = dot[i] >> (8 + Start_Page * 8 - y);
            OLED_WR_DATA(num);
        }
        
    } else {

        OLED_Set_Pos(x, Start_Page);
        for (uint8_t i = 0; i < size; i++)
        {
            num = dot[i] << (y - Start_Page * 8);
            OLED_WR_DATA(num);
        }
        
    }
}


/**
  * @brief  清除指定位置的小球
  * @param  
  *     @arg x：x 坐标（0-124）
  *     @arg y：y 坐标（0-60）
  * @retval None
  */
void Clear_Dot(uint8_t x, uint8_t y) {

    uint8_t Start_Page = y / 8;
    _Bool page = (Start_Page * 8 + 8 - y < size);

    if (page)
    {
        OLED_Set_Pos(x, Start_Page);
        for (uint8_t i = 0; i < size; i++)
        {
            OLED_WR_DATA(0);
        }
        
        OLED_Set_Pos(x, Start_Page + 1);

        for (uint8_t i = 0; i < size; i++)
        {
            OLED_WR_DATA(0);
        }
        
    } else {

        OLED_Set_Pos(x, Start_Page);
        for (uint8_t i = 0; i < size; i++)
        {
            OLED_WR_DATA(0);
        }   
    }
}

/**
  * @brief  在屏幕中央显示一个目标圆圈
  * @param  None 
  * @retval None
  */
void OLED_ShowCir(void) {


    uint8_t num = 0;
    OLED_Set_Pos(60, 3);

    for (uint8_t i = 0; i < 9; i++)
    {
        num = circle[i] << 4;

        OLED_WR_DATA(num);
    }
    
    OLED_Set_Pos(60, 4);

    for (uint8_t i = 9; i < 18; i++)
    {
        num = (circle[i] << 4) | ((0xF0 & circle[i - 9]) >> 4);
        OLED_WR_DATA(num);
    }
}

float k = 0.2;
int16_t x = 0;
int16_t y = 0;


/**
  * @brief  游戏主循环，控制小球移动和游戏逻辑
  * @param  None
  * @retval IsGameEnd: 游戏结束标志
  */
_Bool My_Game(void) {

    _Bool IsGameEnd = 0;
    int8_t vx = angle.KalmanAngleX * k;
    int8_t vy = angle.KalmanAngleY * k;

    Clear_Dot(x, y);

    x -= vx;
    y += vy;

    if (x < 0)
    {
        x  = 0;
    } else if (x > 124)
    {
        x = 124;
    }
    
    if (y < 0)
    {
        y = 0;
    } else if (y > 60)
    {
        y = 60;
    }

    OLED_ShowCir();
    OLED_ShowDot(x, y);

    if (x >= 60 && x <= 64 && y >= 28 && y <= 32 && vx * vx + vy * vy <= 4)
    {
        IsGameEnd = 1;
        
    }
    
    return IsGameEnd;
}


void Game_Init(void) {

    OLED_ShowCir();
    OLED_ShowDot(0, 0);

    x = 0;
    y = 0;
}

