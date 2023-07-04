/*
 * @Descripttion:
 * @version:
 * @Author: MDYi
 * @Date: 2023-01-09 18:48:49
 * @LastEditTime: 2023-02-04 13:38:02
 */
#include "SD.h"

#define SD_PORT hsd1

HAL_SD_CardCIDTypedef pCID;
HAL_SD_CardCSDTypedef pCSD;
HAL_SD_CardInfoTypeDef pCardInfo;

int SD_Init(void)
{
    if (SD_State() == HAL_SD_CARD_TRANSFER)
    {
        HAL_SD_GetCardCID(&SD_PORT, &pCID);
        HAL_SD_GetCardCSD(&SD_PORT, &pCSD);
        HAL_SD_GetCardInfo(&SD_PORT, &pCardInfo);
        return 1;
    }
    else
    {
        return 0;
    }
}

int SD_State(void)
{
    return HAL_SD_GetCardState(&SD_PORT);
}

HAL_SD_CardCIDTypeDef SD_GetCID(void)
{
    HAL_SD_GetCardCID(&SD_PORT, &pCID);
    return pCID;
}

HAL_SD_CardCSDTypedef SD_GetCSD(void)
{
    HAL_SD_GetCardCSD(&SD_PORT, &pCSD);
    return pCSD;
}

HAL_SD_CardInfoTypeDef SD_GetInfo(void)
{
    HAL_SD_GetCardInfo(&SD_PORT, &pCardInfo);
    return pCardInfo;
}

void SD_PrintInfo(void)
{
    printf("Capacity:%.1fGB\r\n", (double)SD_GetInfo().BlockSize * SD_GetInfo().BlockNbr / 1024 / 1024 / 1024);
    printf("BlockSize:%.0fB\r\n", (double)SD_GetInfo().BlockSize);
    printf("ManufactDate:%d\r\n", SD_GetCID().ManufactDate);
    printf("ProdRev:%d\r\n", SD_GetCID().ProdRev);
}