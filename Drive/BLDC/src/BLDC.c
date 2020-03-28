#include "includes.h"

void Delay_us(uint8_t t);
/**********��������**********/
#define IDLE    0
#define	START	1
#define	RUN	    2
#define	STOP    3
#define FAULT   4
#define HIGH	1480
#define LOW     3
/*********ȫ�ֱ���***********/
u8 state;				   //��״̬
FlagStatus zheng_fan = RESET;//��ʼ����Ϊ��ת
uint8_t stalling_count = 0;		   //��ת������

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
 	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;  //TIM1���
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
			 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//TIM1���
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;              //TIM3�Ļ�������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                         //TIM3�Ļ�������
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
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;			   //�����ṹ���������
   TIM_OCInitTypeDef  TIM_OCInitStructure;                     //����ṹ���������
   TIM_BDTRInitTypeDef  TIM_BDTRInitStructure;				   //����ɲ���ṹ���������

   TIM_DeInit(TIM1);

   TIM_TimeBaseStructure.TIM_Prescaler = 2;					   //TIM������ʼ��
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned2;//����������ģʽ
   TIM_TimeBaseStructure.TIM_Period = 1499;					   //PWM 16K
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

   TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 		   //TIM���ͨ����ʼ��
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

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 		   //TIM���ͨ��4��ʼ������������ADע�����
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;                   
   TIM_OCInitStructure.TIM_Pulse =1495; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;           
  
   TIM_OC4Init(TIM1,&TIM_OCInitStructure); 
 
   TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;	//����ɲ����ʼ��
   TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
   TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
   TIM_BDTRInitStructure.TIM_DeadTime = 100;
   TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;	 //��򿪣������������״̬���ң�������
   TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
   TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;

   TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);

   TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);  //ʹ�ܲ���ȽϼĴ���Ԥװ�أ�ͨ��1��

   TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);	 //ʹ�ܲ���ȽϼĴ���Ԥװ�أ�ͨ��2��

   TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);	 //ʹ�ܲ���ȽϼĴ���Ԥװ�أ�ͨ��3��
   
   TIM_SelectInputTrigger(TIM1, TIM_TS_ITR2);        //���봥��Դѡ��TIM3   
  
   //TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger);//��ģʽѡ�� ����	  

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
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;			   //�����ṹ���������
   TIM_ICInitTypeDef TIM_ICInitStructure;                      //����ṹ�����
   TIM_OCInitTypeDef  TIM_OCInitStructure;                     //����ṹ���������
      
   TIM_DeInit(TIM3);

   TIM_TimeBaseStructure.TIM_Prescaler = 71;				   //TIM������ʼ��
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseStructure.TIM_Period =65535;
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

   TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);     
      
   TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;            //ѡ��ͨ��1
   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //���������ز���  
   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_TRC;  //����ͨ��Ϊ���룬��ӳ�䵽����
   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //���벶��Ԥ��Ƶֵ
   TIM_ICInitStructure.TIM_ICFilter = 10;                      //�����˲�����������

   TIM_ICInit(TIM3, &TIM_ICInitStructure);                     //����ͨ������

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 		    //TIM���ͨ����ʼ��
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;             
   TIM_OCInitStructure.TIM_Pulse =1023; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      
  
   TIM_OC2Init(TIM3,&TIM_OCInitStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; 		    //TIM���ͨ����ʼ��
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;             
   TIM_OCInitStructure.TIM_Pulse =65535; 
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      
  
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);

   TIM_SelectHallSensor(TIM3,ENABLE);                          //ʹ��TIMx�Ļ����������ӿ�
   
   TIM_SelectInputTrigger(TIM3, TIM_TS_TI1F_ED);               //���봥��Դѡ��   
  
   TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);             //��ģʽѡ��

   TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);//����ģʽѡ��        
   
   TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_OC2Ref);      //ѡ���������ģʽ(TRGO��)

   TIM_ITConfig(TIM3, TIM_IT_Trigger|TIM_IT_CC4, ENABLE);      //����ʱ���ж� 
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

  irq_zhuanzi=(u8)((GPIOA->IDR&0x000000c0)>>6);	//��ת��λ��
  irq_zhuanzi|=(u8)((GPIOB->IDR&0x00000001)<<2);
  if(zheng_fan==RESET)
  {									 //��ת
    switch(irq_zhuanzi)				 //����ת��λ�ã�����CCER�����λ��ת����ƫ����
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
  {									 //��ת
	switch(irq_zhuanzi)				 //����ת��λ�ã�����CCER�����λ��ת����ƫ����
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
/**************����******************/
void BLDC_Start(void)
{
   TIM1->SMCR|=0x0006;        //��TIM1�����봥��	
   TIM1->DIER=0x0040;         //��TIM1�Ĵ����ж�
   huanxiang();			      //���û�����������			  					 
   TIM3->CR1|=0x0001;		  //��TIM3
   TIM3->DIER|=0x0050;		  //��TIM3�ж�  
}
void BLDC_Stop(void)
{
   TIM1->SMCR&=0xfff8;		  //�ر�TIM1�����봥��
   TIM1->CCER=0;              //�ر�TIM1����·���
   Delay_us(40);			      //��ʱ����������
   TIM1->CCER=0x0ccc;         //����·�¹ܣ������ܺ��ƶ�
   while(stalling_count<1);    //�ȴ����ֹͣ��TIM3�������10�Σ�����Ϊ�����ͣת��   
   TIM1->CCER=0;              //�ر�TIM1����·�������ɲ��		  
   TIM3->CR1&=0xfffe;         //�ر�TIM3						  
   TIM3->CNT=0;               //��TIM3�ļ�����				   
   TIM3->DIER&=0xffaf;		  //��TIM3�ж�
}
void Delay_us(uint8_t t)
{
   while(t--)
   {
   }
}
/**************ֹͣ******************/
/*void stop(void)
{
   TIM1->SMCR&=0xfff8;		  //�ر�TIM1�����봥��
   TIM1->CCER=0;              //�ر�TIM1����·���
   Delay(20);			      //��ʱ����������
   TIM1->CCER=0x0ccc;         //����·�¹ܣ������ܺ��ƶ�
   while(duzhuan_value<1);    //�ȴ����ֹͣ��TIM3�������10�Σ�����Ϊ�����ͣת��   
   TIM1->CCER=0;              //�ر�TIM1����·�������ɲ��		  
   TIM3->CR1&=0xfffe;         //�ر�TIM3						  
   TIM3->CNT=0;               //��TIM3�ļ�����				   
   TIM3->DIER&=0xffaf;		  //��TIM3�ж�
   data_reset();     	      //��λ���в���
}*/
