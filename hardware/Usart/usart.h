/*
*********************************************************************************************************
*	                                  
*	
*	文件名称 : usart.h
*	说    明 : 系统调试串口驱动，简化函数数量，防止串口发送陷入死循环
*
*********************************************************************************************************
*/
#ifndef _USART_H_
#define _USART_H_
#include "config.h"

 /* Private constants ---------------------------------------------------------------------------------------*/
 #define NVIC_PRIORITY_GROUP_3          3 /* Preemption: 4 bits / Subpriority: 0 bits    */                    
 #define NVIC_PRIORITY_GROUP_4          4 /* Preemption: 3 bits / Subpriority: 1 bits    */                  
 #define NVIC_PRIORITY_GROUP_5          5 /* Preemption: 2 bits / Subpriority: 2 bits    */                    
 #define NVIC_PRIORITY_GROUP_6          6 /* Preemption: 1 bits / Subpriority: 3 bits    */                   
 #define NVIC_PRIORITY_GROUP_7          7 /* Preemption: 0 bits / Subpriority: 4 bits    */  
 
 
#define MAX_RCV_LEN  1024
void USART0_Init(unsigned long Baudrate);
void UART0_Init(unsigned long Baudrate1);
void USART1_Init(unsigned long Baudrate2);
void UART1_Init(unsigned long Baudrate3);

void UART0_Write(HT_USART_TypeDef* USARTx, unsigned char *Data,char len);
void USART1_Write(HT_USART_TypeDef* USARTx,unsigned char *Data,char len);
void UART0_IRQHandler(void);
// extern void USART1_Clear(void);
extern unsigned char  http_response[MAX_RCV_LEN];
extern volatile unsigned int   http_response_len;
void SendCmd(char* cmd, char* result, int timeOut);
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/



