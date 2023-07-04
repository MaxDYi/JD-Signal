/*
 * @Description:
 * @Author: MaxDYi
 * @Date: 2023-04-29 18:16:52
 * @LastEditors: MaxDYi
 * @LastEditTime: 2023-07-04 14:37:13
 * @FilePath: \JD-Signal\Drivers\BodeSetting\BodeSetting.c
 */
#include "BodeSetting.h"

#define SINE_DAC_PORT hdac1
#define SINE_DAC_CHANNEL DAC_CHANNEL_2
#define SINE_DAC_TRIGGER_TIM htim6
#define SINE_TIM_CLK 240000000
#define SINE_TIM_PRESCALER 2
#define SINE_DAC_COUNT 1024

#define VREF_DAC_PORT hdac1
#define VREF_DAC_CHANNEL DAC_CHANNEL_1

#pragma location = ".RAM_D1"
uint16_t DualSine12bit[SINE_DAC_COUNT];

/**
 * @description: 正弦波初始化函数
 * @author: MaxDYi
 * @param {double} freq
 * @param {uint8_t} Amp
 * @return {*}
 */
void Sine_Init(double freq, uint8_t Amp)
{
    for (int i = 0; i < SINE_DAC_COUNT; i++)
    {
        DualSine12bit[i] = Sine_GetData(12, SINE_DAC_COUNT, i, Amp);
    }
    HAL_TIM_Base_Start(&SINE_DAC_TRIGGER_TIM);
    Sine_SetFreq(freq);
}

/**
 * @description: 正弦波输出使能函数
 * @author: MaxDYi
 * @param {uint8_t} flag
 * @return {*}
 */
void Sine_OutputEn(uint8_t flag)
{
    if (flag == 0)
    {
        HAL_TIM_Base_Stop(&SINE_DAC_TRIGGER_TIM);
        HAL_DAC_Stop_DMA(&SINE_DAC_PORT, SINE_DAC_CHANNEL);
    }
    else
    {
        HAL_TIM_Base_Start(&SINE_DAC_TRIGGER_TIM);
        HAL_DAC_Start_DMA(&SINE_DAC_PORT, SINE_DAC_CHANNEL, (uint32_t *)DualSine12bit, SINE_DAC_COUNT, DAC_ALIGN_12B_R);
    }
}

/**
 * @description: 生成正弦波形数据
 * @author: MaxDYi
 * @param {uint8_t} dataWidth
 * @param {uint16_t} dataLength
 * @param {uint16_t} dataCount
 * @param {uint8_t} Amp
 * @return {*}
 */
uint16_t Sine_GetData(uint8_t dataWidth, uint16_t dataLength, uint16_t dataCount, uint8_t Amp)
{
    uint32_t maxValue = 1;
    maxValue = (maxValue << dataWidth) - 1;
    double data = (sin((double)dataCount / dataLength * 2 * PI) + 1) / 2 * maxValue * (Amp / 100.0);
    return (uint16_t)data;
}

/**
 * @description: 正弦波频率设置函数
 * @author: MaxDYi
 * @param {double} freq
 * @return {*}
 */
void Sine_SetFreq(double freq)
{
    Sine_OutputEn(0);
    HAL_TIM_Base_Stop(&SINE_DAC_TRIGGER_TIM);
    double timPeriod_double = (double)SINE_TIM_CLK / SINE_TIM_PRESCALER / SINE_DAC_COUNT / freq;
    uint16_t timPeriod = (uint16_t)(timPeriod_double + 0.5) - 1;
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    // SINE_DAC_TRIGGER_TIM.Instance = TIM6;
    SINE_DAC_TRIGGER_TIM.Init.Prescaler = SINE_TIM_PRESCALER - 1;
    SINE_DAC_TRIGGER_TIM.Init.CounterMode = TIM_COUNTERMODE_UP;
    SINE_DAC_TRIGGER_TIM.Init.Period = timPeriod;
    SINE_DAC_TRIGGER_TIM.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (HAL_TIM_Base_Init(&SINE_DAC_TRIGGER_TIM) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_Base_Start(&SINE_DAC_TRIGGER_TIM);
}

void Vref_Init(void)
{
    HAL_DAC_Start(&VREF_DAC_PORT, VREF_DAC_CHANNEL);
    HAL_DAC_SetValue(&VREF_DAC_PORT, VREF_DAC_CHANNEL, DAC_ALIGN_12B_R, 2048);
}

void Vref_Set(uint16_t data)
{
    HAL_DAC_SetValue(&VREF_DAC_PORT, VREF_DAC_CHANNEL, DAC_ALIGN_12B_R, data);
}
