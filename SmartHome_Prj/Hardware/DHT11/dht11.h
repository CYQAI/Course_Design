#ifndef __DHT11_H
#define __DHT11_H 

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DHT11������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
/*Ϊ�˼���*/
#include <stdint.h>
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

/*GD32�Ŀ�*/
#include "gd32e23x.h"
#include "systick.h"

/*temperature��humidity�����Ͻṹ��*/
typedef struct 
{
    uint8_t temperature;
    uint8_t humidity;
}DHT11;


//IO��������
#define DHT11_IO_IN()     gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_12)  
#define DHT11_IO_OUT()    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_12)

////IO��������											   
#define	DHT11_DQ_OUT_Low  gpio_bit_reset(GPIOA,GPIO_PIN_12) //���ݶ˿�	PA12 
#define	DHT11_DQ_OUT_High gpio_bit_set(GPIOA,GPIO_PIN_12) //���ݶ˿�	PA12 
#define	DHT11_DQ_IN       gpio_input_bit_get(GPIOA,GPIO_PIN_12)  //���ݶ˿�	PA12 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    

#endif















