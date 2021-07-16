/**
  ******************************************************************************
  * @file    led.c
  * @author  jOKERII
  * @version v1.1
  * @date    20-10-10
  * @brief   LED_Init();
			 void LED_Task(LED_Typedef LEDx, uint32_t interval) //LEDx:LED几 interval:进多少次函数后翻转
			 // wait for test
  ******************************************************************************
  */
	
#include "bsp_led.h"

void LED_Init(void)
{
	GPIO_Format_Init(GPIOC,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,\
					GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3); 
}

void LED_Task(LED_Typedef LEDx, uint32_t interval)
{
	static uint16_t val[4]  = {0};
	static uint16_t Flag[4] = {0};
	uint16_t        num     =  0 ;
	
	switch(LEDx)
	{
		case(LED0):
		{
			num = 0;
		}
		case(LED1):
		{
			num = 1;
		}
		case(LED2):
		{
			num = 2;
		}
		case(LED3):
		{
			num = 3;
		}
	}
	if(val[num] >= interval)
	{
		if(Flag[num])
		{
			GPIO_ResetBits(GPIOC,LEDx); 
			Flag[num] = 0;
		}
		else
		{
			GPIO_SetBits(GPIOC,LEDx); 
			Flag[num] = 1;
		}
		val[num] = 0;
	}
	val[num]++;
}
