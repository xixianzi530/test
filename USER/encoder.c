#include "include.h"

#define PINA    P04
#define PINB    P34


/* �ϲ������������ⲿ�Ѷ��壩 */
bit     encoder_cnt_en;
uint8   encider_direction;        /* DOWN / UP */

/*�������������������������������������� ״̬���� ��������������������������������������*/
static uint8  enc_prev ;      /* ��һ�� A/B ��ϣ�0~3   */
static char   enc_acc  ;      /* һ��λһ�����ۼ���    */
static bit    EncType  ;      /* 0=һ��λһ���� 1=����λ */

/* 4��4 ���� �� ������+1=�� -1=�� 0=��Ч           */
static const char code enc_tbl[16] = {
/* prev<<2 | now ��      00  01  10  11 (now) */
 /* 00 */                0, +1, -1,  0,
 /* 01 */               -1,  0,  0, +1,
 /* 10 */               +1,  0,  0, -1,
 /* 11 */                0, -1, +1,  0
};

/*�������������������������������������� ��ʼ�� ��������������������������������������*/
void Encoder_Init(void)
{
    P0MOD54 = (P0MOD54&0xf0)|0x01;   /* P0.5 / P0.4 ��Ϊ���� */
    P3MOD54 = (P3MOD54&0xf0)|0x01;   /* P0.5 / P0.4 ��Ϊ���� */
    P3MOD76 = (P3MOD76&0x0f);   /* P0.5 / P0.4 ��Ϊ���� */
    enc_prev = (PINA ? 2 : 0) | (PINB ? 1 : 0);
}

/*�������������������������������������� ɨ�躯������ѯ�� 1 ms ���ڵ��� ��������������������������������������*/
/* ���� ÿ��ת 2 ��(���ο�λ) �ŷ���һ�� ��1 ���� */
static char Encoder_Scan(void)          /* return: -1 / 0 / +1 */
{
    uint8 now  = (PINA ? 2 : 0) | (PINB ? 1 : 0);
    char  step = enc_tbl[(enc_prev << 2) | now];   /* �������䣺��1 / 0 */
    enc_prev   = now;

    if (!step) return 0;            /* ������ */

    enc_acc += step;                /* �ۼӷ�Χ���� -4..+4 */

    /* �ص��ȶ�̬(00 �� 11) �����ۻ�����(��4) �� ���һ�� ��1 */
    if ((now == 0 || now == 3) && (enc_acc == 4 || enc_acc == -4)) {
        step    = enc_acc >> 2;     /* ��1 */
        enc_acc = 0;                /* ���¼��� */
        return step;                /* ���� ÿ 2 �񴥷�һ�� ���� */
    }
    return 0;                       /* δ�� 2 �� */
}





/*�������������������������������������� �������� ��������������������������������������*/
static void Encoder_Do(char dir)         /* dir = ��1 */
{
    encider_direction = (dir > 0) ? UP : DOWN;
	AutoSave_Time = 0;
	AutoStop_Time = 15;
	switch(Servant_Page_State)
	{
		case Time_UI:
		case Alarm_UI:
		case Alarm_UI_1:
		case Alarm_UI_2:
			
		case Ajust_Music_SIZE_UI:
				
				Servant_Page_State = Ajust_Music_SIZE_UI;
		break;
	}
    Get_Add_Action();
}
/*�������������������������������������� ������ڣ���ѭ�����ã� ��������������������������������������*/
void Encoder_Task(void)
{
	char s ;
    if (encoder_cnt_en) return;
   s = Encoder_Scan();
    if      (s > 0) Encoder_Do(-1);
    else if (s < 0) Encoder_Do(+1);
}
/*�������������������������������������� ������� ��������������������������������������*/


