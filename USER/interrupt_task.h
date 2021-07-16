/**
  ******************************************************************************
  * @file	interrupt_task.h
  * @author	qsunj
  * @date	21-7-14
  * @brief   
  ******************************************************************************
  */
#ifndef __INTERRUPT_TASK_H
#define __INTERRUPT_TASK_H

#include "stm32f4xx.h"
#include "init.h"

void InterruptTask_USART1(uint8_t rx_data);
void InterruptTask_USART2(uint8_t rx_data);
void InterruptTask_USART3(uint8_t rx_data);
void InterruptTask_USART6(uint8_t rx_data);

void InterruptTask_TIM2(void);
void InterruptTask_TIM3(void);
void InterruptTask_TIM5(void);
#endif
