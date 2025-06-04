/*��������������������������������������������������������������������������������������������������
 * File : Nixie.c   (C51 / ICN2025 / 9��7 �� LED)
 * Author: ChatGPT (o3)
 * Update: 2025-05-15
 *������������������������������������������������������������������������������������������������*/

#include "include.h"

/*===== ������������������ λ���γ��� ������������������ =====*/
#define OUT_COM_1  0x0400  /* OUT7  */
#define OUT_COM_2  0x0200  /* OUT8  */
#define OUT_COM_3  0x0100
#define OUT_COM_4  0x0800
#define OUT_COM_5  0x1000
#define OUT_COM_6  0x2000
#define OUT_COM_7  0x4000

#define OUT2_COM_1  0X0200  /* OUT7  */
#define OUT2_COM_2  0x0100  /* OUT8  */
#define OUT2_COM_3  0x4000
#define OUT2_COM_4  0x2000
#define OUT2_COM_5  0x0800
#define OUT2_COM_6  0x0400
#define OUT2_COM_7  0x1000


#define SEG_A  0x01u    /* OUT0  */
#define SEG_B  0x02u
#define SEG_C  0x04u
#define SEG_D  0x08u
#define SEG_E  0x10u
#define SEG_F  0x20u
#define SEG_G  0x40u


/********************************************************/

#define OUT1_COM_1  0x8000  /* OUT7  */
#define OUT1_COM_2  0x0008  /* OUT8  */
#define OUT1_COM_3  0x0040
#define OUT1_COM_4  0x0020
#define OUT1_COM_5  0x0010
#define OUT1_COM_6  0x0004
#define OUT1_COM_7  0x0002

#define SEG1_A  0x0100u    /* OUT0  */
#define SEG1_B  0x0200u
#define SEG1_C  0x0400u
#define SEG1_D  0x0800u
#define SEG1_E  0x1000u
#define SEG1_F  0x2000u
#define SEG1_G  0x4000u

/*===== ������������������ ���� + ���Ŷ���� (1=��) ������������������ =====*/
code uint8_t sSegMap[] = {
    SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F,             /* 0 */
    SEG_B|SEG_C,                                     /* 1 */
    SEG_A|SEG_B|SEG_D|SEG_E|SEG_G,                  /* 2 */
    SEG_A|SEG_B|SEG_C|SEG_D|SEG_G,                  /* 3 */
    SEG_B|SEG_C|SEG_F|SEG_G,                        /* 4 */
    SEG_A|SEG_C|SEG_D|SEG_F|SEG_G,                  /* 5 */
    SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,            /* 6 */
    SEG_A|SEG_B|SEG_C,                              /* 7 */
    SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,      /* 8 */
    SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G,            /* 9 */
    0x00,                                           /* ȫ�� */
    SEG_A|SEG_D|SEG_E|SEG_F,                        /* ��C */
    SEG_A|SEG_E|SEG_F|SEG_G,                        /* ��F */
    SEG_C|SEG_D|SEG_E|SEG_G,                        /* o */
    SEG_A|SEG_B|SEG_C|SEG_E|SEG_F,                  /* �� */
    SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G,            /* A */
    SEG_D|SEG_E|SEG_F,                              /* L */
    SEG_A|SEG_E|SEG_F|SEG_G,                        /* F */
    SEG_B|SEG_C|SEG_E|SEG_F|SEG_G,                  /* H */
    SEG_B|SEG_C|SEG_D|SEG_E|SEG_G,                  /* d */
    SEG_B|SEG_C|SEG_D|SEG_E|SEG_F,                  /* U */
    SEG_E|SEG_G,                                    /* �� */
    SEG_A|SEG_B|SEG_E|SEG_F|SEG_G,                  /* P */
};
code uint16_t s1SegMap[] = {
    SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_F,             /* 0 */
    SEG1_B|SEG1_C,                                     /* 1 */
    SEG1_A|SEG1_B|SEG1_D|SEG1_E|SEG1_G,                  /* 2 */
    SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_G,                  /* 3 */
    SEG1_B|SEG1_C|SEG1_F|SEG1_G,                        /* 4 */
    SEG1_A|SEG1_C|SEG1_D|SEG1_F|SEG1_G,                  /* 5 */
    SEG1_A|SEG1_C|SEG1_D|SEG1_E|SEG1_F|SEG1_G,            /* 6 */
    SEG1_A|SEG1_B|SEG1_C,   		          	           /* 7 */
    SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_F|SEG1_G,      /* 8 */
    SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_F|SEG1_G,            /* 9 */
    0x00,                                           /* ȫ�� */
    SEG1_A|SEG1_D|SEG1_E|SEG1_F,                        /* ��C */
    SEG1_A|SEG1_E|SEG1_F|SEG1_G,                        /* ��F */
    SEG1_C|SEG1_D|SEG1_E|SEG1_G,                        /* o */
    SEG1_A|SEG1_B|SEG1_C|SEG1_E|SEG1_F,                  /* �� */
    SEG1_A|SEG1_B|SEG1_C|SEG1_E|SEG1_F|SEG1_G,            /* A */
    SEG1_D|SEG1_E|SEG1_F,                             /* L */
    SEG1_A|SEG1_E|SEG1_F|SEG1_G,                        /* F */
    SEG1_B|SEG1_C|SEG1_E|SEG1_F|SEG1_G,                  /* H */
    SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_G,                  /* d */
    SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_F,                  /* U */
    SEG1_E|SEG1_G,                                   /* �� */
    SEG1_A|SEG1_B|SEG1_E|SEG1_F|SEG1_G,                  /* P */
};
code uint8_t WEEK_TABLE[] = {

	SEG_A ,//����1
	SEG_B ,//����2
	SEG_C ,//����3
	SEG_D ,//����4
	SEG_E ,//����5
	SEG_F ,//����6
	SEG_G ,//����7
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_E, 							//��һ������
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F, 				//��һ������
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,	//��һ������
	0x00,	//��һ������
	
	
	
};




/*===== ������������������ �ⲿӲ�������� ������������������ =====*/
void Write_2025_Command(void);
void Send_2025Data(void);

unsigned char Brightness_level;
unsigned int idata R_DisData       ;
unsigned int  R_DisData1       ;
unsigned int  R_DisData2       ;
unsigned int  R_DisData3       ;
/*===== ������������������ PWM & IO ��ʼ�� ������������������ =====*/
void Nixie_config(void)
{
    /* 5020 ���� IO: P3.2 �� ������� */
    P3MOD32 = (P3MOD32 & 0xF0) | 0x06;
    P32     = 0;                               /* �͵�ƽʹ�� */

    /* PWM0 ���� */
    PWM0_init(PWMIE_off, CKS_SYS);
    PWM0_Duty(100, 0);                         /* Ĭ������ */
    PWM_Enable(PWM_0);

    /* ICN2025 ���� / ʱ�� / LATCH IO */
    P1MOD32 = 0x66;                            /* P1.2 / P1.3 */
    P1MOD10 = (P1MOD10 & 0xF0) | 0x06;         /* P1.0 */

}

/*===== ������������������ ���ȼ��� �� PWM ռ�� =====*/
void Light_adj_fun(unsigned char idx)
{
    code uint8_t table[] = { 90, 70, 40, 0 };  /* ԽСԽ�� */
    PWM0_Duty(100, table[idx]);
}

/*===== ������������������ ICN2025 д 16bit ���� ������������������ */
void Write_2025_Command(void)
{
	unsigned char i = 0;
    ICN2025_LE_CLR();
		R_DisData = R_DisData3;
    Send_2025Data();
		R_DisData = R_DisData2;
    Send_2025Data();
		R_DisData = R_DisData1;
    Send_2025Data();
    ICN2025_LE_SET();
    ICN2025_LE_CLR();
}

void Send_2025Data(void)
{
    uint8_t i;
    for (i = 0; i < 16; ++i) {
        ICN2025_CLK_CLR();
        if (R_DisData & 0x8000)
				{
					ICN2025_SDA3_SET();
        }
					else
					{						
					ICN2025_SDA3_CLR();
					} 
						R_DisData <<= 1;
        ICN2025_CLK_SET();
    }
    ICN2025_CLK_CLR();
}
		


//����0��ʱ��IOΪ���裬����1��ʱ��IO����,��λ��Ӧ��IO��λ���ͱ���0X8000��Ӧ�� IO15
/*===== ������������������ ��ɨ�躯�� ������������������*/
void Nixie_Scan(uint8_t loc)
{  
	
	switch(loc)
	{
		case 0:
			R_DisData1 = OUT_COM_1 | sSegMap[Hour_Hig] | OUT1_COM_1;//COM1
		/********************************************************/
			R_DisData3 = OUT2_COM_1 | sSegMap[Al_Min_Hig];
		/********************************************************/
			R_DisData2 = s1SegMap[Sec_Low];
		
		break;
		break;
		case 2:
			R_DisData1 = OUT_COM_2 | sSegMap[Hour_Low];//COM2
		/********************************************************/
			R_DisData3 = OUT2_COM_2 | sSegMap[Al_Min_Low];
		/********************************************************/
			R_DisData2 = OUT1_COM_2 | ((unsigned char)(Option_Point) << 8) | ((unsigned char)(Month_Hig) << 9) | 
							   	((unsigned char)(Month_Hig) << 10) | ((unsigned char)(M_Point) << 11) | 
									((unsigned char)(D_Point) << 12) | ((unsigned char)(AlarmPoint1) << 13) | ((unsigned char)(AlarmPoint2) << 14);
		break;
		break;
		case 4:
			R_DisData1 = OUT_COM_3 | sSegMap[Min_Hig];//COM3
		/********************************************************/
			R_DisData3 = OUT2_COM_3 | sSegMap[Temp_Hig];
		/********************************************************/
			R_DisData2 = OUT1_COM_3 | s1SegMap[Month_Low];
		break;
		break;
		case 6:
			R_DisData1 = OUT_COM_4 | sSegMap[Min_Low];//COM4
		/********************************************************/
			R_DisData3 = OUT2_COM_4 | sSegMap[Temp_Low];
		/********************************************************/
			R_DisData2 = OUT1_COM_4 | s1SegMap[Day_Hig];
		break;
		break;
		case 8:
			R_DisData1 = OUT_COM_5 | AmPoint | ((unsigned char)(PmPoint)<<1) | ((unsigned char)(TIMER_Point)<<2) | 
									 ((unsigned char)(SleepPoint)<<3) | ((unsigned char)(SecPoint) <<4 )| 
										((unsigned char)(COL2_Point)  <<5) | ((unsigned char)(BAT_Point) <<6);//COM1
		/********************************************************/
			R_DisData3 = OUT2_COM_5 | sSegMap[Hum_Hig];
		/********************************************************/
			R_DisData2 = OUT1_COM_5 | s1SegMap[Day_Low];
	
		break;
		break;
		case 10:
			R_DisData1 = OUT_COM_6 | WEEK_TABLE[Well_s];//COM1
		/********************************************************/
			R_DisData3 = OUT2_COM_6 | sSegMap[Hum_Low];
		/********************************************************/
			R_DisData2 = OUT1_COM_6 | s1SegMap[Al_Hour_Hig];
		break;
		break;
		case 12:
			R_DisData1 = OUT_COM_7 | sSegMap[Sec_Hig];//COM5
		/********************************************************/
			R_DisData3 = OUT2_COM_7 | AlarmPoint3 | ((unsigned char)(COL3_Point) << 1) | ((unsigned char)(Hum_Point) << 2) | 
								   ((unsigned char)(C_Point) << 3) | ((unsigned char)(Temp_Point) << 4) | 
									 ((unsigned char)(BaiFenHao_Point) << 5);
		/********************************************************/
			R_DisData2 = OUT1_COM_7 | s1SegMap[Al_Hour_Low];
		break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		case 13:
				R_DisData1 = 0x0000;
				R_DisData2 = 0x0000;
				R_DisData3 = 0x0000;
		break;
	}
    Write_2025_Command();                      /* �������� */
}

/*===== ������������������ 1 kHz ��ʱ���ж���ѯ ������������������*/
void Nixie_Loop(void)
{
    static uint8_t i = 0;
    Nixie_Scan(i);
    if (++i > 13) i = 0;
}

/*��������������������������������������������������������������������������������������������������
 * �����������һ���ü����ɽ� Pack_COMx д�ɺ꣬
 * �򳹵ײ����֮ǰ������ A������Ч�������ޡ�
 *������������������������������������������������������������������������������������������������*/
