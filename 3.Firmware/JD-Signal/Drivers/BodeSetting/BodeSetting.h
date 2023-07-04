/*
 * @Descripttion:
 * @Author: MaxDYi
 * @Date: 2023-01-16 14:00:01
 * @LastEditors: MaxDYi
 * @LastEditTime: 2023-02-04 13:59:00
 * @FilePath: \JD-Signal\Drivers\BodeSetting\BodeSetting.h
 */

#ifndef __BODESETTING_H__
#define __BODESETTING_H__

#include "stdio.h"
#include "main.h"
#include "arm_math.h"
#include "tim.h"
#include "dac.h"

void Sine_Init(double freq, uint8_t Amp);

void Sine_OutputEn(uint8_t flag);

uint16_t Sine_GetData(uint8_t dataWidth, uint16_t dataLength, uint16_t dataCount, uint8_t Amp);

void Sine_SetFreq(double freq);

void Vref_Init(void);

void Vref_Set(uint16_t data);

#endif