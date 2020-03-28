//========================================================================
// 文件名: LCD_Driver_User.c
// 作  者: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//				 www.Mzdesign.com.cn
// 日  期: 2007/05/17
// 描  述: 底层接口驱动扩展程序集
//
// 参  考: 请参考具体显示器的硬件描述说明书或者是DataSheet,并以此来编写底
//				 层接口驱动程序，以及LCD的初始化代码
// 版  本: 2007/05/17      First version    Mz Design
// 注  意: 
//				 该驱动程序是由通用版LCD驱动程序修改而来，主要为了适应类似于MzL05
//				 这样的仅能写入不能读出数据的LCD而做的
//========================================================================
#include "includes.h"
#include "LCD_Config.h"
#include "LCD_PortConfig.h"
#include "LCD_Dis.h"

//========================================================================
//延时程序
void Delay(void)
{
   unsigned char  t=0xf0;
   for( ; t>0 ; t--);
}
//========================================================================
// 函数: 	void LCD_DataWrite(unsigned int Data)
// 描述: 	写一个字节的显示数据至LCD中的显示缓冲RAM当中
// 参数: 	Data 写入的数据 
// 返回: 	无
// 备注: 	无
// 版本:
//      	2007/01/09      First version
//========================================================================
void LCD_DataWrite(unsigned char Dat)//,_Fill_Dot_LCD
{
	unsigned char Num;
    LCD_CS_L;
	LCD_A0_H;
	for(Num=0;Num<8;Num++)
	{
		if((Dat&0x80) == 0)	
			LCD_SDI_L;
		else  
			LCD_SDI_H;
		Dat = Dat << 1;
		LCD_CLK_L;
		Delay();
		LCD_CLK_H;
	}
	LCD_CS_H;
}
//========================================================================
// 函数: 	void LCD_RegWrite(unsigned char Command)
// 描述: 	写一个字节的数据至LCD中的控制寄存器当中
// 参数: 	Command		写入的数据，低八位有效（byte） 
// 返回: 	无
// 备注: 
// 版本:
//      	2007/01/09      First version
//========================================================================
void LCD_RegWrite(unsigned char Command)
{
	unsigned char Num;
//	LCD_CS = 0;
//	LCD_A0 = 0;
	LCD_CS_L;
	LCD_A0_L;
	for(Num=0;Num<8;Num++)
	{
		if((Command&0x80) == 0)
			LCD_SDI_L;//LCD_SDI = 0;
		else 
			LCD_SDI_H;//LCD_SDI = 1;
		Command = Command << 1;
//		LCD_CLK = 0;
//		LCD_CLK = 1;
		LCD_CLK_L;
		Delay();
		LCD_CLK_H;
	}
//	LCD_CS = 1;
 	LCD_CS_H;
}
//========================================================================
// 函数: 	void LCD_Fill(unsigned int Data)
// 描述: 	会屏填充以Data的数据至各点中
// 参数: 	Data   要填充的颜色数据
// 返回: 	无
// 备注: 	仅在LCD初始化程序当中调用
// 版本:
//      	2006/10/15      First version
//				2007/01/09		V1.2 
//========================================================================
void LCD_Fill(unsigned char Data)
{
	unsigned char i,j;
	unsigned char uiTemp;
	uiTemp = Dis_Y_MAX;
	uiTemp = uiTemp>>3;
	for(i=0;i<=uiTemp;i++)								//往LCD中填充初始化的显示数据
	{
		LCD_RegWrite(0xb0+i);
		LCD_RegWrite(0x01);
		LCD_RegWrite(0x10);
		for(j=0;j<=Dis_X_MAX;j++)
		{
			LCD_DataWrite(Data);
		}
	}
}
//========================================================================
// 函数: 	void LCD_Init(void)
// 描述: 	LCD初始化程序，在里面会完成LCD初始所需要设置的许多寄存器，具体如果
//		 		用户想了解，建议查看DataSheet当中各个寄存器的意义
// 参数: 	无 
// 返回: 	无
// 备注:
// 版本:
//      	2006/10/15      First version
//		  	2007/01/09		V1.2 
//========================================================================
void LCD_Init(void)
{
 	LCD_RES_L;
	CoTickDelay(1);
  	LCD_RES_H;
	CoTickDelay(1);
		
	LCD_RegWrite(M_LCD_ON);								//LCD On
	LCD_RegWrite(M_LCD_POWER_ALL);				//设置上电控制模式
	
	LCD_RegWrite(M_LCD_ELE_VOL);					//电量设置模式（显示亮度）
	LCD_RegWrite(0x1f);										//指令数据0x0000~0x003f
	
	LCD_RegWrite(M_LCD_VDD_SET);					//V5内部电压调节电阻设置
	LCD_RegWrite(M_LCD_VDD);							//LCD偏压设置，V3时选
	
	LCD_RegWrite(M_LCD_COM_REV);					//Com 扫描方式设置
	LCD_RegWrite(M_LCD_SEG_NOR);					//Segment方向选择
	LCD_RegWrite(M_LCD_ALL_LOW);					//全屏点亮/变暗指令
	LCD_RegWrite(M_LCD_ALL_NOR);					//正向反向显示控制指令
	
	LCD_RegWrite(M_LCD_STATIC_OFF);				//关闭静态指示器
	LCD_RegWrite(0x00);										//指令数据
	
	LCD_RegWrite(M_LCD_BEGIN_LINE);				//设置显示起始行对应RAM
	LCD_Fill(LCD_INITIAL_COLOR);
}

void LCD_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/* PB0 PB1 PB2 PB3 PB4 -LCD */ 
	GPIO_InitStruct.GPIO_Pin   = PIO_CS | PIO_RES | PIO_A0 | PIO_CLK | PIO_SDI;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;	 			/* 开漏输出 */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;				/* 50MHz时钟速度 */
	GPIO_Init( LCD_CS , &GPIO_InitStruct);
} 

