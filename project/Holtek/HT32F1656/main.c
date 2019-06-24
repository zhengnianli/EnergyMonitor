/**********************************************************************************************************
*	                                  
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	说    明 : 
*
**********************************************************************************************************/
#include "config.h"
// const u8 TEXT_Buffer[]={"IIC TEST"}; 
// #define SIZE sizeof(TEXT_Buffer)
// u8 datatemp[SIZE];

 FlagStatus  Modeflag=0;
/*
*********************************************************************************************************
* 函 数 名：main
* 功能说明：c程序入口
* 形    参：无

* 返 回 值：无
*********************************************************************************************************
*/
int main(void)
{
	// 上电初始化函数
	SysInit();
 	LED_Init();
	NVIC_Configuration();
	ESP8266_Init();         //ESP8266初始化
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

