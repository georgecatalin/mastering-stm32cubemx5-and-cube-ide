/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"

extern UART_HandleTypeDef huart3;

typedef uint32_t ThreadProfiler;

ThreadProfiler thread_profiler_1=0;
ThreadProfiler thread_profiler_2=0;
ThreadProfiler thread_profiler_3=0;
ThreadProfiler thread_profiler_start_default=0;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId firstThreadHandle;
osThreadId secondThreadHandle;
//TODO
osThreadId thirdThreadHandle;
osMutexId uartMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void first_thread_function(void const * argument);
void second_thread_function(void const * argument);
//TODO
void third_thread_function(void const * argument);

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
  /* definition and creation of uartMutex */
  osMutexDef(uartMutex);
  uartMutexHandle = osMutexCreate(osMutex(uartMutex));

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of firstThread */
  osThreadDef(firstThread, first_thread_function, osPriorityNormal, 0, 128);
  firstThreadHandle = osThreadCreate(osThread(firstThread), NULL);

  /* definition and creation of secondThread */
  osThreadDef(secondThread, second_thread_function, osPriorityNormal, 0, 128);
  secondThreadHandle = osThreadCreate(osThread(secondThread), NULL);

  //TODO
  /* definition and creation of secondThread */
  osThreadDef(thirdThread, third_thread_function, osPriorityNormal, 0, 128);
  thirdThreadHandle = osThreadCreate(osThread(thirdThread), NULL);


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
	thread_profiler_start_default++;
    //osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_first_thread_function */
/**
* @brief Function implementing the firstThread thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_first_thread_function */
void first_thread_function(void const * argument)
{
  /* USER CODE BEGIN first_thread_function */
  /* Infinite loop */

  uint8_t message[50]="Thread 1 says : Ola, Alligator\n\r";

  for(;;)
  {
   //TODO
   xSemaphoreTake(uartMutexHandle,portMAX_DELAY)  ;

   HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
   HAL_UART_Transmit(&huart3, message, 30, 10);

   //TODO
   xSemaphoreGive(uartMutexHandle);

	 //thread_profiler_1++;
    osDelay(10);
  }
  /* USER CODE END first_thread_function */
}

/* USER CODE BEGIN Header_second_thread_function */
/**
* @brief Function implementing the secondThread thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_second_thread_function */
void second_thread_function(void const * argument)
{
  /* USER CODE BEGIN second_thread_function */
  /* Infinite loop */

	uint8_t message[50]="Thread 2 says : Ola, Alligator\n\r";

  for(;;)
  {
	//TODO
	xSemaphoreTake(uartMutexHandle,portMAX_DELAY);

	HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
    HAL_UART_Transmit(&huart3, message, 30, 10);

    //TODO
    xSemaphoreGive(uartMutexHandle);

	//thread_profiler_2++;
    osDelay(10);
  }
  /* USER CODE END second_thread_function */
}

void third_thread_function(void const * argument)
{
	for(;;)
	{
		thread_profiler_3++;

	    osDelay(10);
	}

  /* USER CODE END second_thread_function */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
