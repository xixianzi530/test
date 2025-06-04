#include "include.h"

/***********************��ʾ**********************************/
unsigned char Hour_Hig;  		//Сʱʮλ 
unsigned char Hour_Low;  		//Сʱ��λ
unsigned char Min_Hig;   		//����ʮλ 
unsigned char Min_Low;   		//���Ӹ�λ
unsigned char Sec_Hig;   		//��ʮλ
unsigned char Sec_Low;   		//���λ
unsigned char Month_Hig; 		//��ʮλ
unsigned char Month_Low; 		//�¸�λ
unsigned char Day_Hig;	 		//��ʮλ
unsigned char Day_Low;	 		//�ո�λ
unsigned char Al_Hour_Hig;  //����Сʱʮλ 
unsigned char Al_Hour_Low;  //����Сʱ��λ
unsigned char Al_Min_Hig;   //���ӷ���ʮλ 
unsigned char Al_Min_Low;   //���ӷ��Ӹ�λ
unsigned char Temp_Hig;  		//�¶�ʮλ 
unsigned char Temp_Low;  		//�¶ȸ�λ
unsigned char Hum_Hig; 		  //ʪ��ʮλ 
unsigned char Hum_Low; 		  //ʪ�ȸ�λ
unsigned char Well_s;
bit AmPoint; 								//am
bit PmPoint; 								//pm
bit TIMER_Point;						//Timer ��
bit SleepPoint;							//̰˯
bit SecPoint;	 							//���
bit COL2_Point;	 						//col2
bit BAT_Point;							//BAAT
bit AlarmPoint1;						//����1
bit AlarmPoint2;						//����2
bit AlarmPoint3;						//����3
bit COL3_Point;	 						//col3
bit Hum_Point;	 						//Hum
bit C_Point;	 							//C
bit Temp_Point;							//TEMP 
bit BaiFenHao_Point;				//�ٷֺ� 
bit Option_Point;//
bit M_Point;//
bit D_Point;


unsigned char Servant_Page_State; //��ʾָ�룬���ڵ�ǰ��ʾ�Ǹ�ҳ��
/**************************������-ʱ����-����-����*******************************/
unsigned char idata R_Hour;                  //Сʱ
unsigned char idata R_Min ;                  //����
unsigned char idata R_Sec;                   //��

unsigned char idata R_Year;                  //��
unsigned char idata R_Day ;                  //��
unsigned char idata R_Month;                 //��
unsigned char idata R_Week;                  //����

unsigned char idata R_aHour[3];              //����Сʱ
unsigned char idata R_aMin[3];               //���ӷ���
unsigned char idata R_Alarm_Days[3];         //������������

unsigned char idata Alarm_EN[3];             //���ӿ���
unsigned char idata Alerm_ON[3];             //��������״̬��־λ
unsigned char idata R_Tsleep[3] ;            //̰˯



bit B_FlashData;											 //��˸��־λ�����ڸ�����˸
bit Switch_Layout;                     //1 24Сʱ 0 12Сʱ

unsigned char AutoSave_Time ;					 //�Զ��˳����ý���
unsigned char AutoStop_Time ;					 //����͹���ʱ��


/* ==== ����/ʱ��ѭ����ʾ���� =================================== */
unsigned char ShowDateNow;             // 0=��ʾʱ�� 1=��ʾ���� 2 = �¶�
unsigned char CycleCnt;                // ��������� 10 �л�һ��
/* ============================================================== */


/**************************������Ŀ-��������*******************************/
unsigned char Music_Index;             //��ǰ��Ŀ
unsigned char Music_Size;              //������С



/**************************ҹ��ģʽ���*******************************/
unsigned char Night_Mode;            //1ҹ��ģʽ��0����ģʽ������������ģʽ��2Сʱ����Զ��л���ҹ��ģʽ������ʡ��
unsigned char Night_Mode_Delay;			//�������ֵ����0ʱ��ˢ�º�����ֹͣ���£�Ϊ0ʱ��ˢ�º����Զ����£��л���ԭ������ʾ����


/*****************************�Զ������������****************************/
//bit     Brightness_Manual_Flag = 0;   /* �������ֶ��������� */


/*****************************�����������****************************/
idata unsigned int Alarm_Sleep_Timer = 0;	//��������and̰˯ʱ��
unsigned char idata Stop_rouse = 0;				//���ڵ͹��Ļ��Ѻ��������ӣ���Ϊ��������Э����ʹ��timer2���ģ�

/*****************************����ʱ���****************************/
unsigned char cd_hour  = 0;  				 /* 0-99 */
unsigned char cd_min  = 5;  				 /* 0-59 */
unsigned char cd_sec;  							 /* 0-59  */
unsigned char A_cd_hour  = 0;  				 /* 0-99 */
unsigned char A_cd_min  = 5; 				 /* 0-59 */
unsigned char A_cd_sec;  						 /* 0-59  */
unsigned char idata  B_Counting;     /* 1 = ���ڵ���ʱ 2 = ����ʱ��ͣ 0 = δ����*/

bit Timer_Alarm_On;									 //����ʱ������ʼ����


///*���������������� �ⲿ�ӿڣ��û��Լ�ʵ�֣� ����������������*/
////extern void Alarm_Start(void);                                // ����ʱ�����󴥷�����
//void Refresh_Countdown_UI(unsigned char m, unsigned char s);   // ��ѡ��ˢ����ʾ


//bit Timer_Alarm_On;
//void CD_Service_1s(void);



///****************************************************************************************************************/

/* ���������� �Զ��������״̬ ���������� */
unsigned int  Night_Mode_Time; 			//���ڼ�¼���ڴ��ڳ���ģʽ��ʱ�䣬����¼120����


void TimeKeeping_Fun();							 //1s��ʱ����

//void OFF_Down_Time();
void ClrDis_FlashMenu(void);//��ʾ������
void Dis_FlashMenu(void);   //��ʾ������
void Updata_BaseTim(unsigned char  Hdata,unsigned char  Mdata,unsigned char Sdata);
//void Alarm_Fate_FUN(unsigned char index);
void AutoSave_Quit(void);
void Alerm_Action(unsigned char index);//�����жϺ���
//void Night_Mode_Service(void);

//void AutoBrightness_Service(void);


void ShowData_Init_UpData()
{
	R_Hour = 12;
	R_Min = 0;
	R_Sec = 40;
	
	R_Year = 25;//0Ĭ��Ϊ24��
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
	 
	 
	Music_Index = 1;															 //����ѡ���һ��
	Music_Size = 2; 															 //���������м䵲
	R_Week = CaculateWeekDay(R_Year,R_Month,R_Day);//�������õ������գ����������
	Switch_Layout = 1;														 //24Сʱ
//	Brightness_level = 3;												 //����-���ﲻ��ִ�У��״��ϵ��ʱ�򣬻���ic���磬���ݵ�ѹ����������
	Light_adj_fun(Brightness_level);							 //��������
//	DOT2_Point = 1;                              //
	Night_Mode = 1;                                //����ģʽ����

	B_Base500MS = 1;
	AutoStop_Time = 15;                            //���ڹر���ʾ�ļ�ʱ���ϵ�Ĭ������15s
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
	
/* === �����˸�߼� ================================= */
//    if (P06)                    /* �Ѳ� DC */
//    {
//        if (!P05)               /* ����� �� 0.5 s ��˸ */
//        {
//            BAT_Point = B_FlashData;   /* ����������˸λ */
//        }
//        else                    /* �ѳ��� �� Ϩ�� */
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

//	CD_Service_1s();	//����ʱ����
//	OFF_Down_Time();//�Զ��رյ���ʱ����
	AutoSave_Quit();//�Զ��˳�����
	if(Night_Mode_Delay)	Night_Mode_Delay--;
//	if(AutoStop_Time)			AutoStop_Time--;//����͹���
	i = Timer_Add();
	switch(i)
	{
		case 3://������1
//			Brightness_Manual_Flag = 0;      /* �µ�һ�죬�ָ��Զ����� */

			Updata_YearData();//����������
		
		case 1://���Ӽ�1
		case 2://Сʱ��1
			Alerm_Action(0);
			Alerm_Action(1);
			Alerm_Action(2);
//			Night_Mode_Service();
			R_Week = CaculateWeekDay(R_Year,R_Month,R_Day);//��������
//			AutoBrightness_Service();

		break;
	}
	
}

void SHOW_Out(void)
{
	Hour_Hig       = 10  ;  		//Сʱʮλ 
	Hour_Low       = 10  ;   		//Сʱ��λ
	Min_Hig        = 10  ;   		//����ʮλ 
	Min_Low        = 10  ;   		//���Ӹ�λ
	Sec_Hig        = 10  ;   		//��ʮλ
	Sec_Low        = 10  ;   		//���λ
	Month_Hig      = 0  ; 		//��ʮλ
	Month_Low      = 10  ; 		//�¸�λ
	Day_Hig        = 10  ;	 		//��ʮλ
	Day_Low        = 10  ;	 		//�ո�λ
	Al_Hour_Hig    = 10  ;  //����Сʱʮλ 
	Al_Hour_Low    = 10  ;  //����Сʱ��λ
	Al_Min_Hig     = 10  ;   //���ӷ���ʮλ 
	Al_Min_Low     = 10  ;   //���ӷ��Ӹ�λ
	Temp_Hig       = 10  ;  		//�¶�ʮλ 
	Temp_Low       = 10  ;  		//�¶ȸ�λ
	Hum_Hig        = 10  ; 		  //ʪ��ʮλ 
	Hum_Low        = 10  ; 		  //ʪ�ȸ�λ
	Well_s         = 10  ;
	AmPoint        = 0  ; 								//am
	PmPoint        = 0  ; 								//pm
	TIMER_Point    = 0  ;						//Timer ��
	SleepPoint     = 0  ;							//̰˯
	SecPoint       = 0  ;	 							//���
	COL2_Point     = 0  ;	 						//col2
	BAT_Point      = 0  ;							//BAAT
	AlarmPoint1    = 0  ;						//����1
	AlarmPoint2    = 0  ;						//����2
	AlarmPoint3    = 0  ;						//����3
	COL3_Point     = 0  ;	 						//col3
	Hum_Point      = 0  ;	 						//Hum
	C_Point        = 0  ;	 							//C
	Temp_Point     = 0  ;							//TEMP 
	BaiFenHao_Point= 0  ;				//�ٷֺ� 
	Option_Point   = 0  ;//
	M_Point        = 0  ;//
	D_Point        = 0  ;
}

/**************************����Сʱ����****************************/
/**************************����Сʱ�ͷ���****************************/
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
		Sec_Hig = 10;   		//��ʮλ
		Sec_Low = 10;   		//���λ
		SecPoint = 1;
		COL2_Point = 0;
    // ֻ�ںϷ���Χ�ڸ���Сʱ
    if (Hdata < 200) {
        if (Hdata >= 10) {
            Hour_Hig = Hdata / 10;   // ʮλ
        }
        Hour_Low = Hdata % 10;       // ��λ
    }

    // ֻ�ںϷ���Χ�ڸ��·���
    if (Mdata < 60) {
        Min_Hig = Mdata / 10;       // ʮλ
        Min_Low = Mdata % 10;       // ��λ
    }
		
		 if (Sdata < 60) {
				COL2_Point = 1;
        Sec_Hig = Sdata / 10;       // ʮλ
        Sec_Low = Sdata % 10;       // ��λ
    }
}
   

/**************************12/24Сʱ����****************************/
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

/**************************����ʾ����****************************/
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
/**************************�·���ʾ����****************************/
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
/**************************������ʾ����****************************/
void Week_UI(unsigned char Week_Tmp)
{
	Well_s = 10;
	if(Week_Tmp >200)return;
	Well_s = Week_Tmp;
}

   
/**************************�¶���ʾ����****************************/

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
/**************************ʪ����ʾ����****************************/

void Humidity_UI(char Hum) 
{
	
		Hum_Point = 1;
		BaiFenHao_Point = 1;
		C_Point = 1;
		Hum_Hig = abs(Hum) / 10;
		Hum_Low = abs(Hum) % 10;


}

/**************************������ʾ����****************************/

void Updata_Alarm_UI(unsigned char  AHdata,unsigned char  AMdata)
{
    Al_Hour_Hig = 10;
    Al_Hour_Low = 10;
    Al_Min_Hig = 10;
    Al_Min_Low = 10;

    // ֻ�ںϷ���Χ�ڸ���Сʱ
    if (AHdata < 200) {
        if (AHdata >= 10) {
            Al_Hour_Hig = AHdata / 10;   // ʮλ
        }
        Al_Hour_Low = AHdata % 10;       // ��λ
    }

    // ֻ�ںϷ���Χ�ڸ��·���
    if (AMdata < 60) {
        Al_Min_Hig = AMdata / 10;       // ʮλ
        Al_Min_Low = AMdata % 10;       // ��λ
    }
		
}
///**************************���ӽ���****************************/

//����ͼ����ʾ
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


///************************** ҹ�俪�� **************************/
void YeJian_Onoff(bit state)
{
	AmPoint        = 0  ; 								//am
	PmPoint        = 0  ; 								//pm
	TIMER_Point    = 0  ;						//Timer ��
	SleepPoint     = 0  ;							//̰˯
	SecPoint       = 0  ;	 							//���
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

/************************** ���ӿ�/�� ****************************/
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

    /* ������Ӧ����ָʾ�� */
    if      (ui == Alarm_UI)   AlarmPoint1 = 1;
    else if (ui == Alarm_UI_1) AlarmPoint2 = 1;
    else if (ui == Alarm_UI_2) AlarmPoint3 = 1;
    else                       return;                /* �Ƿ���� */

		COL3_Point = 1;
		Updata_Alarm_UI(ahour, amin);

}

///**************************������������ѡ��****************************/
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


///**************************����ѡ��****************************/



/**************************��������ѡ��****************************/
void Music_SIZE_UI(unsigned char index )
{

	
	Hour_Hig = 10;
	Hour_Low = 20;
	Min_Hig = 0;
	Min_Low = index+1;
}
/**************************����ѡ��****************************/
void Music_Index_UI(unsigned char index )
{ 
	
	Hour_Hig = 10;
	Hour_Low = 22; 
	Min_Hig = index/10;
	Min_Low = index%10;
}	


/**************************��ʾ����-��****************************/
void ClrDis_FlashMenu(void)
{
	if(Night_Mode_Delay)return;
    switch (Servant_Page_State) 
    {       
        case Time_UI:        // ������ʾ
				SleepPoint = 0;
				if(Alerm_ON[0])
					AlarmPoint1 = 0;
				else if(Alerm_ON[1])
					AlarmPoint2 = 0;
				else if(Alerm_ON[2])
					AlarmPoint3 = 0;
				break;
        case Ajust_aYear:       //��   
            Year_UI(0xff);
//					Alarm_Show_Switch();//���� 

				
        break;
        case Ajust_aMonth:      //��   
					Month_Day_UI(0xff,R_Day);//������ʾ 
//					Alarm_Show_Switch();//���� 
        break; 
        case Ajust_aDay:        //��   
					Month_Day_UI(R_Month,0xff);//������ʾ 
//					Alarm_Show_Switch();//���� 
        break;    
	
				case Ajust_12_24:
					fun_12_24_UI(0xff);
//					Alarm_Show_Switch();//���� 
				break;
        case Ajust_Hour:    //Сʱ����
					Get_BaseTim(0xff,R_Min,0xff);
        break;
        case Ajust_Min:     //��������    
					Get_BaseTim(R_Hour,0xff,0xff);
        break;

/***************************************************/
        case Alarm_UI:            //����               
					                                         
				break;					
				case Ajust_Alarm://���ӿ��ؽ���
					Alarm_Onoff(0xff);
				break;
				
        case Ajust_aHour:         //����Сʱ    
					Alarm_Time_Set(Alarm_UI,0xff, R_aMin[0]);
				break;
        case Ajust_aMin:          //���ӷ��� 
					Alarm_Time_Set(Alarm_UI,R_aHour[0], 0xff);   
				break;
        case Ajust_aSnoozeDays:   //������������
					Alarm_Fate_UI(0xff);
        break;        

/***************************************************/
        case Alarm_UI_1:          //����
        break;
				case Ajust_Alarm_1:
					Alarm_Onoff(0xff);
					
				break;
        case Ajust_aHour_1:       //����Сʱ   
					Alarm_Time_Set(Alarm_UI_1,0xff, R_aMin[1]); 
				break;
        case Ajust_aMin_1:        //���ӷ���   
					Alarm_Time_Set(Alarm_UI_1,R_aHour[1], 0xff);  
				break;
        case Ajust_aSnoozeDays_1: //������������
					Alarm_Fate_UI(0xff);
		
        break;    

/***************************************************/
				case Alarm_UI_2:          //����
        break;
				case Ajust_Alarm_2:
					Alarm_Onoff(0xff);
					
				break;
        case Ajust_aHour_2:       //����Сʱ 
					Alarm_Time_Set(Alarm_UI_2,0xff, R_aMin[2]); 
				break;   
        case Ajust_aMin_2:        //���ӷ���   
					Alarm_Time_Set(Alarm_UI_2,R_aHour[2], 0xff);  
				break;
        case Ajust_aSnoozeDays_2: //������������
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
        case Time_UI:        // ������ʾ
					SHOW_Out();
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
					
					Alarm_Show_Switch();							 // ��ʾ����
					Week_UI(R_Week);									 // ��ʾ����
				
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
					if(R_Tsleep[0]||R_Tsleep[1]||R_Tsleep[2])
					{
						SleepPoint = 1;
					}
				break;
        case Ajust_aYear:       //��    
					SHOW_Out();
					Year_UI(R_Year);
				
				
					Alarm_Show_Switch();							 // ��ʾ����
					Week_UI(R_Week);									 // ��ʾ����
				
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				
        break;
        case Ajust_aMonth:      						 //��    
        case Ajust_aDay:        						 //��   
					SHOW_Out();
					Month_Day_UI(R_Month, R_Day);  		 // ��ʾ����
				
					Week_UI(R_Week);									 // ��ʾ����
					Alarm_Show_Switch();							 // ��ʾ����
					Get_BaseTim(R_Hour,R_Min,0xff);		 // ��ʾʱ��
					
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
        break;    
	
				case Ajust_12_24:
					SHOW_Out();
					fun_12_24_UI(Switch_Layout);
				
				
					Month_Day_UI(R_Month, R_Day);  		 // ��ʾ����
					Week_UI(R_Week);									 // ��ʾ����
					Alarm_Show_Switch();							 // ��ʾ����
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				break;
        case Ajust_Hour:    //Сʱ����
        case Ajust_Min:     //��������   
					SHOW_Out();
					Get_BaseTim(R_Hour,R_Min,0xff);
				
				
					
					
					Alarm_Show_Switch();							 // ��ʾ����
					Week_UI(R_Week);									 // ��ʾ����
				
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				
        break;
/***************************************************/
        case Alarm_UI:            //���� 1
				case Alarm_UI_1:          //���� 2
				case Alarm_UI_2:          //���� 3
					SHOW_Out();
					COL3_Point = 1;
					Alarm_UI_FUN(Servant_Page_State);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
        break;
				case Ajust_Alarm:
				
					Alarm_Onoff(Alarm_EN[0]);
				break;
        case Ajust_aHour:         //����Сʱ    
        case Ajust_aMin:          //���ӷ���  
					SHOW_Out();
				
					Alarm_Time_Set(Alarm_UI,R_aHour[0], R_aMin[0]);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				
				break;
        case Ajust_aSnoozeDays:   //������������
					
					SHOW_Out();
					
					AlarmPoint1 = 1;
					Alarm_Fate_UI(R_Alarm_Days[0]);
				
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
//					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				
        break;      
				
	/******************************************************/
       	case Ajust_Alarm_1:
					
					Alarm_Onoff(Alarm_EN[1]);
				break;
        case Ajust_aHour_1:       //����Сʱ    
        case Ajust_aMin_1:        //���ӷ���   	
					SHOW_Out();
				
					Alarm_Time_Set(Alarm_UI_1,R_aHour[1], R_aMin[1]);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				break;
        case Ajust_aSnoozeDays_1: //������������
					SHOW_Out();
					
					AlarmPoint2 = 1;
					Alarm_Fate_UI(R_Alarm_Days[1]);
				
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
//					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
        break;    
	/******************************************************/
     
				case Ajust_Alarm_2:
					
					Alarm_Onoff(Alarm_EN[2]);
				break;
        case Ajust_aHour_2:       //����Сʱ    
        case Ajust_aMin_2:        //���ӷ���   
					SHOW_Out();
				
					Alarm_Time_Set(Alarm_UI_2,R_aHour[2], R_aMin[2]);
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
//					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				break;
        case Ajust_aSnoozeDays_2: //������������
					SHOW_Out();
					
					AlarmPoint3 = 1;
					Alarm_Fate_UI(R_Alarm_Days[2]);
				
				
					Get_BaseTim(R_Hour,R_Min,R_Sec);	 // ��ʾʱ��
				
					Week_UI(R_Week);									 // ��ʾ����
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
				
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
        break;    

				
				case Ajust_Light_UI:
				break;
	/******************************************************/
				case Ajust_Music_SIZE_UI:
				
					SHOW_Out();
				
					
					Music_SIZE_UI(Music_Size);
					
					Alarm_Show_Switch();							 // ��ʾ����
					Week_UI(R_Week);									 // ��ʾ����
				
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				
				
					Music_SIZE_UI(Music_Size);
				break;
	/******************************************************/
				case Ajust_Music_INDEX_UI:
					SHOW_Out();
					Music_Index_UI(Music_Index);
					
					Alarm_Show_Switch();							 // ��ʾ����
					Week_UI(R_Week);									 // ��ʾ����
				
					Month_Day_UI(R_Month, R_Day); 		 // ��ʾ����
					Temperature_UI(temperature);			 // �¶�
					Humidity_UI(humidity);									 // ʪ��
				
				
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
*������ 				  ��Down_Key_Action(uint8 AjustIndex,uint8 Min,uint8 Max)
*������������ 		��������
*�������� 				��AjustIndex��Min��Min
*��������ֵ 			��I 
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
*������ 				  ��Up_Key_Action(uint8 AjustIndex,uint8 Min,uint8z Max)
*������������ 		���Ӳ���
*�������� 				��AjustIndex��Min��Min
*��������ֵ 			��I 
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
* ��ť/��������ͳһ���
***********************************************************************************************/
void Get_Add_Action(void)
{
    /*�D�D�D�D�D�ֲ��������������ǰ��D�D�D�D�D*/
    unsigned char  min  = 0;
    unsigned char  max  = 0;
    unsigned char idata *pbuf = 0;

    /*�D�D�D�D�Dǰ���жϨD�D�D�D�D*/
    if (!Servant_Page_State) return;
    B_FlashData = 0;
		Night_Mode_Delay = 0;
    /*�D�D�D�D�D���ݽ��涨λ�����ڵı��� & �����ިD�D�D�D�D*/
    switch (Servant_Page_State)
    {
    /* ���� / ʱ�� *************************************************************/
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

    case Ajust_12_24:  /* 12/24?��ֱ�ӷ�ת */
        Switch_Layout ^= 1;
        Dis_FlashMenu();
        return;

    /* ���� 0 1 2 */
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

    /* ����ʱ  *******************************************************************/
//    case Ajust_Down_Time_Ahour:       
//			min = 0;  max = 199; pbuf = &cd_min;        
//				
//		break;
//    case Ajust_Down_Time_Amin:
//			min = 0;  max = 59;  pbuf = &cd_sec;   
//		break;

    /* ֻ������ �C ֱ�ӷ��� ******************************************************/
    case Alarm_UI:
    case Alarm_UI_1:
    case Alarm_UI_2:
    case Ajust_Alarm:
    case Ajust_Alarm_1:
    case Ajust_Alarm_2:
		case Ajust_Down_Time_UI:
        return;

    /* ������С ***************************************************************/
    case Ajust_Music_SIZE_UI:
        if (encider_direction == UP && Music_Size < 2)       ++Music_Size;
        else if (encider_direction == DOWN && Music_Size > 0) --Music_Size;
        Play_Music_Size(Music_Size);
        Play_Music(Music_Index - 1);
        Dis_FlashMenu();
        return;

    /* ��Ŀѡ�� ***************************************************************/
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

    /*�D�D�D�D�Dʵ�ʼ�/�������D�D�D�D�D*/
    if (encider_direction == UP)        Up_Key_Action (pbuf, min, max);
    else if (encider_direction == DOWN) Down_Key_Action(pbuf, min, max);
	
		if(Servant_Page_State == Ajust_Hour)
		{
//			AutoBrightness_Service();//�ֶ�����ʱ��ʱ�������ʱ��������ȣ���Ȼֻ����δ���������ȵ������£�������������ȣ���Ҫ�ڶ���
		}
    /*�D�D�D�D�D���ںϷ��Լ��D�D�D�D�D*/
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
 * mode = 0 �� ����̰˯      (Into_Sleep)
 * mode = 1 �� ̰˯����      (Off_SleepIng)
 * mode = 2 �� ֱ��ͣ����    (Off_Sleep)
 * ����: ������ 1 �����ӱ����� �� 1������ 0
 *-------------------------------------------------------------*/
bit alarm_core(uint8 mode)
{
    uint8 i;
    bit   active = 0;

    /* -------- 1) ��ͨ��ɨ�� -------- */
    for (i = 0; i < 3; ++i) {
        if (mode == 0) {                     /* Into_Sleep */
            if (Alerm_ON[i]) {
                R_Tsleep[i] = 1;             /* ����̰˯ */
                Alerm_ON[i] = 0;
                active = 1;
            }
        } else {                             /* Off_SleepIng / Off_Sleep */
            if ((mode == 1 ? R_Tsleep[i]     /* ̰˯�ж��� */
                           : Alerm_ON[i]))   /* �������� */
                active = 1;

            /* ͳһ���� */
            Alerm_ON[i] = 0;
            R_Tsleep[i] = 0;
        }
    }

    /* -------- 2) ������β���� -------- */
    if (active) {
        Alarm_Sleep_Timer = 0;
        SleepPoint        = 0;
        if (mode != 1)                     /* ��̰˯������ͣ���� */
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
		Music_Stop();//�ر�����
		Servant_Page_State=Time_UI;
		Dis_FlashMenu();
		return 1;
	}
	return 0;
}
/**************************�ж���������****************************/
//�����жϡ���������ʱ�䣬̰˯ʱ��
void ON_Music(unsigned char index);
void Alerm_Action(unsigned char index)
{
	if(!Alarm_EN[index])return;//���������Ӽ��
	if(Servant_Page_State== Ajust_Light_UI || Servant_Page_State== Time_UI || Servant_Page_State== Ajust_Music_INDEX_UI || 
		Servant_Page_State== Ajust_Music_SIZE_UI|| Servant_Page_State== 26|| Servant_Page_State== 27|| Servant_Page_State== 28)
	{
		/*************�ж��Ƿ�����������****************/	
		if(Alerm_ON[index])
		{
			Alarm_Sleep_Timer++;
			if(Alarm_Sleep_Timer>=1)//����1min
			{
			
				Alarm_Sleep_Timer = 0;
				//�йر�����
				Off_Sleep();
				
			}
			return;
		}
		/*************�ж��Ƿ�����������****************/	
		if(R_Tsleep[index])
		{
			Alarm_Sleep_Timer++;
			if(Alarm_Sleep_Timer>=1)//̰˯5min
			{
				Alarm_Sleep_Timer = 0;
				goto xiangnao;
			}
		}

		/*************�ж��Ƿ��ڶ�Ӧ������****************/	
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
	Timer_Alarm_On =1;//��ʱ���Σ����ڹرյ���ʱ����
			off_Timer();
		B_Counting = 0; //����ʱ�ر�
		R_Tsleep[0] = 0;
		R_Tsleep[1] = 0;
		R_Tsleep[2] = 0;

		Music_PlayLoop(Music_Index-1);
	
		Alerm_ON[0] = 0;//�ر�����
		Alerm_ON[1] = 0;//�ر�����
		Alerm_ON[2] = 0;//�ر�����
		Alerm_ON[index] = 1;//��������
}

///**************************�Զ��˳�����****************************/
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
		//�˳����ý���
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
// *  ÿ 60?s ��һ���㹻��Ҳ���Ը�Ƶ��
// *------------------------------------------------*/
//void Night_Mode_Service(void)
//{
//    
//    if (Night_Mode) {    //ҹ��ģʽ����
//			Night_Mode_Time = 120;
//        return;
//    }
//		if(Night_Mode_Time)Night_Mode_Time--;
//		if(Night_Mode_Time)return;
//		Night_Mode = 1;//����ҹ��ģʽ
//}
///*-------------------------------------------------
// * AutoBrightness_Service()
// *  ÿ���ӵ���һ�μ��ɣ��ɱ����ͣ�
// *------------------------------------------------*/
//void AutoBrightness_Service(void)
//{
//    unsigned char target;
//    /* �� �͵�״̬ʱ��ֹ�Զ����� */
////    if (B_PowerLock) return;              /* ��ĵ͵������� */

//    /* �� �������ֶ����������� */
//    if (Brightness_Manual_Flag) return;

//    /* �� ����Ŀ������ */
//    if (R_Hour >= 23 || R_Hour < 7)      target = 0;   /* 23-06 */
//    else if (R_Hour >= 19)               target = 1;   /* 19-22 */
//    else 
//		{			
//			if(!B_PowerLock)
//			target = 3;   /* 07-18 */
//		}
//    /* �� �뵱ǰ��ͬ�ŵ������������ PWM ���£� */
//    if (Brightness_level != target)
//    {
//        Brightness_level = target;
//        Light_adj_fun(target);
//    }
//}



/* 1 ������� ���� �ŵ� 1 s ��ʱ�ж������ */
void CD_Service_1s(void)
{
    if (B_Counting==1)
		{
			if (A_cd_sec == 0) {
					if (A_cd_min == 0) {
							B_Counting = 0;                    // ��ʱ���
							
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
			//�йر�����
			off_Timer();
		}
}

