/**
  ******************************************************************************
  * @file    drv_time.c
  * @author  xjc
  * @version v1.0
  * @date    20-09-17
  * @brief   �жϺ�����it��
			 TIM2_Init(uint16_t arr, uint16_t psc)
			 TIM3_Init(uint16_t arr, uint16_t psc)
			 TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
			 
  ******************************************************************************
  */
#include "drv_timer.h"

void TIM2_Init(uint16_t arr, uint16_t psc)   //1ms 8399,9
{
	//arr�Զ���װ��ֵ
	//pscԤ��Ƶֵ
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //��ʱ��2ʱ��ʹ��

	/*��ʱ��2��ʼ��*/
	TIM_TimeBaseStructure.TIM_Period        = arr;                //��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //��������ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               //���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��2�����ж�

	/*�����жϲ���*/
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;                  //��ʱ��2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER2_PreemptionPriority;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = TIMER2_SubPriority;         //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                     //ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);                            //��ʼ���ж�
	TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��

}

void TIM3_Init(uint16_t arr, uint16_t psc)   //1ms 8399,9
{
	//arr�Զ���װ��ֵ
	//pscԤ��Ƶֵ
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //��ʱ��2ʱ��ʹ��

	/*��ʱ��2��ʼ��*/
	TIM_TimeBaseStructure.TIM_Period        = arr;                //��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //��������ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);               //���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��2�����ж�

	/*�����жϲ���*/
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;                  //��ʱ��2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER3_PreemptionPriority;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = TIMER3_SubPriority;         //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                     //ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);                            //��ʼ���ж�
	TIM_Cmd(TIM3, ENABLE);  //ʹ�ܶ�ʱ��
}

void TIM5_Init(uint16_t arr, uint16_t psc)   //1ms 8399,9
{
	//arr�Զ���װ��ֵ
	//pscԤ��Ƶֵ
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //��ʱ��2ʱ��ʹ��

	/*��ʱ��2��ʼ��*/
	TIM_TimeBaseStructure.TIM_Period        = arr;                //��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //��������ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);               //���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��5�����ж�

	/*�����жϲ���*/
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM5_IRQn;                  //��ʱ��5�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER5_PreemptionPriority;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = TIMER5_SubPriority;         //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                     //ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);                            //��ʼ���ж�
	TIM_Cmd(TIM5, ENABLE);  //ʹ�ܶ�ʱ��

}


void TIM14_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;	
	uint8_t pin_source;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14ʱ��ʹ��
	
	switch(pinx)
	{
		case(GPIO_Pin_0):
		{
			pin_source = GPIO_PinSource0;
			break;
		}
		case(GPIO_Pin_1):
		{
			pin_source = GPIO_PinSource1;
			break;
		}
		case(GPIO_Pin_2):
		{
			pin_source = GPIO_PinSource2;
			break;
		}
		case(GPIO_Pin_3):
		{
			pin_source = GPIO_PinSource3;
			break;
		}
		case(GPIO_Pin_4):
		{
			pin_source = GPIO_PinSource4;
			break;
		}
		case(GPIO_Pin_5):
		{
			pin_source = GPIO_PinSource5;
			break;
		}
		case(GPIO_Pin_6):
		{
			pin_source = GPIO_PinSource6;
			break;
		}
		case(GPIO_Pin_7):
		{
			pin_source = GPIO_PinSource7;
			break;
		}
		case(GPIO_Pin_8):
		{
			pin_source = GPIO_PinSource8;
			break;
		}
		case(GPIO_Pin_9):
		{
			pin_source = GPIO_PinSource9;
			break;
		}
		case(GPIO_Pin_10):
		{
			pin_source = GPIO_PinSource10;
			break;
		}
		case(GPIO_Pin_11):
		{
			pin_source = GPIO_PinSource11;
			break;
		}
		case(GPIO_Pin_12):
		{
			pin_source = GPIO_PinSource12;
			break;
		}
		case(GPIO_Pin_13):
		{
			pin_source = GPIO_PinSource13;
			break;
		}
		case(GPIO_Pin_14):
		{
			pin_source = GPIO_PinSource14;
			break;
		}
		case(GPIO_Pin_15):
		{
			pin_source = GPIO_PinSource15;
			break;
		}
		default:
		{
			Serial_Send(ERR_SERIAL,"PWM_Init_ERR, please connect xjc\r\n");
		}
	}
	GPIO_PinAFConfig(GPIOx,pin_source,GPIO_AF_TIM14);              //GPIO����Ϊ��ʱ��9	
	
	GPIO_Format_Init(GPIOx, pinx, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
	
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period        = arr;                //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);                //��ʼ����ʱ��e
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;    //�������:TIM����Ƚϼ��Ե�
	
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);                      //����Tָ���Ĳ�����ʼ������TIM4OC1
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);             //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 	
	
	TIM_Cmd(TIM14, ENABLE);  //ʹ��TIM4

}  


void TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;	
	uint8_t pin_source;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14ʱ��ʹ��
	
	switch(pinx)
	{
		case(GPIO_Pin_0):
		{
			pin_source = GPIO_PinSource0;
			break;
		}
		case(GPIO_Pin_1):
		{
			pin_source = GPIO_PinSource1;
			break;
		}
		case(GPIO_Pin_2):
		{
			pin_source = GPIO_PinSource2;
			break;
		}
		case(GPIO_Pin_3):
		{
			pin_source = GPIO_PinSource3;
			break;
		}
		case(GPIO_Pin_4):
		{
			pin_source = GPIO_PinSource4;
			break;
		}
		case(GPIO_Pin_5):
		{
			pin_source = GPIO_PinSource5;
			break;
		}
		case(GPIO_Pin_6):
		{
			pin_source = GPIO_PinSource6;
			break;
		}
		case(GPIO_Pin_7):
		{
			pin_source = GPIO_PinSource7;
			break;
		}
		case(GPIO_Pin_8):
		{
			pin_source = GPIO_PinSource8;
			break;
		}
		case(GPIO_Pin_9):
		{
			pin_source = GPIO_PinSource9;
			break;
		}
		case(GPIO_Pin_10):
		{
			pin_source = GPIO_PinSource10;
			break;
		}
		case(GPIO_Pin_11):
		{
			pin_source = GPIO_PinSource11;
			break;
		}
		case(GPIO_Pin_12):
		{
			pin_source = GPIO_PinSource12;
			break;
		}
		case(GPIO_Pin_13):
		{
			pin_source = GPIO_PinSource13;
			break;
		}
		case(GPIO_Pin_14):
		{
			pin_source = GPIO_PinSource14;
			break;
		}
		case(GPIO_Pin_15):
		{
			pin_source = GPIO_PinSource15;
			break;
		}
		default:
		{
			Serial_Send(ERR_SERIAL,"PWM_Init_ERR, please connect xjc\r\n");
		}
	}
	
	GPIO_Format_Init(GPIOx, pinx, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
	
	GPIO_PinAFConfig(GPIOx,pin_source,GPIO_AF_TIM4);              //GPIO����Ϊ��ʱ��9	
	
	
	
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period        = arr;                //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);                //��ʼ����ʱ��e
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;    //�������:TIM����Ƚϼ��Ե�
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);                      //����Tָ���Ĳ�����ʼ������TIM4OC1
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);             //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 	
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4

}  

void Set_Pwm1(TIM_TypeDef *timx, uint16_t setvalue)
{
	 TIM_SetCompare1(timx,setvalue);
}

void Set_Pwm2(TIM_TypeDef *timx, uint16_t setvalue)
{
	 TIM_SetCompare2(timx,setvalue);
}















