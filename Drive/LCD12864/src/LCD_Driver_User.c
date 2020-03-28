//========================================================================
// �ļ���: LCD_Driver_User.c
// ��  ��: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//				 www.Mzdesign.com.cn
// ��  ��: 2007/05/17
// ��  ��: �ײ�ӿ�������չ����
//
// ��  ��: ��ο�������ʾ����Ӳ������˵���������DataSheet,���Դ�����д��
//				 ��ӿ����������Լ�LCD�ĳ�ʼ������
// ��  ��: 2007/05/17      First version    Mz Design
// ע  ��: 
//				 ��������������ͨ�ð�LCD���������޸Ķ�������ҪΪ����Ӧ������MzL05
//				 �����Ľ���д�벻�ܶ������ݵ�LCD������
//========================================================================
#include "includes.h"
#include "LCD_Config.h"
#include "LCD_PortConfig.h"
#include "LCD_Dis.h"

//========================================================================
//��ʱ����
void Delay(void)
{
   unsigned char  t=0xf0;
   for( ; t>0 ; t--);
}
//========================================================================
// ����: 	void LCD_DataWrite(unsigned int Data)
// ����: 	дһ���ֽڵ���ʾ������LCD�е���ʾ����RAM����
// ����: 	Data д������� 
// ����: 	��
// ��ע: 	��
// �汾:
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
// ����: 	void LCD_RegWrite(unsigned char Command)
// ����: 	дһ���ֽڵ�������LCD�еĿ��ƼĴ�������
// ����: 	Command		д������ݣ��Ͱ�λ��Ч��byte�� 
// ����: 	��
// ��ע: 
// �汾:
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
// ����: 	void LCD_Fill(unsigned int Data)
// ����: 	���������Data��������������
// ����: 	Data   Ҫ������ɫ����
// ����: 	��
// ��ע: 	����LCD��ʼ�������е���
// �汾:
//      	2006/10/15      First version
//				2007/01/09		V1.2 
//========================================================================
void LCD_Fill(unsigned char Data)
{
	unsigned char i,j;
	unsigned char uiTemp;
	uiTemp = Dis_Y_MAX;
	uiTemp = uiTemp>>3;
	for(i=0;i<=uiTemp;i++)								//��LCD������ʼ������ʾ����
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
// ����: 	void LCD_Init(void)
// ����: 	LCD��ʼ����������������LCD��ʼ����Ҫ���õ����Ĵ������������
//		 		�û����˽⣬����鿴DataSheet���и����Ĵ���������
// ����: 	�� 
// ����: 	��
// ��ע:
// �汾:
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
	LCD_RegWrite(M_LCD_POWER_ALL);				//�����ϵ����ģʽ
	
	LCD_RegWrite(M_LCD_ELE_VOL);					//��������ģʽ����ʾ���ȣ�
	LCD_RegWrite(0x1f);										//ָ������0x0000~0x003f
	
	LCD_RegWrite(M_LCD_VDD_SET);					//V5�ڲ���ѹ���ڵ�������
	LCD_RegWrite(M_LCD_VDD);							//LCDƫѹ���ã�V3ʱѡ
	
	LCD_RegWrite(M_LCD_COM_REV);					//Com ɨ�跽ʽ����
	LCD_RegWrite(M_LCD_SEG_NOR);					//Segment����ѡ��
	LCD_RegWrite(M_LCD_ALL_LOW);					//ȫ������/�䰵ָ��
	LCD_RegWrite(M_LCD_ALL_NOR);					//��������ʾ����ָ��
	
	LCD_RegWrite(M_LCD_STATIC_OFF);				//�رվ�ָ̬ʾ��
	LCD_RegWrite(0x00);										//ָ������
	
	LCD_RegWrite(M_LCD_BEGIN_LINE);				//������ʾ��ʼ�ж�ӦRAM
	LCD_Fill(LCD_INITIAL_COLOR);
}

void LCD_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/* PB0 PB1 PB2 PB3 PB4 -LCD */ 
	GPIO_InitStruct.GPIO_Pin   = PIO_CS | PIO_RES | PIO_A0 | PIO_CLK | PIO_SDI;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;	 			/* ��©��� */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;				/* 50MHzʱ���ٶ� */
	GPIO_Init( LCD_CS , &GPIO_InitStruct);
} 

