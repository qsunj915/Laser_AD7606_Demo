/**
  ******************************************************************************
  * @file    drv_spi.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-02-23
  * @brief   SPI .h file
						 �궨��__USE_SOFT_SPI_INTERFACE__�����Ƿ�ʹ�����spi�������ƣ�
						 
  ******************************************************************************
  */

#ifndef __DRV_SPI_H
#define __DRV_SPI_H

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "main.h"

//SPI���Ŷ���
#define SPI_CLK_GPIO_PORT			GPIOA
#define SPI_CLK_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_CLK_GPIO_PIN			GPIO_Pin_5

#define SPI_MISO_GPIO_PORT			GPIOA
#define SPI_MISO_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_MISO_GPIO_PIN			GPIO_Pin_6

#define SPI_MOSI_GPIO_PORT			GPIOA
#define SPI_MOSI_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_MOSI_GPIO_PIN			GPIO_Pin_7

#define SPI_NSS_GPIO_PORT			GPIOA
#define SPI_NSS_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_NSS_GPIO_PIN			GPIO_Pin_4


#define spi_set_nss_high( )			SPI_NSS_GPIO_PORT->ODR |= SPI_NSS_GPIO_PIN						            		//Ƭѡ�ø�
#define spi_set_nss_low( )			SPI_NSS_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_NSS_GPIO_PIN ))	//Ƭѡ�õ�

//SPI�ӿڶ���
#define SPI_PORT				  	SPI1				        		//SPI�ӿ�
#define SPI_PORT_CLK				RCC_APB2Periph_SPI1			//SPIʱ��


void    drv_spi_init( void );
uint16_t Ex_drv_spi_read_write_byte( void );
uint16_t drv_spi_read_write_byte( uint16_t TxByte );
void    drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );

#endif

