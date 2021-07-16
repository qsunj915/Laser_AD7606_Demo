/**
  ******************************************************************************
  * @file    drv_spi.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-02-23
  * @brief   deive for hardware spi
  ******************************************************************************
  */
	
#include "drv_spi.h"

/** Ӳ��SPI */
#define SPI_WAIT_TIMEOUT			((uint16_t)0x00FF)

/**
  * @brief :SPI��ʼ��(Ӳ��)
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void drv_spi_init( void )
{
	SPI_InitTypeDef		SpiInitStructer;
	
	/** SPI�������� */	
	GPIO_Format_Init(GPIOA,SPI_CLK_GPIO_PIN | SPI_MISO_GPIO_PIN | SPI_MOSI_GPIO_PIN ,GPIO_Mode_AF\
					,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_50MHz);	

	GPIO_PinAFConfig(SPI_CLK_GPIO_PORT,GPIO_PinSource5,GPIO_AF_SPI1);	//PA5����Ϊ SPI1
	GPIO_PinAFConfig(SPI_MISO_GPIO_PORT,GPIO_PinSource6,GPIO_AF_SPI1);	//PA6����Ϊ SPI1
	GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT,GPIO_PinSource7,GPIO_AF_SPI1);	//PA7����Ϊ SPI1
	GPIO_SetBits( SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN );
	
	//NSS����Ϊ�������
	GPIO_Format_Init(GPIOA, SPI_NSS_GPIO_PIN,GPIO_Mode_OUT\
					,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_50MHz);
	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN );				//�ø�

	/** SPI���� */
	SPI_I2S_DeInit( SPI_PORT );			//��λSPI
	RCC_APB2PeriphClockCmd( SPI_PORT_CLK, ENABLE );			//SPI1��APB2�ϣ�����ӦSPIʱ��
	SPI_Cmd( SPI_PORT, DISABLE );		//�ر�SPI���裬����ǰ�ر�
	
	//AD7607 SPI����
	SpiInitStructer.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;		//˫��ȫ˫��
	SpiInitStructer.SPI_Mode              = SPI_Mode_Master;						//����ģʽ
	SpiInitStructer.SPI_CPOL              = SPI_CPOL_High;							//����״̬Ϊ�͵�ƽ 
	SpiInitStructer.SPI_CPHA              = SPI_CPHA_1Edge;							//��һ�����زɼ�����
	SpiInitStructer.SPI_DataSize          = SPI_DataSize_16b;						//16λ����
	SpiInitStructer.SPI_NSS               = SPI_NSS_Soft;							//�ӻ��������
	SpiInitStructer.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;				//4��Ƶ
	SpiInitStructer.SPI_FirstBit          = SPI_FirstBit_MSB;						//���λ�ȷ���
	SpiInitStructer.SPI_CRCPolynomial     = 7;										//CRC����ʽ,Ĭ�ϲ�ʹ��SPI�Դ�CRC	 
	
	SPI_Init( SPI_PORT, &SpiInitStructer );
	SPI_Cmd( SPI_PORT, ENABLE );
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint16_t Ex_drv_spi_read_write_byte( void )
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

uint16_t drv_spi_read_write_byte( uint16_t TxByte )
{
	uint16_t l_Data = 0;
	uint16_t l_WaitTime = 0;
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_TXE ) )		//�ȴ����ͻ�����Ϊ��
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	l_WaitTime = SPI_WAIT_TIMEOUT / 2;		//�������ý��յȴ�ʱ��(��ΪSPI���ٶȺܿ죬����������ڷ������֮��������յ����ݣ��ȴ�ʱ�䲻��Ҫ����)
	SPI_PORT->DR = TxByte;	//��������
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_RXNE ) )		//�ȴ����ջ������ǿ�
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	
	l_Data = (uint16_t)SPI_PORT->DR;		//��ȡ��������
	
	return l_Data;		//����
}


/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:��
  */
void Ex_drv_spi_read_write_string( uint16_t* ReadBuffer, uint16_t* WriteBuffer, uint16_t Length )
{
	GPIO_ResetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);	  		//����Ƭѡ
	while( Length-- )
	{
		*ReadBuffer = Ex_drv_spi_read_write_byte(  );		//�շ�����
		ReadBuffer++;
		WriteBuffer++;			                                    	//��д��ַ��1
	}
	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				  //����Ƭѡ
}

/** Ӳ��SPI */



