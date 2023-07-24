#ifndef __XS16TK06X_UART_H__
#define __XS16TK06X_UART_H__



#define UART0_EN							0	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define UART0_PORT 						UART0_MAP_B//ѡ��UART0ӳ��,UART0_MAP_A~UART0_MAP_F
#define UART0_CFG_BAUD_RATE   9600 //UART0������ѡ��:2400/4800/9600/19200/38400/57600/115200
#define UART0_PAD_CHANGE			0//0:TX/RX���Ź��ܲ�������1:TX/RX���Ź��ܻ���

#define UART1_EN							0	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define UART1_PORT 						UART1_MAP_B//ѡ��UART1ӳ��,UART1_MAP_A~UART1_MAP_B
#define UART1_CFG_BAUD_RATE  	9600 // UART1������ѡ��2400/4800/9600/19200/38400/57600/115200
#define UART1_PAD_CHANGE			0//0:TX/RX���Ź��ܲ�������1:TX/RX���Ź��ܻ���


#define UART_CFG_BUSCLK  		24   // BUSCLK�̶�Ƶ��
#define _CFG_BUSCLK 				(UART_CFG_BUSCLK * 1e6)
#define M_HEX_OF_BR(br)     (_CFG_BUSCLK/(16.0*br))



#define UART0_MAP_A 			0
#define UART0_MAP_B 			1
#define UART0_MAP_C 			6
#define UART0_MAP_D 			2
#define UART0_MAP_E 			4
#define UART0_MAP_F 			5

#define UART0_PORT_SET(x) 		 {REG_ADDR = 0x2B;REG_DATA &= ~(0x07);REG_DATA |= (0x07&(x<<0));}//UART0 RX/TXӳ��ѡ��,0:PA0/PA1;1:PB3/PB4,2/3:PC0/PC1;4:PD6/PA1,5:PD7/PA0��6/7:PD4/PD5

#define UART0_MODULE_SET(x) 	 {UART0_CON1 &= ~(0x40);UART0_CON1 |= (0x40&(x<<6));}//UAERT0ģ�鿪��,1Ϊ����0Ϊ��
#define UART0_RX_EN_SET(x) 		 {UART0_CON1 &= ~(0x20);UART0_CON1 |= (0x20&(x<<5));}//����ʹ�� ,1Ϊʹ�ܣ�0Ϊ��ֹ
#define UART0_MULTI_SET(x) 		 {UART0_CON1 &= ~(0x10);UART0_CON1 |= (0x10&(x<<4));}//�ദ����ͨ��ʹ��,1Ϊʹ�ܣ�0Ϊ��ֹ
#define UART0_STOP_MODE_SET(x) {UART0_CON1 &= ~(0x08);UART0_CON1 |= (0x08&(x<<3));}//STOPλ ,1Ϊ2λSTOP��0Ϊ1λSTOP
#define UART0_SEND_MODE_SET(x) {UART0_CON1 &= ~(0x04);UART0_CON1 |= (0x04&(x<<2));}//��������ģʽѡ�� ,1Ϊ9λģʽģʽ��0Ϊ8λģʽ
#define UART0_OD_EN_SET(x) 		 {UART0_CON1 &= ~(0x02);UART0_CON1 |= (0x02&(x<<1));}//��żУ��ʹ�� ,1Ϊʹ�ܣ�0Ϊ��ʹ��
#define UART0_OD_SET(x) 		 	 {UART0_CON1 &= ~(0x01);UART0_CON1 |= (0x01&(x<<0));}//��żУ��ѡ�� ,1Ϊ��У�飬0ΪżУ��

#define UART0_PC_SET(x) 	 		{UART_IO_CTRL &= ~(0x01);UART_IO_CTRL |= (0x01&(x<<0));}//RX/TX���Ź��ܻ���,1Ϊ���ܻ�����0Ϊ���ܲ�����
#define UART0_TX_IE_SET(x) 		{UART0_CON2 &= ~(0x08);UART0_CON2 |= (0x08&(x<<3));}//UART0�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART0_RX_IE_SET(x) 	  {UART0_CON2 &= ~(0x04);UART0_CON2 |= (0x04&(x<<2));}//UART0�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART0_RX_FUN_SET(x) 	{UART_IO_CTRL1 &= ~(0x02);UART_IO_CTRL1 |= (0x02&(x<<1));}//UART0���Ž��չ���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ
#define UART0_TX_FUN_SET(x) 	{UART_IO_CTRL1 &= ~(0x01);UART_IO_CTRL1 |= (0x01&(x<<0));}//UART0���ŷ��͹���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ

#define UART0_IE_SET IEN2 |= 0x02												//��UART0�ж�ʹ��
#define UART0_IE_CLR IEN2 &= ~0x02											//��UART0�ж�ʹ��
#define UART0_IP_SET IPL2 |= 0x02												//����UART0�ж����ȼ�Ϊ��
#define UART0_IP_CLR IPL2 &= ~0x02											//����UART0�ж����ȼ�Ϊ��
#define UART0_INT_FLAG_CLR IRCON2 &= ~0x02							//���UART0�жϱ�־λ


#define UART1_MAP_A 			0
#define UART1_MAP_B 			1


#define UART1_PORT_SET(x) 		 {REG_ADDR = 0x2B;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}//UART1 RX/TXӳ��ѡ��,0:PB1/PB2;1:PB6/PB7;

#define UART1_MODULE_SET(x) 	 {UART1_CON1 &= ~(0x40);UART1_CON1 |= (0x40&(x<<6));}//UART1ģ�鿪��,1Ϊ����0Ϊ��
#define UART1_RX_EN_SET(x) 		 {UART1_CON1 &= ~(0x20);UART1_CON1 |= (0x20&(x<<5));}//����ʹ�� ,1Ϊʹ�ܣ�0Ϊ��ֹ
#define UART1_MULTI_SET(x) 		 {UART1_CON1 &= ~(0x10);UART1_CON1 |= (0x10&(x<<4));}//�ദ����ͨ��ʹ��,1Ϊʹ�ܣ�0Ϊ��ֹ
#define UART1_STOP_MODE_SET(x) {UART1_CON1 &= ~(0x08);UART1_CON1 |= (0x08&(x<<3));}//STOPλ ,1Ϊ2λSTOP��0Ϊ1λSTOP
#define UART1_SEND_MODE_SET(x) {UART1_CON1 &= ~(0x04);UART1_CON1 |= (0x04&(x<<2));}//��������ģʽѡ�� ,1Ϊ9λģʽģʽ��0Ϊ��λģʽ
#define UART1_OD_EN_SET(x) 		 {UART1_CON1 &= ~(0x02);UART1_CON1 |= (0x02&(x<<1));}//��żУ��ʹ�� ,1Ϊʹ�ܣ�0Ϊ��ʹ��
#define UART1_OD_SET(x) 		 	 {UART1_CON1 &= ~(0x01);UART1_CON1 |= (0x01&(x<<0));}//��żУ��ѡ�� ,1Ϊ��У�飬0ΪżУ��

#define UART1_PC_SET(x) 	 {UART_IO_CTRL &= ~(0x02);UART_IO_CTRL |= (0x02&(x<<1));}//RX/TX���Ź��ܻ���,1Ϊ���ܻ�����0Ϊ���ܲ�����
#define UART1_TX_IE_SET(x) {UART1_CON2 &= ~(0x08);UART1_CON2 |= (0x08&(x<<3));}//UART1�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART1_RX_IE_SET(x) {UART1_CON2 &= ~(0x04);UART1_CON2 |= (0x04&(x<<2));}//UART1�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART1_RX_FUN_SET(x) 	  {UART_IO_CTRL1 &= ~(0x08);UART_IO_CTRL1 |= (0x08&(x<<3));}//UART1���Ž��չ���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ
#define UART1_TX_FUN_SET(x) 	  {UART_IO_CTRL1 &= ~(0x04);UART_IO_CTRL1 |= (0x04&(x<<2));}//UART1���ŷ��͹���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ

#define UART1_IE_SET IEN2 |= 0x04												//��UART1�ж�ʹ��
#define UART1_IE_CLR IEN2 &= ~0x04											//��UART1�ж�ʹ��
#define UART1_IP_SET IPL2  |= 0x04											//����UART1�ж����ȼ�Ϊ��
#define UART1_IP_CLR IPL2 &= ~0x04											//����UART1�ж����ȼ�Ϊ��
#define UART1_INT_FLAG_CLR IRCON2 &= ~0x04							//���UART1�жϱ�־λ



#if(UART0_EN == 1)
extern void UART0_Init(void);
extern void UART0_Send_Word (unsigned int willSendWord);
extern void UART0_Send_Byte (unsigned char willSendByte);
extern void UART0_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#if(UART1_EN == 1)
extern void UART1_Init(void);
extern void UART1_Send_Word (unsigned int willSendWord);
extern void UART1_Send_Byte (unsigned char willSendByte);
extern void UART1_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#if ((UART0_EN == 1)||(UART1_EN == 1))
//extern uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2); 
#endif

#endif