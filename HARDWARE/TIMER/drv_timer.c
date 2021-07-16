/**
  ******************************************************************************
  * @file    drv_time.c
  * @author  xjc
  * @version v1.0
  * @date    20-09-17
  * @brief   中断函数在it内
			 TIM2_Init(uint16_t arr, uint16_t psc)
			 TIM3_Init(uint16_t arr, uint16_t psc)
			 TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
			 
  ******************************************************************************
  */
#include "drv_timer.h"

void TIM2_Init(uint16_t arr, uint16_t psc)   //1ms 8399,9
{
	//arr自动重装载值
	//psc预分频值
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //定时器2时钟使能

	/*定时器2初始化*/
	TIM_TimeBaseStructure.TIM_Period        = arr;                //设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //递增计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               //将结构参数用于初始化定时器2

	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE );           //使能定时器2更新中断

	/*设置中断参数*/
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;                  //定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER2_PreemptionPriority;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = TIMER2_SubPriority;         //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                     //使能中断通道
	NVIC_Init(&NVIC_InitStructure);                            //初始化中断
	TIM_Cmd(TIM2, ENABLE);  //使能定时器

}

void TIM3_Init(uint16_t arr, uint16_t psc)   //1ms 8399,9
{
	//arr自动重装载值
	//psc预分频值
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //定时器2时钟使能

	/*定时器2初始化*/
	TIM_TimeBaseStructure.TIM_Period        = arr;                //设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //递增计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);               //将结构参数用于初始化定时器2

	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE );           //使能定时器2更新中断

	/*设置中断参数*/
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;                  //定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER3_PreemptionPriority;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = TIMER3_SubPriority;         //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                     //使能中断通道
	NVIC_Init(&NVIC_InitStructure);                            //初始化中断
	TIM_Cmd(TIM3, ENABLE);  //使能定时器
}

void TIM5_Init(uint16_t arr, uint16_t psc)   //1ms 8399,9
{
	//arr自动重装载值
	//psc预分频值
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //定时器2时钟使能

	/*定时器2初始化*/
	TIM_TimeBaseStructure.TIM_Period        = arr;                //设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //递增计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);               //将结构参数用于初始化定时器2

	TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE );           //使能定时器5更新中断

	/*设置中断参数*/
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM5_IRQn;                  //定时器5中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER5_PreemptionPriority;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = TIMER5_SubPriority;         //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                     //使能中断通道
	NVIC_Init(&NVIC_InitStructure);                            //初始化中断
	TIM_Cmd(TIM5, ENABLE);  //使能定时器

}


void TIM14_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;	
	uint8_t pin_source;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14时钟使能
	
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
	GPIO_PinAFConfig(GPIOx,pin_source,GPIO_AF_TIM14);              //GPIO复用为定时器9	
	
	GPIO_Format_Init(GPIOx, pinx, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
	
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period        = arr;                //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);                //初始化定时器e
	
	//初始化TIM4 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;    //输出极性:TIM输出比较极性低
	
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);                      //根据T指定的参数初始化外设TIM4OC1
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);             //使能TIM14在CCR1上的预装载寄存器

	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能 	
	
	TIM_Cmd(TIM14, ENABLE);  //使能TIM4

}  


void TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;	
	uint8_t pin_source;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14时钟使能
	
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
	
	GPIO_PinAFConfig(GPIOx,pin_source,GPIO_AF_TIM4);              //GPIO复用为定时器9	
	
	
	
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period        = arr;                //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);                //初始化定时器e
	
	//初始化TIM4 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;    //输出极性:TIM输出比较极性低
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);                      //根据T指定的参数初始化外设TIM4OC1
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);             //使能TIM14在CCR1上的预装载寄存器

	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 	
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4

}  

void Set_Pwm1(TIM_TypeDef *timx, uint16_t setvalue)
{
	 TIM_SetCompare1(timx,setvalue);
}

void Set_Pwm2(TIM_TypeDef *timx, uint16_t setvalue)
{
	 TIM_SetCompare2(timx,setvalue);
}















