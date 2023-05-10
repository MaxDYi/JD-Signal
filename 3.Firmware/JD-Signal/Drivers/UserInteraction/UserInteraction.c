#include "UserInteraction.h"

void LED_Init(void)
{
    HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
}

void Relay_Init(void)
{
    Relay_Off(1);
    Relay_Off(2);
    Relay_Off(3);
    Relay_Off(4);
    Relay_Off(5);
}

void Relay_On(uint8_t num)
{
    switch (num)
    {
    case (1):
    {
        HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_RESET);
        break;
    }
    case (2):
    {
        HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_RESET);
        break;
    }
    case (3):
    {
        HAL_GPIO_WritePin(Relay3_GPIO_Port, Relay3_Pin, GPIO_PIN_RESET);
        break;
    }
    case (4):
    {
        HAL_GPIO_WritePin(Relay4_GPIO_Port, Relay4_Pin, GPIO_PIN_RESET);
        break;
    }
    case (5):
    {
        HAL_GPIO_WritePin(Relay5_GPIO_Port, Relay5_Pin, GPIO_PIN_RESET);
        break;
    }
    default:
        break;
    }
}

void Relay_Off(uint8_t num)
{
    switch (num)
    {
    case (1):
    {
        HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_SET);
        break;
    }
    case (2):
    {
        HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_SET);
        break;
    }
    case (3):
    {
        HAL_GPIO_WritePin(Relay3_GPIO_Port, Relay3_Pin, GPIO_PIN_SET);
        break;
    }
    case (4):
    {
        HAL_GPIO_WritePin(Relay4_GPIO_Port, Relay4_Pin, GPIO_PIN_SET);
        break;
    }
    case (5):
    {
        HAL_GPIO_WritePin(Relay5_GPIO_Port, Relay5_Pin, GPIO_PIN_SET);
        break;
    }
    default:
        break;
    }
}

void Beeper_Init(void)
{
}

uint8_t getOneSwitchValue(uint8_t num)
{
    uint8_t SW = 0;
    switch (num)
    {
    case 1:
    {
        if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == GPIO_PIN_RESET)
        {
            SW = 0;
        }
        else
        {
            SW = 1;
        }
        break;
    }
    case 2:
    {
        if (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == GPIO_PIN_RESET)
        {
            SW = 0;
        }
        else
        {
            SW = 1;
        }
        break;
    }
    case 3:
    {
        if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET)
        {
            SW = 0;
        }
        else
        {
            SW = 1;
        }
        break;
    }
    case 4:
    {
        if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_RESET)
        {
            SW = 0;
        }
        else
        {
            SW = 1;
        }
        break;
    }
    default:
    {
        SW = 2;
        break;
    }
    }
    return SW;
}

uint8_t getAllSwitchValue(void)
{
    uint8_t SW_SUM = 0;
    for (int i = 0; i < 4; i++)
    {
        uint8_t SW = getOneSwitchValue(i + 1);
        if (SW < 2)
        {

            SW_SUM = SW_SUM + (SW << i);
        }
        else
        {
            return 0x80;
        }
    }
    return SW_SUM;
}

void BeeperEn(uint8_t flag)
{
    if (flag == 0)
    {
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
    }
    else
    {
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    }
}