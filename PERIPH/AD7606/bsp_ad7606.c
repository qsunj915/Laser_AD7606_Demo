/**
  ******************************************************************************
  * @file    bsp_ad7606.c
  * @author  qsunj
  * @version v1.0
  * @date    21-7-16
  * @brief   �����README
  ******************************************************************************
  */

#include "bsp_ad7606.h"

//�ڲ�ʹ�õ�ȫ�ֱ���
uint16_t G_conv_data[8]={0};

//�����ڲ�ʹ�õĺ���
void ad7606_SetOS(uint8_t _ucMode);

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitAD7606
*	����˵��: ��ʼ��AD7606 SPI����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitAD7606(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* ʹ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(AD_RESET_GPIO_CLK | AD_CONVST_GPIO_CLK | AD_RANGE_GPIO_CLK | AD_OS0_GPIO_CLK 
		| AD_OS1_GPIO_CLK | AD_OS2_GPIO_CLK, ENABLE);

	/* ����RESET GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_RESET_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(AD_RESET_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����CONVST GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_CONVST_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(AD_CONVST_GPIO_PORT, &GPIO_InitStructure);

	/* ����RANGE GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_RANGE_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(AD_RANGE_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����OS0-2 GPIO */
	GPIO_InitStructure.GPIO_Pin = AD_OS0_PIN;
	GPIO_Init(AD_OS0_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AD_OS1_PIN;
	GPIO_Init(AD_OS1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AD_OS2_PIN;
	GPIO_Init(AD_OS2_GPIO_PORT, &GPIO_InitStructure);

	/* ���ù�����ģʽ */
	ad7606_SetOS(0);

	/* ����GPIO�ĳ�ʼ״̬ */
	ad7606_Reset();				/* Ӳ����λ��AD7606 */
	
	AD_CONVST_HIGH();			/* CONVST������Ϊ�ߵ�ƽ */	
}

/*
*********************************************************************************************************
*	�� �� ��: ad7606_Reset
*	����˵��: Ӳ����λAD7606
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ad7606_Reset(void)
{
	/* AD7606�Ǹߵ�ƽ��λ��Ҫ����С����50ns */
	
	AD_RESET_LOW();
	
	AD_RESET_HIGH();
	AD_RESET_HIGH();
	AD_RESET_HIGH();
	AD_RESET_HIGH();
	
	AD_RESET_LOW();
}

/*
*********************************************************************************************************
*	�� �� ��: ad7606_SetOS
*	����˵��: ���ù�����ģʽ�������˲���Ӳ����ƽ��ֵ)
*	��    �Σ�_ucMode : 0-6  0��ʾ�޹�������1��ʾ2����2��ʾ4����3��ʾ8����4��ʾ16��
*				5��ʾ32����6��ʾ64��
*	�� �� ֵ: ��
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
	else	/* ��0���� */
	{
		AD_OS2_0();
		AD_OS1_0();
		AD_OS0_0();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: ad7606_StartConv
*	����˵��: ����AD7606��ADCת��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ad7606_StartConv(void)
{
	/* �����ؿ�ʼת�����͵�ƽ����ʱ������25ns  */
	AD_CONVST_LOW();
	AD_CONVST_LOW();
	AD_CONVST_LOW();	/* ����ִ��2�Σ��͵�ƽԼ50ns */
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
*	�� �� ��: ad7606_ReadBytes
*	����˵��: ��ȡAD7606�Ĳ������
*	��    �Σ�
*	�� �� ֵ: ��
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
*	�� �� ��: ad7606_IRQSrc
*	����˵��: ��ʱ���ñ����������ڶ�ȡADת��������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ad7606_IRQSrc(void)
{
	uint8_t i=0;
	
	//��ʱ��������
	AD_CS_LOW();
	for ( i=0; i<8; i++ ) {
		G_conv_data[i] = ad7606_ReadBytes();
	}
	AD_CS_HIGH();
	ad7606_StartConv();//ת����ʼ�ź�
//	Serial_Send(Serial1, "Convert result:%d\t", G_conv_data[1]);
}

/*
*********************************************************************************************************
*	�� �� ��: Get_AD7606_voltdata
*	����˵��: ��ʱ���ñ����������ڶ�ȡADת��������
*	��    �Σ�num ��ȡͨ��
*	�� �� ֵ: ���ص�ѹֵ(mV)
*********************************************************************************************************
*/
float Get_AD7606_voltdata(uint8_t num)
{
	/***********************************************
	*ʵ������range��30-32728(0-10V)
	***********************************************/
	float volt_data = (G_conv_data[num]-30)*0.305548;
	
	return volt_data;
}


