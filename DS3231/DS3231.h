/*
 * @file    DS3231.h
 *  
 * @author  NJ
 * @date    2026-03-27
 * 
 */

#ifndef DS3231_H
#define DS3231_H

#include "AnalogI2C.h"


#ifdef _I2C_DS3231_PUBILIC

/* PEXT 宏用于控制函数和变量的可见性 */
#define PEXT
#else
#define PEXT extern
#endif

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


typedef struct 
{
    u8 now_year;
    u8 month;
    u8 date;
    u8 now_week;
    u8 hour;
    u8 minute;
    u8 second;
    u8 now_temprature;
    
} _calendar_obj;


extern _calendar_obj calender;


/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define 						I2Cx_OWN_ADDRESS7     						0X0A   
/* DS3231 地址定义 */
#define 						DS3231_ADDRESS 								0xD0   
 
/* DS3231寄存器地 址 */
																					
#define							DS3231_SECOND								0x00    //秒
#define 						DS3231_MINUTE      							0x01    //分
#define 						DS3231_HOUR        							0x02    //时
#define 						DS3231_WEEK         						0x03    //星期
#define 						DS3231_DAY          						0x04    //日
#define 						DS3231_MONTH                      		    0x05    //月
#define                         DS3231_YEAR        						    0x06    //年 	

/* 闹铃1 */          	
#define                         DS3231_SALARM1ECOND                         0x07    //秒
#define 						DS3231_ALARM1MINUTE                         0x08    //分
#define                         DS3231_ALARM1HOUR                           0x09    //时
#define 						DS3231_ALARM1WEEK  						    0x0A    //星期/日

/* 闹铃2 */
#define 						DS3231_ALARM2MINUTE 						0x0b    //分
#define 						DS3231_ALARM2HOUR                           0x0c    //时
#define 						DS3231_ALARM2WEEK                           0x0d    //星期/日
 
#define 						DS3231_CONTROL                              0x0e    //控制寄存器
#define 						DS3231_STATUS                               0x0f    //状态寄存器
#define 						BSY                 					    2       //忙
#define 						OSF                						    7       //振荡器停止标志
#define 						DS3231_XTAL         						0x10    //晶体老化寄存器
#define 						DS3231_TEMPERATUREH 						0x11    //温度寄存器高字节(8位)
#define 						DS3231_TEMPERATUREL 						0x12    //温度寄存器低字节(高2位) 																				

/* I2C 通信函数I2C 通信函数 */
PEXT void I2C_DS3231_Init(void);
PEXT uint32_t I2C_DS3231_ByteWrite(u8 WriteAddr, u8 data);
PEXT uint8_t I2C_DS3231_DataRead(u8 Read_Addr);

/* 数据转换函数 */
PEXT uint8_t BCD_DEC(u8 value);
PEXT uint8_t DEC_BCD(u8 value);

/* 时间管理函数 */

PEXT void I2C_DS3231_SetTime(u8 year, u8 month, u8 date, u8 week, u8 hour, u8 minute, u8 second);
PEXT void I2C_DS3231_getTime(void);
PEXT void I2C_DS3231_getTemprature(void);

/* 闹钟函数 */

PEXT void I2C_DS3231_SetAlarm(uint8_t h, uint8_t m);
PEXT void I2C_DS3231_ReadAlarm(uint8_t *arr);
PEXT void I2C_DS3231_ClearAlarm(void);

#undef PEXT
#endif


