#include "includes.h"

static void DYP_ME007Delay10us(void);

volatile uint16_t Distance = 0; 
volatile uint8_t  DYP_ME007Finish = 0;
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void DYP_ME007GPIOConfig(void)
{
 	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin   	= 	GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed	=   GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode	=   GPIO_Mode_Out_PP;

	GPIO_Init( GPIOC, &GPIO_InitStruct);
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void DYP_ME007SendTrig(void)
{
    GPIO_SetBits( GPIOC, GPIO_Pin_10);
	DYP_ME007Delay10us();
	GPIO_ResetBits( GPIOC, GPIO_Pin_10);
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void DYP_ME007Receive(uint16_t time)
{
	char LCD_Buf[5] = {0};
	sprintf( LCD_Buf, "%5d",time);
	PutString( 0, 2, LCD_Buf);
	if(time < 30000)
	{
		Distance = time/58;
		DYP_ME007Finish = 1;
		return;
	}
	else
	{
		Distance = 0;
		return;
	} 
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
uint16_t DYP_ME007Process(void)
{
	if(DYP_ME007Finish)
	{
		DYP_ME007Finish = 0;
	    return (Distance);
	}
	else
	{
		return (0);
	}
}
/**********************************************************************
* Function Name  : TIM2_Cap1Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void DYP_ME007Delay10us(void)
{
	uint8_t	t = 85;
	while( t--);
}
