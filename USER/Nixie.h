#ifndef __NIXIE_H__
#define __NIXIE_H__


#define	P12(n)							{if(n) P1 |= BIT2; else  P1 &= ~BIT2;}
#define	P10(n)							{if(n) P1 |= BIT0; else  P1 &= ~BIT0;}
#define	P13(n)							{if(n) P1 |= BIT3; else  P1 &= ~BIT3;}
#define	ICN2025_CLK_SET()   P12(1)
#define	ICN2025_CLK_CLR()   P12(0)
#define	ICN2025_SDA3_SET()  P10(1)
#define	ICN2025_SDA3_CLR()  P10(0)
#define	ICN2025_LE_SET()	  P13(1)
#define	ICN2025_LE_CLR()  	P13(0)


//#define	P17(n)							{if(n) P1 |= BIT7; else  P1 &= ~BIT7;}
//#define	P16(n)							{if(n) P1 |= BIT6; else  P1 &= ~BIT6;}
//#define	P15(n)							{if(n) P1 |= BIT5; else  P1 &= ~BIT5;}
//#define	ICN2025_CLK_SET()   P16(1)
//#define	ICN2025_CLK_CLR()   P16(0)
//#define	ICN2025_LE_SET()	P17(1)
//#define	ICN2025_LE_CLR()	P17(0)
//#define	ICN2025_SDA3_SET()  P15(1)
//#define	ICN2025_SDA3_CLR()  P15(0)






 

extern unsigned char Hour_Hig;  		//小时十位 
extern unsigned char Hour_Low;  		//小时个位
extern unsigned char Min_Hig;   		//分钟十位 
extern unsigned char Min_Low;   		//分钟个位
extern unsigned char Sec_Hig;   		//秒十位
extern unsigned char Sec_Low;   		//秒个位
extern unsigned char Month_Hig; 		//月十位
extern unsigned char Month_Low; 		//月个位
extern unsigned char Day_Hig;	 		//日十位
extern unsigned char Day_Low;	 		//日个位

extern unsigned char Al_Hour_Hig;  //闹钟小时十位 
extern unsigned char Al_Hour_Low;  //闹钟小时个位
extern unsigned char Al_Min_Hig;   //闹钟分钟十位 
extern unsigned char Al_Min_Low;   //闹钟分钟个位

extern unsigned char Temp_Hig;  		//温度十位 
extern unsigned char Temp_Low;  		//温度个位

extern unsigned char Hum_Hig; 		  //湿度十位 
extern unsigned char Hum_Low; 		  //湿度个位

extern unsigned char Well_s;

extern bit AmPoint; 												//am
extern bit PmPoint; 												//pm
extern bit TIMER_Point;										//Timer 点
extern bit SleepPoint;											//贪睡
extern bit SecPoint;	 											//秒点
extern bit COL2_Point;	 										//col2
extern bit BAT_Point;											//BAAT
extern bit AlarmPoint1;										//闹钟1
extern bit AlarmPoint2;										//闹钟2
extern bit AlarmPoint3;										//闹钟3
extern bit COL3_Point;	 										//col3
extern bit Hum_Point;	 										//Hum
extern bit C_Point;	 											//C
extern bit Temp_Point;											//TEMP 
extern bit BaiFenHao_Point;								//百分号 
						
extern bit Option_Point;										//表示现在是否自动切换时钟
extern bit M_Point;												//月点		
extern bit D_Point;												//日点

extern code uint8_t WEEK_TABLE[];

void Write_2025_Command(void);
extern unsigned char Brightness_level;
void Light_adj_fun(unsigned char index);
extern unsigned int idata R_DisData ;
void Nixie_config(void);
void Nixie_Loop(void);
#endif
