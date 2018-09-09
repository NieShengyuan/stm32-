#include "public.h"
#include "dht11.h"
#include "printf.h"
#include "systick.h"
#include "gui.h"
#include "led.h"
#include "key.h"
#include "ds18b20.h"
#include "adc.h"
/*********************************************************************************
*��Ŀ��������ʪ�Ȳ�����ʾ
*					���ף����������ϴ�����ݮ�ɣ�����ݮ��������΢�ſͻ���
*
*Һ������ʾ���ݣ�
*dht11--PA0
*
**********************************************************************************/

u8 posH=100;
u8 posW=160;

int main()
{	
	u8 i=0;
	u32 ad_Value=0;//light intensity
	char tempSensorValue[5];
	u8 temperature_Value;  	    
	u8 humidity_Value;
	char temperature[4];
	char humidity[4];
	char ad[4];
	//��ʼ������
	SystemInit();
	adc_init();
	printf_init();	 //printf��ʼ��
	LED_Init();	  //�˿ڳ�ʼ��
	ds18b20_init();
	GPIO_Write(GPIOC,(u16)(0xff));
	TFT_Init();
	TFT_ClearScreen(BLACK);
	GUI_Show12ASCII(10,10,"This is a test project!",YELLOW,BLACK);
	printf("Waveshare!\r\n");
	while(DHT11_Init());
	
	//printf("start project\n\n");
	while(1)
	{
		delay_ms(2000);
		GUI_Show12ASCII(20,60,"tempure is ",YELLOW,BLACK);
		GUI_Show12ASCII(20,80,"tempure is ",YELLOW,BLACK);
		GUI_Show12ASCII(20,100,"humidity is ",YELLOW,BLACK);
		GUI_Show12ASCII(20,120,"light indensity is ",YELLOW,BLACK);
		
		//ds18b20 get temperature
		sprintf(tempSensorValue,"%.2lf", readtemp() ); //������λС��������λ��������;  //��ȡ�¶�
		printf("%0.2lf\r\n",readtemp());	
		GUI_Show12ASCII(190,60,tempSensorValue,YELLOW,BLACK);
		
		//dht11 temperature
		DHT11_Read_Data(&temperature_Value,&humidity_Value);
		sprintf(temperature,"%d", temperature_Value);
		sprintf(humidity,"%d", humidity_Value);
		GUI_Show12ASCII(190,80,temperature,YELLOW,BLACK);
		GUI_Show12ASCII(190,100,humidity,YELLOW,BLACK);		
		//printf("temperature=%d\r\n",temperature);
		//printf("humidity=%d\r\n",humidity);
		
		//light indensity
		ad_Value=0;
		for(i=0;i<50;i++)
		{
			ADC_SoftwareStartConvCmd(ADC1,ENABLE);
			while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//ת��������־λ
			ad_Value=ad_Value/50;
		}
		sprintf(ad,"%.2f", ad_Value*3.3/4096);
		printf("%.4f",ad_Value*3.3/4096);
		GUI_Show12ASCII(190,120,ad,YELLOW,BLACK);
	}			
}




