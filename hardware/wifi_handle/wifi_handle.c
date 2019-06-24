#include "config.h"  
			 
float  temperature;	
 int Watervalue;
 int ACvalue;
 
double  Qa=0;
double  Qb=0;
float dianfei;
float shuifei;

char tempStr[5];       //�ַ�����ʽ�¶�
char humiStr[5];       //�ַ�����ʽʪ��
char U_Str[6];
char I_Str[5];
char P_Str[6];
char Q_Str[6];
char dianfei_Str[6];
char shuifei_Str[6];
	
volatile int temp4;
volatile int temp1;
volatile int temp2;
volatile int temp3;

char Store_T[5]; //�¶���ʱ�洢��
char Store_U[5]; //��ѹ��ʱ�洢��
char Store_I[5]; //������ʱ�洢��
char Store_P[10]; //������ʱ�洢��
char Store_Q[10]; //������ʱ�洢��
char Store_W[5]; //������ʱ�洢��
char Store1_Q[5]; //������ʱ�洢��

/*******************************************************************************
������   ��void BFTM0_IRQHandler(void)
����     ��BFTM0�жϷ�����
������� ����
����ֵ   ����

********************************************************************************/
void BFTM0_IRQHandler(void)
{
	BFTM_ClearFlag(HT_BFTM0);
	++temp1;
	++temp2;
	++temp3;
	++temp4;
	wifi_send_data(150);
	wifi_get_data(5);
	wifi_get_data1(6);
}

/**************************************************************************
�������ܣ��õ����ݲɼ����� 10S�ɼ�һ������
��ڲ�����time
����  ֵ����
**************************************************************************/
void Data1_refresh()
{
//  static int temp;
// 	   NVIC_DisableIRQ(BFTM0_IRQn);
	/* �¶� */	
	temperature=DS18B20_Get_Temp();
	printf("\nTemperature=%0.2lf��\n",temperature-8);
	AttGetAllVolue();

	Qb=Q+Qa;

	printf("��ѹ��%0.1f;\n",U);

	printf("������%0.3f;\n",I);

	printf("�й����ʣ�%0.3f;\n",P);

	printf("���ܣ�%0.3f;\n",Qb);

	water_get();

	/* ���ܴ��� */
	sprintf(Store1_Q,"wepo \"%0.2f\",80",Qb);
	HMISendStr(Store1_Q);
	HMISendByte(0xff);	

	dianfei=0.5*Qb;
	shuifei=2.25*iFlowRate;
}

/********************************************************************************************************
**	�� �� �� : void wifi_send_data(uint32 time1)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : ���ƶ˷���POST����  5S����һ��
**	��    �� ��	time1
               
**	�� �� ֵ : none
**  ˵    �� ��
*******************************************************************************************************/
void wifi_send_data(uint32 time1)
{
	if(temp1==time1)
	{
		NVIC_DisableIRQ(BFTM0_IRQn); 
		NVIC_DisableIRQ(UART1_IRQn);    
		memset(http_response,0,sizeof(http_response));
		Data1_refresh();

		/* ת��Ϊ�ַ�����ʽ */
		sprintf(tempStr, "%0.1f", temperature-8);
		sprintf(humiStr, "%0.2f", iFlowRate);
		sprintf(U_Str, "%0.1f", U);
		// 		sprintf(I_Str,"%0.1f", I);
		sprintf(P_Str,"%0.1f", P);
		sprintf(Q_Str,"%0.2f", Qb);
		sprintf(dianfei_Str,"%0.2f", dianfei);
		sprintf(shuifei_Str,"%0.2f", shuifei);

		OneNet_Post("wendu",tempStr);
		Sket_Delayms(10);
		OneNet_Post("water",humiStr);
		Sket_Delayms(10);
		OneNet_Post("voltage",U_Str);
		Sket_Delayms(10);
		// 		OneNet_Post("dianliu",I_Str);
		// 		Sket_Delayms(10);
		OneNet_Post("gonglv",P_Str);
		Sket_Delayms(10);
		OneNet_Post("dianneng",Q_Str);
		Sket_Delayms(10);
		OneNet_Post("dianfei",dianfei_Str);
		Sket_Delayms(10);
		OneNet_Post("shuifei",shuifei_Str);

		http_response_len=0;
		memset(http_response,0,sizeof(http_response));
		temp1 = 0;
		NVIC_EnableIRQ(BFTM0_IRQn);                    //�ж�ʹ��
		NVIC_EnableIRQ(UART1_IRQn);
	}
}

/********************************************************************************************************
**	�� �� �� : void wifi_get_data(uint32 time2)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : ���ƶ˷�������Get  1S����һ��
**	��    �� ��	time2
               
**	�� �� ֵ : none
**  ˵    �� ��
*******************************************************************************************************/

void wifi_get_data(uint32 time2)
{
	if(temp2==time2)
	{
		NVIC_DisableIRQ(BFTM0_IRQn);
		if(Modeflag==0)
		{ 	 
			ACvalue=OneNet_get("ACSwitch");	
			if(ACvalue==1)
			{
				HT_GPIOC->RR = GPIO_PIN_5;
				printf("Open AC-Switch\r\n");
			}
			else
			{
				HT_GPIOC->SRR = GPIO_PIN_5;
				printf("Close AC-Switch\r\n");
			}		
		}
		temp2 = 0;
		NVIC_EnableIRQ(BFTM0_IRQn);                    //�ж�ʹ��
	}	 	
}


void wifi_get_data1(uint32 time3)
{
	if(temp3==time3)
	{
		NVIC_DisableIRQ(BFTM0_IRQn); 
		if(Modeflag==0)
		{
			Watervalue=OneNet_get1("Switchwater");
			if(Watervalue==1)
			{
				HT_GPIOC->RR = GPIO_PIN_4;
				printf("Open Water-Switch\r\n");
			}
			else if(Watervalue==0) 
			{
				HT_GPIOC->SRR = GPIO_PIN_4;
				printf("Close Water-Switch\r\n");
			}	
		}
		/* �¶� */	
		sprintf(Store_T,"t7.txt=\"%0.2lf��\"",temperature-8);
		HMISendStr(Store_T);
		HMISendByte(0xff);

		/* ��ѹ */
		sprintf(Store_U,"t9.txt=\"%0.2lfV\"",U);
		HMISendStr(Store_U);
		HMISendByte(0xff);

		/* ���� */
		sprintf(Store_I,"t10.txt=\"%0.2lfA\"",I);
		HMISendStr(Store_I);
		HMISendByte(0xff);

		/* ���� */
		sprintf(Store_P,"t11.txt=\"%0.2lfW\"",P);
		HMISendStr(Store_P);
		HMISendByte(0xff);

		/* ���� */
		sprintf(Store_Q,"t12.txt=\"%0.2lfKwh\"",Qb);
		HMISendStr(Store_Q);
		HMISendByte(0xff);		
		/* ˮ����*/
		sprintf(Store_W,"t8.txt=\"%0.2lfm3\"",iFlowRate);
		HMISendStr(Store_W);
		HMISendByte(0xff);	

		temp3 = 0;	
		NVIC_EnableIRQ(BFTM0_IRQn); 
	}		
}


