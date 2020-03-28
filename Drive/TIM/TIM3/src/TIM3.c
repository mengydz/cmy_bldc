#include "includes.h"


/**********************************************************************
* Function Name  : TIM2_RCCConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_RCCConfig(void)
{
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3 , ENABLE);	
}
/**********************************************************************
* Function Name  : TIM2_NVICConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_NVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStruct;
  	
  NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}
/**********************************************************************
* Function Name  : TIM2_CapGPIOConfig
* Description    : (TIM3_CH1 PA6),(TIM3_CH2 PA7),(TIM3_CH3 PB0),(TIM3_CH4 PB1)
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_CapGPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin   	= 	GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed	=   GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode	=   GPIO_Mode_IN_FLOATING;
	GPIO_Init(	GPIOA, &GPIO_InitStruct);
}
/**********************************************************************
* Function Name  : TIM2_RCCConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void  TIM3_Config(void)
{
   TIM_TimeBaseInitTypeDef TIM_InitStruct;
 
   TIM_DeInit( TIM3);
   TIM_InternalClockConfig( TIM3);

   TIM_InitStruct.TIM_Prescaler 	=  72;
   TIM_InitStruct.TIM_CounterMode 	=  TIM_CounterMode_Up;
   TIM_InitStruct.TIM_Period		=  65535;
   TIM_InitStruct.TIM_ClockDivision =  TIM_CKD_DIV1;

   TIM_TimeBaseInit (TIM3, &TIM_InitStruct);

   TIM_ClearFlag( TIM3, TIM_FLAG_Update);
   
   TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE); 
   
   TIM_Cmd( TIM3,ENABLE);
}
/**********************************************************************
* Function Name  : TIM2_CapConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_CapConfig(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct; //��ʱ����ʼ���ṹ
  TIM_ICInitTypeDef TIM_ICInitStruct;          //ͨ�������ʼ���ṹ

//TIM3�����ʼ��
  TIM_TimeBaseStruct.TIM_Period 			= 65535;     
  TIM_TimeBaseStruct.TIM_Prescaler 			= 72 - 1;       		  //ʱ�ӷ�Ƶ
  TIM_TimeBaseStruct.TIM_ClockDivision 		= TIM_CKD_DIV1;       //ʱ�ӷָ�
  TIM_TimeBaseStruct.TIM_CounterMode 		= TIM_CounterMode_Up; //ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);					  //������ʼ��

//TIM2ͨ��1�Ĳ�׽��ʼ��  
  TIM_ICInitStruct.TIM_Channel 			= TIM_Channel_1;//ͨ��ѡ��
  TIM_ICInitStruct.TIM_ICPolarity 		= TIM_ICPolarity_Falling;//�½���
  TIM_ICInitStruct.TIM_ICSelection 		= TIM_ICSelection_DirectTI;//�ܽ���Ĵ�����Ӧ��ϵ
  TIM_ICInitStruct.TIM_ICPrescaler 		= TIM_ICPSC_DIV1;//��Ƶ��
  TIM_ICInitStruct.TIM_ICFilter 		= 0x4;//�˲����ã������������������϶������ȶ�0x0��0xF
  TIM_ICInit(TIM3, &TIM_ICInitStruct);        //��ʼ��
//TIM3ͨ��4�Ĳ�׽��ʼ��
// TIM_ICInitStruct.TIM_Channel 		= TIM_Channel_4;//ͨ��ѡ��
//  TIM_ICInit(TIM2, &TIM_ICInitStruct);        		//��ʼ��

  
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);   	//ѡ��ʱ�Ӵ���Դ
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);	//������ʽ
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable); //������ʱ���ı�������

  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);        //���ж�
//  TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);      //���ж�
  
  TIM_Cmd(TIM3, ENABLE);                         //����TIM2
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_Cap1Start(void)
{
   TIM_CCxCmd( TIM3, TIM_Channel_1, TIM_CCx_Enable);	 
}
/**********************************************************************
* Function Name  : TIM2_Cap1Stop
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_Cap1Stop(void)
{
   TIM_CCxCmd( TIM3, TIM_Channel_1, TIM_CCx_Disable);
} 
/**********************************************************************
* Function Name  : TIM2_Cap4Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_Cap4Start(void)
{
	TIM_CCxCmd( TIM3, TIM_Channel_4, TIM_CCx_Enable);	 
}
/**********************************************************************
* Function Name  : TIM2_Cap4Stop
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM3_Cap4Stop(void)
{
	TIM_CCxCmd( TIM3, TIM_Channel_4, TIM_CCx_Disable);
}
