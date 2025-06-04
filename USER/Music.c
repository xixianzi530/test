
#include "include.h"




bit Music_en;
unsigned char idata R_SendCnt ;
unsigned char idata R_SendState ;
unsigned char idata SendData ;



// ��ʱ��1��ʼ������
void timer1_init(void)
{
	TMOD = (TMOD & ~ 0X30) | (1 << 4);       // Timer1ģʽѡ�� 16λ��ʱ��  0��8 λ��ʱ��/������(TH1)�� 5 λԤ��Ƶ��(TL1)��       1��16 λ��ʱ��/�������� 
	                                         // 2��8 λ�Զ����ض�ʱ��/������(TL1) ��            3��Timer1 ֹͣ                	      

	TH1 = TIME_5000US_CHUFA;                                       // 100US
	TL1 = TIME_5000US_YUQU;										 //
																	  						
	TR1 = 1;                                                         // TIMER1 ���� 
	ET1 = 1;                                                         // TIMER1ʹ��
//	PT1 = 1;
	
	P0MOD76=0x61;		//DC+DATA
	P07 = 1;
}

void timer1_Stop()
{
              
	TMOD = 0;       							// Timer0ģʽѡ��  0: 8λ��ʱ��/��������TH0�� ��5λԤ��Ƶ����TL0��1:16λ��ʱ��/������ 
	                                                                 // 2:8λ�Զ����ض�ʱ��/��������TL0�� 3:TL0��һ��8λ��ʱ��/��������TH0 ��һ��8λ��ʱ��/������                     

	TH1 = 0;                                     // 100US
	TL1 = 0;
		
	TR1 = 0;                                                       // TIMER0 ����
	ET1 = 0;                                                       //����TIMER0�ж�

}
// ��ʱ��1�жϷ������
void timer1_int() interrupt 3
{
    if (!Music_en)
    {
        TH1 = (TIME_5000US_CHUFA);
        TL1 = (TIME_5000US_YUQU) ;
	
        R_SendState = 0;
        R_SendCnt = 0;
        P07 = 0;                  
        return;
    }
    Send_MusicData();               // ���Music_enΪ1��������������
}

// �����������ݺ���
void Send_MusicData(void)
{
    switch (R_SendState)
    {
        case 0: // ���͵͵�ƽ�źţ�����9ms
            TH1 = (TIME_5000US_CHUFA);
            TL1 = (TIME_5000US_YUQU) ;
            P07 = 1;           
            R_SendState = 1;
            R_SendCnt = 0;
            break;
        case 1:
            P07 = 0;             
            if (SendData & 0x01)
            {
                TH1 = (TIME_500US_CHUFA);
                TL1 = (TIME_500US_YUQU) ;
            }
            else
            {
                TH1 = (TIME_1500US_CHUFA);
                TL1 = (TIME_1500US_YUQU) ;
            }
            R_SendState = 2;
            break;
        case 2:
            P07 = 1;             
            if (SendData & 0x01)
            {
                TH1 = (TIME_1500US_CHUFA);
                TL1 = (TIME_1500US_YUQU) ;
            }
            else
            {
                TH1 = (TIME_500US_CHUFA);
                TL1 = (TIME_500US_YUQU) ;
            }
            R_SendState = 1;
            R_SendCnt++;
            SendData >>= 1;         // ������������һλ
            if (R_SendCnt == 8) R_SendState = 3;
            break;
        case 3:
            TH1 = (TIME_5000US_CHUFA);;
            TL1 = (TIME_5000US_YUQU) ;
            P07 = 0;             
            Music_en = 0;          // �ر����ַ���
            R_SendState = 0;       // ���÷���״̬
            break;
    }
}

void Play_Music(uint8 index)
{					
					while(Music_en);					
					R_SendState=0;
					R_SendCnt=0;
					Music_en=1;
					SendData=index;
}//0x06 0x17 0x28



/* ���������������������������������������������� �궨�� ���������������������������������������������� */

#define MUSIC_CMD_PLAY_INT     0xFB    /* �ɴ�ϲ��� */
#define MUSIC_CMD_STOP         0xFF    /* ֹͣ+���� */
#define MUSIC_CMD_LOOP         0xD2    /* ѭ������(������Э��) */



void Music_Config(void)
{
    Play_Music(0XF5);   							/* �����е����� */
    Play_Music(MUSIC_CMD_PLAY_INT);   /* �ٷ��������� */
}
void Play_Music_Size(unsigned char r_size)
{
	code unsigned char size_table[]={0,3,7};

  Play_Music(0xf0+size_table[r_size]);   							/* �����е����� */
	
}

/* ���������������������������������������������� ��Ŀ��� ���������������������������������������������� */
/* ����ָ����Ŀ���ɱ���ϣ� */
//void Music_Play(uint8_t track)
//{
//    Play_Music(track);          /* �� �ȷ���Ŀ�� */
//}

/* ѭ�����ţ�Э��Ҫ����Ŀ �� 10?ms ��ʱ �� 0xD2�� */
void Music_PlayLoop(uint8_t track)
{
    Play_Music(track);
    delay_ms(10);                 /* ��10?ms���Լ�ʵ�ֻ���ϵͳ��ʱ */
    Play_Music(MUSIC_CMD_LOOP);     /* 0xD2 */
}

/* ֹͣ���ţ��������� */
void Music_Stop(void)
{
    Play_Music(MUSIC_CMD_STOP);     /* 0xFF */
}

