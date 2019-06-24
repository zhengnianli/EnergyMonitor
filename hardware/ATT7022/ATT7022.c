/*
*********************************************************************************************************
*	                                  
*	
*	文件名称 : att7022.c
*	说    明 : att7022驱动
*
*********************************************************************************************************
*/
#include "att7022.h"
#include "config.h"
//-------------------------------------------------------------------------------
// ATT7022 SPI宏定义
#define		ATT_SPI_Init()				SPI1_Init()										
#define		ATT_SPI_ReadWrite(dat)		SPI1_ReadWrite(dat)	

//电压、电流、功率、电能全局变量。
double U=0;
double I=0;
double P=0;
double Q=0;



//-------------------------------------------------------------------------------
// ATT7022校准数据
static Energy_t s_tEmt = {0};
//-------------------------------------------------------------------------------
// ATT7022校准数据
static Revise_t s_tRts ={0xDC,{1.67,1.67,1.67},{34.3,34.3,34.3}};  


/*******************************************************************************************************
** 函数: ReadData_ATT7022,  读参数寄存器
**------------------------------------------------------------------------------------------------------
** 参数: addr:被读数据的地址(最高位为0)	
** 返回: temp:读出数据(24位) 
********************************************************************************************************/
unsigned long AttReadData(unsigned char addr)
{
	unsigned long temp=0;
// 	ATTCS=0;
	HT_GPIOB->RR = GPIO_PIN_6;
	ATT_SPI_ReadWrite(addr&0x7f);
// 	TimDelayUs(2);						// SPI时钟频率过高，读数据时需要等待2us
	Sket_Delayus(2);
	temp=(temp<<8)|ATT_SPI_ReadWrite(0);
	temp=(temp<<8)|ATT_SPI_ReadWrite(0);
	temp=(temp<<8)|ATT_SPI_ReadWrite(0);
// 	ATTCS=1;
	HT_GPIOB->SRR = GPIO_PIN_6;	
	return temp;   		
	
}

/*******************************************************************************************************
** 函数: WriteData_ATT7022,  写入命令或校表数据
**------------------------------------------------------------------------------------------------------
** 参数: addr:被写数据的地址 dat 被写的数据
** 返回: void 
********************************************************************************************************/
void WriteData_ATT7022(unsigned char addr,unsigned long dat)
{	  
// 	ATTCS=0;
	HT_GPIOB->RR = GPIO_PIN_6;
	ATT_SPI_ReadWrite(addr|0x80);
	ATT_SPI_ReadWrite(dat>>16);
	ATT_SPI_ReadWrite(dat>>8);
	ATT_SPI_ReadWrite(dat>>0);
// 	ATTCS=1;
	HT_GPIOB->SRR = GPIO_PIN_6;
}


/*******************************************************************************************************
** 函数: AttVarInit, ATT7022寄存器配置
**------------------------------------------------------------------------------------------------------
** 参数: NOLL
** 返回: NOLL
********************************************************************************************************/
void ATT7022VarInit(void)
{	
	WriteData_ATT7022( 0xC3,0x000000); 							// 清校表数据
	WriteData_ATT7022( 0xC9,0x00005A); 							// 打开校准数据写
	WriteData_ATT7022( 0x01,0xB97E);							// 模式配置寄存器
	WriteData_ATT7022( 0x03,0xF804);							// EMU 单元配置寄存器
	WriteData_ATT7022( 0x31,0x3427);							// 模拟模块使能寄存器
	WriteData_ATT7022( 0x6D,0xFF00); 							// Vrefgain 的补偿曲线系数
	WriteData_ATT7022( 0x6E,0x0DB8); 							// Vrefgain 的补偿曲线系数
	WriteData_ATT7022( 0x6F,0xD1DA); 							// Vrefgain 的补偿曲线系数
	WriteData_ATT7022( 0x16,0x0000);							// 无功相位校正寄存器
	WriteData_ATT7022( 0x1E,HFconst);							// HFConst高频脉冲参数校准
	WriteData_ATT7022( 0xC9,0x0001); 							// 关闭校准数据写
//	printf("%x\n\n",(u32)AttReadData(0));							// 测试指令 打印 7122A0 芯片工作 SPI通信正常
}

/********************************************************************************************************
** 函数: Att7022Init
**------------------------------------------------------------------------------------------------------
** 参数: void
** 返回: void
*******************************************************************************************************/
void Att7022Init(void)
{
	ATT_SPI_Init();
	ATT7022VarInit();
	AttGetAllVolue();
}
/*******************************************************************************************************
** 函数: AttGetVolue 
**------------------------------------------------------------------------------------------------------
** 参数: addr 地址 
** 返回: 有符号数据
********************************************************************************************************/
long AttGetVolue( unsigned char Value)
{	
	long temp;
	temp=AttReadData(Value);
	if(AttReadData(0X2d)!=temp) return -1;
	if(temp&0x800000) temp = 0x1000000 - temp ;  
	return temp;
}

/*******************************************************************************************************
** 函数: AttGetUnVolue 
**------------------------------------------------------------------------------------------------------
** 参数: addr 地址 
** 返回: 无符号数据
********************************************************************************************************/
long AttGetUnVolue(  unsigned char Value)
{	
	long temp;
	temp=AttReadData(Value);
	if(AttReadData(0X2d)!=temp) return -1;
	return 	temp;
}

/*******************************************************************************************************
** 函数: AttGetAllVolue, 获取ATT7022UE内部电能计量值
**------------------------------------------------------------------------------------------------------
** 参数: Energy_t *dat
** 返回: NONE
********************************************************************************************************/
void AttGetAllVolue( void )
{	
	//----------------------------------------------------------------------------------------------- 
	// A相电能参数采集
	s_tEmt.dMU [ItemA]   = AttGetVolue(VOLTAGE+ItemA)/UKrmsA;				   		// A相电压
	s_tEmt.dMI [ItemA]   = AttGetVolue(CURRENT+ItemA)/IKrmsA;				  		// A相电流
	s_tEmt.dMP [ItemA]   = AttGetVolue(POWERS+ItemA)*KCoefficient;				// A相有功功率
	s_tEmt.dMQ [ItemA]   = AttGetVolue(QPOWERS+ItemA)*KCoefficient;		   		// A相无功功率
	s_tEmt.dMPF[ItemA]   = AttGetVolue(PF+ItemA)/8388608.0;				   		// A相功率因数
	s_tEmt.dwMPoEpt[ItemA] = AttGetUnVolue(EP+ItemA);								// A相有功电能
	s_tEmt.dwMQoEpt[ItemA] = AttGetUnVolue(EQ+ItemA);								// A相无功电能
	
	//----------------------------------------------------------------------------------------------- 
	// B相电能参数采集
	s_tEmt.dMU [ItemB]   = AttGetVolue(VOLTAGE+ItemB)/UKrmsB;				   		// B相电压
	s_tEmt.dMI [ItemB]   = AttGetVolue(CURRENT+ItemB)/IKrmsB;			  			// B相电流
	s_tEmt.dMP [ItemB]   = AttGetVolue(POWERS+ItemB)*KCoefficient;				// B相有功功率
	s_tEmt.dMQ [ItemB]   = AttGetVolue(QPOWERS+ItemB)*KCoefficient;		   		// B相无功功率
	s_tEmt.dMPF[ItemB]   = AttGetVolue(PF+ItemB)/8388608.0;				   		// B相功率因数
	s_tEmt.dwMPoEpt[ItemB] = AttGetUnVolue(EP+ItemB);								// B相有功电能
	s_tEmt.dwMQoEpt[ItemB] = AttGetUnVolue(EQ+ItemB);								// B相无功电能
	
	//----------------------------------------------------------------------------------------------- 
	// C相电能参数采集
	s_tEmt.dMU [ItemC]   = AttGetVolue(VOLTAGE+ItemC)/UKrmsC;					   	// C相电压	
	s_tEmt.dMI [ItemC]   = AttGetVolue(CURRENT+ItemC)/IKrmsC;					  	// C相电流	
	s_tEmt.dMP [ItemC]   = AttGetVolue(POWERS+ItemC)*KCoefficient;				// C相有功功率
	s_tEmt.dMQ [ItemC]   = AttGetVolue(QPOWERS+ItemC)*KCoefficient;				// C相无功功率
	s_tEmt.dMPF[ItemC]   = AttGetVolue(PF+ItemC)/8388608.0;						// C相功率因数
	s_tEmt.dwMPoEpt[ItemC] = AttGetUnVolue(EP+ItemC);								// C相有功电能
	s_tEmt.dwMQoEpt[ItemC] = AttGetUnVolue(EQ+ItemC);								// C相无功电能
	
	//----------------------------------------------------------------------------------------------- 
	// 总电能参数采集
	s_tEmt.dMF  = AttGetVolue(FREQUENCY)/8191.0;									// 总频率
	s_tEmt.dMP [ItemALL]   = AttGetVolue(POWERS+ItemALL)*KCoefficient*2;			// 总有功功率
	s_tEmt.dMQ [ItemALL]   = AttGetVolue(QPOWERS+ItemALL)*KCoefficient*2;			// 总无功功率
 	s_tEmt.dMPF[ItemALL] = AttGetVolue(PF+ItemALL)/8388608.0;						// 总功率因数
	s_tEmt.dwMPoEpt[ItemALL] = AttGetUnVolue(EP+ItemALL);							// 总有功电能
	s_tEmt.dwMQoEpt[ItemALL] = AttGetUnVolue(EQ+ItemALL);							// 总无功电能
	
	 U=s_tEmt.dMU[ItemA];
	 I=s_tEmt.dMI[ItemA];
	 P=s_tEmt.dMP[ItemA];
	 Q=s_tEmt.dwMPoEpt[ItemALL]/EC;
}

/********************************************************************************************************
** 函数: Appear_data
**------------------------------------------------------------------------------------------------------
** 参数: void
** 返回: void
*******************************************************************************************************/
void Appear_U_Data (void){	printf("电压：%0.1f,%0.1f,%0.1f;\n",s_tEmt.dMU[ItemA],s_tEmt.dMU[ItemB],s_tEmt.dMU[ItemC]);}
void Appear_I_Data (void){	printf("电流：%0.3f,%0.3f,%0.3f;\n",s_tEmt.dMI[ItemA],s_tEmt.dMI[ItemB],s_tEmt.dMI[ItemC]);}
void Appear_F_Data (void){	printf("频率：%0.1f;\n",s_tEmt.dMF);}
void Appear_P_Data (void){	printf("有功功率：%0.3f,%0.3f,%0.3f,%0.3f;\n", s_tEmt.dMP[ItemA], s_tEmt.dMP[ItemB], s_tEmt.dMP[ItemC], s_tEmt.dMP[ItemALL]);}
void Appear_Q_Data (void){	printf( "无功功率：%0.2f,%0.2f,%0.2f,%0.2f;\n", s_tEmt.dMQ[ItemA], s_tEmt.dMQ[ItemB], s_tEmt.dMQ[ItemC], s_tEmt.dMQ[ItemALL]);}
void Appear_EP_Data(void){	printf( "有功电能：%0.1f;\n",s_tEmt.dwMPoEpt[ItemALL]/EC);}
void Appear_EQ_Data(void){	printf( "无功电能：%0.1f;\n",s_tEmt.dwMQoEpt[ItemALL]/EC);}

/********************************************************************************************************
** 函数: PutAllData
**------------------------------------------------------------------------------------------------------
** 参数: void
** 返回: void
*******************************************************************************************************/
void PutAllData(void)
{
	Appear_U_Data();		// 串口显示 电压数据
	Appear_I_Data();		// 串口显示 电流数据
	Appear_F_Data();		// 串口显示 频率数据
	Appear_P_Data();		// 串口显示 有功功率数据
	Appear_Q_Data();		// 串口显示 无功功率数据
	Appear_EP_Data();		// 串口显示 有功电能数据
	Appear_EQ_Data();		// 串口显示 无功电能数据
	printf("\n\n");
}

/********************************************************************************************************
** 函数: PutAllVolue,输出电能参数至串口
**------------------------------------------------------------------------------------------------------
** 参数: NULL
** 返回: 成功 1 失败 0
*******************************************************************************************************/
// int PutAllVolue(void)
// {
// 	if(PutEmtTimer)	return FALSE;
// 	PutEmtTimer=TIMER_SEC*5;
// 	AttGetAllVolue();
// 	PutAllData();
// 	return TRUE;
// }
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
