#include "led.h"

/**
  * @brief  delay .
  * @param  u32 i:delay(6000000) == 1s
  * @retval None
  */
void delay(u32 i)	  
{
	while(i--);
}

/**
  * @brief  GPIO_pin for led Initialization .
  * @param  void
  * @retval None
  */
void LED_Init()	  //�˿ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ���ṹ�������������ʼ��GPIO

	SystemInit();	//ʱ�ӳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=LED;  //Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
}

/**
  * @brief  led_display .
  * @param  void
  * @retval None
  */
void led_display()
{
	u8 i;
	for(i=0;i<8;i++)   //
	{
		GPIO_Write(GPIOC,(u16)~(0x01<<i));//��IO��д������
		delay(2000000);
	}
	for(i=0;i<8;i++)  //
	{
		GPIO_Write(GPIOC,(u16)~(0x80>>i));//1000 0000 >> i
		delay(1000000);
	}
	for(i=0;i<4;i++)  //
	{
		GPIO_Write(GPIOC,(u16)~(0x11<<i));//0001 0001 
		delay(2000000);
	}
	for(i=0;i<4;i++)  //
	{
		GPIO_Write(GPIOC,(u16)~(0x88>>i));//1000 1000
		delay(1000000);
	}	
}


