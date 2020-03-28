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
		    
	newFall = time;//下降沿捕获的时间
	if(newFall > oldFall)
	{
		temp = newFall - oldFall;	
	}
	else
	{
	 	temp = 0xffff + newFall - oldFall;
	}
	oldFall = newFall;
	if((temp>10) && (temp<13)) 	// "0"信号
	{ 
	    temp=0; 
	} 
	else if((temp>21) && (temp<24)) //"1"信号 
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
    if(bitcnt<16) //开始接收前16位 
	{ 
	     data0=data0|temp; 
	     data0=data0<<1; 
	} 
	else if(bitcnt==16) 
	{ 
	      data0=data0|temp; 
	} 
	else if(bitcnt<32) //开始接收后16位 
	{ 
	      data1=data1|temp; 
	      data1=data1<<1; 
	} 
	else if(bitcnt==32) //接收完最后一位 
	{ 
	      data1=data1|temp;
		  bitcnt=0;     //计数标志位清0 
	      remote_f=1;   //接收完一帧，标志位置1 
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
       a=((uint8_t)((data0&0xff00)>>8));		//机器码 
       b=((uint8_t)(data0&0x00ff));			//机器反码 
       c=((uint8_t)((data1&0xff00)>>8));		//用户码 
       d=((uint8_t)(data1&0x00ff));			//用户反码 

	   if(((a+b)==255)&&((c+d)==255))	//编码验证
	     return c;
   }
   return 0;
}
