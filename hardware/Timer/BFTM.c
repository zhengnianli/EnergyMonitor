
#include "config.h"


// vu16 delay_cnt;


/********************************************************************************************************
**	�� �� �� : void BFTM0_Init(void)
**------------------------------------------------------------------------------------------------------- 
**	����˵�� : BFTM0��ʼ������
**	��    �� �� NONE
**	�� �� ֵ : NONE
**  ˵    �� ��
*******************************************************************************************************/
void BFTM0_Init(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCUClock.Bit.BFTM0      = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
	BFTM_SetCompare(HT_BFTM0, 72000000/10);//�������ıȽ�ֵ   100ms�ж�
	BFTM_SetCounter(HT_BFTM0, 0);                  //BFTM ��������ֵ         
	BFTM_IntConfig(HT_BFTM0, ENABLE);              // BFTM �Ƚ�ƥ���ж�ʹ�ܿ���  ENABLE/DISABLE 
	BFTM_OneShotModeCmd(HT_BFTM0, DISABLE);        // BFTM ����ģʽѡ��    ENABLE/DISABLE  �������ظ�ģʽ
	BFTM_EnaCmd(HT_BFTM0, ENABLE);                 // BFTM ������ʹ�ܿ���  ENABLE/DISABLE
	NVIC_EnableIRQ(BFTM0_IRQn);                    //�ж�ʹ��
	NVIC_SetPriority(BFTM0_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 2, 0));
}

/*******************************************************************************
������   ��void NVIC_Configuration(void)
����     ���ж�����������
������� ����
����ֵ   ����

********************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_SetVectorTable(NVIC_VECTTABLE_FLASH, 0x0);     /* Set the Vector Table base location at 0x00000000   */
}

// void B_dealy_ms(u16 time)
// {
//    
// 	 delay_cnt = time;
//     while(delay_cnt);
// }


// void Led_Flash(u16 time1)
// {
//    static int count;
// 	if(++count==time1)
// 	{
// 		
//   }
// }



