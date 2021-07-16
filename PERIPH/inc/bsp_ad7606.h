/**
  ******************************************************************************
  * @file    bsp_ad7606.h
  * @author  qsunj
  * @version test
  * @date    21-7-15
  * @brief   
  ******************************************************************************
  */
#ifndef __BSP_AD7606_H
#define __BSP_AD7606_H

#include "stm32f4xx.h"
#include "drv_gpio.h"
#include "drv_spi.h"

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* 每个样本2字节，采集通道 */
#define CH_NUM			8				/* 采集2通道 */
#define FIFO_SIZE		1*1024*2		/* 大小不要超过48K (CPU内部RAM 只有64K) */

/* 定义AD7606的SPI GPIO */
/************************************************************/
#define AD_SPI_SCK_PIN                   SPI_CLK_GPIO_PIN
#define AD_SPI_SCK_GPIO_PORT             SPI_CLK_GPIO_PORT
#define AD_SPI_SCK_GPIO_CLK              SPI_CLK_GPIO_CLK

#define AD_SPI_MISO_PIN                  SPI_MISO_GPIO_PIN
#define AD_SPI_MISO_GPIO_PORT            SPI_MISO_GPIO_PORT
#define AD_SPI_MISO_GPIO_CLK             SPI_MISO_GPIO_CLK

#define AD_CS_PIN                        SPI_NSS_GPIO_PIN
#define AD_CS_GPIO_PORT                  SPI_NSS_GPIO_PORT
#define AD_CS_GPIO_CLK                   SPI_NSS_GPIO_CLK
/************************************************************/
/*　定义AD7606其它的GPIO */
#define AD_RESET_PIN                     GPIO_Pin_10
#define AD_RESET_GPIO_PORT               GPIOC
#define AD_RESET_GPIO_CLK                RCC_AHB1Periph_GPIOC

#define AD_CONVST_PIN                    GPIO_Pin_1
#define AD_CONVST_GPIO_PORT              GPIOA		
#define AD_CONVST_GPIO_CLK               RCC_AHB1Periph_GPIOC

#define AD_RANGE_PIN                     GPIO_Pin_8
#define AD_RANGE_GPIO_PORT               GPIOC		
#define AD_RANGE_GPIO_CLK                RCC_AHB1Periph_GPIOC

#define AD_OS0_PIN           			 GPIO_Pin_2
#define AD_OS0_GPIO_PORT     			 GPIOE		
#define AD_OS0_GPIO_CLK      			 RCC_AHB1Periph_GPIOC
										 
#define AD_OS1_PIN           			 GPIO_Pin_3
#define AD_OS1_GPIO_PORT     			 GPIOE		
#define AD_OS1_GPIO_CLK      			 RCC_AHB1Periph_GPIOC
										 
#define AD_OS2_PIN           			 GPIO_Pin_4
#define AD_OS2_GPIO_PORT     			 GPIOE		
#define AD_OS2_GPIO_CLK      			 RCC_AHB1Periph_GPIOC

/*************************************************************************/
#define AD_CS_LOW()     		GPIO_ResetBits(AD_CS_GPIO_PORT, AD_CS_PIN);
#define AD_CS_HIGH()     		GPIO_SetBits(AD_CS_GPIO_PORT, AD_CS_PIN);

#define AD_RESET_LOW()			GPIO_ResetBits(AD_RESET_GPIO_PORT, AD_RESET_PIN);
#define AD_RESET_HIGH()			GPIO_SetBits(AD_RESET_GPIO_PORT, AD_RESET_PIN);

#define AD_CONVST_LOW()			GPIO_ResetBits(AD_CONVST_GPIO_PORT, AD_CONVST_PIN);
#define AD_CONVST_HIGH()		GPIO_SetBits(AD_CONVST_GPIO_PORT, AD_CONVST_PIN);

#define AD_RANGE_5V()			GPIO_ResetBits(AD_RANGE_GPIO_PORT, AD_RANGE_PIN);
#define AD_RANGE_10V()			GPIO_SetBits(AD_RANGE_GPIO_PORT, AD_RANGE_PIN);

#define AD_OS0_0()				GPIO_ResetBits(AD_OS0_GPIO_PORT, AD_OS0_PIN);
#define AD_OS0_1()				GPIO_SetBits(AD_OS0_GPIO_PORT, AD_OS0_PIN);

#define AD_OS1_0()				GPIO_ResetBits(AD_OS1_GPIO_PORT, AD_OS1_PIN);
#define AD_OS1_1()				GPIO_SetBits(AD_OS1_GPIO_PORT, AD_OS1_PIN);

#define AD_OS2_0()				GPIO_ResetBits(AD_OS2_GPIO_PORT, AD_OS2_PIN);
#define AD_OS2_1()				GPIO_SetBits(AD_OS2_GPIO_PORT, AD_OS2_PIN);

#define AD_MISO_LOW()			GPIO_ResetBits(AD_SPI_MISO_GPIO_PORT, AD_SPI_MISO_PIN);
#define AD_MISO_HIGH()	    	GPIO_SetBits(AD_SPI_MISO_GPIO_PORT, AD_SPI_MISO_PIN);

#define AD_SCK_LOW()			GPIO_ResetBits(AD_SPI_SCK_GPIO_PORT, AD_SPI_SCK_PIN);
#define AD_CSK_HIGH()			GPIO_SetBits(AD_SPI_SCK_GPIO_PORT, AD_SPI_SCK_PIN);

#define AD_MISO_IN				GPIO_ReadOutputDataBit(SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN)
/***********************************************************************************/
/* AD数据采集缓冲区 */
typedef struct
{
	uint16_t usRead;
	uint16_t usWrite;
	uint16_t usCount;
	uint16_t usBuf[FIFO_SIZE];
}FIFO_T;

/* 供外部调用的函数声明 */
void ad7606_Reset(void);
void ad7606_SetOS(uint8_t _ucMode);
void bsp_SET_TIM2_FREQ(uint32_t _ulFreq);
void bsp_InitAD7606(void);
void ad7606_StopRecord(void);
uint8_t GetAdcFormFifo(uint16_t *_usReadAdc);
void ad7606_IRQSrc(void);

void ad7606_StartRecord(uint32_t _ulFreq);

uint16_t ad7606_ReadBytes(void);
void ad7606_StartConv(void);

extern FIFO_T  g_tAD;

#endif
