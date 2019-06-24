/*
*********************************************************************************************************
*
*
*  �ļ���HMI.c
*  ע�⣺�����ʱ�������Ϊ9600������
*  �����򴮿�����������Ҫ����������Ҫ����:��1�����ʹ���ָ���2�����ͽ����� 
*
*********************************************************************************************************
*/

#include "config.h"
char HMI_Cmd=0;
unsigned char ELE_Flag;    //���ϵ��־λ��0Ϊ�ϣ�1Ϊ��
unsigned char Water_Flag;  //����ˮ��־λ��0Ϊ�ϣ�1Ϊ��

char ELE_Str0[2];
char ELE_Str1[2];

char Water_Str0[2];
char Water_Str1[2];

unsigned char HMI_response_len=0;				// ���ڽ�����������ĳ���
unsigned char HMI_response[32];	    // ���ڽ��ջ�������

unsigned char HMI_ssid[32];
unsigned char HMI_password[32];

unsigned char HMI_Pkt[64];


/********************************************************************************************************
**	�� �� �� : HMISendStart
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : Ϊȷ������HMI����ͨ��
**	��    �� ����
**	�� �� ֵ : ��
**  ˵    �� ��
*******************************************************************************************************/
void HMISendStart(void)
{
	delay_ms(200);
	HMISendByte(0xff);
	delay_ms(200);
}
/********************************************************************************************************
**	�� �� �� : HMISendStr
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : �򴮿��������ַ��� 
**	��    �� ��*buf
**	�� �� ֵ : ��
**  ˵    �� ��
*******************************************************************************************************/
void HMISendStr(char *buf)
{
	uint8 i=0;
	while(1)
	{
		if(buf[i]!=0)
		{	
			USART_SendData(HT_UART1, buf[i]);  //����һ���ֽ�
			while (USART_GetLineStatus(HT_UART1, USART_LSR_TE) == RESET){};//�ȴ����ͽ���
			i++;
		}
		else
			return;
	}
}
/********************************************************************************************************
**	�� �� �� : HMISendByte
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : �򴮿ڷ����ֽ� 
**	��    �� ��k
**	�� �� ֵ : ��
**  ˵    �� ��
*******************************************************************************************************/
void HMISendByte(uint8 k)
{
	uint8 i;
	for(i=0;i<3;i++)
	{
		if(k!=0)
		{
			USART_SendData(HT_UART1, k);  //����һ���ֽ�
			while (USART_GetLineStatus(HT_UART1, USART_LSR_TE) == RESET){};//�ȴ����ͽ���
		}
		else
			return;
	}
}

/********************************************************************************************************
**	�� �� �� : void UART1_IRQHandler(void)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : 
**	��    �� �� void
**	�� �� ֵ : void
**  ˵    �� ��
*******************************************************************************************************/
void UART1_IRQHandler(void)
{
//     unsigned char i;
//      printf("���봮�ڽ����жϺ���\r\n" );
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
**	�� �� �� : void HMI_getwifi()
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : �����û���������
**	��    �� ����
**	�� �� ֵ : ��
**  ˵    �� ��
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
		//printf("ssid:%s\r\n",HMI_ssid);     // ��ӡ���յ������� 	
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
		//printf("password:%s\r\n",HMI_response);     // ��ӡ���յ������� 
		HMI_response_len=0;
		memset(HMI_response,0,sizeof(HMI_response));
	}	
	delay_ms(100);	
	strcat(HMI_Pkt, "AT+CWJAP=");
	strcat(HMI_Pkt,HMI_ssid);
	strcat(HMI_Pkt,",");
	strcat(HMI_Pkt,HMI_password);
	strcat(HMI_Pkt,"\r\n");
	//printf("%s\r\n",HMI_Pkt);     // ��ӡ���յ������� 
	delay_ms(100);	
}

/********************************************************************************************************
**	�� �� �� : void get_dianneng(void)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : ��ȡ����
**	��    �� ����
**	�� �� ֵ : ��
**  ˵    �� ��
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
		printf("����:%0.2f\r\n",Qa);     // ��ӡ���յ������� 			
		HMI_response_len=0;
		memset(HMI_response,0,sizeof(HMI_response));
	}	
	delay_ms(100);	
}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/

