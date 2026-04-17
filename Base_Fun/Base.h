#ifndef __Base_H
#define __Base_H

#include "gpio.h"
#include "Pubilsh.h"

#define LED_ON                  HAL_GPIO_WritePin(GPIOB, LED_Pin, 1)
#define LED_OFF                 HAL_GPIO_WritePin(GPIOB, LED_Pin, 0)

#define SW0                     HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)
#define SW1                     HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)
#define SW2                     HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)
#define SW3                     HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13)



//extern osThreadId defaultTaskHandle;
//extern osThreadId LED_TaskHandle;
//extern osSemaphoreId SW_SignalHandle;


extern uint8_t sw;
extern uint8_t No_OperationTime;
extern _Bool Alarm_Flag;

#endif

