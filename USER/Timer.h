#ifndef _TIMER_H_
#define _TIMER_H_

extern bit b_10ms_flag;
extern unsigned int idata l_value ;

void delay_ms(unsigned int ms);
void tim3_init(void);
void timer0_init();
void timer0_Stop();
#endif
