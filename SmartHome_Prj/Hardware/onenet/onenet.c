/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	onenet.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-05-09
	*
	*	�汾�� 		V1.1
	*
	*	˵���� 		��onenetƽ̨�����ݽ����ӿڲ�
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "gd32e23x.h"
#include "gd32e230c_eval.h"
#include "systick.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"

//Ӳ������
#include "dht11.h"


//C��
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
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(void)
{
	
	char buf[256];
	
	memset(buf, 0, sizeof(buf));
	
	OneNet_FillBuf(buf);									//��װ������
	
	ESP8266_SendData((unsigned char *)buf, strlen(buf));	//�ϴ�����
	
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *dataPtr)
{

	if(strstr((char *)dataPtr, "CLOSED"))
	{
		printf( "TCP CLOSED\r\n");
	}
	else
	{
		//������������Ƿ��ͳɹ�
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
