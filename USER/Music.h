#ifndef __MUSIC_H__
#define __MUSIC_H__
#define FRC_HZ1				16000000
#define FRC_DIV1				1
#define CLK_US0              6000                     //100us
#define TIME_5000US_CHUFA         (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US0/1000)))/256)   //���ȸ���
#define TIME_5000US_YUQU          (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US0/1000)))%256)   //%�ȸ���


#define CLK_US1 	1500            // ��ʱ���ڣ�1500΢��
#define TIME_1500US_CHUFA        (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US1/1000)))/256)  //���ȸ���
#define TIME_1500US_YUQU        (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US1/1000)))%256)  //���ȸ���

#define CLK_US2		 500             // ��ʱ���ڣ�500΢��
#define TIME_500US_CHUFA         (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US2/1000)))/256)   //���ȸ���
#define TIME_500US_YUQU          (((unsigned int)(65536-(((FRC_HZ1/FRC_DIV1)/2/1000)*CLK_US2/1000)))%256)   //���ȸ���
/*
0-37 	Ϊ����
0XF0 	����1
0XF1 	����2
0XF2 	����3
0XF3 	����4
0XF4 	����5
0XF5 	����6
0XF6	����7
0XF7	����8
0XFB	����   �ɴ�ϲ���
0XFF  ֹͣ   ֹͣ��ǰ�Ķ�����������˯��
0XD0  ����   ���ɴ�ϲ���
0XD1  ����   ����ֹͣ��ǰ��Ŀ�����еƹ���
0XD2  ѭ��   ����ԡ�����Э��+10ms+0XD2��˳����
*/
void timer1_init(void);
void Send_MusicData(void);
void Play_Music(uint8 index);
/* ����ָ����Ŀ���ɱ���ϣ� */
//void Music_Play(uint8_t track);
/* ѭ�����ţ�Э��Ҫ����Ŀ �� 10?ms ��ʱ �� 0xD2�� */
void Music_PlayLoop(uint8_t track);
/* ֹͣ���ţ��������� */
void Music_Config(void);
void Music_Stop(void);void timer1_Stop();
void Play_Music_Size(unsigned char r_size);
#endif

