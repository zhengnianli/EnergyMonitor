#ifndef __MYIIC_H
#define __MYIIC_H
#include "config.h"

//IO��������
void SDA_OUT(void);
void SDA_IN(void);
//IO��������	 
// #define IIC_SCL    PBout(10) //SCL
// #define IIC_SDA    PBout(11) //SDA	 
#define IIC_SDA_H HT_GPIOE->SRR = GPIO_PIN_15

#define IIC_SDA_L HT_GPIOE->RR = GPIO_PIN_15
 
#define IIC_SCL_H HT_GPIOE->SRR = GPIO_PIN_14
#define IIC_SCL_L HT_GPIOE->RR = GPIO_PIN_15

#define READ_SDA   GPIO_ReadInBit(HT_GPIOE,GPIO_PIN_15)  //����SDA 
                   
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















