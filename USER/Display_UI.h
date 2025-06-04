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


extern unsigned char Servant_Page_State; //显示指针，用于当前显示那个页面
/**************************年月日-时分秒-星期-闹钟*******************************/
extern unsigned char idata R_Hour;                  //小时
extern unsigned char idata R_Min ;                  //分钟
extern unsigned char idata R_Sec;                   //秒
                     
extern unsigned char idata R_Year;                  //年
extern unsigned char idata R_Day ;                  //月
extern unsigned char idata R_Month;                 //日
extern unsigned char idata R_Week;                  //星期

extern unsigned char idata R_aHour[3];              //闹钟小时
extern unsigned char idata R_aMin[3];               //闹钟分钟
extern unsigned char idata R_Alarm_Days[3];         //闹钟响闹天数
extern unsigned char idata Alarm_EN[3];             //闹钟开关
extern unsigned char idata Alerm_ON[3];             //闹钟响闹状态标志位
extern unsigned char idata R_Tsleep[3] ;            //贪睡



extern bit B_FlashData;											 //闪烁标志位，用于各种闪烁
extern bit Switch_Layout;                     //1 24小时 0 12小时

extern unsigned char AutoSave_Time ;					 //自动退出设置界面
extern unsigned char AutoStop_Time ;					 //进入低功耗时间


/* ==== 日期/时间循环显示控制 =================================== */
extern unsigned char ShowDateNow;             // 0=显示时间 1=显示日期 2 = 温度
extern unsigned char CycleCnt;                // 秒计数，满 10 切换一次
/* ============================================================== */


/**************************音乐曲目-音乐声音*******************************/
extern unsigned char Music_Index;             //当前曲目
extern unsigned char Music_Size;              //声音大小



/**************************夜间模式相关*******************************/
extern unsigned char Night_Mode;//夜间模式开关 off常亮模式 on夜间模式
extern unsigned char Night_Mode_Delay;//这个是用于开启和关闭夜间模式后，计时用的（长按开启夜间模式，切换至on界面，持续3s自动退出界面回复到进入前的界面）


/**************************闹钟相关*******************************/
extern unsigned char idata Stop_rouse;//用于处于低功耗时，关闭定时器后，唤醒后响闹    闹钟

      
/* 与旧接口保持一致 -------------------------------------------*/
bit alarm_core(uint8 mode);
#define Into_Sleep()   (alarm_core(0))
#define Off_SleepIng() (alarm_core(1))
#define Off_Sleep()    (alarm_core(2))



/**************************倒计时相关*******************************/
extern unsigned char idata B_Counting;              /* 1 = 正在倒计时 */
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



////年月日
//extern unsigned char R_Year;
//extern unsigned char R_Day;
//extern unsigned char R_Month;

////12/24小时
//extern unsigned char idata Switch_Layout;//1 24小时 0 12小时
////两组闹钟
//extern unsigned char R_aMin[3];
//extern unsigned char R_aHour[3];
//extern unsigned char R_Alarm_Days[3];
//extern unsigned char Alarm_EN[3];
//extern unsigned char Alerm_ON[3];
//extern unsigned char R_Tsleep[3] ;	//贪睡

////音乐
//extern  unsigned char Music_Index;//当前曲目
//extern  unsigned char Music_Size;//声音大小



//extern unsigned int Night_Mode_Time ;//夜间模式自动开启计时
//extern unsigned char Servant_Page_State;

//extern unsigned char AutoStop_Time;
//extern unsigned char CycleCnt;
//extern unsigned char AutoSave_Time;//自动退出设置界面
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
////默认数据
//void moren_data();
//void Display_CommonInfo(void);
///*************贪睡处理**************/
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
//extern unsigned char idata B_Counting;              /* 1 = 正在倒计时 */
void SHOW_Out(void);
//void PowerOn_Detection(void);
//void PB_Task_1ms(void);
//void PB_Restore(void);

//void PB_Init(void);
#endif
