#ifndef _TIMER_C_
#define _TIMER_C_

#include 	"include.h"

#define FRC_HZ							16000000
#define FRC_DIV							1
#define CLK_US              500                     //100us
#define TIME_RELOAD        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US/1000))   //���ȸ���

unsigned int idata l_value = 0;
bit b_10ms_flag;
/******************************************************************************************
** ��������: timer0_init
** ��������: time0��ʼ������   
** �������: ��
** �������: �� 
*******************************************************************************************/
void timer0_init()
{
	TMOD = (TMOD & ~ 0x03) | 0x01;       							// Timer0ģʽѡ��  0: 8λ��ʱ��/��������TH0�� ��5λԤ��Ƶ����TL0��1:16λ��ʱ��/������ 
	                                                                 // 2:8λ�Զ����ض�ʱ��/��������TL0�� 3:TL0��һ��8λ��ʱ��/��������TH0 ��һ��8λ��ʱ��/������                     

	TH0 = (TIME_RELOAD) / 256;                                     // 100US
	TL0 = (TIME_RELOAD) % 256;

	TR0 = 1;                                                       // TIMER0 ����
	ET0 = 1;                                                        //����TIMER0�ж�
	PT0 = 1;
	IPH = (IPH&0XFD)|0X02;

}

void timer0_Stop()
{
	TMOD = 0;       							// Timer0ģʽѡ��  0: 8λ��ʱ��/��������TH0�� ��5λԤ��Ƶ����TL0��1:16λ��ʱ��/������ 
	                                                                 // 2:8λ�Զ����ض�ʱ��/��������TL0�� 3:TL0��һ��8λ��ʱ��/��������TH0 ��һ��8λ��ʱ��/������                     

	TH0 = 0;                                     // 100US
	TL0 = 0;

	TR0 = 0;                                                       // TIMER0 ����
	ET0 = 0;                                                       //����TIMER0�ж�
 

}
/******************************************************************************************
** ��������: timer0_int
** ��������: time0�жϴ�����
** �������: ��
** �������: �� 
*******************************************************************************************/
void timer0_irq(void) interrupt 1
{
    static unsigned char T2 = 0, T1 = 0;

    TH0 = (u8)(TIME_RELOAD >> 8);
    TL0 = (u8)(TIME_RELOAD & 0xFF);

    /*============================ �� ʪ�Ȳ��� ============================*/
    if (hum_run == 1)
    {
        /* ÿ 250 ��s ��ת�������� */
			
			
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
						 hum_acc += (((ADCDH << 4) & 0xFF0) | (ADCDL >> 4));      /* ��ѡ�� ADC9      */
            if (++hum_cnt >= 10) {           /* �� 10 ����       */
							  hum_acc = hum_acc / 10;
                hum_run   = 2;               /* ��������         */

                /* �� IO ���ͣ��ͷ� ADC ���¶� */
                P15 = 0; P17 = 0;
            }
						hum_phase = 0;
					break;
				}
    }

    /*============================ �� ԭ�� 100 ��s/10 ms ���� ===============*/
    Nixie_Loop();

    if (l_value) l_value--;
    if (++T1 < 4) return;                   /* 250 ��s ��4 = 1 ms */
    T1 = 0;

    if (AdDet1MS)  AdDet1MS--;
    if (!B_KeySCAN) B_KeySCAN = 1;
    if (R_KeyHoldTimer) R_KeyHoldTimer--;

    if (++T2 >= 10) {                       /* 1 ms ��10 = 10 ms */
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