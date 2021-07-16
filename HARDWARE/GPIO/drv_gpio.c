/**
  ******************************************************************************
  * @file    drv_gpio.c
  * @author  xjc
  * @version v1.0
  * @date    20-10-07
  * @brief   GPIO cv
  ******************************************************************************
  */
#include "drv_gpio.h"

/**
  * @brief  GPIO初始化，将结构体的成员初始化输入函数，引脚处可用或运算
  * @param  GPIOX  :  GPIOA~E
			PinX   ： GPIO_Pin_1~15 || GPIO_Pin_All
		    Mode   :  GPIO_Mode_IN || GPIO_Mode_OUT || GPIO_Mode_AF || GPIO_Mode_AN
			OType  :  GPIO_OType_PP || GPIO_OType_OD
			PuPd   ： GPIO_PuPd_NOPULL || GPIO_PuPd_UP || GPIO_PuPd_DOWN
		    Speed  :  GPIO_Speed_2MHz || GPIO_Speed_25MHz || GPIO_Speed_50MHz || GPIO_Speed_100MHz
  * @retval NULL
  */

void GPIO_Format_Init(GPIO_TypeDef * GPIOX, uint16_t PinX, GPIOMode_TypeDef Mode, \
					GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char GPIO[5] = {'G','P','I','O',0};
	uint8_t num = 0;
	
	/*--------GPIOX----------*/
	if(IS_GPIO_ALL_PERIPH(GPIOX))
	{
		if(GPIOX == GPIOA)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
			GPIO[4] = 'A';
		}
		else
		{
			if(GPIOX == GPIOB)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
				GPIO[4] = 'B';
			}
			else
			{
				if(GPIOX == GPIOC)
				{
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
					GPIO[4] = 'C';
				}
				else
				{
					if(GPIOX == GPIOD)
					{
						RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
						GPIO[4] = 'D';
					}
					else
					{
						if(GPIOX == GPIOE)
						{
							RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
							GPIO[4] = 'E';
						}
						else
						{
							Serial_Send(ERR_SERIAL,"GPIO_Init_ERR, please connect xjc\r\n");
							return;
						}
					}
				}
			}
		}
	}
	else
	{
		Serial_Send(ERR_SERIAL,"GPIO_Init_ERR\r\n");
		return;
	}
	
	Serial_Send(ERR_SERIAL,"%s,",GPIO);

	/*--------PinX----------*/
	GPIO_InitStructure.GPIO_Pin = PinX;
	while(PinX)
	{
		if(PinX & 0x01)
		{
			Serial_Send(ERR_SERIAL,"Pin%d,",num);
		}
		num ++;
		PinX >>= 1;
	}
	
	/*--------Mode----------*/
	if(IS_GPIO_MODE(Mode))
	{
		GPIO_InitStructure.GPIO_Mode = Mode;

	}
	else
	{
		Serial_Send(ERR_SERIAL,"GPIO_Init_ERR\r\n");
		return;
	}	

	/*--------OType----------*/
	if(IS_GPIO_OTYPE(OType))
	{
		GPIO_InitStructure.GPIO_OType = OType;

	}
	else
	{
		Serial_Send(ERR_SERIAL,"GPIO_Init_ERR\r\n");
		return;
	}
	
	/*--------PuPd----------*/
	if(IS_GPIO_PUPD(PuPd))
	{
		GPIO_InitStructure.GPIO_PuPd = PuPd;

	}
	else
	{
		Serial_Send(ERR_SERIAL,"GPIO_Init_ERR\r\n");
		return;
	}
	
	/*--------Speed----------*/
	if(IS_GPIO_SPEED(Speed))
	{
		GPIO_InitStructure.GPIO_Speed = Speed;

	}
	else
	{
		Serial_Send(ERR_SERIAL,"GPIO_Init_ERR\r\n");
		return;
	}
	
	GPIO_Init(GPIOX,&GPIO_InitStructure);
	
	Serial_Send(ERR_SERIAL,"Init_Ok\r\n");
}
