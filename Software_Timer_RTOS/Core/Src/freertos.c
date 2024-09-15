/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "timers.h"
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
osTimerId_t Timer_ThreeHandle, Timer_FourHandle, Timer_FiveHandle, Timer_SixHandle;
/* USER CODE END Variables */
/* Definitions for Task_One */
osThreadId_t Task_OneHandle;
const osThreadAttr_t Task_One_attributes = {
  .name = "Task_One",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Timer_One */
osTimerId_t Timer_OneHandle;
const osTimerAttr_t Timer_One_attributes = {
  .name = "Timer_One"
};
/* Definitions for Timer_Two */
osTimerId_t Timer_TwoHandle;
const osTimerAttr_t Timer_Two_attributes = {
  .name = "Timer_Two"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskOne(void *argument);
void MyTimerOne_Callback(void *argument);
void MyTimerTwo_Callback(void *argument);

/* FreeRTOS API*/
void MyTimer_Callback(TimerHandle_t xTimer);


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) (CMSIS) */
  /* creation of Timer_One */
  Timer_OneHandle = osTimerNew(MyTimerOne_Callback, osTimerPeriodic, NULL, &Timer_One_attributes);

  /* creation of Timer_Two */
  Timer_TwoHandle = osTimerNew(MyTimerTwo_Callback, osTimerOnce, NULL, &Timer_Two_attributes);
	
 /* Create the timer(s) (FreeRTOS APIs) */
  Timer_ThreeHandle = xTimerCreate("Timer3",pdMS_TO_TICKS(100),pdTRUE,( void * ) 3,MyTimer_Callback);
  Timer_FourHandle = xTimerCreate("Timer4",pdMS_TO_TICKS(200),pdTRUE,( void * ) 4,MyTimer_Callback);
  Timer_FiveHandle = xTimerCreate("Timer5",pdMS_TO_TICKS(300),pdTRUE,( void * ) 5,MyTimer_Callback);
  Timer_SixHandle = xTimerCreate("Timer6",pdMS_TO_TICKS(400),pdTRUE,( void * ) 6,MyTimer_Callback);
  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_One */
  Task_OneHandle = osThreadNew(TaskOne, NULL, &Task_One_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_TaskOne */
/**
  * @brief  Function implementing the Task_One thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskOne */
void TaskOne(void *argument)
{
  /* USER CODE BEGIN TaskOne */
	BaseType_t TimerStartRetVal = 0;
	
	// Start Timers Using CMSIS 
	osTimerStart(Timer_OneHandle,100);
	osTimerStart(Timer_TwoHandle,1000);
	
	// Start Timers Using FreeRTOS APIs	
	TimerStartRetVal = xTimerStart(Timer_ThreeHandle, 0);
	TimerStartRetVal = xTimerStart(Timer_FourHandle, 0);
	TimerStartRetVal = xTimerStart(Timer_FiveHandle, 0);
	TimerStartRetVal = xTimerStart(Timer_SixHandle, 0);
	
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END TaskOne */
}

/* MyTimerOne_Callback function */
unsigned short MyTimerOne_CallbackVar = 0;
void MyTimerOne_Callback(void *argument)
{
  /* USER CODE BEGIN MyTimerOne_Callback */
   MyTimerOne_CallbackVar ^= (1<<0);
  /* USER CODE END MyTimerOne_Callback */
}

/* MyTimerTwo_Callback function */
unsigned short MyTimerTwo_CallbackVar = 0;
void MyTimerTwo_Callback(void *argument)
{
  /* USER CODE BEGIN MyTimerTwo_Callback */
   MyTimerTwo_CallbackVar ^= (1<<0);
  /* USER CODE END MyTimerTwo_Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* FreeRTOS API */
void MyTimer_Callback(TimerHandle_t xTimer){
	uint32_t ulCount = 0;
	/* The number of times this timer has expired is saved as the
       timer's ID. Obtain the count. */
    ulCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
	
	if(ulCount == 3){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}
	else if(ulCount == 4){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}
	else if(ulCount == 5){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	}
	else if(ulCount == 6){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
