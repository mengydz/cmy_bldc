#include"includes.h"
/****************************应用层定义*********************************/
uint8_t 	PS2KCODE = 0,/**/ 
					PS2KCODE_END_FLG = 0,/**/ 
					PS2KUP_FLG = 0,/**/ 
					PS2KBI_FLG = 0,/**/
	 			 	PS2KBI_CNT = 0 ;/**/

uint8_t 	PS2KNUM_END_FLG = 0,/**/ 
					PS2KNUM_COUNT = 0,/**/ 
					PS2KNUM[NUM_LEN] = {0},/**/
	 				PS2KNUM_SIGN = 0,/**/  
					PS2KNUM_FLG = 0;/**/

uint8_t 	PS2NUM_TABLE[] = {0x70,0x69,0x72,0x7A,0x6B,0x73,0x74,0x6C,0x75,0x7D};

/*****************************应用层定义*********************************/
void PS2_GPIOConfig(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN_FLOATING;

    GPIO_Init( GPIOC , &GPIO_InitStruct);  
}
void PS2_EXITConfig(void)
{
  EXTI_InitTypeDef  EXTI_InitStructure;

  /* Configure EXTI Line3 to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line 		= 	EXTI_Line0;                   //外部中断通道3
  EXTI_InitStructure.EXTI_Mode 		= 	EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger 	= 	EXTI_Trigger_Falling;    //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd 	= 	ENABLE;        //使能

  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);  //将PC0连接到外部中断通道0
}
void PS2_NVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStruct;
 	
  NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}


/****************************************************************************
 * 函  数：uint8_t PS2KeyCodeGet(void);
 * 功  能：PS2键盘键值译码函数。可以将中断中接收到的键盘按键发送的通码+断码
			中的通码分离出来，并且返回通码，如果通码有两个的，只返回第二个
			码。如'/'的通码为 0xE0 + 0x4A，只返回0x4A，enter的通码为 0xE0 + 0x5A
			只返回0x5A。如果没有按键按下的话则返回0
 * 参  数：无
 * 返回值：uint8_t 相应按键的通码
 * 更  新：无
 * 备  注：
		PS2KUP_FLG：全局变量，按键抬起标志。即接收到0xF0
 		PS2KCODE：全局变量，按键后键盘所发送的编码。在中断中得到该值，键盘
 		发送出来的值，可能为通码也可能为断码。
		PS2KBI_CNT：全局变量，通码为两个8位数时对通码打头字0xE0进行计数用
****************************************************************************/
uint8_t PS2KeyCodeGet(void)
{
	if(!PS2KUP_FLG)
	{
		switch(PS2KCODE)
		{
			case 0xE0:						//通码为两个8位数时
			{
				PS2KBI_CNT += 1;
				if(PS2KBI_CNT == 2)
				{
					PS2KBI_CNT = 0;
				}
				break;
			}
			case 0xF0:						//断码的倒数第2位，用来判断按键抬起
			{
				PS2KUP_FLG = 1;
				break;
			}
			default:							//返回通码
			{
				return (PS2KCODE);
			}
		}
	}
	else
	{
		PS2KUP_FLG = 0;
	}
	return (0);
}
/****************************************************************************
 * 函  数：uint8_t PS2KeyCodeRslt(void);
 * 功  能：得到按键的通码，并对中断中一些标志位做复位操作。
 		   		 PS2KCODE_END_FLG = 0;开中断
 * 参  数：无
 * 返回值：uint8_t ：按键的通码，若没有键按下，则则返回0
 * 更  新：无
 * 备  注：无
****************************************************************************/
uint8_t PS2KeyCodeRslt(void)
{
	uint8_t ps2code = 0;
	if(PS2KCODE_END_FLG == 1)
	{
		ps2code = PS2KeyCodeGet();
		PS2KCODE_END_FLG = 0;
		PS2KCODE = 0;
	}
	else
	{
		;
	}
	return (ps2code);
}
/****************************************************************************
 * 函  数：Uint8 PS2KeyCodeReal(void);
 * 功  能：将按键（0~9）的通码转化为按键的真值。功能键未做转化。
 * 参  数：无
 * 返回值：Uint8 ：经过转换后的按键编码。如果没有键按下则返回0xFF
 * 更  新：无
 * 备  注：通码码表如下:
		#define PS2_NUM		0x77
		#define PS2_DIV		0x4A
		#define PS2_MUL		0x7C
		#define PS2_MIN		0x7B
		#define PS2_ADD		0x79
		#define PS2_ENT		0x5A
		#define PS2_BSP		0x66
		#define PS2_PNT		0x71
		#define PS2_0		0x70
		#define PS2_1		0x69
		#define PS2_2		0x72
		#define PS2_3		0x7A
		#define PS2_4		0x6B
		#define PS2_5		0x73
		#define PS2_6		0x74
		#define PS2_7		0x6C
		#define PS2_8		0x75
		#define PS2_9		0x7D
****************************************************************************/
uint8_t PS2KeyCodeReal(void)
{
	uint8_t /*i = 0,*/funcode = 0;
	funcode = PS2KeyCodeRslt();
#define __METHOD 1				
#if (__METHOD == 1)
	switch(funcode)
	{
		case 0: 
		{
			return (0xFF);
		}
		case PS2_0:
		{
			return (0);
		}
		case PS2_1:
		{
			return (1);
		}
		case PS2_2:
		{
			return (2);
		}
		case PS2_3:
		{
			return (3);
		}
		case PS2_4:
		{
			return (4);
		}
		case PS2_5:
		{
			return (5);
		}
		case PS2_6:
		{
			return (6);
		}
		case PS2_7:
		{
			return (7);
		}
		case PS2_8:
		{
			return (8);
		}
		case PS2_9:
		{
			return (9);
		}
		default:
		{
			return (funcode);
		}
	}
#elif (__METHOD == 2)
	if(funcode == 0)
	{
		return (0xFF);
	}
	else
	{
		for(;i<10;i++)
		{
			if(funcode == PS2NUM_TABLE[i])
			return (i);
		}
	}
	return (funcode);

#endif
}
/****************************************************************************
 * 函  数：Uint32 Power10(int8 x);
 * 功  能：求10的x次幂。最大为9次幂
 * 参  数：无
 * 返回值：Uint32 ：10的x次幂
 * 更  新：无
 * 备  注：无
****************************************************************************/
uint32_t Power10(uint8_t x)
{
	switch(x)
	{
		case 0  : return (1L);
		case 1  : return (10L);
		case 2  : return (100L);
		case 3  : return (1000L);
		case 4  : return (10000L);
		case 5  : return (100000L);
		case 6  : return (1000000L);
		case 7  : return (10000000L);
		case 8  : return (100000000L);
		case 9  : return (1000000000L);
		default : return (0);
	}
}
/****************************************************************************
 * 函  数：void PS2KeyNumInpt(void);
 * 功  能：从键盘上接收一个长度不超过NUM_LEN的int32型数，将该数信息保存到
		 PS2KNUM[]数组中。
 * 参  数：无
 * 返回值：无
 * 更  新：无
 * 备  注：无
****************************************************************************/
void PS2KeyNumInpt(void)
{
	uint8_t realcode = 0;
	realcode = PS2KeyCodeReal();
	switch(realcode)
	{
		case 0xFF:
		{
			break;
		}
		case PS2_BSP:
		{
			if(PS2KNUM_COUNT >0)
			PS2KNUM_COUNT--;
			break;
		}
		case PS2_MIN:
		{
			PS2KNUM_SIGN = !PS2KNUM_SIGN;
			break;
		}
		case PS2_PNT:
		{
			break;
		}
		case PS2_NUM:
		{
			PS2KNUM_FLG = !PS2KNUM_FLG;
			break;
		}
		case PS2_DIV:
		{
			break;
		}
		case PS2_MUL:
		{
			break;
		}
		case PS2_ADD:
		{
			break;
		}
		case PS2_ENT:
		{
			PS2KNUM_END_FLG = 1;
			break;
		}
		default:
		{
			PS2KNUM[PS2KNUM_COUNT] = realcode;
			PS2KNUM_COUNT++;
			if(PS2KNUM_COUNT > NUM_LEN-1)
				PS2KNUM_COUNT = NUM_LEN-1;
		}
	}
}
/****************************************************************************
 * 函  数：Uint32 PS2KeyNumRslt(void);
 * 功  能：若检测到Uint32型数输入完成标志PS2KNUM_END_FLG置位后（Enter按下）
			得到该int32型数的值。
 * 参  数：空
 * 返回值：Uint32 result or 0xFFFFFFFF。若没有转化完成则返回0xFFFFFFFF
			完成后返回输入的int32型数的值。
 * 更  新：无
 * 备  注：无
****************************************************************************/
uint32_t PS2KeyNumRslt(void)
{
	uint32_t result = 0;
	uint8_t  i = 0;
	PS2KeyNumInpt();
	if(PS2KNUM_END_FLG)
	{
		PS2KNUM_END_FLG = 0;
		for(; i<PS2KNUM_COUNT; i++)
		{
			result += PS2KNUM[i] * Power10(PS2KNUM_COUNT-i-1);
		}
		for(i=0;i<PS2KNUM_COUNT;i++)
		{
			PS2KNUM[i] = 0;
		}
		PS2KNUM_COUNT = 0;
		return (result);
	}
	return (0xFFFFFFFF);
}
/****************************************************************************
 * No more.
****************************************************************************/



