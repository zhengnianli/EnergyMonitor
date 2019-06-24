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
#include "ds18B20.h"
/*
*********************************************************************************************************
* 函 数 名：DS18B20_IO_OUT    
* 功能说明：ds18b20数据总线写
* 形    参：无
* 返 回 值：无
*********************************************************************************************************
*/
void DS18B20_IO_OUT(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PA         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCUClock.Bit.BKP        = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
	{
		while (1);
	}
	AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_MODE_DEFAULT);
	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT);
}
/*
*********************************************************************************************************
* 函 数 名：DS18B20_IO_IN       
* 功能说明：ds18b20数据总线读       
* 形    参：无
* 返 回 值：无                 
*********************************************************************************************************
*/
void DS18B20_IO_IN(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PA         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCUClock.Bit.BKP        = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
	{
		while (1);
	}
	AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_MODE_DEFAULT);
	GPIO_DirectionConfig( HT_GPIOA, GPIO_PIN_1,GPIO_DIR_IN); 
	GPIO_InputConfig(HT_GPIOA,GPIO_PIN_1,ENABLE);  
}
/*
*********************************************************************************************************
* 函 数 名：DS18B20_Rst       
* 功能说明：复位ds18b20
* 形    参：无
* 返 回 值：无                 
*********************************************************************************************************
*/
void DS18B20_Rst(void)	   
{                 
	DS18B20_IO_OUT(); 
    DS18B20_DQ_OUT_L; 
    Sket_Delayus(480); 
    DS18B20_DQ_OUT_H; 
	Sket_Delayus(480);     
}
/*
*********************************************************************************************************
* 函 数 名：DS18B20_Read_Byte
* 功能说明：ds18b20读字节函数
* 形    参：GPIO_Pin
* 返 回 值：读取的字节
*********************************************************************************************************
*/
u8 DS18B20_Read_Byte(void)    // read one byte
{        
	u8 i=0,TempData=0;

	for(i=0;i<8;i++)
	{
		TempData>>=1;

		DS18B20_IO_OUT();//输出
		DS18B20_DQ_OUT_L;	 //拉低
 		Sket_Delayus(4);//延时4微妙
		DS18B20_DQ_OUT_H;
 		Sket_Delayus(10);//延时10微妙
		DS18B20_IO_IN();

		if(GPIO_ReadInBit(GPIO_DS18B20,IO_Temp)==1)
		{
		   TempData|=0x80;//读数据 从低位开始
		}

 		Sket_Delayus(45);//延时45微妙
	}

	return TempData;
}
/*
*********************************************************************************************************
* 函 数 名：DS18B20_Write_Byte
* 功能说明：ds18b20写字节函数
* 形    参：GPIO_Pin
* 返 回 值：要写入的字节    如写入0xcc（11001100），由低位到高位依次写入，写0、写0、写1……
*********************************************************************************************************
*/
void DS18B20_Write_Byte(u8 dat)     
{             
	u8 i=0;
	DS18B20_IO_OUT();//输出

	for(i=0;i<8;i++)
	{
		DS18B20_DQ_OUT_L;	 //拉低
 		Sket_Delayus(15);//延时15微妙
		if((dat&0x01)==1)
		{
			DS18B20_DQ_OUT_H;
		}
		else
		{
			DS18B20_DQ_OUT_L;
		}
 		Sket_Delayus(60);//延时60微妙
		DS18B20_DQ_OUT_H;
		
		dat>>=1;//准备下一位数据的发送	
	}
}
/*
*********************************************************************************************************
* 函 数 名：DS18B20_Get_Temp
* 功能说明：获取ds18b20温度数据
* 形    参：无
* 返 回 值：温度值 （-550~1250） 
* 描    述：精度：0.1C
*********************************************************************************************************
*/
double DS18B20_Get_Temp(void)
{
	u8 TL=0,TH=0;
	u16 temp=0;
	double wd=0;

	DS18B20_Rst();//复位
	DS18B20_Write_Byte(0xCC); //跳过ROM命令
	DS18B20_Write_Byte(0x44); //温度转换命令

	Sket_Delayms(800);//延时800毫秒
 	DS18B20_Rst();//复位
	DS18B20_Write_Byte(0xCC); //跳过ROM命令
	DS18B20_Write_Byte(0xBE); //读温度命令

	TL=DS18B20_Read_Byte();//LSB
	TH=DS18B20_Read_Byte();//MSB

	temp=TH;
	temp=(temp<<8)+TL;

	if((temp&0xF800)==0xF800)//负温度判断
	{
		temp=~temp;
		temp=temp+1;
		wd=temp*(-0.0625);
	}
	else
	{
		wd=temp*0.0625;	
	}

	return wd;
}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
