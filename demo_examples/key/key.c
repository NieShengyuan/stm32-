#include "key.h"
#include "systick.h"
/**
  * @brief  getKeyValue .
  * @param  多个按键状态检测（5向开关检测按键）
  * @retval 
  *
  *
  *   注意：
  *			1.定时器每20ms检测一次，包括消抖、短按检测、长按检测
			2.按键处理函数负责测定是哪个按键按下，短按还是长按，然后放入队列
			3.主函数负责处理队列数据
  *
  *
  *
  
  */
////////////////////////////////////////////////////////////////////////////////////////////
//1.定时器每20ms检测一次，包括消抖、短按检测、长按检测
//2.按键处理函数负责测定是哪个按键按下，短按还是长按，然后放入队列
//3.主函数负责处理队列数据
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////

//指向按键状态变量按键状态（0-未按）（1-短按）（2-长按）
int *keyState;
//定时器中断函数使用
s8 key_mode=0;//按键状态处理标志
u8 key_con=0;//统计按键持续时间
//获取所有按键的状态，保存
int key[4];
int *keyInput = &key[0];

u8 getKeyState()
{
	//1.定时器每20ms检测一次，包括消抖、短按检测、长按检测
    //2.按键处理函数负责测定是哪个按键按下，短按还是长按，然后放入队列
    //3.主函数负责处理队列数据
	//4.返回值为按键状态（0-未按）（1-短按）（2-长按）
	static s8 key_state=0;//按键状态（0-未按）（1-短按）（2-长按）
	
	key[0]=k_up;
    key[1]=k_down;
	key[2]=k_left;
	key[3]=k_right;
	
	switch(key_mode)
	{
		case 0://初始状态
			if(k_up==key_Press || k_down==key_Press || k_left==key_Press || k_right==key_Press)
			{
				key_mode = 1;//按下检测
			}break;
			
		case 1://按下待确认状态
			if(k_up==key_Press || k_down==key_Press || k_left==key_Press || k_right==key_Press)
			{
				key_mode = 2;//确认按下
			}break;
			
		case 2://消抖完成并确认按下状态
			//持续按下
			if(k_up==key_Press || k_down==key_Press || k_left==key_Press || k_right==key_Press)
			{
				key_con ++;
				//防止按下时间过长
				if(key_con > Time_Multiple_Hit * 10)
					key_con = Time_Multiple_Hit * 10;
			}
			//释放按键
			else
			{
				if(key_con < Time_Multiple_Hit)
					key_state = 1;//短按
				else
					key_state = 2;//长按
				
				key_con = 0;//计数清零
				key_mode = 0;
			}break;
		default:break;
	}
	return key_state;
}


void key_process()
{
	//结合 u8 getKeyState() 判定哪个按键按下，并运行其对应任务
	*keyState = getKeyState();//获取按键状态
	/////////////////////////////////////////////////
	if(*keyState != 0)
	{
		//注意优先级
		if(keyState[0] == key_Press)
		{
			if(*keyState == 1)
			{
				//短按任务
			}
			else
			{
				//长按任务
			}
		}
		else if(keyState[1] == key_Press)
		{
			if(*keyState == 1)
			{
				//短按任务
			}
			else
			{
				//长按任务
			}		
		}
		else if(keyState[2] == key_Press)
		{
			if(*keyState == 1)
			{
				//短按任务
			}
			else
			{
				//长按任务
			}
		}
		else if(keyState[3] == key_Press)
		{
			if(*keyState == 1)
			{
				//短按任务
			}
			else
			{
				//长按任务
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
	if(k_up==1)	  //判断按键k_up是否按下
	{
		delay_ms(10); //消抖处理
		if(k_up==1)	 //再次判断按键k_up是否按下
		{
			GPIO_Write(GPIOC,(u16)0xfe);			
		}
		while(k_up); //等待按键松开
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
	GPIO_InitTypeDef GPIO_InitStructure;	  //声明一个结构体变量，用来初始化GPIO

	SystemInit();
	// 开启GPIO时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

	//  配置GPIO的模式和IO口
	GPIO_InitStructure.GPIO_Pin=K_UP;	   //选择设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//下拉输入  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_Init(GPIOA,&GPIO_InitStructure);		  // 初始化GPIO 
	
	GPIO_InitStructure.GPIO_Pin=K_DOWN|K_LEFT|K_RIGHT;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
				
	GPIO_ResetBits(GPIOA,K_UP);	//对K_UP初始化输出0
}