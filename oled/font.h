#ifndef __FONT_H
#define __FONT_H

#include "stm32f1xx_hal.h"

/* 8行6列的 ASCII 字符点阵（6x8字体） */
extern const uint8_t F6x8[][6];

/* 16行8列的 ASCII 字符点阵（8x16字体 */
extern const uint8_t F8x16[];

/*
    图像数据：

        time0 到 time9：数字 0-9 的图像数据
        timeSplit：时间分隔符（冒号）的图像数据
        timeNumDisplay：指向上述图像数据的指针数组，方便通过索引访问
*/

extern const uint8_t time0[];
extern const uint8_t time1[];
extern const uint8_t time2[];
extern const uint8_t time3[];
extern const uint8_t time4[];
extern const uint8_t time5[];
extern const uint8_t time6[];
extern const uint8_t time7[];
extern const uint8_t time8[];
extern const uint8_t time9[];
extern const uint8_t timeSplit[];
extern const uint8_t *timeNumDisplay[];


#endif
