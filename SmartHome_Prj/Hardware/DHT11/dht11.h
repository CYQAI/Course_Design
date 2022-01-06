#ifndef __DHT11_H
#define __DHT11_H 

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DHT11数字温湿度传感器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/12
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
/*为了兼容*/
#include <stdint.h>
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

/*GD32的库*/
#include "gd32e23x.h"
#include "systick.h"

/*temperature，humidity的联合结构体*/
typedef struct 
{
    uint8_t temperature;
    uint8_t humidity;
}DHT11;

/*dht11结构声明*/
extern DHT11 dht11;

//IO方向设置
#define DHT11_IO_IN()     gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_12)  
#define DHT11_IO_OUT()    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_12)

////IO操作函数											   
#define	DHT11_DQ_OUT_Low  gpio_bit_reset(GPIOA,GPIO_PIN_12) //数据端口	PA12 
#define	DHT11_DQ_OUT_High gpio_bit_set(GPIOA,GPIO_PIN_12) //数据端口	PA12 
#define	DHT11_DQ_IN       gpio_input_bit_get(GPIOA,GPIO_PIN_12)  //数据端口	PA12 


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    

#endif















