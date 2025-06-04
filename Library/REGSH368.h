/*
******************************************************************************************************
Name        :SH368.h
Version     :V2.0
Author      :AE Team(Hsinchu)V2.0
Date        :2024.03.12
Referance specification sheet version 054.
******************************************************************************************************
*/
#ifndef __SH368_H__
#define __SH368_H__
/*
******************************************************************************************************
BYTE Registers
******************************************************************************************************
*/


sfr     P0            = 0x80;            //Port 0 data
    //--------------------------------------------------------------------------------------------
    sbit         P07        = P0^7;
    sbit         P06        = P0^6;
    sbit         P05        = P0^5;
    sbit         P04        = P0^4;
    sbit         P03        = P0^3;
    sbit         P02        = P0^2;
    sbit         P01        = P0^1;
    sbit         P00        = P0^0;
/*
******************************************************************************************************
*/
sfr     SP           = 0x81;            //Stack Point
/*
******************************************************************************************************
*/
sfr     DPL           = 0x82;           //Data Point Low byte
sfr     DPH           = 0x83;           //Data Point High byte
/*
******************************************************************************************************
*/
sfr     INTE2          = 0x84;           //
    #define    PWM1IE    0x40            //PWM1 Interrupt Enable. 1: enable, 0: disable
    #define    PWM0IE    0x20            //PWM0 Interrupt Enable. 1: enable, 0: disable    

/*
******************************************************************************************************
*/
sfr     INTFLG2        = 0x85;           //
    #define    PWM1IF    0x40            //PWM1 Interrupt Flag. 1: interrupt asserted, 0: interrupt not asserted
    #define    PWM0IF    0x20            //PWM0 Interrupt Flag. 1: interrupt asserted, 0: interrupt not asserted

/*
******************************************************************************************************
*/
sfr     PCON          = 0x87;          //不支持位操作,用读改写方式
    //--------------------------------------------------------------------------------------------
    #define     SMOD    0x80           //PCON Bit[7],1=波特率倍增
    //--------------------------------------------------------------------------------------------
    #define     GF1        0x08        //PCON Bit[3],用户可以随便使用
    #define     GF0        0x04        //PCON Bit[2],用户可以随便使用
    //--------------------------------------------------------------------------------------------
    #define     PD        0x02         //PCON Bit[1],此位置1,芯片进入stop模式
    //--------------------------------------------------------------------------------------------
    #define     IDL        0x01        //PCON Bit[0],此位置1,芯片进入IDL模式
    //---------------------------------------------------------------------------------------------
    #define        ENTER_IDLE_MODE        PCON=(PCON&0xfe)|IDL
    #define        LEAVE_IDLE_MODE        PCON=(PCON&0xfe)
    #define        ENTER_STOP_MODE        PCON=(PCON&0xfd)|PD
    #define        LEAVE_STOP_MODE        PCON=(PCON&0xfd)
    
/*
******************************************************************************************************
*/
sfr     TCON          = 0x88;
    //--------------------------------------------------------------------------------------------
    sbit         TF1         = TCON^7;    //定时器T1溢出标志,可由程序查询和清零,TF1也是中断请求源,当CPU响应T1中断时由硬件清零
    sbit         TR1         = TCON^6;    //T1充许计数控制位,为1时充许T1计数
    //--------------------------------------------------------------------------------------------
    sbit         TF0         = TCON^5;    //定时器T0溢出标志,可由程序查询和清零,TF0也是中断请求源,当CPU响应T0中断时由硬件清零
    sbit         TR0         = TCON^4;    //T0充许计数控制位,为1时充许T0计数
    //--------------------------------------------------------------------------------------------
    sbit         IE1         = TCON^3;    //外部中断1请示源(INT1,P3.3)标志;IE1也是中断请求源,当CPU响应该中断时由硬件清IE1(边沿触发方式)
    sbit         IT1         = TCON^2;    //外部中断源1触发方式控制位,IT1＝0,外部中断1程控为电平触发方式;当INT1（P3.3）输入低电平时,置位IE1
    //--------------------------------------------------------------------------------------------
    sbit         IE0         = TCON^1;    //外部中断0请示源(INT1,P3.2)标志;IE0也是中断请求源,当CPU响应该中断时由硬件清IE0(边沿触发方式)
    sbit         IT0         = TCON^0;    //外部中断源0触发方式控制位,IT0＝0,外部中断0程控为电平触发方式;当INT0（P3.2）输入低电平时,置位IE0
/*
******************************************************************************************************
*/
sfr     TMOD          = 0x89;             //不支持位操作,用读改写方式
    //--------------------------------------------------------------------------------------------
    #define     T1_Mask        ~0xf0      //T1工作模式选择Mask
    //--------------------------------------------------------------------------------------------
    #define     GATE1        0x80         //定时器1操作开关控制位
                                          //当GATE1=1时,INT1引脚为高电平,同时TCON中的TR1控制位为1时,计时/计数器1才开始工作
                                          //当GATE1=0时,则只要将TR1控制位设为1，计时/计数器1就开始工作
    #define     CT1          0x40         //定时/计数器1功能的选择位
                                          //CT1=1为计数器,通过外部引脚T1输入计数脉冲
                                          //CT1=0为定时器,由内部系统时钟提供计时工作脉冲
    #define     CT1N         0x40         //定时/计数器1功能的选择位 (ref version 083)
                                          //CT1=1为计数器,通过外部引脚T1输入计数脉冲
                                          //CT1=0为定时器,由内部系统时钟提供计时工作脉冲
    //-----------------------------------  ---------------------------------------------------------
    #define     T1_Mode0        0x00        //T1为13位计时/计数器
    #define     T1_Mode1        0x10        //T1为16位计时/计数器
    #define     T1_Mode2        0x20        //T1为8位自动加载计数/计时器 
    #define     T1_Mode3        0x30        //timer stop
    //--------------------------------------------------------------------------------------------
    #define     T0_Mask            ~0x0f      //T0工作模式选择Mask
    //--------------------------------------------------------------------------------------------
    #define     GATE0            0x08         //定时器0操作开关控制位
                                              //当GATE0=1时,INT0引脚为高电平,同时TCON中的TR0控制位为1时,计时/计数器0才开始工作
                                              //当GATE0=0时,则只要将TR0控制位设为1，计时/计数器0就开始工作
    #define     CT0              0x04         //定时/计数器0功能的选择位
                                              //CT0=1为计数器,通过外部引脚T0输入计数脉冲
                                              //CT0=0为定时器,由内部系统时钟提供计时工作脉冲
    #define     CT0N             0x04         //定时/计数器0功能的选择位  (ref version 083)
                                              //CT0=1为计数器,通过外部引脚T0输入计数脉冲
                                              //CT0=0为定时器,由内部系统时钟提供计时工作脉冲
    //--------------------------------------------------------------------------------------------
    #define     T0_Mode0            0x00        //T0为13位计时/计数器 
    #define     T0_Mode1            0x01        //T0为16位计时/计数器 
    #define     T0_Mode2            0x02        //T0为8位自动加载计数/计时器
    #define     T0_Mode3            0x03        //仅适用于T0,T0分为两个独立的8位定时器/计数器TH0及TL0,在此模式下T1停止工作
/*
******************************************************************************************************
*/    
sfr     TL0           = 0x8A;                //Timer 0 data low byte
sfr     TH0           = 0x8C;                //Timer 0 data high byte
/*
******************************************************************************************************
*/
sfr     TL1           = 0x8B;                //Timer 1 data low byte
sfr     TH1           = 0x8D;                //Timer 1 data high byte
/*
******************************************************************************************************
*/
sfr     P1            = 0x90;                //Port 1 data
    //--------------------------------------------------------------------------------------------
    sbit         P17        = P1^7;
    sbit         P16        = P1^6;    
    sbit         P15        = P1^5;    
    sbit         P14        = P1^4;    
    sbit         P13        = P1^3;    
    sbit         P12        = P1^2;    
    sbit         P11        = P1^1;    
    sbit         P10        = P1^0;    


/*
******************************************************************************************************
*/ 
sfr     P0MOD10        = 0x91;
    //--------------------------------------------------------------------------------------------
    //P0OE:P0OE Bit[7:0],P0 CMOS Push-Pull Output Enable (1=Enable) 

/*
******************************************************************************************************
*/
sfr     P0MOD32        = 0x92;
    //--------------------------------------------------------------------------------------------
    //P1LOE:P1LOE Bit[3:0],P1.5~2 (COM3~0) LCD 1/2 bais Output Enable (1=Enable) 

/*
******************************************************************************************************
*/
sfr     P0MOD54        = 0x93;


    //P2MOD1:PINMOD Bit[3:2],P2.1 Pin Control
    //P2MOD0:PINMOD Bit[1:0],P2.0 Pin Control

/*
******************************************************************************************************
*/
sfr     OPTION        = 0x94;
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------
    
    #define        TM3CKS        0x40        //Timer3 Clock Source Select. 0: SLOW (SRC/SXT), 1: FRC/512 (31.25KHz)

    //--------------------------------------------------------------------------------------------
    //WDT:OPTION Bit[5:4],WDT Prescale.  
    #define        WDTPSC_1      0x00                    //Watch Dog Timer Prescale 3=Fastest   
    #define        WDTPSC_2      0x10                    //Watch Dog Timer Prescale 3=Fastest   
    #define        WDTPSC_3      0x20                    //Watch Dog Timer Prescale 3=Fastest   
    #define        WDTPSC_4      0x30                    //Watch Dog Timer Prescale 3=Fastest   
    
    #define        WDTPSC_00     0x00                    //Watch Dog Timer Prescale 0  
    #define        WDTPSC_01     0x10                    //Watch Dog Timer Prescale 1   
    #define        WDTPSC_02     0x20                    //Watch Dog Timer Prescale 2   
    #define        WDTPSC_03     0x30                    //Watch Dog Timer Prescale 3
        
    #define      WDTPSC0    OPTION=OPTION&0xcf           //Watch Dog Timer Prescale 3=Fastest   
    #define      WDTPSC1    OPTION=(OPTION&0xcf)|0x10    //Watch Dog Timer Prescale 3=Fastest   
    #define      WDTPSC2    OPTION=(OPTION&0xcf)|0x20    //Watch Dog Timer Prescale 3=Fastest   
    #define      WDTPSC3    OPTION=(OPTION&0xcf)|0x30    //Watch Dog Timer Prescale 3=Fastest   
    
    //--------------------------------------------------------------------------------------------
    //ADCKS:OPTION Bit[3:2],ADC Clock Rate 
    #define        ADCKS_Mask          0x0C         //b'00001100'        //ADC Clock Rate Mask
    #define        ADCKS_sys_32        0x00         //Interrupt rate is 32768 system clock cycle
    #define        ADCKS_sys_16        0x04         //Interrupt rate is 16384 system clock cycle
    #define        ADCKS_sys_8         0x08         // Interrupt rate is 8192 system clock cycle
    #define        ADCKS_sys_4         0x0c         //Interrupt rate is 128 system clock cycle
    //--------------------------------------------------------------------------------------------
    //SXTGAIN:OPTION Bit[1:0],SXT oscillator gain 
    #define        SXTGAIN_Mask      0x03           //b'00000011' //SXT oscillator gain Mask
    #define        SXTGAIN_00        0x00           //00=Lowest gain,11=Highest gain.
    #define        SXTGAIN_01        0x01           //00=Lowest gain,11=Highest gain.
    #define        SXTGAIN_02        0x02           //00=Lowest gain,11=Highest gain.
    #define        SXTGAIN_03        0x03           //00=Lowest gain,11=Highest gain.
    //TM3PSC:OPTION Bit[1:0],Timer3 Interrupt rate control,Timer3 Intr. rate. 0/1/2/3=overflow/1sec/0.5sec/0.25sec
    // #define        TM3_InterruptRateMask               0x03        //b'00000011'        //TM3_InterruptRateMask
    // #define        TM3_InterruptIsCountDataOverflow    0x00        //Interrupt rate is 32768 Slow clock cycle
    // #define        TM3_InterruptIs1SecondRate          0x01        //Interrupt rate is 16384 Slow clock cycle
    // #define        TM3_InterruptIs1_2SecondRate        0x02        //Interrupt rate is 8192 Slow clock cycle
    // #define        TM3_InterruptIs1_4SecondRate        0x03        //Interrupt rate is 128 Slow clock cycle
/*
******************************************************************************************************
*/
sfr     INTFLAG        = 0x95;
    //--------------------------------------------------------------------------------------------
    #define     LVDIF    0x80 
    //--------------------------------------------------------------------------------------------
    #define     CMPIF    0x40
    //--------------------------------------------------------------------------------------------
    #define     TKIF     0x20
    //--------------------------------------------------------------------------------------------
    #define     ADIF     0x10        //ADC 中断标志，HW clear while ADSOC set
    //--------------------------------------------------------------------------------------------
    #define     WGIF     0x08
    //--------------------------------------------------------------------------------------------    
    #define     IE2      0x04        //INT2 中断标志，1=外部中断2中断
    //--------------------------------------------------------------------------------------------
    #define     PCIF     0x02        //Port0/1/2/3 Pin Change INT Flag (INTVEC=43h)
    //--------------------------------------------------------------------------------------------
    #define     TF3      0x01        //TM3中断标志,1=TM3中断
/*
******************************************************************************************************
*/
sfr        P0MOD76        = 0x96;                        //

/*
******************************************************************************************************
*/
sfr        SWCMD        = 0x97;            //Write 56h to this register will generate SW Reset 
                                           

    #define        WDTO      0x02          //WatchDog Time-Out flag

sfr        P1MOD10        = 0x9A;                        //
sfr        P1MOD32        = 0x9B;                        //
sfr        P1MOD54        = 0x9C;                        //
sfr        P1MOD76        = 0x9D;                        //

    //P1MOD0:P1MOD10 Bit[3:0],P1.0 Pin Mode Control
    #define        P1MOD0_Mask        ~0x0f
    //P1MOD1:P1MOD10 Bit[7:4],P1.1 Pin Mode Control
    #define        P1MOD1_Mask        ~0xf0
    //P1MOD2:P1MOD32 Bit[3:0],P1.2 Pin Mode Control
    #define        P1MOD2_Mask        ~0x0f
    //P1MOD3:P1MOD32 Bit[7:4],P1.3 Pin Mode Control
    #define        P1MOD3_Mask        ~0xf0
    //P1MOD4:P1MOD54 Bit[3:0],P1.4 Pin Mode Control
    #define        P1MOD4_Mask        ~0x0f
    //P1MOD5:P1MOD54 Bit[7:4],P1.5 Pin Mode Control
    #define        P1MOD5_Mask        ~0xf0
    //P1MOD6:P1MOD76 Bit[3:0],P1.6 Pin Mode Control
    #define        P1MOD6_Mask        ~0x0f
    //P1MOD7:P1MOD76 Bit[7:4],P1.7 Pin Mode Control
    #define        P1MOD7_Mask        ~0xf0
    
sfr        P2MOD10        = 0x9E;                        //
    //P2MOD0:P2MOD10 Bit[3:0],P2.0 Pin Mode Control
    #define        P2MOD0_Mask        ~0x0f
    //P2MOD1:P2MOD10 Bit[7:4],P2.1 Pin Mode Control
    #define        P2MOD1_Mask        ~0xf0
/*
******************************************************************************************************
*/
sfr     P2            = 0xA0;            //Port 2 data
    //--------------------------------------------------------------------------------------------

    sbit         P21        = P2^1;    
    sbit         P20        = P2^0;                            
/*
******************************************************************************************************
*/
sfr        PWMCON        = 0xA1;
    #define        PWM1CKS_Mask    ~0xc0
    #define        PWM1CKS_1        0x00// PWM1 Clock source sysclk div4
    #define        PWM1CKS_2        0x40// PWM1 Clock source sysclk div2
    #define        PWM1CKS_3        0x80// PWM1 Clock source sysclk div1
    #define        PWM1CKS_4        0xc0// PWM1 IRC16M

    #define        PWM0CKS_Mask    ~0x0C
    #define        PWM0CKS_1        0x00// PWM0 Clock source sysclk div4
    #define        PWM0CKS_2        0x04// PWM0 Clock source sysclk div2
    #define        PWM0CKS_3        0x08// PWM0 Clock source sysclk div1
    #define        PWM0CKS_4        0x0C// PWM0 IRC16M


    #define        PWM1EN        0x20    //
    #define        PWM0EN        0x10    //
        
/*
******************************************************************************************************
*/
sfr        P3MOD10        = 0xA2;
sfr        P3MOD32        = 0xA3;
sfr        P3MOD54        = 0xA4;
sfr        P3MOD76        = 0xA5;
    //--------------------------------------------------------------------------------------------
    //P3MOD0:P3MOD10 Bit[3:0],P3.0 Pin Mode Control
    #define        P3MOD0_Mask        ~0x0f
    //P3MOD1:P3MOD10 Bit[7:4],P3.1 Pin Mode Control
    #define        P3MOD1_Mask        ~0xf0
    //P3MOD2:P3MOD32 Bit[3:0],P3.2 Pin Mode Control
    #define        P3MOD2_Mask        ~0x0f
    //P3MOD3:P3MOD32 Bit[7:4],P3.3 Pin Mode Control
    #define        P3MOD3_Mask        ~0xf0
    //P3MOD4:P3MOD54 Bit[3:0],P3.4 Pin Mode Control
    #define        P3MOD4_Mask        ~0x0f
    //P3MOD5:P3MOD54 Bit[7:4],P3.5 Pin Mode Control
    #define        P3MOD5_Mask        ~0xf0
    //P3MOD6:P3MOD76 Bit[3:0],P3.6 Pin Mode Control
    #define        P3MOD6_Mask        ~0x0f
    //P3MOD7:P3MOD76 Bit[7:4],P3.7 Pin Mode Control
    #define        P3MOD7_Mask        ~0xf0
/*
******************************************************************************************************
*/
    
//------------------------------------------------------------------------------------------------------------
sfr        TKCHS            =0xA7;

/*
******************************************************************************************************
*/
sfr     IE            = 0xA8;
    //--------------------------------------------------------------------------------------------
    sbit         EA          = IE^7;        //EA=0时,所有中断禁止;EA=1时,各中断的产生由个别的允许位决定
    sbit         ET2         = IE^5;        //定时2中断允许
    sbit         ET1         = IE^3;        //定时1中断充许
    sbit         EX1         = IE^2;        //外中断INT1中断充许
    sbit         ET0         = IE^1;        //定时器0中断充许
    sbit         EX0         = IE^0;        //外部中断INT0的中断允许
/*
******************************************************************************************************
*/
sfr        INTE1        = 0xA9;
    //--------------------------------------------------------------------------------------------
    #define        PWMIE        0x80        //PWM0/1 Interrupt Enable
    //--------------------------------------------------------------------------------------------
    #define        CMPIE        0x40        //PWM0/1 Interrupt Enable    
    //--------------------------------------------------------------------------------------------
    #define        LVDIE        0x20        //LVD Interrupt Enable
    //--------------------------------------------------------------------------------------------
    #define        WGIE         0x10        //I2CE Interrupt Enable
    //--------------------------------------------------------------------------------------------
    #define        ADTKIE       0x08        //ADC Interrupt Enable
    //--------------------------------------------------------------------------------------------
    #define        EX2          0x04        //XINT2 中断允许、Stop Mode 唤醒功能启用
    //--------------------------------------------------------------------------------------------
    #define        PCIE         0x02        //Port0/1/2/3 Pin Change Interrupt Enable
    //--------------------------------------------------------------------------------------------
    #define        TM3IE        0x01        //TM3中断允许        
/*
******************************************************************************************************
*/
sfr        ADCDL        = 0xAA;
    //--------------------------------------------------------------------------------------------
    //ADCDL:ADCDL Bit[7:4],ADC Data LSB 3~0
/*
******************************************************************************************************
*/
sfr        ADCDH        = 0xAB;//ADC Data 11~4
/*
******************************************************************************************************
*/

//------------------------------------------------------------------------------------------------------------
sfr        PWMCON3            =0xAC;
    
    //PWM0 output mode.
    //00 ~ 11: Mode0 ~ Mode3
    #define        PWM1OM_0    0x00
    #define        PWM1OM_1    0x10
    #define        PWM1OM_2    0x20
    #define        PWM1OM_3    0x30
    
    //PWM1 Dead Zone.
    //0000 ~ 1111: 0 ~ 14, 16*Tpwmclk
    #define        PWM1DZ_0     0x00
    #define        PWM1DZ_1     0x01
    #define        PWM1DZ_2     0x02    
    #define        PWM1DZ_3     0x03    
    #define        PWM1DZ_4     0x04    
    #define        PWM1DZ_5     0x05    
    #define        PWM1DZ_6     0x06    
    #define        PWM1DZ_7     0x07    
    #define        PWM1DZ_8     0x08    
    #define        PWM1DZ_9     0x09    
    #define        PWM1DZ_10    0x0a
    #define        PWM1DZ_11    0x0b
    #define        PWM1DZ_12    0x0c
    #define        PWM1DZ_13    0x0d
    #define        PWM1DZ_14    0x0e
    #define        PWM1DZ_15    0x0f
    

sfr        TKCON        =0xAD;
sfr        CHSEL        =0xAE;//ADC Channel Select
sfr        ADCHSEL      =0xAE;//ADC Channel Select(ref version 083)
    //--------------------------------------------------------------------------------------------
    //ADCHS:ADCHSEL Bit[7:3],ADC Channel Select
                 //00000: AD0  (P3.0)
                 //00001: AD1  (P3.1)
                 //00010: AD2  (P3.2)
                 //00011: AD3  (P3.3)
                 //00100: AD4  (P3.4)
                 //00101: AD5  (P3.5)
                 //00110: AD6  (P3.6)
                 //00111: AD7  (P2.0)
                 //01000: AD8  (P2.1)
                 //01001: AD9  (P1.4)
                 //01010: AD10 (P1.5)
                 //01011: AD11 (P1.6)
                 //01100: AD12 (P1.7)
                 //others:Reserved
                 //11011: VSS
                 //11100: VBG 
                 //11101: DAC
                 //11110: 30mV
                 //11111: VCC/4   
      #define     ADCVREFS_0     0x00   //ADC reference voltage select: 0: VCC  1:VBG(ref version 083)
      #define     ADCVREFS_1     0x04   //ADC reference voltage select: 0: VCC  1:VBG(ref version 083)

      #define     ADCVBGS_Mask   ~0x03  
      #define     ADCVBGS_0      0x00   //VBG voltage select 1.18V  for ADC  (ref version 083)
      #define     ADCVBGS_1      0x01   //VBG voltage select 2.50V  for ADC  (ref version 083)
      #define     ADCVBGS_2      0x02   //VBG voltage select 3.00V  for ADC  (ref version 083)
      #define     ADCVBGS_3      0x03   //VBG voltage select 2.00V  for ADC  (ref version 083)

//------------------------------------------------------------------------------------------------------------
sfr        PWMCON2            =0xAF;    
    //PWM0 output mode.
    //00 ~ 11: Mode0 ~ Mode3
    #define        PWM0OM_0    0x00
    #define        PWM0OM_1    0x10
    #define        PWM0OM_2    0x20
    #define        PWM0OM_3    0x30
    
    //PWM0 Dead Zone.
    //0000 ~ 1111: 0 ~ 14, 16*Tpwmclk
    #define        PWM0DZ_0    0x00
    #define        PWM0DZ_1    0x01
    #define        PWM0DZ_2    0x02    
    #define        PWM0DZ_3    0x03    
    #define        PWM0DZ_4    0x04    
    #define        PWM0DZ_5    0x05    
    #define        PWM0DZ_6    0x06    
    #define        PWM0DZ_7    0x07    
    #define        PWM0DZ_8    0x08    
    #define        PWM0DZ_9    0x09    
    #define        PWM0DZ_10   0x0a
    #define        PWM0DZ_11   0x0b
    #define        PWM0DZ_12   0x0c
    #define        PWM0DZ_13   0x0d
    #define        PWM0DZ_14   0x0e
    #define        PWM0DZ_15   0x0f
    
    
/*
******************************************************************************************************
*/
sfr     P3            = 0xB0;                //Port 3 data
    //--------------------------------------------------------------------------------------------
    sbit         P37        = P3^7;
    sbit         P36        = P3^6;
    sbit         P35        = P3^5;
    sbit         P34        = P3^4;
    sbit         P33        = P3^3;
    sbit         P32        = P3^2;
    sbit         P31        = P3^1;
    sbit         P30        = P3^0;

sfr     LEDCON            = 0xB1;
sfr     LEDCON2           = 0xB2;
sfr     DACON             = 0xB3;
sfr     TKDH              = 0xB4;
sfr     TKDL              = 0xB5;

sfr     WGCON             = 0xB6;
sfr     WGBUF             = 0xB7;

    
/*
******************************************************************************************************
*/
sfr     IP            = 0xB8;
    //--------------------------------------------------------------------------------------------
    sbit         PT2            = IP^5;        //定时2中断优先级低位
    sbit         PT1            = IP^3;        //定时1中断优先级低位
    sbit         PX1            = IP^2;        //外中断INT1中断优先级低位
    sbit         PT0            = IP^1;        //定时0中断优先级低位
    sbit         PX0            = IP^0;        //外中断INT0中断优先级低位
/*
******************************************************************************************************
*/
sfr     IPH            = 0xB9;
    //--------------------------------------------------------------------------------------------
//    sbit         PT2H        = IP^5;        //定时2中断优先级高位
//    sbit         PT1H        = IP^3;        //定时1中断优先级高位
//    sbit         PX1H        = IP^2;        //外中断INT1中断优先级高位
//    sbit         PT0H        = IP^1;        //定时0中断优先级高位
//    sbit         PX0H        = IP^0;        //外中断INT0中断优先级高位/*
    #define        IPH_Mask     ~0x3F         //
    #define        IPH_PT2H    0x20           //定时2中断优先级高位             
    #define        IPH_PT1H    0x08           //定时1中断优先级高位       
    #define        IPH_PX1H    0x04           //外中断INT1中断优先级高位  
    #define        IPH_PT0H    0x02           //定时0中断优先级高位       
    #define        IPH_PX0H    0x01           //外中断INT0中断优先级高位/*
/*
******************************************************************************************************
*/    
sfr     IP1          = 0xBA;        //Interrupt Priority Control Low bits
    //--------------------------------------------------------------------------------------------
    #define        PPWM        0x80        //PWM0~1 Interupt Priority Low bit
    #define        PCMP        0x40        //CMP Interupt Priority Low bit    
    #define        PLVD        0x20        //LVD Interupt Priority Low bit
    #define        PWG         0x10        //WG Interupt Priority Low bit
    #define        PADTKI      0x08        //ADC/TK中断优先级低位 (ref version 083)
    #define        PX2         0x04        //XIN T2中断优先级低位
    #define        PPC         0x02        //Px中断优先级低位
    #define        PT3         0x01        //定时3中断优先级低位

/*
******************************************************************************************************
*/
sfr     IP1H           = 0xBB;        //Interrupt Priority Control High bits
    //--------------------------------------------------------------------------------------------
    #define        PPWMH        0x80        //PWM0~1 Interupt Priority High bit
    #define        PCMPH        0x40        //CMP Interupt Priority High bit    
    #define        PLVDH        0x20        //LVD Interupt Priority High bit  (ref version 083)
    #define        PWGH         0x10        //WG Interupt Priority High bit   (ref version 083)
    #define        PADTKIH      0x08        //ADC/TK中断优先级高位     (ref version 083)
    #define        PX2H         0x04        //XIN T2中断优先级高位
    #define        PPCH         0x02        //Px中断优先级高位
    #define        PT3H         0x01        //定时3中断优先级高位

sfr     DACDH            = 0xBC;
sfr     DACDL            = 0xBD;

sfr     CMPCON           = 0xBE;
sfr     CMPPNS           = 0xBF;

sfr     DRVCON           = 0xC4;
sfr     DRVCON2          = 0xC5;
sfr     DRVCON3          = 0xC6;
sfr     DRVCON4          = 0xC7;


/*
******************************************************************************************************
*/

sfr     T2CON          = 0xC8;
    //--------------------------------------------------------------------------------------------
    sbit         TF2         = T2CON^7;        //定时器T2溢出中断标志。TF2必须由用户程序清“0”。当T2作为串口波特率发生器时，TF2不会被置“1”。
    sbit         EXF2        = T2CON^6;        //外部中断2标志。EXEN2为1时，当T2EX（P1.1）发生负跳变时置1中断标志DXF2，EXF2必须由用户程序清“0”。
    sbit         RCLK        = T2CON^5;        //串行接口的接收时钟选择标志。TCLK=1时，T2工作于mode 1 or 3。
    sbit         TCLK        = T2CON^4;        //串行接口的发送时钟选择标志位。RCLK＝1时，T2工作于mode 1 or 3。
    sbit         EXEN2       = T2CON^3;        //外部中断2充许标志。
    sbit         TR2         = T2CON^2;        //Timer2运行控制。0：Timer2停止，1：Timer2运行
    sbit         CT2         = T2CON^1;        //Timer2计数器/定时器选择位。C/T2=0时，为定时器模式。C/T2=1时，为计数器模式。
    sbit         CT2N        = T2CON^1;        //Timer2计数器/定时器选择位。C/T2=0时，为定时器模式。C/T2=1时，为计数器模式。(ref version 083)
    sbit         CPRL2       = T2CON^0;        //捕捉和常数自动再装入方式选择位。为1时工作于捕捉方式，为0时T2工作于常数自动再装入方式。当TCLK或RCLK为1时，CP/RL2被忽略，T2总是工作于常数自动再装入方式。
    sbit         CPRL2N      = T2CON^0;        //捕捉和常数自动再装入方式选择位。为1时工作于捕捉方式，为0时T2工作于常数自动再装入方式。当TCLK或RCLK为1时，CP/RL2被忽略，T2总是工作于常数自动再装入方式。(ref version 083)
/*
******************************************************************************************************
*/

sfr     RCP2L         = 0xCA;                //外部输入（P1.1）计数器/自动再装入模式时初值寄存器低八位
sfr     RCP2H         = 0xCB;                //外部输入（P1.1）计数器/自动再装入模式时初值寄存器高八位
/*
******************************************************************************************************
*/
sfr     TL2           = 0xCC;                  //Timer2 data low byte
sfr     TH2           = 0xCD;                //Timer2 data high byte
/*
******************************************************************************************************
*/
sfr     EXA2           = 0xCE;    
    //EXA2:EXA2 Bit[7:0],extra ACC for 32/16 bit division operation
/*
******************************************************************************************************
*/
sfr     EXA3           = 0xCF;
    //EXA3:EXA3 Bit[7:0],extra ACC for 32/16 bit division operation
/*
******************************************************************************************************
*/
sfr     PSW           = 0xD0;
    //--------------------------------------------------------------------------------------------
    sbit         CY         = PSW^7;        //进位标志,有进或借位,CY＝1;无进或借位,CY＝0
    sbit         AC         = PSW^6;        //半进位标志
    sbit         F0         = PSW^5;        //用户可以随便使用
    sbit         RS1        = PSW^4;        //工作寄存器区选择[RS1:RS0]
    sbit         RS0        = PSW^3;        //00--0区,01--1区,10--2区,11--3区
    sbit         OV         = PSW^2;        //运算结果按补码运算,有溢出,OV=1;无溢出,OV＝0
    sbit         F1         = PSW^1;        //用户自定义标志
    sbit         P          = PSW^0;        //用来表示ALU运算结果中二进制数位1的个数的奇偶性,若为奇数,则P=1,否则为0
    
/*
******************************************************************************************************
*/
sfr     PWM0DH        = 0xD1;
    //PWM0DH:PWM0DH Bit[7:0],PWM0 Duty 15~8

/*
******************************************************************************************************
*/
sfr     PWM0DL        = 0xD2;
    //PWM0DL:PWM0DL Bit[7:0],PWM0 Duty 7~0
/*
******************************************************************************************************
*/
sfr     PWM0ADH        = 0xD3;
    //PWM1DH:PWM1DH Bit[7:0],PWM1 Duty 15~8

/*
******************************************************************************************************
*/
sfr     PWM0ADL        = 0xD4;
    //PWM1DL:PWM1DL Bit[7:0],PWM1 Duty 7~0
/*
******************************************************************************************************
*/
sfr     PWM0BDH        = 0xD5;
    //PWM2DH:PWM2DH Bit[7:0],PWM2 Duty 15~8

/*
******************************************************************************************************
*/
sfr     PWM0BDL        = 0xD6;
    //PWM2DL:PWM2DL Bit[7:0],PWM2 Duty 7~0

/*
******************************************************************************************************
*/
sfr     TM3RLD        = 0xD7;

/*
******************************************************************************************************
*/
sfr        CLKCON          = 0xD8;
    sbit         SCKTYPE    = CLKCON^7;        //慢时钟类型选择，Slow Clock Type. 1=SXT, 0=SRC
    sbit         STPSCK     = CLKCON^5;        //Set 1 to stop Slow clock in stop mode.          (ref version 083)
    sbit         STPPCK     = CLKCON^4;        //1=进入IDL模式，Stop UART/Timer0/Timer1/Timer2 Clock in Idle mode
    sbit         STPFCK     = CLKCON^3;        //1=停止快时钟，0=快时钟工作
    sbit         SELFCK     = CLKCON^2;        //1=选择快时钟为系统时钟源，0=慢时钟为系统时钟源
    //CLKPSC:CLKCON Bit[1:0],系统时钟预分频，SYSCLK Prescaler, 0:div16, 1:div4, 2:div2, 3:div1
    sbit         CLKPSC_H   = CLKCON^1;    
    sbit         CLKPSC_L   = CLKCON^0;    

/*
******************************************************************************************************
*/
sfr     PWM0PRDH    = 0xD9;
    //PWM0PRDH:PWM0PRDH Bit[7:0],PWM0 Period 15~8

sfr     PWM0PRDL    = 0xDA;
    //PWM0PRDL:PWM0PRDL Bit[7:0],PWM0 Period 7~0

sfr     PWM1PRDH    = 0xDB;
    //PWM1PRDH:PWM1PRDH Bit[7:0],PWM1 Period 15~8

sfr     PWM1PRDL    = 0xDC;
    //PWM1PRDH:PWM1PRDH Bit[7:0],PWM1 Period 7~0

/*
******************************************************************************************************
*/
sfr     RDCON        = 0xDF;    
/*
******************************************************************************************************
*/
sfr     ACC           = 0xE0;        //Accumulator


//******************************************************************************************************
sfr        LVRCON    = 0xE3;       //(ref version 083)
    #define      LVRPD    0x10     //LVR power down  0=LVR enable ,1=LVR disable (ref version 083)
    
    #define    LVRSEL_000    0x00    //    1.58V
    #define    LVRSEL_001    0x01    //    1.70V
    #define    LVRSEL_002    0x02    //    1.83V
    #define    LVRSEL_003    0x03    //    1.95V
    #define    LVRSEL_004    0x04    //    2.07V
    #define    LVRSEL_005    0x05    //    2.20V
    #define    LVRSEL_006    0x06    //    2.32V
    #define    LVRSEL_007    0x07    //    2.44V
    #define    LVRSEL_008    0x08    //    2.56V
    #define    LVRSEL_009    0x09    //    2.69V
    #define    LVRSEL_010    0x0a    //    2.81V
    #define    LVRSEL_011    0x0b    //    2.93V
    #define    LVRSEL_012    0x0c    //    3.06V
    #define    LVRSEL_013    0x0d    //    3.18V
    #define    LVRSEL_014    0x0e    //    3.30V
    #define    LVRSEL_015    0x0f    //    3.42V
    
sfr        LVDCON    = 0xE4;

    #define    LVDSEL_000    0x00    //    1.58V
    #define    LVDSEL_001    0x01    //    1.70V
    #define    LVDSEL_002    0x02    //    1.83V
    #define    LVDSEL_003    0x03    //    1.95V
    #define    LVDSEL_004    0x04    //    2.07V
    #define    LVDSEL_005    0x05    //    2.20V
    #define    LVDSEL_006    0x06    //    2.32V
    #define    LVDSEL_007    0x07    //    2.44V
    #define    LVDSEL_008    0x08    //    2.56V
    #define    LVDSEL_009    0x09    //    2.69V
    #define    LVDSEL_010    0x0a    //    2.81V
    #define    LVDSEL_011    0x0b    //    2.93V
    #define    LVDSEL_012    0x0c    //    3.06V
    #define    LVDSEL_013    0x0d    //    3.18V
    #define    LVDSEL_014    0x0e    //    3.30V
    #define    LVDSEL_015    0x0f    //    3.42V

//******************************************************************************************************
sfr        EFTCON    = 0xE5;


//******************************************************************************************************
sfr        EXA        = 0xE6;
    //EXA:EXA Bit[7:0],extra ACC for 16 bit mul/div operation

//******************************************************************************************************
sfr        EXB        = 0xE7;
    //EXB:EXB Bit[7:0],extra B for 16 bit mul/div operation

//******************************************************************************************************
sfr        PWM1DH        = 0xE9;
    //PWM1DH:PWM4DH Bit[7:0],PWM4 Duty 15~8
    
//******************************************************************************************************
sfr        PWM1DL        = 0xEA;
    //PWM1DL:PWM4DL Bit[7:0],PWM4 Duty 7~0

//******************************************************************************************************
sfr        PWM1ADH        = 0xEB;
    //PWM5DH:PWM5DH Bit[7:0],PWM5 Duty 15~8
    
//******************************************************************************************************
sfr        PWM1ADL        = 0xEC;
    //PWM5DL:PWM5DL Bit[7:0],PWM5 Duty 7~0

//******************************************************************************************************
sfr        PWM1BDH        = 0xED;
    //PWM6DH:PWM6DH Bit[7:0],PWM6 Duty 15~8
    
//******************************************************************************************************
sfr        PWM1BDL        = 0xEE;
    //PWM6DL:PWM6DL Bit[7:0],PWM6 Duty 7~0
    
//******************************************************************************************************
sfr        AUX3          = 0xEF;

//******************************************************************************************************
sfr     B                = 0xF0;        //B register
//******************************************************************************************************
sfr     CRCDL           = 0xF1;
    //--------------------------------------------------------------------------------------------
    //CRCDL:CRCDL Bit[7:0],CRC16 Data 7~0
//******************************************************************************************************
sfr     CRCDH           = 0xF2;
    //--------------------------------------------------------------------------------------------
    //CRCDH:CRCDH Bit[7:0],CRC16 Data 15~8
//******************************************************************************************************
sfr     CRCIN           = 0xF3;
    //--------------------------------------------------------------------------------------------
    //CRCIN:CRCIN Bit[7:0],CRC16 input


//
sfr     CFGBG           = 0xF5;
    //--------------------------------------------------------------------------------------------
    //CFGBG:CFGBG Bit[3:0],VBG trimming value

sfr     CFGWL           = 0xF6;
    //--------------------------------------------------------------------------------------------
    //FRCF:CFGWL Bit[6:0],FRC freq
    
/*
******************************************************************************************************
*/    
sfr     AUX2        = 0xF7;
    //--------------------------------------------------------------------------------------------
    //WDTE:AUX2 Bit[7:6],WDT Control
    //#define     WDT_EN                  0xC0        
    //#define     WDT_ENFS_DISILDE        0x80        
    //#define     WDT_DIS                 0x00        
    
    #define      WDT_IS_OPEN                         AUX2=(AUX2&0x3f)|0xC0    //11：WDT Always Enable
    #define      WDT_RUN_FAST_DIS_ILDE               AUX2=(AUX2&0x3f)|0x80    //10: WDT Enable in Fast/Slow, Disable in Idle/Stop mode
    #define      WDT_IS_STOP                         AUX2=AUX2&0x3f           //0X: WDT Disable

    #define      PWRSAV        0x20    //Set 1 to reduce the chip's power comsumption at Idle/Halt/Stop mode.
    #define      PWRSAV_ENABLE                       AUX2=(AUX2&0xdf)|PWRSAV
    #define      PWRSAV_DISABLE                      AUX2=(AUX2&0xdf)
    
    #define      VBGOUT        0x10    //1: VBG output to P3.2,   0: P32 as normal IO
    #define      VBG_OUTPUT                          AUX2=(AUX2&0xef)|VBGOUT
    #define      VBG_NORMAL                          AUX2=(AUX2&0xef)

    
    //0: 16/16 division operation
    //1: 32/16 division operation"
    #define      DIV32        0x08
    #define      DIV32_16                            AUX2=(AUX2&0xf7)|DIV32
    #define      DIV32_32                            AUX2=(AUX2&0xf7)
    
    #define      MULDIV16     0x01    //0: 8bit mul/div

/*
******************************************************************************************************
*/    
sfr     AUX1           = 0xF8;
    //--------------------------------------------------------------------------------------------
    sbit         CLRWDT        = AUX1^7;    //Clear WatchDog, HW auto clear
    #define      CLR_WDT        CLRWDT=1    //设置以清除看门狗定时器,H/W自动在一个时钟周期清除它         
    sbit         CLRTM3        = AUX1^6;    //清零TM3也是启动TM3
    sbit         TKSOC         = AUX1^5;    //Touch key start of conversion.
    sbit         ADSOC         = AUX1^4;    //ADC开始，结束时硬件自动清零
    sbit         CLRPWM0       = AUX1^3;     //Clear PWM0
    sbit         CLRPWM1       = AUX1^2;    //Clear PWM1
    sbit         WGEN          = AUX1^1;    //Clear PWM1
    sbit         DPSEL         = AUX1^0;    //0表选择DPTR;1表选择DPTR1

/*
******************************************************************************************************
*/    
sfr     ICECON         = 0xF9;
    #define     HWBRK              0x80        //H/W Break
    #define     RETROREQ           0x40        //Retro-OPCode Request,HW set at SWBRK,clear at NMI return
    #define     TXRDY              0x20        //Transmitt Ready
    #define     CMDRDY             0x10        //Ready for Command
    #define     XFIRCK             0x08        //Swich to FIRC 4MHZ
    //#define     WRFAIL              0x01     //EEPROM Write Fail
/*
******************************************************************************************************
*/    
sfr     RETROCODE     = 0xFA;    //ICE Mode Retro-OPCode
/*
******************************************************************************************************
*/    
sfr     ICERCD         = 0xFB;    //ICE Mode Receive Data
/*
******************************************************************************************************
*/    
sfr     ICECMDL        = 0xFC;    //ICE Mode Command Low Byte
/*
******************************************************************************************************
*/    
sfr     ICECMDH        = 0xFD;    //ICE Mode Command High Byte
/*
******************************************************************************************************
*/    
sfr     ICETXD        = 0xFE;    //ICE Mode Transmit Data
/*
******************************************************************************************************
*/    
sfr     INDSFR        = 0xFF;    //SFR direct Adr replaced by ICECMDL in NMI "mov dir,a" & "mov a,dir"
/*
******************************************************************************************************
*/    


#define     All_Interrupt_Enable()     EA = 1        //全局中断使能
#define     All_Interrupt_Disable()    EA = 0        //全局中断关闭
/*
******************************************************************************************************
*/
#define     PowerDown()            PCON = PCON | PD    //进入掉电模式
#define     PowerIdel()            PCON = PCON | IDL    //进入IDEL模式
/*
******************************************************************************************************
*/
#endif
/*
******************************************************************************************************
*/


