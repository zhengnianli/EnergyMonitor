/**********************************************************************************************************
*	                                  
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	˵    �� : 
*
**********************************************************************************************************/
#include "config.h"
// const u8 TEXT_Buffer[]={"IIC TEST"}; 
// #define SIZE sizeof(TEXT_Buffer)
// u8 datatemp[SIZE];

 FlagStatus  Modeflag=0;
/*
*********************************************************************************************************
* �� �� ����main
* ����˵����c�������
* ��    �Σ���

* �� �� ֵ����
*********************************************************************************************************
*/
int main(void)
{
	// �ϵ��ʼ������
	SysInit();
 	LED_Init();
	NVIC_Configuration();
	ESP8266_Init();         //ESP8266��ʼ��
    BFTM0_Init();
	printf("ESP8266 init over\r\n");
 	Sket_Delayms(100);

	while(1)
	{	
		if(GPIO_ReadInBit(HT_GPIOB, GPIO_PIN_1)==RESET)
		{
			delay_ms(15);
			if(GPIO_ReadInBit(HT_GPIOB, GPIO_PIN_1)==RESET)
			{
			   Modeflag=0;
			// Modeflag=!Modeflag;
			// GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_5, (FlagStatus)Modeflag);
			   while(GPIO_ReadInBit(HT_GPIOB, GPIO_PIN_1)==RESET);
			}
		}
	}
}



/********************************************************************************************************
**                            End Of File
********************************************************************************************************/

