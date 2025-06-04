#ifndef _calednar_C_
#define _calednar_C_
#include 	"include.h"



int leap (int year)//判断闰年
{ 
   if(year%4==0&&year%100!=0||year%400==0)
      return 1;
      else return 0;
}
	unsigned char idata mon_day[]={31,28,31,30,31,30,31,31,30,31,30,31}; 
int month_day(int year,int month) //判断月份
{ 
	 return (month==2 && leap(2000+year)) ? 29 : mon_day[month-1];
}	

int Calc_Days(uint8 year,uint8 month,uint8 day)
{
    uint16 d = day - 1;
    while(--month) d += month_day(year, month);
    return d;
}	
/*
x=公元多少年
y=这一天是这一年的多少天
S=星期天
*/

uint8 CaculateWeekDay(int y,int m, int d)
{
    uint16 z = 2000 + y - 1;
    uint16 s = z + z/4 - z/100 + z/400 + Calc_Days(y, m, d) + 1;
    return (s + 6) % 7;
}

void Updata_YearData(void)
{
	  unsigned char i;
	  i=month_day(R_Year,R_Month);
	  R_Day++;
	  if(R_Day<=i) return;
		R_Day=1;
		R_Month++;
		if(R_Month<=12)return;
		R_Month=1;
		R_Year++;
		if(R_Year<=99)return;	
		R_Year=00;								
}
#endif