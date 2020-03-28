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
 
  /* CAN register init ��CAN�ļĴ���ȫ������Ϊȱʡֵ */
  CAN_DeInit(CAN1);
  /* ��CAN_InitStructure�е�ÿ��������ȱʡֵ���� */
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE; /* ʱ�䴥��ģʽͨ�Ž�ֹ */
  CAN_InitStructure.CAN_ABOM=DISABLE; /* �������Bus_off(�Զ�����)״̬ */
  CAN_InitStructure.CAN_AWUM=DISABLE; /* ʧ���Զ�����ģʽ */
  CAN_InitStructure.CAN_NART=DISABLE; /* ʧ�ܷ��Զ��ش���ģʽ */
  CAN_InitStructure.CAN_RFLM=DISABLE; /* ʧ�ܽ���FIFO����ģʽ */
  CAN_InitStructure.CAN_TXFP=DISABLE; /* ʧ�ܷ���FIFO���ȵȼ� */
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//CAN_Mode_Silent_LoopBack;  //CAN_Mode_Normal; /* CANӲ������������ģʽ//CAN_Mode_Silent_LoopBack;// */
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      /* ����ͬ����Ծ���1��ʱ�䵥λ */
  CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;     /* ����ʱ���1Ϊ13ʱ�䵥λ */
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      /* ����ʱ���2Ϊ2ʱ�䵥λ */
  CAN_InitStructure.CAN_Prescaler=9;	      /* ���õ�λʱ�䳤�� */
  /* CAN������500k/s */
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=0;  /* ָ����ʼ��ָ���Ĺ����� */
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;/* ָ��������Ϊ��ʶ������λģʽ */
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;/* һ��32λ�Ĺ����� */
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;/* ����32λ�������ĸ�16λ */
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000; /* ����32λ�������ĵ�16λ */ 
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;/* ���ù��������α�ʶ�� */
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;

//  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0220;
//  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;

  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;  /* ������0ָ��FIFO0 */
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; /* ʹ�ܹ����� */
  CAN_FilterInit(&CAN_FilterInitStructure);

  CAN_ITConfig( CAN1, CAN_IT_FMP0, ENABLE);
}
