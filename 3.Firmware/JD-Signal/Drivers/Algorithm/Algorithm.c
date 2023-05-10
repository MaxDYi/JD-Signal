#include "Algorithm.h"
/* 变量 */
uint32_t ifftFlag = 0;
uint32_t fftSize = 0;

/* 输入和输出缓冲*/
#define TEST_LENGTH_SAMPLES 1024

static float32_t testOutput_f32[TEST_LENGTH_SAMPLES * 2];
static float32_t testOutputMag_f32[TEST_LENGTH_SAMPLES * 2];
static float32_t testInput_f32[TEST_LENGTH_SAMPLES * 2];
static float32_t Phase_f32[TEST_LENGTH_SAMPLES * 2]; /* 相位*/

static float64_t testOutput_f64[TEST_LENGTH_SAMPLES * 2];
static float64_t testOutputMag_f64[TEST_LENGTH_SAMPLES * 2];
static float64_t testInput_f64[TEST_LENGTH_SAMPLES * 2];
static float64_t Phase_f64[TEST_LENGTH_SAMPLES * 2]; /* 相位*/

CoilTest CoilTestResult[COIL_TEST_COUNT];

#pragma location = ".RAM_D1"
uint16_t ADC1_Buffer[ADC_COUNT];
#pragma location = ".RAM_D1"
uint16_t ADC2_Buffer[ADC_COUNT];

__IO uint8_t ADC1ConvEnd = 0;
__IO uint8_t ADC2ConvEnd = 0;

uint16_t CoilTestFreq[COIL_TEST_COUNT] = {25, 550, 650, 750, 850, 1700, 2000, 2300, 2600};
uint16_t CoilTestShortCircuitCurrent[COIL_TEST_COUNT] = {1050, 113, 90, 69, 50, 310, 275, 255, 235};
double CoilTestStandardVoltage[COIL_TEST_COUNT] = {9.3, 15.9, 14.6, 12.4, 10.0, 100, 100, 100, 100};
double CoilTestVoltageErrorRange[COIL_TEST_COUNT] = {0.7, 1.2, 0.9, 0.8, 7.5, 7.5, 7.5, 7.5};
double CoilTestTestVoltage[COIL_TEST_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1)
    {
        ADC1ConvEnd = 1;
    }
    else if (hadc == &hadc2)
    {
        ADC2ConvEnd = 1;
    }
}

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

void AcquireData(void)
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC1_Buffer, ADC_COUNT);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)ADC2_Buffer, ADC_COUNT);

    HAL_TIM_Base_Start(&htim4);
    while (!ADC1ConvEnd)
        ;
    while (!ADC2ConvEnd)
        ;

    HAL_TIM_Base_Stop(&htim4);
    HAL_ADC_Stop_DMA(&hadc1);
    HAL_ADC_Stop_DMA(&hadc2);

    SaveCoilTestResult(ADC1_Buffer, ADC2_Buffer);
}

void ADC_Calibration(void)
{
    HAL_Delay(1000);

    HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);

    HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
}

double AcquireTemp(void)
{
    uint16_t ts_cal1 = *(volatile uint16_t *)(0X1FF1E820);        /* ??TS_CAL1 */
    uint16_t ts_cal2 = *(volatile uint16_t *)(0X1FF1E840);        /* ??TS_CAL2 */
    double temp = (double)((110.0 - 30.0) / (ts_cal2 - ts_cal1)); /* ?????? */

    uint16_t adcx = HAL_ADC_GetValue(&hadc3);
    double temperature = (double)(temp * (adcx - ts_cal1) + 30.0); /* ???? */

    printf("MCU Temp = %.2f\r\n", temperature);
    return temperature;
}

void PowerPhaseRadians_f32(float32_t *_ptr, float32_t *_phase, uint16_t _usFFTPoints, float32_t _uiCmpValue)
{
    float32_t lX, lY;
    uint16_t i;
    float32_t phase;
    float32_t mag;

    for (i = 0; i < _usFFTPoints; i++)
    {
        lX = _ptr[2 * i];
        lY = _ptr[2 * i + 1];

        phase = atan2f(lY, lX);
        arm_sqrt_f32((float32_t)(lX * lX + lY * lY), &mag);

        if (_uiCmpValue > mag)
        {
            Phase_f32[i] = 0;
        }
        else
        {
            Phase_f32[i] = phase * 180.0f / 3.1415926f;
        }
    }
}

void PowerPhaseRadians_f64(float64_t *_ptr, float64_t *_phase, uint16_t _usFFTPoints, float64_t _uiCmpValue)
{
    float64_t lX, lY;
    uint16_t i;
    float64_t phase;
    float64_t mag;

    for (i = 0; i < _usFFTPoints; i++)
    {
        lX = _ptr[2 * i];     /* 实部 */
        lY = _ptr[2 * i + 1]; /* 虚部 */

        phase = atan2(lY, lX);         /* atan2求解的结果范围是(-pi, pi], 弧度�? */
        mag = sqrt(lX * lX + lY * lY); /* 求模 */

        if (_uiCmpValue > mag)
        {
            Phase_f64[i] = 0;
        }
        else
        {
            Phase_f64[i] = phase * 180.0 / 3.1415926; /* 将求解的结果由弧度转�?为�?�度 */
        }
    }
}

static void arm_rfft_f32_app(void)
{
    uint16_t i;
    arm_rfft_fast_instance_f32 S;

    /* 正变�? */
    ifftFlag = 0;

    /* 初�?�化结构体S�?的参�? */
    arm_rfft_fast_init_f32(&S, TEST_LENGTH_SAMPLES);

    for (i = 0; i < 1024; i++)
    {
        /* 波形�?由直流分量，50Hz正弦波组成，波形采样�?1024，初始相�?60° */
        testInput_f32[i] = 1 + cos(2 * 3.1415926f * 50 * i / 1024 + 3.1415926f / 3);
    }

    /* 1024点实序列�?速FFT */
    arm_rfft_fast_f32(&S, testInput_f32, testOutput_f32, ifftFlag);

    /* 为了方便跟函数arm_cfft_f32计算的结果做对比，这里求解了1024组模值，实际函数arm_rfft_fast_f32
       �?求解出了512�?
    */
    arm_cmplx_mag_f32(testOutput_f32, testOutputMag_f32, TEST_LENGTH_SAMPLES);

    printf("=========================================\r\n");

    /* 求相�? */
    PowerPhaseRadians_f32(testOutput_f32, Phase_f32, TEST_LENGTH_SAMPLES, 0.5f);

    /* 串口打印求解的幅频和相�?? */
    for (i = 0; i < TEST_LENGTH_SAMPLES; i++)
    {
        printf("%f, %f\r\n", testOutputMag_f32[i], Phase_f32[i]);
    }
}

static void arm_rfft_f64_app(void)
{
    uint16_t i;
    float64_t lX, lY;
    arm_rfft_fast_instance_f64 S;

    /* 正变�? */
    ifftFlag = 0;

    /* 初�?�化结构体S�?的参�? */
    arm_rfft_fast_init_f64(&S, TEST_LENGTH_SAMPLES);

    for (i = 0; i < 1024; i++)
    {
        /* 波形�?由直流分量，50Hz正弦波组成，波形采样�?1024，初始相�?60° */
        testInput_f64[i] = 1 + cos(2 * 3.1415926 * 50 * i / 1024 + 3.1415926 / 3);
    }

    /* 1024点实序列�?速FFT */
    arm_rfft_fast_f64(&S, testInput_f64, testOutput_f64, ifftFlag);

    /* 求解模�?  */
    for (i = 0; i < TEST_LENGTH_SAMPLES; i++)
    {
        lX = testOutput_f64[2 * i];                     /* 实部*/
        lY = testOutput_f64[2 * i + 1];                 /* 虚部 */
        testOutputMag_f64[i] = sqrt(lX * lX + lY * lY); /* 求模 */
    }

    printf("=========================================\r\n");

    /* 求相�? */
    PowerPhaseRadians_f64(testOutput_f64, Phase_f64, TEST_LENGTH_SAMPLES, 0.5);

    /* 串口打印求解的幅频和相�?? */
    for (i = 0; i < TEST_LENGTH_SAMPLES; i++)
    {
        printf("%.11f, %.11f\r\n", testOutputMag_f64[i], Phase_f64[i]);
    }
}
