
#ifndef _HTTP_Demo_
#define _HTTP_Demo_

 extern unsigned int HTTP_PostPkt(char *pkt, char *key, char *devid, char *dsid, char *val);
 extern unsigned int HTTP_GetPkt(char pkt[], char *key, char *devid, char *dsid);
 extern unsigned int OneNet_get(char *dsid);
 extern unsigned int OneNet_get1(char *dsid);
 extern unsigned int OneNet_Post(char *dsid,char *val);
 
#endif
