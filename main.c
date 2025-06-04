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
1.倒计时界面，设定好时间后，开启倒计时，短按编码器强制退出后（短按设置键也是，短按闹钟键也是），下次进入恢复成倒计时钱的时间，长按编码器下次进入不恢复。
2.样机倒计时结束后响闹2min
*/

bit power_off=1;
void Stop(void);

void main(void)
{	
// //这个芯片上电一定要先初始化一下RTC，不然很大可能会跑不起来
	P2MOD10=0x00;
	P20=1;
	P21=1;
	OPTION =(OPTION &~0x03);
//	OPTION = OPTION|0x00;	//TM3CKS:Timer3 ?????0:??? (SXT/SRC)	1:FRC/512 (31.25 KHz)
//	bsp_SXT_clock_init();
//		SELFCK = 0;	         //切换到慢时钟
	
//	CLKCON = 0x02;       //时钟二分频 
	CLKCON = 0x03;       //时钟一分频
	STPPCK = 0;			 //开启快时钟
	STPFCK = 0;			 //开启部分模块使用快时钟
	SELFCK = 1;			 //切换到快时钟
  SCKTYPE = 1;           //SXT
	SELFCK = 0;	         //切换到慢时钟
//	bsp_clock_init();
	SELFCK = 0;	         //切换到慢时钟
		
//	CLKCON = 0x02;       //时钟二分频
	
//	STPPCK = 0;			 //开启部分模块使用快时钟
//	STPFCK = 0;			 //开启快时钟
	SELFCK = 1;			 //切换到快时钟
	/************RTC*************/
//	tim3_init();
	INTFLAG=0;				//清除所有中断向量
	TM3RLD=0xF0;			//16 位 Timer3 高 8 位重载数据
	INTE1= INTE1 | 0x01;	//使能 Timer3 中断
	IE= IE|0x80;			//:总中断使能控制
	
	
	P12 = 1;
	P10 = 1;
	
	/********定时器初始化*********/
	timer0_init();//正常计时用
	timer1_init();//语音用
	

	/********温度初始化*********/
	adc_init();
	/********5020初始化***********/
	Nixie_config();
/* 5020 供电 IO: P3.2 → 推挽输出 */
	P3MOD32 = (P3MOD32 & 0xF0) | 0x06;
	P32     = 0;                               /* 低电平使能 */

	/* PWM0 调光 */
	PWM0_init(PWMIE_off, CKS_SYS);
	PWM0_Duty(100, 0);                         /* 默认最亮 */
	PWM_Enable(PWM_0);

	/* ICN2025 数据 / 时钟 / LATCH IO */
	P1MOD32 = 0x66;                            /* P1.2 / P1.3 */
	P1MOD10 = (P1MOD10 & 0xF0) | 0x06;         /* P1.0 */

//	R_DisData = 0x0000;
//	Write_2025_Command();                      /* 全消隐一次 */

	
	/********按键初始化***********/
//	Sol_Key_Init();
	key_Init();
	/********数据初始化***********/
	ShowData_Init_UpData();
	
	
	/*********DC检测***********/
//	P0MOD76 = 已经在语音那边进行了IO初始化
	
	/*********声控检测***********/
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
//	P32 = 1;//5020电源关
////	
//	P13 = 0;
//	P12 = 0;
//	P10 = 0;
//	PWM0_Duty(100,0);
//	
//	
//	//测温
//	P16 = 1;
//	
//	Night_Mode_Time = 120;
//	Stop_rouse = 100;
//	PowerOffCnt =0;
//	while(1)
//	{
//	
//		STPSCK = 0;       //停止慢钟
//		AUX2 = (AUX2 & ~0x20) | (1 << 5); //PWRSAV置一，进一步降低功耗
//		PCON = (PCON & ~0x02) | (1 << 1); //停止位,如果 1 进入停止模式。
//	//进入停止模式
//	//退出停止模式
//		AUX2 = (AUX2 & ~ 0x20) | (0 << 5); //   pwrsav = 0；
//		STPSCK = 0;       //慢钟打开
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
//			P00 = 1;//声控关闭声控
//		}
//		else
//		{ 
//			P00 = 1;//声控关闭声控
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
//	P32 = 0;//5020电源关

//	
////	P13 = 0;
//	//测温
//	P16 = 0;
//	P00 = 0;//声控
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
