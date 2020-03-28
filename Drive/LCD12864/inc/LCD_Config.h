
#define 	LCD_X_MAX				128-1			//屏幕的X轴的物理宽度
#define 	LCD_Y_MAX				64-1			//屏幕的Y轴的物理宽度
			
#define 	LCD_XY_Switch		0					//显示时X轴和Y由交换
#define 	LCD_X_Rev				0					//显示时X轴反转
#define 	LCD_Y_Rev				0					//显示时Y轴反转

#if LCD_XY_Switch == 0
	#define 	Dis_X_MAX		LCD_X_MAX
	#define 	Dis_Y_MAX		LCD_Y_MAX	
#endif

#if LCD_XY_Switch == 1
	#define 	Dis_X_MAX		LCD_Y_MAX
	#define 	Dis_Y_MAX		LCD_X_MAX	
#endif

#define LCD_INITIAL_COLOR	0x00			//定义LCD屏初始化时的背景色



/*************************************************************/
//以下定义为针对于SPLC501的功能指令进行定义的，局部可修改~
/********************** LCD供电电平选择 **********************/
#define		M_LCD_VDD_SET		M_LCD_SETR_4		//3.3V供电时选此二项
#define		M_LCD_VDD				M_LCD_BIAS_9		//....
//#define		M_LCD_VDD_SET		M_LCD_SETR_4	//5.0V供电时选此二项
//#define		M_LCD_VDD				M_LCD_BIAS_9	//...


/************************* LCD指令 ***************************/
//LCD开关命令
#define		M_LCD_ON					0xaf
#define		M_LCD_OFF					0xae
//设置上电控制模式
#define		M_LCD_POWER_BC		0x2c
#define		M_LCD_POWER_VR		0x2a
#define		M_LCD_POWER_VC		0x29
#define		M_LCD_POWER_ALL		0x2f
//V5内部电压调节电阻设置……
#define		M_LCD_SETR_0			0x20
#define		M_LCD_SETR_1			0x21
#define		M_LCD_SETR_2			0x22
#define		M_LCD_SETR_3			0x23
#define		M_LCD_SETR_4			0x24
#define		M_LCD_SETR_5			0x25
#define		M_LCD_SETR_6			0x26
#define		M_LCD_SETR_7			0x27
//...end
#define		M_LCD_ELE_VOL			0x81		//电量设置模式（显示亮度）
//偏压设置
#define		M_LCD_BIAS_9			0xa2		//V5时选此选项设置
#define		M_LCD_BIAS_7			0xa1		//V3时选此选项设置
//Com 扫描方式设置命令
#define		M_LCD_COM_NOR			0xc0		//正常方式
#define		M_LCD_COM_REV			0xc8		//反相
//Segment方向选择
#define		M_LCD_SEG_NOR			0xa0		//正常
#define		M_LCD_SEG_REV			0xa1		//反向
//全屏点亮/变暗指令
#define		M_LCD_ALL_LIGNT		0xa5		//LCD ALL paint ON
#define		M_LCD_ALL_LOW			0xa4		//Normal Display mode
//正相反相显示控制指令,RAM中数据不变
#define		M_LCD_ALL_NOR			0xa6		//正相
#define		M_LCD_ALL_REV			0xa7		//反相
//静态指示器控制指令
#define		M_LCD_STATIC_ON		0xad		//ON
#define		M_LCD_STATIC_OFF 	0xac		//OFF
//设置显示起始行对应RAM行号
#define		M_LCD_BEGIN_LINE 	0x40		//基数，后面可加的尾数可为0~63
//设置当前页基数
#define		M_LCD_COL_PAGE		0xb0		//基数指令，后可加尾数0~8
//设置当前列基数
#define		M_LCD_COL_LINE_LOW	0x04		//基数指令，低四位有效
#define		M_LCD_COL_LINE_HIG	0x10		//基数指令，低四位有效
