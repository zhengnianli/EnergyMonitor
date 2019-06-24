/*
*********************************************************************************************************
*	                                  
*	
*	�ļ����� : config.h
*	˵    �� : ���ڴ�ſ������̵�ȫ�ֱ���
*
*********************************************************************************************************
*/
#ifndef __CONFIG__H__
#define __CONFIG__H__

//----------------------------------------------------------------
//�޷������ͺ궨��
#define uchar 	unsigned char													 
#define uint 	unsigned int

#define uint8 	unsigned char 
#define uint16 	unsigned short int
#define uint32 	unsigned int
	
//----------------------------------------------------------------
//��������ͷ�ļ�  
#include "ht32f1655_56.h"
#include "ht32.h"
#include "ht32_board.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdint.h>
#include "math.h"

	
//---------------------------------------------------------------
//��������ͷ�ļ�
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ds18b20.h"
#include "spi.h"
#include "esp8266.h"
#include "HTTP_Demo.h"
#include "BFTM.h"
#include "att7022.h"
#include "Water_485.h"
#include "wifi_handle.h"
#include "HMI.h"
#include "myiic.h"
#include "24cxx.h" 
//---------------------------------------------------------------
//����ȫ�ֱ���
extern char HMI_Cmd;	  //���ڽ��մ���������ָ��
extern FlagStatus  Modeflag;


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
