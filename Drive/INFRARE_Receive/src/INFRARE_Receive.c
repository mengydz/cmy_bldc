#include "includes.h"

volatile uint16_t data0  = 0;
volatile uint16_t data1  = 0;
volatile uint8_t  remote_f = 0;
/**********************************************************************
* Function Name  : TIM2_CapConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
/*void INFRARE_GPIOConfig(void)
{
	TIM3_CapGPIOConfig();
} */
/**********************************************************************
* Function Name  : TIM2_CapConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
/*void INFRARE_Config(void)
{
    TIM3_CapConfig();
}  */

/**********************************************************************
* Function Name  : TIM2_CapConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void INFRARE_Receive(uint16_t time)
{
	static uint16_t newFall = 0;
	static uint16_t oldFall = 0;
//	static uint16_t data0 	= 0;
//	static uint16_t data1 	= 0;
	static uint16_t bitcnt  = 0;
		   uint32_t temp  	= 0;
		    
	newFall = time;//�½��ز����ʱ��
	if(newFall > oldFall)
	{
		temp = newFall - oldFall;	
	}
	else
	{
	 	temp = 0xffff + newFall - oldFall;
	}
	oldFall = newFall;
	if((temp>10) && (temp<13)) 	// "0"�ź�
	{ 
	    temp=0; 
	} 
	else if((temp>21) && (temp<24)) //"1"�ź� 
	{ 
	    temp=1; 
	}
	else if((temp>130) && (temp<140))
	{
		 bitcnt = 0;
		 data0  = 0;
		 data1  = 0;
		 return ;
	} 
	else
	{
	 	 bitcnt = 0;
		 data0  = 0;
		 data1  = 0;
		 return ;
	}
		 bitcnt ++;
    if(bitcnt<16) //��ʼ����ǰ16λ 
	{ 
	     data0=data0|temp; 
	     data0=data0<<1; 
	} 
	else if(bitcnt==16) 
	{ 
	      data0=data0|temp; 
	} 
	else if(bitcnt<32) //��ʼ���պ�16λ 
	{ 
	      data1=data1|temp; 
	      data1=data1<<1; 
	} 
	else if(bitcnt==32) //���������һλ 
	{ 
	      data1=data1|temp;
		  bitcnt=0;     //������־λ��0 
	      remote_f=1;   //������һ֡����־λ��1 
	} 
}
/**********************************************************************
* Function Name  : TIM2_CapConfig
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/

uint8_t INFRARE_Process(void)
{
   uint8_t a = 0;
   uint8_t b = 0;
   uint8_t c = 0;
   uint8_t d = 0;
   if(remote_f)
   {
	   remote_f=0;
       a=((uint8_t)((data0&0xff00)>>8));		//������ 
       b=((uint8_t)(data0&0x00ff));			//�������� 
       c=((uint8_t)((data1&0xff00)>>8));		//�û��� 
       d=((uint8_t)(data1&0x00ff));			//�û����� 

	   if(((a+b)==255)&&((c+d)==255))	//������֤
	     return c;
   }
   return 0;
}
