/*
*********************************************************************************************************
*
*
*  文件：ds18b20.c
*  功能：此部分为ds18b20的驱动程序
*  说明：主机控制ds18b20完成温度转换必须经过三个步骤：（1）复位；（2）发送ROM指令；（3）发送RAM指令
*
*
*********************************************************************************************************
*/
#ifndef _DS18B20_H
#define _DS18B20_H

#include "config.h"

//IO方向设置
void DS18B20_IO_IN(void);
void DS18B20_IO_OUT(void);

#define GPIO_DS18B20 HT_GPIOA
#define IO_Temp  GPIO_PIN_1

//IO操作
#define	DS18B20_DQ_OUT_H HT_GPIOA->SRR = GPIO_PIN_1
#define	DS18B20_DQ_OUT_L HT_GPIOA->RR = GPIO_PIN_1
#define	DS18B20_DQ_IN  GPIO_ReadInBit(HT_GPIOA,GPIO_PIN_1)

double DS18B20_Get_Temp(void);//获取温度
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);//读出一个字节
void DS18B20_Rst(void);//复位DS18B20    

#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/


