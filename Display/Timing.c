#include "Timing.h"

uint8_t Timing_Num[2] = {0, 0};

/**
  * @brief  显示当前计时时间
  * @param  None
  * @retval None
  */
void Timing_Motion(void) {

    OLED_ShowTimes(0, Timing_Num[0] / 10, 1);
    OLED_ShowTimes(1, Timing_Num[0] % 10, 1);

    OLED_ShowTimes(3, Timing_Num[1] / 10, 1);
    OLED_ShowTimes(4, Timing_Num[1] % 10, 1);

}

/**
  * @brief  初始化计时，将分钟和秒重置为 0
  * @param  None
  * @retval None
  */
void Timing_Init(void) {
     
    Timing_Num[0] = 0;
    Timing_Num[1] = 0;

}
