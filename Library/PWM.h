#ifndef __PWMS_H__
#define __PWMS_H__

#define PWM1_IE(N)			(N<<6)	  //N=0-1
#define PWM0_IE(N)			(N<<5)	  //N=0-1

#define PWM1_CKS(N)			(N<<6)	  //N=0-3
#define PWM0_CKS(N)			(N<<2)	  //N=0-3

typedef enum {
	CKS_SYS		= 0,		//FSYSCLK
	CKS_FRC_256	= 1,		//FRC/256
	CKS_FRC		= 2,		//FRC
	CKS_FRCx2	= 3,		//FRCx2 (VCC>2.5V)
} PWM_CKS_TypeDef;

typedef enum {
	PWM_0 = 4,
	PWM_1 = 5,
} PWM_Channel_TypeDef;

typedef enum {
	PWMIE_off = 0,
	PWMIE_on = 1,
} PWMIE_TypeDef;


void PWM0_init(PWMIE_TypeDef ie,
			   PWM_CKS_TypeDef cks);

void PWM0_Duty(unsigned int DIV,unsigned int DUT);
void PWM_Enable(PWM_Channel_TypeDef Pwmch);




#endif