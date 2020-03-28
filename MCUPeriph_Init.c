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

void  RCC_Config  (void);
void  GPIO_Config (void);
void  NVIC_Config(void);
void  EXTI_Config (void);
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
void Periph_Init(void)
{
  /*********ʱ��ʹ��*************/
  RCC_Config();

  /********�ж����ȼ�����********/
  NVIC_Config();

  /********�ⲿ�ж�����**********/
//  EXTI_Config();
  /********�ⲿGPIO����**********/
   GPIO_Config();
   BLDC_TIM1Config();
   BLDC_TIM3Config();
   USART2_Config();
//   MCPWM1_Config();
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
void RCC_Config(void)
{
	SystemInit();

	/* ʹ��GPIO(A~C)|ADC1|USART1 ʱ�� */
	RCC_APB2PeriphClockCmd(   RCC_APB2Periph_GPIOA 
							| RCC_APB2Periph_GPIOB
			 	 	 	 	| RCC_APB2Periph_GPIOC 
							| RCC_APB2Periph_AFIO
							| RCC_APB2Periph_TIM1
//							| RCC_APB2Periph_USART1
 							, ENABLE );
//	 RCC_APB1PeriphClockCmd(  RCC_APB1Periph_USART2 
//	 						, ENABLE );
/******************CANʱ��ʹ��**************************/
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
 	RCC_APB1PeriphClockCmd(   RCC_APB1Periph_TIM3
							| RCC_APB1Periph_USART2 
//							| RCC_APB1Periph_TIM4
							, ENABLE);	
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void  GPIO_Config(void)
{		
//    USART1_GPIOConfig();
    USART2_GPIOConfig();
//	CAN1_GPIOConfig();
//  ADC_GPIOConfig();
    LED_GPIOConfig();
//	TIM3_CapGPIOConfig();
//	PS2_GPIOConfig();
//	StepMotor_GPIOConfig();
//	TIM2_CapGPIOConfig();
//	PWM3_GPIOConfig();
//	PWM4_GPIOConfig();
//	MCPWM1_GPIOConfig();
	BLDC_GPIOConfig();
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void NVIC_Config(void)
{
	   NVIC_InitTypeDef NVIC_InitStructure; 					 //��λNVIC�Ĵ���ΪĬ��ֵ	
  /* Configure the NVIC Preemption Priority Bits */  
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

         NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);           //�����ж����ȼ���
	  
       /*����EXTI�жϼ��������ȼ�*/
       NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_IRQn;//��TIM1�����ж�
       NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
       NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
       NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
       NVIC_Init(&NVIC_InitStructure);

	   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;		//��TIM3�ж�
       NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
       NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
       NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
       NVIC_Init(&NVIC_InitStructure);
//  USART1_NVICConfig();
}
/***************************************************
* Descirbe  :
* Input     :
* Output    :
* Attention :
* author 	:
***************************************************/
void EXTI_Config(void)
{
/*******PS2����ʱ��CLK�ⲿ�ж�����*****************/
//	PS2_NVICConfig();	 
}


