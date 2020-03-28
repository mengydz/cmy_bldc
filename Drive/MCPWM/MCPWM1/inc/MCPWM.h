#ifndef _MCPWM_H
#define _MCPWM_H

/**********************************************************************
* Description    : PWM　初始化
* Attention      : None
**********************************************************************/
extern void MCPWM1_GPIOConfig(void);
extern void MCPWM1_Config(void);
/**********************************************************************
* Description    : 控制PWM的开关
* Attention      : None
**********************************************************************/
extern void PWM1_OC1Start(void);
extern void PWM1_OC1Stop(void);
extern void PWM1_OC1NStart(void);
extern void PWM1_OC1NStop(void);
extern void PWM1_OC2Start(void);
extern void PWM1_OC2Stop(void);
extern void PWM1_OC2NStart(void);
extern void PWM1_OC2NStop(void);
extern void PWM1_OC3Start(void);
extern void PWM1_OC3Stop(void);
extern void PWM1_OC3NStart(void);
extern void PWM1_OC3NStop(void);
extern void PWM1_OC4Start(void);
extern void PWM1_OC4Stop(void);
/**********************************************************************
* Description    : 控制PWM的占空比
* Attention      : None
**********************************************************************/
extern void PWM1_SetOC1Pulse(uint16_t pulse);
extern void PWM1_SetOC2Pulse(uint16_t pulse);
extern void PWM1_SetOC3Pulse(uint16_t pulse);
extern void PWM1_SetOC4Pulse(uint16_t pulse); 
#endif
