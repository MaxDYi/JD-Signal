#include "BodeSetting.h"

#define SINE_DAC hdac1
#define SINE_DAC_CHANNEL DAC_CHANNEL_1
#define SINE_DAC_TRIGGER_TIM htim6
#define SINE_TIM_CLK 240000000
#define SINE_TIM_PRESCALER 2
#define SINE_DAC_COUNT 1024

#pragma location = ".RAM_D1"
uint16_t DualSine12bit[SINE_DAC_COUNT];


void Sine_Init(double freq, uint8_t Amp) {
    for (int i = 0; i < SINE_DAC_COUNT; i++)
    {
        DualSine12bit[i] = Sine_GetData(12, SINE_DAC_COUNT, i, Amp);
    }
    HAL_TIM_Base_Start(&SINE_DAC_TRIGGER_TIM);
    Sine_SetFreq(freq);
}

void Sine_OutputEn(uint8_t flag) {
    if (flag == 0) {
        HAL_TIM_Base_Stop(&SINE_DAC_TRIGGER_TIM);
        HAL_DAC_Stop_DMA(&SINE_DAC, DAC_CHANNEL_1);
    }
    else {
        HAL_TIM_Base_Start(&SINE_DAC_TRIGGER_TIM);
        HAL_DAC_Start_DMA(&SINE_DAC, DAC_CHANNEL_1, (uint32_t*)DualSine12bit, SINE_DAC_COUNT, DAC_ALIGN_12B_R);
    }
}

uint16_t Sine_GetData(uint8_t dataWidth, uint16_t dataLength, uint16_t dataCount, uint8_t Amp) {
    uint32_t maxValue = 1;
    maxValue = (maxValue << dataWidth) - 1;
    double data = (sin((double)dataCount / dataLength * 2 * PI) + 1) / 2 * maxValue;
    return (uint16_t)data;
}

void Sine_SetFreq(double freq) {
    Sine_OutputEn(0);
    HAL_TIM_Base_Stop(&SINE_DAC_TRIGGER_TIM);
    double timPeriod_double = (double)SINE_TIM_CLK / SINE_TIM_PRESCALER / SINE_DAC_COUNT / freq;
    uint16_t timPeriod = (uint16_t)(timPeriod_double + 0.5) - 1;
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    //SINE_DAC_TRIGGER_TIM.Instance = TIM6;
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
