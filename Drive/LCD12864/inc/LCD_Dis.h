//LCD 初始化函数，一般用于LCD屏的寄存器初始化
extern void LCD_Init(void);	//在LCD_Driver_User.c中定义的函数，如有必要该函数还会包含端口初始化、复位等操作
//LCD 引脚配置
extern void LCD_GPIOConfig(void);
//画直线函数，s_x、s_y为起始点，e_x、e_y为结束点
//extern void Line(unsigned char s_x,unsigned char s_y,unsigned char e_x,unsigned char e_y);
//绘图模式、当前绘图颜色设置
extern void SetPaintMode(unsigned char Mode,unsigned char Color);
//标准字符设置，包括两型号ASCII码的大小尺寸，以及字体颜色的设置
extern void FontSet(unsigned char Font_NUM,unsigned char Color);
//于x、y的坐标上写入一个标准字符
extern void PutChar(unsigned char x,unsigned char y,char a);
//于x、y的坐标为起始写入一串标准字符串
extern void PutString(unsigned char x,unsigned char y,char *p);
//于x、y的坐标为中心，绘制一个圆边或实心圆
//extern void PutPixel(unsigned char x,unsigned char y);
//extern void Circle(unsigned char x,unsigned char y,unsigned char r,unsigned char mode);
//绘制一个以left、top和right、bottom为两个对角的矩形框或者实心矩形
extern void Rectangle(unsigned char left,unsigned char top,unsigned char right,unsigned char bottom);
//清屏函数，执行全屏幕清除或填充前景色
extern void ClrScreen(unsigned char Mode);

//以下函数以及变量的声明一般建议用户不要调用，仅供高级用户在自行编写特殊显示效果以及特性应用程序时使用
//
//extern unsigned char code Asii16[];	//8X16的ASII字符库
//extern unsigned char code GB32[];		//自定义的32X29汉字库
//extern unsigned char code GB48[];		//自定义的48X55汉字库

extern unsigned char X_Witch;					//字符写入时的宽度
extern unsigned char Y_Witch;					//字符写入时的高度
extern unsigned char Font_Wrod;				//字体的大
extern unsigned char *Char_TAB;				//字库指针
//extern unsigned char Plot_Mode;			//绘图模式
extern unsigned char BMP_Color;
extern unsigned char Char_Color;

//extern void Pos_Switch(unsigned int * x,unsigned int * y);
//extern void Writ_Dot(int x,int y,unsigned int Color);
//extern void Line_f(int s_x,int s_y,int e_x);
//extern unsigned int Get_Dot(int x,int y);
//extern void Clear_Dot(int x,int y);
//extern void Set_Dot_Addr(int x,int y);
