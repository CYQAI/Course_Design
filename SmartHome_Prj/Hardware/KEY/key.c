#include "key.h"

uint8_t key_value=0;
int page_num=0;
const uint8_t Up_key_MASK = 0x08;		//0000 1000
const uint8_t Down_key_MASK = 0x04;		//0000 0100
const uint8_t Left_key_MASK = 0x02;		//0000 0010
const uint8_t Right_key_MASK = 0x01;	//0000 0001


uint8_t get_key_value(void)
{
	
	uint8_t key_value_now=0;	
	
	if(SET == gd_eval_key_state_get(KEY0)){
		delay_1ms(1);
		while(SET == gd_eval_key_state_get(KEY0));
		
		key_value_now = Up_key_MASK;
		printf("KEY0 down\r\n");
	}
	else if(SET == gd_eval_key_state_get(KEY1)){
		delay_1ms(1);
		while(SET == gd_eval_key_state_get(KEY1));
	
		key_value_now = Down_key_MASK;		
		printf("KEY1 down\r\n");
	}
	else if(SET == gd_eval_key_state_get(KEY2)){
		delay_1ms(1);
		while(SET == gd_eval_key_state_get(KEY2));
		key_value_now = Right_key_MASK;		
		printf("KEY2 down\r\n");
	}
	else if(SET == gd_eval_key_state_get(KEY3)){
		delay_1ms(1);
		while(SET == gd_eval_key_state_get(KEY3));
		key_value_now = Left_key_MASK;		
		printf("KEY3 down\r\n");
	}
	return key_value_now;
}

void key_ctrl_picture(void)
{
	uint8_t key_value_cur=0;
	
	display_page[page_num]();

	key_value_cur = get_key_value();
	
	if(key_value_cur == Right_key_MASK){
		page_num++;
		if(page_num == 3) page_num = 0;
		OLED_Clear(); 
	}
	if(key_value_cur == Left_key_MASK){
		page_num--;
		if(page_num == -1) page_num = 2;
		OLED_Clear(); 		
	}
	if(key_value_cur == Up_key_MASK && (page_num == 1 || page_num == 2)){
		if(page_num == 1){
			dht11_warning.temperature++;
		}
		if(page_num == 2){
			dht11_warning.humidity++;
		}		
	}	
	if(key_value_cur == Down_key_MASK && (page_num == 1 || page_num == 2)){
		if(page_num == 1){
			dht11_warning.temperature--;
		}
		if(page_num == 2){
			dht11_warning.humidity--;
		}	
	}
}

void LED_warning(void)
{
		if(dht11.temperature >= dht11_warning.temperature)
				gd_eval_led_toggle(LED1);
		else gd_eval_led_off(LED1);
		if(dht11.humidity >= dht11_warning.humidity)
				gd_eval_led_toggle(LED2);
		else gd_eval_led_off(LED2);
}





