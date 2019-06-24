

/**------------------------------------------------------------------------------------------------------
** 描述:
**     说明：
**        1.协议版本号：
**        2.物理接口：RS485
**        3.串口设置：波特率2400bps,1位起始位，8位数据位，1位停止位，无校验。
**        4.数据格式：收发数据都是HEX, 2字节、4字节均为高位在前、低位在后。
**------------------------------------------------------------------------------------------------------*/
#include "config.h"

unsigned char Usart1Buf_MaxLen=0;					  // 串口接收数据数组的长度
unsigned char Usart1Buf[UARTBUF_SIZE];	   		 	  // 串口接收缓冲数组
unsigned char Print_BUF[100];						  // 上报数据缓冲buf
#define   WaterMeterPosition_Flow           15        //接收数据的第14字节开始为水表值
#define   WaterMeterPosition_FlowMeasure    19        //接收数据的第18字节开始为水表值的单位
#define   c4Bytes		    				4 		  // 协议中数据对应字段的字节数，4字节
#define   EN485_1  HT_GPIOA->SRR = GPIO_PIN_6
#define   EN485_0  HT_GPIOA->RR = GPIO_PIN_6

float   iFlowRate;	   //水表总流量 全局变量
char Store_Water[5];  //水表数据临时存储区

/********************************************************************************************************
**	函 数 名 : void Water_Send_Dat(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 进行读表操作
**	形    参 : NONE
**	返 回 值 : NONE
**  说    明 ：
*******************************************************************************************************/
void Water_Send_Dat(void)
{	
	unsigned char *order_tmp = &Print_BUF[0];				// 发送指令暂存数组
	unsigned char order_len;
//  unsigned char i;
	
	order_len = 0;											// 地址偏移
// 	i = 0;
	order_tmp[order_len++] = 0xFE;							// EF唤醒设备
	order_tmp[order_len++] = 0xFE;							
	order_tmp[order_len++] = 0xFE;							
	order_tmp[order_len++] = 0xFE;							
	order_tmp[order_len++] = 0xFE;							
	order_tmp[order_len++] = 0xFE;							
	order_tmp[order_len++] = 0x68;             //帧起始符
 	order_tmp[order_len++] = 0x10;             //表计类型为冷水表
	order_tmp[order_len++] = 0x87;             //表计地址
	order_tmp[order_len++] = 0x01;             
 	order_tmp[order_len++] = 0x20;             
	order_tmp[order_len++] = 0x30; 
	order_tmp[order_len++] = 0x01;
 	order_tmp[order_len++] = 0x00;            
	order_tmp[order_len++] = 0x00; 
	order_tmp[order_len++] = 0x01;             //控制码_由主站发出的控制帧,通讯正常,读数据.
 	order_tmp[order_len++] = 0x03;             //数据长度
	order_tmp[order_len++] = 0x90;             //数据标识_读计量数据
	order_tmp[order_len++] = 0x1F;             //数据标识
 	order_tmp[order_len++] = 0x01;             //序列号
	order_tmp[order_len++] = 0x05;             //校验码
	order_tmp[order_len++] = 0x16;             //结束码
	
	/************ 发送Buf *************/
	EN485_1;
	USART1_Write(HT_USART1,order_tmp, order_len);
	EN485_0;
	
// 	for(i=0;i<Usart1Buf_MaxLen;i++)
// 	{
// 		printf("%02X",Usart1Buf[i]) ;         // 打印接收到的数据
// 		printf(" ");
// 	}
// 	printf("\n");
// 	printf("\n");
// 	Frame_wait = FRAME_TIME;								// 数据包超时定时器重置
 	Usart1Buf_MaxLen = 0;									// 清空数据长度
    Sket_Delayms(300);
	//return 1;
}

/********************************************************************************************************
**	函 数 名 : void water_unpack(uint8 *pStr, uint8 len)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 解包进行数据有效性判断
**	形    参 ：*pStr:原始数据，len：数据长度
**	返 回 值 : NONE
**  说    明 ：
*******************************************************************************************************/
void water_unpack(uint8 *pStr, uint8 len)
{
	char  i;  

	for (i = 0; i<len - 12; i++)                        
	{
		if (pStr[i] != 0xFE)continue;			            // 查找帧起始符
		if (pStr[i + 1] == 0xFE)continue;				
		{		
			Save_Data(&pStr[i]);	                        // 保存数据 
		}
		Usart1Buf_MaxLen = 0;             //  清除串口缓存										
	}
}

/********************************************************************************************************
**	函 数 名 : void Save_Data(uint8 *pStr)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 对数据进一步解析，保存数据
**	形    参 ：*pStr:从累积值数据开始的数据包,
**	返 回 值 : 水表流量值iFlowRate
**  说    明 ：
*******************************************************************************************************/
void Save_Data(uint8 *pStr)
{
    signed  char   i;                     
    uint8   temp8;                 
    float  temp32;                						
    temp8 = 0;
    temp32= 0;

	for(i=c4Bytes - 1; i>=0; i--)                                  
    {
       temp8 = *(pStr + WaterMeterPosition_Flow + i); 		// 从高字节(高位)到低字节（低位）取
   	   temp32=temp32*100+BCDtoDec(temp8);			
    }
	
   temp32 = temp32 * 0.01;
   temp8 =  *(pStr + WaterMeterPosition_FlowMeasure);
   
   switch(temp8)		// 判断单位档位
   {
   		case 0x2C:   	// 2CH----1立方米
   			temp32 = temp32 * 1;
   			break;
   		case 0x2B:		// 2BH----0.1立方米
   			temp32 = temp32 * 0.1;
   			break;
   		case 0x2A:		// 2AH----0.01立方米
   			temp32 = temp32 * 0.01;
   			break;
   		default:
   			break;
   }
    temp32 = ( (float)( (int)( (temp32+0.005)*100 ) ) )/100;
    printf("\n当前累计流量：%.2f 吨\n",temp32);
    iFlowRate = temp32;     // 水表流量值
}


/********************************************************************************************************
**	函 数 名 : uint8 BCDtoDec( uint8 temp )
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : BCD码转换成十进制码
**	形    参 ：temp:转化的BCD码
**	返 回 值 : 转化后的十进制码
**  说    明 ：
*******************************************************************************************************/
uint8 BCDtoDec( uint8 temp )
{
	return ( ( temp/16 )*10+temp%16) ;
}

/********************************************************************************************************
**	函 数 名 : void water_get(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 
**	形    参 ：
**	返 回 值 : 
**  说    明 ：
*******************************************************************************************************/
void water_get(void)
{
	Water_Send_Dat();
	if(Usart1Buf_MaxLen > 0)
	{
		water_unpack(Usart1Buf,Usart1Buf_MaxLen);
    }	
}

/********************************************************************************************************
**	函 数 名 : void USART1_IRQHandler(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 水表485总线接收中断服务函数
**	形    参 ： void
**	返 回 值 : void
**  说    明 ：
*******************************************************************************************************/
void USART1_IRQHandler(void)
{
	if (((HT_USART1->IIR) & USART_IID_RDA ) == USART_IID_RDA )
	{
		Usart1Buf[Usart1Buf_MaxLen++]=USART_ReceiveData(HT_USART1); 
	}	
}


