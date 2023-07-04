/* USER CODE BEGIN Header */
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
#define QSPI_BK_IO2_Pin GPIO_PIN_2
#define QSPI_BK_IO2_GPIO_Port GPIOE
#define LED_SYS_Pin GPIO_PIN_3
#define LED_SYS_GPIO_Port GPIOE
#define LED_BLUE_Pin GPIO_PIN_4
#define LED_BLUE_GPIO_Port GPIOE
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOC
#define USB_TX_Pin GPIO_PIN_2
#define USB_TX_GPIO_Port GPIOA
#define USB_RX_Pin GPIO_PIN_3
#define USB_RX_GPIO_Port GPIOA
#define DAC_1V65_Pin GPIO_PIN_4
#define DAC_1V65_GPIO_Port GPIOA
#define DAC_SINE_Pin GPIO_PIN_5
#define DAC_SINE_GPIO_Port GPIOA
#define BEEPER_Pin GPIO_PIN_1
#define BEEPER_GPIO_Port GPIOB
#define QSPI_BK_CLK_Pin GPIO_PIN_2
#define QSPI_BK_CLK_GPIO_Port GPIOB
#define LCD_BLK_Pin GPIO_PIN_10
#define LCD_BLK_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
#define LCD_SCK_Pin GPIO_PIN_12
#define LCD_SCK_GPIO_Port GPIOE
#define LCD_DC_Pin GPIO_PIN_13
#define LCD_DC_GPIO_Port GPIOE
#define LCD_SDA_Pin GPIO_PIN_14
#define LCD_SDA_GPIO_Port GPIOE
#define IPORT_TX_Pin GPIO_PIN_14
#define IPORT_TX_GPIO_Port GPIOB
#define IPORT_RX_Pin GPIO_PIN_15
#define IPORT_RX_GPIO_Port GPIOB
#define IPORT_RST_Pin GPIO_PIN_8
#define IPORT_RST_GPIO_Port GPIOD
#define IPORT_FUN_Pin GPIO_PIN_9
#define IPORT_FUN_GPIO_Port GPIOD
#define IPORT_CFG_Pin GPIO_PIN_10
#define IPORT_CFG_GPIO_Port GPIOD
#define QSPI_BK_IO0_Pin GPIO_PIN_11
#define QSPI_BK_IO0_GPIO_Port GPIOD
#define QSPI_BK_IO1_Pin GPIO_PIN_12
#define QSPI_BK_IO1_GPIO_Port GPIOD
#define QSPI_BK_IO3_Pin GPIO_PIN_13
#define QSPI_BK_IO3_GPIO_Port GPIOD
#define RELAY1_Pin GPIO_PIN_14
#define RELAY1_GPIO_Port GPIOD
#define RELAY2_Pin GPIO_PIN_15
#define RELAY2_GPIO_Port GPIOD
#define RELAY3_Pin GPIO_PIN_6
#define RELAY3_GPIO_Port GPIOC
#define RELAY4_Pin GPIO_PIN_7
#define RELAY4_GPIO_Port GPIOC
#define SD_D0_Pin GPIO_PIN_8
#define SD_D0_GPIO_Port GPIOC
#define SD_D1_Pin GPIO_PIN_9
#define SD_D1_GPIO_Port GPIOC
#define RELAY5_Pin GPIO_PIN_8
#define RELAY5_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DN_Pin GPIO_PIN_11
#define USB_DN_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SD_D2_Pin GPIO_PIN_10
#define SD_D2_GPIO_Port GPIOC
#define SD_D3_Pin GPIO_PIN_11
#define SD_D3_GPIO_Port GPIOC
#define SD_CK_Pin GPIO_PIN_12
#define SD_CK_GPIO_Port GPIOC
#define VCP_RX_Pin GPIO_PIN_0
#define VCP_RX_GPIO_Port GPIOD
#define VCP_TX_Pin GPIO_PIN_1
#define VCP_TX_GPIO_Port GPIOD
#define SD_CMD_Pin GPIO_PIN_2
#define SD_CMD_GPIO_Port GPIOD
#define SD_SW_Pin GPIO_PIN_4
#define SD_SW_GPIO_Port GPIOD
#define PGA_CS2_Pin GPIO_PIN_6
#define PGA_CS2_GPIO_Port GPIOD
#define PGA_CS1_Pin GPIO_PIN_7
#define PGA_CS1_GPIO_Port GPIOD
#define PGA_SCK_Pin GPIO_PIN_3
#define PGA_SCK_GPIO_Port GPIOB
#define PGA_MISO_Pin GPIO_PIN_4
#define PGA_MISO_GPIO_Port GPIOB
#define PGA_MOSI_Pin GPIO_PIN_5
#define PGA_MOSI_GPIO_Port GPIOB
#define QSPI_BK_NCS_Pin GPIO_PIN_6
#define QSPI_BK_NCS_GPIO_Port GPIOB
#define SW4_Pin GPIO_PIN_8
#define SW4_GPIO_Port GPIOB
#define SW3_Pin GPIO_PIN_9
#define SW3_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_0
#define SW2_GPIO_Port GPIOE
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
