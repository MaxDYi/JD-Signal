#include "Algorithm.h"

uint32_t ifftFlag = 0;
uint32_t fftSize = 0;


#define TEST_LENGTH_SAMPLES 1024

CoilTest CoilTestResult[COIL_TEST_COUNT];

uint16_t CoilTestFreq[COIL_TEST_COUNT] = {25, 550, 650, 750, 850, 1700, 2000, 2300, 2600};
uint16_t CoilTestShortCircuitCurrent[COIL_TEST_COUNT] = {1050, 113, 90, 69, 50, 310, 275, 255, 235};
double CoilTestStandardVoltage[COIL_TEST_COUNT] = {9.3, 15.9, 14.6, 12.4, 10.0, 100, 100, 100, 100};
double CoilTestVoltageErrorRange[COIL_TEST_COUNT] = {0.7, 1.2, 0.9, 0.8, 7.5, 7.5, 7.5, 7.5};
double CoilTestTestVoltage[COIL_TEST_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};


void CoilTestResult_Init(CoilTest *CoilTestResult)
{
    for (int i = 0; i < COIL_TEST_COUNT; i++)
    {
        CoilTestResult[i].Freq = CoilTestFreq[i];
        CoilTestResult[i].ShortCircuitCurrent = CoilTestShortCircuitCurrent[i];
        CoilTestResult[i].StandardVoltage = CoilTestStandardVoltage[i];
        CoilTestResult[i].VoltageErrorRange = CoilTestVoltageErrorRange[i];
        CoilTestResult[i].TestVoltage = CoilTestTestVoltage[i];
    }
}

void SaveCoilTestResult(uint16_t *ADC1_BasicValue, uint16_t *ADC2_BasicValue)
{
    CoilTestResult_Init(CoilTestResult);
    FATFS_RecordTimeStamp();
    FATFS_SaveResult(COIL_TEST_COUNT,
                     CoilTestResult->Freq,
                     CoilTestResult->ShortCircuitCurrent,
                     CoilTestResult->StandardVoltage,
                     CoilTestResult->TestVoltage,
                     CoilTestResult->VoltageErrorRange);
    FATFS_SaveBasicData(ADC_COUNT, 2, 4, ADC1_BasicValue, ADC2_BasicValue);
}

double AcquireTemp(void)
{
    uint16_t ts_cal1 = *(volatile uint16_t *)(0X1FF1E820);
    uint16_t ts_cal2 = *(volatile uint16_t *)(0X1FF1E840);
    double temp = (double)((110.0 - 30.0) / (ts_cal2 - ts_cal1));

    uint16_t adcx = HAL_ADC_GetValue(&hadc3);
    double temperature = (double)(temp * (adcx - ts_cal1) + 30.0);

    printf("MCU Temp = %.2f\r\n", temperature);
    return temperature;
}
