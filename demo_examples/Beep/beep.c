#include "beep.h"

/**
  * @brief  GPIO_pin for beep Initialization .
  * @param  void
  * @retval None
  */
void BEEP_Init()	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   /* 开启GPIO时钟 */

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=BZ;		//选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	 /* 初始化GPIO */
}

/**
  * @brief  Make a sound.
  * @param  void
  * @retval None
  */
void sound()  //电动车报警
{
	u32 i=1000;
	while(i--)					//产生一段时间的PWM波，使蜂鸣器发声
	{
		GPIO_SetBits(GPIOB,BZ);	   //IO口输出高电平
		delay(i);
		GPIO_ResetBits(GPIOB,BZ);	//IO口输出低电平
		delay(i--);
	}	
}