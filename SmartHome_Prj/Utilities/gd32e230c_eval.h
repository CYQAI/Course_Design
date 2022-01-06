/*!
    \file  gd32e230c_eval.h
    \brief definitions for GD32E230C_EVAL's leds, keys and COM ports hardware resources
    
    \version 2019-02-19, V1.0.0, firmware for GD32E23x
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef GD32E230C_EVAL_H
#define GD32E230C_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "gd32e23x.h"

/*外设驱动*/
#include "oled.h"
#include "dht11.h"
#include "onenet.h"
#include "esp8266.h"
//#include "oled_display.h"

#include <stdio.h>

/* exported types */
typedef enum 
{
    LED0 = 0,
    LED1 = 1,
    LED2 = 2,
}led_typedef_enum;

typedef enum 
{
    KEY0 = 0,
    KEY1 = 1,
    KEY2 = 2,
    KEY3 = 3,
    HC_SR501 = 4,
}key_typedef_enum;

typedef enum 
{
    KEY_MODE_GPIO = 0,
    KEY_MODE_EXTI = 1
}keymode_typedef_enum;

typedef enum 
{
    COM0 = 0,   /*usart0*/
    COM1 = 1    /*usart1*/
}COM_typedef_enum;

/* eval board low layer led */
#define LEDn                             3U

#define LED0_PIN                         GPIO_PIN_6
#define LED0_GPIO_PORT                   GPIOA
#define LED0_GPIO_CLK                    RCU_GPIOA

#define LED1_PIN                         GPIO_PIN_7
#define LED1_GPIO_PORT                   GPIOA
#define LED1_GPIO_CLK                    RCU_GPIOA

#define LED2_PIN                         GPIO_PIN_0
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCU_GPIOB

/* eval board low layer button */  
#define KEYn                             5U

/* KEY0 push-button */
#define KEY0_KEY_PIN                   GPIO_PIN_13
#define KEY0_KEY_GPIO_PORT             GPIOB
#define KEY0_KEY_GPIO_CLK              RCU_GPIOB
#define KEY0_KEY_EXTI_LINE             EXTI_0
#define KEY0_KEY_EXTI_PORT_SOURCE      EXTI_SOURCE_GPIOA
#define KEY0_KEY_EXTI_PIN_SOURCE       EXTI_SOURCE_PIN0
#define KEY0_KEY_EXTI_IRQn             EXTI0_1_IRQn

/* KEY1 push-button */
#define KEY1_KEY_PIN                   GPIO_PIN_14
#define KEY1_KEY_GPIO_PORT             GPIOB
#define KEY1_KEY_GPIO_CLK              RCU_GPIOB
#define KEY1_KEY_EXTI_LINE             EXTI_13
#define KEY1_KEY_EXTI_PORT_SOURCE      EXTI_SOURCE_GPIOC
#define KEY1_KEY_EXTI_PIN_SOURCE       EXTI_SOURCE_PIN13
#define KEY1_KEY_EXTI_IRQn             EXTI4_15_IRQn

/* KEY2 push-button */
#define KEY2_KEY_PIN                   GPIO_PIN_15
#define KEY2_KEY_GPIO_PORT             GPIOB
#define KEY2_KEY_GPIO_CLK              RCU_GPIOB

/* KEY3 push-button */
#define KEY3_KEY_PIN                   GPIO_PIN_12
#define KEY3_KEY_GPIO_PORT             GPIOB
#define KEY3_KEY_GPIO_CLK              RCU_GPIOB

/* HC-SR501 数据监测 */
#define HC_SR501_PIN                   GPIO_PIN_1
#define HC_SR501_GPIO_PORT             GPIOA
#define HC_SR501_GPIO_CLK              RCU_GPIOA
#define HC_SR501_EXTI_LINE             EXTI_1
#define HC_SR501_EXTI_PORT_SOURCE      EXTI_SOURCE_GPIOA
#define HC_SR501_EXTI_PIN_SOURCE       EXTI_SOURCE_PIN1
#define HC_SR501_EXTI_IRQn             EXTI0_1_IRQn

/* eval board low layer COM */
#define COMn                             2U

/* definition for COM, connected to USART0 */
#define EVAL_COM                         USART0
#define EVAL_COM_CLK                     RCU_USART0

#define EVAL_COM_TX_PIN                  GPIO_PIN_9
#define EVAL_COM_RX_PIN                  GPIO_PIN_10

#define EVAL_COM_GPIO_PORT               GPIOA
#define EVAL_COM_GPIO_CLK                RCU_GPIOA
#define EVAL_COM_AF                      GPIO_AF_1

/* definition for COM, connected to USART1 */
#define EVAL_COM1                         USART1
#define EVAL_COM1_CLK                     RCU_USART1

#define EVAL_COM1_TX_PIN                  GPIO_PIN_2
#define EVAL_COM1_RX_PIN                  GPIO_PIN_3

#define EVAL_COM1_GPIO_PORT               GPIOA
#define EVAL_COM1_GPIO_CLK                RCU_GPIOA
#define EVAL_COM1_AF                      GPIO_AF_1

/* function declarations */
/* configure led GPIO */
void gd_eval_led_init(led_typedef_enum lednum);
/* turn on selected led */
void gd_eval_led_on(led_typedef_enum lednum);
/* turn off selected led */
void gd_eval_led_off(led_typedef_enum lednum);
/* toggle the selected led */
void gd_eval_led_toggle(led_typedef_enum lednum);
/* configure key */
void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum keymode);
/* return the selected key state */
uint8_t gd_eval_key_state_get(key_typedef_enum keynum);
/* configure COM port */
void gd_eval_com_init(COM_typedef_enum COM_ID);
/*与esp8266沟通的串口*/
void Usart_SendString(char *str, unsigned short len);
/*板子的资源初始化*/
void eval_init(void);
/*HC-SR501检测*/
void HC_SR501_check(void);


#ifdef __cplusplus
}
#endif

#endif /* GD32E230C_EVAL_H */

