/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	onenet.c
	*
	*	作者： 		张继瑞
	*
	*	日期： 		2017-05-09
	*
	*	版本： 		V1.1
	*
	*	说明： 		与onenet平台的数据交互接口层
	*
	*	修改记录：	
	************************************************************
	************************************************************
	************************************************************
**/

//单片机头文件
#include "gd32e23x.h"
#include "gd32e230c_eval.h"
#include "systick.h"

//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"

//硬件驱动
#include "dht11.h"


//C库
#include <string.h>
#include <stdio.h>


#define DEVID	"873399928"

#define APIKEY	"wXOQjcqA8ikRtCMs8HINBeIRGtI="


void OneNet_FillBuf(char *buf)
{
	
	char text[24];
	char buf1[128];
	
	memset(text, 0, sizeof(text));
	memset(buf1, 0, sizeof(buf1));
	
	strcpy(buf1, "{");
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Temperature\":%d,", dht11.temperature);
	strcat(buf1, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Humidity\":%d", dht11.humidity);
	strcat(buf1, text);
	
	strcat(buf1, "}");
	
	sprintf(buf, "POST /devices/%s/datapoints?type=3 HTTP/1.1\r\napi-key:%s\r\nHost:api.heclouds.com\r\n"
					"Content-Length:%d\r\n\r\n",
	
					DEVID, APIKEY, strlen(buf1));
					
	strcat(buf, buf1);

}

//==========================================================
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	
	char buf[256];
	
	memset(buf, 0, sizeof(buf));
	
	OneNet_FillBuf(buf);									//封装数据流
	
	ESP8266_SendData((unsigned char *)buf, strlen(buf));	//上传数据
	
}

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *dataPtr)
{

	if(strstr((char *)dataPtr, "CLOSED"))
	{
		printf( "TCP CLOSED\r\n");
	}
	else
	{
		//这里用来检测是否发送成功
		if(strstr((char *)dataPtr, "succ"))
		{
			printf( "Tips:	Send OK\r\n");
		}
		else
		{
			printf( "Tips:	Send Err\r\n");
		}
	}
	
	ESP8266_Clear();

}
