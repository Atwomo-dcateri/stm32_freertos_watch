#include "menu.h"

/**
  * @brief  在指定位置显示菜单图标
  * @param  
  *     x：菜单项索引
  * @retval None
  */
void Display_MenuLogo(uint8_t x) {

    if (x <= 3)
    {
        OLED_ShowImage(32, 0, 64, 64, MenuElement[x]);
    } else {

        x == Menu_Num? OLED_ShowImage(0, 3, 13, 16, MenuElement[x]): OLED_ShowImage(115, 3, 13, 16, MenuElement[x]);
    }
}

/**
  * @brief  显示静态菜单界面
  * @param  None
  * @retval None
  */

void  Menu_Static(void) {

    Display_MenuLogo(Menu_Num);
    Display_MenuLogo(Menu_Num + 1);
    Display_Choice(1);
}