//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PB9（SCL）
//              D1   接PB8（SDA）
//              RES  接NRST
//              DC   接PB7
//              CS   接PB6               
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stdlib.h"	    	

/*为了兼容*/
#include <stdint.h>
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

/*GD32的库*/
#include "gd32e23x.h"

//OLED模式设置
//0:4线串行模式，即是SPI模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   
#define OLED_CS_Clr()  gpio_bit_reset(GPIOB,GPIO_PIN_6)//CS
#define OLED_CS_Set()  gpio_bit_set(GPIOB,GPIO_PIN_6)

// #define OLED_RST_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_6)//RES
// #define OLED_RST_Set() gpio_bit_set(GPIOB,GPIO_PIN_6)

#define OLED_DC_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_7)//DC 数据or命令
#define OLED_DC_Set() gpio_bit_set(GPIOB,GPIO_PIN_7)

/*以下两个引脚是用于并行8080模式*/
// #define OLED_WR_Clr() gpio_bit_reset(GPIOG,GPIO_PIN_6)
// #define OLED_WR_Set() gpio_bit_set(GPIOG,GPIO_PIN_6)

// #define OLED_RD_Clr() gpio_bit_reset(GPIOG,GPIO_PIN_6)
// #define OLED_RD_Set() gpio_bit_set(GPIOG,GPIO_PIN_6)



//PC0~7,作为数据线
// #define DATAOUT(x) GPIO_Write(GPIOC,x);//输出  
//使用4线串行接口时使用 

#define OLED_SCLK_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_9)//CLK，对应OLED的D0引脚
#define OLED_SCLK_Set() gpio_bit_set(GPIOB,GPIO_PIN_9)

#define OLED_SDIN_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_8)//DIN，对应OLED的D1引脚
#define OLED_SDIN_Set() gpio_bit_set(GPIOB,GPIO_PIN_8)

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
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
	 



