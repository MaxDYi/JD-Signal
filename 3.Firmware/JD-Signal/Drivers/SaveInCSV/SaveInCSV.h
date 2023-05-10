/*
 * @Descripttion:SD卡保存文件驱动
 * @Author: MaxDYi
 * @Date: 2023-01-16 14:00:01
 * @LastEditors: MaxDYi
 * @LastEditTime: 2023-02-04 15:47:56
 * @FilePath: \JD-Signal\Drivers\SaveInCSV\SaveInCSV.h
 */

#ifndef __SAVEINCSV_H__
#define __SAVEINCSV_H__

#include "main.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "rtc.h"
#include "stdio.h"
#include "string.h"

uint8_t FATFS_Format(void);

void FATFS_RecordTimeStamp(void);

uint8_t FATFS_SaveBasicData(uint16_t ADC_Count, uint16_t PGA1_Amp, uint16_t PGA2_Amp, uint16_t* ADC1_BasicValue, uint16_t* ADC2_BasicValue);

uint8_t FATFS_SaveResult(uint16_t CoilTestCount, uint16_t Freq, uint16_t ShortCircuitCurrent, double StandardVoltage, double VoltageErrorRange, double TestVoltage);

void FATFS_WriteBasicData(uint16_t ADC_Count, uint16_t PGA1_Amp, uint16_t PGA2_Amp, uint16_t* ADC1_BasicValue, uint16_t* ADC2_BasicValue);

void FATFS_WriteResult(uint16_t CoilTestCount, uint16_t Freq, uint16_t ShortCircuitCurrent, double StandardVoltage, double VoltageErrorRange, double TestVoltage);

void FATFS_PrintFileCode(uint8_t Code);

#endif
