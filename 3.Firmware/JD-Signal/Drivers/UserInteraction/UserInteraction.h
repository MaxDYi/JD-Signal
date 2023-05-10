#ifndef __USERINTERACTION_H__
#define __USERINTERACTION_H__

#include "main.h"
#include "stdio.h"
#include "usart.h"
#include "tim.h"

void LED_Init(void);

void Relay_Init(void);

void Relay_On(uint8_t num);

void Relay_Off(uint8_t num);

void Beeper_Init(void);

uint8_t getOneSwitchValue(uint8_t num);

uint8_t getAllSwitchValue(void);

void BeeperEn(uint8_t flag);

#endif
