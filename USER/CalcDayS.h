#ifndef __CALCDAYS_H__
#define __CALCDAYS_H__

int leap (int year);//判断闰年
int month_day(int year,int month); //判断月份
int Calc_Days(uint8 year,uint8 month,uint8 day);
/*
x=公元多少年
y=这一天是这一年的多少天
S=星期天
*/
uint8 CaculateWeekDay(int y,int m, int d);

void Updata_YearData(void);

#endif
