
#ifndef _Water_485_H_
#define _Water_485_H_

#include "ht32.h"

//----------------------------------------------------------------
//无符号类型宏定义
#define uchar 	unsigned char													 
#define uint 	unsigned int
#define uint8 	unsigned char 
#define uint16 	unsigned short int
#define uint32 	unsigned int

#define UARTBUF_SIZE 	200		  // 串口接收数据数组的大小
extern unsigned char Usart1Buf_MaxLen;				// 串口接收数据数组的长度
extern unsigned char Usart1Buf[UARTBUF_SIZE];	    // 串口接收缓冲数组
extern float  iFlowRate;	
void Water_Send_Dat(void);

void water_get(void);

void USART1_IRQHandler(void);
void water_unpack(uint8 *pStr, uint8 len);
void Save_Data(uint8 *pStr);
uint8 BCDtoDec( uint8 temp );

#endif

