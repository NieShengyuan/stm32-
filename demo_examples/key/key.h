#ifndef _key_H
#define _key_H

#include "stm32f10x.h"
/////////////////////////////////////  按键IO相关配置   ////////////////////////////////////////////////////////////////////

#define K_UP GPIO_Pin_0 //PA0
#define K_DOWN GPIO_Pin_3 //PE3
#define K_LEFT GPIO_Pin_2 //PE2
#define K_RIGHT GPIO_Pin_4 //PE4

#define Hight            1       //高电平
#define Low              0       //低电平

//配置按键按下的时候和松开的时候的电平状态
#define key_Press        Hight   //按键按下时的电平状态
#define key_Release      Low     //按键松开时的电平状态

////////////////////////////// 每Time_DELAYMS (ms) 检测一次 //////////////////////////////////////////////
#define Time_DELAYMS 20
////////////////////////////// 认定持续 Time_Multiple_Hit * Time_DELAYMS = 长按阈值 //////////////////////////
#define Time_Multiple_Hit 100

//获取按键的状态
#define k_up GPIO_ReadInputDataBit(GPIOA,K_UP)		  
#define k_down GPIO_ReadInputDataBit(GPIOE,K_DOWN)
#define k_left GPIO_ReadInputDataBit(GPIOE,K_LEFT)
#define k_right GPIO_ReadInputDataBit(GPIOE,K_RIGHT)



void key_Init(void);
//在定时器中断函数中调用，获取按键状态
u8 getKeyState();
//按键处理函数，定位具体按键，并执行相应服务函数
void key_process();

void key_pros(void);

#endif