#include "Config.h"
//#include 	".\Application_Library\Global.h"

/********************************************************************
��������:ů�˻� XS-FC-OLK-01-011-B
оƬ:XS16TK06F-16SOP 
�ؼ���:�̵���,4������,2λ5�������,�̰�,����,��������,�Ǹ���
ע������:
��������:2022��10��7��14:38:14
�޸�����:2022��10��7��14:38:17
*********************************************************************/
/*700W
;�ᴥ��ť:�� ,������ť:�� ,LED:��
;;			  _    _  . _    _ 
;			 /_/  /_/  /_/  /_/ 	
;			/_/  /_/  /_/  /_/
;
;	�ﱬ��(L1)    ������(L2)	������(L3)       
;	  
;	������(L4)    ��ţ��(L5)	����(L6)	  
;			
;	��ԤԼ/����(KEY1) 	 ����/ȡ��(KEY2)		
;	���(KEY3)			���(KEY4)		      												
*/

//*******************************************************************
//************************MCU������Ϣ*********************************
//�� �ںˣ����� 8051
//	�� ����Ƶ�ʣ� 12MHz�� 6MHz�� 4MHz�� 1MHz
//	�� ʱ��ƫ� ��1% @-20��~65��, 5V
//				��3% @-40��~85��, 5V
//�� �洢����SMTP��
//	�� CODE�� 16K Bytes
//	�� DATA�� 1K Bytes
//	�� SRAM�� 256 Bytes(data)+512 Bytes(xdata)
//	�� ֧�� BOOT �������� 1/2/3/4K ��ѡ
//�� ʱ��Դ����λ�͵�Դ����
//	�� �ڲ�����ʱ�� LIRC�� 32kHz�� ʱ��ƫ�
//	  ��10%@25��, 5V�� ��20% @-40��~85��, 5V
//	�� �ڲ����� RC ������ 1MHz
//	�� �ⲿ���������� 32768Hz/4MHz
//	�� 8 �ָ�λ�� ���縴λ��ѹ��BOR����
//	  2.8V/3.3V/3.7V/4.2V
//	�� �͵�ѹ��⣺ 2.7V/3.0V/3.3V/3.6V/3.9V/4.2V
//�� IO
//	�� PB ����������/�������� 28k������ IO ��������
//	  ������ 4.7k
//	�� ��������(PB0~PB7)
//	�� ֧���������蹦�ܸ���
//	�� ���� IO �ڶ�֧���ⲿ�жϹ��ܣ� INT0~2 �ⲿ��
//	  ��(�����ء��½��ء�˫��)�� INT3 �����ж�Դ(��
//	  ���ء��½���)
//�� ͨ��ģ��
//	�� 2xUART ͨ�ţ�֧�� IO ӳ��
//	�� 1xIIC Ӳ���ӻ�ͨ�ţ�֧�� 100kHz/400kHz
//�� 16-bit PWM
//	�� PWM0 ֧�� 4 ·ͨ�����������ڣ� ռ�ձȺͼ���
//����
//	�� PWM1/2 ��֧�� 1 ·ͨ�����
//�� ������ѹ�� 2.7V ~ 5.5V
//�� �����¶ȣ� -40�� ~ 85��
//	�� ��ǿ�͹�ҵ�������� JESD ��ҵ���ɿ�����
//֤��׼
//�� �߾��� 12 λ ADC
//	�� ���ɴ� 26 ��ģ������ͨ��
//	�� �ο���ѹ�� VCC/2V/4V
//�� �ж�
//	�� �����ж����ȼ���ѡ
//	�� ADC�� CSD�� INT0/1/2/3�� LVDT��
//	  Timer0/1/2�� WDT�� UART0/1�� IIC
//�� ��ʱ��
//	�� 3 �� 16 λ Timer
//	�� Timer2 ʱ��ԴΪ�ڲ�����ʱ�� LIRC32k ��
//	  �ⲿ���� 32768Hz/4MHz
//	�� ���Ź���ʱ�������ʱ�� 18ms �� 2.304s
//�� �͹���ģʽ
//	�� ����ģʽ������ģʽ
//	�� ������ߣ����� 7��A @5V ����
//�� ��������
//	�� �������������ȿɶ�������
//	�� ���ݰ��������ɸ���Ϊ GPIO
//�� ������¼���ߵ��Է���ӿ�
//�� ��װ
//	�� SOP16/SOP20/SOP28


//*******************************************************************
//***************************�������*********************************
//XS16TK06X ���ø��� 8051 �ںˣ� 1T ָ�����ڣ�����ڱ�׼�� 8051(12T)ָ�����ڣ���
//�и���������ٶȣ�ͬʱ���ݱ�׼ 8051 ָ�
//XS16TK06X ���������п��Ź��� ������⡢ IIC�� UART���͵�ѹ��⡢���縴λ�� 3 ·
//16bit PWM�� Timer0�� Timer1�� Timer2�� 12bit �߾�����αƽ� ADC���͹���ģʽ�ȡ�
//XS16TK06X ���ɵĵ��ݼ��ͨ�����������������������Ӧ���ߴ�����������
//MCU����������ã�ͨ�����ÿ�ʵ�ְ��������֡������ȶ���Ӧ�á��������ܶ������У�
//����ÿ����������ͨ������Ӧ�Ĺ��ܼĴ��������������ȡ�

//**************************************************************************
//*********************************MCU����ͼ*********************************
//**************************************************************************
/*
                                              ������������  ������������
             PWM2_A1/INT3_15/ADC15/SNS15/PC7 ����1   ��������  20���� PD0/SNS16/ADC16/INT0/PWM1_A
             PWM1_A1/INT3_14/ADC14/SNS14/PC6 ����2         19���� PD1/SNS17/ADC17/INT3_16/PWM2_A
             PWM0_D1/INT3_13/ADC13/SNS13/PC5 ����3         18���� PD2/SNS18/ADC18/INT3_17/XTAL_OUT
                     INT3_12/ADC12/SNS12/PC4 ����4         17���� PD3/SNS19/ADC19/INT3_18/XTAL_IN
             PWM0_C1/INT3_11/ADC11/SNS11/PC3 ����5         16���� PD4/SNS20/ADC20/INT3_19/RXD0_C
                     INT3_10/ADC10/SNS10/PC2 ����6         15���� PD5/SNS21/ADC21/INT3_20/TXD0_C
SDA0_B/RXD0_D/PWM0_B1/INT3_8/ADC08/SNS08/PC0 ����7         14���� PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C
          TXD1_B/COM7/INT3_7/ADC07/SNS07/PB7 ����8         13���� PD7/SNS23/ADC23/INT2/RXD0_F
                                         VSS ����9         12���� PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC
                                         VCC ����10        11���� PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE/PGD
                                              ����������������������������
											     XS16TK06A
*/
//************************************************************************************
/*
                                              ������������  ������������
            XTAL_OUT/INT3_17/ADC18/SNS18/PD2 ����1   ��������  28���� PD3/SNS19/ADC19/INT3_18/XTAL_IN
              PWM2_A/INT3_16/ADC17/SNS17/PD1 ����2         27���� PD4/SNS20/ADC20/INT3_19/RXD0_C
                 PWM1_A/INT0/ADC16/SNS16/PD0 ����3         26���� PD5/SNS21/ADC21/INT3_20/TXD0_C
             PWM2_A1/INT3_15/ADC15/SNS15/PC7 ����4         25���� PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C
             PWM1_A1/INT3_14/ADC14/SNS14/PC6 ����5         24���� PD7/SNS23/ADC23/INT2/RXD0_F
             PWM0_D1/INT3_13/ADC13/SNS13/PC5 ����6         23���� PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC
                     INT3_12/ADC12/SNS12/PC4 ����7         22���� PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE/PGD
             PWM0_C1/INT3_11/ADC11/SNS11/PC3 ����8         21���� VCC
                     INT3_10/ADC10/SNS10/PC2 ����9         20���� VSS
               TXD0_D/INT3_9/ADC09/SNS09/PC1 ����10        19���� PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A
SDA0_B/RXD0_D/PWM0_B1/INT3_8/ADC08/SNS08/PC0 ����11        18���� PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A
          TXD1_B/COM7/INT3_7/ADC07/SNS07/PB7 ����12        17���� PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A
          RXD1_B/COM6/INT3_6/ADC06/SNS06/PB6 ����13        16���� PB3/SNS03/ADC03/INT3_3/COM3/PWM0_D/RXD0_B
  SCL0_B/PWM0_A1/COM5/INT3_5/ADC05/SNS05/PB5 ����14        15���� PB4/SNS04/ADC04/INT3_4/COM4/TXD0_B
                                              ����������������������������
											     XS16TK05B
*/
//************************************************************************************
/*
                                              ������������  ������������
             PWM0_C1/INT3_11/ADC11/SNS11/PC3 ����1   ��������  28���� PC4/SNS12/ADC12/INT3_12
                     INT3_10/ADC10/SNS10/PC2 ����2         27���� PC5/SNS13/ADC13/INT3_13/PWM0_D1
               TXD0_D/INT3_9/ADC09/SNS09/PC1 ����3         26���� PC6/SNS14/ADC14/INT3_14/PWM1_A1
SDA0_B/RXD0_D/PWM0_B1/INT3_8/ADC08/SNS08/PC0 ����4         25���� PC7/SNS15/ADC15/INT3_15/PWM2_A1
          TXD1_B/COM7/INT3_7/ADC07/SNS07/PB7 ����5         24���� PD0/SNS16/ADC16/INT0/PWM1_A
          RXD1_B/COM6/INT3_6/ADC06/SNS06/PB6 ����6         23���� PD1/SNS17/ADC17/INT3_16/PWM2_A
  SCL0_B/PWM0_A1/COM5/INT3_5/ADC05/SNS05/PB5 ����7         22���� PD2/SNS18/ADC18/INT3_17/XTAL_OUT
          TXD0_B/COM4/INT3_4/ADC04/SNS04/PB4 ����8         21���� PD3/SNS19/ADC19/INT3_18/XTAL_IN
   RXD0_B/PWM0_D/COM3/INT3_3/ADC03/SNS03/PB3 ����9         20���� PD4/SNS20/ADC20/INT3_19/RXD0_C
   TXD1_A/PWM0_C/COM2/INT3_2/ADC02/SNS02/PB2 ����10        19���� PD5/SNS21/ADC21/INT3_20/TXD0_C
   RXD1_A/PWM0_B/COM1/INT3_1/ADC01/SNS01/PB1 ����11        18���� PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C
          PWM0_A/COM0/INT3_0/ADC00/SNS00/PB0 ����12        17���� PD7/SNS23/ADC23/INT2/RXD0_F
                                         VSS ����13        16���� PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC
                                         VCC ����14        15���� PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE/PGD
                                              ����������������������������
												 XS16TK05C

*/
//************************************************************************************
/*
                                              ������������  ������������
SWE2/PGD2/SDA0_C/RXD0_E/INT1/ADC22/SNS22/PD6 ����1   ��������  16���� PD7/SNS23/ADC23/INT2/RXD0_F/PGC2
			 XTAL_IN/INT3_18/ADC19/SNS19/PD3 ����2         15���� PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC0
			XTAL_OUT/INT3_17/ADC18/SNS18/PD2 ����3         14���� PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE0/PGD0
			  PWM2_A/INT3_16/ADC17/SNS17/PD1 ����4         13���� VCC
		  RXD1_B/COM6/INT3_6/ADC06/SNS06/PB6 ����5         12���� VSS
  SCL0_B/PWM0_A1/COM5/INT3_5/ADC05/SNS05/PB5 ����6         11���� PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A
		  TXD0_B/COM4/INT3_4/ADC04/SNS04/PB4 ����7         10���� PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A
   RXD0_B/PWM0_D/COM3/INT3_3/ADC03/SNS03/PB3 ����8          9���� PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A
                                              ����������������������������
												 XS16TK05F
*/

/*-------------------------------------------------------------------------------------
                                      I/0�ڶ�Ӧ���
---------------------------------------------------------------------------------------
;оƬ�ͺ�:XS16TK06A
|(01)PC7/SNS15/ADC15/INT3_15/PWM2_A1			<--> KEY2 ����/ȡ��					SEG5		
|(02)PC6/SNS14/ADC14/INT3_14/PWM1_A1 			<--> KEY4 ��					SEG2		
|(03)PC5/SNS13/ADC13/INT3_13/PWM0_D1			<--> JDQ ����				SEG4		
|(04)PC4/SNS12/ADC12/INT3_12					<--> SEG9 L1- L3- L4- L6-		SEG6		
|(05)PC3/SNS11/ADC11/INT3_11/PWM0_C1			<--> zero					KKG_A		
|(06)PC2/SNS10/ADC10/INT3_10					<--> NTC/BUZ				NTC_A/BUZ	
|(07)PC0/SNS08/ADC08/INT3_8/PWM0_B1/RXD0_D		<--> KEY1 ԤԼ/����					NTC_B		
|(08)PB7/SNS07/ADC07/INT3_7/TXD1_B				<--> KEY3 ��					ZERO		
|(09)VSS										<--> 0V						0V		
|(10)VCC										<--> 5V						5V	

|(11)PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E		<--> KKG ����				KEY6	
|(12)PA0/SNS24/ADC24/INT3_21/RXD0_A/TXD0_F		<--> SEG8 L1+				KEY5	
|(13)PD7/SNS23/ADC23/INT2/RXD0_F				<--> SEG7 L4+				KEY4	
|(14)PD6/SNS22/ADC22/INT1/RXD0_E				<--> SEG4					KEY3	
|(15)PD5/SNS21/ADC21/INT3_20/TXD0_C				<--> SEG3 L2+				KEY2	
|(16)PD4/SNS20/ADC20/INT3_19/RXD0_C				<--> SEG10 L2- L5-			KEY1	
|(17)PD3/SNS19/ADC19/INT3_18/XTAL_IN			<--> SEG2 L5+				OUT_B	
|(18)PD2/SNS18/ADC18/INT3_17/XTAL_OUT			<--> SEG1					SEG1	
|(19)PD1/SNS17/ADC17/INT3_16/PWM2_A				<--> SEG6 L6+				SEG7	
|(20)PD0/SNS16/ADC16/INT0/PWM1_A				<--> SEG5 L3+				SEG3	
*/

/*-------------------------------------------------------------------------------------
                                      I/0�ڶ�Ӧ���
-------------------------------------------------------------------------------------
;оƬ�ͺ�:XS16TK06B
|(01)PD2/SNS18/ADC18/INT3_17/XTAL_OUT 								<-->	
|(02)PD1/SNS17/ADC17/INT3_16/PWM2_A									<-->	
|(03)PD0/SNS16/ADC16/INT0/PWM1_A									<-->	
|(04)PC7/SNS15/ADC15/INT3_15/PWM2_A1								<-->	
|(05)PC6/SNS14/ADC14/INT3_14/PWM1_A1								<-->	
|(06)PC5/SNS13/ADC13/INT3_13/PWM0_D1								<-->	
|(07)PC4/SNS12/ADC12/INT3_12										<-->	
|(08)PC3/SNS11/ADC11/INT3_11/PWM0_C1								<-->	
|(09)PC2/SNS10/ADC10/INT3_10										<-->	
|(10)PC1/SNS09/ADC09/INT3_9/TXD0_D									<-->	
|(11)PC0/SNS08/ADC08/INT3_8/PWM0_B1/RXD0_D/SDA0_B					<-->	
|(12)PB7/SNS07/ADC07/INT3_7/COM7/TXD1_B								<-->	
|(13)PB6/SNS06/ADC06/INT3_6/COM6/RXD1_B								<-->	
|(14)PB5/SNS05/ADC05/INT3_5/COM5/PWM0_A1/SCL0_B						<-->

|(15)PB4/SNS04/ADC04/INT3_4/COM4/TXD0_B								<-->	
|(16)PB3/SNS03/ADC03/INT3_3/COM3/PWM0_D/RXD0_B						<-->	
|(17)PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A						<-->	
|(18)PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A						<-->	
|(19)PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A								<-->	
|(20)VSS															<-->	
|(21)VCC															<-->	
|(22)PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE0/PGD0	<-->	
|(23)PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC0				<-->	
|(24)PD7/SNS23/ADC23/INT2/RXD0_F/PGC2								<-->	
|(25)PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C/SWE2/PGD2					<-->	
|(26)PD5/SNS21/ADC21/INT3_20/TXD0_C/PGC1							<-->	
|(27)PD4/SNS20/ADC20/INT3_19/RXD0_C/SWE1/PGD1						<-->	
|(28)PD3/SNS19/ADC19/INT3_18/XTAL_IN								<-->		
*/

/*-------------------------------------------------------------------------------------
                                      I/0�ڶ�Ӧ���
;;-------------------------------------------------------------------------------------
;оƬ�ͺ�:XS16TK06C
|(01)PC3/SNS11/ADC11/INT3_11/PWM0_C1 			<-->	
|(02)PC2/SNS10/ADC10/INT3_10					<-->	
|(03)PC1/SNS09/ADC09/INT3_9/TXD0_D				<-->	
|(04)PC0/SNS08/ADC08/INT3_8/PWM0_B1/RXD0_D		<-->	
|(05)PB7/SNS07/ADC07/INT3_7/COM7/TXD1_B				<-->	
|(06)PB6/SNS06/ADC06/INT3_6/COM6/RXD1_B				<-->	
|(07)PB5/SNS05/ADC05/INT3_5/COM5/COM5/PWM0_A1		<-->	
|(08)PB4/SNS04/ADC04/INT3_4/COM4/TXD0_B				<-->	
|(09)PB3/SNS03/ADC03/INT3_3/COM3/PWM0_D/RXD0_B		<-->	
|(10)PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A		<-->	
|(11)PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A		<-->	
|(12)PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A				<-->	
|(13)VSS										<-->	
|(14)VCC										<-->	

|(15)PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E		<-->	
|(16)PA0/SNS24/ADC24/INT3_21/RXD0_A/TXD0_F		<-->	
|(17)PD7/SNS23/ADC23/INT2/RXD0_F				<-->	
|(18)PD6/SNS22/ADC22/INT1/RXD0_E				<-->	
|(19)PD5/SNS21/ADC21/INT3_20/TXD0_C				<-->	
|(20)PD4/SNS20/ADC20/INT3_19/RXD0_C				<-->	
|(21)PD3/SNS19/ADC19/INT3_18/XTAL_IN			<-->	
|(22)PD2/SNS18/ADC18/INT3_17/XTAL_OUT			<-->	
|(23)PD1/SNS17/ADC17/INT3_16/PWM2_A				<-->	
|(24)PD0/SNS16/ADC16/INT0/PWM1_A				<-->	
|(25)PC7/SNS15/ADC15/INT3_15/PWM2_A1			<-->	
|(26)PC6/SNS14/ADC14/INT3_14/PWM1_A1			<-->	
|(27)PC5/SNS13/ADC13/INT3_13/PWM0_D1			<-->	
|(28)PC4/SNS12/ADC12/INT3_12					<-->	  	
*/
/*-------------------------------------------------------------------------------------
                                      I/0�ڶ�Ӧ���
;;-------------------------------------------------------------------------------------
;оƬ�ͺ�:XS16TK06F
|(01)PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C/PGD2/SWE2		<--> KEY3
|(02)PD3/SNS19/ADC19/INT3_18/XTAL_IN					<--> JDQ ����
|(03)PD2/SNS18/ADC18/INT3_17/XTAL_OUT					<--> COM1 LED����
|(04)PD1/SNS17/ADC17/INT3_16/PWM2_A						<--> SEG1 LED1+
|(05)PB6/ADC06/INT3_6/COM6/RXD1_B						<--> SEG2 LED3+
|(06)PB5/SNS05/ADC05/INT3_5/COM5/PWM0_A1/SCL0_B			<--> SEG3
|(07)PB4/SNS04/ADC04/INT3_4/COM4/TXD0_B					<--> NTC 27K���� 100kNTC
|(08)PB3/SNS03/ADC03/INT3_3/COM3/PWM0_D/RXD0_B			<--> KEY1 

|(09)PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A			<--> BUZ ����	ZERO
|(10)PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A			<--> SEG5 LED2+
|(11)PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A					<--> SEG4 LED4+
|(12)VSS												<--> 0V
|(13)VCC												<--> 5V
|(14)PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/PGD0	<--> KEY2
|(15)PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC0	<--> KEY4
|(16)PD7/SNS23/ADC23/INT2/RXD0_F/PGC2					<--> ZERO		BUZ ����	
*/

/*��������
GPIO<PA0-PA7><PB0-PB7><PC0-PC7><PD0-PD7>
COM0-COM7: ��������
SNS0-SNS25: ��������ͨ�� 
ADC0-ADC25: ADC ͨ��
INT1: �ⲿ�ж� 1
INT2: �ⲿ�ж� 2
INT3_0-INT3_22: �ⲿ�ж� 3  
PWM0_X (A,B,C,D,A1,B1,C1,D1):PWM0 �����
PWM1_X (A,A1):PWM1 �����
PWM2_X (A,A1):PWM2 �����
XTAL_OUT: �ⲿ�������
XTAL_IN: �ⲿ��������

SWE1: ���߷����
SWE2: ���߷����
PGD2: ��¼��
*/

//-----------------------------------------------------------------//
//�������ƣ� void CFG_Check(void)
//�������ܣ� �����ֶԱ��ж�(��ӦMCU04оƬ)
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
uchar xdata CFG_Rb = 80;
void CFG_Check(void)
{   
	unsigned char i = 0;
	unsigned int	code add_cfg[9] =     {0x407F,0x407D,0x407B,0x4079,0x4077,0x4075,0x4073,0x4071,0x406F};
	unsigned char code add_cfg_Bit[9] = {0x00,	 0x1F,	0x3F,	 0xFF,	0xFF,	 0xFF,	0x3F,	 0xFF,  0x7F};
	uint rom_offset = 0;
	EA = 0;//�����ж�
	REG_ADDR = 0x23;
	rom_offset = ((uint)REG_DATA)<<8;
	REG_ADDR = 0x22;
	rom_offset |= REG_DATA;
	for(i = 1; i < 9;i++)
	{
		REG_ADDR = i+1;
	
		if((CBYTE[add_cfg[i]-rom_offset]&add_cfg_Bit[i]) != (REG_DATA&add_cfg_Bit[i]))
		{
			SOFT_RST = 0x55;
		}	
	}
	
	if((CBYTE[0x404D-rom_offset] >= 64)&&(CBYTE[0x404D-rom_offset] <= 96))
	{
		CFG_Rb=CBYTE[0x404D-rom_offset];
	}

	P2_XH = 0;//ʹ��MOVX ����PDATA��ʱ��P2_XH��0
	EA = 1;//�����ж�	
	
}
//-----------------------------------------------------------------//
//�������ƣ� void Delay_Us(uint us)
//�������ܣ� ��ʱΪ��us
//��������� us
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//


//void Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
//{
//	for (; us > 0; us--)
//	{	
//		WDT_CTRL = 0x07;
//	}		
//}
 

//-----------------------------------------------------------------//
//�������ƣ� void Bor_Init(void)
//�������ܣ� ���縴λ��ʼ��
//��������� �� 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Bor_Init(void) 
{
	EA = 0;
	V_BOR_SET(2);//���õ��縴λ��:(0/1-����)-(2-2.8V)-(3-3.3V)-(4-3.7V)-(5/6/7-4.2V)
	BOR_DELAY_SET(1);//0��ʱ1��1��ʱ2;(��ʱ�����������)
	
	BOR_ON;//�������縴λ
	EA = 1;
}

//-----------------------------------------------------------------//
//�������ƣ� void Set_Sys_Clk(void)
//�������ܣ� ϵͳʱ������
//��������� �� 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Set_Sys_Clk(void) 
{
	SYS_CLK_SET(SYSCLK_SEL);//ϵͳʱ��ѡ��0-12MHz,1-6MHZ,2-4MHZ,3-1MHz
}
 

//-----------------------------------------------------------------//
//�������ƣ� void Pow_Delay(uint t)
//�������ܣ� �ϵ���ʱ����������ʵ��Ӧ�����ѡ����á�
//��������� t
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//



//void Pow_Up_Delay(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms*2@12MHz;1000-1000ms
//{  
//	uint a = 954,b = ms;

//	for (b = ms; b > 0; b--)
//	{
//		for (a = 954; a > 0; a--)
//		{
//			WDT_CTRL = 0x07;
//		} 
//	}	

//}


//-----------------------------------------------------------------//
//�������ƣ� void Delay_Ms(uint t)
//�������ܣ� ms��ʱ����
//��������� t
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//


//	void Delay_Ms(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
//	{  
//		uint a = 954,b = ms;
//		for (b = ms; b > 0; b--)
//		{
//			for (a = 954; a > 0; a--)
//			{
//				WDT_CTRL = 0x07;
//			} 
//		}	
//	}
	

	


//-----------------------------------------------------------------//
//�������ƣ� void WDT_Init(void)
//�������ܣ� ���Ź���ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void WDT_Init(void)
{

		EA = 0;//�����жϣ�
		WDT_IP_CLR;//����WDT�ж��ż�Ϊ�ͣ�����ʵ��Ӧ���������ȼ�
		WDT_INT_FLAG_CLR;//������Ź��жϱ�־
		WDT_ON_OFF(0);//������0x55ʱ�رտ��Ź�
		WDT_CTRL = 7;//����WDT���ʱ��(0~7--18ms~2.304S)7--2.304S
		WDT_IE_SET;	//��WDT�ж�ʹ��
		EA = 1;//�����ж�	
}


//-----------------------------------------------------------------//
//�������ƣ� void Init_IO(void)
//�������ܣ� IO�ڳ�ʼ��,��û���õ��Ļ����յ�IO�ڣ�����ΪIO���Ϊ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Init_IO(void)
{

}

//-----------------------------------------------------------------//
//�������ƣ� void Default_Set_IO(void)
//�������ܣ� Ĭ��IO������
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Default_Set_IO(void)
{   

		SNS_IO_SEL1 = 0x00;//bit0~bit7-0������ΪIO�ڣ�1������ΪSNS��
		SNS_IO_SEL2 = 0x00;//bit0~bit7-0������ΪIO�ڣ�1������ΪSNS��
		SNS_IO_SEL3 = 0x00;//bit0~bit7-0������ΪIO�ڣ�1������ΪSNS��
		SNS_IO_SEL4 = 0x00;//bit0~bit1-0������ΪIO�ڣ�1������ΪSNS��
	
		/*cubic*/
		IICCON &= ~0x01;//IIC������ʹ��
		ODRAIN_EN  =b(00000000);	//1����©����� 0��CMOS��� ��֧��PD6/PA1/PA0	
		COM_IO_SEL =b(00000000); 	//1:������� 0:����IO��
		PD_PB = b(00000000);		//0������Ϊ������ʹ�ܣ�1������Ϊ����ʹ�ܣ�


		DATAA = b(00000010);	//0������Ϊ����ͣ�1������Ϊ����ߣ�
		TRISA = b(00000000);	//0������Ϊ�����1������Ϊ���룻	
		PU_PA = b(00000000);	//0������Ϊ������ʹ�ܣ�1������Ϊ����ʹ�ܣ�
		
		DATAB = b(00000000);
		TRISB = b(00000000);	//b(00010100);
		PU_PB = b(00000000);
		
		DATAC = b(00000000);
		TRISC = b(00001000);	
		PU_PC = b(00000000);	

		DATAD = b(00000000);
		TRISD = b(00000000);	
		PU_PD = b(00000000);	

}


//-----------------------------------------------------------------//
//�������ƣ� void Function_Init(void)
//�������ܣ� ����ģ���ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Function_Init(void)
{
		
	#if (TRACEMODE == TRUE)
			XS16TK06X_Trace_Mode_Init(0);//����ģʽ��ʼ��
	#endif
	
	#ifdef Timer0_EN
		#if Timer0_EN

			Timer0_Init(1000);//��ʱ��0��ʼ��

		#endif
	#endif
	
	#ifdef Timer1_EN
		#if Timer1_EN

			Timer1_Init(c_timer1US);//��ʱ��1��ʼ��

		#endif
	#endif
	
	#ifdef Timer2_EN
		#if Timer2_EN
		
			Timer2_Init(1000);//��ʱ��2��ʼ��

		#endif
	#endif
	
	#ifdef IDLE_MODE
		#if IDLE_MODE
			Idle_Wake_Up_Init(5000,3);//Idle��ʼ��
		#endif 
	#endif
	
	#ifdef UART0_EN
		#if(UART0_EN == 1)
			UART0_Init();//UART0��ʼ��
		#endif
	#endif
	
	#ifdef UART1_EN
		#if(UART1_EN == 1)
			UART1_Init();//UART1��ʼ��
		#endif
	#endif
	
	#ifdef PWM0_EN
		#if (PWM0_EN == 1)
		
			PWM0_Init();
			
			#if (PWM0_CH0_EN)
			PWM0A_Set(38000,50);
			#endif
			
			#if (PWM0_CH1_EN)
				PWM0B_Set(38000,50);
			#endif
			
			#if (PWM0_CH2_EN)
				//PWM0C_Set(38000,50);
				PWM0C_Set(38000,100);
			#endif
			
			#if (PWM0_CH3_EN)
				PWM0D_Set(38000,50);
			#endif

		#endif
	#endif
	
	#ifdef PWM1_EN
		#if (PWM1_EN == 1)
			PWM1_Init();
			PWM1_Set(1,38000,50);
		#endif
	#endif
	
	#ifdef PWM2_EN
		#if (PWM2_EN == 1)
			PWM2_Init();
			PWM2_Set(1,38000,50);
		#endif
	#endif
	
		
	#ifdef ExtInt0_EN
		#if ExtInt0_EN
			ExtInt0_Init(ExtInt0_MODE);
		#endif
	#endif
	
	#ifdef ExtInt1_EN
		#if ExtInt1_EN
			ExtInt1_Init(ExtInt1_MODE);
		#endif
	#endif
	
	#ifdef ExtInt2_EN
		#if ExtInt2_EN
			ExtInt2_Init(ExtInt2_MODE);
		#endif
	#endif
	
	#ifdef ExtInt3_EN
		#if ExtInt3_EN
			ExtInt3_Init(ExtInt3_MODE,ExtInt3_SEL);
		#endif
	#endif
	
	#ifdef VolDet_EN
		#if ((VolDet_EN == 1))
			LVDT_Init();
		#endif
	#endif
	
	
	#ifdef EEPROM_EN
		#if ((EEPROM_EN == 1))
			Eeprom_Init();
		#endif
	#endif
	

	#ifdef ADC_IS_OPEN
		#if ADC_IS_OPEN
			ADC_Init();
		#endif
	#endif
		
	#if (TRACEMODE == FALSE)
		#ifdef IICS_EN
			#if IICS_EN
				IIC_Slave_Init(0xC0,0);
			#endif
		#endif
	#endif
	

	#ifdef SNS_NUM
		#if SNS_NUM
			//CTK��ʼ��	
			CTK_Init();
		#endif
	#endif
}

//-----------------------------------------------------------------//
//�������ƣ� void MCU_Init(void)
//��������:		MUC��ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void MCU_Init(void)
{	 
	//���縴λ��ʼ��
	Bor_Init();
	
	//���Ź���ʼ��
	WDT_Init();

	//���ú˹���ʱ��
	Set_Sys_Clk();
	

	//�����ֶԱ��ж�
	CFG_Check();

	//IO��Ĭ������
	Default_Set_IO();
	
	//IO�ڳ�ʼ��
	Init_IO();

	//���ܺ�����ʼ��
	Function_Init(); 
	
}