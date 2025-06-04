#ifndef _ADC_C_
#define _ADC_C_

#include "include.h"

/* ── 电压阈值(ADC 原码) ─────────────────────────── */
#define ADC_TH_3V50   3050u
#define ADC_TH_3V30   2850 //2650u//2850

/* ── 新的状态变量 ──────────────────────────────── */
unsigned char  B_PowerLock ;   /* 1=已锁死 */
unsigned char Brightness_Max = 3;  /* 0~3 → 4 档；锁死或低压会下调 */

/* -------- 湿度子状态机 -------- */
unsigned char          hum_run  = 0;   /* 1 = 正在采湿度 */
unsigned char          hum_phase= 0;   /* 0/1 半周期相位 */
unsigned int hum_acc  = 0;   /* ADC 累加       */
unsigned char hum_cnt = 0;   /* 已累积样本数   */


char temperature ;
unsigned int humidity ;
code unsigned int Temp_Table[];
static  unsigned char R_ADState;
static  unsigned char R_ADCnt;
static  unsigned int R_ReadData[10];
static  unsigned int adc_value;
static  unsigned char ch_index;
idata unsigned char AdDet1MS;
void Battery_Vol_Check(void);
u16 Trana(s16 Tem,u16 HumAD);
/* 初始化 ADC 并清空采样缓冲 */
void adc_init(void) {
    OPTION   = (OPTION & 0xF3) | ADCKS_sys_32;
    ADCHSEL  = (ADCHSEL & ~0x08) | ADCVREFS_0;
	
/**********************************************/
		//测温电路
    P1MOD54  = 0x63;		//(P15输出.湿度)  P14 ADC
		P15 = 0;
    P1MOD76  = 0x66;		//(P17输出.湿度和温度复用口)  P16 输出
    P17      = 0;  // 使能测温电源
    P16      = 1;  // 使能测温地
/**********************************************/
	
    AdDet1MS = 0;
    R_ADState = 0;
    R_ADCnt   = 0;
	
    P0MOD54 = (P0MOD54&0x0f);   /* P0.5 检测充电是否充满  充满后4056高阻态，IO拉高 */
}

unsigned int adc_get_value(void)            
{                             
	unsigned int idata adc_temp = 0;
	unsigned int idata temph=0;
	unsigned int idata templ=0;
	
	ADCHSEL = (ADCHSEL & ~0xF8)| (ADC_CH9 << 3);            // ADC ??????
	
	ADSOC = 1;                            // ADC???????     
    while(ADSOC);
	
	templ = ADCDL;
	temph = ADCDH; 
	
	adc_temp  = (temph<<4) &0xff0;
	adc_temp  |= (templ>>4);
	return adc_temp ;	
}

/* 每 1ms 调用一次，用于驱动 ADC 采样并在 10 次后求平均 */
void Ad_Det(void) {
		unsigned char i ;
    if (AdDet1MS) return;
		AdDet1MS = 2;
	
    switch (R_ADState) {
    case 0:
				ch_index++;
				if(ch_index >2)ch_index = 0;
				if(!ch_index)
				{
					
					ADCHSEL = (ADCHSEL & ~0x04) | (ADCVREFS_0);			//  参考电压选择VCC				
					ADCHSEL = (ADCHSEL & ~0xF8) | (ADC_CH9 << 3);
					P1MOD54  = 0x63;		//(P15输出.湿度)  P14 ADC
					P15 = 0;
					P1MOD76  = 0x66;		//(P17输出.湿度和温度复用口)  P16 输出
					P17      = 0;  // 使能测温地
					P16      = 1;  // 使能测温电源
					
					
				}
				else if(ch_index==1)
				{
						P1MOD54  = 0x63;		//(P15输出.湿度)  P14 ADC
						P15 = 0;
						P1MOD76  = 0x61;		//(P17输出.湿度和温度复用口)  P16 输出
						P17      = 0;  // 使能测温地
						P16      = 0;  // 关闭测温电源
					
				}
        ADSOC    = 1;
        R_ADState = 1;
        break;
		
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (ADSOC) break;
        ADSOC = 0;
        R_ADState++;
				if(ch_index==1 && R_ADState == 7)
				{
					/* ---------- 温度 1 帧结束后，切到湿度 ---------- */
					if (ch_index == 1 && R_ADState == 7)
					{
							/* 1) 配好湿度用的 IO 方向（你原来的分支已做，这里不变） */

							/* 2) 只做一次：选湿度通道 + 清计数 + 置 busy 标志 */
							if (!hum_run) {
								
									hum_acc  = 0;
									hum_cnt  = 0;
									hum_phase= 0;
									hum_run  = 1;            /* 交给 Timer-0 去跑 10 次采样   */
							}
							else  if(hum_run == 2)
							{
								
                humidity = Trana(hum_acc, temperature);
                hum_run   =0;               /* 采样结束         */
							}

							return;                      /* 立刻退出，1 ms 后再进来       */
					}

					return;
				}
		ADSOC = 1;
		break;
    case 8:
        if (ADSOC) break;
        ADSOC = 0;
        if (R_ADCnt < 10) {
            R_ReadData[R_ADCnt++] = ((ADCDH << 4) & 0xFF0) | (ADCDL >> 4);
            ADSOC = 1;
            break;
        }
        {
            unsigned int sum = 0;
            for (i= 0; i < 10; i++)
                sum += R_ReadData[i];
            adc_value = sum / 10;
        }
        R_ADCnt = 0;
        for (i = 0; i < 10; i++)
            R_ReadData[i] = 0;
        R_ADState = 0;
				
			if(!ch_index)
			{
				for(i=0;i<52;i++)
				{
					if(adc_value<=Temp_Table[i])break;
				}
				
				temperature = i-3;
			}
			else
			{
				//2600 3v
				//3050 3.5v
				Battery_Vol_Check();
			}
        break;
    }
}

code unsigned int TAD[]={
//HGL12
// 90%-80%-70%-60%-50%-40%-30%-20%-10% (RH)
879,798,634,424,238,113, 55, 41, 39, //0℃
898,820,676,468,273,128, 59, 42, 39, //5℃
912,849,711,507,307,148, 64, 43, 39, //10℃
925,873,745,552,339,164, 69, 44, 39, //15℃
933,888,773,586,366,182, 74, 45, 39, //20℃
942,903,804,625,399,200, 81, 47, 40, //25℃
949,912,824,655,424,218, 89, 49, 40, //30℃
953,921,842,684,452,241, 98, 50, 40, //35℃
959,929,858,711,483,258,106, 52, 40, //40℃
963,938,873,731,504,266,114, 54, 41, //45℃
967,944,884,749,525,281,121, 56, 41 //50℃
};//
unsigned int idata CurAD[9];
u16 Trana(s16 Tem,u16 HumAD)
{
	u16 Rehum,k;
	u8 num;
	if(Tem<=0)//0 摄氏度的使用 0 的
	{
		for(num=0;num<9;num++)
		{
			CurAD[num] = TAD[num];
		}
	}
	else if(Tem>=500)//超过 50 摄氏度的
	{
		Rehum = Tem - 500;
		for(num=0;num<9;num++)

		{
			CurAD[num] = TAD[90+num]+(TAD[90+num]-TAD[81+num])*Rehum/50;
		}
	}
	else 
	{
		for(k=1;k<11;k++)//从 1 开始
		{
			if(Tem<(k*50)) //温度有做 10 倍数
			{
				Rehum = k*50-Tem;
				k = 9*k;
				for(num=0;num<9;num++)
				{
					CurAD[num] = TAD[k+num] - (TAD[k+num]-TAD[k-9+num])*Rehum/50;//
				}
				break;
			}
		}
	}
	if(HumAD<CurAD[8])//10%--
	{
		Rehum = 100-(CurAD[8]-HumAD)*100/(CurAD[7]-CurAD[8]);
		if(Rehum>100)Rehum=0;
	}
	else
	for(k=1;k<9;k++)//从 1 开始,也就是 90%>HumAD>80%
	{
		if(HumAD>=CurAD[k]) //湿度在 90%-80%-70%-60%-50%-40%
		{
			Rehum = (HumAD-CurAD[k])*100/(CurAD[k-1]-CurAD[k])+900-k*100;//
			break;
		}
	}
	if(Rehum>=999)Rehum=999;
	return Rehum;
}

/* 每次 VCC 通道采样完毕后调用 */
void Battery_Vol_Check(void)
{ 
}


code unsigned int Temp_Table[]=
{
		417 	,		//	-1
		436 	,		//	0
		457 	,		//	1
		478 	,		//	2
		499 	,		//	3
		522 	,		//	4
		545 	,		//	5
		569 	,		//	6
		593 	,		//	7
		618 	,		//	8
		644 	,		//	9
		671 	,		//	10
		698 	,		//	11
		726 	,		//	12
		755 	,		//	13
		784 	,		//	14
		814 	,		//	15
		845 	,		//	16
		876 	,		//	17
		908 	,		//	18
		941 	,		//	19
		974 	,		//	20
		1008 	,		//	21
		1043 	,		//	22
		1078 	,		//	23
		1113 	,		//	24
		1149 	,		//	25
		1186 	,		//	26
		1223 	,		//	27
		1260 	,		//	28
		1298 	,		//	29
		1336 	,		//	30
		1375 	,		//	31
		1414 	,		//	32
		1453 	,		//	33
		1493 	,		//	34
		1532 	,		//	35
		1572 	,		//	36
		1612 	,		//	37
		1653 	,		//	38
		1693 	,		//	39
		1733 	,		//	40
		1774 	,		//	41
		1814 	,		//	42
		1854 	,		//	43
		1895 	,		//	44
		1935 	,		//	45
		1975 	,		//	46
		2015 	,		//	47
		2054 	,		//	48
		2094 	,		//	49
		2133 	,		//	50
		2172 	,		//	51




};

#endif
