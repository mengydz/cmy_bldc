#include "includes.h"
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void LED_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin   	= 	LED0_Pin;
	GPIO_InitStruct.GPIO_Speed	=   GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode	=   GPIO_Mode_Out_PP;

	GPIO_Init( LED0_PORT, &GPIO_InitStruct);
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void LED_On(void)
{
  	GPIO_ResetBits( LED0_PORT, LED0_Pin);
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void LED_Off(void)
{
	GPIO_SetBits( LED0_PORT, LED0_Pin);
}
