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
  /* PA8设置为功能脚(PWM) */

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

    TIM_DeInit(TIM1); //重设为缺省值 
 	/*TIM1时钟配置*/
 	TIM_BaseInitStruct.TIM_Prescaler 		= 72 - 1;      //预分频(时钟分频)
 	TIM_BaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Up;  //向上计数
 	TIM_BaseInitStruct.TIM_Period 			= 200 - 1;       //装载值
 	TIM_BaseInitStruct.TIM_ClockDivision	= TIM_CKD_DIV1;   //设置了时钟分割
 	TIM_BaseInitStruct.TIM_RepetitionCounter= 0x00;     //周期计数器值

 	TIM_TimeBaseInit(TIM1,&TIM_BaseInitStruct);    		//初始化TIMx的时间基数单位
	TIM_ARRPreloadConfig( TIM1, ENABLE); 			    //使能预装载寄存器

 	/* Channel 1 Configuration in PWM mode 通道一的PWM */
 	TIM_OCInitStruct.TIM_OCMode 			= TIM_OCMode_PWM1;     //PWM模式2
 	TIM_OCInitStruct.TIM_OutputState 		= TIM_OutputState_Enable;  //正向通道有效 
 	TIM_OCInitStruct.TIM_OutputNState 		= TIM_OutputNState_Enable; //反向通道也有效
 	TIM_OCInitStruct.TIM_Pulse 				= 150;        //占空时间
 	TIM_OCInitStruct.TIM_OCPolarity 		= TIM_OCPolarity_High;   //输出极性
 	TIM_OCInitStruct.TIM_OCNPolarity 		= TIM_OCNPolarity_High;   //互补端的极性  
 	TIM_OCInitStruct.TIM_OCIdleState 		= TIM_OCIdleState_Set;  //空闲状态下的非工作状态
 	TIM_OCInitStruct.TIM_OCNIdleState 		= TIM_OCNIdleState_Set;  //

	TIM_OC1Init(TIM1,&TIM_OCInitStruct);     //数初始化外设TIMx通道1这里2.0库为TIM_OCInit
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_OCInitStruct.TIM_Pulse 				= 150;        //占空时间
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

 	/* TIM1 counter enable开定时器 */
 	TIM_Cmd(TIM1,ENABLE);
    /* TIM1 Main Output Enable 使能TIM1外设的主输出*/
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
