#ifndef _DYP_ME007_H
#define _DYP_ME007_H

extern void DYP_ME007GPIOConfig(void);
extern void DYP_ME007SendTrig(void);
extern void DYP_ME007Receive(uint16_t time);
extern uint16_t DYP_ME007Process(void);

#endif
