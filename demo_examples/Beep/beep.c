#include "beep.h"

/**
  * @brief  GPIO_pin for beep Initialization .
  * @param  void
  * @retval None
  */
void BEEP_Init()	  //�˿ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����һ���ṹ�������������ʼ��GPIO

	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   /* ����GPIOʱ�� */

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=BZ;		//ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	 /* ��ʼ��GPIO */
}

/**
  * @brief  Make a sound.
  * @param  void
  * @retval None
  */
void sound()  //�綯������
{
	u32 i=1000;
	while(i--)					//����һ��ʱ���PWM����ʹ����������
	{
		GPIO_SetBits(GPIOB,BZ);	   //IO������ߵ�ƽ
		delay(i);
		GPIO_ResetBits(GPIOB,BZ);	//IO������͵�ƽ
		delay(i--);
	}	
}