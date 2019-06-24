
#include "config.h"

#define API_KEY     "ewgLfFQIYmGFIAPAZZY1O7xNTIw="		//需要定义为用户自己的参�?
#define DEV_ID      "5066355"							            //需要定义为用户自己的参�?
unsigned char  value1=1;	
unsigned char  value2=1;
	/********************************************************************************************************
**	�?�?�?: unsigned int HTTP_PostPkt(char *pkt, char *key, char *devid, char *dsid, 	char *val)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 组HTTP POST报文
**	�?   �?�?* pkt  报文缓存指针
								key    API_KEY
							  devid  设备ID�?
								dsid   数据流ID
								val   字符串形式的数据点的�?
**	�?�?�?: 整个包的长度
**  �?   �?�?
*******************************************************************************************************/
 unsigned int HTTP_PostPkt(char *pkt, char *key, char *devid, char *dsid, 	char *val)
{
    char dataBuf[100] = {0};
    char lenBuf[10] = {0};
    *pkt = 0;

    sprintf(dataBuf, ",;%s,%s", dsid, val);     //采用分割字符串格�?type = 5
    sprintf(lenBuf, "%d", strlen(dataBuf));

    strcat(pkt, "POST /devices/");
    strcat(pkt, devid);
    strcat(pkt, "/datapoints?type=5 HTTP/1.1\r\n");

    strcat(pkt, "api-key:");
    strcat(pkt, key);
    strcat(pkt, "\r\n");

    strcat(pkt, "Host:api.heclouds.com\r\n");

    strcat(pkt, "Content-Length:");
    strcat(pkt, lenBuf);
    strcat(pkt, "\r\n\r\n");

    strcat(pkt, dataBuf);

    return strlen(pkt);
}


/********************************************************************************************************
**	�?�?�?: unsigned int HTTP_GetPkt(char pkt[], char *key, char *devid, char *dsid)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 组HTTP Get报文
**	�?   �?�?* pkt   报文缓存指针
								key     API_KEY
							  devid  设备ID�?
								dsid   数据流ID
**	�?�?�?: 整个包的长度
**  �?   �?�?
*******************************************************************************************************/

unsigned int HTTP_GetPkt(char pkt[], char *key, char *devid, char *dsid)
{
	*pkt =0;
	strcat(pkt, "GET /devices/");
	strcat(pkt, devid);
	strcat(pkt, "/datastreams/");
	strcat(pkt, dsid);
	strcat(pkt, " HTTP/1.1\r\n");

	strcat(pkt, "api-key: ");
	strcat(pkt, key);
	strcat(pkt, "\r\n");

	//  strcat(pkt, "Host:api.heclouds.com\r\n\r\n");
	strcat(pkt, "Host:api.heclouds.com\r\n");
	strcat(pkt, "Connection:close\r\n\r\n");
	return strlen(pkt);
}

/********************************************************************************************************
**	�?�?�?: unsigned int OneNet_Post(char *dsid,char *val)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 向OneNet Post数据
**	�?   �?�?dsid  数据流ID
                val   字符串形式的数据点的�?
**	�?�?�?: 1
**  �?   �?�?
*******************************************************************************************************/
unsigned int OneNet_Post(char *dsid,char *val)
{
	unsigned int len;
	char HTTP_Buf[400];     //HTTP报文缓存�?
	
	len = HTTP_PostPkt(HTTP_Buf, API_KEY, DEV_ID, dsid, val); //HTTP组包
	UART0_Write(HT_UART0, (unsigned char *)(HTTP_Buf), len);			//报文发�?
	printf("send HTTP msg:\r\n%s\r\n", HTTP_Buf);
	printf("\r\n") ; 
 	return 1;
}

/********************************************************************************************************
**	�?�?�?: unsigned int OneNet_Post(char *dsid,char *val)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : 向OneNet Gut 布尔值数�?
**	�?   �?�?dsid  数据流ID
               
**	�?�?�?: 开关数�?
**  �?   �?�?
*******************************************************************************************************/
unsigned int OneNet_get(char *dsid)
{			
	unsigned int len;
	char* presult=NULL;
	static char unitTmp[64]={0};
	static char unit_symbolTmp[64]={0};
	static char idTmp[64]={0};
	static char timestampTmp[64]={0};
	static char valueTmp[64]={0};
	static char value[64]={0};  
	static char HTTP_Buf[400];
	static char strTmp[MAX_RCV_LEN]={0};  //声明为静态变量，防止堆栈溢出
	static char strTmp1[MAX_RCV_LEN]={0}; //声明为静态变量，防止堆栈溢出

	http_response_len=0;
	memset(http_response,0,sizeof(http_response));

	len = HTTP_GetPkt(HTTP_Buf, API_KEY, DEV_ID,dsid); //HTTP组包
	UART0_Write(HT_UART0, (unsigned char *)(HTTP_Buf), len);			//报文发�?
	//printf("send HTTP msg:\r\n%s\r\n", HTTP_Buf1);
	Sket_Delayms(300);
	if(http_response_len > 0)
	{
	//  http_response[http_response_len] = '\0';
		presult = strstr( (const char *)http_response , (const char *)"200 OK\r\n");
	//  printf("%s",http_response) ;         // 打印接收到的数据  
	}
	if(presult != 0)
	{
		sscanf((const char *)http_response,"%*[^{]{%[^}]",strTmp);  //获取 {�?} 之间的字�?
		strcat(strTmp, "}");
		sscanf(strTmp,"%*[^{]{%[^}]",strTmp1);  //获取 {�?} 之间的字�?
	// 	sscanf(strTmp1,"%[^,],%[^,]",timestampTmp,valueTmp); 	//提取返回信息
		sscanf(strTmp1,"%[^,],%[^,],%[^,],%[^,],%[^,]",unitTmp,unit_symbolTmp,timestampTmp,idTmp,valueTmp); 	//提取返回信息
		strncpy(value,strstr(valueTmp,":")+1,strlen(strstr(valueTmp,":"))-1);//   strstr(str1,str2) 判断字符串str2是否是str1的子�?
		printf("%s",value) ;         // 打印接收到的数据  
		printf("\r\n") ; 	

		if(strstr(value,"1"))
		{
			value1=1;
		}
	// 			else if (strstr(value,"0")) 
		if(strstr(value,"0"))	
		{
			value1=0;
		}		
	}
	memset(http_response,0,sizeof(http_response));
	return value1;
}

unsigned int OneNet_get1(char *dsid)
{			
	unsigned int len;
	char* presult=NULL;
	static char unitTmp[64]={0};
	static char unit_symbolTmp[64]={0};
	static char idTmp[64]={0};
	static char timestampTmp[64]={0};
	static char valueTmp[64]={0};
	static char value[64]={0};  
	static char HTTP_Buf[400];
	static char strTmp[MAX_RCV_LEN]={0};  //声明为静态变量，防止堆栈溢出
	static char strTmp1[MAX_RCV_LEN]={0}; //声明为静态变量，防止堆栈溢出

	http_response_len=0;
	memset(http_response,0,sizeof(http_response));
	len = HTTP_GetPkt(HTTP_Buf, API_KEY, DEV_ID,dsid); //HTTP组包
	UART0_Write(HT_UART0, (unsigned char *)(HTTP_Buf), len);			//报文发�?
	//printf("send HTTP msg:\r\n%s\r\n", HTTP_Buf1);
	Sket_Delayms(300);

	if(http_response_len > 0)
	{
	//http_response[http_response_len] = '\0';
		presult = strstr( (const char *)http_response , (const char *)"200 OK\r\n");
	//printf("%s",http_response) ;         // 打印接收到的数据  
	}

	if(presult != 0)
	{
		sscanf((const char *)http_response,"%*[^{]{%[^}]",strTmp);  //获取 {�?} 之间的字�?
		strcat(strTmp, "}");

		sscanf(strTmp,"%*[^{]{%[^}]",strTmp1);  //获取 {�?} 之间的字�?
	// 	sscanf(strTmp1,"%[^,],%[^,]",timestampTmp,valueTmp); 	//提取返回信息
		sscanf(strTmp1,"%[^,],%[^,],%[^,],%[^,],%[^,]",unitTmp,unit_symbolTmp,timestampTmp,idTmp,valueTmp); 	//提取返回信息
		strncpy(value,strstr(valueTmp,":")+1,strlen(strstr(valueTmp,":"))-1);//   strstr(str1,str2) 判断字符串str2是否是str1的子�?
		printf("%s",value) ;         // 打印接收到的数据  
		printf("\r\n") ; 	

		if(strstr(value,"1"))
		{
			value2=1;
		}

		if(strstr(value,"0"))	
		{
			value2=0;
		}		
	}
	memset(http_response,0,sizeof(http_response));
	return value2;
}

