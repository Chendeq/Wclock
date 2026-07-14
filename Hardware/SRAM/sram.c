#include "stm32f4xx.h"
#include "sram.h"
#include "Usart1.h"

/* 初始化 FSMC 用于 SRAM */
void SRAM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef Timing;

    /* 使能时钟 */
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE |
                           RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

    /* 配置地址线、数据线、NOE、NWE、NE3、NBL0/1 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

    /* GPIOD: D0-D1, D8-D15, NOE, NWE, A16-A18 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
                                  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource4,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

    /* GPIOE: D2-D7, NBL0, NBL1, A0-A15 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7 |
                                  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
                                  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);

    /* GPIOF: A0-A5, A12-A15 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource0,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource1,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource2,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource3,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource4,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource5,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_FSMC);

    /* GPIOG: A6-A11, NE3 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource0,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource1,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource2,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource3,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource4,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource5,  GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_FSMC);

    /* FSMC 时序配置 */
    Timing.FSMC_AddressSetupTime      = 2;
    Timing.FSMC_AddressHoldTime       = 0;
    Timing.FSMC_DataSetupTime         = 8;
    Timing.FSMC_BusTurnAroundDuration = 0;
    Timing.FSMC_CLKDivision           = 0;
    Timing.FSMC_DataLatency           = 0;
    Timing.FSMC_AccessMode            = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank                  = FSMC_Bank1_NORSRAM3;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType            = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode              = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive       = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode          = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &Timing;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &Timing;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}

/* 16-bit 写缓冲区 */
void SRAM_WriteBuffer(uint16_t *pBuffer, uint32_t uwWriteAddr, uint32_t uwHalfWordCount)
{
    uint32_t i;
    uint8_t *pb = (uint8_t *)pBuffer;   // 字节视角

    Serial_Printf("\r\n>> SRAM Write 0x%08lX len=%lu half-word\r\n",
                  SRAM_BASE_ADDR + uwWriteAddr, uwHalfWordCount);

    for (i = 0; i < uwHalfWordCount; i++)
    {
        *(volatile uint16_t *)(SRAM_BASE_ADDR + uwWriteAddr) = pBuffer[i];
        uwWriteAddr += 2;
    }

    /* 把原始字节流打印成 Hex + ASCII */
    for (i = 0; i < uwHalfWordCount * 2; i += 16)
    {
        uint32_t thisLine = ((uwHalfWordCount * 2 - i) > 16) ? 16 : (uwHalfWordCount * 2 - i);
        Serial_Printf("0x%08lX: ", SRAM_BASE_ADDR + uwWriteAddr - uwHalfWordCount * 2 + i);
        /* Hex */
        for (uint32_t j = 0; j < thisLine; j++)
            Serial_Printf("%02X ", pb[i + j]);
        for (uint32_t j = thisLine; j < 16; j++)
            Serial_Printf("   ");
        /* ASCII */
        Serial_Printf("|");
        for (uint32_t j = 0; j < thisLine; j++)
        {
            uint8_t ch = pb[i + j];
            Serial_Printf("%c", (ch >= 32 && ch < 127) ? ch : '.');
        }
        Serial_Printf("|\r\n");
    }
}

/* 16-bit 读缓冲区 */
void SRAM_ReadBuffer(uint16_t *pBuffer, uint32_t uwReadAddr, uint32_t uwHalfWordCount)
{
    uint32_t i;
    uint8_t *pb = (uint8_t *)pBuffer;   // 字节视角

    for (i = 0; i < uwHalfWordCount; i++)
    {
        pBuffer[i] = *(volatile uint16_t *)(SRAM_BASE_ADDR + uwReadAddr);
        uwReadAddr += 2;
    }

    Serial_Printf("\r\n<< SRAM Read  0x%08lX len=%lu half-word\r\n",
                  SRAM_BASE_ADDR + uwReadAddr - uwHalfWordCount * 2, uwHalfWordCount);

    /* 打印读到的字节流 */
    for (i = 0; i < uwHalfWordCount * 2; i += 16)
    {
        uint32_t thisLine = ((uwHalfWordCount * 2 - i) > 16) ? 16 : (uwHalfWordCount * 2 - i);
        Serial_Printf("0x%08lX: ", SRAM_BASE_ADDR + uwReadAddr - uwHalfWordCount * 2 + i);
        /* Hex */
        for (uint32_t j = 0; j < thisLine; j++)
            Serial_Printf("%02X ", pb[i + j]);
        for (uint32_t j = thisLine; j < 16; j++)
            Serial_Printf("   ");
        /* ASCII */
        Serial_Printf("|");
        for (uint32_t j = 0; j < thisLine; j++)
        {
            uint8_t ch = pb[i + j];
            Serial_Printf("%c", (ch >= 32 && ch < 127) ? ch : '.');
        }
        Serial_Printf("|\r\n");
    }
}