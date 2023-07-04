/*
 * @Descripttion:周立功串口转以太网模块IPort-3网口驱动
 * @Author: MaxDYi
 * @Date: 2023-02-04 13:17:01
 * @LastEditors: MaxDYi
 * @LastEditTime: 2023-02-04 14:17:45
 * @FilePath: \JD-Signal\Drivers\IPort3\IPort3.c
 */

#include "IPort3.h"

#define IPORT_UART huart1

#define IPORT_PASSWORD "88888"

#pragma location = ".RAM_D1"
char IPortReadBuffer[128]; /* 读缓冲区 */
#pragma location = ".RAM_D1"
char IPortWriteBuffer[128]; /* 读缓冲区 */

/**
 * @description: IPort-3初始化
 * @author: MaxDYi
 * @return {*}
 */
void IPort3_Init(void) {
    HAL_Delay(2000);
    IPort3_SettingStatus();
    HAL_Delay(200);

    IPort3_AT_StrPara("MODE", "0");
    IPort3_AT_StrPara("LOGIN", IPORT_PASSWORD);

    IPort3_Rst();
    IPort3_CommunicationStatus();
}

/**
 * @description: IPort-3复位
 * @author: MaxDYi
 * @return {*}
 */
void IPort3_Rst(void) {
    HAL_GPIO_WritePin(IPORT_RST_GPIO_Port, IPORT_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(IPORT_RST_GPIO_Port, IPORT_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(IPORT_RST_GPIO_Port, IPORT_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}
/**
 * @description: IPort-3无参数命令
 * @author: MaxDYi
 * @param {char*} command
 * @return {*}
 */
void IPort3_AT_NoPara(char* command) {
    sprintf(IPortWriteBuffer, "AT+%s\r\n", command);
    HAL_UART_Transmit(&IPORT_UART, (uint8_t*)IPortWriteBuffer, sizeof(IPortWriteBuffer), 0xFFFF);
}
/**
 * @description:IPort-3帮助命令
 * @author: MaxDYi
 * @param {char*} command
 * @return {*}
 */
void IPort3_AT_Help(char* command) {
    sprintf(IPortWriteBuffer, "AT+%s=?\r\n", command);
    HAL_UART_Transmit(&IPORT_UART, (uint8_t*)IPortWriteBuffer, sizeof(IPortWriteBuffer), 0xFFFF);
}

/**
 * @description:IPort-3查询命令
 * @author: MaxDYi
 * @param {char*} command
 * @return {*}
 */
void IPort3_AT_Inquiry(char* command) {
    sprintf(IPortWriteBuffer, "AT+%s?\r\n", command);
    HAL_UART_Transmit(&IPORT_UART, (uint8_t*)IPortWriteBuffer, sizeof(IPortWriteBuffer), 0xFFFF);
}

/**
 * @description:IPort-3带整形参数命令
 * @author: MaxDYi
 * @param {char*} command
 * @param {char*} para
 * @return {*}
 */
void IPort3_AT_IntPara(char* command, uint16_t para) {
    sprintf(IPortWriteBuffer, "AT+%s=%d\r\n", command, para);
    HAL_UART_Transmit(&IPORT_UART, (uint8_t*)IPortWriteBuffer, sizeof(IPortWriteBuffer), 0xFFFF);
}

/**
 * @description:IPort-3带字符串参数命令
 * @author: MaxDYi
 * @param {char*} command
 * @param {char*} para
 * @return {*}
 */
void IPort3_AT_StrPara(char* command, char* para) {
    sprintf(IPortWriteBuffer, "AT+%s=%s\r\n", command, para);
    HAL_UART_Transmit(&IPORT_UART, (uint8_t*)IPortWriteBuffer, sizeof(IPortWriteBuffer), 0xFFFF);
}

/**
 * @description:IPort-3通讯模式
 * @author: MaxDYi
 * @return {*}
 */
void IPort3_CommunicationStatus(void) {
    HAL_GPIO_WritePin(IPORT_CFG_GPIO_Port, IPORT_CFG_Pin, GPIO_PIN_SET);
}

/**
 * @description:IPort-3配置模式
 * @author: MaxDYi
 * @return {*}
 */
void IPort3_SettingStatus(void) {
    HAL_GPIO_WritePin(IPORT_CFG_GPIO_Port, IPORT_CFG_Pin, GPIO_PIN_RESET);
}

