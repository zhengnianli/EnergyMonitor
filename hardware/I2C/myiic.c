#include "myiic.h"
 
//��ʼ��IIC
void IIC_Init(void)
{					     
	
	/* Enable  clock */
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PE         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	//   SCL E14  
	AFIO_GPxConfig(GPIO_PE, AFIO_PIN_14, AFIO_MODE_1); //�������ֲ�õ���Ӧע��
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_14, GPIO_DIR_OUT);
	SDA_OUT();
}
void SDA_OUT(void)
{
	/* Enable  clock */
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PE         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	AFIO_GPxConfig(GPIO_PE, AFIO_PIN_15, AFIO_MODE_1); //�������ֲ�õ���Ӧע��
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_15, GPIO_DIR_OUT);
}
void SDA_IN(void)
{
	/* Enable  clock */
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PE         = 1;
    CKCUClock.Bit.AFIO       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	AFIO_GPxConfig(GPIO_PE, AFIO_PIN_15, AFIO_MODE_1); //�������ֲ�õ���Ӧע��
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_15, GPIO_DIR_IN);
	GPIO_InputConfig(HT_GPIOE,GPIO_PIN_15,ENABLE);  
}
	//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_us(4);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_H;delay_us(1);	   
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        delay_us(2);
		IIC_SCL_H;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}



























