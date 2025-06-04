#ifndef __MUSIC_H__
#define __MUSIC_H__
#define FRC_HZ1				16000000
#define FRC_DIV1				1
#define CLK_US0              6000                     //100us
#define TIME_5000US_CHUFA         (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US0/1000)))/256)   //精度更高
#define TIME_5000US_YUQU          (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US0/1000)))%256)   //%度更高


#define CLK_US1 	1500            // 定时周期，1500微秒
#define TIME_1500US_CHUFA        (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US1/1000)))/256)  //精度更高
#define TIME_1500US_YUQU        (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US1/1000)))%256)  //精度更高

#define CLK_US2		 500             // 定时周期，500微秒
#define TIME_500US_CHUFA         (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US2/1000)))/256)   //精度更高
#define TIME_500US_YUQU          (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US2/1000)))%256)   //精度更高
/*
0-37 	为音乐
0XF0 	音量1
0XF1 	音量2
0XF2 	音量3
0XF3 	音量4
0XF4 	音量5
0XF5 	音量6
0XF6	音量7
0XF7	音量8
0XFB	播放   可打断播放
0XFF  停止   停止当前的动作，并进入睡眠
0XD0  播放   不可打断播放
0XD1  静音   静音停止当前曲目，但有灯工作
0XD2  循环   务必以“声音协议+10ms+0XD2”顺序发送
*/
void timer1_init(void);
void Send_MusicData(void);
void Play_Music(uint8 index);
/* 播放指定曲目（可被打断） */
//void Music_Play(uint8_t track);
/* 循环播放（协议要求：曲目 → 10?ms 延时 → 0xD2） */
void Music_PlayLoop(uint8_t track);
/* 停止播放，立即休眠 */
void Music_Config(void);
void Music_Stop(void);void timer1_Stop();
void Play_Music_Size(unsigned char r_size);
#endif

