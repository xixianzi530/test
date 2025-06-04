#ifndef __DISPLAY_UI_H__
#define __DISPLAY_UI_H__
typedef enum
{
	Time_UI = 0,
	
	Ajust_aYear=1,	
	Ajust_aMonth=2,	
	Ajust_aDay=3,	
	
	Ajust_12_24 = 4,
	Ajust_Hour=5,
	Ajust_Min=6,
	
	
	Alarm_UI = 7,
	Ajust_aHour=8,	
	Ajust_aMin=9,		
	Ajust_aSnoozeDays=10,	
	Ajust_Alarm=11,	
	
	Alarm_UI_1 = 12,
	Ajust_aHour_1=13,		
	Ajust_aMin_1=14,	
	Ajust_aSnoozeDays_1=15,	
	Ajust_Alarm_1=16,	
	
	Alarm_UI_2 = 17,
	Ajust_aHour_2=18,		
	Ajust_aMin_2=19,	
	Ajust_aSnoozeDays_2=20,	
	Ajust_Alarm_2=21,	
	
	Ajust_Light_UI	= 22,
	Ajust_Music_INDEX_UI  = 23,
	Ajust_Music_SIZE_UI  = 24,
	Ajust_YEJIAN_UI  = 25,
	
	Ajust_Down_Time_UI=26,
	Ajust_Down_Time_Ahour=27,
	Ajust_Down_Time_Amin=28,
	Ajust_Down_Time_Asec=29,
	
}page_state_t;


extern unsigned char Servant_Page_State; //��ʾָ�룬���ڵ�ǰ��ʾ�Ǹ�ҳ��
/**************************������-ʱ����-����-����*******************************/
extern unsigned char idata R_Hour;                  //Сʱ
extern unsigned char idata R_Min ;                  //����
extern unsigned char idata R_Sec;                   //��
                     
extern unsigned char idata R_Year;                  //��
extern unsigned char idata R_Day ;                  //��
extern unsigned char idata R_Month;                 //��
extern unsigned char idata R_Week;                  //����

extern unsigned char idata R_aHour[3];              //����Сʱ
extern unsigned char idata R_aMin[3];               //���ӷ���
extern unsigned char idata R_Alarm_Days[3];         //������������
extern unsigned char idata Alarm_EN[3];             //���ӿ���
extern unsigned char idata Alerm_ON[3];             //��������״̬��־λ
extern unsigned char idata R_Tsleep[3] ;            //̰˯



extern bit B_FlashData;											 //��˸��־λ�����ڸ�����˸
extern bit Switch_Layout;                     //1 24Сʱ 0 12Сʱ

extern unsigned char AutoSave_Time ;					 //�Զ��˳����ý���
extern unsigned char AutoStop_Time ;					 //����͹���ʱ��


/* ==== ����/ʱ��ѭ����ʾ���� =================================== */
extern unsigned char ShowDateNow;             // 0=��ʾʱ�� 1=��ʾ���� 2 = �¶�
extern unsigned char CycleCnt;                // ��������� 10 �л�һ��
/* ============================================================== */


/**************************������Ŀ-��������*******************************/
extern unsigned char Music_Index;             //��ǰ��Ŀ
extern unsigned char Music_Size;              //������С



/**************************ҹ��ģʽ���*******************************/
extern unsigned char Night_Mode;//ҹ��ģʽ���� off����ģʽ onҹ��ģʽ
extern unsigned char Night_Mode_Delay;//��������ڿ����͹ر�ҹ��ģʽ�󣬼�ʱ�õģ���������ҹ��ģʽ���л���on���棬����3s�Զ��˳�����ظ�������ǰ�Ľ��棩


/**************************�������*******************************/
extern unsigned char idata Stop_rouse;//���ڴ��ڵ͹���ʱ���رն�ʱ���󣬻��Ѻ�����    ����

      
/* ��ɽӿڱ���һ�� -------------------------------------------*/
bit alarm_core(uint8 mode);
#define Into_Sleep()   (alarm_core(0))
#define Off_SleepIng() (alarm_core(1))
#define Off_Sleep()    (alarm_core(2))



/**************************����ʱ���*******************************/
extern unsigned char idata B_Counting;              /* 1 = ���ڵ���ʱ */
extern bit Timer_Alarm_On ;

extern unsigned char cd_min  ; 				 /* 0-199 */
extern unsigned char cd_sec; 					 /* 0-59  */
extern unsigned char A_cd_min; 				 /* 0-199 */
extern unsigned char A_cd_sec;  						 /* 0-59  */
bit off_Timer();


void Dis_FlashMenu(void);
void ShowData_Init_UpData();
void Half_Second ();
void Get_Add_Action(void);

void Alarm_Show_Switch();
void Week_UI(unsigned char Week_Tmp);
void Month_Day_UI(unsigned char Month_Tmp,unsigned char Day_Tmp);
void Temperature_UI(char Temp) ;
void Humidity_UI(char Hum) ;


void YeJian_Onoff(bit state);



//extern bit power_off; 



////������
//extern unsigned char R_Year;
//extern unsigned char R_Day;
//extern unsigned char R_Month;

////12/24Сʱ
//extern unsigned char idata Switch_Layout;//1 24Сʱ 0 12Сʱ
////��������
//extern unsigned char R_aMin[3];
//extern unsigned char R_aHour[3];
//extern unsigned char R_Alarm_Days[3];
//extern unsigned char Alarm_EN[3];
//extern unsigned char Alerm_ON[3];
//extern unsigned char R_Tsleep[3] ;	//̰˯

////����
//extern  unsigned char Music_Index;//��ǰ��Ŀ
//extern  unsigned char Music_Size;//������С



//extern unsigned int Night_Mode_Time ;//ҹ��ģʽ�Զ�������ʱ
//extern unsigned char Servant_Page_State;

//extern unsigned char AutoStop_Time;
//extern unsigned char CycleCnt;
//extern unsigned char AutoSave_Time;//�Զ��˳����ý���
//extern unsigned char ShowDateNow ;
//extern bit sleep_onoff ;
//extern bit      CycleDateFlag ;
//extern bit B_FlashData ;
//extern unsigned char g_comp_timer;
//void Sleep_UI(unsigned char index);
//void Dis_FlashMenu(void);
//void ShowData_Init_UpData();
//void Half_Second ();
//void Get_Add_Action(void);
////Ĭ������
//void moren_data();
//void Display_CommonInfo(void);
///*************̰˯����**************/
//bit Off_Sleep();//
//bit Into_Sleep();
//bit Off_SleepIng();
//void ON_Music(unsigned char index);
//extern unsigned char cd_min;   /* 0-199 */
//extern unsigned char cd_sec;   /* 0-59  */
//extern unsigned char A_cd_min;
//extern unsigned char A_cd_sec;
//extern bit     Brightness_Manual_Flag;
//extern uint8   pb_idx ;
//void PB_Set(uint8 idx);
//extern unsigned char idata B_Counting;              /* 1 = ���ڵ���ʱ */
void SHOW_Out(void);
//void PowerOn_Detection(void);
//void PB_Task_1ms(void);
//void PB_Restore(void);

//void PB_Init(void);
#endif
