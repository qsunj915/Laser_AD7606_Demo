/**
  ******************************************************************************
  * @file    bsp_ad7606.c
  * @author  qsunj
  * @version test
  * @date    21-7-15
  * @brief   ��ֲ��ע���еĶ�ʱ�����ˣ�����TIM2����TIM4
  ******************************************************************************
  */

#include "bsp_ad7606.h"

FIFO_T	g_tAD;	/* ����һ�����������������ڴ洢AD�ɼ����ݣ�������д��SD�� */

void bsp_TIM4_Configuration(void);

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
//	SPI_InitTypeDef   SPI_InitStructure;
	
	/* AD_SPI_CS_GPIO, AD_SPI_MOSI_GPIO, AD_SPI_MISO_GPIO, AD_SPI_DETECT_GPIO 
	   and AD_SPI_SCK_GPIO Periph clock enable */
	//drv_spi_init����
//	RCC_APB2PeriphClockCmd(AD_CS_GPIO_CLK | AD_SPI_MISO_GPIO_CLK | AD_SPI_SCK_GPIO_CLK
//			, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = AD_SPI_SCK_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(AD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = AD_CS_PIN;
//	GPIO_Init(AD_CS_GPIO_PORT, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = AD_SPI_MISO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
//	GPIO_Init(AD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
	/* ����������GPIO */

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
*	�� �� ��: bsp_TIM4_Configuration
*	����˵��: ����TIM4��ʱ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_TIM4_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  

	/* Configure the NVIC Preemption Priority Bits[�������ȼ���] */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the TIM2 gloabal Interrupt [����TIM2ȫ���ж�]*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
	
/*
*********************************************************************************************************
*	�� �� ��: bsp_SET_TIM4_FREQ
*	����˵��: ����TIM4��ʱ��Ƶ��
*	��    �Σ�_ulFreq : ����Ƶ�ʣ���λHz��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_SET_TIM4_FREQ(uint32_t _ulFreq)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint16_t usPrescaler;
	uint16_t usPeriod;

	TIM_DeInit(TIM4);	/* ��λTIM2��ʱ�� */

	/* TIM2 configuration 
		TIM2CLK = 36 MHz	
	*/
	if (_ulFreq == 0)
	{
		return;		/* ����Ƶ��Ϊ0��ֹͣ���� */
	}
	else if (_ulFreq <= 100)   /* ����Ƶ��С��100Hz */
	{
		usPrescaler = 36000;		/* TM2CLK = 72 000 000/36000 = 2000 */
		usPeriod = 2000 / _ulFreq;			 	
	}
	else if (_ulFreq <= 200000)	/* ����Ƶ�� ��100Hz - 200kHz */
	{
		usPrescaler = 36 - 1;		/* TM2CLK = 36 000 000/36 = 2 000 000 */
		usPeriod = 2000000 / _ulFreq;
	}	
	else	/* ����Ƶ�ʴ��� 200kHz */
	{
		return;
	}
	
	TIM_TimeBaseStructure.TIM_Period = usPeriod - 1; 		/* �������� */
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;	/* ��Ƶϵ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 		/* */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //�����������ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* Clear TIM2 update pending flag[���TIM2����жϱ�־] */
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	TIM_SetCounter(TIM4, 0);

	/* Enable TIM2 Update interrupt [TIM2����ж�����]*/
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  

	/* TIM2 enable counter [����tim2����]*/
	TIM_Cmd(TIM4, ENABLE);
} 

//SPIд����
//������ICд��1byte����    
//num:Ҫд�������
/**********************************************************
void SPI_SendData(u16 data)    
{  
	u8 count=0;   
	AD_SCK_LOW();	//�½�����Ч
	for(count=0;count<16;count++)  
	{ 	  
		if(data&0x8000)
			AD_MISO_LOW();  
		else 
			AD_MISO_HIGH();   
		data<<=1;    
		AD_SCK_LOW(); 	 
		AD_CSK_HIGH();		//��������Ч	        
	}		 			    
} 		 
*************************************************************/
//SPI������ 
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������	   
//u16 SPI_ReceiveData(void)	  
//{ 	 
//	u8 count=0; 	  
//	u16 Num=0; 
//	AD_SCK_LOW();		//������ʱ�� 	 	     	    
//	for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч 
//	{ 				  
//		Num<<=1; 	 
//		AD_SCK_LOW();	//�½�����Ч  	    	   
//		AD_CSK_HIGH();
//		
//		if(AD_MISO_IN)Num++;
//	}
//	return(Num);
//}
/*************************************************************
u16 SPI_ReceiveData(void)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	AD_CSK_HIGH();	
	for(count=0;count<16;count++)//����16λ����
	{
		Num<<=1;
		AD_SCK_LOW();	//�½�����Ч
		if(AD_MISO_IN)Num++;
		AD_CSK_HIGH();
	}
	return(Num);
}
*************************************************************/
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
	
//	usData = SPI_ReceiveData();
//	usData = Ex_drv_spi_read_write_byte();
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
	uint8_t i;
	uint16_t usReadValue;

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	/* ��ȡ���� 
	ʾ������⣬CS�͵�ƽ����ʱ�� 35us 
	*/
	AD_CS_LOW();
	for (i = 0; i < CH_NUM; i++)
	{
		usReadValue = ad7606_ReadBytes();	
		if (g_tAD.usWrite < FIFO_SIZE)
		{
			g_tAD.usBuf[g_tAD.usWrite] = usReadValue;
			++g_tAD.usWrite;
		}
	}		
	
	AD_CS_HIGH();
//	g_tAD.usWrite = 0;
	ad7606_StartConv();
}

/*
*********************************************************************************************************
*	�� �� ��: GetAdcFormFifo
*	����˵��: ��FIFO�ж�ȡһ��ADCֵ
*	��    �Σ�_usReadAdc : ���ADC����ı���ָ��
*	�� �� ֵ: 1 ��ʾOK��0��ʾ��������
*********************************************************************************************************
*/
uint8_t GetAdcFormFifo(uint16_t *_usReadAdc)
{
	uint16_t usWrite;
	
	DISABLE_INT();	
	usWrite = g_tAD.usWrite;
	ENABLE_INT();
	
	if (usWrite != g_tAD.usRead)
	{
		*_usReadAdc = g_tAD.usBuf[g_tAD.usRead];

		DISABLE_INT();
		if (++g_tAD.usRead >= FIFO_SIZE)
		{
			g_tAD.usRead = 0;
		}		
		ENABLE_INT();
		return 1;		
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: ad7606_StartRecord
*	����˵��: ��ʼ�ɼ�
*	��    �Σ�_ulFreq : ����Ƶ��, ��λ HZ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ad7606_StartRecord(uint32_t _ulFreq)
{
	//ad7606_Reset();	/* ��λӲ�� */

	ad7606_StartConv();				/* ���������������1������ȫ0������ */

	g_tAD.usRead = 0;				/* �����ڿ���TIM2֮ǰ��0 */
	g_tAD.usWrite = 0;

	bsp_TIM4_Configuration();		/* ����TIM2��ʱ�ж� */		

	bsp_SET_TIM4_FREQ(_ulFreq);		/* ���ò���Ƶ��, ��ʹ��TIM2��ʱ�����ж� */
}

/*
*********************************************************************************************************
*	�� �� ��: ad7606_StopRecord
*	����˵��: ֹͣ�ɼ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ad7606_StopRecord(void)
{
	/* TIM2 enable counter [����tim2����]*/
	TIM_Cmd(TIM4, DISABLE);
}

