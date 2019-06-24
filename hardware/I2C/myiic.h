#ifndef __MYIIC_H
#define __MYIIC_H
#include "config.h"

//IO方向设置
void SDA_OUT(void);
void SDA_IN(void);
//IO操作函数	 
// #define IIC_SCL    PBout(10) //SCL
// #define IIC_SDA    PBout(11) //SDA	 
#define IIC_SDA_H HT_GPIOE->SRR = GPIO_PIN_15

#define IIC_SDA_L HT_GPIOE->RR = GPIO_PIN_15
 
#define IIC_SCL_H HT_GPIOE->SRR = GPIO_PIN_14
#define IIC_SCL_L HT_GPIOE->RR = GPIO_PIN_15

#define READ_SDA   GPIO_ReadInBit(HT_GPIOE,GPIO_PIN_15)  //输入SDA 
                   
//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















