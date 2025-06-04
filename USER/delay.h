#ifndef __DELAY_H__
#define __DELAY_H__

#define delay_19nop()	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();	
void bsp_delay(unsigned int delay_cnt) ;
#endif