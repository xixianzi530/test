#ifndef _adc_h_
#define _adc_h_
extern unsigned char          hum_run  ;   /* 1 = ���ڲ�ʪ�� */
extern unsigned char          hum_phase;   /* 0/1 ��������λ */
extern unsigned int hum_acc  ;   /* ADC �ۼ�       */
extern unsigned char hum_cnt ;   /* ���ۻ�������   */


extern unsigned int humidity ;
extern unsigned char  B_PowerLock ;
extern  unsigned char Brightness_Max ;
extern char temperature ;
extern idata unsigned char AdDet1MS;
void Ad_Det(void);
void adc_init(void);
unsigned int adc_get_value(void)   ;

u16 Trana(s16 Tem,u16 HumAD);
#endif