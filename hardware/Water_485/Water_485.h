
#ifndef _Water_485_H_
#define _Water_485_H_

#include "ht32.h"

//----------------------------------------------------------------
//�޷������ͺ궨��
#define uchar 	unsigned char													 
#define uint 	unsigned int
#define uint8 	unsigned char 
#define uint16 	unsigned short int
#define uint32 	unsigned int

#define UARTBUF_SIZE 	200		  // ���ڽ�����������Ĵ�С
extern unsigned char Usart1Buf_MaxLen;				// ���ڽ�����������ĳ���
extern unsigned char Usart1Buf[UARTBUF_SIZE];	    // ���ڽ��ջ�������
extern float  iFlowRate;	
void Water_Send_Dat(void);

void water_get(void);

void USART1_IRQHandler(void);
void water_unpack(uint8 *pStr, uint8 len);
void Save_Data(uint8 *pStr);
uint8 BCDtoDec( uint8 temp );

#endif

