//LCD ��ʼ��������һ������LCD���ļĴ�����ʼ��
extern void LCD_Init(void);	//��LCD_Driver_User.c�ж���ĺ��������б�Ҫ�ú�����������˿ڳ�ʼ������λ�Ȳ���
//LCD ��������
extern void LCD_GPIOConfig(void);
//��ֱ�ߺ�����s_x��s_yΪ��ʼ�㣬e_x��e_yΪ������
//extern void Line(unsigned char s_x,unsigned char s_y,unsigned char e_x,unsigned char e_y);
//��ͼģʽ����ǰ��ͼ��ɫ����
extern void SetPaintMode(unsigned char Mode,unsigned char Color);
//��׼�ַ����ã��������ͺ�ASCII��Ĵ�С�ߴ磬�Լ�������ɫ������
extern void FontSet(unsigned char Font_NUM,unsigned char Color);
//��x��y��������д��һ����׼�ַ�
extern void PutChar(unsigned char x,unsigned char y,char a);
//��x��y������Ϊ��ʼд��һ����׼�ַ���
extern void PutString(unsigned char x,unsigned char y,char *p);
//��x��y������Ϊ���ģ�����һ��Բ�߻�ʵ��Բ
//extern void PutPixel(unsigned char x,unsigned char y);
//extern void Circle(unsigned char x,unsigned char y,unsigned char r,unsigned char mode);
//����һ����left��top��right��bottomΪ�����Խǵľ��ο����ʵ�ľ���
extern void Rectangle(unsigned char left,unsigned char top,unsigned char right,unsigned char bottom);
//����������ִ��ȫ��Ļ��������ǰ��ɫ
extern void ClrScreen(unsigned char Mode);

//���º����Լ�����������һ�㽨���û���Ҫ���ã������߼��û������б�д������ʾЧ���Լ�����Ӧ�ó���ʱʹ��
//
//extern unsigned char code Asii16[];	//8X16��ASII�ַ���
//extern unsigned char code GB32[];		//�Զ����32X29���ֿ�
//extern unsigned char code GB48[];		//�Զ����48X55���ֿ�

extern unsigned char X_Witch;					//�ַ�д��ʱ�Ŀ��
extern unsigned char Y_Witch;					//�ַ�д��ʱ�ĸ߶�
extern unsigned char Font_Wrod;				//����Ĵ�
extern unsigned char *Char_TAB;				//�ֿ�ָ��
//extern unsigned char Plot_Mode;			//��ͼģʽ
extern unsigned char BMP_Color;
extern unsigned char Char_Color;

//extern void Pos_Switch(unsigned int * x,unsigned int * y);
//extern void Writ_Dot(int x,int y,unsigned int Color);
//extern void Line_f(int s_x,int s_y,int e_x);
//extern unsigned int Get_Dot(int x,int y);
//extern void Clear_Dot(int x,int y);
//extern void Set_Dot_Addr(int x,int y);
