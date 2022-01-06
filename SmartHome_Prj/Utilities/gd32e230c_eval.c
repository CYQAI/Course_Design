/*!
    \file  gd32e230c_eval.c
    \brief firmware functions to manage leds, keys, COM ports
    
    \version 2019-02-19, V1.0.0, firmware for GD32E23X
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

#include "gd32e230c_eval.h"

/* private variables */
/*LED*/
static const uint32_t GPIO_PORT[LEDn]       = {LED0_GPIO_PORT,
                                               LED1_GPIO_PORT,
                                               LED2_GPIO_PORT};

static const uint32_t GPIO_PIN[LEDn]        = {LED0_PIN,
                                               LED1_PIN,
                                               LED2_PIN};

static const rcu_periph_enum GPIO_CLK[LEDn] = {LED0_GPIO_CLK,
                                               LED1_GPIO_CLK,
                                               LED2_GPIO_CLK};
/*usart COM*/
static const uint32_t COM[COMn]      = {EVAL_COM,
                                        EVAL_COM1
                                       };

static const rcu_periph_enum COM_CLK[COMn]  = {EVAL_COM_CLK,
                                               EVAL_COM1_CLK
                                               };

static const uint32_t COM_TX_PIN[COMn]      = {EVAL_COM_TX_PIN,
                                               EVAL_COM1_TX_PIN
                                              };

static const uint32_t COM_RX_PIN[COMn]      = {EVAL_COM_RX_PIN,
                                               EVAL_COM1_RX_PIN
                                              };

/*KEY*/
static const uint32_t KEY_PORT[KEYn]        = {KEY0_KEY_GPIO_PORT, 
                                               KEY1_KEY_GPIO_PORT,
                                               KEY2_KEY_GPIO_PORT,
                                               KEY3_KEY_GPIO_PORT,
                                               HC_SR501_GPIO_PORT
                                               };

static const uint32_t KEY_PIN[KEYn]         = {KEY0_KEY_PIN, 
                                               KEY1_KEY_PIN,
                                               KEY2_KEY_PIN,
                                               KEY3_KEY_PIN,
                                               HC_SR501_PIN
                                               };

static const rcu_periph_enum KEY_CLK[KEYn]  = {KEY0_KEY_GPIO_CLK, 
                                               KEY1_KEY_GPIO_CLK,
                                               KEY2_KEY_GPIO_CLK,
                                               KEY3_KEY_GPIO_CLK,
                                               HC_SR501_GPIO_CLK
                                               };

/*这里只是简单设置按键为输入模式，采用查询方式，不用外部中断*/
static const exti_line_enum KEY_EXTI_LINE[KEYn] = {KEY0_KEY_EXTI_LINE,
                                                   KEY1_KEY_EXTI_LINE,
                                                   KEY1_KEY_EXTI_LINE,
                                                   KEY1_KEY_EXTI_LINE,
                                                   HC_SR501_EXTI_LINE
                                                   };

static const uint8_t KEY_PORT_SOURCE[KEYn]      = {KEY0_KEY_EXTI_PORT_SOURCE,
                                                   KEY1_KEY_EXTI_PORT_SOURCE,
                                                   KEY1_KEY_EXTI_PORT_SOURCE,
                                                   KEY1_KEY_EXTI_PORT_SOURCE,
                                                   HC_SR501_EXTI_PORT_SOURCE
                                                   };

static const uint8_t KEY_PIN_SOURCE[KEYn]       = {KEY0_KEY_EXTI_PIN_SOURCE,
                                                   KEY1_KEY_EXTI_PIN_SOURCE,
                                                   KEY1_KEY_EXTI_PIN_SOURCE,
                                                   KEY1_KEY_EXTI_PIN_SOURCE,
                                                   HC_SR501_EXTI_PIN_SOURCE
                                                   };

static const uint8_t KEY_IRQn[KEYn]             = {KEY0_KEY_EXTI_IRQn, 
                                                   KEY1_KEY_EXTI_IRQn,
                                                   KEY1_KEY_EXTI_IRQn,
                                                   KEY1_KEY_EXTI_IRQn,
                                                   HC_SR501_EXTI_IRQn
                                                   };

/* eval board low layer private functions */
/*!
    \brief      configure led GPIO
    \param[in]  lednum: specify the led to be configured
      \arg        LED0
      \arg        LED1
      \arg        LED2
    \param[out] none
    \retval     none
*/
void gd_eval_led_init(led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIO_PORT[lednum], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN[lednum]);
    gpio_output_options_set(GPIO_PORT[lednum], GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the led to be turned on
      \arg        LED0
      \arg        LED1
      \arg        LED2
    \param[out] none
    \retval     none
*/
void gd_eval_led_on(led_typedef_enum lednum)
{
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the led to be turned off
      \arg        LED0
      \arg        LED1
      \arg        LED2
    \param[out] none
    \retval     none
*/
void gd_eval_led_off(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      toggle selected led
    \param[in]  lednum: specify the led to be toggled
      \arg        LED0
      \arg        LED1
      \arg        LED2
    \param[out] none
    \retval     none
*/
void gd_eval_led_toggle(led_typedef_enum lednum)
{
    GPIO_TG(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      configure key
    \param[in]  keynum: specify the key to be configured
      \arg        KEY_TAMPER: tamper key
      \arg        KEY_WAKEUP: wakeup key
    \param[in]  keymode: specify button mode
      \arg        KEY_MODE_GPIO: key will be used as simple IO
      \arg        KEY_MODE_EXTI: key will be connected to EXTI line with interrupt
    \param[out] none
    \retval     none
*/
void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum keymode)
{
    /* enable the key clock */
    rcu_periph_clock_enable(KEY_CLK[keynum]);
    rcu_periph_clock_enable(RCU_CFGCMP);

    /* configure button pin as input */
    gpio_mode_set(KEY_PORT[keynum], GPIO_MODE_INPUT, GPIO_PUPD_NONE, KEY_PIN[keynum]);

    if (keymode == KEY_MODE_EXTI) {
        /* enable and set key EXTI interrupt to the lowest priority */
        nvic_irq_enable(KEY_IRQn[keynum], 2U);

        /* connect key EXTI line to key GPIO pin */
        syscfg_exti_line_config(KEY_PORT_SOURCE[keynum], KEY_PIN_SOURCE[keynum]);

        /* configure key EXTI line */
        exti_init(KEY_EXTI_LINE[keynum], EXTI_INTERRUPT, EXTI_TRIG_RISING);
        exti_interrupt_flag_clear(KEY_EXTI_LINE[keynum]);
    }
}

/*!
    \brief      return the selected key state
    \param[in]  keynum: specify the key to be checked
      \arg        KEY_TAMPER: tamper key
      \arg        KEY_WAKEUP: wakeup key
    \param[out] none
    \retval     the key's GPIO pin value
*/
uint8_t gd_eval_key_state_get(key_typedef_enum keynum)
{
    return gpio_input_bit_get(KEY_PORT[keynum], KEY_PIN[keynum]);
}

/*!
    \brief      configure COM port
    \param[in]  com: COM on the board
      \arg        EVAL_COM: COM on the board
    \param[out] none
    \retval     none
*/
void gd_eval_com_init(COM_typedef_enum COM_ID)
{

    /* enable COM GPIO clock */
    rcu_periph_clock_enable(EVAL_COM_GPIO_CLK);

    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[COM_ID]);

    /* connect port to USARTx_Tx */
    gpio_af_set(EVAL_COM_GPIO_PORT, EVAL_COM_AF, COM_TX_PIN[COM_ID]);

    /* connect port to USARTx_Rx */
    gpio_af_set(EVAL_COM_GPIO_PORT, EVAL_COM_AF, COM_RX_PIN[COM_ID]);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(EVAL_COM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_TX_PIN[COM_ID]);
    gpio_output_options_set(EVAL_COM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, COM_TX_PIN[COM_ID]);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(EVAL_COM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_RX_PIN[COM_ID]);
    gpio_output_options_set(EVAL_COM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, COM_RX_PIN[COM_ID]);

    /* USART configure */
    usart_deinit(COM[COM_ID]);
    usart_baudrate_set(COM[COM_ID], 115200U);
    usart_receive_config(COM[COM_ID], USART_RECEIVE_ENABLE);
    usart_transmit_config(COM[COM_ID], USART_TRANSMIT_ENABLE);

    usart_enable(COM[COM_ID]);
}

/*!
    \brief      与esp8266沟通的串口
    \param[in]  str: 字符数组的指针
    \param[in]  len: 字符数组的大小
    \param[out] none
    \retval     none
*/
void Usart_SendString(char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		usart_data_transmit(EVAL_COM1, *str++);									//发送数据
		while(usart_flag_get(EVAL_COM1, USART_FLAG_TBE) == RESET);		//等待发送完成
	}

}

/*!
    \brief      板子的资源初始化
    \param[in]  none
    \param[out] none
    \retval     none
*/
void eval_init(void)
{
	nvic_irq_enable(USART1_IRQn, 0);
	
    /* initilize the LEDs, USART and key */
    gd_eval_led_init(LED0);   
    gd_eval_led_init(LED1); 
    gd_eval_led_init(LED2); 

    gd_eval_com_init(COM0);
    gd_eval_com_init(COM1);
	
	usart_interrupt_enable(USART1, USART_INT_RBNE);
   
    gd_eval_key_init(KEY0, KEY_MODE_GPIO);
    gd_eval_key_init(KEY1, KEY_MODE_GPIO);
    gd_eval_key_init(KEY2, KEY_MODE_GPIO);
    gd_eval_key_init(KEY3, KEY_MODE_GPIO);


    /*initilize OLED*/
    OLED_Init();
	OLED_Clear(); 
		
	/*initilize ESP8266*/
	ESP8266_Init();	

    /*initilize DHT11*/
    while(DHT11_Init())	
	{
        printf("DHT11 Error");
 		delay_1ms(200);
	}    

    /*initilize HC_SR501接口*/
    gd_eval_key_init(HC_SR501,KEY_MODE_EXTI);
}

/*!
    \brief      HC-SR501检测
    \param[in]  none
    \param[out] none
    \retval     none
	\note		HC-SR501检测到有人会点亮LED0（中断那里），
				这里检测到低电平（无人），灯灭
				这个放在后面执行，HC-SR501一上电初始化1S
*/
void HC_SR501_check(void)
{
	if(RESET == gd_eval_key_state_get(HC_SR501)){
		gd_eval_led_off(LED0);
	}
}

