#include "Alarm.h"

/**
  * @brief  初始化闹钟界面
  * @param  
  *     @arg arr: 存储闹钟界面图像数组
  * @retval None
  */
void Alarm_Init(uint8_t *arr) {

    OLED_ShowTimes(0, arr[0], 1);
    OLED_ShowTimes(1, arr[1], 1);
    OLED_ShowTimes(2, 1, 1);
    OLED_ShowTimes(3, arr[2], 1);
    OLED_ShowTimes(4, arr[3], 1);

}