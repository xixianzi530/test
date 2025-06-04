#ifndef __SH368_SFT_CONFIG_H_
#define __SH368_SFT_CONFIG_H_



enum 
{
	ADC_CH0  		= 0,
	ADC_CH1  		= 1,
	ADC_CH2  		= 2,
	ADC_CH3  		= 3,
	ADC_CH4  		= 4,
	ADC_CH5  		= 5,
	ADC_CH6  		= 6,
	ADC_CH7  		= 7,
	ADC_CH8  		= 8,
	ADC_CH9  		= 9,
	ADC_CH10  		= 10,
	ADC_CH11  		= 11,		
	ADC_CH12  		= 12,		
	ADC_VCC  		= 0X1F,
};


#define		PIN_L_MODE_OD 	  	        0x01    //开漏
#define		PIN_L_MODE_OD_IPU	          0x00    //开漏带上拉
#define		PIN_L_MODE_OD_IPD	          0x04    //开漏带下拉

#define		PIN_L_MODE_PP		         		0x06    //推挽输出
#define		PIN_L_MODE_ADC		          0x03    //ADC
#define		PIN_L_MODE_LED		          0x07    //LED
#define		PIN_L_MODE_AF 		          0x0B    //PWM TxO CKO
#define		PIN_L_MODE_COM		          0x0F    //LCD 1/2BIAS

#define		PIN_L_MODE_OD_WAKEUP 	  	  0x09    //开漏+唤醒
#define		PIN_L_MODE_OD_IPU_WAKEUP	  0x08    //开漏带上拉+唤醒
#define		PIN_L_MODE_OD_IPD_WAKEUP	  0x0C    //开漏带下拉+唤醒

#define		PIN_H_MODE_OD 		          0x10    //开漏
#define		PIN_H_MODE_OD_IPU	          0x00    //开漏带上拉
#define		PIN_H_MODE_OD_IPD	          0x40    //开漏带下拉

#define		PIN_H_MODE_PP		  	      0x60    //推挽输出
#define		PIN_H_MODE_ADC		          0x30    //ADC
#define		PIN_H_MODE_LED		          0x70    //LED
#define		PIN_H_MODE_AF 		          0xB0    //PWM TxO CKO
#define		PIN_H_MODE_COM		          0xF0    //LCD 1/2BIAS

#define		PIN_H_MODE_OD_WAKEUP 		  0x90    //开漏+唤醒
#define		PIN_H_MODE_OD_IPU_WAKEUP	  0x80    //开漏带上拉+唤醒
#define		PIN_H_MODE_OD_IPD_WAKEUP	  0xC0    //开漏带下拉+唤醒



#define SET_REG_BITS(reg,regbit,value) 	   reg = reg&regbit

#endif