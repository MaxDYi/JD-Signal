/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2023-01-13 08:31:31
 * @LastEditTime: 2023-06-16 16:47:38
 * @FilePath     : \JD-Signal\Drivers\Algorithm\Algorithm.h
 */

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "math.h"
#include "arm_math.h"
#include "SaveInCSV.h"

#define COIL_TEST_COUNT 9

#define ADC_COUNT 1024

typedef struct
{
    uint16_t Freq;
    uint16_t ShortCircuitCurrent;
    double StandardVoltage;
    double VoltageErrorRange;
    double TestVoltage;
} CoilTest;

typedef struct
{
    double DacFreq;
    uint16_t PGA1_Amp;
    uint16_t PGA2_Amp;

} SystemSetting;

void SaveCoilTestResult(uint16_t *ADC1_BasicValue, uint16_t *ADC2_BasicValue);

/**
 * @description    : 求内部温度传感器的温度值
 * @author         : MaxDYi
 * @return          {*}
 */
double AcquireTemp(void);

#endif
