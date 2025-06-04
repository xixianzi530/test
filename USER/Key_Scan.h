#ifndef __KEY_H__
#define __KEY_H__

typedef enum
{
	SET_KEY = 1, 				//时间设置按键	 
	ALlARM_KEY = 2, 	//闹钟按键
	LIGHT_KEY = 4,
	ENCODER_KEY = 3,
	POWEROFF_KEY = 5,

	
	UP      = 10,
	DOWN    = 11,
};
extern unsigned int PowerOffCnt;
extern unsigned int Key_Sustain_Time ;
extern bit Bit_KeyPress;
extern bit Bit_KeyReles;
extern unsigned int R_KeyCode;
extern bit B_KeySCAN ;
extern unsigned int R_KeyHoldTimer ;
void Key_Sustain_Press (void);
void key_Init();
void Key_Scan(void);
void State_Ctrl(void);
#endif /* __KEY_H__ */
