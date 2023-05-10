/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2023-01-13 08:31:31
 * @LastEditTime : 2023-01-14 15:14:13
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

typedef struct {
    uint16_t Freq;
    uint16_t ShortCircuitCurrent;
    double StandardVoltage;
    double VoltageErrorRange;
    double TestVoltage;
} CoilTest;

typedef struct {
    double DacFreq;
    uint16_t PGA1_Amp;
    uint16_t PGA2_Amp;

} SystemSetting;


void SaveCoilTestResult(uint16_t* ADC1_BasicValue, uint16_t* ADC2_BasicValue);

/**
 * @description    : 采集两路ADC的值（DMA方式TIM4触发）
 * @author         : MaxDYi
 * @return          {*}
 */
void AcquireData(void);

/**
 * @description    : 校准ADC
 * @author         : MaxDYi
 * @return          {*}
 */
void ADC_Calibration(void);

/**
 * @description    : 求内部温度传感器的温度值
 * @author         : MaxDYi
 * @return          {*}
 */
double AcquireTemp(void);

/**
 * @description    : 求相位
 * @author         : MaxDYi
 * @param           {float32_t*} _ptr 复位地址，含实部和虚部
 * @param           {float32_t*} _phase 求出相位，单位角度制，范围(-180, 180]
 * @param           {uint16_t} _usFFTPoints 复数个数，每个复数是两个float32_t数值
 * @param           {float32_t} _uiCmpValue 比较值，需要求出相位的数值
 * @return          {*}
 */
void PowerPhaseRadians_f32(float32_t* _ptr, float32_t* _phase, uint16_t _usFFTPoints, float32_t _uiCmpValue);

/**
 * @description    : 求相位
 * @author         : MaxDYi
 * @param           {float64_t*} _ptr 复位地址，含实部和虚部
 * @param           {float64_t*} _phase 求出相位，单位角度制，范围(-180, 180]
 * @param           {uint16_t} _usFFTPoints 复数个数，每个复数是两个float64_t数值
 * @param           {float64_t} _uiCmpValue 比较值，需要求出相位的数值
 * @return          {*}
 */
void PowerPhaseRadians_f64(float64_t* _ptr, float64_t* _phase, uint16_t _usFFTPoints, float64_t _uiCmpValue);

/**
 * @description    : 调用函数arm_rfft_fast_f32计算幅频和相频
 * @author         : MaxDYi
 * @return          {*}
 */
static void arm_rfft_f32_app(void);

/**
 * @description    : 调用函数arm_rfft_fast_f64计算幅频和相频
 * @author         : MaxDYi
 * @return          {*}
 */

static void arm_rfft_f64_app(void);

#endif
