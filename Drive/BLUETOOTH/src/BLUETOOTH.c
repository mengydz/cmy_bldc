/***************************************************
* Author	:	lijinzhi
* Data		:	2011.8.15
* Descirbe  :	BLUETOOTH
***************************************************/
#include "includes.h"

//蓝牙控制口PIO0的宏定义
#define	PIO0_GPIO		GPIOA
#define PIO0_Pin		GPIO_Pin_4
//AT命令宏定义
//#define 
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void BLUETOOTH_GPIOConfig(void)
{
   GPIO_InitTypeDef	GPIO_InitStruct;
   /* 配置 USART1 Tx (PA2) */
   GPIO_InitStruct.GPIO_Pin 	= PIO0_Pin;
   GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;	 			/* 复用推挽输出模式 */
   GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;				/* 输出最大频率为50MHz */
   GPIO_Init( PIO0_GPIO, &GPIO_InitStruct);
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void BLUETTOOTH_SendATOrder(void)
{
	GPIO_SetBits( PIO0_GPIO, PIO0_Pin);
	CoTickDelay(10);
	GPIO_ResetBits( PIO0_GPIO, PIO0_Pin);
	USART2_SendString("AT+IMME=0");
	//发送清除主设备配对信息命令
	USART2_SendString("AT+CLEAR");
	//设置配对密码
	USART2_SendString("AT+PIN=1234");		
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
