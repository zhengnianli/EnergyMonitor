/*
*********************************************************************************************************
*	                                  
*	
*	�ļ����� : usart.c
*	˵    �� : ϵͳ���Դ����������򻯺�����������ֹ���ڷ���������ѭ��
*
*********************************************************************************************************
*/
#include "usart.h"

unsigned char  http_response[MAX_RCV_LEN];//���ջ����� ����Ϊ��̬��������ֹ��ջ���
volatile unsigned int   http_response_len = 0;


/*

*********************************************************************************************************
* �� �� ����USART0_Init
* ����˵��������0��ʼ������
* ��    �Σ�Baudrate(������)
* �� �� ֵ����
*********************************************************************************************************
*/
void USART0_Init(unsigned long Baudrate)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    USART_InitTypeDef USART_InitStructure;

    /* Enable peripheral clock of AFIO, USART0                                                                */
    CKCUClock.Bit.AFIO   = 1;
    CKCUClock.Bit.USART0 = 1;
    CKCUClock.Bit.PA    = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
    
     // Configure AFIO mode of output pins
// 	  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_6, AFIO_MODE_DEFAULT);
//     GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_6, GPIO_DIR_OUT);

    /* Config AFIO mode as USART0_Rx and USART0_Tx function.                                                  */
    AFIO_GPAConfig(AFIO_PIN_2 | AFIO_PIN_3, AFIO_MODE_6);     // TX (PA2), RX (PA3)
   
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

    USART_Init(HT_USART0, &USART_InitStructure);
    USART_TxCmd(HT_USART0, ENABLE);
    USART_RxCmd(HT_USART0, ENABLE);
}
/*
*********************************************************************************************************
* �� �� ����UART0_Init
* ����˵��������0��ʼ������
* ��    �Σ�Baudrate(������)
* �� �� ֵ����
*********************************************************************************************************
*/
void UART0_Init(unsigned long Baudrate1)
{
	  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    USART_InitTypeDef USART_InitStructure;

    /* Enable peripheral clock of AFIO, UART0                                                                */
    CKCUClock.Bit.AFIO   = 1;
    CKCUClock.Bit.UART0  = 1;
    CKCUClock.Bit.PC    = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

//      // Configure AFIO mode of output pins
//   	AFIO_GPxConfig(GPIO_PC, AFIO_PIN_11, AFIO_MODE_DEFAULT);
//    //Configure GPIO direction of output pins 
// 	 GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_OUT);
// 	 HT_GPIOC->SRR = GPIO_PIN_11;

    /* Config AFIO mode as USART0_Rx and USART0_Tx function.                                                  */
    AFIO_GPCConfig(AFIO_PIN_9 | AFIO_PIN_10, AFIO_MODE_6);     // TX (PB2), RX (PB3)

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

    USART_Init(HT_UART0, &USART_InitStructure);
    USART_FIFOReset(HT_UART0, USART_FIFO_TX | USART_FIFO_RX);
   
   /*������FIFO��ֵ�趨Ϊ0 empty*/
    USART_TFITLConfig(HT_UART0, USART_TFITL_00);
    USART_TxCmd(HT_UART0, ENABLE);

    /*������FIFO��ֵ�趨Ϊ1 empty*/
    USART_RFITLConfig(HT_UART0, USART_RFITL_01);
    /*ʹ�ܴ򿪽����ж�*/
    USART_IntConfig(HT_UART0, USART_IER_RDAIE, ENABLE);
    /*���ջ��жϱ�����FIFO��ʱ�ж�ʹ��*/
    HT_UART0->TPR = 0x80 | 40;
    USART_RxCmd(HT_UART0, ENABLE);
  
    NVIC_EnableIRQ(UART0_IRQn);

    /*�����ж����ȼ����ж����ȼ�����Ϊ��2��2 ��ռ���ȼ�Ϊ��0  �����ȼ�Ϊ��0 */
    NVIC_SetPriority(UART0_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 0, 0));
}

/*
*********************************************************************************************************
* �� �� ����USART01 Init
* ����˵��������1��ʼ������
* ��    �Σ�Baudrate(������)
* �� �� ֵ����
*********************************************************************************************************
*/
void USART1_Init(unsigned long Baudrate2)
{
	  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    USART_InitTypeDef USART_InitStructure;

    /* Enable peripheral clock of AFIO, USART0                                                                */
    CKCUClock.Bit.AFIO   = 1;
    CKCUClock.Bit.USART1 = 1;
     CKCUClock.Bit.PA    = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /*����485��������*/
     // Configure AFIO mode of output pins
	  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_6, AFIO_MODE_DEFAULT);
    GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_6, GPIO_DIR_OUT);

    /* Config AFIO mode as USART0_Rx and USART0_Tx function.                                                  */
    AFIO_GPAConfig(AFIO_PIN_4 | AFIO_PIN_5, AFIO_MODE_6);     // TX (PA2), RX (PA3)

    USART_InitStructure.USART_BaudRate = 2400;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    
    USART_Init(HT_USART1, &USART_InitStructure);
    USART_FIFOReset(HT_USART1, USART_FIFO_TX | USART_FIFO_RX);
   
   /*������FIFO��ֵ�趨Ϊ0 empty*/
    USART_TFITLConfig(HT_USART1, USART_TFITL_00);
   USART_TxCmd(HT_USART1, ENABLE);

    /*������FIFO��ֵ�趨Ϊ1 empty*/
    USART_RFITLConfig(HT_USART1, USART_RFITL_01);
    /*ʹ�ܴ򿪽����ж�*/
    USART_IntConfig(HT_USART1, USART_IER_RDAIE, ENABLE);
    /*���ջ��жϱ�����FIFO��ʱ�ж�ʹ��*/
     HT_USART1->TPR = 0x80 | 40;
    USART_RxCmd(HT_USART1, ENABLE);
  
    NVIC_EnableIRQ(USART1_IRQn);

    /*�����ж����ȼ����ж����ȼ�����Ϊ��2��2 ��ռ���ȼ�Ϊ��0  �����ȼ�Ϊ��0 */
    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 1, 1));
    	
}

/*
*********************************************************************************************************
* �� �� ����UART1_Init
* ����˵��������1��ʼ������
* ��    �Σ�Baudrate(������)
* �� �� ֵ����
* ����:  ����HMI������   ����������Ϊ2400
*********************************************************************************************************
*/
void UART1_Init(unsigned long Baudrate3)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    USART_InitTypeDef USART_InitStructure;

    /* Enable peripheral clock of AFIO, UART0                                                                */
    CKCUClock.Bit.AFIO   = 1;
    CKCUClock.Bit.UART1  = 1;
    CKCUClock.Bit.PB    = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Config AFIO mode as USART0_Rx and USART0_Tx function.                                                  */
    AFIO_GPBConfig(AFIO_PIN_4 | AFIO_PIN_5, AFIO_MODE_6);     // TX (PC2), RX (PC3)

    USART_InitStructure.USART_BaudRate = Baudrate3;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

    USART_Init(HT_UART1, &USART_InitStructure);
    USART_FIFOReset(HT_UART1, USART_FIFO_TX | USART_FIFO_RX);
   
   /*������FIFO��ֵ�趨Ϊ0 empty*/
    USART_TFITLConfig(HT_UART1, USART_TFITL_00);
    USART_TxCmd(HT_UART1, ENABLE);

    /*������FIFO��ֵ�趨Ϊ1 empty*/
    USART_RFITLConfig(HT_UART1, USART_RFITL_01);
    /*ʹ�ܴ򿪽����ж�*/
    USART_IntConfig(HT_UART1, USART_IER_RDAIE, ENABLE);
    /*���ջ��жϱ�����FIFO��ʱ�ж�ʹ��*/
    HT_UART1->TPR = 0x80 | 40;
    USART_RxCmd(HT_UART1, ENABLE);
  
    NVIC_EnableIRQ(UART1_IRQn);

    /*�����ж����ȼ����ж����ȼ�����Ϊ��2��2 ��ռ���ȼ�Ϊ��0  �����ȼ�Ϊ��0 */
    NVIC_SetPriority(UART1_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 0, 1));
}

/********************************************************************************************************
**	�� �� �� : void UART0_IRQHandler(void)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : WiFi�����жϷ�����
**	��    �� �� void
**	�� �� ֵ : void
**  ˵    �� ��
*******************************************************************************************************/
void UART0_IRQHandler(void)
{
	//printf("���봮�ڽ����жϺ���\r\n" );
	if (((HT_UART0->IIR) & USART_IID_RDA ) == USART_IID_RDA )
	{
		http_response[http_response_len++]=USART_ReceiveData(HT_UART0); 
	}	
}
/*
*  @brief USART2���ڽ���״̬��ʼ��
*/
// void USART1_Clear(void)
// {
// 		memset(usart1_rcv_buf, 0, sizeof(usart1_rcv_buf));
//     usart1_rcv_len = 0;
// }

/********************************************************************************************************
**	�� �� �� : void UART0_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : UART0���ڣ�WIFI���ֽڷ���
**	��    �� �� USARTx: ���ں�
                *Data:  ���͵�����
								len:     ���ݳ���
**	�� �� ֵ : void
**  ˵    �� ��
*******************************************************************************************************/
void UART0_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len)
{
    char i;

    for(i = 0; i < len; i++)
    {
        USART_SendData(HT_UART0, *Data++);
        while (USART_GetLineStatus(HT_UART0, USART_LSR_TE) == RESET);
    }
}


/********************************************************************************************************
**	�� �� �� : void USART1_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : USART1���ڣ�ˮ��485���ֽڷ���
**	��    �� �� USARTx: ���ں�
                *Data:  ���͵�����
								len:     ���ݳ���
**	�� �� ֵ : void
**  ˵    �� ��
*******************************************************************************************************/
void USART1_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len)
{
    char i;
 
    for(i = 0; i < len; i++)
    {
        USART_SendData(HT_USART1, *Data++);
        while (USART_GetLineStatus(HT_USART1, USART_LSR_TE) == RESET);
    }
}

/********************************************************************************************************
**	�� �� �� : void SendCmd(char* cmd, char* result, int timeOut)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : UART0���ڷ���AT������
**	��    �� �� cmd  AT����
                result Ԥ�ڵ���ȷ������?
								timeOut��ʱʱ��,ms
**	�� �� ֵ : void
**  ˵    �� ��
*******************************************************************************************************/
void SendCmd(char* cmd, char* result, int timeOut)
{
	while(1)
	{
		//USART1_Clear();
		http_response_len=0;
		memset(http_response,0,sizeof(http_response));
		UART0_Write(HT_UART0, (unsigned char *)cmd, strlen((const char *)cmd));
		Sket_Delayms(timeOut);
		printf("%s %d cmd:%s,rsp:%s\n", __func__, __LINE__, cmd, http_response);
		if((NULL != strstr((const char *)http_response, result)))	//�ж��Ƿ���Ԥ�ڵĽ��
		{
			break;
		}
		else
		{
			Sket_Delayms(100);
		}
	}		
}


// #if 1
// /*
//  *  @brief ����USART2�ѽ��յ����ݳ���
//  */
// unsigned int USART1_GetRcvNum(void)
// {
//     return usart1_rcv_len;
// }

// /*
//  *  @brief ����USART2�ѽ��յ����ݵ�buf������Ϊrcv_len
//  */
// void  USART1_GetRcvData(unsigned char *buf, unsigned int rcv_len)
// {
//     if(buf)
//     {
//         memcpy(buf, usart1_rcv_buf, rcv_len);
//     }
//     USART1_Clear();
// }
// #endif


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/


