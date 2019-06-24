/*
*********************************************************************************************************
*
*
*  �ļ���ds18b20.c
*  ���ܣ��˲���Ϊds18b20����������
*  ˵������������ds18b20����¶�ת�����뾭���������裺��1����λ����2������ROMָ���3������RAMָ��
*
*
*********************************************************************************************************
*/
#ifndef _DS18B20_H
#define _DS18B20_H

#include "config.h"

//IO��������
void DS18B20_IO_IN(void);
void DS18B20_IO_OUT(void);

#define GPIO_DS18B20 HT_GPIOA
#define IO_Temp  GPIO_PIN_1

//IO����
#define	DS18B20_DQ_OUT_H HT_GPIOA->SRR = GPIO_PIN_1
#define	DS18B20_DQ_OUT_L HT_GPIOA->RR = GPIO_PIN_1
#define	DS18B20_DQ_IN  GPIO_ReadInBit(HT_GPIOA,GPIO_PIN_1)

double DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);//����һ���ֽ�
void DS18B20_Rst(void);//��λDS18B20    

#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/


