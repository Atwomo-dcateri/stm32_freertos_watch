#ifndef ROOT_H
#define ROOT_H

#include "AllInclude.h"
#include "i2c.h"
#include "DS3231.h"

#define years           calender.now_year
#define mons            calender.month
#define day             calender.date
#define week            calender.now_week
#define hrs             calender.hour
#define mins            calender.minute
#define sec             calender.second
#define temprature      calender.now_temprature

void OLED_ShowTimes(uint8_t place, uint16_t num, _Bool state);
void Root_Motion(void);

#endif
