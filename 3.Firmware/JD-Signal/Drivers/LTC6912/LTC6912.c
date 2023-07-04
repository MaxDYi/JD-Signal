/*
 * @Descripttion:程控放大器LTC6912驱动
 * @Author: MaxDYi
 * @Date: 2023-01-10 18:42:36
 * @LastEditors: MaxDYi 157596643@qq.com
 * @LastEditTime: 2023-05-10 14:09:17
 * @FilePath: \JD-Signal\Drivers\LTC6912\LTC6912.c
 */

#include "LTC6912.h"

#define SPI_PGA hspi4

#define LTC6912_TYPE LTC6912_TYPE1

uint16_t Gain_LTC6912_1_Single[] = {0, 1, 2, 5, 10, 20, 50, 100};
uint8_t Reg_LTC6912_1_Single[] = {0x00, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
uint16_t Gain_LTC6912_2_Single[] = {0, 1, 2, 4, 8, 16, 32, 64};
uint8_t Reg_LTC6912_2_Single[] = {0x00, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

uint16_t Gain_LTC6912_1_Series[] = {0, 1, 2, 4, 5,
                                    10, 20, 25, 40, 50,
                                    100, 200, 250, 500, 1000,
                                    2500, 5000, 10000};
uint8_t Reg_LTC6912_1_Series[] = {0x00, 0x11, 0x12, 0x22, 0x13,
                                  0x23, 0x24, 0x33, 0x25, 0x34,
                                  0x44, 0x27, 0x36, 0x46, 0x47,
                                  0x66, 0x67, 0x77};
uint16_t Gain_LTC6912_2_Series[] = {0, 1, 2, 4, 8,
                                    16, 32, 64, 128, 256,
                                    512, 1024, 2048, 4096};
uint8_t Reg_LTC6912_2_Series[] = {0x00, 0x11, 0x12, 0x22, 0x23,
                                  0x33, 0x34, 0x44, 0x45, 0x55,
                                  0x56, 0x66, 0x67, 0x77};

/**
 * @description: LTC6912增益设置
 * @author: MaxDYi
 * @param {uint16_t} xGain
 * @param {uint8_t} IC_Num
 * @return {*}
 */
void LTC6912_SetGain(uint16_t Gain, uint8_t IC_Num)
{
    uint8_t reg = LTC6912_Series_GetReg(Gain, LTC6912_TYPE);
    switch (IC_Num)
    {
    case 1:
    {
        HAL_GPIO_WritePin(PGA_CS1_GPIO_Port, PGA_CS1_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(PGA_CS1_GPIO_Port, PGA_CS1_Pin, GPIO_PIN_RESET);
        LTC6912_SendOneByte(reg);
        HAL_GPIO_WritePin(PGA_CS1_GPIO_Port, PGA_CS1_Pin, GPIO_PIN_SET);
    }
    case 2:
    {
        HAL_GPIO_WritePin(PGA_CS2_GPIO_Port, PGA_CS2_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(PGA_CS2_GPIO_Port, PGA_CS2_Pin, GPIO_PIN_RESET);
        LTC6912_SendOneByte(reg);
        HAL_GPIO_WritePin(PGA_CS2_GPIO_Port, PGA_CS2_Pin, GPIO_PIN_SET);
    }
    default:
    {
        break;
    }
    }
}

/**
 * @description:LTC6912分开使用获取寄存器配置
 * @author: MaxDYi
 * @param {uint16_t} Gain
 * @param {uint8_t} model
 * @return {*}
 */
uint8_t LTC6912_Single_GetReg(uint16_t Gain, uint8_t model)
{
    uint8_t reg = 0;
    if (model == 1)
    {
        for (int i = 0; i < sizeof(Gain_LTC6912_1_Single); i++)
        {
            if (Gain == Gain_LTC6912_1_Single[i])
            {
                reg = Reg_LTC6912_1_Single[i];
            }
        }
    }
    else if (model == 2)
    {
        for (int i = 0; i < sizeof(Gain_LTC6912_2_Single); i++)
        {
            if (Gain == Gain_LTC6912_2_Single[i])
            {
                reg = Reg_LTC6912_2_Single[i];
            }
        }
    }
    return reg;
}

/**
 * @description:LTC6912串联使用获取寄存器配置
 * @author: MaxDYi
 * @param {uint16_t} Gain
 * @param {uint8_t} model
 * @return {*}
 */
uint8_t LTC6912_Series_GetReg(uint16_t Gain, uint8_t model)
{
    uint8_t reg = 0;
    if (model == 1)
    {
        for (int i = 0; i < sizeof(Gain_LTC6912_1_Series); i++)
        {
            if (Gain == Gain_LTC6912_1_Series[i])
            {
                reg = Reg_LTC6912_1_Series[i];
            }
        }
    }
    else if (model == 2)
    {
        for (int i = 0; i < sizeof(Gain_LTC6912_2_Series); i++)
        {
            if (Gain == Gain_LTC6912_2_Series[i])
            {
                reg = Reg_LTC6912_2_Series[i];
            }
        }
    }
    return reg;
}

/**
 * @description: SPI发送LTC6912控制数据
 * @author: MaxDYi
 * @param {uint8_t} data
 * @return {*}
 */
void LTC6912_SendOneByte(uint8_t data)
{
    HAL_SPI_Transmit(&SPI_PGA, &data, 1, 0xff);
}