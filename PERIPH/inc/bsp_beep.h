/**
  ******************************************************************************
  * @file    bsp_beep.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-11
  * @brief   header
  ******************************************************************************
  */
#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "stm32f4xx.h"
#include "drv_gpio.h"

void Beep_Init(void);
void Beep_On(void);
void Beep_Off(void);
void Beep_Task(uint32_t interval);

#endif

