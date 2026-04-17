#include "cartoon.h"

/**
  * @brief  绘制kunkun舞蹈（在 OLED 屏幕上显示跳舞动画的一帧）
  * @param  None
  *     @arg x: 动画帧索引，用于选择要显示的动画帧
  * @retval None
  */
void Kunkun_dance(uint8_t x) {

    OLED_ShowImage(0, 0, 128, 64, Video_Images[x]);
    
}