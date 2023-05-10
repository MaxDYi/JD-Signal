/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PGA1_CS_Pin GPIO_PIN_3
#define PGA1_CS_GPIO_Port GPIOE
#define PGA2_CS_Pin GPIO_PIN_4
#define PGA2_CS_GPIO_Port GPIOE
#define SD_SW_Pin GPIO_PIN_0
#define SD_SW_GPIO_Port GPIOC
#define Relay5_Pin GPIO_PIN_7
#define Relay5_GPIO_Port GPIOE
#define Relay4_Pin GPIO_PIN_8
#define Relay4_GPIO_Port GPIOE
#define Relay3_Pin GPIO_PIN_9
#define Relay3_GPIO_Port GPIOE
#define Relay2_Pin GPIO_PIN_10
#define Relay2_GPIO_Port GPIOE
#define Relay1_Pin GPIO_PIN_11
#define Relay1_GPIO_Port GPIOE
#define SW1_Pin GPIO_PIN_12
#define SW1_GPIO_Port GPIOE
#define SW2_Pin GPIO_PIN_13
#define SW2_GPIO_Port GPIOE
#define SW3_Pin GPIO_PIN_14
#define SW3_GPIO_Port GPIOE
#define SW4_Pin GPIO_PIN_15
#define SW4_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_12
#define KEY1_GPIO_Port GPIOD
#define KEY1_EXTI_IRQn EXTI15_10_IRQn
#define KEY2_Pin GPIO_PIN_13
#define KEY2_GPIO_Port GPIOD
#define KEY2_EXTI_IRQn EXTI15_10_IRQn
#define LED_BLUE_Pin GPIO_PIN_14
#define LED_BLUE_GPIO_Port GPIOD
#define LED_GREEN_Pin GPIO_PIN_15
#define LED_GREEN_GPIO_Port GPIOD
#define IPORT_CFG_Pin GPIO_PIN_8
#define IPORT_CFG_GPIO_Port GPIOC
#define IPORT_FUN_Pin GPIO_PIN_9
#define IPORT_FUN_GPIO_Port GPIOC
#define IPORT_RST_Pin GPIO_PIN_8
#define IPORT_RST_GPIO_Port GPIOA
#define LCD_BLK_Pin GPIO_PIN_15
#define LCD_BLK_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_0
#define LCD_DC_GPIO_Port GPIOD
#define LCD_RST_Pin GPIO_PIN_1
#define LCD_RST_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
