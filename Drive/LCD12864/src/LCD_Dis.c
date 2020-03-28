//========================================================================
// 文件名: LCD_Dis.c
// 作  者: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//			www.Mzdesign.com.cn
// 日  期: 2007/05/17
// 描  述: 串行接口版LCD用户接口层程序集
//
// 参  考: 请参考具体显示器的硬件描述说明书或者是DataSheet,并以此来编写加速
//			版接口程序;适用于MCS51系列MCU驱动串行的只写入无法读出的LCD
// 版  本:
//      2007/05/17      First version    Mz Design
//========================================================================
#include "LCD_Driver_User.h"						//LCD底层驱动声明头文件
#include "LCD_Config.h"									//LCD的配置文件，比如坐标轴是否倒置等的定义
#include "LCD_Dis.h"

extern unsigned char Asii0608[];				//6X8的ASII字符库
extern unsigned char Asii0816[];				//8X16的ASII字符库
extern unsigned char GB1616[];					//16*16自定义的汉字库

unsigned char X_Witch;									//字符写入时的宽度
unsigned char Y_Witch;									//字符写入时的高度
unsigned char Font_Wrod;								//字体的每个字模占用多少个存储单元数
unsigned char *Char_TAB;						    //字库指针
//unsigned char Plot_Mode;							//绘图模式
unsigned char BMP_Color;
unsigned char Char_Color;

//========================================================================
// 函数: void FontSet(int Font_NUM,unsigned int Color)
// 描述: 文本字体设置
// 参数: Font_NUM 字体选择,以驱动所带的字库为准
//		 Color  文本颜色,仅作用于自带字库  
// 返回: 无
// 备注: 
// 版本:
//      2006/10/15      First version
//========================================================================
void FontSet(unsigned char Font_NUM,unsigned char Color)
{
	switch(Font_NUM)
	{
		case 0: Font_Wrod = 16;	//ASII字符A
				X_Witch = 8;
				Y_Witch = 2;
				Char_Color = Color;
				Char_TAB = &Asii0816[0] - 512;	  //32*16
		break;
		case 1: Font_Wrod = 6;	//ASII字符B
				X_Witch = 6;
				Y_Witch = 1;
				Char_Color = Color;
				Char_TAB = &Asii0608[0] - 192;	  //32*6
		break;		
		case 2: Font_Wrod = 32;	//汉字A
				X_Witch = 16;
				Y_Witch = 2;
				Char_Color = Color;
				Char_TAB =(unsigned char *)GB1616;
		break;
		/*
		case 3: Font_Wrod = 16;	//汉字B
				X_Witch = 16;
				Y_Witch = 2;
				Char_Color = Color;
				Char_TAB = GB16;
		break;*/
		default: break;
	}
}
//========================================================================
// 函数: void PutChar(unsigned char x,unsigned char y,char a)  
// 描述: 写入一个标准字符
// 参数: x  X轴坐标     y  Y轴坐标(0~7页)
//		 	 a  要显示的字符在字库中的偏移量  
// 返回: 无
// 备注: ASCII字符可直接输入ASCII码即可
// 版本:
//       2006/10/15      First version
//			 2007/05/17			 V2.1  for seriea port LCD
//========================================================================
void PutChar(unsigned char x,unsigned char y,char a)       
{
	unsigned char i,j;
	unsigned char *p_data; 
	p_data = Char_TAB + a*Font_Wrod;	//要写字符的首地址
	x = x+1;							//Edit by xinqiang
	for(j=0;j<Y_Witch;j++)
	{
		if((y+j) < (Dis_Y_MAX/8))
			LCD_RegWrite(y+j+0xb0);
		LCD_RegWrite(((x&0xf0) >> 4)|0x10);	//设置初始地址 
		LCD_RegWrite(x&0x0f);
		for(i=0;i<X_Witch;i++)
		{  
			if(((x+i) < Dis_X_MAX)&&((y+j) < (Dis_Y_MAX/8)))
				LCD_DataWrite(*p_data++);
		}
	}
}

//========================================================================
// 函数: void PutString(unsigned char x,unsigned char y,char *p)
// 描述: 在x、y为起始坐标处写入一串标准字符
// 参数: x  X轴坐标     y  Y轴坐标(0~7页)
//		 p  要显示的字符串  
// 返回: 无
// 备注: 仅能用于自带的ASCII字符串显示
// 版本:
//      2006/10/15      First version
//========================================================================
void PutString(unsigned char x,unsigned char y,char *p)
{
	while(*p!=0)
	{
		PutChar(x,y,*p);
		x += X_Witch;
		if((x + X_Witch) > Dis_X_MAX)
		{
			x = 0;
			if((Dis_Y_MAX - y) < Y_Witch) break;
			else y += Y_Witch;
		}
		p++;
	}
}
//========================================================================
// 函数: void SetPaintMode(int Mode,unsigned int Color)
// 描述: 绘图模式设置
// 参数: Mode 绘图模式    Color  像素点的颜色,相当于前景色  
// 返回: 无
// 备注: Mode无效
// 版本:
//      2006/10/15      First version
//========================================================================
void SetPaintMode(unsigned char Mode,unsigned char Color)
{
	Mode = Mode;//Plot_Mode = Mode;		//仅仅是为了保持与其它驱动的一至性，绘图模式在该版驱动中未用
	BMP_Color = Color;
}
//========================================================================
// 函数: void Rectangle(unsigned char left, unsigned char top, unsigned char right,
//						 unsigned char bottom, unsigned char Mode)
// 描述: 以x,y为圆心R为半径画一个圆(mode = 0) or 圆面(mode = 1)
// 参数: left - 矩形的左上角横坐标，范围0到126
//		 top - 矩形的左上角纵坐标(0~7页)，范围0到6
//		 right - 矩形的右下角横坐标，范围1到127
//		 bottom - 矩形的右下角纵坐标(0~7页)，范围0到7
// 返回: 无
// 备注: 画圆函数执行较慢，如果MCU有看门狗，请作好清狗的操作
// 版本:
//      2005/05/21      First version
//		2007/05/17		V2.1  for seriea port LCD
//========================================================================
void Rectangle(unsigned char left, unsigned char top, unsigned char right, unsigned char bottom)
{
	unsigned char uiTemp,ucTemp2;
	if(left>right)
	{
		uiTemp = left;
		left = right;
		right = uiTemp;
	}
	if(top>bottom)
	{
		uiTemp = top;
		top = bottom;
		bottom = uiTemp;
	}
	for(uiTemp=top;uiTemp<=bottom;uiTemp++)
	{
		LCD_RegWrite(uiTemp+0xb0);
		LCD_RegWrite(((left&0xf0) >> 4)|0x10);	//设置初始地址 
		LCD_RegWrite(left&0x0f);
		for(ucTemp2=left;ucTemp2<=right;ucTemp2++)
		{
			LCD_DataWrite(BMP_Color);
		}
	}
}
//========================================================================
// 函数: void ClrScreen(unsigned int Mode)
// 描述: 清屏函数，执行全屏幕清除或填充前景色
// 参数: Mode   0:全屏除屏
//				1:全屏填充前景色
// 返回: 无
// 备注: 
// 版本:
//      2007/01/11      First version
//========================================================================
void ClrScreen(unsigned char Mode)
{
	if(Mode==0)
		LCD_Fill(LCD_INITIAL_COLOR);
	else
		LCD_Fill(BMP_Color);
}
