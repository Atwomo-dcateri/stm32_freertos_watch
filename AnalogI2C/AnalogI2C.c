#include "AnalogI2C.h"

/**
  * @brief  i2c I/O配置
  * @param  None
  * @retval None
  */

void I2C_GPIO_Config(void) {

    GPIO_InitTypeDef GPIO_Initure;

    /* 使能与 I2C 有关的时钟 */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* I2C_SCL、I2C_SDA 配置*/

    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_Initure.Pin = I2C_SCL_PIN | I2C_SDA_PIN;
    HAL_GPIO_Init(I2C_SCL_PORT, &GPIO_Initure);
    HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN | I2C_SDA_PIN, GPIO_PIN_SET);


}

/**
  * @brief  I2C 总线位延时， 最快400kHz
  * @param  None
  * @retval None
  */

void i2c_Delay(void) {
    uint8_t i;

    /*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
    for ( i = 0; i < 10; i++);
    
}


/**
  * @brief  I2C总线启动信号
  * @param  None
  * @retval None
  */

void i2c_Start(void) {
    /* 当SCL高电平时，SDA出现一个下跳沿表示总线开始信号*/
    I2C_SDA_1();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_0();
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();

}

/**
  * @brief  I2C总线停止信号
  * @param  None
  * @retval None
  */
void i2c_Stop() {
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号*/
    I2C_SDA_0();
    I2C_SCL_1();

    i2c_Delay();
    I2C_SDA_1();
}

/**
  * @brief  MCU向I2C总线设备发送8bit数据
  * @param  
  *     @arg _ucByte
  * @retval None
  */

void i2c_SendByte(uint8_t _ucByte) {

    uint8_t i;

    /* 先发送字节的高位bit7 */

    for ( i = 0; i < 8; i++)
    {
        if (_ucByte & 0x80)
        {
            I2C_SDA_1();
        } else {
            I2C_SDA_0();
        }

        i2c_Delay();

        I2C_SCL_1();
        i2c_Delay();
        I2C_SCL_0();
        
        if (i == 7)
        {
            I2C_SDA_1(); // 释放总线
        }
        
        _ucByte <<= 1;// 左移一个bit位
        i2c_Delay();
    }
}

/**
  * @brief  MCU从I2C总线设备读取8bit数据
  * @param
  * @retval 读到的数据
  */

uint8_t i2c_Readbyte(void) {

    uint8_t i, value;

    for ( i = 0; i < 8; i++)
    {
        value <<= 1; // 将第一位清零
        I2C_SCL_1();
        i2c_Delay();

        if (I2C_SDA_READ())// 发现SDA的电平为1
        {
            value++; // 读取引脚值
        }
        
        I2C_SCL_0();
        i2c_Delay();
    }
    
    return value;
}

uint8_t i2c_ReadByte(void) {
    return i2c_Readbyte();
}


/**
  * @brief  MCU产生一个时钟，并读取器件的ACK应答信号
  * @param  None
    * @retval 返回1表示正确应答，返回0表示器件没有响应
  */
 uint8_t i2c_WaitAck() {

    uint8_t re;

    I2C_SDA_1(); /* CPU释放SDA总线*/
    i2c_Delay();

    I2C_SCL_1();  /* CPU驱动SCL=1， 此时器件会返回ACK应答*/

    i2c_Delay();

    if (I2C_SDA_READ()) /* CPU读取SDA口线的状态*/
    {
        re = 1;
    } else {

        re = 0;
    }
    I2C_SCL_0();
    i2c_Delay();

    return re;

 }


/**
  * @brief  MCU产生一个ACK信号
  * @param  None
  * @retval None
  */

void i2c_Ack() {

    I2C_SDA_0(); /* CPU驱动SDA = 0 */
    i2c_Delay();
    I2C_SCL_1(); /* CPU产生一个时钟信号*/
    i2c_Delay(); 
    I2C_SCL_0();
    i2c_Delay();
    I2C_SDA_1(); /* CPU释放SDA总线 */
}

/**
  * @brief  MCU产生一个NACK信号
  * @param  None
  * @retval None
  */

void i2c_NAck(void) {

    I2C_SDA_1(); /* CPU驱动SDA = 1 */
    i2c_Delay(); 
    I2C_SCL_1(); /* 产生一个时钟信号*/
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();

}


/**
  * @brief  检测I2C总线设备， CPU发送设备地址，然后读取设备应答信号来判断该设备是否存在
  * @param
        @arg _Address: 设备的I2C总线地址
  * @retval 返回 0 表示正确，返回 1 表示不存在
  */

uint8_t i2c_CheckDevice(uint8_t _Address) {

    uint8_t ucAck;

    I2C_GPIO_Config(); /* 配置GPIO */
    i2c_Stop();

    i2c_Start(); /* 发送启动信号 */

    /* 发送设备地址 + 读写控制bit（0 = w，1 = r）从bit7先传*/

    i2c_SendByte(_Address | I2C_WR);
    ucAck = i2c_WaitAck(); /* 检测设备ACK应答 */ 

    i2c_Stop(); /* 发送停止信号 */

    return ucAck;
    
}
