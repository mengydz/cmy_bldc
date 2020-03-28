#ifndef _USART2_H
#define _USART2_H

extern void USART2_GPIOConfig(void);
extern void USART2_NVICConfing(void);
extern void USART2_Config(void);
extern void USART2_SendString(char* data);

#endif
