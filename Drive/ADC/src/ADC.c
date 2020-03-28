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
void ADC_GPIOConfig(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init( GPIOC, &GPIO_InitStructure);
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
void ADC_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;
    
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	   /* 独立模式 */
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;			   /* 连续多通道模式 */
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	   /* 连续转换 */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  /* 转换不受外界决定 */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		       /* 右对齐 */
  ADC_InitStructure.ADC_NbrOfChannel = 1;					   /* 扫描通道数 */
  ADC_Init(ADC1, &ADC_InitStructure);

 /* ADC1 regular channel8 configuration */ 
  ADC_RegularChannelConfig( ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);  /* 通道X,采用时间为55.5周期,1代表规则通道第1个 */	
  ADC_Cmd(ADC1, ENABLE);                 /* Enable ADC1 */                      
  ADC_SoftwareStartConvCmd(ADC1,ENABLE);    /* 使能转换开始 */
}
