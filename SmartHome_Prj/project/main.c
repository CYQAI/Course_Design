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
#include "main.h"
#include "gd32e230c_eval.h"

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
	unsigned short timeCount = 0;	//发送间隔变量
	
	unsigned char *dataPtr = NULL;
	/* configure systick */
    systick_config();
	
	/*板子的资源初始化*/
    eval_init();
  		
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
				
				WIFI_Send(500); //发送间隔5s
				
			
				HC_SR501_check();	
    }
		
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM, USART_FLAG_TBE));

    return ch;
}
