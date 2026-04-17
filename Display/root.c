#include "root.h"

/* 存储星期缩写字符串 */
uint8_t *weeks[] = {(uint8_t *)"Mon", (uint8_t *)"Tue", (uint8_t *)"Wed", (uint8_t *)"Thu", (uint8_t *)"Fri", (uint8_t *)"Sat", (uint8_t *)"Sun"};

/**
  * @brief  更新根界面的显示内容
  * @param  None
  * @retval None
  */
void Root_Motion(void) {

    OLED_ShowTimes(0, hrs / 10, 1);// 显示时间
    OLED_ShowTimes(1, hrs % 10, 1);
    OLED_ShowTimes(2, 10, sec % 2);
    OLED_ShowTimes(3, mins / 10, 1);
    OLED_ShowTimes(4, mins % 10, 1);

    OLED_ShowTimes(5, years, 1);// 显示日期
    OLED_ShowTimes(6, mons, 1);
    OLED_ShowTimes(7, day, 1);
    OLED_ShowTimes(8, week, 1);
    
}

/**
  * @brief  在指定位置显示数字或信息
  * @param  
  *     @arg place ：显示位置（0-8）
  *     @arg num：要显示的数字
  *     @arg state：显示状态（true 显示，false 清除）
  * @retval None
  */
void OLED_ShowTimes(uint8_t place, uint16_t num, _Bool state) {


    place = place % 9;

    if (place <= 4 && place != 2)
    {
        state ? OLED_ShowImage(4 + 24 * place, 1, 24, 48, timeNumDisplay[num % 10]) : OLED_ClearImage(4 + 24 * place, 1, 24, 48);
        return;
    }
    
    unsigned char c[] =  {num / 10 + '0', num % 10 + '0', '/',  '\0'};
    
    switch(place) {

        case 2:
            state? OLED_ShowImage(4 * 24 * place, 1, 24, 48, timeNumDisplay[10]): OLED_ClearImage(4 + 24 *place, 1, 24, 48);
            break;
        case 5:
            state? OLED_ShowString(0, 0, c, 8): OLED_ClearString(0, 0, 2, 8);
            break;
        case 6:
            state? OLED_ShowString(24, 0, c, 8): OLED_ClearString(24, 0, 2, 8);
            break;
        case 7:
            state? OLED_ShowString(48, 0, c, 8): OLED_ClearString(48, 0, 2, 8);
            break;
        case 8:
            state? OLED_ShowString(104, 0, weeks[num], 8): OLED_ClearString(0, 0, 3, 8);
            break;           
    }
}
