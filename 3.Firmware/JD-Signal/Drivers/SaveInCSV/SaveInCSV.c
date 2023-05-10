/*
 * @Descripttion:SD卡保存文件驱动
 * @Author: MaxDYi
 * @Date: 2023-01-16 13:59:59
 * @LastEditors: MaxDYi
 * @LastEditTime: 2023-02-04 15:49:44
 * @FilePath: \JD-Signal\Drivers\SaveInCSV\SaveInCSV.c
 */

#include "SaveInCSV.h"

#pragma location = ".RAM_D1"
FATFS fs; /* FatFs文件系统对象 */
#pragma location = ".RAM_D1"
DIR dir; /* 目录对象 */
#pragma location = ".RAM_D1"
FIL file; /* 文件对象 */
#pragma location = ".RAM_D1"
FRESULT f_res; /* 文件操作结果 */
#pragma location = ".RAM_D1"
UINT fnum; /* 文件成功读写数量 */

#pragma location = ".RAM_D1"
char ReadBuffer[1024]; /* 读缓冲区 */
#pragma location = ".RAM_D1"
char WriteBuffer[1024]; /* 写缓冲区 */

char TimeStamp[32]; // 用于保存时间戳

/**
 * @description: SD卡格式化
 * @author: MaxDYi
 * @return {*}
 */
uint8_t FATFS_Format(void)
{
    f_res = f_mkfs("0:", FM_EXFAT, 2048, WriteBuffer, 2048); // 格式化为exFAT格式
    FATFS_PrintFileCode(f_res);
    if (f_res == FR_OK)
    {
        printf("The SD card successfully formatted the file system\r\n");
        /* 格式化后，先取消挂载 */
        f_res = f_mount(NULL, "0:", 1);
        /* 重新挂载 */
        f_res = f_mount(&fs, "0:", 1);
        return 1;
    }
    else
    {
        printf("The format failed\r\n");
        return 0;
    }
}

/**
 * @description: 记录时间戳
 * @author: MaxDYi
 * @return {*}
 */
void FATFS_RecordTimeStamp(void)
{
    RTC_DateTypeDef RTC_Date;
    RTC_TimeTypeDef RTC_Time;
    HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BIN);
    sprintf(TimeStamp, "%04d-%02d-%02d_%02d-%02d-%02d",
        RTC_Date.Year + 1970, RTC_Date.Month, RTC_Date.Date,
        RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}

/**
 * @description: 保存ADC采样原始数据
 * @author: MaxDYi
 * @param {uint16_t} ADC_Count
 * @param {uint16_t} PGA1_Amp
 * @param {uint16_t} PGA2_Amp
 * @param {uint16_t*} ADC1_BasicValue
 * @param {uint16_t*} ADC2_BasicValue
 * @return {*}
 */
uint8_t FATFS_SaveBasicData(uint16_t ADC_Count, uint16_t PGA1_Amp, uint16_t PGA2_Amp, uint16_t* ADC1_BasicValue, uint16_t* ADC2_BasicValue)
{
    char FileName[255];
    sprintf(FileName, "BasicData_%s.csv", TimeStamp);
    char FolderPath[255];
    sprintf(FolderPath, "0:/%s", TimeStamp);
    char FilePath[255];
    sprintf(FilePath, "%s/%s", FolderPath, FileName);

    f_res = f_mount(&fs, "0:", 1);
    if (f_res != FR_OK)
    {
        return f_res;
    }
    if (f_opendir(&dir, FolderPath) == FR_NO_PATH)
    {
        f_mkdir(FolderPath);
        f_res = f_opendir(&dir, FolderPath);
        if (f_res != FR_OK)
        {
            return f_res;
        }
    }
    f_res = f_open(&file, FilePath, FA_CREATE_ALWAYS | FA_WRITE);
    FATFS_WriteBasicData(ADC_Count, PGA1_Amp, PGA2_Amp, ADC1_BasicValue, ADC2_BasicValue);
    f_close(&file);
    return FR_OK;
}

/**
 * @description: 保存计算结果
 * @author: MaxDYi
 * @param {uint16_t} CoilTestCount
 * @param {uint16_t} Freq
 * @param {uint16_t} ShortCircuitCurrent
 * @param {double} StandardVoltage
 * @param {double} VoltageErrorRange
 * @param {double} TestVoltage
 * @return {*}
 */
uint8_t FATFS_SaveResult(uint16_t CoilTestCount, uint16_t Freq, uint16_t ShortCircuitCurrent, double StandardVoltage, double VoltageErrorRange, double TestVoltage)
{
    char FileName[255];
    sprintf(FileName, "Result_%s.csv", TimeStamp);
    char FolderPath[255];
    sprintf(FolderPath, "0:/%s", TimeStamp);
    char FilePath[255];
    sprintf(FilePath, "%s/%s", FolderPath, FileName);

    f_res = f_mount(&fs, "0:", 1);
    FATFS_PrintFileCode(f_res);
    if (f_res != FR_OK)
    {
        return f_res;
    }
    if (f_opendir(&dir, FolderPath) == FR_NO_PATH)
    {
        f_mkdir(FolderPath);
        f_res = f_opendir(&dir, FolderPath);
        if (f_res != FR_OK)
        {
            return f_res;
        }
    }

    f_res = f_open(&file, FilePath, FA_CREATE_ALWAYS | FA_WRITE);
    FATFS_WriteResult(CoilTestCount, Freq, ShortCircuitCurrent,
        StandardVoltage, VoltageErrorRange, TestVoltage);
    f_close(&file);
    return FR_OK;
}

/**
 * @description: 写入ADC采样原始数据
 * @author: MaxDYi
 * @param {uint16_t} ADC_Count
 * @param {uint16_t} PGA1_Amp
 * @param {uint16_t} PGA2_Amp
 * @param {uint16_t*} ADC1_BasicValue
 * @param {uint16_t*} ADC2_BasicValue
 * @return {*}
 */
void FATFS_WriteBasicData(uint16_t ADC_Count, uint16_t PGA1_Amp, uint16_t PGA2_Amp, uint16_t* ADC1_BasicValue, uint16_t* ADC2_BasicValue)
{
    sprintf(WriteBuffer, "Test Time,%s\r\n\r\n", TimeStamp);
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);

    sprintf(WriteBuffer, "PGA1 Amplifier multiple,%d\r\n", PGA1_Amp);
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);
    sprintf(WriteBuffer, "PGA2 Amplifier multiple,%d\r\n", PGA2_Amp);
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);

    sprintf(WriteBuffer, "\r\nADC Basic Value\r\n");
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);

    sprintf(WriteBuffer, "ADC1,ADC2\r\n");
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);

    for (int i = 0; i < ADC_Count; i++)
    {
        sprintf(WriteBuffer, "%d,%d\r\n", ADC1_BasicValue[i], ADC2_BasicValue[i]);
        f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);
    }
}

/**
 * @description: 写入计算结果
 * @author: MaxDYi
 * @param {uint16_t} CoilTestCount
 * @param {uint16_t} Freq
 * @param {uint16_t} ShortCircuitCurrent
 * @param {double} StandardVoltage
 * @param {double} VoltageErrorRange
 * @param {double} TestVoltage
 * @return {*}
 */
void FATFS_WriteResult(uint16_t CoilTestCount, uint16_t Freq, uint16_t ShortCircuitCurrent, double StandardVoltage, double VoltageErrorRange, double TestVoltage)
{
    sprintf(WriteBuffer, "Test Time,%s\r\n\r\n", TimeStamp);
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);

    sprintf(WriteBuffer, "Test Frequency,Short-Circuit Current,Standard Voltage,Error Range,Test Voltage\r\n");
    f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);
    for (int i = 0; i < CoilTestCount; i++)
    {
        sprintf(WriteBuffer, "%d,%d,%f,%f,%f\r\n", Freq,
            ShortCircuitCurrent, StandardVoltage,
            VoltageErrorRange, TestVoltage);
        f_res = f_write(&file, WriteBuffer, strlen(WriteBuffer), &fnum);
    }
}

/**
 * @description: 输出FatFS状态码
 * @author: MaxDYi
 * @param {uint8_t} Code
 * @return {*}
 */
void FATFS_PrintFileCode(uint8_t Code)
{
    if (Code == 0)
    {
        printf("FatFS Succeeded\r\n");
    }
    else
    {
        printf("FatFS Error Code(%02d)\r\n", Code);
        switch (Code)
        {
        case ( 1 ):
        {
            printf("FR_DISK_ERR: A hard error occurred in the low level disk I/O layer\r\n");
            break;
        }
        case ( 2 ):
        {
            printf("FR_INT_ERR: Assertion failed\r\n");
            break;
        }
        case ( 3 ):
        {
            printf("FR_NOT_READY: The physical drive cannot work\r\n");
            break;
        }
        case ( 4 ):
        {
            printf("FR_NO_FILE: Could not find the file\r\n");
            break;
        }
        case ( 5 ):
        {
            printf("FR_NO_PATH: Could not find the path\r\n");
            break;
        }
        case ( 6 ):
        {
            printf("FR_INVALID_NAME: The path name format is invalid\r\n");
            break;
        }
        case ( 7 ):
        {
            printf("FR_DENIED: Access denied due to prohibited access or directory full\r\n");
            break;
        }
        case ( 8 ):
        {
            printf("FR_EXIST: Access denied due to prohibited access\r\n");
            break;
        }
        case ( 9 ):
        {
            printf("FR_INVALID_OBJECT: The file/directory object is invalid\r\n");
            break;
        }
        case ( 10 ):
        {
            printf("FR_WRITE_PROTECTED: The physical drive is write protected\r\n");
            break;
        }
        case ( 11 ):
        {
            printf("FR_INVALID_DRIVE: The logical drive number is invalid\r\n");
            break;
        }
        case ( 12 ):
        {
            printf("FR_NOT_ENABLED: The volume has no work area\r\n");
            break;
        }
        case ( 13 ):
        {
            printf("FR_NO_FILESYSTEM: There is no valid FAT volume\r\n");
            break;
        }
        case ( 14 ):
        {
            printf("FR_MKFS_ABORTED: The f_mkfs() aborted due to any problem\r\n");
            break;
        }
        case ( 15 ):
        {
            printf("FR_TIMEOUT: Could not get a grant to access the volume within defined period\r\n");
            break;
        }
        case ( 16 ):
        {
            printf("FR_LOCKED: The operation is rejected according to the file sharing policy\r\n");
            break;
        }
        case ( 17 ):
        {
            printf("FR_NOT_ENOUGH_CORE: LFN working buffer could not be allocated\r\n");
            break;
        }
        case ( 18 ):
        {
            printf("FR_TOO_MANY_OPEN_FILES: Number of open files > _FS_LOCK\r\n");
            break;
        }
        case ( 19 ):
        {
            printf("FR_INVALID_PARAMETER: Given parameter is invalid\r\n");
            break;
        }
        default:
            break;
        }
    }
}
