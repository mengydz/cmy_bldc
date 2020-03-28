#include "includes.h"
void StepMotor_GPIOConfig(void)
{
 	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin   	= 	GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed	=   GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode	=   GPIO_Mode_Out_PP;

	GPIO_Init( GPIOC, &GPIO_InitStruct);
}
void StepMotor_Contr(void)
{
	 static uint8_t cStep = 0;

	 cStep = (cStep + 1) % 8; 

	 switch (cStep) {

     case 0:                                                             /*  A(PC6)     */
		GPIO_SetBits( GPIOC, GPIO_Pin_6);
		GPIO_ResetBits( GPIOC, GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9);
        break;

     case 1:                                                             /*   AB(PC6 | PC7)*/
		GPIO_SetBits( GPIOC, GPIO_Pin_6| GPIO_Pin_7);
		GPIO_ResetBits( GPIOC, GPIO_Pin_8| GPIO_Pin_9);
        break;

     case 2:                                                             /*  B            */
		GPIO_SetBits( GPIOC,  GPIO_Pin_7);
		GPIO_ResetBits( GPIOC, GPIO_Pin_6| GPIO_Pin_8| GPIO_Pin_9);
        break;

     case 3:                                                             /*  BC(PC7 | PC8) */
		GPIO_SetBits( GPIOC,  GPIO_Pin_7| GPIO_Pin_8);
		GPIO_ResetBits( GPIOC, GPIO_Pin_6| GPIO_Pin_9);
        break;

     case 4:                                                             /*  C(PC8)       */
		GPIO_SetBits( GPIOC,  GPIO_Pin_8);
		GPIO_ResetBits( GPIOC, GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_9);
        break;

     case 5:                                                             /* CD(PC8 | PC9)  */
		GPIO_SetBits( GPIOC,  GPIO_Pin_8| GPIO_Pin_9);
		GPIO_ResetBits( GPIOC, GPIO_Pin_6| GPIO_Pin_7);
        break;

     case 6:                                                             /* D(PC9)        */
		GPIO_SetBits( GPIOC, GPIO_Pin_9);
		GPIO_ResetBits( GPIOC, GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8);
        break;

     case 7:                                                             /* DA(PC9 | PC6) */
		GPIO_SetBits( GPIOC,  GPIO_Pin_6|GPIO_Pin_9);
		GPIO_ResetBits( GPIOC, GPIO_Pin_7| GPIO_Pin_8);
        break;

     default:
        break;
    }
}
