/*
*********************************************************************************************************
*
*
*  文件：HMI.h
*  注意：波特率必须配置为9600！！！
*  主机向串口屏发送数据要经过两个重要步骤:（1）发送串口指令；（2）发送结束符 *
*
*********************************************************************************************************
*/
#ifndef _HMI_H
#define _HMI_H
#include "config.h"


extern unsigned char HMI_response_len;				// 串口接收数据数组的长度
extern unsigned char HMI_response[32];	    // 串口接收缓冲数组
extern unsigned char HMI_Pkt[64];

void HMISendStart(void);
void HMISendStr(char *buf);
void HMISendByte(uint8 k);
void HMI_getwifi(void);
void get_dianneng(void);
// void HMIPageSelect(char *PageName);
#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
