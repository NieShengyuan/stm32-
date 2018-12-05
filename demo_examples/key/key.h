#ifndef _key_H
#define _key_H

#include "stm32f10x.h"
/////////////////////////////////////  ����IO�������   ////////////////////////////////////////////////////////////////////

#define K_UP GPIO_Pin_0 //PA0
#define K_DOWN GPIO_Pin_3 //PE3
#define K_LEFT GPIO_Pin_2 //PE2
#define K_RIGHT GPIO_Pin_4 //PE4

#define Hight            1       //�ߵ�ƽ
#define Low              0       //�͵�ƽ

//���ð������µ�ʱ����ɿ���ʱ��ĵ�ƽ״̬
#define key_Press        Hight   //��������ʱ�ĵ�ƽ״̬
#define key_Release      Low     //�����ɿ�ʱ�ĵ�ƽ״̬

////////////////////////////// ÿTime_DELAYMS (ms) ���һ�� //////////////////////////////////////////////
#define Time_DELAYMS 20
////////////////////////////// �϶����� Time_Multiple_Hit * Time_DELAYMS = ������ֵ //////////////////////////
#define Time_Multiple_Hit 100

//��ȡ������״̬
#define k_up GPIO_ReadInputDataBit(GPIOA,K_UP)		  
#define k_down GPIO_ReadInputDataBit(GPIOE,K_DOWN)
#define k_left GPIO_ReadInputDataBit(GPIOE,K_LEFT)
#define k_right GPIO_ReadInputDataBit(GPIOE,K_RIGHT)



void key_Init(void);
//�ڶ�ʱ���жϺ����е��ã���ȡ����״̬
u8 getKeyState();
//��������������λ���尴������ִ����Ӧ������
void key_process();

void key_pros(void);

#endif