/**
  ******************************************************************************
  * @file    uart.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-03-31
  * @brief   header
  ******************************************************************************
  */
	
#ifndef __DRV_UART_H
#define __DRV_UART_H

#include "stm32f4xx.h"
#include "stdarg.h"
#include "stdio.h"
#include "drv_nvic.h"

#define Serial1	USART1
#define Serial2	USART2
#define Serial3	USART3
#define Serial6	USART6
#define ERR_SERIAL Serial1 // 错误输出串口 默认串口1

typedef USART_TypeDef Serial_TypeDef;

void USART1_Init(uint32_t BaudRate);
void USART2_Init(uint32_t BaudRate);
void USART3_Init(uint32_t BaudRate);
void USART6_Init(uint32_t BaudRate);

void Serial_SendByte(Serial_TypeDef *Serialx, uint8_t Data);
void Serial_Send(Serial_TypeDef *Serialx,const char *Data,...);
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );

char *itoa(int value, char *string, int radix);

#endif
