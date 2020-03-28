/***************************************************
* Author	:	lijinzhi
* Data		:	2011.8.15
* Descirbe  :	BLUETOOTH
***************************************************/
#include "includes.h"

//�������ƿ�PIO0�ĺ궨��
#define	PIO0_GPIO		GPIOA
#define PIO0_Pin		GPIO_Pin_4
//AT����궨��
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
   /* ���� USART1 Tx (PA2) */
   GPIO_InitStruct.GPIO_Pin 	= PIO0_Pin;
   GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;	 			/* �����������ģʽ */
   GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;				/* ������Ƶ��Ϊ50MHz */
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
	//����������豸�����Ϣ����
	USART2_SendString("AT+CLEAR");
	//�����������
	USART2_SendString("AT+PIN=1234");		
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
