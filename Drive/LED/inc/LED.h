#ifndef _LED_H
#define _LED_H

#define LED0_PORT	GPIOC
#define LED0_Pin	GPIO_Pin_3

void LED_GPIOConfig(void);
void LED_On(void);
void LED_Off(void);
#endif
