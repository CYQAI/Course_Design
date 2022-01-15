#ifndef __OLED_DISPLAY_H
#define __OLED_DISPLAY_H

/*外设驱动*/
#include "oled.h"
#include "dht11.h"

extern void (*display_page[])(void);

void display_page_1(void);

void display_page_2(void);

void display_page_3(void);


#endif