//////////////////////////////////////////////////////////////////////////////////	 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB9��SCL��
//              D1   ��PB8��SDA��
//              RES  ��NRST
//              DC   ��PB7
//              CS   ��PB6               
//              ----------------------------------------------------------------
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stdlib.h"	    	

/*Ϊ�˼���*/
#include <stdint.h>
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

/*GD32�Ŀ�*/
#include "gd32e23x.h"

//OLEDģʽ����
//0:4�ߴ���ģʽ������SPIģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  					   
#define OLED_CS_Clr()  gpio_bit_reset(GPIOB,GPIO_PIN_6)//CS
#define OLED_CS_Set()  gpio_bit_set(GPIOB,GPIO_PIN_6)

// #define OLED_RST_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_6)//RES
// #define OLED_RST_Set() gpio_bit_set(GPIOB,GPIO_PIN_6)

#define OLED_DC_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_7)//DC ����or����
#define OLED_DC_Set() gpio_bit_set(GPIOB,GPIO_PIN_7)

/*�����������������ڲ���8080ģʽ*/
// #define OLED_WR_Clr() gpio_bit_reset(GPIOG,GPIO_PIN_6)
// #define OLED_WR_Set() gpio_bit_set(GPIOG,GPIO_PIN_6)

// #define OLED_RD_Clr() gpio_bit_reset(GPIOG,GPIO_PIN_6)
// #define OLED_RD_Set() gpio_bit_set(GPIOG,GPIO_PIN_6)



//PC0~7,��Ϊ������
// #define DATAOUT(x) GPIO_Write(GPIOC,x);//���  
//ʹ��4�ߴ��нӿ�ʱʹ�� 

#define OLED_SCLK_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_9)//CLK����ӦOLED��D0����
#define OLED_SCLK_Set() gpio_bit_set(GPIOB,GPIO_PIN_9)

#define OLED_SDIN_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_8)//DIN����ӦOLED��D1����
#define OLED_SDIN_Set() gpio_bit_set(GPIOB,GPIO_PIN_8)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,char *chr);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



