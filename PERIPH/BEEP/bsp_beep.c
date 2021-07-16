/**
  ******************************************************************************
  * @file    bsp_beep.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-11
  * @brief   Beep_On();
			 Beep_Off();
			 void Beep_Change(void)
			 void Beep_Task(uint32_t interval)        //进多少次函数翻转，记得用完Beep_Off();
			 //wait for test
  ******************************************************************************
  */

#include "bsp_beep.h"

void Beep_Init(void)
{
	GPIO_Format_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
}

void Beep_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
}

void Beep_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
}

void Beep_Change(void)
{
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0))
	{
		Beep_Off();
	}
	else
	{
		Beep_On();
	}
}

void Beep_Task(uint32_t interval)
{
	static uint32_t val = 0; 
	if(val < interval)
	{
		val++;
	}
	else
	{
		val = 0;
		Beep_Change();
	}
}
