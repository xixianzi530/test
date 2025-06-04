#include 	"include.h"

void Into_HoldState(unsigned char index);
void Into_PressState(unsigned char index);
void Into_RelseState(unsigned char index);
unsigned char Check_Hold_Flag(void);
void Set_Hold_Flag(unsigned int HoldTime);


bit B_KeySCAN = 0;

bit Bit_KeyPress = 0;
bit Bit_KeyReles = 0;
bit Bit_KeyPad = 0;
bit Bit_KeyHold = 0;
unsigned int  R_KeyCode = 0;
unsigned int idata R_KeyValue = 0;
unsigned char idata R_KeyOld = 0;
unsigned char idata R_KeyBuf = 0;

bit Key_Add_Press = 0;
bit Key_Dec_Press = 0;
unsigned int Key_Sustain_Time = 0;
unsigned int R_KeyHoldTimer = 0;


void key_Init()
{
	P3MOD10 = 0x00;						//开漏
//	P14 = 1;
//	P15 = 1;
}

unsigned char get_key(void)
{
	unsigned char index = 0;

	if(!P30)index = 1;
	if(!P31)index = 2;
	if(!P37)index = 3;
	if(P11)index = 4;
	return index;
}
/* ─── 手动关机组合键：Alarm(P37=0) + Set(P11=1) ─── */
unsigned int PowerOffCnt = 0;      /* ms 计数器 */
#define POWEROFF_MS   2000                /* 长按 2 s */
void Key_Scan(void)
{	 												        
	if(!B_KeySCAN) return;
	B_KeySCAN=0;
	
	R_KeyOld=R_KeyBuf;
		
	R_KeyBuf=get_key();		
	if(R_KeyOld!=R_KeyBuf)	return;
	if(Bit_KeyPress)   //按键已经按下过
	{	
		if(R_KeyBuf) return;
		Bit_KeyPress=0;
		Bit_KeyReles=1;	
		return;
	}						
	if(!R_KeyBuf)return;	
	Bit_KeyReles=0;
	Bit_KeyPad=1;
	R_KeyValue = 0;
	if(Bit_KeyPress)return;
	Bit_KeyPress=1;

		AutoStop_Time = 15;
	if(off_Timer())return;
	if(R_KeyBuf == LIGHT_KEY)
	{
		if(Into_Sleep())return;
		if(Off_SleepIng())return;
	}
	else
	{
		AutoSave_Time = 0;
		if(Off_Sleep())return;
		if(Off_SleepIng())return;
	}
	Bit_KeyHold=0;	
	R_KeyValue=R_KeyBuf;
//
}

bit Chk_KeyCode(void)
{
  if(!Bit_KeyPad) return 0;
	Bit_KeyPad=0;
	R_KeyCode=R_KeyValue;			
	return 1; 	
}


void State_Ctrl(void)
{ 
	unsigned char i=0;
	i=Check_Hold_Flag();
	if(i==1)Into_HoldState(R_KeyCode);
	if(i==2)Into_RelseState(R_KeyCode);
	if(!Chk_KeyCode()) return;
	
	Into_PressState(R_KeyCode);
	/* POWEROFF_KEY 要 2 s，其余仍 1 s */
Set_Hold_Flag(R_KeyCode == POWEROFF_KEY ? 2000 : 1000);

}


void Into_HoldState(unsigned char index)
{

	switch (index)
	{

		case ENCODER_KEY:
			if(Servant_Page_State>=Ajust_Down_Time_UI && Servant_Page_State<=Ajust_Down_Time_Amin)
			{
				Servant_Page_State = Time_UI;
				B_Counting = 0;//恢复成默认状态
				
						B_Counting = 0;
//						pb_active = 0;
//						PB_Stop();
			}
			else
			{
				A_cd_min=cd_min;
				A_cd_sec=cd_sec;
				B_Counting = 0;//恢复成默认状态
							Night_Mode_Delay = 0;
				Servant_Page_State = Ajust_Down_Time_Ahour;
//				PB_ALL_ON();
			}
			Dis_FlashMenu();
			break;
			case LIGHT_KEY:
				Night_Mode =!Night_Mode;
				Night_Mode_Delay = 3;
				YeJian_Onoff(Night_Mode);
				
			break;
			case ALlARM_KEY://闹钟按键	
				switch(Servant_Page_State)
				{
					case Alarm_UI:
						B_Counting = 0;
//						pb_active = 0;
//						PB_Stop();
						Servant_Page_State = Ajust_aHour;
							
						Dis_FlashMenu();
					break;
					case Alarm_UI_1:
						Servant_Page_State = Ajust_aHour_1;
							
						Dis_FlashMenu();
					break;
					case Alarm_UI_2:
						Servant_Page_State = Ajust_aHour_2;
							
						Dis_FlashMenu();
					break;
				}
			
			break;

			case SET_KEY://
				switch(Servant_Page_State)
				{
					case Time_UI:	
					case Alarm_UI:
					case Ajust_Alarm:	
					case Ajust_aHour:	
					case Ajust_aMin:		
					case Ajust_aSnoozeDays:
					case Alarm_UI_1 :
					case Ajust_Alarm_1  :
					case Ajust_aHour_1  :
					case Ajust_aMin_1:
					case Ajust_aSnoozeDays_1:
					case Alarm_UI_2:
					case Ajust_Alarm_2:
					case Ajust_aHour_2:	
					case Ajust_aMin_2:
					case Ajust_Down_Time_UI:
					case Ajust_Down_Time_Ahour:
					case Ajust_Down_Time_Amin:
					case Ajust_Music_INDEX_UI:
					case Ajust_Music_SIZE_UI:
						B_Counting = 0;
//						pb_active = 0;
// 						PB_Stop();
						Servant_Page_State = Ajust_aYear;
						Dis_FlashMenu();
					break;
				}
				if(Servant_Page_State)return;
			
			
			break;
	
		default:
			break;	
	}
}	

void Into_PressState(unsigned char index)
{
	switch (index)
	{
		case ENCODER_KEY:
			
			break;
			case LIGHT_KEY:
				
			break;
			case ALlARM_KEY://闹钟按键	
				
			break;

			case SET_KEY://闹钟按键	
			break;
	
		default:
			break;	
	}
}	

	

unsigned char memory_tmp = 0;

/* ────────── 共???具 ────────── */
static void CycleAlarmPage(void)
{
    /*  Alarm_UI → Alarm_UI_1 → Alarm_UI_2 → Time_UI → Alarm_UI … */
    switch (memory_tmp)
    {
        case Alarm_UI:   Servant_Page_State = Alarm_UI_1; memory_tmp = Alarm_UI_1; break;
        case Alarm_UI_1: Servant_Page_State = Alarm_UI_2; memory_tmp = Alarm_UI_2; break;
        case Alarm_UI_2: Servant_Page_State = Time_UI;    memory_tmp = Time_UI;    break;
        default:         Servant_Page_State = Alarm_UI;   memory_tmp = Alarm_UI;   break;
    }
    Dis_FlashMenu();
}

static void ToggleAlarm(unsigned char *en,
                               unsigned char st_alarm,
                               unsigned char st_hour)
{
    *en = !*en;
    Servant_Page_State = *en ? st_hour : st_alarm;
}

void Into_RelseState(unsigned char index)
{
    switch (index)
    {
		case ENCODER_KEY:
		
			if(Servant_Page_State>=Ajust_Down_Time_UI && Servant_Page_State<=Ajust_Down_Time_Asec)
			{
				if(B_Counting == 1)
				{
					
					Servant_Page_State = Time_UI;
					B_Counting = 0;
					Dis_FlashMenu();
					return;
				}
				Servant_Page_State++;
				if(Servant_Page_State>Ajust_Down_Time_Asec)
					Servant_Page_State=Ajust_Down_Time_UI;
				Dis_FlashMenu();
				return;
			}	
			
			break;
/* ======================================================================= */
      case LIGHT_KEY:
//				if(Servant_Page_State == Ajust_Down_Time_UI ||Servant_Page_State == Ajust_Down_Time_Ahour || Servant_Page_State == Ajust_Down_Time_Amin)
//				{
//					switch(B_Counting)
//					{
//						case 0://默认状态，首次进入倒计时界面时为0
//							PB_Init();
//						case 2://倒计时暂停
//							B_Counting = 1;
//						break;
//						case 1://开始倒计时
//							
//							B_Counting = 2;//暂停倒计时
//						break;
//					}
//							PB_Set(pb_idx);      /* 点亮下一颗闪烁 */
//					Servant_Page_State = Ajust_Down_Time_UI;
//					Dis_FlashMenu();
//					return;
//				}
//				Brightness_Manual_Flag = 1;        /* 今天已手动调过亮度 */

        Brightness_level++;
        if (Brightness_level > Brightness_Max) Brightness_level = 0;
        Light_adj_fun(Brightness_level);
        break;


/* ======================================================================= */
    case ALlARM_KEY:
			

		
        switch (Servant_Page_State)
        {
        /* ——— 两个音乐界?共?循环 ——— */
        case Ajust_Music_INDEX_UI:
        case Ajust_Music_SIZE_UI:
        case Time_UI:
						
            Servant_Page_State = Alarm_UI;
				
            break;
        /* ——— Alarm_UI ? Time_UI 四页循环 ——— */
        case Alarm_UI:
            Servant_Page_State = Alarm_UI_1;
				
            break;
        case Alarm_UI_1:
            Servant_Page_State = Alarm_UI_2;
				
            break;
        case Alarm_UI_2:
            Servant_Page_State = Alarm_UI;
				
            break;
					

        /* ——— 闹钟 1 ——— */
        case Ajust_Alarm://闹钟开关
        case Ajust_Alarm_1:
        case Ajust_Alarm_2:
						Servant_Page_State = Time_UI;
				
            break;

        case Ajust_aHour:
        case Ajust_aMin:
        case Ajust_aSnoozeDays:
        case Ajust_aHour_1:
        case Ajust_aMin_1:
        case Ajust_aSnoozeDays_1:
        case Ajust_aHour_2:
        case Ajust_aMin_2:
        case Ajust_aSnoozeDays_2:
            ++Servant_Page_State;
            break;

           
				case Ajust_Down_Time_UI:
				case Ajust_Down_Time_Ahour:
				case Ajust_Down_Time_Amin:
					
					Servant_Page_State = Time_UI;
					B_Counting = 0;
					Dis_FlashMenu();            /* 除?上? return，否则都要刷新 */
				
				break;
        default:
            break;
        }
        Dis_FlashMenu();            /* 除?上? return，否则都要刷新 */
        break;
/* ======================================================================= */
    case SET_KEY:
        switch (Servant_Page_State)
        {
        /* ——— 进?音乐索引设置 ——— */
        case Time_UI:
        case Ajust_Music_SIZE_UI:
        case Alarm_UI:
        case Alarm_UI_1:
        case Alarm_UI_2:
            encider_direction = 110;
            Servant_Page_State = Ajust_Music_INDEX_UI;
            Get_Add_Action();
            return;                 /* ? 保持原来的提前返回 */

        /* ——— 顺序递增的?个界? ——— */
        case Ajust_aYear:
        case Ajust_aMonth:
        case Ajust_aDay:
        case Ajust_12_24:
        case Ajust_Hour:
            ++Servant_Page_State;
            break;

        /* ——— 退出回到 Time_UI ——— */
        case Ajust_Min:
            Servant_Page_State = Time_UI;
				break;
        case Ajust_Music_INDEX_UI:
            Music_Stop();
						if(memory_tmp == Time_UI)
							Servant_Page_State = Time_UI;
						else
							Servant_Page_State = memory_tmp;
            break;

        /* ——— Alarm 1 开关 ——— */
        case Ajust_Alarm:
        case Ajust_aHour:
        case Ajust_aMin:
        case Ajust_aSnoozeDays:
            ToggleAlarm(&Alarm_EN[0], Ajust_Alarm, Ajust_aHour);
            break;

        /* ——— Alarm 2 开关 ——— */
        case Ajust_Alarm_1:
        case Ajust_aHour_1:
        case Ajust_aMin_1:
        case Ajust_aSnoozeDays_1:
            ToggleAlarm(&Alarm_EN[1], Ajust_Alarm_1, Ajust_aHour_1);
            break;

        /* ——— Alarm 3 开关 ——— */
        case Ajust_Alarm_2:
        case Ajust_aHour_2:
        case Ajust_aMin_2:
        case Ajust_aSnoozeDays_2:
            ToggleAlarm(&Alarm_EN[2], Ajust_Alarm_2, Ajust_aHour_2);
            break;

				case Ajust_Down_Time_UI:
				case Ajust_Down_Time_Ahour:
				case Ajust_Down_Time_Amin:
					
					Servant_Page_State = Time_UI;
//					B_Counting = 0;
        Dis_FlashMenu();            /* 除?上? return，否则都要刷新 */
				break;
        default:
            break;
        }
        Dis_FlashMenu();            /* 除?上? return，否则都要刷新 */
        break;

/* ======================================================================= */
    default:
        break;
    }
}



/***********************************************************************************************
*函数名 				：Check_Hold_Flag
*函数功能描述 		: 检测按键状态
*函数参数 			：无 
*函数返回值 			：按键状态 
***********************************************************************************************/
unsigned char Check_Hold_Flag(void)
{
	if(!Bit_KeyHold) return 0;
	if((R_KeyHoldTimer==0)&&(Bit_KeyReles==0))	 //长按
	{
		 Bit_KeyHold=0;	
		 return 1;
	}
	if(Bit_KeyReles)							//短按
	{
		 Bit_KeyHold=0;
		 R_KeyHoldTimer=0;	
		 Bit_KeyReles=0;
		 return 2;
	}	 			  
	return 0;
}
///---------------------------------------------------------------------------------------
void Set_Hold_Flag(unsigned int HoldTime)
{
	R_KeyHoldTimer=HoldTime;
	Bit_KeyHold=0;
	if(HoldTime)Bit_KeyHold=1;
}
