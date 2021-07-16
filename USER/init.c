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
  * @retval ��
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
	
	//ad7606��ʼ��
	drv_spi_init();				//spi���ų�ʼ��
	bsp_InitAD7606();			//ad7606���ų�ʼ��
	AD_RANGE_10V();				//����Ϊ����10V
	ad7606_StartConv();			//���������������1������ȫ0������
//	ad7606_StartRecord(200);
//	Serial_Send(Serial1, "Range = %d, OS = %d, \r\n", g_tAD.usBuf[0], g_tAD.usBuf[1]);
	
	TIM2_Init(8399,9);	//1ms
	TIM3_Init(8399,49);	//5ms
	TIM5_Init(8399, 99);//10ms
	
	
	Serial_Send(Serial1,"All init are ready\r\n");
	
	delay_ms(500);
	
}


