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






 

extern unsigned char Hour_Hig;  		//Сʱʮλ 
extern unsigned char Hour_Low;  		//Сʱ��λ
extern unsigned char Min_Hig;   		//����ʮλ 
extern unsigned char Min_Low;   		//���Ӹ�λ
extern unsigned char Sec_Hig;   		//��ʮλ
extern unsigned char Sec_Low;   		//���λ
extern unsigned char Month_Hig; 		//��ʮλ
extern unsigned char Month_Low; 		//�¸�λ
extern unsigned char Day_Hig;	 		//��ʮλ
extern unsigned char Day_Low;	 		//�ո�λ

extern unsigned char Al_Hour_Hig;  //����Сʱʮλ 
extern unsigned char Al_Hour_Low;  //����Сʱ��λ
extern unsigned char Al_Min_Hig;   //���ӷ���ʮλ 
extern unsigned char Al_Min_Low;   //���ӷ��Ӹ�λ

extern unsigned char Temp_Hig;  		//�¶�ʮλ 
extern unsigned char Temp_Low;  		//�¶ȸ�λ

extern unsigned char Hum_Hig; 		  //ʪ��ʮλ 
extern unsigned char Hum_Low; 		  //ʪ�ȸ�λ

extern unsigned char Well_s;

extern bit AmPoint; 												//am
extern bit PmPoint; 												//pm
extern bit TIMER_Point;										//Timer ��
extern bit SleepPoint;											//̰˯
extern bit SecPoint;	 											//���
extern bit COL2_Point;	 										//col2
extern bit BAT_Point;											//BAAT
extern bit AlarmPoint1;										//����1
extern bit AlarmPoint2;										//����2
extern bit AlarmPoint3;										//����3
extern bit COL3_Point;	 										//col3
extern bit Hum_Point;	 										//Hum
extern bit C_Point;	 											//C
extern bit Temp_Point;											//TEMP 
extern bit BaiFenHao_Point;								//�ٷֺ� 
						
extern bit Option_Point;										//��ʾ�����Ƿ��Զ��л�ʱ��
extern bit M_Point;												//�µ�		
extern bit D_Point;												//�յ�

extern code uint8_t WEEK_TABLE[];

void Write_2025_Command(void);
extern unsigned char Brightness_level;
void Light_adj_fun(unsigned char index);
extern unsigned int idata R_DisData ;
void Nixie_config(void);
void Nixie_Loop(void);
#endif
