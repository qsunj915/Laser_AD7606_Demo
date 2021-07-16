/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-22
  * @brief   void Key_Init(void)
			 int8_t Get_Keyx_Status(KEY_Typedef KEYx)
			 //wait for test
  ******************************************************************************
  */
	
#include "bsp_key.h"

void Key_Init(void)
{
	//GPIO_Init
	
	GPIO_Format_Init(GPIOC,GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);

	
}


/**
  * @brief :单个按键状态获取
  * @param :KEYx
  * @note  :无
  * @retval:err : -1
			UP  :  1
			DOWN:  0
  */ 

int8_t Get_Keyx_Status(KEY_Typedef KEYx)
{	 
	switch(KEYx)
	{
		case(KEY0):
		{
			return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4);  
			//break;
		}
		case(KEY1):
		{
			return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5);  
			//break;
		}
		default:
		{
			Serial_Send(ERR_SERIAL,"KEYx input err, please check your input");
			return -1;
		}
	}

}
