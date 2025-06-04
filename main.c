/*
****************************************************************************************************
* @file    main.c
* @brief   main Source File.
*
* @version V1.0.0
* @author  wangjiajun
* @date    2024/04/26
*
* Copyright (C) XSHX (ShenZhen) Technology Co., Ltd
****************************************************************************************************
*/
#include 	"include.h"
/*
***************************************************************************************************/
/*
1.����ʱ���棬�趨��ʱ��󣬿�������ʱ���̰�������ǿ���˳��󣨶̰����ü�Ҳ�ǣ��̰����Ӽ�Ҳ�ǣ����´ν���ָ��ɵ���ʱǮ��ʱ�䣬�����������´ν��벻�ָ���
2.��������ʱ����������2min
*/

bit power_off=1;
void Stop(void);

void main(void)
{	
// //���оƬ�ϵ�һ��Ҫ�ȳ�ʼ��һ��RTC����Ȼ�ܴ���ܻ��ܲ�����
	P2MOD10=0x00;
	P20=1;
	P21=1;
	OPTION =(OPTION &~0x03);
//	OPTION = OPTION|0x00;	//TM3CKS:Timer3 ?????0:??? (SXT/SRC)	1:FRC/512 (31.25 KHz)
//	bsp_SXT_clock_init();
//		SELFCK = 0;	         //�л�����ʱ��
	
//	CLKCON = 0x02;       //ʱ�Ӷ���Ƶ 
	CLKCON = 0x03;       //ʱ��һ��Ƶ
	STPPCK = 0;			 //������ʱ��
	STPFCK = 0;			 //��������ģ��ʹ�ÿ�ʱ��
	SELFCK = 1;			 //�л�����ʱ��
  SCKTYPE = 1;           //SXT
	SELFCK = 0;	         //�л�����ʱ��
//	bsp_clock_init();
	SELFCK = 0;	         //�л�����ʱ��
		
//	CLKCON = 0x02;       //ʱ�Ӷ���Ƶ
	
//	STPPCK = 0;			 //��������ģ��ʹ�ÿ�ʱ��
//	STPFCK = 0;			 //������ʱ��
	SELFCK = 1;			 //�л�����ʱ��
	/************RTC*************/
//	tim3_init();
	INTFLAG=0;				//��������ж�����
	TM3RLD=0xF0;			//16 λ Timer3 �� 8 λ��������
	INTE1= INTE1 | 0x01;	//ʹ�� Timer3 �ж�
	IE= IE|0x80;			//:���ж�ʹ�ܿ���
	
	
	P12 = 1;
	P10 = 1;
	
	/********��ʱ����ʼ��*********/
	timer0_init();//������ʱ��
	timer1_init();//������
	

	/********�¶ȳ�ʼ��*********/
	adc_init();
	/********5020��ʼ��***********/
	Nixie_config();
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

//	R_DisData = 0x0000;
//	Write_2025_Command();                      /* ȫ����һ�� */

	
	/********������ʼ��***********/
//	Sol_Key_Init();
	key_Init();
	/********���ݳ�ʼ��***********/
	ShowData_Init_UpData();
	
	
	/*********DC���***********/
//	P0MOD76 = �Ѿ��������Ǳ߽�����IO��ʼ��
	
	/*********���ؼ��***********/
	P0MOD10 = (P0MOD10&0XF0)|0X06;
	P00 = 0;
	P3MOD54 = (P3MOD54&0X0F)|0X90;
	
	while(1)
	{
//		Stop();
		Key_Scan();
		State_Ctrl();
		Encoder_Task();
		Half_Second();
		Ad_Det();
	}	
}   

void Stop(void)
{
//	if(B_PowerLock == 2||B_PowerLock == 3)goto jinru;
//	if(P06||Alerm_ON[0]||Alerm_ON[1]||Alerm_ON[2] || !Night_Mode || Timer_Alarm_On || B_Counting)
//	{
//		AutoStop_Time = 15;
//		return;
//	}
//	if(AutoStop_Time)return;
//	jinru:
//	Music_Stop();
//	R_KeyHoldTimer = 200;
//	while(R_KeyHoldTimer);
//	timer0_Stop();
//	power_off= 0;
////	timer1_Stop();
//	//5020
//	P32 = 1;//5020��Դ��
////	
//	P13 = 0;
//	P12 = 0;
//	P10 = 0;
//	PWM0_Duty(100,0);
//	
//	
//	//����
//	P16 = 1;
//	
//	Night_Mode_Time = 120;
//	Stop_rouse = 100;
//	PowerOffCnt =0;
//	while(1)
//	{
//	
//		STPSCK = 0;       //ֹͣ����
//		AUX2 = (AUX2 & ~0x20) | (1 << 5); //PWRSAV��һ����һ�����͹���
//		PCON = (PCON & ~0x02) | (1 << 1); //ֹͣλ,��� 1 ����ֹͣģʽ��
//	//����ֹͣģʽ
//	//�˳�ֹͣģʽ
//		AUX2 = (AUX2 & ~ 0x20) | (0 << 5); //   pwrsav = 0��
//		STPSCK = 0;       //���Ӵ�
//		
//		Half_Second();
//		if(B_PowerLock==0||B_PowerLock==1)
//		{
//			if(Stop_rouse<50)goto huanx;
//			if(!P14)break;
//			if(!P15)break;
//			if(!P37)break;
//			if(P11)break;
//			if(!P35)goto huanx;
//			
//		}
//		else if(B_PowerLock == 2)
//		{
//			Stop_rouse = 100;
//			P00 = 1;//���عر�����
//		}
//		else
//		{ 
//			P00 = 1;//���عر�����
//			Stop_rouse = 100;
//			if((!P14) && (!P15))
//			{
//				++PowerOffCnt;
//				if (PowerOffCnt >= 16)
//				{
//					PowerOffCnt =0;
//					B_PowerLock = 0;
//					break;
//				}
//			}
//			else
//			{
//				PowerOffCnt = 0;
//			}
//		}
//		if(P06)break;
//	}
//	
////		Bit_KeyReles=0;
////	Bit_KeyPress=1;	
//	huanx:
//	B_PowerLock = 0;
//		//5020
//	
//	P12 = 1;
//	P10 = 1;
//	P32 = 0;//5020��Դ��

//	
////	P13 = 0;
//	//����
//	P16 = 0;
//	P00 = 0;//����
////	timer1_init();
//	timer0_init();
//	Servant_Page_State = 0;
//	Dis_FlashMenu();
//	Light_adj_fun(Brightness_level);
//	AutoStop_Time = 15;
//	if(Stop_rouse<50)
//	{
//		ON_Music(Stop_rouse);
//		Stop_rouse = 100;
//	}

}
