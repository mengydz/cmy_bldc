/**
  ******************************************************************************
  * @file USART/Interrupt/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "includes.h"
/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*******************CoOS变量**************************/



/*****************************************************/
/******************一般变量***************************/ 
uint32_t Speed_count;
extern uint8_t stalling_count;		   //堵转计数器
extern uint8_t USART_Flag;
/*****************************************************/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
/*
void PendSV_Handler(void)
{
}
*/
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
/*
void SysTick_Handler(void)
{
}
*/


/******************************************************************************/
/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
/******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

}
/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void CAN1_RX1_IRQHandler(void)
{	
} 
/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus( USART1, USART_IT_RXNE) !=RESET)
	{
	    USART_ClearITPendingBit( USART1, USART_IT_RXNE);
	}
}

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
}


/**
  * @brief  This function handles DMA1_Channel1 global interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC1)!=RESET)
  {	 
	 DMA_ClearITPendingBit(DMA1_IT_TC1);
  }
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI0_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
	  EXTI_ClearFlag(EXTI_Line0);

   }		
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI1_IRQHandler(void)
{ 
   if(EXTI_GetITStatus(EXTI_Line1) != RESET)
   {
	  EXTI_ClearFlag(EXTI_Line1);
   }	
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI2_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line2))
   {
	  EXTI_ClearFlag(EXTI_Line2);
   }	
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI3_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line3))
   {
	  EXTI_ClearFlag(EXTI_Line3);
   }
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
void TIM1_TRG_COM_IRQHandler(void)
{ 
  TIM1->SR&=0;           //清中断标志
  
  huanxiang();		     //调用换向函数
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
uint16_t Speed_data[10] ={0};//存放10次捕获到的定时器值　对速度滤波用
void TIM3_IRQHandler(void)
{
  static uint8_t time_over  = 0; 	//定时器溢出计数
  static uint8_t filt_count = 0;	//
  static int Set_PwmValue = 800;
  if(TIM3->SR&0x0010)       		//产生比较/捕获事件４中断计数器溢出  
  {
	TIM3->SR&=0xffef;	    		//清中断标志
	if(time_over>3)
	{
	   /*溢出清零　堵转计数*/
	   time_over=0;	   		  
	   stalling_count++;       		  
	}
	time_over++;
  } 
  if(TIM3->SR&0x0040)      		//TIF触发中断标记   
  {
    TIM3->SR&=0xffbf;        	//清中断标志
	TIM3->CCR2=TIM3->CCR1>>1;	//计算换向点
	Speed_data[filt_count]= TIM3->CCR1+(65535*time_over);
	filt_count ++;
	if(filt_count>9)
	{
	   for(filt_count=0;filt_count<10;filt_count++)
	   {
	 		Speed_count += Speed_data[filt_count];
	   }
	   Speed_count /= 10;
	   Set_PwmValue = Speed_PIDAdjust(Speed_count);
	   TIM1->CCR1=Set_PwmValue;	   //输出到TIM1的PWM寄存器
  	   TIM1->CCR2=Set_PwmValue;
  	   TIM1->CCR3=Set_PwmValue; 
	   filt_count = 0;
	   USART_Flag = 1;
	}
	time_over = 0;			  	//溢出计数清零
	stalling_count = 0;	
  }     		
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
