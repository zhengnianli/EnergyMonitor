/*
*********************************************************************************************************
*	                                  
*	
*	文件名称 : led.h
*	说    明 : LED灯
*
*********************************************************************************************************
*/
#ifndef __LED_H_
#define __LED_H_

#include "config.h"

 
#define LED0_L  HT_GPIOB->RR = GPIO_PIN_0   //SET 0
#define LED1_L  HT_GPIOB->RR = GPIO_PIN_1   //SET 0
#define LED2_L  HT_GPIOC->RR = GPIO_PIN_9   //SET 0
#define LED3_L  HT_GPIOC->RR = GPIO_PIN_11   //SET 0

#define LED0_H  HT_GPIOB->SRR = GPIO_PIN_0   //SET 1
#define LED1_H  HT_GPIOB->SRR = GPIO_PIN_1   //SET 1
#define LED2_H  HT_GPIOC->SRR = GPIO_PIN_9   //SET 1
#define LED3_H  HT_GPIOC->SRR = GPIO_PIN_11   //SET 0

void LED_Init(void);



#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/




