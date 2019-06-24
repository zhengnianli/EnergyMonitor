
#ifndef _wifi_handle_H_
#define _wifi_handle_H_

extern double  Qa;
void BFTM0_IRQHandler(void);
void Data_refresh(uint32 time);
void wifi_send_data(uint32 time1);
void wifi_get_data(uint32 time2);
 void wifi_get_data1(uint32 time3);
void save_dianneng(uint32 time4);

#endif
