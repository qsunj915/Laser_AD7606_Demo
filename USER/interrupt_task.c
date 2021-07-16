/**
  ******************************************************************************
  * @file	interrupt_task.h
  * @author	qsunj
  * @date	21-7-14
  * @brief   
  ******************************************************************************
  */
#include "interrupt_task.h"

/****************USART**************************/
void InterruptTask_USART1(uint8_t rx_data) {
//	TransmitData_UnPack( RxData );
}

void InterruptTask_USART2(uint8_t rx_data) {

}

void InterruptTask_USART3(uint8_t rx_data) {

}

void InterruptTask_USART6(uint8_t rx_data) {

}

/******************TIM**********************/
void InterruptTask_TIM2(void) {
	
}

//5ms
void InterruptTask_TIM3(void) {
	
//	ad7606_IRQSrc();
	
	uint16_t volt_data[8]={0};
	uint8_t i=0;
	
	//��ʱ��������
	AD_CS_LOW();
	for ( i=0; i<8; i++ ) {
		volt_data[i] = ad7606_ReadBytes();
	}
//	volt_data = ad7606_ReadBytes(); //��ȡ���ݴ���
	AD_CS_HIGH();
	ad7606_StartConv();//ת����ʼ�ź�
	Serial_Send(Serial1, "Convert result:%d\r\n", volt_data[1]);
}

//10ms
void InterruptTask_TIM5(void) {
	LED_Task(LED0, 100);
}

