#ifndef __ENCODER_H__
#define __ENCODER_H__
extern unsigned long sys_ms; 
extern uint32_t enc_last_tick;
/**
 * @brief ��ʼ��������������ż��ڲ�����
 */
extern unsigned char encider_direction ;
void Encoder_Init(void);
void Encoder_Task(void);
#endif

