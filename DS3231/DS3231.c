#include "DS3231.h"

/* 初始化全局日历对象 calendar，默认值为 26年3月27日 15:42:04 */
_calendar_obj calender = {26, 3, 27, 0, 15, 42, 4, 0};

/**
  * @brief  初始化 I2C 通信
  * @param  None
  * @retval None
  */

void I2C_DS3231_Init(void) {

    I2C_GPIO_Config();
    
    /* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */

    i2c_Stop();

}


/**
  * @brief  向 DS3231 写入一个字节
  * @param  None
  * @retval None
  */

uint32_t I2C_DS3231_ByteWrite(u8 WriteAddr, u8 data) 
{
    i2c_Start();
    i2c_SendByte(DS3231_ADDRESS | I2C_WR);

    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }

    i2c_SendByte(data);

    if (i2c_WaitAck != 0)
    {
        goto cmd_fail;
    }
    i2c_Stop();
    return 1;

    cmd_fail:
        i2c_Stop();
        return 0;
}

/**
  * @brief  从 DS3231 读取一个字节
  * @param  
  *     @arg 寄存器地址
  * @retval data
  */
uint8_t I2C_DS3231_DataRead(u8 ReadAddr) {

    uint8_t data;

    i2c_Start();
    i2c_SendByte(DS3231_ADDRESS | I2C_WR);
    
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    i2c_SendByte(ReadAddr | I2C_RD);

    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    data = i2c_Readbyte();
    i2c_NAck();
    i2c_Stop();
    return data;
    cmd_fail:
        i2c_Stop();
        return 0;
}

/**
  * @brief  设置 DS3231 的时间
  * @param  
  *   @arg u8 year,u8 month,u8 date,u8 week,u8 hour,u8 minute,u8 second
  * @retval 
  */
void I2C_DS3231_SetTime(u8 year,u8 month,u8 date,u8 week,u8 hour,u8 minute,u8 second){


    u8 temp;

    temp = DEC_BCD(year);
    I2C_DS3231_ByteWrite(DS3231_YEAR, temp);
    temp = DEC_BCD(month);
    I2C_DS3231_ByteWrite(DS3231_MONTH, temp);
    temp = DEC_BCD(date);
    I2C_DS3231_ByteWrite(DS3231_DAY, temp);
    temp = DEC_BCD(week);
    I2C_DS3231_ByteWrite(DS3231_WEEK, temp);
    temp = DEC_BCD(hour);
    I2C_DS3231_ByteWrite(DS3231_HOUR, temp);
    temp = DEC_BCD(minute);
    I2C_DS3231_ByteWrite(DS3231_MINUTE, temp);
    temp = DEC_BCD(second);
    I2C_DS3231_ByteWrite(DS3231_SECOND, temp);
}


/**
  * @brief  获取 DS3231 的当前时间
  * @param  None
  * @retval None
  */
void I2C_DS3231_getTime(void) {

    calender.now_year = I2C_DS3231_DataRead(DS3231_YEAR);
    calender.now_year = BCD_DEC(calender.now_year);
    calender.month = I2C_DS3231_DataRead(DS3231_MONTH);
    calender.month = BCD_DEC(calender.month);
    calender.date = I2C_DS3231_DataRead(DS3231_DAY);
    calender.date = BCD_DEC(calender.date);
    calender.now_week = I2C_DS3231_DataRead(DS3231_WEEK);
    calender.now_week = BCD_DEC(calender.now_week);
    calender.hour = I2C_DS3231_DataRead(DS3231_HOUR);
    calender.hour = BCD_DEC(calender.hour);
    calender.hour &= 0x3f;
    calender.minute = I2C_DS3231_DataRead(DS3231_MINUTE);
    calender.minute = BCD_DEC(calender.minute);
    calender.second = I2C_DS3231_DataRead(DS3231_SECOND);
    calender.second = BCD_DEC(calender.second);
}

/**
  * @brief  获取 DS3231 的温度
  * @param  None
  * @retval None
  */

void I2C_DS3231_getTemprature(void) {

    I2C_DS3231_ByteWrite(DS3231_CONTROL, 0x20 | 0x05);
    calender.now_temprature = I2C_DS3231_DataRead(DS3231_TEMPERATUREH); //只读取了温度的整数部分，精度为 1°C
}

/**
  * @brief  设置 DS3231 的闹钟
  * @param  
  *     @arg uint8_t hour, uint8_t minute
  * @retval None
  */

void I2C_DS3231_SetAlarm(uint8_t hour, uint8_t minute) {

    I2C_DS3231_ByteWrite(DS3231_CONTROL, DS3231_XTAL);
    I2C_DS3231_ByteWrite(DS3231_SALARM1ECOND, 0);
    I2C_DS3231_ByteWrite(DS3231_ALARM1HOUR, DEC_BCD(hour));
    I2C_DS3231_ByteWrite(DS3231_ALARM1MINUTE, DEC_BCD(minute));
    I2C_DS3231_ByteWrite(DS3231_WEEK, 0x81);

}

/**
  * @brief  清除 DS3231 的闹钟
  * @param  None
  * @retval None
  */
void I2C_DS3231_ClearAlarm(void) {

    I2C_DS3231_ByteWrite(DS3231_CONTROL, 0x1C);//写入控制寄存器，禁用闹钟
}


/**
  * @brief  读取 DS3231 的闹钟设置
  * @param  
  *     @arg uint8_t *arr
  * @retval None
  */

void I2C_DS3231_ReadAlarm(uint8_t *arr) {
    // 存储闹钟时间的数组
    uint8_t num;

    num = I2C_DS3231_DataRead(DS3231_ALARM1HOUR);
    arr[0] = num >> 4;
    arr[1] = num & 0x0f;

    num = I2C_DS3231_DataRead(DS3231_ALARM1MINUTE);
    arr[2] = num >> 4;
    arr[3] = num & 0x0f;
}


/**
  * @brief  将 BCD 码转换为十进制
  * @param  
  *      @arg uint8_t value
  * @retval None
  */
uint8_t BCD_DEC(uint8_t value) {

    u8 i;
    i = value & 0x0f;
    value >>= 4;
    value &= 0x0f;
    value *= 10;// 十位乘以 10
    i += value;// 个位加上十位乘以 10 的结果
    return i;
}

/**
  * @brief  将十进制转换为 BCD 码
  * @param  
  *     @arg 
  * @retval 
  */

uint8_t DEC_BCD(uint8_t value) {

    u8 i, j, k;

    i = value / 10;
    j = value % 10;
    k = j + (i << 4);
    return k;
}
