#include "includes.h"

void Delay_us(uint8_t t);
/**********常量定义**********/
#define IDLE    0
#define	START	1
#define	RUN	    2
#define	STOP    3
#define FAULT   4
#define HIGH	1480
#define LOW     3
/*********全局变量***********/
u8 state;				   //主状态
FlagStatus zheng_fan = RESET;//初始化后为正转
uint8_t stalling_count = 0;		   //堵转计数器

/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void BLDC_GPIOConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
 	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;  //TIM1输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
			 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//TIM1输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;              //TIM3的霍尔输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                         //TIM3的霍尔输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);   
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void BLDC_TIM1Config(void)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;			   //基本结构体变量定义
   TIM_OCInitTypeDef  TIM_OCInitStructure;                     //输出结构体变量定义
   TIM_BDTRInitTypeDef  TIM_BDTRInitStructure;				   //死区刹车结构体变量定义

   TIM_DeInit(TIM1);

   TIM_TimeBaseStructure.TIM_Prescaler = 2;					   //TIM基本初始化
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned2;//中央对齐计数模式
   TIM_TimeBaseStructure.TIM_Period = 1499;					   //PWM 16K
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

   TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 		   //TIM输出通道初始化
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; 
   TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                  
   TIM_OCInitStructure.TIM_Pulse =1200; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
   TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;         
   TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
   TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;          
  
   TIM_OC1Init(TIM1,&TIM_OCInitStructure); 

   TIM_OCInitStructure.TIM_Pulse =1200;
   TIM_OC2Init(TIM1,&TIM_OCInitStructure);

   TIM_OCInitStructure.TIM_Pulse =1200;
   TIM_OC3Init(TIM1,&TIM_OCInitStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 		   //TIM输出通道4初始化，用来触发AD注入采样
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;                   
   TIM_OCInitStructure.TIM_Pulse =1495; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;           
  
   TIM_OC4Init(TIM1,&TIM_OCInitStructure); 
 
   TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;	//死区刹车初始化
   TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
   TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
   TIM_BDTRInitStructure.TIM_DeadTime = 100;
   TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;	 //如打开，开机无输出且状态紊乱？？？？
   TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
   TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;

   TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);

   TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);  //使能捕获比较寄存器预装载（通道1）

   TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);	 //使能捕获比较寄存器预装载（通道2）

   TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);	 //使能捕获比较寄存器预装载（通道3）
   
   TIM_SelectInputTrigger(TIM1, TIM_TS_ITR2);        //输入触发源选择TIM3   
  
   //TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger);//从模式选择 触发	  

   TIM_CtrlPWMOutputs(TIM1,ENABLE);

   TIM_Cmd(TIM1,ENABLE);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void BLDC_TIM3Config(void)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;			   //基本结构体变量定义
   TIM_ICInitTypeDef TIM_ICInitStructure;                      //定义结构体变量
   TIM_OCInitTypeDef  TIM_OCInitStructure;                     //输出结构体变量定义
      
   TIM_DeInit(TIM3);

   TIM_TimeBaseStructure.TIM_Prescaler = 71;				   //TIM基本初始化
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseStructure.TIM_Period =65535;
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);     
      
   TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;            //选择通道1
   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //输入上升沿捕获  
   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_TRC;  //配置通道为输入，并映射到哪里
   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //输入捕获预分频值
   TIM_ICInitStructure.TIM_ICFilter = 10;                      //输入滤波器带宽设置

   TIM_ICInit(TIM3, &TIM_ICInitStructure);                     //输入通道配置

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 		    //TIM输出通道初始化
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;             
   TIM_OCInitStructure.TIM_Pulse =1023; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      
  
   TIM_OC2Init(TIM3,&TIM_OCInitStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; 		    //TIM输出通道初始化
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;             
   TIM_OCInitStructure.TIM_Pulse =65535; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      
  
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);

   TIM_SelectHallSensor(TIM3,ENABLE);                          //使能TIMx的霍尔传感器接口
   
   TIM_SelectInputTrigger(TIM3, TIM_TS_TI1F_ED);               //输入触发源选择   
  
   TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);             //从模式选择

   TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);//主从模式选择        
   
   TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_OC2Ref);      //选择输出触发模式(TRGO端)

   TIM_ITConfig(TIM3, TIM_IT_Trigger|TIM_IT_CC4, ENABLE);      //开定时器中断 
   //TIM_Cmd(TIM3,ENABLE);
}
/**********************************************************************
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
**********************************************************************/
void huanxiang(void)
{
  u8 irq_zhuanzi; 

  irq_zhuanzi=(u8)((GPIOA->IDR&0x000000c0)>>6);	//读转子位置
  irq_zhuanzi|=(u8)((GPIOB->IDR&0x00000001)<<2);
  if(zheng_fan==RESET)
  {									 //正转
    switch(irq_zhuanzi)				 //根据转子位置，决定CCER输出相位和转子字偏移量
    {
/*	  case 0x01:{	                      												
			  	  TIM1->CCER=0x3081;    //1,4
			    };break;
	  case 0x03:{
				  TIM1->CCER=0x3180;	//4,5	          	   
	            };break;							
  	  case 0x02:{
				  TIM1->CCER=0x3108;	//2,5
			    };break;
	  case 0x06:{
				  TIM1->CCER=0x3018;	//2,3	          		
	            };break;
	  case 0x04:{
				  TIM1->CCER=0x3810;	//3,6	          		
	            };break;
	  case 0x05:{
	             			
				  TIM1->CCER=0x3801;    //1,6	          		
	            };break;
	  default:break;  */
	  case 0x05:{	                      												
			  	  TIM1->CCER=0x3081;    //1,4
			    };break;
	  case 0x04:{
				  TIM1->CCER=0x3180;	//4,5	          	   
	            };break;							
  	  case 0x06:{
				  TIM1->CCER=0x3108;	//2,5
			    };break;
	  case 0x02:{
				  TIM1->CCER=0x3018;	//2,3	          		
	            };break;
	  case 0x03:{
				  TIM1->CCER=0x3810;	//3,6	          		
	            };break;
	  case 0x01:{
	             			
				  TIM1->CCER=0x3801;    //1,6	          		
	            };break;
	  default:break;
    }  
  }
  else
  {									 //反转
	switch(irq_zhuanzi)				 //根据转子位置，决定CCER输出相位和转子字偏移量
    {
	  case 0x01:{										
			  	  TIM1->CCER=0x3810;
			    };break;
	  case 0x05:{
				  TIM1->CCER=0x3018;		          	   
	            };break;							
  	  case 0x04:{
				  TIM1->CCER=0x3108;
			    };break;
	  case 0x06:{
				  TIM1->CCER=0x3180;		          		
	            };break;
	  case 0x02:{
				  TIM1->CCER=0x3081;		          		
	            };break;
	  case 0x03:{ 	              			
				  TIM1->CCER=0x3801;		          		
	            };break;
	  default:break;
    }
  }
}
/**************启动******************/
void BLDC_Start(void)
{
   TIM1->SMCR|=0x0006;        //开TIM1的输入触发	
   TIM1->DIER=0x0040;         //开TIM1的触发中断
   huanxiang();			      //调用换向函数，启动			  					 
   TIM3->CR1|=0x0001;		  //开TIM3
   TIM3->DIER|=0x0050;		  //开TIM3中断  
}
void BLDC_Stop(void)
{
   TIM1->SMCR&=0xfff8;		  //关闭TIM1的输入触发
   TIM1->CCER=0;              //关闭TIM1的六路输出
   Delay_us(40);			      //延时（加死区）
   TIM1->CCER=0x0ccc;         //打开三路下管，进行能耗制动
   while(stalling_count<1);    //等待电机停止（TIM3连续溢出10次，即认为电机已停转）   
   TIM1->CCER=0;              //关闭TIM1的六路输出，关刹车		  
   TIM3->CR1&=0xfffe;         //关闭TIM3						  
   TIM3->CNT=0;               //清TIM3的计数器				   
   TIM3->DIER&=0xffaf;		  //关TIM3中断
}
void Delay_us(uint8_t t)
{
   while(t--)
   {
   }
}
/**************停止******************/
/*void stop(void)
{
   TIM1->SMCR&=0xfff8;		  //关闭TIM1的输入触发
   TIM1->CCER=0;              //关闭TIM1的六路输出
   Delay(20);			      //延时（加死区）
   TIM1->CCER=0x0ccc;         //打开三路下管，进行能耗制动
   while(duzhuan_value<1);    //等待电机停止（TIM3连续溢出10次，即认为电机已停转）   
   TIM1->CCER=0;              //关闭TIM1的六路输出，关刹车		  
   TIM3->CR1&=0xfffe;         //关闭TIM3						  
   TIM3->CNT=0;               //清TIM3的计数器				   
   TIM3->DIER&=0xffaf;		  //关TIM3中断
   data_reset();     	      //复位运行参数
}*/
