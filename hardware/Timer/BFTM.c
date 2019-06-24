
#include "config.h"


// vu16 delay_cnt;


/********************************************************************************************************
**	函 数 名 : void BFTM0_Init(void)
**------------------------------------------------------------------------------------------------------- 
**	功能说明 : BFTM0初始化函数
**	形    参 ： NONE
**	返 回 值 : NONE
**  说    明 ：
*******************************************************************************************************/
void BFTM0_Init(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCUClock.Bit.BFTM0      = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
	BFTM_SetCompare(HT_BFTM0, 72000000/10);//计数器的比较值   100ms中断
	BFTM_SetCounter(HT_BFTM0, 0);                  //BFTM 计数器的值         
	BFTM_IntConfig(HT_BFTM0, ENABLE);              // BFTM 比较匹配中断使能控制  ENABLE/DISABLE 
	BFTM_OneShotModeCmd(HT_BFTM0, DISABLE);        // BFTM 单次模式选项    ENABLE/DISABLE  工作于重复模式
	BFTM_EnaCmd(HT_BFTM0, ENABLE);                 // BFTM 计数器使能控制  ENABLE/DISABLE
	NVIC_EnableIRQ(BFTM0_IRQn);                    //中断使能
	NVIC_SetPriority(BFTM0_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 2, 0));
}

/*******************************************************************************
函数名   ：void NVIC_Configuration(void)
功能     ：中断向量表配置
输入参数 ：无
返回值   ：无

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



