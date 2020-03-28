#include "includes.h"
/********************CoOS变量**********************/
#define TASK_STK_SIZE 	128

#define TASK0_PRIO	2
#define TASK1_PRIO  3

OS_STK STK_TASK0[TASK_STK_SIZE];
OS_STK STK_TASK1[TASK_STK_SIZE];


void TASK0(void *param);
void TASK1(void *param);

/*************************************************/

/*********************一般变量********************/
extern uint32_t Speed_count;
uint8_t USART_Flag = 0;

/*************************************************/
int main(void)
{
	/* 片内外设初始化 */	
	Periph_Init();
	
	/* 操作系统初始化 */
    CoInitOS();

	CoCreateTask( TASK0, (void*)0, TASK0_PRIO, &STK_TASK0[TASK_STK_SIZE - 1], TASK_STK_SIZE);
	CoCreateTask( TASK1, (void*)0, TASK1_PRIO, &STK_TASK1[TASK_STK_SIZE - 1], TASK_STK_SIZE);
	CoStartOS();
    while(1);
}

void TASK0(void *param)
{
  uint16_t data;
  KEY_Init();
  Speed_PIDInit();			
  for(;;)
  { 
    if(KEY_Read(KEY1))
	{
		CoTickDelay(5);
		if(KEY_Read(KEY1))
		{
		   BLDC_Start();	
		}
	}
	if(KEY_Read(KEY2))
	{
		CoTickDelay(5);
		if(KEY_Read(KEY2))
		{
		   BLDC_Stop();
		}
	} 
	if(USART_Flag)
	{
    	data = 1000000/(6*Speed_count);
		USART_SendData( USART2, data);
		USART_Flag = 0;
	}
	CoTickDelay(5);
  }			
}
void TASK1(void *param)
{	
  for(;;)
  {
	   LED_On();
	   CoTickDelay(200);
	   LED_Off();
	   CoTickDelay(200);
  }
}
