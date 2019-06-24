/*
*********************************************************************************************************
*
*
*  文件：HMI.c
*  注意：波特率必须配置为9600！！！
*  主机向串口屏发送数据要经过两个重要步骤:（1）发送串口指令；（2）发送结束符 
*
*********************************************************************************************************
*/

#include "config.h"
char HMI_Cmd=0;
unsigned char ELE_Flag;    //开断电标志位，0为断，1为开
unsigned char Water_Flag;  //开断水标志位，0为断，1为开

char ELE_Str0[2];
char ELE_Str1[2];

char Water_Str0[2];
char Water_Str1[2];

unsigned char HMI_response_len=0;				// 串口接收数据数组的长度
unsigned char HMI_response[32];	    // 串口接收缓冲数组

unsigned char HMI_ssid[32];
unsigned char HMI_password[32];

unsigned char HMI_Pkt[64];


/********************************************************************************************************
**	函 数 名 : HMISendStart
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 为确保串口HMI正常通信
**	形    参 ：无
**	返 回 值 : 无
**  说    明 ：
*******************************************************************************************************/
void HMISendStart(void)
{
	delay_ms(200);
	HMISendByte(0xff);
	delay_ms(200);
}
/********************************************************************************************************
**	函 数 名 : HMISendStr
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 向串口屏发送字符串 
**	形    参 ：*buf
**	返 回 值 : 无
**  说    明 ：
*******************************************************************************************************/
void HMISendStr(char *buf)
{
	uint8 i=0;
	while(1)
	{
		if(buf[i]!=0)
		{	
			USART_SendData(HT_UART1, buf[i]);  //发送一个字节
			while (USART_GetLineStatus(HT_UART1, USART_LSR_TE) == RESET){};//等待发送结束
			i++;
		}
		else
			return;
	}
}
/********************************************************************************************************
**	函 数 名 : HMISendByte
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 向串口发送字节 
**	形    参 ：k
**	返 回 值 : 无
**  说    明 ：
*******************************************************************************************************/
void HMISendByte(uint8 k)
{
	uint8 i;
	for(i=0;i<3;i++)
	{
		if(k!=0)
		{
			USART_SendData(HT_UART1, k);  //发送一个字节
			while (USART_GetLineStatus(HT_UART1, USART_LSR_TE) == RESET){};//等待发送结束
		}
		else
			return;
	}
}

/********************************************************************************************************
**	函 数 名 : void UART1_IRQHandler(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 
**	形    参 ： void
**	返 回 值 : void
**  说    明 ：
*******************************************************************************************************/
void UART1_IRQHandler(void)
{
//     unsigned char i;
//      printf("进入串口接收中断函数\r\n" );
    if (((HT_UART1->IIR) & USART_IID_RDA ) == USART_IID_RDA )
    {
		HMI_response[HMI_response_len++]=USART_ReceiveData(HT_UART1); 
		HMI_Cmd=USART_ReceiveData(HT_UART1); 
    }
// 	printf("HMI_Cmd=%X\r\n",HMI_Cmd);
  
	switch(HMI_Cmd)
	{
		case 1:
			ELE_Flag=1;
			if(Modeflag==1)
			{
				HT_GPIOC->RR = GPIO_PIN_5;  
			}
			break;
			
		case 2:
			ELE_Flag=0;
			if(Modeflag==1)
			{
				HT_GPIOC->SRR = GPIO_PIN_5;  
			}
			break;
			
		case 3:
			Water_Flag=1;
			if(Modeflag==1)
			{
				HT_GPIOC->RR = GPIO_PIN_4;  
			}
			break;
			
		case 4:
			Water_Flag=0;
			if(Modeflag==1)
			{
				HT_GPIOC->SRR = GPIO_PIN_4;  
			}
			break;
			
		case 5:
			Modeflag=1;
			break;
		// 		case 6:
		// 			if(ELE_Flag==1)
		// 			{
		//        	for(i=0;i<2;i++)
		// 		 {
		//   		sprintf(ELE_Str1,"%s", "1");
		// 		  OneNet_Post("ACSwitch",ELE_Str1);
		// 		  Sket_Delayms(10);
		// 		 }
		//       }
		// 			if(ELE_Flag==0)
		// 			{
		//        for(i=0;i<2;i++)
		// 		 {
		// 		   sprintf(ELE_Str0,"%s", "0");
		// 		   OneNet_Post("ACSwitch",ELE_Str0);
		// 			 Sket_Delayms(10);
		// 		
		// 		 } 
		//       }
		//      if (Water_Flag==1)	
		//      {
		// 			  for(i=0;i<2;i++)
		// 		 {
		// 		  sprintf(Water_Str1,"%s", "1");
		// 		  OneNet_Post("Switchwater",Water_Str1);
		// 		  Sket_Delayms(10);
		// 		 }	
		//      }	
		//      if(Water_Flag==0)	
		//      {
		//       for(i=0;i<2;i++)
		// 		{
		// 		  sprintf(Water_Str1,"%s", "0");
		// 		  OneNet_Post("Switchwater",Water_Str1);
		// 		  Sket_Delayms(10);
		// 		}
		//      }	
		//       Sket_Delayms(100);	 
		//   			Modeflag=0;
		// 		  break;
		default:
		break;
	}
  
}

/********************************************************************************************************
**	函 数 名 : void HMI_getwifi()
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 解析用户名和密码
**	形    参 ：无
**	返 回 值 : 无
**  说    明 ：
*******************************************************************************************************/
void HMI_getwifi(void)
{
	memset(HMI_Pkt,0,sizeof(HMI_Pkt));
	HMISendStr("rept 0,20");
	HMISendByte(0xff);	
	delay_ms(100);	
	if(HMI_response_len > 0)
	{
		sprintf(HMI_ssid,"\"%s\"",HMI_response);
		//printf("ssid:%s\r\n",HMI_ssid);     // 打印接收到的数据 	
		HMI_response_len=0;
		memset(HMI_response,0,sizeof(HMI_response));
	}	
	delay_ms(100);	
	HMISendStr("rept 50,20");
	HMISendByte(0xff);	
	delay_ms(100);	
	if(HMI_response_len > 0)
	{
		sprintf(HMI_password,"\"%s\"",HMI_response);
		//printf("password:%s\r\n",HMI_response);     // 打印接收到的数据 
		HMI_response_len=0;
		memset(HMI_response,0,sizeof(HMI_response));
	}	
	delay_ms(100);	
	strcat(HMI_Pkt, "AT+CWJAP=");
	strcat(HMI_Pkt,HMI_ssid);
	strcat(HMI_Pkt,",");
	strcat(HMI_Pkt,HMI_password);
	strcat(HMI_Pkt,"\r\n");
	//printf("%s\r\n",HMI_Pkt);     // 打印接收到的数据 
	delay_ms(100);	
}

/********************************************************************************************************
**	函 数 名 : void get_dianneng(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 获取电能
**	形    参 ：无
**	返 回 值 : 无
**  说    明 ：
*******************************************************************************************************/
void get_dianneng(void)
{
	memset(HMI_Pkt,0,sizeof(HMI_Pkt));
	HMISendStr("rept 80,10");
	HMISendByte(0xff);	
	delay_ms(100);	
	if(HMI_response_len > 0)
	{
		Qa=atof(HMI_response);
		printf("电能:%0.2f\r\n",Qa);     // 打印接收到的数据 			
		HMI_response_len=0;
		memset(HMI_response,0,sizeof(HMI_response));
	}	
	delay_ms(100);	
}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/

