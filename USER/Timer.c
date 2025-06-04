#ifndef _TIMER_C_
#define _TIMER_C_

#include 	"include.h"

#define FRC_HZ							16000000
#define FRC_DIV							1
#define CLK_US              500                     //100us
#define TIME_RELOAD        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US/1000))   //精度更高

unsigned int idata l_value = 0;
bit b_10ms_flag;
/******************************************************************************************
** 函数名称: timer0_init
** 函数描述: time0初始化函数   
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void timer0_init()
{
	TMOD = (TMOD & ~ 0x03) | 0x01;       							// Timer0模式选择  0: 8位定时器/计数器（TH0） 和5位预分频器（TL0）1:16位定时器/计数器 
	                                                                 // 2:8位自动重载定时器/计数器（TL0） 3:TL0是一个8位定时器/计数器。TH0 是一个8位定时器/计数器                     

	TH0 = (TIME_RELOAD) / 256;                                     // 100US
	TL0 = (TIME_RELOAD) % 256;

	TR0 = 1;                                                       // TIMER0 运行
	ET0 = 1;                                                        //允许TIMER0中断
	PT0 = 1;
	IPH = (IPH&0XFD)|0X02;

}

void timer0_Stop()
{
	TMOD = 0;       							// Timer0模式选择  0: 8位定时器/计数器（TH0） 和5位预分频器（TL0）1:16位定时器/计数器 
	                                                                 // 2:8位自动重载定时器/计数器（TL0） 3:TL0是一个8位定时器/计数器。TH0 是一个8位定时器/计数器                     

	TH0 = 0;                                     // 100US
	TL0 = 0;

	TR0 = 0;                                                       // TIMER0 运行
	ET0 = 0;                                                       //允许TIMER0中断
 

}
/******************************************************************************************
** 函数名称: timer0_int
** 函数描述: time0中断处理函数
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
void timer0_irq(void) interrupt 1
{
    static unsigned char T2 = 0, T1 = 0;

    TH0 = (u8)(TIME_RELOAD >> 8);
    TL0 = (u8)(TIME_RELOAD & 0xFF);

    /*============================ ① 湿度采样 ============================*/
    if (hum_run == 1)
    {
        /* 每 250 μs 翻转互补方波 */
			
			
				switch(hum_phase)
				{
					case 0:
            P15 = 0;  P17 = 1;
						hum_phase = 1;
					break;
					case 1:
					
            P15 = 1;  P17 = 0;	
						hum_phase = 2;
					ADSOC = 1;
					break;
					case 2:
						if(ADSOC)break;
						ADSOC = 0;
						 hum_acc += (((ADCDH << 4) & 0xFF0) | (ADCDL >> 4));      /* 已选好 ADC9      */
            if (++hum_cnt >= 10) {           /* 满 10 样本       */
							  hum_acc = hum_acc / 10;
                hum_run   = 2;               /* 采样结束         */

                /* 把 IO 拉低，释放 ADC 给温度 */
                P15 = 0; P17 = 0;
            }
						hum_phase = 0;
					break;
				}
    }

    /*============================ ② 原有 100 μs/10 ms 任务 ===============*/
    Nixie_Loop();

    if (l_value) l_value--;
    if (++T1 < 4) return;                   /* 250 μs ×4 = 1 ms */
    T1 = 0;

    if (AdDet1MS)  AdDet1MS--;
    if (!B_KeySCAN) B_KeySCAN = 1;
    if (R_KeyHoldTimer) R_KeyHoldTimer--;

    if (++T2 >= 10) {                       /* 1 ms ×10 = 10 ms */
        T2 = 0;
        b_10ms_flag = 1;
    }
}


void delay_ms(unsigned int ms)
{
	l_value = ms;
	while(l_value);
}



#endif