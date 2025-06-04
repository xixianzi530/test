#ifndef __PWMS_C__
#define __PWMS_C__

#include 	"include.h"
/******************************************************************************************
** 函数名称: PWM0_init
** 函数描述: PWM0通道初始化
** 输入参数: 无 
** 输出参数: 无 
*******************************************************************************************/
void PWM0_init(PWMIE_TypeDef ie,
			   PWM_CKS_TypeDef cks)
{
	INTE2 = PWM0_IE(ie);
	PWMCON = PWM0_CKS(cks);
}

void PWM0_Duty(unsigned int DIV,unsigned int DUT)
{
	if(DUT == 0)
	{
		
		P3MOD32 = (P3MOD32&~0xF0) | (PIN_H_MODE_PP);			//P33-GPIO
		P33 = 0;
		return;
	}
	
	P3MOD32 = (P3MOD32&~0xF0) | (PIN_H_MODE_AF);			//P32-PWM0N
	PWM0PRDL	= (unsigned char)(DIV);
	PWM0PRDH	= (unsigned char)(DIV>>8);
	
	AUX1 = (AUX1 & ~0X08) | 0x00;
	PWM0ADL		= (unsigned char)(DUT);
	PWM0ADH		= (unsigned char)(DUT>>8);	
}
/******************************************************************************
函数名：	PWM_Enable
功能描述：PWM使能
输入参数: Pwmch	，使能的PWM通道
返回值：  无					
******************************************************************************/
void PWM_Enable(PWM_Channel_TypeDef Pwmch)
{
	PWMCON |= 1<<Pwmch;
}




//#define I2C_SCL  P04       // 定义SCL引脚
//#define I2C_SDA  P00       // 定义SDA引脚
//#define AIP33623_ADDR 0x78 // AIP33623 I2C 地址（7位地址 0x3C，写时为0x78）
//#define I2C_TIMEOUT_TIMES 500

//void I2C_Init()
//{
//    P0MOD54 = (P0MOD54 & 0xf0) | 0x01; // 开漏
//    P0MOD10 = (P0MOD10 & 0xf0) | 0x01; // 开漏
//    I2C_SCL = 1;
//    I2C_SDA = 1;
//}

//void I2C_Delay(void) {
//    unsigned char i;
//    for (i = 0; i < 10; i++);  // 软件I2C短延时
//}

///* I2C启动信号 */
//void I2C_Start(void) {
//    I2C_SDA = 1;
//    I2C_SCL = 1;
//    I2C_Delay();
//    I2C_SDA = 0;
//    I2C_Delay();
//    I2C_SCL = 0;
//}

///* I2C停止信号 */
//void I2C_Stop(void) {
//    I2C_SDA = 0;
//    I2C_SCL = 1;
//    I2C_Delay();
//    I2C_SDA = 1;
//    I2C_Delay();
//}

///* 等待ACK信号 */
//unsigned char I2C_WaitAck(void) {
//    unsigned char timeout = 0;
//    I2C_SDA = 1;   // 释放SDA
//    I2C_Delay();
//    I2C_SCL = 1;
//    I2C_Delay();
//    while (I2C_SDA) {  // 等待从设备拉低SDA表示ACK
//        timeout++;
//        if (timeout > I2C_TIMEOUT_TIMES) {
//            I2C_Stop();
//            return 1;  // 超时未收到ACK
//        }
//    }
//    I2C_SCL = 0;
//    return 0;  // 收到ACK
//}

///* 发送一个字节数据，并读取ACK */
//unsigned char I2C_SendByte(unsigned char byte) {
//    unsigned char i;
//    for (i = 0; i < 8; i++) {
//        I2C_SDA = (byte & 0x80) >> 7; // 发送最高位
//        byte <<= 1;
//        I2C_SCL = 1;
//        I2C_Delay();
//        I2C_SCL = 0;
//        I2C_Delay();
//    }
//    // 等待ACK应答
//    return I2C_WaitAck();
//}

///* 发送命令，未收到ACK时重传一次 */
//void AIP33623_WriteCommand(unsigned char command) {
//    unsigned char retry = 0, error;
//    do {
//        I2C_Start();
//        error = I2C_SendByte(AIP33623_ADDR);  // 发送设备地址+写标志
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        error = I2C_SendByte(command);  // 发送命令
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        I2C_Stop();
//        break;  // 发送成功
//    } while (retry < 2);
//}

///* 初始化设备 */
//void AIP33623_Init(void) {
//	AIP33623_WriteData(0x01,0x3f);//设置为最大
//	AIP33623_WriteData(0x78);	//GRID1~GRID8有效，RAM地址自加
//}


///* 发送数据，未收到ACK时重传一次 */
//void AIP33623_WriteData(unsigned char address, unsigned char Data) {
//    unsigned char retry = 0, error;
//    do {
//        I2C_Start();
//        error = I2C_SendByte(AIP33623_ADDR);  // 发送设备地址
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        error = I2C_SendByte(0xC0 | address);  // 发送数据起始地址
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        error = I2C_SendByte(Data);  // 发送数据
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        I2C_Stop();
//        break;  // 数据发送成功
//    } while (retry < 2);
//}

///* 清除显示 */
//void AIP33623_ClearDisplay(void) {
//    unsigned char i;
//    for (i = 0; i < 12; i++) {
//        AIP33623_WriteData(i, 0x00);  // 清屏
//    }
//}

#endif