/**
  ******************************************************************************
  * @file    init.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-03
  * @brief   System_Init(void);
						 

  ******************************************************************************
  */

#include "init.h"

/**
  * @brief  system init
  * @param  none
  * @retval 无
  */
void System_Init(void)
{
	SystemInit();
	NVIC_Priority_Init();
	SysTick_Init();
	
	USART1_Init(115200);
	
	LED_Init();
	Key_Init();
	Beep_Init();
	
	USART2_Init(115200);
	USART6_Init(115200);
	
	//ad7606初始化
	drv_spi_init();				//spi引脚初始化
	bsp_InitAD7606();			//ad7606引脚初始化
	AD_RANGE_10V();				//量程为正负10V
	ad7606_StartConv();			//启动采样，避免第1组数据全0的问题
	
	TIM2_Init(8399,9);	//1ms
	TIM3_Init(8399,49);	//5ms
	TIM5_Init(8399, 99);//10ms
	
	//初始化完成标志
	GPIO_ResetBits(GPIOC,LED3); 
	
	delay_ms(500);
	
}


