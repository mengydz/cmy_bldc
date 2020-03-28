#ifndef  _USART1_H
#define  _USART1_H


extern void USART1_GPIOConfig(void);
extern void USART1_Config(void);
extern void USART1_NVICConfig(void);
extern void USART1_SendString( char* data);

extern u8 ASCII_Buff[5];

#endif
