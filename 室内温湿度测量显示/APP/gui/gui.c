#include "gui.h"

#ifdef USE_FONT_UPDATE
#include "ff.h"
#include "diskio.h"
#endif

#ifdef USE_FLASH_CHAR
#include "flash.h"
#else
#include "asciicode.h"
#endif

#ifdef USE_FONT_UPDATE
#include "malloc.h"
#endif

void get_circle(int x,int y,int r,int col)
{
	int xc=0;
	int yc,p;
	yc=r;
	p=3-(r<<1);	
	while(xc <= yc)
	{
		GUI_Dot(x+xc,y+yc,col);
		GUI_Dot(x+xc,y-yc,col);	
		GUI_Dot(x-xc,y+yc,col);
		GUI_Dot(x-xc,y-yc,col);
		GUI_Dot(x+yc,y+xc,col);	
		GUI_Dot(x+yc,y-xc,col);
		GUI_Dot(x-yc,y+xc,col);
		GUI_Dot(x-yc,y-xc,col);
		if(p<0)
		{
			p += (xc++ << 2) + 6;	
		}
		else
			p += ((xc++ - yc--)<<2) + 10;
	}
}
void draw_circle()	 //��Բ
{
	get_circle(100,200,100,YELLOW);//�����꣬�����꣬�뾶����ɫ
	get_circle(100,200,99,YELLOW);
	get_circle(100,200,98,YELLOW);
	get_circle(100,200,97,YELLOW);
	get_circle(100,200,5,YELLOW);			
}
void draw_dotline()  //�����
{
	u8 i;
	u8 rome[][3]={"12","1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" } ; //�������� 
	int x1,y1,x2,y2,x3,y3;
	for(i=0;i<60;i++)
	{
		x1 = (int)(100 + (sin(i * PI / 30) * 92)); 
		y1 = (int)(100 - (cos(i * PI / 30) * 92)); 
		x2 = (int)(100 + (sin(i * PI / 30) * 97)); 
		y2 = (int)(100 - (cos(i * PI / 30) * 97)); 
		GUI_Line(x1,y1+100,x2,y2+100,RED);

		if(i%5==0)
		{
			x1 = (int)(100 + (sin(i * PI / 30) * 85)); 
			y1 = (int)(100 - (cos(i * PI / 30) * 85)); 
			x2 = (int)(100 + (sin(i * PI / 30) * 97)); 
			y2 = (int)(100 - (cos(i * PI / 30) * 97)); 
			GUI_Line(x1,y1+100,x2,y2+100,RED);	

			x3 = (int)(92 + (sin((i ) * PI / 30) * 80)); 
			y3 = (int)(92 - (cos((i ) * PI / 30) * 80));

			GUI_Show12ASCII(x3,y3+100,rome[i/5],YELLOW,BLACK);
		}
		
	}		
}
void draw_hand(int hhour,int mmin,int ssec)  //��ָ��
{
	int xhour, yhour, xminute, yminute, xsecond, ysecond; //��������ϵָ������
	xhour = (int)(60 * sin( hhour * PI / 6 + mmin * PI / 360 + ssec * PI / 1800)); 
	yhour = (int)(60 * cos( hhour * PI / 6 + mmin * PI / 360 + ssec * PI / 1800)); 
	xminute = (int)(90 * sin( mmin * PI / 30 + ssec * PI / 1800)); 
	yminute = (int)(90 * cos( mmin * PI / 30 + ssec * PI / 1800)); 
	xsecond = (int)(100 * sin( ssec * PI / 30)); 
	ysecond = (int)(100 * cos( ssec * PI / 30)); 

	
	GUI_Line(100 + xhour, 200 - yhour, 100 -xhour / 6, 200 + yhour / 6,RED);
	GUI_Line(100 + xminute, 200 - yminute, 100 -xminute / 4, 200 + yminute / 4,BLUE);
	GUI_Line(100 + xsecond, 200 - ysecond, 100 -xsecond / 3, 200 + ysecond / 3,GREEN);
	
}
void draw_hand_clear(int hhour,int mmin,int ssec)  //��ָ��
{
	int xhour, yhour, xminute, yminute, xsecond, ysecond; //��������ϵָ������
	xhour = (int)(60 * sin( hhour * PI / 6 + mmin * PI / 360 + ssec * PI / 1800)); 
	yhour = (int)(60 * cos( hhour * PI / 6 + mmin * PI / 360 + ssec * PI / 1800)); 
	xminute = (int)(90 * sin( mmin * PI / 30 + ssec * PI / 1800)); 
	yminute = (int)(90 * cos( mmin * PI / 30 + ssec * PI / 1800)); 
	xsecond = (int)(100 * sin( ssec * PI / 30)); 
	ysecond = (int)(100 * cos( ssec * PI / 30)); 

	
	GUI_Line(100 + xhour, 200 - yhour, 100 -xhour / 6, 200 + yhour / 6,BLACK);
	GUI_Line(100 + xminute, 200 - yminute, 100 -xminute / 4, 200 + yminute / 4,BLACK);
	GUI_Line(100 + xsecond, 200 - ysecond, 100 -xsecond / 3, 200 + ysecond / 3,BLACK);
	
}


/****************************************************************************
* Function Name  : GUI_Dot
* Description    : �ڲ������滭һ��
* Input          : x�����X����
*                * y�����Y����
*                * color�������ɫ
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Dot(uint16_t x, uint16_t y, uint16_t color)
{  
	TFT_SetWindow(x, y, x, y);  //���õ��λ��
	TFT_WriteData(color);       //����	
}

void GUI_Line(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color)
{
	u16 t;  
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;  
	int incx, incy;  
	u16 row, col;  
	delta_x = xEnd - xStart;//������������  
	delta_y = yEnd - yStart;  
	col = xStart;  
	row = yStart;  
	if (delta_x > 0)
	{
		incx=1;//���õ�������
	} 	  
	else    
	{  
	    if (delta_x == 0)
		{
			incx = 0;//��ֱ�� 
		} 		 
	    else 
			{
				incx = -1;
				delta_x = -delta_x;
			}  
	}  
	if (delta_y > 0)
	{
		incy = 1;
	}	  
	else  
	{  
	    if (delta_y == 0)
		{
			incy = 0;//ˮƽ��  
		} 
	    else 
		{
			incy = -1;
			delta_y = -delta_y;
		}  
	}  
	if (delta_x > delta_y)
	{ 
		distance = delta_x;//ѡȡ��������������  
	}
	else
	{
		distance = delta_y; 
	} 	
	for (t=0; t<=distance+1; t++)  
	{                                     //�������  
	    GUI_Dot(col, row, color);
	    xerr += delta_x;  
	    yerr += delta_y;  
	  	if(xerr > distance)  
	    {  
	        xerr -= distance;  
	        col += incx;  
	    }  
	    if(yerr > distance)  
	    {  
	        yerr -= distance;  
	        row += incy;  
	    }  
	}  
}
/****************************************************************************
* Function Name  : GUI_Box
* Description    : ��һ������Ϳ����ɫ
* Input          : sx����ʼX����, sy����ʵY����, 
*                * ex����ֹX����, ey����ֹY����,
*                * color���������ɫ
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{ 
	uint16_t temp;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	TFT_SetWindow(xState, yState, xEnd, yEnd); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{	
			TFT_WriteData(color);
		}
	}
}

/****************************************************************************
* Function Name  : GUI_DrowSign
* Description    : ��һ��ʮ�ֵı��
* Input          : x����ǵ�X���ꣻ
*                * y����ǵ�Y����
*                * color����ǵ���ɫ
* Output         : None
* Return         : None
****************************************************************************/

void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;

    /* ���� */
    TFT_SetWindow(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
        TFT_WriteData(color);    
    }

    /* ���� */
    TFT_SetWindow(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
        TFT_WriteData(color);    
    }

    /* ���� */
    TFT_SetWindow(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
        TFT_WriteData(color);    
    }
}

#ifndef USE_FLASH_CHAR
/****************************************************************************
* Function Name  : GUI_Show12ASCII
* Description    : д12��ASCII��
* Input          : x����ʼX����
*                * y����ʼY����
*                * p���ַ����׵�ַ
*                * wordColor��������ɫ
*                * backColor��������ɫ
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Show12ASCII(uint16_t x, uint16_t y, uint8_t *p, 
                     uint16_t wordColor, uint16_t backColor)
{
	uint8_t i, wordByte, wordNum;
	uint16_t color;

	while(*p != '\0')   //����Ƿ������һ����
	{
        /* ���ֿ��е�ASCII���Ǵӿո�ʼ��Ҳ����32��ʼ�ģ����Լ�ȥ32 */
		wordNum = *p - 32;
		
        TFT_SetWindow(x, y, x+7, y+15);           //�ֿ�*��Ϊ��8*16
		for (wordByte=0; wordByte<16; wordByte++) //ÿ����ģһ����16���ֽ�
		{
			color = ASCII8x16[wordNum][wordByte];
			for (i=0; i<8; i++) 
			{
				if ((color&0x80) == 0x80)
				{
					TFT_WriteData(wordColor);
				} 						
				else
				{
					TFT_WriteData(backColor);
				} 	
				color <<= 1;
			}
		}

		p++;    //ָ��ָ����һ����
		
        /* ��Ļ���괦�� */
        x += 8;
        if(x > 233)   //TFT_XMAX -8
        {
            x = 0;
            y += 16;    
        }
	}
}

#else

/****************************************************************************
* Function Name  : GUI_Show12Char
* Description    : ͨ��FLASH�ֿ���ʾ12����ĸ�ͺ��֣�ʹ��GBK��
* Input          : x����ʼX����
*                * y����ʼY����
*                * ch���ַ����׵�ַ
*                * wordColor��������ɫ
*                * backColor��������ɫ
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Show12Char(uint16_t x, uint16_t y, uint8_t *ch, 
                    uint16_t wordColor, uint16_t backColor)
{
    uint8_t i, j, color, buf[32];
    uint16_t asc;
    uint32_t wordAddr = 0;

    while(*ch != '\0')
    {
        /*��ʾ��ĸ */
        if(*ch < 0x80)  //ASCII���0~127
        {
            /* ���ֿ��е�ASCII���Ǵӿո�ʼ��Ҳ����32��ʼ�ģ����Լ�ȥ32 */
    		wordAddr = *ch - 32;
            wordAddr *= 16;
            wordAddr += GUI_FLASH_ASCII_ADDR;
            
            /* ��ȡFLASH�и��ֵ���ģ */
            FLASH_ReadData(buf, wordAddr, 16);
            
            /* ��ʾ������ */		
            TFT_SetWindow(x, y, x+7, y+15);           //�ֿ�*��Ϊ��8*16
    		for (j=0; j<16; j++) //ÿ����ģһ����16���ֽ�
    		{
    			color = buf[j];
    			for (i=0; i<8; i++) 
    			{
    				if ((color&0x80) == 0x80)
    				{
    					TFT_WriteData(wordColor);
    				} 						
    				else
    				{
    					TFT_WriteData(backColor);
    				} 	
    				color <<= 1;
    			}
    		}
    
    		ch++;    //ָ��ָ����һ����
    		
            /* ��Ļ���괦�� */
            x += 8;
            if(x > 233)   //TFT_XMAX -8
            {
                x = 0;
                y += 16;    
            }            
        }
        /* ��ʾ���� */
        else
        {
            /* �����ֱ���ת������FLASH�еĵ�ַ */
            asc = *ch - 0x81;     //���ֽ��Ǳ�ʾ�����������Ǵ�0x81��0xFE,����ת���ɵ�ַ-0x80
            wordAddr = asc * 190; //ÿ������һ����190����
    
            asc = *(ch + 1); //���ֽڴ���ÿ������ÿ��������λ�ã����Ǵ�0x40��0xFF
            if(asc < 0x7F)   //��0x7Fλ���и���λ����������ȡģ�����գ����Դ���0x7F֮����һ
            {
                asc -= 0x40;
            }
            else
            {
                asc -= 0x41;
            }
            
            wordAddr += asc; //�����GBK���ǵڼ�����
            wordAddr *= 32;  //����λ��ת��λFLASH��ַ
            wordAddr += GUI_FLASH_12CHAR_ADDR; //�����׵�ַ
    
            /* ��ȡFLASH�и��ֵ���ģ */
            FLASH_ReadData(buf, wordAddr, 32);
    
            /* �ڲ���������ʾ */
            TFT_SetWindow(x, y, x+15, y+15);
            for(i=0; i<32; i++)
            {
                 
                color = buf[i];            
                for(j=0; j<8; j++) 
        		{
        			if((color & 0x80) == 0x80)
        			{
        				TFT_WriteData(wordColor);
        			} 						
        			else
        			{
        				TFT_WriteData(backColor);
        			} 
        			color <<= 1;
        		}//for(j=0;j<8;j++)����
            }
    
            /* ��Ļ���괦�� */
            x += 16;
            if(x > 225)   //TFT_XMAX -15
            {
                x = 0;
                y += 16;    
            }
    
            /* д��һ���֣�ÿ������ռ�����ֽ�����+2 */
            ch += 2;             
        }
    }    
}
/****************************************************************************
* Function Name  : GUI_Show12Chinese
* Description    : ͨ��FLASH�ֿ���ʾ12�ź��֣�ʹ��GBK��
* Input          : x����ʼX����
*                * y����ʼY����
*                * cn���ַ����׵�ַ
*                * wordColor��������ɫ
*                * backColor��������ɫ
* Output         : None
* Return         : None
****************************************************************************/

void GUI_Show16Chinese(uint16_t x, uint16_t y, uint8_t *cn, 
                       uint16_t wordColor, uint16_t backColor)
{   
    uint8_t i, j, color, buf[63];
    uint16_t asc;
    uint32_t wordAddr = 0;    
    while(*cn != '\0')
    {  
        /* �����ֱ���ת������FLASH�еĵ�ַ */
        asc = *cn - 0x81;     //���ֽ��Ǳ�ʾ�����������Ǵ�0x81��0xFE,����ת���ɵ�ַ-0x80
        wordAddr = asc * 190; //ÿ������һ����190����

        asc = *(cn + 1); //���ֽڴ���ÿ������ÿ��������λ�ã����Ǵ�0x40��0xFF
        if(asc < 0x7F)   //��0x7Fλ���и���λ����������ȡģ�����գ����Դ���0x7F֮����һ
        {
            asc -= 0x40;
        }
        else
        {
            asc -= 0x41;
        }
        
        wordAddr += asc; //�����GBK���ǵڼ�����
        wordAddr *= 63;  //����λ��ת��λFLASH��ַ
        wordAddr += GUI_FLASH_16CHAR_ADDR; //�����׵�ַ

        /* ��ȡFLASH�и��ֵ���ģ */
        FLASH_ReadData(buf, wordAddr, 63);

        /* �ڲ���������ʾ */
        TFT_SetWindow(x, y, x+23, y+20);
        for(i=0; i<63; i++)
        {
            color = buf[i];            
            for(j=0; j<8; j++) 
    		{
    			if((color & 0x80) == 0x80)
    			{
    				TFT_WriteData(wordColor);
    			} 						
    			else
    			{
    				TFT_WriteData(backColor);
    			} 
    			color <<= 1;
    		}//for(j=0;j<8;j++)����
        }

        /* ��Ļ���괦�� */
        x += 21;
        if(x > 218)   //TFT_XMAX -21
        {
            x = 0;
            y += 21;    
        }

        /* д��һ���֣�ÿ������ռ�����ֽ�����+2 */
        cn += 2;      
    }    
}

#endif


#ifdef USE_FONT_UPDATE

/****************************************************************************
* Function Name  : GUI_FontUpdate
* Description    : �����ֿ�
* Input          : updateState��ѡ����µ��ֿ�
* Output         : None
* Return         : None
****************************************************************************/

void GUI_FontUpdate(uint8_t updateState)
{
    FRESULT res;
	FIL fsrc;
	UINT  br;
    uint32_t wordAddr, i, j;

#ifdef __MALLOC_H	
    uint8_t *p;
    p = malloc(4096);                  //����һ���ڴ��
    if(p == 0)
    {
        return;
    }
#else
	uint8_t buffer[512];
#endif    	

    /* ����ASCII�ֿ� */
    if((updateState & GUI_UPDATE_ASCII) == GUI_UPDATE_ASCII)
    {
        /* ����д����ʼ��ַ */
        wordAddr = GUI_FLASH_ASCII_ADDR;
        j = 0;

        /* �򿪶�ȡ�ļ� */
        res = f_open(&fsrc, GUI_ASCII_FILE, FA_READ);	
    	if(res == FR_OK)  //�򿪳ɹ�
        { 
         	for (;;)      //��ʼ��ȡ����
         	{       
#ifdef __MALLOC_H	
                res = f_read(&fsrc, p, 4096, &br);
    
                /* ����ȡ��������д��FLASH */
                FLASH_WriteData(p, wordAddr, br);
          	    wordAddr += br;   //д���ַ����

#else
                res = f_read(&fsrc, buffer, sizeof(buffer), &br);
    
                /* ����ȡ��������д��FLASH */
                FLASH_WriteData(buffer, wordAddr, br);
          	    wordAddr += br;   //д���ַ����
#endif
                j += br;
                i = j * 100 / 1456;
                GUI_Box(0, 80, i, 90, RED);    

                if (res || br == 0)
    			{
    				break;    // error or eof 
    			}
            } 
        }
    	 
        f_close(&fsrc);  //�����Ǵ򿪣������½��ļ���һ���ǵùر�
    }

    /* ����12�ź��ֿ� */
    if((updateState & GUI_UPDATE_12CHAR) == GUI_UPDATE_12CHAR)
    {
        wordAddr = GUI_FLASH_12CHAR_ADDR;
        j = 0;

        res = f_open(&fsrc, GUI_12CHAR_FILE, FA_READ);
    	
    	if(res == FR_OK) 
        {  
         	for (;;)  
         	{      
#ifdef __MALLOC_H	
                res = f_read(&fsrc, p, 4096, &br);
    
                /* ����ȡ��������д��FLASH */
                FLASH_WriteData(p, wordAddr, br);
          	    wordAddr += br;   //д���ַ����
#else
                res = f_read(&fsrc, buffer, sizeof(buffer), &br);
    
                FLASH_WriteData(buffer, wordAddr, br);
          	    wordAddr += br;
#endif
                j += br;
                i = j * 100 / 766080;
                GUI_Box(0, 95, i, 105, RED);    

    
                if (res || br == 0)
    			{
    				break;    // error or eof 
    			}
            } 
        }
        f_close(&fsrc);  //�����Ǵ򿪣������½��ļ���һ���ǵùر�
    }
    
    /* ����16�ź��ֿ� */
    if((updateState & GUI_UPDATE_16CHAR) == GUI_UPDATE_16CHAR)
    {
        
        wordAddr = GUI_FLASH_16CHAR_ADDR;
        j = 0;

        res = f_open(&fsrc, GUI_16CHAR_FILE, FA_READ);	
    	if(res == FR_OK) 
        { 
         	for (;;)  
         	{       
#ifdef __MALLOC_H	
                res = f_read(&fsrc, p, 4096, &br);
    
                /* ����ȡ��������д��FLASH */
                FLASH_WriteData(p, wordAddr, br);
          	    wordAddr += br;   //д���ַ����
#else
                res = f_read(&fsrc, buffer, sizeof(buffer), &br);
    
                FLASH_WriteData(buffer, wordAddr, br);
          	    wordAddr += br;
#endif
                j += br;
                i = j * 100 / 1508220;
                GUI_Box(0, 110, i, 120, RED);    

    
                if (res || br == 0)
    			{
    				break;    // error or eof 
    			}
            } 
        }
    	 
        f_close(&fsrc);  //�����Ǵ򿪣������½��ļ���һ���ǵùر�
    }
#ifdef __MALLOC_H	
    free(p);
#endif
} 
 
#endif


