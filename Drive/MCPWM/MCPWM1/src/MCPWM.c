/**
  *************************************************************************
  *@FileName
  *@Author
  *@Version
  *@Date
  *@History
  *@Dependence
  *@Description
  *************************************************************************
  *@CopyRight
  *************************************************************************
  *
	*/
#include "includes.h"

/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void MCPWM1_GPIOConfig(void)
{
  	GPIO_InitTypeDef GPIO_InitStruct;
  /* PA8����Ϊ���ܽ�(PWM) */

    GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);


    GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void MCPWM1_Config(void)
{
    TIM_TimeBaseInitTypeDef 	TIM_BaseInitStruct;
    TIM_OCInitTypeDef 			TIM_OCInitStruct;
	TIM_BDTRInitTypeDef   		TIM_BDTRInitStruct;

    TIM_DeInit(TIM1); //����Ϊȱʡֵ 
 	/*TIM1ʱ������*/
 	TIM_BaseInitStruct.TIM_Prescaler 		= 72 - 1;      //Ԥ��Ƶ(ʱ�ӷ�Ƶ)
 	TIM_BaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Up;  //���ϼ���
 	TIM_BaseInitStruct.TIM_Period 			= 200 - 1;       //װ��ֵ
 	TIM_BaseInitStruct.TIM_ClockDivision	= TIM_CKD_DIV1;   //������ʱ�ӷָ�
 	TIM_BaseInitStruct.TIM_RepetitionCounter= 0x00;     //���ڼ�����ֵ

 	TIM_TimeBaseInit(TIM1,&TIM_BaseInitStruct);    		//��ʼ��TIMx��ʱ�������λ
	TIM_ARRPreloadConfig( TIM1, ENABLE); 			    //ʹ��Ԥװ�ؼĴ���

 	/* Channel 1 Configuration in PWM mode ͨ��һ��PWM */
 	TIM_OCInitStruct.TIM_OCMode 			= TIM_OCMode_PWM1;     //PWMģʽ2
 	TIM_OCInitStruct.TIM_OutputState 		= TIM_OutputState_Enable;  //����ͨ����Ч 
 	TIM_OCInitStruct.TIM_OutputNState 		= TIM_OutputNState_Enable; //����ͨ��Ҳ��Ч
 	TIM_OCInitStruct.TIM_Pulse 				= 150;        //ռ��ʱ��
 	TIM_OCInitStruct.TIM_OCPolarity 		= TIM_OCPolarity_High;   //�������
 	TIM_OCInitStruct.TIM_OCNPolarity 		= TIM_OCNPolarity_High;   //�����˵ļ���  
 	TIM_OCInitStruct.TIM_OCIdleState 		= TIM_OCIdleState_Set;  //����״̬�µķǹ���״̬
 	TIM_OCInitStruct.TIM_OCNIdleState 		= TIM_OCNIdleState_Set;  //

	TIM_OC1Init(TIM1,&TIM_OCInitStruct);     //����ʼ������TIMxͨ��1����2.0��ΪTIM_OCInit
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_OCInitStruct.TIM_Pulse 				= 150;        //ռ��ʱ��
	TIM_OC2Init(TIM1,&TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_OCInitStruct.TIM_Pulse 				= 150;
	TIM_OC3Init(TIM1,&TIM_OCInitStruct);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_BDTRInitStruct.TIM_OSSRState 		=	TIM_OSSRState_Enable;
	TIM_BDTRInitStruct.TIM_OSSIState	    =   TIM_OSSIState_Enable;
	TIM_BDTRInitStruct.TIM_LOCKLevel	    = 	TIM_LOCKLevel_OFF;
	TIM_BDTRInitStruct.TIM_DeadTime			=	256 - 1;
	TIM_BDTRInitStruct.TIM_Break			=   TIM_Break_Disable;
	TIM_BDTRInitStruct.TIM_BreakPolarity	=	TIM_BreakPolarity_Low;
	TIM_BDTRInitStruct.TIM_AutomaticOutput	=	TIM_AutomaticOutput_Enable;

	TIM_BDTRConfig( TIM1, &TIM_BDTRInitStruct);

 	/* TIM1 counter enable����ʱ�� */
 	TIM_Cmd(TIM1,ENABLE);
    /* TIM1 Main Output Enable ʹ��TIM1����������*/
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC1Start(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_1, TIM_CCx_Enable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC1Stop(void)
{
    TIM_CCxCmd( TIM1, TIM_Channel_1, TIM_CCx_Disable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC1NStart(void)
{
	TIM_CCxNCmd( TIM1, TIM_Channel_1, TIM_CCx_Enable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC1NStop(void)
{
	TIM_CCxNCmd( TIM1, TIM_Channel_1, TIM_CCx_Disable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC2Start(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_2, TIM_CCx_Enable);	
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC2Stop(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_2, TIM_CCx_Disable);	
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC2NStart(void)
{
	TIM_CCxNCmd( TIM1, TIM_Channel_2, TIM_CCx_Enable);
}
void PWM1_OC2NStop(void)
{
	TIM_CCxNCmd( TIM1, TIM_Channel_2, TIM_CCx_Disable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC3Start(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_3, TIM_CCx_Enable);	
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC3Stop(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_3, TIM_CCx_Disable);	
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC3NStart(void)
{
	TIM_CCxNCmd( TIM1, TIM_Channel_3, TIM_CCx_Enable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC3NStop(void)
{
	TIM_CCxNCmd( TIM1, TIM_Channel_3, TIM_CCx_Disable);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC4Start(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_4, TIM_CCx_Enable);	
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_OC4Stop(void)
{
	TIM_CCxCmd( TIM1, TIM_Channel_4, TIM_CCx_Disable);	
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_SetOC1Pulse(uint16_t pulse)
{
   TIM_SetCompare1(TIM1, pulse);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_SetOC2Pulse(uint16_t pulse)
{
   TIM_SetCompare2(TIM1, pulse);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_SetOC3Pulse(uint16_t pulse)
{
   TIM_SetCompare3(TIM1, pulse);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void PWM1_SetOC4Pulse(uint16_t pulse)
{
   TIM_SetCompare4(TIM1, pulse);
}
