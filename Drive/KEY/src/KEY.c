#include "includes.h"
#define KEY_PORT 	 GPIOB
#define KEY1_Pin	 GPIO_Pin_6
#define KEY2_Pin 	 GPIO_Pin_7
/**********************************************************************
* Function Name  : KEY_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin   	= 	KEY1_Pin | KEY2_Pin;
//	GPIO_InitStruct.GPIO_Speed	=   GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode	=   GPIO_Mode_IN_FLOATING;

	GPIO_Init( KEY_PORT, &GPIO_InitStruct);
}
/**********************************************************************
* Function Name  : KEY_Read
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
uint8_t KEY_Read(uint8_t key)
{
	uint8_t data=0;
	switch(key)
	{
		case KEY1: 	data=GPIO_ReadInputDataBit( KEY_PORT, KEY1_Pin);
		break;
		case KEY2:  data=GPIO_ReadInputDataBit( KEY_PORT, KEY2_Pin);
		break;
		default: data=1;
	}
	if(data)
	{
	 	return 0;
	}
	return 1;
}
