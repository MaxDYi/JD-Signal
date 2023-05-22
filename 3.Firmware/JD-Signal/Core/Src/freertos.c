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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "math.h"
#include "main.h"
#include "LCD.h"
#include "stdlib.h"
#include "rtc.h"
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
osThreadId default_TaskHandle;
osThreadId sysLED_TaskHandle;
osThreadId sysTime_TaskHandle;
osThreadId cJSON_TaskHandle;
osMessageQId UART_QueueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Default_Task(void const *argument);
void SysLED_Task(void const *argument);
void SysTime_Task(void const *argument);
void CJSON_Task(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
}

__weak unsigned long getRunTimeCounterValue(void)
{
    return 0;
}
/* USER CODE END 1 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
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
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* definition and creation of UART_Queue */
    osMessageQDef(UART_Queue, 128, uint8_t);
    UART_QueueHandle = osMessageCreate(osMessageQ(UART_Queue), NULL);

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* definition and creation of default_Task */
    osThreadDef(default_Task, Default_Task, osPriorityNormal, 0, 128);
    default_TaskHandle = osThreadCreate(osThread(default_Task), NULL);

    /* definition and creation of sysLED_Task */
    osThreadDef(sysLED_Task, SysLED_Task, osPriorityLow, 0, 128);
    sysLED_TaskHandle = osThreadCreate(osThread(sysLED_Task), NULL);

    /* definition and creation of sysTime_Task */
    osThreadDef(sysTime_Task, SysTime_Task, osPriorityLow, 0, 128);
    sysTime_TaskHandle = osThreadCreate(osThread(sysTime_Task), NULL);

    /* definition and creation of cJSON_Task */
    osThreadDef(cJSON_Task, CJSON_Task, osPriorityLow, 0, 128);
    cJSON_TaskHandle = osThreadCreate(osThread(cJSON_Task), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_Default_Task */
/**
 * @brief  Function implementing the default_Task thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Default_Task */
void Default_Task(void const *argument)
{
    /* USER CODE BEGIN Default_Task */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1000);
    }
    /* USER CODE END Default_Task */
}

/* USER CODE BEGIN Header_SysLED_Task */
/**
 * @brief Function implementing the sysLED_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SysLED_Task */
void SysLED_Task(void const *argument)
{
    /* USER CODE BEGIN SysLED_Task */
    /* Infinite loop */
    for (;;)
    {
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
        osDelay(500);
    }
    /* USER CODE END SysLED_Task */
}

/* USER CODE BEGIN Header_SysTime_Task */
/**
 * @brief Function implementing the sysTime_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SysTime_Task */
void SysTime_Task(void const *argument)
{
    /* USER CODE BEGIN SysTime_Task */
    /* Infinite loop */
    for (;;)
    {
        RTC_DateTypeDef RTC_Date;
        RTC_TimeTypeDef RTC_Time;
        HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BIN);
        char TimeStamp[32];
        sprintf(TimeStamp, "%04d-%02d-%02d %02d:%02d:%02d",
                RTC_Date.Year + 1970, RTC_Date.Month, RTC_Date.Date,
                RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
        LCD_ShowString(30, 60, (uint8_t const *)TimeStamp, WHITE, BLACK, 24, 0);
        osDelay(500);
    }

    /* USER CODE END SysTime_Task */
}

/* USER CODE BEGIN Header_CJSON_Task */
/**
 * @brief Function implementing the cJSON_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_CJSON_Task */
void CJSON_Task(void const *argument)
{
    /* USER CODE BEGIN CJSON_Task */
    BaseType_t xReturn;
    uint32_t r_quque;
    /* Infinite loop */
    for (;;)
    {
        xReturn = xQueueReceive(UART_QueueHandle, &r_quque, portMAX_DELAY);
        if (xReturn == pdTRUE)
        {
            printf("%d\r\n", r_quque);
        }
        else
        {
            printf("error");
        }
        osDelay(1);
    }
    /* USER CODE END CJSON_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
