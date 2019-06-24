/*
*********************************************************************************************************
*	                                  
*	
*	�ļ����� : led.c
*	˵    �� : LED��
*
*********************************************************************************************************
*/
#include "led.h"
/*
*********************************************************************************************************
* �� �� ����LED_Init
* ����˵����LED GPIO ��ʼ������
* ��    ����void
* �� �� ֵ��void
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

