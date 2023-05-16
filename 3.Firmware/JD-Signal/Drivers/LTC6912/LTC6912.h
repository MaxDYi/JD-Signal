/*
 * @Descripttion:程控放大器LTC6912驱动
 * @Author: MaxDYi
 * @Date: 2023-01-10 18:42:43
 * @LastEditors: MaxDYi 157596643@qq.com
 * @LastEditTime: 2023-05-16 12:15:58
 * @FilePath: \JD-Signal\Drivers\LTC6912\LTC6912.h
 */

#ifndef __LTC6912_H__
#define __LTC6912_H__

#include "main.h"
#include "spi.h"
#include "stdio.h"

#define LTC6912_TYPE1 1
#define LTC6912_TYPE2 2



void LTC6912_SetGain(uint16_t xGain, uint8_t IC_Num);
uint8_t LTC6912_Single_GetReg(uint16_t Gain, uint8_t model);
uint8_t LTC6912_Series_GetReg(uint16_t Gain, uint8_t model);
void LTC6912_SendOneByte(uint8_t data);

#endif