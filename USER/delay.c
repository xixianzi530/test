#ifndef __DELAY_C__
#define __DELAY_C__

#include 	<intrins.h>
#include	"REGSH368.h"

#include 	"include.h"
void bsp_delay(unsigned int delay_cnt) 
{
		while(delay_cnt--)
		{
			delay_19nop();
			delay_19nop();
			delay_19nop();
			delay_19nop();
		}

}





#endif