#include "Display.h"

/**
  * @brief  根据不同的界面状态显示相应的选择按钮
  * @param  None
  * @retval None
  */
void Display_Choice(uint8_t c) {

    switch (c)
    {
    case 0:
        OLED_ShowString(0, 7, "Menu", 8);
        OLED_ShowString(78, 7, "Change", 8);
        break;
    case 1:
        OLED_ShowString(0, 7, "Ok", 8);
        OLED_ShowString(96, 7, "Bye", 8);
        break;
    case 2:
        OLED_ShowString(0, 7, "Start", 8);
        OLED_ShowString(96, 7, "Bye", 8);
        break;
    case 3:
        OLED_ShowString(0, 7, "Stop", 8);
        OLED_ShowString(96, 7, "Bye", 8);
        break;
    case 4:
        OLED_ShowImage(0, 0, 128, 64, end);
        OLED_ShowString(0, 7, "Again", 8);
        OLED_ShowString(96, 7, "Bye", 8);
        break;
    case 5:
        OLED_ShowTimes(2, 10, 1);
        OLED_ShowString(96, 7, "Bye", 8);
        OLED_ShowString(94, 7, "Init", 8);
        break;
    case 6:
        OLED_ShowString(0, 7, "Ok", 8);
        OLED_ShowString(78, 7, "Delete", 8);
        break;
    default:
        break;
    }
}