/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-22
  * @brief   keyscan
  ******************************************************************************
  */
	
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f4xx.h"
#include "drv_gpio.h"
#include "drv_uart.h"
#include "bsp_key.h"

typedef enum KEYs
{ 
  KEY0   = 0x01,
  KEY1   = 0x02, 
}KEY_Typedef;

void Key_Init(void);
int8_t Get_Keyx_Status(KEY_Typedef KEYx);

#endif
