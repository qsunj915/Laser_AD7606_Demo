/**
  ******************************************************************************
  * @file    timer.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-08
  * @brief   Í·ÎÄ¼þ
  ******************************************************************************
  */
	
#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H

#include "stm32f4xx.h"
#include "drv_nvic.h"
#include "drv_gpio.h"

void TIM2_Init(uint16_t arr, uint16_t psc);
void TIM3_Init(uint16_t arr, uint16_t psc);
void TIM4_Init(uint16_t arr, uint16_t psc);
void TIM5_Init(uint16_t arr, uint16_t psc);

void TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx);
void TIM14_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx);
//void TIM5_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx);

void Set_Pwm1(TIM_TypeDef *timx, uint16_t setvalue);
void Set_Pwm2(TIM_TypeDef *timx, uint16_t setvalue);

#endif

