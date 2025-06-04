#ifndef __PWMS_C__
#define __PWMS_C__

#include 	"include.h"
/******************************************************************************************
** ��������: PWM0_init
** ��������: PWM0ͨ����ʼ��
** �������: �� 
** �������: �� 
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
��������	PWM_Enable
����������PWMʹ��
�������: Pwmch	��ʹ�ܵ�PWMͨ��
����ֵ��  ��					
******************************************************************************/
void PWM_Enable(PWM_Channel_TypeDef Pwmch)
{
	PWMCON |= 1<<Pwmch;
}




//#define I2C_SCL  P04       // ����SCL����
//#define I2C_SDA  P00       // ����SDA����
//#define AIP33623_ADDR 0x78 // AIP33623 I2C ��ַ��7λ��ַ 0x3C��дʱΪ0x78��
//#define I2C_TIMEOUT_TIMES 500

//void I2C_Init()
//{
//    P0MOD54 = (P0MOD54 & 0xf0) | 0x01; // ��©
//    P0MOD10 = (P0MOD10 & 0xf0) | 0x01; // ��©
//    I2C_SCL = 1;
//    I2C_SDA = 1;
//}

//void I2C_Delay(void) {
//    unsigned char i;
//    for (i = 0; i < 10; i++);  // ���I2C����ʱ
//}

///* I2C�����ź� */
//void I2C_Start(void) {
//    I2C_SDA = 1;
//    I2C_SCL = 1;
//    I2C_Delay();
//    I2C_SDA = 0;
//    I2C_Delay();
//    I2C_SCL = 0;
//}

///* I2Cֹͣ�ź� */
//void I2C_Stop(void) {
//    I2C_SDA = 0;
//    I2C_SCL = 1;
//    I2C_Delay();
//    I2C_SDA = 1;
//    I2C_Delay();
//}

///* �ȴ�ACK�ź� */
//unsigned char I2C_WaitAck(void) {
//    unsigned char timeout = 0;
//    I2C_SDA = 1;   // �ͷ�SDA
//    I2C_Delay();
//    I2C_SCL = 1;
//    I2C_Delay();
//    while (I2C_SDA) {  // �ȴ����豸����SDA��ʾACK
//        timeout++;
//        if (timeout > I2C_TIMEOUT_TIMES) {
//            I2C_Stop();
//            return 1;  // ��ʱδ�յ�ACK
//        }
//    }
//    I2C_SCL = 0;
//    return 0;  // �յ�ACK
//}

///* ����һ���ֽ����ݣ�����ȡACK */
//unsigned char I2C_SendByte(unsigned char byte) {
//    unsigned char i;
//    for (i = 0; i < 8; i++) {
//        I2C_SDA = (byte & 0x80) >> 7; // �������λ
//        byte <<= 1;
//        I2C_SCL = 1;
//        I2C_Delay();
//        I2C_SCL = 0;
//        I2C_Delay();
//    }
//    // �ȴ�ACKӦ��
//    return I2C_WaitAck();
//}

///* �������δ�յ�ACKʱ�ش�һ�� */
//void AIP33623_WriteCommand(unsigned char command) {
//    unsigned char retry = 0, error;
//    do {
//        I2C_Start();
//        error = I2C_SendByte(AIP33623_ADDR);  // �����豸��ַ+д��־
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        error = I2C_SendByte(command);  // ��������
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        I2C_Stop();
//        break;  // ���ͳɹ�
//    } while (retry < 2);
//}

///* ��ʼ���豸 */
//void AIP33623_Init(void) {
//	AIP33623_WriteData(0x01,0x3f);//����Ϊ���
//	AIP33623_WriteData(0x78);	//GRID1~GRID8��Ч��RAM��ַ�Լ�
//}


///* �������ݣ�δ�յ�ACKʱ�ش�һ�� */
//void AIP33623_WriteData(unsigned char address, unsigned char Data) {
//    unsigned char retry = 0, error;
//    do {
//        I2C_Start();
//        error = I2C_SendByte(AIP33623_ADDR);  // �����豸��ַ
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        error = I2C_SendByte(0xC0 | address);  // ����������ʼ��ַ
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        error = I2C_SendByte(Data);  // ��������
//        if (error) {
//            I2C_Stop();
//            retry++;
//            continue;
//        }
//        I2C_Stop();
//        break;  // ���ݷ��ͳɹ�
//    } while (retry < 2);
//}

///* �����ʾ */
//void AIP33623_ClearDisplay(void) {
//    unsigned char i;
//    for (i = 0; i < 12; i++) {
//        AIP33623_WriteData(i, 0x00);  // ����
//    }
//}

#endif