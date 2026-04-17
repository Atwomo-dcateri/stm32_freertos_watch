/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId RTC_TaskHandle;
osThreadId Root_TaskHandle;
osThreadId Change_TaskHandle;
osThreadId Menu_TaskHandle;
osThreadId Cartoon_TaskHandle;
osThreadId Gyro_TaskHandle;
osThreadId AlarmSet_TaskHandle;
osThreadId AlarmGo_TaskHandle;
osThreadId Timing_TaskHandle;
osThreadId Game_TaskHandle;
osThreadId Key_TaskHandle;
osMutexId Time_SignalHandle;
osMutexId Gyro_SignalHandle;
osMutexId SW_SignalHandle;
osSemaphoreId Key_StateHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osThreadId *Custom_Features[] = {
    &Cartoon_TaskHandle,
    &AlarmSet_TaskHandle,
    &Timing_TaskHandle,
    &Game_TaskHandle
};
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
extern void Read_Time(void const * argument);
extern void Display_Root(void const * argument);
extern void Display_ChangeTime(void const * argument);
extern void Display_Menu(void const * argument);
extern void Display_Cartoon(void const * argument);
extern void Read_Gyro(void const * argument);
extern void Alarm_Set(void const * argument);
extern void Alarm_GO(void const * argument);
extern void Timing(void const * argument);
extern void Game(void const * argument);
extern void Key_Scan(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of Time_Signal */
  osMutexDef(Time_Signal);
  Time_SignalHandle = osMutexCreate(osMutex(Time_Signal));

  /* definition and creation of Gyro_Signal */
  osMutexDef(Gyro_Signal);
  Gyro_SignalHandle = osMutexCreate(osMutex(Gyro_Signal));

  /* definition and creation of SW_Signal */
  osMutexDef(SW_Signal);
  SW_SignalHandle = osMutexCreate(osMutex(SW_Signal));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of Key_State */
  osSemaphoreDef(Key_State);
  Key_StateHandle = osSemaphoreCreate(osSemaphore(Key_State), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of RTC_Task */
  osThreadDef(RTC_Task, Read_Time, osPriorityAboveNormal, 0, 64);
  RTC_TaskHandle = osThreadCreate(osThread(RTC_Task), NULL);

  /* definition and creation of Root_task */
  osThreadDef(Root_task, Display_Root, osPriorityBelowNormal, 0, 128);
  Root_TaskHandle = osThreadCreate(osThread(Root_task), NULL);

  /* definition and creation of Change_Task */
  osThreadDef(Change_Task, Display_ChangeTime, osPriorityBelowNormal, 0, 128);
  Change_TaskHandle = osThreadCreate(osThread(Change_Task), NULL);

  /* definition and creation of Menu_Task */
  osThreadDef(Menu_Task, Display_Menu, osPriorityBelowNormal, 0, 128);
  Menu_TaskHandle = osThreadCreate(osThread(Menu_Task), NULL);

  /* definition and creation of Cartoon_Task */
  osThreadDef(Cartoon_Task, Display_Cartoon, osPriorityBelowNormal, 0, 128);
  Cartoon_TaskHandle = osThreadCreate(osThread(Cartoon_Task), NULL);

  /* definition and creation of Gyro_Task */
  osThreadDef(Cyro_Task, Read_Gyro, osPriorityNormal, 0, 128);
  Gyro_TaskHandle = osThreadCreate(osThread(Cyro_Task), NULL);

  /* definition and creation of AlarmSet_Task */
  osThreadDef(AlarmSet_Task, Alarm_Set, osPriorityBelowNormal, 0, 128);
  AlarmSet_TaskHandle = osThreadCreate(osThread(AlarmSet_Task), NULL);

  /* definition and creation of AlarmGo_Task */
  osThreadDef(AlarmGo_Task, Alarm_GO, osPriorityBelowNormal, 0, 64);
  AlarmGo_TaskHandle = osThreadCreate(osThread(AlarmGo_Task), NULL);

  /* definition and creation of Timing_Task */
  osThreadDef(Timing_Task, Timing, osPriorityBelowNormal, 0, 128);
  Timing_TaskHandle = osThreadCreate(osThread(Timing_Task), NULL);

  /* definition and creation of Game_Task */
  osThreadDef(Game_Task, Game, osPriorityBelowNormal, 0, 128);
  Game_TaskHandle = osThreadCreate(osThread(Game_Task), NULL);

  /* definition and creation of Key_Task */
  osThreadDef(Key_Task, Key_Scan, osPriorityAboveNormal, 0, 64);
  Key_TaskHandle = osThreadCreate(osThread(Key_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

