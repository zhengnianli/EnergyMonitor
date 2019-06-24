/*
*********************************************************************************************************
*	                                  
*	
*	�ļ����� : spi.c
*	˵    �� : 
*
*********************************************************************************************************
*/
#include "spi.h"

//-----------------------------------------------------------------------------------
//SPI�����Ŷ���   ע��SPIΪ���ýӿ�CS���Զ���
#define  SPI1_SCLK_PIN 		    (GPIO_PIN_7)
#define  SPI1_MOSI_PIN 			(GPIO_PIN_8)
#define  SPI1_MISO_PIN			(GPIO_PIN_9)

#define  SPI1_SCLK_AFIO_PIN 	(AFIO_PIN_7)
#define  SPI1_MOSI_AFIO_PIN 	(AFIO_PIN_8)
#define  SPI1_MISO_AFIO_PIN	    (AFIO_PIN_9)

//�ӻ�ѡ����
#define  SPI1_SEL_GPIO_IB	    (GPIO_PB)
#define  SPI1_SEL_PIN 			(GPIO_PIN_6)


/*******************************************************************************************************
** ����: SPI1_Init��ʼ��
**------------------------------------------------------------------------------------------------------
** ����: NONE 
** ����: NONE
*******************************************************************************************************/
void SPI1_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	/* Configure Clock */
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.SPI1         = 1;
    CKCUClock.Bit.AFIO         = 1;
	  CKCUClock.Bit.PB           = 1;
// 	  CKCUClock.Bit.PE           = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /*  Configure SPI SEL pin (PD13)*/
    GPIO_SetOutBits(GPIO_PORT[SPI1_SEL_GPIO_IB], SPI1_SEL_PIN);
    GPIO_DirectionConfig(GPIO_PORT[SPI1_SEL_GPIO_IB], SPI1_SEL_PIN, GPIO_DIR_OUT);
	/* Configure AFIO mode of SCLK��MISO��MOSI*/
 	 AFIO_GPxConfig(GPIO_PB, SPI1_SCLK_AFIO_PIN, AFIO_FUN_SPI);
	AFIO_GPxConfig(GPIO_PB, SPI1_MOSI_AFIO_PIN, AFIO_FUN_SPI);
	AFIO_GPxConfig(GPIO_PB, SPI1_MISO_AFIO_PIN, AFIO_FUN_SPI);

	  /* SPI Configuration  */
	  SPI_InitStructure.SPI_Mode = SPI_MASTER ;
    SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
    SPI_InitStructure.SPI_DataLength =SPI_DATALENGTH_8;
    SPI_InitStructure.SPI_SELMode = SPI_SEL_SOFTWARE ;
  	SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW ;
    SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_LOW;   //ʱ�Ӽ��ԣSCK �߿���״̬Ϊ�͵�ƽ��
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_SECOND; //ʱ����λ�����ݻ��ڵ�2�� SCK ʱ��ת��ʱ������
    SPI_InitStructure.SPI_RxFIFOTriggerLevel = 0;
    SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
    SPI_InitStructure.SPI_ClockPrescaler = 1;
    SPI_Init(HT_SPI1, &SPI_InitStructure);
	//SEL���ʹ��
	SPI_SELOutputCmd(HT_SPI1, ENABLE);
	//ʹ��SPI1
	SPI_Cmd(HT_SPI1, ENABLE);
}
/*******************************************************************************************************
** ����: SPI1_SendByte, SPI����һ���ֽڣ�ͬʱ����һ���ֽ�
**------------------------------------------------------------------------------------------------------
** ����: byte �������� 
** ����: ��������
*******************************************************************************************************/
u16 SPI1_ReadWrite(u8 dat)
{
  /* Loop while Tx buffer register is empty                                                                 */
  while (!SPI_GetFlagStatus(HT_SPI1, SPI_FLAG_TXBE));

  /* Send byte through the SPI1 peripheral                                                                  */
  SPI_SendData(HT_SPI1, dat);

  /* Loop while Rx is not empty                                                                             */
  while (!SPI_GetFlagStatus(HT_SPI1, SPI_FLAG_RXBNE));

  /* Return the byte read from the SPI                                                                      */
  return SPI_ReceiveData(HT_SPI1);
}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/

