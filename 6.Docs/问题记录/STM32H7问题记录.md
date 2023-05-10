# STM32H7

## 1.DMA

![6141703-5310c167cef9d0df.png](https://img-blog.csdnimg.cn/img_convert/6ee0fb6a96bfe3e52f466416d62921b4.png)

DMA需要在外设之前初始化。

使用`__attribute__((section( )))`指定DMA访问的目标地址。

在定义数组时，通过`__attribute__((section(".ARM.__at_address")))`指令把数组地址分配到AXI。

```c
uint16_t DualSine12bit[1024] __attribute__((section(".ARM.__at_0x24000000")));
```

或修改程序下载地址：

![image-20230108191648900](https://raw.githubusercontent.com/Tiramisumisu/PicGo/main/img/202301081916940.png)

可以解决STM32H7芯片使用DMA无效的问题。

## 2.DAC

DAC使用DMA方式传输，配置如下。

![image-20230108191534923](https://raw.githubusercontent.com/Tiramisumisu/PicGo/main/img/202301081915991.png)

DMA使用TIM6触发。



TIM6 触发频率 = TIM6CLK / （Period + 1）/（Prescaler + 1）。

## 3.RTC

RTC时间从1970年1月1日0点0分0秒开始。

**时间寄存器RTC_TR**

![img](https://img-blog.csdnimg.cn/img_convert/c3ddbf47454900d706bce91f5653f71a.png)

**日期寄存器RTC_DR**

![image-20220323111621496](https://img-blog.csdnimg.cn/img_convert/a1a570d316e9c283ae76ec41534e8449.png)

**注意**：VBAT同时为PC13~PC15供电，为避免PC13消耗电流应悬空。

## 4.SDMMC

SDMMC1与SDMMC2的IDMA可以访问的RAM区域不同，SDMMC1只能访问AXI，SDMMC2可以访问AXI、SRAM1、SRAM2、SRAM3。

使用SDMMC2时候必须设置程序起始地址到IDMA可访问区间。

## 5.FATFS

**FS_NORTC** 用于设定文件时间戳。

固定时间戳在ffconf.h中设定：

```C
#define _NORTC_MON	1
#define _NORTC_MDAY	1
#define _NORTC_YEAR	2023
```

动态时间戳在**fatfs.c**中的**DWORD get_fattime(*void*)**函数中补全。

```c
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
      // 0-4 bit: second / 2
      // 5-10 bit: minute
      // 11-15 bit: hour
      // 16-20 bit: day
      // 21-24 bit: month
      // 25-31 bit: year - 1980
    RTC_DateTypeDef RTC_Date;  //获取日期结构体
    RTC_TimeTypeDef RTC_Time;   //获取时间结构体
    HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BIN);
    DWORD time = ((DWORD)(RTC_Date.Year - 10) << 25) | ((DWORD)RTC_Date.Month << 21) | ((DWORD)RTC_Date.Date << 16) | ((DWORD)RTC_Time.Hours << 11) | ((DWORD)RTC_Time.Minutes << 5) | ((DWORD)RTC_Time.Seconds >> 1);
    return time;
  /* USER CODE END get_fattime */
}
```

**注意**：FatFS时间从1980年1月1日0点0分0秒开始，**与RTC相差10年**。
