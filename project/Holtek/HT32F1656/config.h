/*
*********************************************************************************************************
*	                                  
*	
*	文件名称 : config.h
*	说    明 : 用于存放开发工程的全局变量
*
*********************************************************************************************************
*/
#ifndef __CONFIG__H__
#define __CONFIG__H__

//----------------------------------------------------------------
//无符号类型宏定义
#define uchar 	unsigned char													 
#define uint 	unsigned int

#define uint8 	unsigned char 
#define uint16 	unsigned short int
#define uint32 	unsigned int
	
//----------------------------------------------------------------
//包含常用头文件  
#include "ht32f1655_56.h"
#include "ht32.h"
#include "ht32_board.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdint.h>
#include "math.h"

	
//---------------------------------------------------------------
//包含驱动头文件
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
//包含全局变量
extern char HMI_Cmd;	  //用于接收串口屏控制指令
extern FlagStatus  Modeflag;


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
