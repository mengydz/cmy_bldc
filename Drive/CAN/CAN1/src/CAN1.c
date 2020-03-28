/***************************************************
* Author	:	lijinzhi
* Data		:	2011.8.15
* Descirbe  :	STM32_CAN
***************************************************/
#include "includes.h"
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void CAN1_GPIOConfig()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//PA11-CAN_RX
	GPIO_InitStruct.GPIO_Pin	=	GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode	=   GPIO_Mode_IPU;
	GPIO_Init( GPIOA, &GPIO_InitStruct);
	//PA12-CAN_TX
	GPIO_InitStruct.GPIO_Pin	=	GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode	=	GPIO_Mode_AF_PP;
	GPIO_Init( GPIOA, &GPIO_InitStruct);

//  GPIO_PinRemapConfig( GPIO_Remap1_CAN1 , ENABLE);
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void CAN1_NVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStruct;
 	
  NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; /*USB_LP_CAN1_RX0_IRQn , CAN1_RX1_IRQn */
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void CAN1_Config(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 
  /* CAN register init 将CAN的寄存器全部设置为缺省值 */
  CAN_DeInit(CAN1);
  /* 将CAN_InitStructure中的每个参数按缺省值填入 */
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE; /* 时间触发模式通信禁止 */
  CAN_InitStructure.CAN_ABOM=DISABLE; /* 软件设置Bus_off(自动离线)状态 */
  CAN_InitStructure.CAN_AWUM=DISABLE; /* 失能自动唤醒模式 */
  CAN_InitStructure.CAN_NART=DISABLE; /* 失能非自动重传输模式 */
  CAN_InitStructure.CAN_RFLM=DISABLE; /* 失能接受FIFO锁定模式 */
  CAN_InitStructure.CAN_TXFP=DISABLE; /* 失能发送FIFO优先等级 */
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//CAN_Mode_Silent_LoopBack;  //CAN_Mode_Normal; /* CAN硬件工作在正常模式//CAN_Mode_Silent_LoopBack;// */
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      /* 重新同步跳跃宽度1个时间单位 */
  CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;     /* 设置时间段1为13时间单位 */
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      /* 设置时间段2为2时间单位 */
  CAN_InitStructure.CAN_Prescaler=9;	      /* 设置单位时间长度 */
  /* CAN波特率500k/s */
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=0;  /* 指定初始化指定的过滤器 */
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;/* 指定过滤器为标识符屏蔽位模式 */
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;/* 一个32位的过滤器 */
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;/* 设置32位过滤器的高16位 */
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000; /* 设置32位过滤器的低16位 */ 
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;/* 设置过滤器屏蔽标识符 */
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;

//  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0220;
//  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;

  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;  /* 过滤器0指向FIFO0 */
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; /* 使能过滤器 */
  CAN_FilterInit(&CAN_FilterInitStructure);

  CAN_ITConfig( CAN1, CAN_IT_FMP0, ENABLE);
}
