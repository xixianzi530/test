#include "include.h"

/***********************显示**********************************/
unsigned char Hour_Hig;  		//小时十位 
unsigned char Hour_Low;  		//小时个位
unsigned char Min_Hig;   		//分钟十位 
unsigned char Min_Low;   		//分钟个位
unsigned char Sec_Hig;   		//秒十位
unsigned char Sec_Low;   		//秒个位
unsigned char Month_Hig; 		//月十位
unsigned char Month_Low; 		//月个位
unsigned char Day_Hig;	 		//日十位
unsigned char Day_Low;	 		//日个位
unsigned char Al_Hour_Hig;  //闹钟小时十位 
unsigned char Al_Hour_Low;  //闹钟小时个位
unsigned char Al_Min_Hig;   //闹钟分钟十位 
unsigned char Al_Min_Low;   //闹钟分钟个位
unsigned char Temp_Hig;  		//温度十位 
unsigned char Temp_Low;  		//温度个位
unsigned char Hum_Hig; 		  //湿度十位 
unsigned char Hum_Low; 		  //湿度个位
unsigned char Well_s;
bit AmPoint; 								//am
bit PmPoint; 								//pm
bit TIMER_Point;						//Timer 点
bit SleepPoint;							//贪睡
bit SecPoint;	 							//秒点
bit COL2_Point;	 						//col2
bit BAT_Point;							//BAAT
bit AlarmPoint1;						//闹钟1
bit AlarmPoint2;						//闹钟2
bit AlarmPoint3;						//闹钟3
bit COL3_Point;	 						//col3
bit Hum_Point;	 						//Hum
bit C_Point;	 							//C
bit Temp_Point;							//TEMP 
bit BaiFenHao_Point;				//百分号 
bit Option_Point;//
bit M_Point;//
bit D_Point;


unsigned char Servant_Page_State; //显示指针，用于当前显示那个页面
/**************************年月日-时分秒-星期-闹钟*******************************/
unsigned char idata R_Hour;                  //小时
unsigned char idata R_Min ;                  //分钟
unsigned char idata R_Sec;                   //秒

unsigned char idata R_Year;                  //年
unsigned char idata R_Day ;                  //月
unsigned char idata R_Month;                 //日
unsigned char idata R_Week;                  //星期

unsigned char idata R_aHour[3];              //闹钟小时
unsigned char idata R_aMin[3];               //闹钟分钟
unsigned char idata R_Alarm_Days[3];         //闹钟响闹天数

unsigned char idata Alarm_EN[3];             //闹钟开关
unsigned char idata Alerm_ON[3];             //闹钟响闹状态标志位
unsigned char idata R_Tsleep[3] ;            //贪睡



bit B_FlashData;											 //闪烁标志位，用于各种闪烁
bit Switch_Layout;                     //1 24小时 0 12小时

unsigned char AutoSave_Time ;					 //自动退出设置界面
unsigned char AutoStop_Time ;					 //进入低功耗时间


/* ==== 日期/时间循环显示控制 =================================== */
unsigned char ShowDateNow;             // 0=显示时间 1=显示日期 2 = 温度
unsigned char CycleCnt;                // 秒计数，满 10 切换一次
/* ============================================================== */


/**************************音乐曲目-音乐声音*******************************/
unsigned char Music_Index;             //当前曲目
unsigned char Music_Size;              //声音大小



/**************************夜间模式相关*******************************/
unsigned char Night_Mode;            //1夜间模式，0常亮模式，当开启常亮模式后，2小时后会自动切换成夜间模式，用于省电
unsigned char Night_Mode_Delay;			//当这个数值大于0时，刷新函数将停止更新，为0时，刷新函数自动更新，切换成原来的显示界面


/*****************************自动调整亮度相关****************************/
//bit     Brightness_Manual_Flag = 0;   /* 今日已手动调过亮度 */


/*****************************闹钟响闹相关****************************/
idata unsigned int Alarm_Sleep_Timer = 0;	//闹钟响闹and贪睡时间
unsigned char idata Stop_rouse = 0;				//用于低功耗唤醒后，启动闹钟，因为发送闹钟协议是使用timer2做的，

/*****************************倒计时相关****************************/
unsigned char cd_hour  = 0;  				 /* 0-99 */
unsigned char cd_min  = 5;  				 /* 0-59 */
unsigned char cd_sec;  							 /* 0-59  */
unsigned char A_cd_hour  = 0;  				 /* 0-99 */
unsigned char A_cd_min  = 5; 				 /* 0-59 */
unsigned char A_cd_sec;  						 /* 0-59  */
unsigned char idata  B_Counting;     /* 1 = 正在倒计时 2 = 倒计时暂停 0 = 未开启*/

bit Timer_Alarm_On;									 //倒计时结束开始响铃


///*──────── 外部接口（用户自己实现） ────────*/
////extern void Alarm_Start(void);                                // 倒计时结束后触发闹铃
//void Refresh_Countdown_UI(unsigned char m, unsigned char s);   // 可选：刷新显示


//bit Timer_Alarm_On;
//void CD_Service_1s(void);



///****************************************************************************************************************/

/* ───── 自动亮度相关状态 ───── */
unsigned int  Night_Mode_Time; 			//用于记录现在处于常亮模式的时间，最大记录120分钟


void TimeKeeping_Fun();							 //1s计时函数

//void OFF_Down_Time();
void ClrDis_FlashMenu(void);//显示函数灭
void Dis_FlashMenu(void);   //显示函数亮
void Updata_BaseTim(unsigned char  Hdata,unsigned char  Mdata,unsigned char Sdata);
//void Alarm_Fate_FUN(unsigned char index);
void AutoSave_Quit(void);
void Alerm_Action(unsigned char index);//闹钟判断函数
//void Night_Mode_Service(void);

//void AutoBrightness_Service(void);


void ShowData_Init_UpData()
{
	R_Hour = 12;
	R_Min = 0;
	R_Sec = 40;
	
	R_Year = 25;//0默认为24年
	R_Month = 1;
	R_Day = 1;
	
	R_aHour[0] = 12;
	R_aMin[0] = 1;
	R_Alarm_Days[0] = 2;
	Alarm_EN[0] = 1;
	 Alerm_ON[0] = 0;
	 R_Tsleep[0] = 0;
	
	R_aHour[1] = 12;
	R_aMin[1] = 0;
	R_Alarm_Days[1] = 2;	
	 Alarm_EN[1] = 0;
	 Alerm_ON[1] = 0;
	 R_Tsleep[1] = 0;
	
	R_aHour[2] = 12;
	R_aMin[2] = 0;
	R_Alarm_Days[2] = 2;	
	 Alarm_EN[2] = 0;
	 Alerm_ON[2] = 0;
	 R_Tsleep[2] = 0;
	 
	 
	Music_Index = 1;															 //音乐选择第一首
	Music_Size = 2; 															 //声音调制中间挡
	R_Week = CaculateWeekDay(R_Year,R_Month,R_Day);//根据设置的年月日，计算出星期
	Switch_Layout = 1;														 //24小时
//	Brightness_level = 3;												 //亮度-这里不会执行，首次上电的时候，会检测ic供电，根据电压来设置亮度
	Light_adj_fun(Brightness_level);							 //设置亮度
//	DOT2_Point = 1;                              //
	Night_Mode = 1;                                //声控模式开启

	B_Base500MS = 1;
	AutoStop_Time = 15;                            //用于关闭显示的计时，上电默认设置15s
	Servant_Page_State = Time_UI;
}

//	Alarm_UI = 7,
//	Ajust_Alarm=8,	
//	Ajust_aHour=9,	
//	Ajust_aMin=10,		
//	Ajust_aSnoozeDays=11,	

void Half_Second (void)
{
	if(!B_Base500MS)return;
	B_Base500MS = 0;

	
	B_MinFlag=~B_MinFlag;
	if(B_MinFlag)B_Base1S = 1;
	TimeKeeping_Fun();
	B_FlashData =!B_FlashData;
	if(B_FlashData)Dis_FlashMenu();
	if(B_FlashData==0)ClrDis_FlashMenu();
	
/* === 充电闪烁逻辑 ================================= */
//    if (P06)                    /* 已插 DC */
//    {
//        if (!P05)               /* 充电中 → 0.5 s 闪烁 */
//        {
//            BAT_Point = B_FlashData;   /* 复用已有闪烁位 */
//        }
//        else                    /* 已充满 → 熄灭 */
//        {
//            BAT_Point = 0;
//        }
//    }

}

unsigned char Timer_Add()
{
	if(++R_Sec<60) return 0;
    R_Sec=0;
	if(++R_Min<60) return 1;
	R_Min=0;	
	if(++R_Hour<24) return 2;	
	R_Hour=0;
	 return 3;
}
void TimeKeeping_Fun()
{
	unsigned char i;
	if(!B_Base1S)return;
	B_Base1S = 0;

//	CD_Service_1s();	//倒计时函数
//	OFF_Down_Time();//自动关闭倒计时响铃
	AutoSave_Quit();//自动退出设置
	if(Night_Mode_Delay)	Night_Mode_Delay--;
//	if(AutoStop_Time)			AutoStop_Time--;//进入低功耗
	i = Timer_Add();
	switch(i)
	{
		case 3://天数加1
//			Brightness_Manual_Flag = 0;      /* 新的一天，恢复自动调光 */

			Updata_YearData();//更新年月日
		
		case 1://分钟加1
		case 2://小时加1
			Alerm_Action(0);
			Alerm_Action(1);
			Alerm_Action(2);
//			Night_Mode_Service();
			R_Week = CaculateWeekDay(R_Year,R_Month,R_Day);//更新星期
//			AutoBrightness_Service();

		break;
	}
	
}

void SHOW_Out(void)
{
	Hour_Hig       = 10  ;  		//小时十位 
	Hour_Low       = 10  ;   		//小时个位
	Min_Hig        = 10  ;   		//分钟十位 
	Min_Low        = 10  ;   		//分钟个位
	Sec_Hig        = 10  ;   		//秒十位
	Sec_Low        = 10  ;   		//秒个位
	Month_Hig      = 0  ; 		//月十位
	Month_Low      = 10  ; 		//月个位
	Day_Hig        = 10  ;	 		//日十位
	Day_Low        = 10  ;	 		//日个位
	Al_Hour_Hig    = 10  ;  //闹钟小时十位 
	Al_Hour_Low    = 10  ;  //闹钟小时个位
	Al_Min_Hig     = 10  ;   //闹钟分钟十位 
	Al_Min_Low     = 10  ;   //闹钟分钟个位
	Temp_Hig       = 10  ;  		//温度十位 
	Temp_Low       = 10  ;  		//温度个位
	Hum_Hig        = 10  ; 		  //湿度十位 
	Hum_Low        = 10  ; 		  //湿度个位
	Well_s         = 10  ;
	AmPoint        = 0  ; 								//am
	PmPoint        = 0  ; 								//pm
	TIMER_Point    = 0  ;						//Timer 点
	SleepPoint     = 0  ;							//贪睡
	SecPoint       = 0  ;	 							//秒点
	COL2_Point     = 0  ;	 						//col2
	BAT_Point      = 0  ;							//BAAT
	AlarmPoint1    = 0  ;						//闹钟1
	AlarmPoint2    = 0  ;						//闹钟2
	AlarmPoint3    = 0  ;						//闹钟3
	COL3_Point     = 0  ;	 						//col3
	Hum_Point      = 0  ;	 						//Hum
	C_Point        = 0  ;	 							//C
	Temp_Point     = 0  ;							//TEMP 
	BaiFenHao_Point= 0  ;				//百分号 
	Option_Point   = 0  ;//
	M_Point        = 0  ;//
	D_Point        = 0  ;
}

/**************************设置小时分钟****************************/
/**************************设置小时和分钟****************************/
void Get_BaseTim(unsigned char hour, unsigned char min,unsigned char sec)
{
	unsigned char i;
	
	
	i=hour;
	if(hour<24)
	{	
		i=hour&0x1f;
		if(!Switch_Layout)
		{	
			if(i>=12)
			{
				i-=12;
				if(!i)
				{
					i=12;	
				}	
				PmPoint = 1;
				AmPoint = 0;
			}
			else
			{
				PmPoint = 0;
				AmPoint = 1;
				if(!i)
				{
					i=12;	
				}		
			}	
		}
	}
	Updata_BaseTim(i,min,sec);
}


void Updata_BaseTim(unsigned char  Hdata,unsigned char  Mdata,unsigned char Sdata)
{
    Hour_Hig = 10;
    Hour_Low = 10;
    Min_Hig = 10;
    Min_Low = 10;
		Sec_Hig = 10;   		//秒十位
		Sec_Low = 10;   		//秒个位
		SecPoint = 1;
		COL2_Point = 0;
    // 只在合法范围内更新小时
    if (Hdata < 200) {
        if (Hdata >= 10) {
            Hour_Hig = Hdata / 10;   // 十位
        }
        Hour_Low = Hdata % 10;       // 个位
    }

    // 只在合法范围内更新分钟
    if (Mdata < 60) {
        Min_Hig = Mdata / 10;       // 十位
        Min_Low = Mdata % 10;       // 个位
    }
		
		 if (Sdata < 60) {
				COL2_Point = 1;
        Sec_Hig = Sdata / 10;       // 十位
        Sec_Low = Sdata % 10;       // 个位
    }
}
   

/**************************12/24小时函数****************************/
void fun_12_24_UI(unsigned char temp)
{	
	
	Min_Hig = 18;
	Min_Low = 21;
	Hour_Hig = 10;
	Hour_Low = 10;
	if(temp>=100)return;
	if(temp == 0)
	{
		Hour_Hig = 1;
		Hour_Low = 2;
	}
	else
	{
		Hour_Hig = 2;
		Hour_Low = 4;
	}
}

/**************************年显示函数****************************/
void Year_UI(unsigned char Year_Tmp)
{
	Hour_Hig = 10;
	Hour_Low = 10;
	Min_Hig =  10;
	Min_Low =  10;
	if(Year_Tmp > 110)return;
		
	Hour_Hig = 2;
	Hour_Low = Year_Tmp/100;
	Min_Hig = Year_Tmp/10%10;
	Min_Low = Year_Tmp%10;
}
/**************************月份显示函数****************************/
void Month_Day_UI(unsigned char Month_Tmp,unsigned char Day_Tmp)
{
	M_Point = 1;//
	D_Point = 1;
	Month_Hig = 0;
	Month_Low = 10;
	Day_Hig =  10;
	Day_Low =  10;
	if(Month_Tmp < 13)
	{
		if(Month_Tmp >= 10)
		{
			Month_Hig = 1;
		}
		Month_Low = Month_Tmp%10;
	}
	
	if(Day_Tmp > 32)return;
		
		Day_Hig = Day_Tmp/10;

	Day_Low = Day_Tmp%10;
}
/**************************星期显示函数****************************/
void Week_UI(unsigned char Week_Tmp)
{
	Well_s = 10;
	if(Week_Tmp >200)return;
	Well_s = Week_Tmp;
}

   
/**************************温度显示函数****************************/

void Temperature_UI(char Temp) 
{
	
    if (Temp <= 0)
    {
			Temp =0;
    }
    if (Temp > 50)
    {
        Temp = 50;
    }
		Temp_Point = 1;
		C_Point = 1;
		Temp_Hig = abs(Temp) / 10;
		Temp_Low = abs(Temp) % 10;


}
/**************************湿度显示函数****************************/

void Humidity_UI(char Hum) 
{
	
		Hum_Point = 1;
		BaiFenHao_Point = 1;
		C_Point = 1;
		Hum_Hig = abs(Hum) / 10;
		Hum_Low = abs(Hum) % 10;


}

/**************************闹钟显示函数****************************/

void Updata_Alarm_UI(unsigned char  AHdata,unsigned char  AMdata)
{
    Al_Hour_Hig = 10;
    Al_Hour_Low = 10;
    Al_Min_Hig = 10;
    Al_Min_Low = 10;

    // 只在合法范围内更新小时
    if (AHdata < 200) {
        if (AHdata >= 10) {
            Al_Hour_Hig = AHdata / 10;   // 十位
        }
        Al_Hour_Low = AHdata % 10;       // 个位
    }

    // 只在合法范围内更新分钟
    if (AMdata < 60) {
        Al_Min_Hig = AMdata / 10;       // 十位
        Al_Min_Low = AMdata % 10;       // 个位
    }
		
}
///**************************闹钟界面****************************/

//闹钟图标显示
void Alarm_Show_Switch()
{
	if(Alarm_EN[0])
	{
		COL3_Point = 1;
		Updata_Alarm_UI(R_aHour[0],R_aMin[0]);
	}
	else if(Alarm_EN[1])
	{
		COL3_Point = 1;
		Updata_Alarm_UI(R_aHour[1],R_aMin[1]);

	}
	else if(Alarm_EN[2])
	{
		COL3_Point = 1;
		Updata_Alarm_UI(R_aHour[2],R_aMin[2]);

	}
	AlarmPoint1=Alarm_EN[0];
	AlarmPoint2=Alarm_EN[1];
	AlarmPoint3=Alarm_EN[2];
}
void Alarm_UI_FUN(unsigned char index)
{
	COL3_Point = 1;
	switch(index)
	{ 
		case Alarm_UI:
		
				AlarmPoint1 = 1;
				Updata_Alarm_UI(R_aHour[0],R_aMin[0]);
		break;
		
		case Alarm_UI_1:
				AlarmPoint2 = 1;
				Updata_Alarm_UI(R_aHour[1],R_aMin[1]);
			
		break;
		case Alarm_UI_2:
				AlarmPoint3 = 1;
				Updata_Alarm_UI(R_aHour[2],R_aMin[2]);
			
		break;
	}
	

}	


///************************** 夜间开关 **************************/
void YeJian_Onoff(bit state)
{
	AmPoint        = 0  ; 								//am
	PmPoint        = 0  ; 								//pm
	TIMER_Point    = 0  ;						//Timer 点
	SleepPoint     = 0  ;							//贪睡
	SecPoint       = 0  ;	 							//秒点
	COL2_Point     = 0  ;	 						//col2
  Hour_Hig  = 10; 
	Sec_Hig = 10;
	Sec_Low = 10;
	
	if(state)
	{
    Hour_Low  = 10;
    Min_Hig  =  0;
    Min_Low  =  14;	
	}
	else
	{
		 Hour_Low = 0;
		 Min_Hig  = 12;
		 Min_Low  = 12;
	}
}

/************************** 闹钟开/关 ****************************/
void Alarm_Onoff(unsigned char Index)
{
	
	Al_Hour_Hig = 10;  

	Al_Hour_Low =10;
	Al_Min_Hig  = 10;
	Al_Min_Low  = 10;
	if(Index >200)return;
    Al_Hour_Hig = 0;  
	if(Index)
	{
    Al_Hour_Low =14;
	}
	else
	{
    Al_Hour_Low =12;
    Al_Min_Hig  = 12;
		
	}
}

void Alarm_Time_Set(unsigned char ui,unsigned char ahour, unsigned char amin)
{

    /* 点亮对应闹钟指示灯 */
    if      (ui == Alarm_UI)   AlarmPoint1 = 1;
    else if (ui == Alarm_UI_1) AlarmPoint2 = 1;
    else if (ui == Alarm_UI_2) AlarmPoint3 = 1;
    else                       return;                /* 非法编号 */

		COL3_Point = 1;
		Updata_Alarm_UI(ahour, amin);

}

///**************************闹钟想闹天数选择****************************/
void Alarm_Fate_UI(unsigned char index)
{
	code unsigned char fate_table[] = {5,6,7};
	
	Al_Hour_Hig = 10;   /* OFF */
	Al_Hour_Low = 10;
	Al_Min_Hig  = 10;
	Al_Min_Low  = 10;
	if(index>200)return;
	Al_Hour_Hig = fate_table[index];
	Al_Hour_Low = 19;
	
	Week_UI(index+7);

}


///**************************亮度选择****************************/



/**************************音乐声音选择****************************/
void Music_SIZE_UI(unsigned char index )
{

	
	Hour_Hig = 10;
	Hour_Low = 20;
	Min_Hig = 0;
	Min_Low = index+1;
}
/**************************音乐选择****************************/
void Music_Index_UI(unsigned char index )
{ 
	
	Hour_Hig = 10;
	Hour_Low = 22; 
	Min_Hig = index/10;
	Min_Low = index%10;
}	


/**************************显示函数-灭****************************/
void ClrDis_FlashMenu(void)
{
	if(Night_Mode_Delay)return;
    switch (Servant_Page_State) 
    {       
        case Time_UI:        // 正常显示
				SleepPoint = 0;
				if(Alerm_ON[0])
					AlarmPoint1 = 0;
				else if(Alerm_ON[1])
					AlarmPoint2 = 0;
				else if(Alerm_ON[2])
					AlarmPoint3 = 0;
				break;
        case Ajust_aYear:       //年   
            Year_UI(0xff);
//					Alarm_Show_Switch();//闹钟 

				
        break;
        case Ajust_aMonth:      //月   
					Month_Day_UI(0xff,R_Day);//月日显示 
//					Alarm_Show_Switch();//闹钟 
        break; 
        case Ajust_aDay:        //日   
					Month_Day_UI(R_Month,0xff);//月日显示 
//					Alarm_Show_Switch();//闹钟 
        break;    
	
				case Ajust_12_24:
					fun_12_24_UI(0xff);
//					Alarm_Show_Switch();//闹钟 
				break;
        case Ajust_Hour:    //小时设置
					Get_BaseTim(0xff,R_Min,0xff);
        break;
        case Ajust_Min:     //分钟设置    
					Get_BaseTim(R_Hour,0xff,0xff);
        break;

/***************************************************/
        case Alarm_UI:            //闹钟               
					                                         
				break;					
				case Ajust_Alarm://闹钟开关界面
					Alarm_Onoff(0xff);
				break;
				
        case Ajust_aHour:         //闹钟小时    
					Alarm_Time_Set(Alarm_UI,0xff, R_aMin[0]);
				break;
        case Ajust_aMin:          //闹钟分钟 
					Alarm_Time_Set(Alarm_UI,R_aHour[0], 0xff);   
				break;
        case Ajust_aSnoozeDays:   //响闹天数设置
					Alarm_Fate_UI(0xff);
        break;        

/***************************************************/
        case Alarm_UI_1:          //闹钟
        break;
				case Ajust_Alarm_1:
					Alarm_Onoff(0xff);
					
				break;
        case Ajust_aHour_1:       //闹钟小时   
					Alarm_Time_Set(Alarm_UI_1,0xff, R_aMin[1]); 
				break;
        case Ajust_aMin_1:        //闹钟分钟   
					Alarm_Time_Set(Alarm_UI_1,R_aHour[1], 0xff);  
				break;
        case Ajust_aSnoozeDays_1: //响闹天数设置
					Alarm_Fate_UI(0xff);
		
        break;    

/***************************************************/
				case Alarm_UI_2:          //闹钟
        break;
				case Ajust_Alarm_2:
					Alarm_Onoff(0xff);
					
				break;
        case Ajust_aHour_2:       //闹钟小时 
					Alarm_Time_Set(Alarm_UI_2,0xff, R_aMin[2]); 
				break;   
        case Ajust_aMin_2:        //闹钟分钟   
					Alarm_Time_Set(Alarm_UI_2,R_aHour[2], 0xff);  
				break;
        case Ajust_aSnoozeDays_2: //响闹天数设置
					Alarm_Fate_UI(0xff);
					
        break;    
	/******************************************************/
	
				case Ajust_Light_UI:
					
				break;
				case Ajust_Down_Time_UI:
					
				if(Timer_Alarm_On)
				{
					
					Updata_BaseTim(0xff,0xff,0XFF);
					TIMER_Point = 0;
					SecPoint = 0;
					COL2_Point = 0;
				}
				break;
				case Ajust_Down_Time_Ahour:
					Updata_BaseTim(0XFF,A_cd_min,A_cd_sec);
					TIMER_Point = 1;
				break;
				case Ajust_Down_Time_Amin:
					Updata_BaseTim(A_cd_hour,0xff,A_cd_sec);
					TIMER_Point = 1;
				break;
				case Ajust_Down_Time_Asec:
					Updata_BaseTim(A_cd_hour,A_cd_min,0xff);
					TIMER_Point = 1;
				break;
        default:
        break;
    }    
}	

void Dis_FlashMenu(void)
{ 
	if(Night_Mode_Delay)return;
		switch (Servant_Page_State)
    {       
        case Time_UI:        // 正常显示
					SHOW_Out();
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
					
					Alarm_Show_Switch();							 // 显示闹钟
					Week_UI(R_Week);									 // 显示星期
				
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
					if(R_Tsleep[0]||R_Tsleep[1]||R_Tsleep[2])
					{
						SleepPoint = 1;
					}
				break;
        case Ajust_aYear:       //年    
					SHOW_Out();
					Year_UI(R_Year);
				
				
					Alarm_Show_Switch();							 // 显示闹钟
					Week_UI(R_Week);									 // 显示星期
				
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				
        break;
        case Ajust_aMonth:      						 //月    
        case Ajust_aDay:        						 //日   
					SHOW_Out();
					Month_Day_UI(R_Month, R_Day);  		 // 显示月日
				
					Week_UI(R_Week);									 // 显示星期
					Alarm_Show_Switch();							 // 显示闹钟
					Get_BaseTim(R_Hour,R_Min,0xff);		 // 显示时间
					
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
        break;    
	
				case Ajust_12_24:
					SHOW_Out();
					fun_12_24_UI(Switch_Layout);
				
				
					Month_Day_UI(R_Month, R_Day);  		 // 显示月日
					Week_UI(R_Week);									 // 显示星期
					Alarm_Show_Switch();							 // 显示闹钟
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				break;
        case Ajust_Hour:    //小时设置
        case Ajust_Min:     //分钟设置   
					SHOW_Out();
					Get_BaseTim(R_Hour,R_Min,0xff);
				
				
					
					
					Alarm_Show_Switch();							 // 显示闹钟
					Week_UI(R_Week);									 // 显示星期
				
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				
        break;
/***************************************************/
        case Alarm_UI:            //闹钟 1
				case Alarm_UI_1:          //闹钟 2
				case Alarm_UI_2:          //闹钟 3
					SHOW_Out();
					COL3_Point = 1;
					Alarm_UI_FUN(Servant_Page_State);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
        break;
				case Ajust_Alarm:
				
					Alarm_Onoff(Alarm_EN[0]);
				break;
        case Ajust_aHour:         //闹钟小时    
        case Ajust_aMin:          //闹钟分钟  
					SHOW_Out();
				
					Alarm_Time_Set(Alarm_UI,R_aHour[0], R_aMin[0]);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				
				break;
        case Ajust_aSnoozeDays:   //响闹天数设置
					
					SHOW_Out();
					
					AlarmPoint1 = 1;
					Alarm_Fate_UI(R_Alarm_Days[0]);
				
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
//					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				
        break;      
				
	/******************************************************/
       	case Ajust_Alarm_1:
					
					Alarm_Onoff(Alarm_EN[1]);
				break;
        case Ajust_aHour_1:       //闹钟小时    
        case Ajust_aMin_1:        //闹钟分钟   	
					SHOW_Out();
				
					Alarm_Time_Set(Alarm_UI_1,R_aHour[1], R_aMin[1]);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				break;
        case Ajust_aSnoozeDays_1: //响闹天数设置
					SHOW_Out();
					
					AlarmPoint2 = 1;
					Alarm_Fate_UI(R_Alarm_Days[1]);
				
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
//					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
        break;    
	/******************************************************/
     
				case Ajust_Alarm_2:
					
					Alarm_Onoff(Alarm_EN[2]);
				break;
        case Ajust_aHour_2:       //闹钟小时    
        case Ajust_aMin_2:        //闹钟分钟   
					SHOW_Out();
				
					Alarm_Time_Set(Alarm_UI_2,R_aHour[2], R_aMin[2]);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
//					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				break;
        case Ajust_aSnoozeDays_2: //响闹天数设置
					SHOW_Out();
					
					AlarmPoint3 = 1;
					Alarm_Fate_UI(R_Alarm_Days[2]);
				
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // 显示时间
				
					Week_UI(R_Week);									 // 显示星期
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
				
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
        break;    

				
				case Ajust_Light_UI:
				break;
	/******************************************************/
				case Ajust_Music_SIZE_UI:
				
					SHOW_Out();
				
					
					Music_SIZE_UI(Music_Size);
					
					Alarm_Show_Switch();							 // 显示闹钟
					Week_UI(R_Week);									 // 显示星期
				
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				
				
					Music_SIZE_UI(Music_Size);
				break;
	/******************************************************/
				case Ajust_Music_INDEX_UI:
					SHOW_Out();
					Music_Index_UI(Music_Index);
					
					Alarm_Show_Switch();							 // 显示闹钟
					Week_UI(R_Week);									 // 显示星期
				
					Month_Day_UI(R_Month, R_Day); 		 // 显示月日
					Temperature_UI(temperature);			 // 温度
					Humidity_UI(humidity);									 // 湿度
				
				
				break;
				case Ajust_YEJIAN_UI:
					
				break;
				case Ajust_Down_Time_UI:
				case Ajust_Down_Time_Ahour:
				case Ajust_Down_Time_Amin:
				case Ajust_Down_Time_Asec:
					Updata_BaseTim(A_cd_hour,A_cd_min,A_cd_sec);
					TIMER_Point = 1;
					
				break;
			
        default:
        break;
    }    
}


/***********************************************************************************************
*函数名 				  ：Down_Key_Action(uint8 AjustIndex,uint8 Min,uint8 Max)
*函数功能描述 		：减参数
*函数参数 				：AjustIndex，Min，Min
*函数返回值 			：I 
***********************************************************************************************/
void  Down_Key_Action(unsigned char *Ajustdata,unsigned char Min,unsigned char Max)
{
	if((*Ajustdata)<=Min)
	{
			(*Ajustdata)=Max;
		   return;
	}
	(*Ajustdata)-=1;
}
/***********************************************************************************************
*函数名 				  ：Up_Key_Action(uint8 AjustIndex,uint8 Min,uint8z Max)
*函数功能描述 		：加参数
*函数参数 				：AjustIndex，Min，Min
*函数返回值 			：I 
***********************************************************************************************/
void  Up_Key_Action(unsigned char *Ajustdata,unsigned char Min,unsigned char Max)
{

	if((*Ajustdata)>Max-1)
	{
		(*Ajustdata)=Min;
		return;
	}		
		(*Ajustdata)+=1;
}
/***********************************************************************************************
* 旋钮/按键调节统一入口
***********************************************************************************************/
void Get_Add_Action(void)
{
    /*―――――局部变量必须放在最前面―――――*/
    unsigned char  min  = 0;
    unsigned char  max  = 0;
    unsigned char idata *pbuf = 0;

    /*―――――前置判断―――――*/
    if (!Servant_Page_State) return;
    B_FlashData = 0;
		Night_Mode_Delay = 0;
    /*―――――根据界面定位被调节的变量 & 上下限―――――*/
    switch (Servant_Page_State)
    {
    /* 日期 / 时间 *************************************************************/
    case Ajust_aYear:  
//			min = 0;  
				max = 99;  
				pbuf = &R_Year;      
		break;
    case Ajust_aMonth: 
				min = 1;  
				max = 12;
				pbuf = &R_Month;     
		break;
    case Ajust_aDay:   
				min = 1; 
				max = month_day(R_Year, R_Month); 
				pbuf = &R_Day; 
		break;
    case Ajust_Hour:  
//				min = 0;  
				max = 23;
				pbuf = &R_Hour;     
		break;
    case Ajust_Min:    
//				min = 0;  
				max = 59; 
				pbuf = &R_Min; 
				R_Sec = 0;
		break;

    case Ajust_12_24:  /* 12/24?制直接翻转 */
        Switch_Layout ^= 1;
        Dis_FlashMenu();
        return;

    /* 闹钟 0 1 2 */
    case Ajust_aHour:         
				pbuf = &R_aHour[0];      
				goto Ahour_ADJ;
    case Ajust_aHour_1:     
				pbuf = &R_aHour[1];  
				goto Ahour_ADJ;
    case Ajust_aHour_2:          
				pbuf = &R_aHour[2];   
		Ahour_ADJ:
//				min = 0;  
				max = 23;         
		break;
    case Ajust_aMin:    
				pbuf = &R_aMin[0];    
				goto Amin_ADJ;
    case Ajust_aMin_1:  
				pbuf = &R_aMin[1];
				goto Amin_ADJ;
    case Ajust_aMin_2:
				pbuf = &R_aMin[2];
		Amin_ADJ:
//				min = 0; 
				max = 59; 
		break;
    case Ajust_aSnoozeDays:   
				pbuf = &R_Alarm_Days[0];
				goto ASnoozeDays_ADJ;
    case Ajust_aSnoozeDays_1: 
				pbuf = &R_Alarm_Days[1];
				goto ASnoozeDays_ADJ;
    case Ajust_aSnoozeDays_2: 
				pbuf = &R_Alarm_Days[2];
		ASnoozeDays_ADJ:
//				min = 0;  
				max = 2;     
		break;

    /* 倒计时  *******************************************************************/
//    case Ajust_Down_Time_Ahour:       
//			min = 0;  max = 199; pbuf = &cd_min;        
//				
//		break;
//    case Ajust_Down_Time_Amin:
//			min = 0;  max = 59;  pbuf = &cd_sec;   
//		break;

    /* 只读界面 – 直接返回 ******************************************************/
    case Alarm_UI:
    case Alarm_UI_1:
    case Alarm_UI_2:
    case Ajust_Alarm:
    case Ajust_Alarm_1:
    case Ajust_Alarm_2:
		case Ajust_Down_Time_UI:
        return;

    /* 音量大小 ***************************************************************/
    case Ajust_Music_SIZE_UI:
        if (encider_direction == UP && Music_Size < 2)       ++Music_Size;
        else if (encider_direction == DOWN && Music_Size > 0) --Music_Size;
        Play_Music_Size(Music_Size);
        Play_Music(Music_Index - 1);
        Dis_FlashMenu();
        return;

    /* 曲目选择 ***************************************************************/
    case Ajust_Music_INDEX_UI:
        min = 1;  max = 38;  pbuf = &Music_Index;
        if (encider_direction == UP)        Up_Key_Action (pbuf, min, max);
        else if (encider_direction == DOWN) Down_Key_Action(pbuf, min, max);
        Play_Music(Music_Index - 1);
        Dis_FlashMenu();
        return;

    default:
        return;
    }

    /*―――――实际加/减动作―――――*/
    if (encider_direction == UP)        Up_Key_Action (pbuf, min, max);
    else if (encider_direction == DOWN) Down_Key_Action(pbuf, min, max);
	
		if(Servant_Page_State == Ajust_Hour)
		{
//			AutoBrightness_Service();//手动调整时间时，会根据时间调整亮度，当然只有在未调整过亮度的条件下，如果调整过亮度，就要第二天
		}
    /*―――――日期合法性检查―――――*/
    if (Servant_Page_State >= Ajust_aYear && Servant_Page_State <= Ajust_aDay)
    {
        unsigned int idata days;

        days = leap(2000 + R_Year)
             ? (R_Month == 2 ? 29 : ((R_Month == 4 || R_Month == 6 || R_Month == 9 || R_Month == 11) ? 30 : 31))
             : (R_Month == 2 ? 28 : ((R_Month == 4 || R_Month == 6 || R_Month == 9 || R_Month == 11) ? 30 : 31));

        if (R_Day > days) R_Day = (unsigned char)days;
        R_Week = CaculateWeekDay(R_Year, R_Month, R_Day);
    }
//		if(Servant_Page_State ==Ajust_Down_Time_Amin || Servant_Page_State == Ajust_Down_Time_Ahour )
//		{
//			A_cd_min=cd_min;
//			A_cd_sec=cd_sec;
//		}
    Dis_FlashMenu();
} 


/*--------------------------------------------------------------
 * mode = 0 ─ 进入贪睡      (Into_Sleep)
 * mode = 1 ─ 贪睡醒来      (Off_SleepIng)
 * mode = 2 ─ 直接停闹钟    (Off_Sleep)
 * 返回: 至少有 1 个闹钟被处理 → 1，否则 0
 *-------------------------------------------------------------*/
bit alarm_core(uint8 mode)
{
    uint8 i;
    bit   active = 0;

    /* -------- 1) 逐通道扫描 -------- */
    for (i = 0; i < 3; ++i) {
        if (mode == 0) {                     /* Into_Sleep */
            if (Alerm_ON[i]) {
                R_Tsleep[i] = 1;             /* 开启贪睡 */
                Alerm_ON[i] = 0;
                active = 1;
            }
        } else {                             /* Off_SleepIng / Off_Sleep */
            if ((mode == 1 ? R_Tsleep[i]     /* 贪睡中断醒 */
                           : Alerm_ON[i]))   /* 正在响闹 */
                active = 1;

            /* 统一清零 */
            Alerm_ON[i] = 0;
            R_Tsleep[i] = 0;
        }
    }

    /* -------- 2) 公共收尾动作 -------- */
    if (active) {
        Alarm_Sleep_Timer = 0;
        SleepPoint        = 0;
        if (mode != 1)                     /* 非贪睡醒来需停音乐 */
            Music_Stop();
    }
    return active;
}




bit off_Timer()
{
	if(Timer_Alarm_On)
	{
		Timer_Alarm_On = 0;
		Alarm_Sleep_Timer = 0;
		Music_Stop();//关闭闹铃
		Servant_Page_State=Time_UI;
		Dis_FlashMenu();
		return 1;
	}
	return 0;
}
/**************************判断闹钟响闹****************************/
//闹钟判断。闹铃响闹时间，贪睡时间
void ON_Music(unsigned char index);
void Alerm_Action(unsigned char index)
{
	if(!Alarm_EN[index])return;//不进入闹钟检测
	if(Servant_Page_State== Ajust_Light_UI || Servant_Page_State== Time_UI || Servant_Page_State== Ajust_Music_INDEX_UI || 
		Servant_Page_State== Ajust_Music_SIZE_UI|| Servant_Page_State== 26|| Servant_Page_State== 27|| Servant_Page_State== 28)
	{
		/*************判断是否有闹铃响闹****************/	
		if(Alerm_ON[index])
		{
			Alarm_Sleep_Timer++;
			if(Alarm_Sleep_Timer>=1)//响闹1min
			{
			
				Alarm_Sleep_Timer = 0;
				//有关闭闹钟
				Off_Sleep();
				
			}
			return;
		}
		/*************判断是否有闹铃响闹****************/	
		if(R_Tsleep[index])
		{
			Alarm_Sleep_Timer++;
			if(Alarm_Sleep_Timer>=1)//贪睡5min
			{
				Alarm_Sleep_Timer = 0;
				goto xiangnao;
			}
		}

		/*************判断是否处于对应的星期****************/	
		if(!R_Alarm_Days[index])
		{
			if(R_Week == 5 || R_Week == 6)//1-5
				return;
		}
		else if(R_Alarm_Days[index] == 1)//1-6
		{
			if( R_Week == 6)
				return;
		}

		if((R_Hour)!=R_aHour[index] || R_Min!=R_aMin[index]) return;
		xiangnao:	
		Stop_rouse = index;
		if(AutoStop_Time)
		ON_Music(index);
	}
}
void ON_Music(unsigned char index)
{
	Timer_Alarm_On =1;//暂时屏蔽，用于关闭倒计时响闹
			off_Timer();
		B_Counting = 0; //倒计时关闭
		R_Tsleep[0] = 0;
		R_Tsleep[1] = 0;
		R_Tsleep[2] = 0;

		Music_PlayLoop(Music_Index-1);
	
		Alerm_ON[0] = 0;//关闭闹钟
		Alerm_ON[1] = 0;//关闭闹钟
		Alerm_ON[2] = 0;//关闭闹钟
		Alerm_ON[index] = 1;//开启闹钟
}

///**************************自动退出设置****************************/
void AutoSave_Quit(void)
{
	if(!Servant_Page_State)
	{
		AutoSave_Time = 0;
		return;
	}
//	if(Timer_Alarm_On || B_Counting)
//	{
//		AutoSave_Time = 0;
//		return;
//	}
	AutoSave_Time++;
	if(AutoSave_Time>10)
	{
		
		AutoSave_Time = 0;
		//退出设置界面
		Servant_Page_State=0;
		Dis_FlashMenu();
		B_FlashData = 0;
		B_Base500MS = 0;
		
//		B_Counting = 0;
		//Get_BaseTim(R_Hour,R_Min);	
	}
} 




///*-------------------------------------------------
// * Night_Mode_Service()
// *  每 60?s 调一次足够，也可以更频繁
// *------------------------------------------------*/
//void Night_Mode_Service(void)
//{
//    
//    if (Night_Mode) {    //夜间模式开启
//			Night_Mode_Time = 120;
//        return;
//    }
//		if(Night_Mode_Time)Night_Mode_Time--;
//		if(Night_Mode_Time)return;
//		Night_Mode = 1;//开启夜间模式
//}
///*-------------------------------------------------
// * AutoBrightness_Service()
// *  每分钟调用一次即可（成本极低）
// *------------------------------------------------*/
//void AutoBrightness_Service(void)
//{
//    unsigned char target;
//    /* ① 低电状态时禁止自动调光 */
////    if (B_PowerLock) return;              /* 你的低电锁变量 */

//    /* ② 当天已手动调光则跳过 */
//    if (Brightness_Manual_Flag) return;

//    /* ③ 计算目标亮度 */
//    if (R_Hour >= 23 || R_Hour < 7)      target = 0;   /* 23-06 */
//    else if (R_Hour >= 19)               target = 1;   /* 19-22 */
//    else 
//		{			
//			if(!B_PowerLock)
//			target = 3;   /* 07-18 */
//		}
//    /* ④ 与当前不同才调整（避免多余 PWM 更新） */
//    if (Brightness_level != target)
//    {
//        Brightness_level = target;
//        Light_adj_fun(target);
//    }
//}



/* 1 秒服务函数 —— 放到 1 s 定时中断里调用 */
void CD_Service_1s(void)
{
    if (B_Counting==1)
		{
			if (A_cd_sec == 0) {
					if (A_cd_min == 0) {
							B_Counting = 0;                    // 计时完毕
							
							Timer_Alarm_On = 1;
							Music_PlayLoop(Music_Index-1);
							Night_Mode_Delay = 0;
							Dis_FlashMenu();
							return;
					}
					A_cd_min--;
					A_cd_sec = 59;
			} else {
					A_cd_sec--;
			}
		}

}

void OFF_Down_Time()
{
	if(!Timer_Alarm_On)
		return;
		Alarm_Sleep_Timer++;
		if(Alarm_Sleep_Timer>=120)
		{
		
			Alarm_Sleep_Timer = 0;
			//有关闭闹钟
			off_Timer();
		}
}

