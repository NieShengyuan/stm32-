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
void LED_Init()	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure; //声明一个结构体变量，用来初始化GPIO

	SystemInit();	//时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=LED;  //要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* 初始化GPIO */
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
		GPIO_Write(GPIOC,(u16)~(0x01<<i));//给IO口写入数据
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


