/*!
    \file    main.c
    \brief   led spark with systick, USART print and key example
    
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

#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "gd32e230c_eval.h"

/*定义温湿度结构*/
DHT11 dht11;

/*!
    \brief      toggle the led every 500ms
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_spark(void)
{
    static __IO uint32_t timingdelaylocal = 0U;

    if(timingdelaylocal){

        if(timingdelaylocal < 500U){
            gd_eval_led_on(LED1);
        }else{
            gd_eval_led_off(LED1);
        }

        timingdelaylocal--;
    }else{
        timingdelaylocal = 1000U;
    }
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
    /* configure systick */
    systick_config();

    /* initilize the LEDs, USART and key */
    gd_eval_led_init(LED0);   
    gd_eval_led_init(LED1); 
    gd_eval_led_init(LED2); 

    gd_eval_com_init(EVAL_COM);

    gd_eval_key_init(KEY0, KEY_MODE_GPIO);
    gd_eval_key_init(KEY1, KEY_MODE_GPIO);
    gd_eval_key_init(KEY2, KEY_MODE_GPIO);
    gd_eval_key_init(KEY3, KEY_MODE_GPIO);


    /*initilize OLED*/
    OLED_Init();
	OLED_Clear(); 

    /*initilize DHT11*/
    while(DHT11_Init())	//DHT11初始化	
	{
        printf("DHT11 Error");
 		delay_1ms(200);
	}    

    /*initilize HC_SR501接口*/
    gd_eval_key_init(HC_SR501,KEY_MODE_EXTI);
    
    gd_eval_led_on(LED0);
    gd_eval_led_on(LED1);
    gd_eval_led_on(LED2);

    OLED_ShowString(0,6,"ASCII:");  
	OLED_ShowString(63,6,"CODE:");  

    /* print out the clock frequency of system, AHB, APB1 and APB2 */
    printf("CK_SYS is %d\r\n", rcu_clock_freq_get(CK_SYS));
    printf("CK_AHB is %d\r\n", rcu_clock_freq_get(CK_AHB));
    printf("CK_APB1 is %d\r\n", rcu_clock_freq_get(CK_APB1));


    while (1)
    {
        /*测试按键是否正常*/
        if(SET == gd_eval_key_state_get(KEY0)){
            printf("KEY0 down\r\n");
        }
        if(SET == gd_eval_key_state_get(KEY1)){
            printf("KEY1 down\r\n");
        }
        if(SET == gd_eval_key_state_get(KEY2)){
            printf("KEY2 down\r\n");
        }
         if(SET == gd_eval_key_state_get(KEY3)){
            printf("KEY3 down\r\n");
        }

        DHT11_Read_Data(&dht11.temperature,&dht11.humidity);					    
        printf("temperature=%d  humidity=%d\r\n",dht11.temperature,dht11.humidity);
    
        delay_1ms(200);
    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM, USART_FLAG_TBE));

    return ch;
}
