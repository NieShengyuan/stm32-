#include "systick.h"
/**
  * @brief  use systick get delay .
  * @param  u32 i: (i)us
  * @retval None
  */
void delay_us(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		 //ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;		   	 //���������
	do
	{
		temp=SysTick->CTRL;		   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}

/**
  * @brief  use systick get delay.
  * @param  u32 i: (i)ms
  * @retval None
  */
void delay_ms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		//ʹ�ܣ�������ʱ�޶����������ⲿʱ��Դ
	SysTick->VAL=0;			//���������
	do
	{
		temp=SysTick->CTRL;	   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ�ʱ�䵽��//(temp&0x01)�ж�systick��ʱ���Ƿ񻹴��ڿ���״̬�����Է�ֹsystick������رյ��µ���ѭ��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}

/**
  * @brief  �Զ���ϵͳʱ�ӣ�����ͨ���޸�PLLʱ��Դ�ͱ�Ƶϵ��ʵ��ʱ�ӵ���.
  * @param  
  * @retval None
  */
void RCC_HSE_Configuration() //�Զ���ϵͳʱ�䣨�����޸�ʱ�ӣ�
{
	RCC_DeInit(); //������RCC�Ĵ�������Ϊȱʡֵ
	RCC_HSEConfig(RCC_HSE_ON);//�����ⲿ���پ���HSE��
	if(RCC_WaitForHSEStartUp()==SUCCESS) //�ȴ�HSE����
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHBʱ�ӣ�HCLK��
		RCC_PCLK1Config(RCC_HCLK_Div2);//���õ���AHBʱ�ӣ�PCLK1��
		RCC_PCLK2Config(RCC_HCLK_Div1);//���ø���AHBʱ�ӣ�PCLK2��
		RCC_PLLConfig(RCC_PLLSource_HSE_Div2,RCC_PLLMul_9);//����PLLʱ��Դ����Ƶϵ��
		RCC_PLLCmd(ENABLE); //ʹ�ܻ���ʧ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//���ָ����RCC��־λ�������,PLL����
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//����ϵͳʱ�ӣ�SYSCLK��
		while(RCC_GetSYSCLKSource()!=0x08);//��������ϵͳʱ�ӵ�ʱ��Դ,0x08��PLL��Ϊϵͳʱ��
	}
}