/***************************************************
* Author	:	lijinzhi
* Data		:	2011.8.15
* Descirbe  :	USART1
***************************************************/
#include "includes.h"
/**
  *@Function		
  *@Description			
  *@Calls			
  *@Call By		
  *@Param	xxx
  *		@arg
  *		@arg
  *@Param	xxx
  *		@arg
  *		@arg
  *@Reture			
  *@Others			
  **/
void USART1_GPIOConfig(void)
{
  GPIO_InitTypeDef	GPIO_InitStruct;
  /* ���� USART1 Tx (PA9) */
  GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;	 			/* �����������ģʽ */
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;				/* ������Ƶ��Ϊ50MHz */
  GPIO_Init(GPIOA, &GPIO_InitStruct);
    
  /* ���� USART1 Rx (PA10)  */
  GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;		/* ��������ģʽ */
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void USART1_NVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStruct;
 	
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}
/**
  *@Function		
  *@Description			
  *@Calls			
  *@Call By		
  *@Param	xxx
  *		@arg
  *		@arg
  *@Param	xxx
  *		@arg
  *		@arg
  *@Reture			
  *@Others			
  **/
void USART1_Config(void)
{
	USART_InitTypeDef USART_InitStruct;
	/* USART and USART2 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled */
 	USART_InitStruct.USART_BaudRate            = 9600;	  					
	USART_InitStruct.USART_StopBits            = USART_StopBits_1;	 
	USART_InitStruct.USART_WordLength          = USART_WordLength_8b; 
	USART_InitStruct.USART_Parity              = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

	/* ���ô���1 */
	USART_Init(USART1, &USART_InitStruct);
	/* ����1�����ж�ʹ�� USART_IT_RXNE : ���ղ����ж� */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* ʹ�ܴ���1 */
	USART_Cmd(USART1, ENABLE);
}
/**
  *@Function		
  *@Description			
  *@Calls			
  *@Call By		
  *@Param	xxx
  *		@arg
  *		@arg
  *@Param	xxx
  *		@arg
  *		@arg
  *@Reture			
  *@Others			
  **/
void USART1_SendString(char* data)
{
   unsigned char i = 0;
   for (i=0; data[i] != '\0'; i++)
   {
	  USART_SendData( USART1, data[i]);
	  while( USART_GetFlagStatus(USART1 , USART_FLAG_TXE) == RESET );
		/* ��������ֱ�� USART_FLAG_TXE ���Ϳ�Ϊ��,�Ϳ��Խ����´η��� */
   }
}
