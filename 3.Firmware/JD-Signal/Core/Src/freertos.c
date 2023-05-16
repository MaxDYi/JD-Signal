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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for sysLED */
osThreadId_t sysLEDHandle;
const osThreadAttr_t sysLED_attributes = {
  .name = "sysLED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for sysTimeShowTask */
osThreadId_t sysTimeShowTaskHandle;
const osThreadAttr_t sysTimeShowTask_attributes = {
  .name = "sysTimeShowTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartSysLED(void *argument);
void StartSysTimeShowTask(void *argument);

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

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of sysLED */
  sysLEDHandle = osThreadNew(StartSysLED, NULL, &sysLED_attributes);

  /* creation of sysTimeShowTask */
  sysTimeShowTaskHandle = osThreadNew(StartSysTimeShowTask, NULL, &sysTimeShowTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */

    for (;;)
    {
        osDelay(1);
    }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSysLED */
/**
 * @brief Function implementing the sysLED thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSysLED */
void StartSysLED(void *argument)
{
  /* USER CODE BEGIN StartSysLED */
    /* Infinite loop */
    for (;;)
    {
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
        osDelay(500);
    }
  /* USER CODE END StartSysLED */
}

/* USER CODE BEGIN Header_StartSysTimeShowTask */
/**
 * @brief Function implementing the sysTimeShowTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSysTimeShowTask */
void StartSysTimeShowTask(void *argument)
{
  /* USER CODE BEGIN StartSysTimeShowTask */
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
        LCD_ShowString(30, 60, TimeStamp, WHITE, BLACK, 24, 0);
        osDelay(500);
    }
  /* USER CODE END StartSysTimeShowTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

