#ifndef __CALCDAYS_H__
#define __CALCDAYS_H__

int leap (int year);//�ж�����
int month_day(int year,int month); //�ж��·�
int Calc_Days(uint8 year,uint8 month,uint8 day);
/*
x=��Ԫ������
y=��һ������һ��Ķ�����
S=������
*/
uint8 CaculateWeekDay(int y,int m, int d);

void Updata_YearData(void);

#endif
