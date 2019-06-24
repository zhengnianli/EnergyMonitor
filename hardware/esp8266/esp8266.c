
#include "config.h"







/**
  * @brief  ESP8266硬件复位
**/
// void ESP8266_Rst(void)
// {
// 	
// 	  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
//     CKCUClock.Bit.PC         = 1;
//     CKCUClock.Bit.AFIO       = 1;
//     CKCU_PeripClockConfig(CKCUClock, ENABLE);
//     //PC11--对应ESP8266的reset引脚;
// 	HT_GPIOC->RR = GPIO_PIN_11;
// 	 Sket_Delayms(100);
// 	HT_GPIOC->SRR = GPIO_PIN_11;
//   Sket_Delayms(100);
// }




/*
 *  @brief ESP8266模块初始化
 */
void ESP8266_Init(void)
{
// 	  ESP8266_Rst();
#if 1
    SendCmd(AT, "OK", 1000);		  //模块有效性检查
    SendCmd(CWMODE, "OK",1000);	//模块工作模式
    SendCmd(RST, "OK", 1000);		  //模块重置
    SendCmd(CIFSR, "OK",1000);		//查询网络信息
    SendCmd(CWJAP, "OK",1000);		//配置需要连接的WIFI热点SSID和密码
    SendCmd(CIPSTART, "OK",1000);	//TCP连接
    SendCmd(CIPMODE1, "OK", 1000);	//配置透传模式
		SendCmd(CIPSEND, ">", 1000);	//进入透传模式
		//USART1_Clear();
#endif
}
