#include "oled_display.h"



void (*display_page[])(void) = {display_page_1, display_page_2, display_page_3};
 
void display_page_1(void)
{
    uint8_t i=0;

    for(;i<4;i++)
        OLED_ShowCHinese(0+16*i,0,i);
    OLED_ShowString(0,2,"temp:"); 
    OLED_ShowNum(8*7,2,dht11.temperature,3,16);
    OLED_ShowString(0,4,"humi:");
    OLED_ShowNum(8*7,4,dht11.humidity,3,16); 
}

void display_page_2(void)
{
		uint8_t i=0;
	
		for(;i<5;i++)
			OLED_ShowCHinese(0+16*i,0,i+4);
		OLED_ShowString(0,2,"temp:"); 
		OLED_ShowNum(8*7,2,dht11_warning.temperature,3,16);
		OLED_ShowCHinese(0+16*6,2,9);
		OLED_ShowString(0,4,"humi:");
		OLED_ShowNum(8*7,4,dht11_warning.humidity,3,16);
}

void display_page_3(void)
{
		uint8_t i=0;
	
		for(;i<5;i++)
			OLED_ShowCHinese(0+16*i,0,i+4);
		OLED_ShowString(0,2,"temp:"); 
		OLED_ShowNum(8*7,2,dht11_warning.temperature,3,16);
		OLED_ShowString(0,4,"humi:");
		OLED_ShowNum(8*7,4,dht11_warning.humidity,3,16);
		OLED_ShowCHinese(0+16*6,4,9);
}



