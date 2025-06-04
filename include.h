#ifndef _INCLUDE_H_
#define _INCLUDE_H_

typedef unsigned char int8_t;
typedef unsigned int  int16_t;
typedef unsigned long int32_t;

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long  uint32_t;

typedef     int8_t      s8;
typedef     int16_t     s16;
typedef     int32_t     s32;
 

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t  u32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t  uint32;

typedef volatile uint8_t    vu8;
typedef volatile uint16_t   vu16;  
typedef volatile uint32_t   vu32;


#define BIT0         						0x01
#define BIT1         						0x02
#define BIT2         						0x04
#define BIT3         						0x08
#define BIT4         						0x10
#define BIT5         						0x20
#define BIT6         						0x40
#define BIT7         						0x80
#define BIT8         						0x100
#define BIT9         						0x200
#define BIT10         					0x400
#define BIT11         					0x800
#define BIT12         					0x1000
#define BIT13         					0x2000
#define BIT14         					0x4000
#define BIT15         					0x8000


#define __NOP1__  	_nop_()
#define __NOP2__ 	__NOP1__; __NOP1__
#define __NOP4__ 	__NOP2__; __NOP2__
#define __NOP8__ 	__NOP4__; __NOP4__
#define __NOP16__ 	__NOP8__; __NOP8__
#define __NOP32__ 	__NOP16__; __NOP16__
#define __NOP64__ 	__NOP32__; __NOP32__
#define __NOP128__ 	__NOP64__; __NOP64__

/*******************************************************************************/
#include	"Library/REGSH368.h"
#include 	"Library/SH368_bsp.h"
#include	"Library/SH368_sfr_config.h"
#include	"Library/SH368_RTC.h"
#include	"Library/PWM.h"
#include <stdlib.h>
#include 	<intrins.h>
#include 	<stdarg.h>
#include 	<stdio.h>
/*******************************************************************************/
#include	"USER/delay.h"
#include	"USER/Timer.h"
#include	"USER/Display_UI.h"
#include	"USER/Key_Scan.h"
#include	"USER/CalcDayS.h"
#include "USER/Nixie.h"
#include "USER/adc.h"
#include "USER/Music.h"
#include "USER/encoder.h"

/*******************************************************************************/
#endif