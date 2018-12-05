#include "key.h"
#include "systick.h"
/**
  * @brief  getKeyValue .
  * @param  �������״̬��⣨5�򿪹ؼ�ⰴ����
  * @retval 
  *
  *
  *   ע�⣺
  *			1.��ʱ��ÿ20ms���һ�Σ������������̰���⡢�������
			2.��������������ⶨ���ĸ��������£��̰����ǳ�����Ȼ��������
			3.�������������������
  *
  *
  *
  
  */
////////////////////////////////////////////////////////////////////////////////////////////
//1.��ʱ��ÿ20ms���һ�Σ������������̰���⡢�������
//2.��������������ⶨ���ĸ��������£��̰����ǳ�����Ȼ��������
//3.�������������������
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////

//ָ�򰴼�״̬��������״̬��0-δ������1-�̰�����2-������
int *keyState;
//��ʱ���жϺ���ʹ��
s8 key_mode=0;//����״̬�����־
u8 key_con=0;//ͳ�ư�������ʱ��
//��ȡ���а�����״̬������
int key[4];
int *keyInput = &key[0];

u8 getKeyState()
{
	//1.��ʱ��ÿ20ms���һ�Σ������������̰���⡢�������
    //2.��������������ⶨ���ĸ��������£��̰����ǳ�����Ȼ��������
    //3.�������������������
	//4.����ֵΪ����״̬��0-δ������1-�̰�����2-������
	static s8 key_state=0;//����״̬��0-δ������1-�̰�����2-������
	
	key[0]=k_up;
    key[1]=k_down;
	key[2]=k_left;
	key[3]=k_right;
	
	switch(key_mode)
	{
		case 0://��ʼ״̬
			if(k_up==key_Press || k_down==key_Press || k_left==key_Press || k_right==key_Press)
			{
				key_mode = 1;//���¼��
			}break;
			
		case 1://���´�ȷ��״̬
			if(k_up==key_Press || k_down==key_Press || k_left==key_Press || k_right==key_Press)
			{
				key_mode = 2;//ȷ�ϰ���
			}break;
			
		case 2://������ɲ�ȷ�ϰ���״̬
			//��������
			if(k_up==key_Press || k_down==key_Press || k_left==key_Press || k_right==key_Press)
			{
				key_con ++;
				//��ֹ����ʱ�����
				if(key_con > Time_Multiple_Hit * 10)
					key_con = Time_Multiple_Hit * 10;
			}
			//�ͷŰ���
			else
			{
				if(key_con < Time_Multiple_Hit)
					key_state = 1;//�̰�
				else
					key_state = 2;//����
				
				key_con = 0;//��������
				key_mode = 0;
			}break;
		default:break;
	}
	return key_state;
}


void key_process()
{
	//��� u8 getKeyState() �ж��ĸ��������£����������Ӧ����
	*keyState = getKeyState();//��ȡ����״̬
	/////////////////////////////////////////////////
	if(*keyState != 0)
	{
		//ע�����ȼ�
		if(keyState[0] == key_Press)
		{
			if(*keyState == 1)
			{
				//�̰�����
			}
			else
			{
				//��������
			}
		}
		else if(keyState[1] == key_Press)
		{
			if(*keyState == 1)
			{
				//�̰�����
			}
			else
			{
				//��������
			}		
		}
		else if(keyState[2] == key_Press)
		{
			if(*keyState == 1)
			{
				//�̰�����
			}
			else
			{
				//��������
			}
		}
		else if(keyState[3] == key_Press)
		{
			if(*keyState == 1)
			{
				//�̰�����
			}
			else
			{
				//��������
			}
		}
	}
}	





  
  
  
  
/**
  * @brief  key_pros .
  * @param  void
  * @retval None
  */
void key_pros()
{
	if(k_up==1)	  //�жϰ���k_up�Ƿ���
	{
		delay_ms(10); //��������
		if(k_up==1)	 //�ٴ��жϰ���k_up�Ƿ���
		{
			GPIO_Write(GPIOC,(u16)0xfe);			
		}
		while(k_up); //�ȴ������ɿ�
	}
	if(k_down==0)
	{
		delay_ms(10);
		if(k_down==0)
		{
			GPIO_Write(GPIOC,(u16)(0xfd));		
		}
		while(!k_down);
	}
	if(k_left==0)
	{
		delay_ms(10);
		if(k_left==0)
		{
			GPIO_Write(GPIOC,(u16)(0xfb));		
		}
		while(!k_left);
	}
	if(k_right==0)
	{
		delay_ms(10);
		if(k_right==0)
		{
			GPIO_Write(GPIOC,(u16)(0xf7));		
		}
		while(!k_right);
	}	
}

/**
  * @brief  key_Init .
  * @param  void
  * @retval None
  */
void key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	  //����һ���ṹ�������������ʼ��GPIO

	SystemInit();
	// ����GPIOʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

	//  ����GPIO��ģʽ��IO��
	GPIO_InitStructure.GPIO_Pin=K_UP;	   //ѡ�����õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//��������  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //���ô�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);		  // ��ʼ��GPIO 
	
	GPIO_InitStructure.GPIO_Pin=K_DOWN|K_LEFT|K_RIGHT;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
				
	GPIO_ResetBits(GPIOA,K_UP);	//��K_UP��ʼ�����0
}