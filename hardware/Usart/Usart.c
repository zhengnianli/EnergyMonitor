/*
*********************************************************************************************************
*	                                  
*	
*	文件名称 : usart.c
*	说    明 : 系统调试串口驱动，简化函数数量，防止串口发送陷入死循环
*
*********************************************************************************************************
*/
#include "usart.h"

unsigned char  http_response[MAX_RCV_LEN];//接收缓冲区 声明为静态变量，防止堆栈溢出
volatile unsigned int   http_response_len = 0;


/*

*********************************************************************************************************
* 函 数 名：USART0_Init
* 功能说明：串口0初始化配置
* 形    参：Baudrate(波特率)
* 返 回 值：无
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
* 函 数 名：UART0_Init
* 功能说明：串口0初始化配置
* 形    参：Baudrate(波特率)
* 返 回 值：无
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
   
   /*发送区FIFO阀值设定为0 empty*/
    USART_TFITLConfig(HT_UART0, USART_TFITL_00);
    USART_TxCmd(HT_UART0, ENABLE);

    /*接收区FIFO阀值设定为1 empty*/
    USART_RFITLConfig(HT_UART0, USART_RFITL_01);
    /*使能打开接收中断*/
    USART_IntConfig(HT_UART0, USART_IER_RDAIE, ENABLE);
    /*接收机中断保护，FIFO超时中断使能*/
    HT_UART0->TPR = 0x80 | 40;
    USART_RxCmd(HT_UART0, ENABLE);
  
    NVIC_EnableIRQ(UART0_IRQn);

    /*设置中断优先级，中断优先级分组为：2：2 抢占优先级为：0  子优先级为：0 */
    NVIC_SetPriority(UART0_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 0, 0));
}

/*
*********************************************************************************************************
* 函 数 名：USART01 Init
* 功能说明：串口1初始化配置
* 形    参：Baudrate(波特率)
* 返 回 值：无
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

    /*定义485控制引脚*/
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
   
   /*发送区FIFO阀值设定为0 empty*/
    USART_TFITLConfig(HT_USART1, USART_TFITL_00);
   USART_TxCmd(HT_USART1, ENABLE);

    /*接收区FIFO阀值设定为1 empty*/
    USART_RFITLConfig(HT_USART1, USART_RFITL_01);
    /*使能打开接收中断*/
    USART_IntConfig(HT_USART1, USART_IER_RDAIE, ENABLE);
    /*接收机中断保护，FIFO超时中断使能*/
     HT_USART1->TPR = 0x80 | 40;
    USART_RxCmd(HT_USART1, ENABLE);
  
    NVIC_EnableIRQ(USART1_IRQn);

    /*设置中断优先级，中断优先级分组为：2：2 抢占优先级为：0  子优先级为：0 */
    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 1, 1));
    	
}

/*
*********************************************************************************************************
* 函 数 名：UART1_Init
* 功能说明：串口1初始化配置
* 形    参：Baudrate(波特率)
* 返 回 值：无
* 描述:  用于HMI串口屏   波特率设置为2400
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
   
   /*发送区FIFO阀值设定为0 empty*/
    USART_TFITLConfig(HT_UART1, USART_TFITL_00);
    USART_TxCmd(HT_UART1, ENABLE);

    /*接收区FIFO阀值设定为1 empty*/
    USART_RFITLConfig(HT_UART1, USART_RFITL_01);
    /*使能打开接收中断*/
    USART_IntConfig(HT_UART1, USART_IER_RDAIE, ENABLE);
    /*接收机中断保护，FIFO超时中断使能*/
    HT_UART1->TPR = 0x80 | 40;
    USART_RxCmd(HT_UART1, ENABLE);
  
    NVIC_EnableIRQ(UART1_IRQn);

    /*设置中断优先级，中断优先级分组为：2：2 抢占优先级为：0  子优先级为：0 */
    NVIC_SetPriority(UART1_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 0, 1));
}

/********************************************************************************************************
**	函 数 名 : void UART0_IRQHandler(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : WiFi接收中断服务函数
**	形    参 ： void
**	返 回 值 : void
**  说    明 ：
*******************************************************************************************************/
void UART0_IRQHandler(void)
{
	//printf("进入串口接收中断函数\r\n" );
	if (((HT_UART0->IIR) & USART_IID_RDA ) == USART_IID_RDA )
	{
		http_response[http_response_len++]=USART_ReceiveData(HT_UART0); 
	}	
}
/*
*  @brief USART2串口接收状态初始化
*/
// void USART1_Clear(void)
// {
// 		memset(usart1_rcv_buf, 0, sizeof(usart1_rcv_buf));
//     usart1_rcv_len = 0;
// }

/********************************************************************************************************
**	函 数 名 : void UART0_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : UART0串口，WIFI多字节发送
**	形    参 ： USARTx: 串口号
                *Data:  发送的数据
								len:     数据长度
**	返 回 值 : void
**  说    明 ：
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
**	函 数 名 : void USART1_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : USART1串口，水表485多字节发送
**	形    参 ： USARTx: 串口号
                *Data:  发送的数据
								len:     数据长度
**	返 回 值 : void
**  说    明 ：
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
**	函 数 名 : void SendCmd(char* cmd, char* result, int timeOut)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : UART0串口发送AT命令用
**	形    参 ： cmd  AT命令
                result 预期的正确返回信?
								timeOut延时时间,ms
**	返 回 值 : void
**  说    明 ：
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
		if((NULL != strstr((const char *)http_response, result)))	//判断是否有预期的结果
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
//  *  @brief 返回USART2已接收的数据长度
//  */
// unsigned int USART1_GetRcvNum(void)
// {
//     return usart1_rcv_len;
// }

// /*
//  *  @brief 返回USART2已接收的数据到buf，长度为rcv_len
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


