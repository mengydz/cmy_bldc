#ifndef __PS2_H__
#define __PS2_H__

/*START**************************Ӧ�ò㶨��*********************************/
//���а�����ͨ��궨��
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
//0~9  PS2����ͨ�����
extern u8 PS2NUM_TABLE[];
extern uint8_t PS2KCODE;
extern uint8_t PS2KCODE_END_FLG;
/*****************************��������Ϣ���ݽṹ****************************/
//�����������������󳤶�
#define NUM_LEN 10
/**END***************************Ӧ�ò㶨��*********************************/
/*******************************�ؼ�����ע��********************************/
#define __USE_DSP

#ifdef __USE_DSP
	#define PS2KDATA_IN() GpioMuxRegs.GPEMUX.bit.XINT2_ADCSOC_GPIOE1 = 0; \
					GpioMuxRegs.GPEDIR.bit.GPIOE1 = 0;\
					GpioMuxRegs.GPEQUAL.bit.QUALPRD = 0

	#define PS2KCLK	 GpioDataRegs.GPEDAT.bit.GPIOE0
	#define PS2KDATA GpioDataRegs.GPEDAT.bit.GPIOE1
#endif //__USE_DSP

/*********************************����������********************************/
extern void 	PS2_GPIOConfig(void);
extern void 	PS2_EXITConfig(void);
extern void 	PS2_NVICConfig(void);
extern uint8_t  PS2KeyCodeRslt(void);
extern uint8_t  PS2KeyCodeReal(void);
extern void 	PS2KeyNumInpt(void);
extern uint32_t PS2KeyNumRslt(void);
#endif
