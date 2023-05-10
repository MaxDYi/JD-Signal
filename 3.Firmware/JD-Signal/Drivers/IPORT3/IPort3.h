/*
 * @Descripttion:周立功串口转以太网模块IPort-3网口驱动
 * @Author: MaxDYi
 * @Date: 2023-02-04 13:17:06
 * @LastEditors: MaxDYi
 * @LastEditTime: 2023-02-04 14:15:28
 * @FilePath: \JD-Signal\Drivers\IPort3\IPort3.h
 */

#ifndef __IPORT3_H__
#define __IPORT3_H__

#include "main.h"
#include "usart.h"
#include "stdio.h"


void IPort3_Init(void);
void IPort3_Rst(void);
void IPort3_AT_NoPara(char* command);
void IPort3_AT_Help(char* command);
void IPort3_AT_Inquiry(char* command);
void IPort3_AT_IntPara(char* command, uint16_t para);
void IPort3_AT_StrPara(char* command, char* para);
void IPort3_CommunicationStatus(void);
void IPort3_SettingStatus(void);

#endif