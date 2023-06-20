/*
 * @Author: MaxDYi 157596643@qq.com
 * @Date: 2023-04-29 18:16:52
 * @LastEditors: MaxDYi 157596643@qq.com
 * @LastEditTime: 2023-06-20 17:23:12
 * @FilePath: \JD-Signal\Drivers\LCD\ST7789.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ST7789_H__
#define __ST7789_H__

#include "main.h"
#include "spi.h"

#define SPI_ST7789 hspi3

#define USE_HORIZONTAL 2 // 设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#define LCD_W 320
#define LCD_H 240

//-----------------LCD端口定义----------------

#define LCD_RES_Clr() HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET)
#define LCD_RES_Set() HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_DC_Set() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)

#define LCD_CS_Clr() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_Set() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_RESET)
#define LCD_BLK_Set() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET)

void LCD_Writ_Bus(uint8_t dat);                                           // 模拟SPI时序
void LCD_WR_DATA8(uint8_t dat);                                           // 写入一个字节
void LCD_WR_DATA(uint16_t dat);                                           // 写入两个字节
void LCD_WR_REG(uint8_t dat);                                             // 写入一个指令
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // 设置坐标函数
void LCD_Init(void);                                                      // LCD初始化

#endif
