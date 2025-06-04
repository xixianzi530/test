
#include "include.h"




bit Music_en;
unsigned char idata R_SendCnt ;
unsigned char idata R_SendState ;
unsigned char idata SendData ;



// 定时器1初始化函数
void timer1_init(void)
{
	TMOD = (TMOD & ~ 0X30) | (1 << 4);       // Timer1模式选择 16位定时器  0：8 位定时器/计数器(TH1)和 5 位预分频器(TL1)；       1：16 位定时器/计数器； 
	                                         // 2：8 位自动重载定时器/计数器(TL1) ；            3：Timer1 停止                	      

	TH1 = TIME_5000US_CHUFA;                                       // 100US
	TL1 = TIME_5000US_YUQU;										 //
																	  						
	TR1 = 1;                                                         // TIMER1 运行 
	ET1 = 1;                                                         // TIMER1使能
//	PT1 = 1;
	
	P0MOD76=0x61;		//DC+DATA
	P07 = 1;
}

void timer1_Stop()
{
              
	TMOD = 0;       							// Timer0模式选择  0: 8位定时器/计数器（TH0） 和5位预分频器（TL0）1:16位定时器/计数器 
	                                                                 // 2:8位自动重载定时器/计数器（TL0） 3:TL0是一个8位定时器/计数器。TH0 是一个8位定时器/计数器                     

	TH1 = 0;                                     // 100US
	TL1 = 0;
		
	TR1 = 0;                                                       // TIMER0 运行
	ET1 = 0;                                                       //允许TIMER0中断

}
// 定时器1中断服务程序
void timer1_int() interrupt 3
{
    if (!Music_en)
    {
        TH1 = (TIME_5000US_CHUFA);
        TL1 = (TIME_5000US_YUQU) ;
	
        R_SendState = 0;
        R_SendCnt = 0;
        P07 = 0;                  
        return;
    }
    Send_MusicData();               // 如果Music_en为1，则发送音乐数据
}

// 发送音乐数据函数
void Send_MusicData(void)
{
    switch (R_SendState)
    {
        case 0: // 发送低电平信号，持续9ms
            TH1 = (TIME_5000US_CHUFA);
            TL1 = (TIME_5000US_YUQU) ;
            P07 = 1;           
            R_SendState = 1;
            R_SendCnt = 0;
            break;
        case 1:
            P07 = 0;             
            if (SendData & 0x01)
            {
                TH1 = (TIME_500US_CHUFA);
                TL1 = (TIME_500US_YUQU) ;
            }
            else
            {
                TH1 = (TIME_1500US_CHUFA);
                TL1 = (TIME_1500US_YUQU) ;
            }
            R_SendState = 2;
            break;
        case 2:
            P07 = 1;             
            if (SendData & 0x01)
            {
                TH1 = (TIME_1500US_CHUFA);
                TL1 = (TIME_1500US_YUQU) ;
            }
            else
            {
                TH1 = (TIME_500US_CHUFA);
                TL1 = (TIME_500US_YUQU) ;
            }
            R_SendState = 1;
            R_SendCnt++;
            SendData >>= 1;         // 发送数据左移一位
            if (R_SendCnt == 8) R_SendState = 3;
            break;
        case 3:
            TH1 = (TIME_5000US_CHUFA);;
            TL1 = (TIME_5000US_YUQU) ;
            P07 = 0;             
            Music_en = 0;          // 关闭音乐发送
            R_SendState = 0;       // 重置发送状态
            break;
    }
}

void Play_Music(uint8 index)
{					
					while(Music_en);					
					R_SendState=0;
					R_SendCnt=0;
					Music_en=1;
					SendData=index;
}//0x06 0x17 0x28



/* ─────────────────────── 宏定义 ─────────────────────── */

#define MUSIC_CMD_PLAY_INT     0xFB    /* 可打断播放 */
#define MUSIC_CMD_STOP         0xFF    /* 停止+休眠 */
#define MUSIC_CMD_LOOP         0xD2    /* 循环播放(须两步协议) */



void Music_Config(void)
{
    Play_Music(0XF5);   							/* 发送中等声音 */
    Play_Music(MUSIC_CMD_PLAY_INT);   /* 再发播放命令 */
}
void Play_Music_Size(unsigned char r_size)
{
	code unsigned char size_table[]={0,3,7};

  Play_Music(0xf0+size_table[r_size]);   							/* 发送中等声音 */
	
}

/* ─────────────────────── 曲目相关 ─────────────────────── */
/* 播放指定曲目（可被打断） */
//void Music_Play(uint8_t track)
//{
//    Play_Music(track);          /* ① 先发曲目号 */
//}

/* 循环播放（协议要求：曲目 → 10?ms 延时 → 0xD2） */
void Music_PlayLoop(uint8_t track)
{
    Play_Music(track);
    delay_ms(10);                 /* ≈10?ms，自己实现或用系统延时 */
    Play_Music(MUSIC_CMD_LOOP);     /* 0xD2 */
}

/* 停止播放，立即休眠 */
void Music_Stop(void)
{
    Play_Music(MUSIC_CMD_STOP);     /* 0xFF */
}

