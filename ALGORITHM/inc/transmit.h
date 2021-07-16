#ifndef __TRANSMIT_H
#define __TRANSMIT_H

#define SX1278_COMMUNICATION    
//#define UART_COMMUNICATION      
//#define UART_DEBUG                

/*-----------------------------------
             ���ݰ���ʽ
һ��20֡����

֡ͷ2�� 0xaa 0x55

����֡  14��u8 һ��7��u16ҡ��ֵ     ���ȸ�8λ
  16    2 ��u8 һ��16������ֵ       ���ȸ�8λ

֡β2�� 0x55 0xaa
-----------------------------------*/
#include "stm32f4xx.h"
#include "drv_uart.h"

typedef enum 
{
	ASxx_Write_OK = 0,		//д��ɹ�
	ASxx_Write_ERROR		//д��ʧ��
}ASxxWriteStatusType;

void Uart_Debug_Transmit(void);
void Uart_Transmit(void);
void SX1278_Init(void);
void SX1278_Transmit(void);
ASxxWriteStatusType ASxx_param_init( void );
void ASxx_read_param  ( uint8_t *pReadBuffer );
void ASxx_read_version( uint8_t *pReadBuffer );
void ASxx_read_voltage( uint8_t *pReadBuffer );
void ASxx_reset( void );
void ASxx_tx_packet( uint8_t Addr_H, uint8_t Addr_L, uint8_t Channel, uint8_t *pTxBuff, uint8_t Length );
uint8_t ASxx_rx_packet( uint8_t *pRxBuff );

#endif

