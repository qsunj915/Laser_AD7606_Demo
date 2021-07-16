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
	ad7606_IRQSrc();
	Serial_Send(Serial1, "Convert volt:%f\r\n", Get_AD7606_voltdata(1));
}

//10ms
void InterruptTask_TIM5(void) {
	LED_Task(LED0, 100);	//1秒1闪，用于提示程序正常
}

