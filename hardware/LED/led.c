/*
*********************************************************************************************************
*	                                  
*	
*	文件名称 : led.c
*	说    明 : LED灯
*
*********************************************************************************************************
*/
#include "led.h"
/*
*********************************************************************************************************
* 函 数 名：LED_Init
* 功能说明：LED GPIO 初始化函数
* 参    数：void
* 返 回 值：void
*********************************************************************************************************
*/
void LED_Init(void)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PA         = 1;
    CKCUClock.Bit.PC         = 1;
    CKCUClock.Bit.PD         = 1;
    CKCUClock.Bit.PB         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCUClock.Bit.BKP        = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
	{
		while (1);
	}
    // Configure AFIO mode of output pins
	AFIO_GPxConfig(GPIO_PC, AFIO_PIN_4, AFIO_MODE_DEFAULT);
  AFIO_GPxConfig(GPIO_PC, AFIO_PIN_5, AFIO_MODE_DEFAULT);
	//Configure GPIO direction of output pins 
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_4, GPIO_DIR_OUT);
  GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_5, GPIO_DIR_OUT);
//   HT_GPIOC->SRR = GPIO_PIN_5;
	
	AFIO_GPxConfig(GPIO_PB, AFIO_PIN_1, AFIO_MODE_1);
  GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_1, GPIO_DIR_IN);
	GPIO_InputConfig(HT_GPIOB, GPIO_PIN_1, ENABLE);
  GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_1, GPIO_PR_UP);

}

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/

