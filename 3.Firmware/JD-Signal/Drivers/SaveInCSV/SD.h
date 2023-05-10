#ifndef __SD_H__
#define __SD_H__


#include "main.h"
#include "sdmmc.h"
#include "stdio.h"


int SD_Init(void);

int SD_State(void);

HAL_SD_CardCIDTypeDef SD_GetCID(void);

HAL_SD_CardCSDTypedef SD_GetCSD(void);

HAL_SD_CardInfoTypeDef SD_GetInfo(void);

void SD_PrintInfo(void);

#endif
