/**
  ******************************************************************************
  * @file    bsp_ad7606.c
  * @author  qsunj
  * @version v1.0
  * @date    21-7-16
  * @brief   详情见README
  ******************************************************************************
  */

#include "bsp_ad7606.h"

//内部使用的全局变量
uint16_t G_conv_data[8]={0};

//仅供内部使用的函数
void ad7606_SetOS(uint8_t _ucMode);

/*
*********************************************************************************************************
*	函 数 名: bsp_InitAD7606
*	功能说明: 初始化AD7606 SPI口线
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitAD7606(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* 使能GPIO时钟 */
	RCC_AHB1PeriphClockCmd(AD_RESET_GPIO_CLK | AD_CONVST_GPIO_CLK | AD_RANGE_GPIO_CLK | AD_OS0_GPIO_CLK 
		| AD_OS1_GPIO_CLK | AD_OS2_GPIO_CLK, ENABLE);

	/* 配置RESET GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_RESET_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(AD_RESET_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置CONVST GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_CONVST_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(AD_CONVST_GPIO_PORT, &GPIO_InitStructure);

	/* 配置RANGE GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_RANGE_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(AD_RANGE_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置OS0-2 GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_OS0_PIN;
	GPIO_Init(AD_OS0_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AD_OS1_PIN;
	GPIO_Init(AD_OS1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AD_OS2_PIN;
	GPIO_Init(AD_OS2_GPIO_PORT, &GPIO_InitStructure);

	/* 设置过采样模式 */
	ad7606_SetOS(0);

	/* 设置GPIO的初始状态 */
	ad7606_Reset();				/* 硬件复位复AD7606 */
	
	AD_CONVST_HIGH();			/* CONVST脚设置为高电平 */	
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_Reset
*	功能说明: 硬件复位AD7606
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_Reset(void)
{
	/* AD7606是高电平复位，要求最小脉宽50ns */
	
	AD_RESET_LOW();
	
	AD_RESET_HIGH();
	AD_RESET_HIGH();
	AD_RESET_HIGH();
	AD_RESET_HIGH();
	
	AD_RESET_LOW();
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_SetOS
*	功能说明: 设置过采样模式（数字滤波，硬件求平均值)
*	形    参：_ucMode : 0-6  0表示无过采样，1表示2倍，2表示4倍，3表示8倍，4表示16倍
*				5表示32倍，6表示64倍
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_SetOS(uint8_t _ucMode)
{
	if (_ucMode == 1)
	{
		AD_OS2_0();
		AD_OS1_0();
		AD_OS0_1();
	}
	else if (_ucMode == 2)
	{
		AD_OS2_0();
		AD_OS1_1();
		AD_OS0_0();
	}
	else if (_ucMode == 3)
	{
		AD_OS2_0();
		AD_OS1_1();
		AD_OS0_1();
	}
	else if (_ucMode == 4)
	{
		AD_OS2_1();
		AD_OS1_0();
		AD_OS0_0();
	}
	else if (_ucMode == 5)
	{
		AD_OS2_1();
		AD_OS1_0();
		AD_OS0_1();
	}
	else if (_ucMode == 6)
	{
		AD_OS2_1();
		AD_OS1_1();
		AD_OS0_0();
	}
	else	/* 按0处理 */
	{
		AD_OS2_0();
		AD_OS1_0();
		AD_OS0_0();
	}
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_StartConv
*	功能说明: 启动AD7606的ADC转换
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_StartConv(void)
{
	/* 上升沿开始转换，低电平持续时间至少25ns  */
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	AD_CONVST_LOW();	/* 连续执行2次，低电平约50ns */
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	
	AD_CONVST_HIGH();
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_ReadBytes
*	功能说明: 读取AD7606的采样结果
*	形    参：
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t ad7606_ReadBytes(void)
{
	uint16_t usData = 0;
	usData = drv_spi_read_write_byte(0);
	
	/* Return the shifted data */
	return usData;
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_IRQSrc
*	功能说明: 定时调用本函数，用于读取AD转换器数据
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_IRQSrc(void)
{
	uint8_t i=0;
	
	//定时采样任务
	AD_CS_LOW();
	for ( i=0; i<8; i++ ) {
		G_conv_data[i] = ad7606_ReadBytes();
	}
	AD_CS_HIGH();
	ad7606_StartConv();//转换开始信号
//	Serial_Send(Serial1, "Convert result:%d\t", G_conv_data[1]);
}

/*
*********************************************************************************************************
*	函 数 名: Get_AD7606_voltdata
*	功能说明: 定时调用本函数，用于读取AD转换器数据
*	形    参：num 读取通道
*	返 回 值: 返回电压值(mV)
*********************************************************************************************************
*/
float Get_AD7606_voltdata(uint8_t num)
{
	/***********************************************
	*实测数据range：30-32728(0-10V)
	***********************************************/
	float volt_data = (G_conv_data[num]-30)*0.305548;
	
	return volt_data;
}


