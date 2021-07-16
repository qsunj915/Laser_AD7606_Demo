/**
  ******************************************************************************
  * @file    systick.c
  * @author  xjc
  * @version V2.0.0
  * @date    2020.10.07
  * @brief   系统滴答定时器初始化，延迟。
			 void SysTick_Init(void)
			 void delay_us(u32 time)
			 void delay_ms(u32 time)

  ******************************************************************************
  */
#include "drv_systick.h"

uint32_t E_COUNTER;


void SysTick_Init(void)
{
	SysTick->LOAD  = (uint32_t)(SystemCoreClock/1000000 - 1UL);
	SysTick->VAL   = 0UL;
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


void delay_us(u32 time)
{
	if(time<=0)
		return;

	E_COUNTER = time;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(E_COUNTER!=0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(u32 time)
{
	if(time<=0)
		return;

	E_COUNTER = time*1000;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(E_COUNTER!=0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/*-----------------
      在it内
-----------------*/
////systick中断处理函数
//void SysTick_Handler(void)
//{
//	if(count!=0){
//		count--;
//	}
//}
