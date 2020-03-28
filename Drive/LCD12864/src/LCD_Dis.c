//========================================================================
// �ļ���: LCD_Dis.c
// ��  ��: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//			www.Mzdesign.com.cn
// ��  ��: 2007/05/17
// ��  ��: ���нӿڰ�LCD�û��ӿڲ����
//
// ��  ��: ��ο�������ʾ����Ӳ������˵���������DataSheet,���Դ�����д����
//			��ӿڳ���;������MCS51ϵ��MCU�������е�ֻд���޷�������LCD
// ��  ��:
//      2007/05/17      First version    Mz Design
//========================================================================
#include "LCD_Driver_User.h"						//LCD�ײ���������ͷ�ļ�
#include "LCD_Config.h"									//LCD�������ļ��������������Ƿ��õȵĶ���
#include "LCD_Dis.h"

extern unsigned char Asii0608[];				//6X8��ASII�ַ���
extern unsigned char Asii0816[];				//8X16��ASII�ַ���
extern unsigned char GB1616[];					//16*16�Զ���ĺ��ֿ�

unsigned char X_Witch;									//�ַ�д��ʱ�Ŀ��
unsigned char Y_Witch;									//�ַ�д��ʱ�ĸ߶�
unsigned char Font_Wrod;								//�����ÿ����ģռ�ö��ٸ��洢��Ԫ��
unsigned char *Char_TAB;						    //�ֿ�ָ��
//unsigned char Plot_Mode;							//��ͼģʽ
unsigned char BMP_Color;
unsigned char Char_Color;

//========================================================================
// ����: void FontSet(int Font_NUM,unsigned int Color)
// ����: �ı���������
// ����: Font_NUM ����ѡ��,�������������ֿ�Ϊ׼
//		 Color  �ı���ɫ,���������Դ��ֿ�  
// ����: ��
// ��ע: 
// �汾:
//      2006/10/15      First version
//========================================================================
void FontSet(unsigned char Font_NUM,unsigned char Color)
{
	switch(Font_NUM)
	{
		case 0: Font_Wrod = 16;	//ASII�ַ�A
				X_Witch = 8;
				Y_Witch = 2;
				Char_Color = Color;
				Char_TAB = &Asii0816[0] - 512;	  //32*16
		break;
		case 1: Font_Wrod = 6;	//ASII�ַ�B
				X_Witch = 6;
				Y_Witch = 1;
				Char_Color = Color;
				Char_TAB = &Asii0608[0] - 192;	  //32*6
		break;		
		case 2: Font_Wrod = 32;	//����A
				X_Witch = 16;
				Y_Witch = 2;
				Char_Color = Color;
				Char_TAB =(unsigned char *)GB1616;
		break;
		/*
		case 3: Font_Wrod = 16;	//����B
				X_Witch = 16;
				Y_Witch = 2;
				Char_Color = Color;
				Char_TAB = GB16;
		break;*/
		default: break;
	}
}
//========================================================================
// ����: void PutChar(unsigned char x,unsigned char y,char a)  
// ����: д��һ����׼�ַ�
// ����: x  X������     y  Y������(0~7ҳ)
//		 	 a  Ҫ��ʾ���ַ����ֿ��е�ƫ����  
// ����: ��
// ��ע: ASCII�ַ���ֱ������ASCII�뼴��
// �汾:
//       2006/10/15      First version
//			 2007/05/17			 V2.1  for seriea port LCD
//========================================================================
void PutChar(unsigned char x,unsigned char y,char a)       
{
	unsigned char i,j;
	unsigned char *p_data; 
	p_data = Char_TAB + a*Font_Wrod;	//Ҫд�ַ����׵�ַ
	x = x+1;							//Edit by xinqiang
	for(j=0;j<Y_Witch;j++)
	{
		if((y+j) < (Dis_Y_MAX/8))
			LCD_RegWrite(y+j+0xb0);
		LCD_RegWrite(((x&0xf0) >> 4)|0x10);	//���ó�ʼ��ַ 
		LCD_RegWrite(x&0x0f);
		for(i=0;i<X_Witch;i++)
		{  
			if(((x+i) < Dis_X_MAX)&&((y+j) < (Dis_Y_MAX/8)))
				LCD_DataWrite(*p_data++);
		}
	}
}

//========================================================================
// ����: void PutString(unsigned char x,unsigned char y,char *p)
// ����: ��x��yΪ��ʼ���괦д��һ����׼�ַ�
// ����: x  X������     y  Y������(0~7ҳ)
//		 p  Ҫ��ʾ���ַ���  
// ����: ��
// ��ע: ���������Դ���ASCII�ַ�����ʾ
// �汾:
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
// ����: void SetPaintMode(int Mode,unsigned int Color)
// ����: ��ͼģʽ����
// ����: Mode ��ͼģʽ    Color  ���ص����ɫ,�൱��ǰ��ɫ  
// ����: ��
// ��ע: Mode��Ч
// �汾:
//      2006/10/15      First version
//========================================================================
void SetPaintMode(unsigned char Mode,unsigned char Color)
{
	Mode = Mode;//Plot_Mode = Mode;		//������Ϊ�˱���������������һ���ԣ���ͼģʽ�ڸð�������δ��
	BMP_Color = Color;
}
//========================================================================
// ����: void Rectangle(unsigned char left, unsigned char top, unsigned char right,
//						 unsigned char bottom, unsigned char Mode)
// ����: ��x,yΪԲ��RΪ�뾶��һ��Բ(mode = 0) or Բ��(mode = 1)
// ����: left - ���ε����ϽǺ����꣬��Χ0��126
//		 top - ���ε����Ͻ�������(0~7ҳ)����Χ0��6
//		 right - ���ε����½Ǻ����꣬��Χ1��127
//		 bottom - ���ε����½�������(0~7ҳ)����Χ0��7
// ����: ��
// ��ע: ��Բ����ִ�н��������MCU�п��Ź����������幷�Ĳ���
// �汾:
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
		LCD_RegWrite(((left&0xf0) >> 4)|0x10);	//���ó�ʼ��ַ 
		LCD_RegWrite(left&0x0f);
		for(ucTemp2=left;ucTemp2<=right;ucTemp2++)
		{
			LCD_DataWrite(BMP_Color);
		}
	}
}
//========================================================================
// ����: void ClrScreen(unsigned int Mode)
// ����: ����������ִ��ȫ��Ļ��������ǰ��ɫ
// ����: Mode   0:ȫ������
//				1:ȫ�����ǰ��ɫ
// ����: ��
// ��ע: 
// �汾:
//      2007/01/11      First version
//========================================================================
void ClrScreen(unsigned char Mode)
{
	if(Mode==0)
		LCD_Fill(LCD_INITIAL_COLOR);
	else
		LCD_Fill(BMP_Color);
}
