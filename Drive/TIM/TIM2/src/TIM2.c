#include "includes.h"


/**********************************************************************
* Function Name  : TIM2_RCCConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_RCCConfig(void)
{
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2 , ENABLE);	
}
/**********************************************************************
* Function Name  : TIM2_NVICConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_NVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStruct;
  	
  NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}
/**********************************************************************
* Function Name  : TIM2_CapGPIOConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_CapGPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin   	= 	GPIO_Pin_0 |GPIO_Pin_3;
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
void  TIM2_Config(void)
{
   TIM_TimeBaseInitTypeDef TIM_InitStruct;
 
   TIM_DeInit( TIM2);
   TIM_InternalClockConfig( TIM2);

   TIM_InitStruct.TIM_Prescaler 	=  7200;
   TIM_InitStruct.TIM_CounterMode 	=  TIM_CounterMode_Up;
   TIM_InitStruct.TIM_Period		=  36000 - 1;
   TIM_InitStruct.TIM_ClockDivision =  TIM_CKD_DIV1;

   TIM_TimeBaseInit (TIM2, &TIM_InitStruct);

   TIM_ClearFlag( TIM2, TIM_FLAG_Update);
   
   TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE); 
   
   TIM_Cmd( TIM2,ENABLE);
}
/**********************************************************************
* Function Name  : TIM2_CapConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_CapConfig(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;//��ʱ����ʼ���ṹ
  TIM_ICInitTypeDef TIM_ICInitStruct;         //ͨ�������ʼ���ṹ

//TIM2�����ʼ��
  TIM_TimeBaseStruct.TIM_Period 			= 50000 - 1;     
  TIM_TimeBaseStruct.TIM_Prescaler 			= 7200;       //ʱ�ӷ�Ƶ
  TIM_TimeBaseStruct.TIM_ClockDivision 		= TIM_CKD_DIV1;   //ʱ�ӷָ�
  TIM_TimeBaseStruct.TIM_CounterMode 		= TIM_CounterMode_Up;//ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);//������ʼ��

//TIM2ͨ��1�Ĳ�׽��ʼ��  
  TIM_ICInitStruct.TIM_Channel 			= TIM_Channel_1;//ͨ��ѡ��
  TIM_ICInitStruct.TIM_ICPolarity 		= TIM_ICPolarity_Falling;//������
  TIM_ICInitStruct.TIM_ICSelection 		= TIM_ICSelection_DirectTI;//�ܽ���Ĵ�����Ӧ��ϵ
  TIM_ICInitStruct.TIM_ICPrescaler 		= TIM_ICPSC_DIV1;//��Ƶ��
  TIM_ICInitStruct.TIM_ICFilter 		= 0x4;//�˲����ã������������������϶������ȶ�0x0��0xF
  TIM_ICInit(TIM2, &TIM_ICInitStruct);        //��ʼ��
//TIM2ͨ��2�Ĳ�׽��ʼ��
  TIM_ICInitStruct.TIM_Channel 		= TIM_Channel_4;//ͨ��ѡ��
  TIM_ICInit(TIM2, &TIM_ICInitStruct);        		//��ʼ��

  
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);   	//ѡ��ʱ�Ӵ���Դ
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);	//������ʽ
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable); //������ʱ���ı�������

  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);        //���ж�
  TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);        //���ж�
  
  TIM_Cmd(TIM2, ENABLE);                         //����TIM2
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_Cap1Start(void)
{
	 TIM_CCxCmd( TIM2, TIM_Channel_1, TIM_CCx_Enable);	 
}
/**********************************************************************
* Function Name  : TIM2_Cap1Stop
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_Cap1Stop(void)
{
	TIM_CCxCmd( TIM2, TIM_Channel_1, TIM_CCx_Disable);
} 
/**********************************************************************
* Function Name  : TIM2_Cap4Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_Cap4Start(void)
{
	 TIM_CCxCmd( TIM2, TIM_Channel_4, TIM_CCx_Enable);	 
}
/**********************************************************************
* Function Name  : TIM2_Cap4Stop
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void TIM2_Cap4Stop(void)
{
	TIM_CCxCmd( TIM2, TIM_Channel_4, TIM_CCx_Disable);
}
