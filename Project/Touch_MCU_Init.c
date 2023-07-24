#include "Config.h"
//#include 	".\Application_Library\Global.h"

/********************************************************************
工程名称:暖菜机 XS-FC-OLK-01-011-B
芯片:XS16TK06F-16SOP 
关键字:继电器,4键触摸,2位5线数码管,短按,长按,长按连续,非隔离
注意事项:
创建日期:2022年10月7日14:38:14
修改日期:2022年10月7日14:38:17
*********************************************************************/
/*700W
;轻触按钮:□ ,触摸按钮:◎ ,LED:★
;;			  _    _  . _    _ 
;			 /_/  /_/  /_/  /_/ 	
;			/_/  /_/  /_/  /_/
;
;	★爆炒(L1)    ★炖煮(L2)	★清蒸(L3)       
;	  
;	★慢炖(L4)    ★牛排(L5)	★火锅(L6)	  
;			
;	◎预约/保温(KEY1) 	 ◎功能/取消(KEY2)		
;	◎减(KEY3)			◎加(KEY4)		      												
*/

//*******************************************************************
//************************MCU基本信息*********************************
//◆ 内核：高速 8051
//	§ 工作频率： 12MHz、 6MHz、 4MHz、 1MHz
//	§ 时钟偏差： ±1% @-20℃~65℃, 5V
//				±3% @-40℃~85℃, 5V
//◆ 存储器（SMTP）
//	§ CODE： 16K Bytes
//	§ DATA： 1K Bytes
//	§ SRAM： 256 Bytes(data)+512 Bytes(xdata)
//	§ 支持 BOOT 功能区， 1/2/3/4K 可选
//◆ 时钟源，复位和电源管理
//	§ 内部低速时钟 LIRC： 32kHz， 时钟偏差：
//	  ±10%@25℃, 5V， ±20% @-40℃~85℃, 5V
//	§ 内部高速 RC 振荡器： 1MHz
//	§ 外部晶体振荡器： 32768Hz/4MHz
//	§ 8 种复位， 掉电复位电压（BOR）：
//	  2.8V/3.3V/3.7V/4.2V
//	§ 低电压检测： 2.7V/3.0V/3.3V/3.6V/3.9V/4.2V
//◆ IO
//	§ PB 口内置上拉/下拉电阻 28k，其他 IO 口内置上
//	  拉电阻 4.7k
//	§ 大灌电流口(PB0~PB7)
//	§ 支持器件外设功能复用
//	§ 所有 IO 口都支持外部中断功能， INT0~2 外部中
//	  断(上升沿、下降沿、双沿)， INT3 共用中断源(上
//	  升沿、下降沿)
//◆ 通信模块
//	§ 2xUART 通信，支持 IO 映射
//	§ 1xIIC 硬件从机通信，支持 100kHz/400kHz
//◆ 16-bit PWM
//	§ PWM0 支持 4 路通道，共用周期， 占空比和极性
//可配
//	§ PWM1/2 均支持 1 路通道输出
//◆ 工作电压： 2.7V ~ 5.5V
//◆ 工作温度： -40℃ ~ 85℃
//	§ 增强型工业级，符合 JESD 工业级可靠性认
//证标准
//◆ 高精度 12 位 ADC
//	§ 最多可达 26 个模拟输入通道
//	§ 参考电压： VCC/2V/4V
//◆ 中断
//	§ 两级中断优先级可选
//	§ ADC， CSD， INT0/1/2/3， LVDT，
//	  Timer0/1/2， WDT， UART0/1， IIC
//◆ 定时器
//	§ 3 个 16 位 Timer
//	§ Timer2 时钟源为内部低速时钟 LIRC32k 或
//	  外部晶振 32768Hz/4MHz
//	§ 看门狗定时器，溢出时间 18ms 到 2.304s
//◆ 低功耗模式
//	§ 空闲模式和休眠模式
//	§ 深度休眠，功耗 7μA @5V 典型
//◆ 触摸按键
//	§ 各按键的灵敏度可独立设置
//	§ 电容按键，均可复用为 GPIO
//◆ 两线烧录单线调试仿真接口
//◆ 封装
//	§ SOP16/SOP20/SOP28


//*******************************************************************
//***************************整体概述*********************************
//XS16TK06X 采用高速 8051 内核， 1T 指令周期，相比于标准的 8051(12T)指令周期，具
//有更快的运行速度，同时兼容标准 8051 指令。
//XS16TK06X 包含外设有看门狗、 按键检测、 IIC、 UART、低电压检测、掉电复位、 3 路
//16bit PWM、 Timer0、 Timer1、 Timer2、 12bit 高精度逐次逼近 ADC、低功耗模式等。
//XS16TK06X 集成的电容检测通道，它可以用来检测近距离感应或者触摸。其内置
//MCU，可灵活配置；通过配置可实现按键、滚轮、滑条等多种应用。按键都能独立运行，
//并且每个按键都能通过对相应的功能寄存器来调节灵敏度。

//**************************************************************************
//*********************************MCU引脚图*********************************
//**************************************************************************
/*
                                              ┏━━━━┓  ┏━━━━┓
             PWM2_A1/INT3_15/ADC15/SNS15/PC7 ━┃1   ┗━━┛  20┃━ PD0/SNS16/ADC16/INT0/PWM1_A
             PWM1_A1/INT3_14/ADC14/SNS14/PC6 ━┃2         19┃━ PD1/SNS17/ADC17/INT3_16/PWM2_A
             PWM0_D1/INT3_13/ADC13/SNS13/PC5 ━┃3         18┃━ PD2/SNS18/ADC18/INT3_17/XTAL_OUT
                     INT3_12/ADC12/SNS12/PC4 ━┃4         17┃━ PD3/SNS19/ADC19/INT3_18/XTAL_IN
             PWM0_C1/INT3_11/ADC11/SNS11/PC3 ━┃5         16┃━ PD4/SNS20/ADC20/INT3_19/RXD0_C
                     INT3_10/ADC10/SNS10/PC2 ━┃6         15┃━ PD5/SNS21/ADC21/INT3_20/TXD0_C
SDA0_B/RXD0_D/PWM0_B1/INT3_8/ADC08/SNS08/PC0 ━┃7         14┃━ PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C
          TXD1_B/COM7/INT3_7/ADC07/SNS07/PB7 ━┃8         13┃━ PD7/SNS23/ADC23/INT2/RXD0_F
                                         VSS ━┃9         12┃━ PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC
                                         VCC ━┃10        11┃━ PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE/PGD
                                              ┗━━━━━━━━━━━━┛
											     XS16TK06A
*/
//************************************************************************************
/*
                                              ┏━━━━┓  ┏━━━━┓
            XTAL_OUT/INT3_17/ADC18/SNS18/PD2 ━┃1   ┗━━┛  28┃━ PD3/SNS19/ADC19/INT3_18/XTAL_IN
              PWM2_A/INT3_16/ADC17/SNS17/PD1 ━┃2         27┃━ PD4/SNS20/ADC20/INT3_19/RXD0_C
                 PWM1_A/INT0/ADC16/SNS16/PD0 ━┃3         26┃━ PD5/SNS21/ADC21/INT3_20/TXD0_C
             PWM2_A1/INT3_15/ADC15/SNS15/PC7 ━┃4         25┃━ PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C
             PWM1_A1/INT3_14/ADC14/SNS14/PC6 ━┃5         24┃━ PD7/SNS23/ADC23/INT2/RXD0_F
             PWM0_D1/INT3_13/ADC13/SNS13/PC5 ━┃6         23┃━ PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC
                     INT3_12/ADC12/SNS12/PC4 ━┃7         22┃━ PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE/PGD
             PWM0_C1/INT3_11/ADC11/SNS11/PC3 ━┃8         21┃━ VCC
                     INT3_10/ADC10/SNS10/PC2 ━┃9         20┃━ VSS
               TXD0_D/INT3_9/ADC09/SNS09/PC1 ━┃10        19┃━ PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A
SDA0_B/RXD0_D/PWM0_B1/INT3_8/ADC08/SNS08/PC0 ━┃11        18┃━ PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A
          TXD1_B/COM7/INT3_7/ADC07/SNS07/PB7 ━┃12        17┃━ PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A
          RXD1_B/COM6/INT3_6/ADC06/SNS06/PB6 ━┃13        16┃━ PB3/SNS03/ADC03/INT3_3/COM3/PWM0_D/RXD0_B
  SCL0_B/PWM0_A1/COM5/INT3_5/ADC05/SNS05/PB5 ━┃14        15┃━ PB4/SNS04/ADC04/INT3_4/COM4/TXD0_B
                                              ┗━━━━━━━━━━━━┛
											     XS16TK05B
*/
//************************************************************************************
/*
                                              ┏━━━━┓  ┏━━━━┓
             PWM0_C1/INT3_11/ADC11/SNS11/PC3 ━┃1   ┗━━┛  28┃━ PC4/SNS12/ADC12/INT3_12
                     INT3_10/ADC10/SNS10/PC2 ━┃2         27┃━ PC5/SNS13/ADC13/INT3_13/PWM0_D1
               TXD0_D/INT3_9/ADC09/SNS09/PC1 ━┃3         26┃━ PC6/SNS14/ADC14/INT3_14/PWM1_A1
SDA0_B/RXD0_D/PWM0_B1/INT3_8/ADC08/SNS08/PC0 ━┃4         25┃━ PC7/SNS15/ADC15/INT3_15/PWM2_A1
          TXD1_B/COM7/INT3_7/ADC07/SNS07/PB7 ━┃5         24┃━ PD0/SNS16/ADC16/INT0/PWM1_A
          RXD1_B/COM6/INT3_6/ADC06/SNS06/PB6 ━┃6         23┃━ PD1/SNS17/ADC17/INT3_16/PWM2_A
  SCL0_B/PWM0_A1/COM5/INT3_5/ADC05/SNS05/PB5 ━┃7         22┃━ PD2/SNS18/ADC18/INT3_17/XTAL_OUT
          TXD0_B/COM4/INT3_4/ADC04/SNS04/PB4 ━┃8         21┃━ PD3/SNS19/ADC19/INT3_18/XTAL_IN
   RXD0_B/PWM0_D/COM3/INT3_3/ADC03/SNS03/PB3 ━┃9         20┃━ PD4/SNS20/ADC20/INT3_19/RXD0_C
   TXD1_A/PWM0_C/COM2/INT3_2/ADC02/SNS02/PB2 ━┃10        19┃━ PD5/SNS21/ADC21/INT3_20/TXD0_C
   RXD1_A/PWM0_B/COM1/INT3_1/ADC01/SNS01/PB1 ━┃11        18┃━ PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C
          PWM0_A/COM0/INT3_0/ADC00/SNS00/PB0 ━┃12        17┃━ PD7/SNS23/ADC23/INT2/RXD0_F
                                         VSS ━┃13        16┃━ PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC
                                         VCC ━┃14        15┃━ PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE/PGD
                                              ┗━━━━━━━━━━━━┛
												 XS16TK05C

*/
//************************************************************************************
/*
                                              ┏━━━━┓  ┏━━━━┓
SWE2/PGD2/SDA0_C/RXD0_E/INT1/ADC22/SNS22/PD6 ━┃1   ┗━━┛  16┃━ PD7/SNS23/ADC23/INT2/RXD0_F/PGC2
			 XTAL_IN/INT3_18/ADC19/SNS19/PD3 ━┃2         15┃━ PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC0
			XTAL_OUT/INT3_17/ADC18/SNS18/PD2 ━┃3         14┃━ PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/SCL0_C/SWE0/PGD0
			  PWM2_A/INT3_16/ADC17/SNS17/PD1 ━┃4         13┃━ VCC
		  RXD1_B/COM6/INT3_6/ADC06/SNS06/PB6 ━┃5         12┃━ VSS
  SCL0_B/PWM0_A1/COM5/INT3_5/ADC05/SNS05/PB5 ━┃6         11┃━ PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A
		  TXD0_B/COM4/INT3_4/ADC04/SNS04/PB4 ━┃7         10┃━ PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A
   RXD0_B/PWM0_D/COM3/INT3_3/ADC03/SNS03/PB3 ━┃8          9┃━ PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A
                                              ┗━━━━━━━━━━━━┛
												 XS16TK05F
*/

/*-------------------------------------------------------------------------------------
                                      I/0口对应简介
---------------------------------------------------------------------------------------
;芯片型号:XS16TK06A
|(01)PC7/SNS15/ADC15/INT3_15/PWM2_A1			<--> KEY2 功能/取消					SEG5		
|(02)PC6/SNS14/ADC14/INT3_14/PWM1_A1 			<--> KEY4 加					SEG2		
|(03)PC5/SNS13/ADC13/INT3_13/PWM0_D1			<--> JDQ 高驱				SEG4		
|(04)PC4/SNS12/ADC12/INT3_12					<--> SEG9 L1- L3- L4- L6-		SEG6		
|(05)PC3/SNS11/ADC11/INT3_11/PWM0_C1			<--> zero					KKG_A		
|(06)PC2/SNS10/ADC10/INT3_10					<--> NTC/BUZ				NTC_A/BUZ	
|(07)PC0/SNS08/ADC08/INT3_8/PWM0_B1/RXD0_D		<--> KEY1 预约/保温					NTC_B		
|(08)PB7/SNS07/ADC07/INT3_7/TXD1_B				<--> KEY3 减					ZERO		
|(09)VSS										<--> 0V						0V		
|(10)VCC										<--> 5V						5V	

|(11)PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E		<--> KKG 低驱				KEY6	
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
                                      I/0口对应简介
-------------------------------------------------------------------------------------
;芯片型号:XS16TK06B
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
                                      I/0口对应简介
;;-------------------------------------------------------------------------------------
;芯片型号:XS16TK06C
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
                                      I/0口对应简介
;;-------------------------------------------------------------------------------------
;芯片型号:XS16TK06F
|(01)PD6/SNS22/ADC22/INT1/RXD0_E/SDA0_C/PGD2/SWE2		<--> KEY3
|(02)PD3/SNS19/ADC19/INT3_18/XTAL_IN					<--> JDQ 高驱
|(03)PD2/SNS18/ADC18/INT3_17/XTAL_OUT					<--> COM1 LED共阴
|(04)PD1/SNS17/ADC17/INT3_16/PWM2_A						<--> SEG1 LED1+
|(05)PB6/ADC06/INT3_6/COM6/RXD1_B						<--> SEG2 LED3+
|(06)PB5/SNS05/ADC05/INT3_5/COM5/PWM0_A1/SCL0_B			<--> SEG3
|(07)PB4/SNS04/ADC04/INT3_4/COM4/TXD0_B					<--> NTC 27K上拉 100kNTC
|(08)PB3/SNS03/ADC03/INT3_3/COM3/PWM0_D/RXD0_B			<--> KEY1 

|(09)PB2/SNS02/ADC02/INT3_2/COM2/PWM0_C/TXD1_A			<--> BUZ 低驱	ZERO
|(10)PB1/SNS01/ADC01/INT3_1/COM1/PWM0_B/RXD1_A			<--> SEG5 LED2+
|(11)PB0/SNS00/ADC00/INT3_0/COM0/PWM0_A					<--> SEG4 LED4+
|(12)VSS												<--> 0V
|(13)VCC												<--> 5V
|(14)PA1/SNS25/ADC25/INT3_22/TXD0_A/TXD0_E/SDA0_A/PGD0	<--> KEY2
|(15)PA0/SNS24/ADC24/INT3_21/RXD0_A/SCL0_A/TXD0_F/PGC0	<--> KEY4
|(16)PD7/SNS23/ADC23/INT2/RXD0_F/PGC2					<--> ZERO		BUZ 低驱	
*/

/*功能描述
GPIO<PA0-PA7><PB0-PB7><PC0-PC7><PD0-PD7>
COM0-COM7: 大灌电流口
SNS0-SNS25: 触摸按键通道 
ADC0-ADC25: ADC 通道
INT1: 外部中断 1
INT2: 外部中断 2
INT3_0-INT3_22: 外部中断 3  
PWM0_X (A,B,C,D,A1,B1,C1,D1):PWM0 输出口
PWM1_X (A,A1):PWM1 输出口
PWM2_X (A,A1):PWM2 输出口
XTAL_OUT: 外部晶振输出
XTAL_IN: 外部晶振输入

SWE1: 单线仿真口
SWE2: 单线仿真口
PGD2: 烧录口
*/

//-----------------------------------------------------------------//
//函数名称： void CFG_Check(void)
//函数功能： 配置字对比判断(对应MCU04芯片)
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
uchar xdata CFG_Rb = 80;
void CFG_Check(void)
{   
	unsigned char i = 0;
	unsigned int	code add_cfg[9] =     {0x407F,0x407D,0x407B,0x4079,0x4077,0x4075,0x4073,0x4071,0x406F};
	unsigned char code add_cfg_Bit[9] = {0x00,	 0x1F,	0x3F,	 0xFF,	0xFF,	 0xFF,	0x3F,	 0xFF,  0x7F};
	uint rom_offset = 0;
	EA = 0;//关总中断
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

	P2_XH = 0;//使用MOVX 操作PDATA区时，P2_XH清0
	EA = 1;//开总中断	
	
}
//-----------------------------------------------------------------//
//函数名称： void Delay_Us(uint us)
//函数功能： 延时为几us
//输入参数： us
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//


//void Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
//{
//	for (; us > 0; us--)
//	{	
//		WDT_CTRL = 0x07;
//	}		
//}
 

//-----------------------------------------------------------------//
//函数名称： void Bor_Init(void)
//函数功能： 掉电复位初始化
//输入参数： 无 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Bor_Init(void) 
{
	EA = 0;
	V_BOR_SET(2);//设置掉电复位点:(0/1-保留)-(2-2.8V)-(3-3.3V)-(4-3.7V)-(5/6/7-4.2V)
	BOR_DELAY_SET(1);//0延时1，1延时2;(延时参数见规格书)
	
	BOR_ON;//开启掉电复位
	EA = 1;
}

//-----------------------------------------------------------------//
//函数名称： void Set_Sys_Clk(void)
//函数功能： 系统时钟设置
//输入参数： 无 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Set_Sys_Clk(void) 
{
	SYS_CLK_SET(SYSCLK_SEL);//系统时钟选择0-12MHz,1-6MHZ,2-4MHZ,3-1MHz
}
 

//-----------------------------------------------------------------//
//函数名称： void Pow_Delay(uint t)
//函数功能： 上电延时函数，根据实际应用情况选择调用。
//输入参数： t
//输出参数： 无
//返 回 值： 无
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
//函数名称： void Delay_Ms(uint t)
//函数功能： ms延时函数
//输入参数： t
//输出参数： 无
//返 回 值： 无
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
//函数名称： void WDT_Init(void)
//函数功能： 看门狗初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void WDT_Init(void)
{

		EA = 0;//关总中断；
		WDT_IP_CLR;//设置WDT中断优级为低，根据实际应运设置优先级
		WDT_INT_FLAG_CLR;//清除看门狗中断标志
		WDT_ON_OFF(0);//仅等于0x55时关闭看门狗
		WDT_CTRL = 7;//设置WDT溢出时间(0~7--18ms~2.304S)7--2.304S
		WDT_IE_SET;	//开WDT中断使能
		EA = 1;//开总中断	
}


//-----------------------------------------------------------------//
//函数名称： void Init_IO(void)
//函数功能： IO口初始化,将没有用到的或悬空的IO口，设置为IO输出为低
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Init_IO(void)
{

}

//-----------------------------------------------------------------//
//函数名称： void Default_Set_IO(void)
//函数功能： 默认IO口设置
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Default_Set_IO(void)
{   

		SNS_IO_SEL1 = 0x00;//bit0~bit7-0：设置为IO口；1：设置为SNS；
		SNS_IO_SEL2 = 0x00;//bit0~bit7-0：设置为IO口；1：设置为SNS；
		SNS_IO_SEL3 = 0x00;//bit0~bit7-0：设置为IO口；1：设置为SNS；
		SNS_IO_SEL4 = 0x00;//bit0~bit1-0：设置为IO口；1：设置为SNS；
	
		/*cubic*/
		IICCON &= ~0x01;//IIC工作关使能
		ODRAIN_EN  =b(00000000);	//1：开漏输出； 0：CMOS输出 仅支持PD6/PA1/PA0	
		COM_IO_SEL =b(00000000); 	//1:大电流口 0:正常IO口
		PD_PB = b(00000000);		//0：设置为下拉不使能；1：设置为下拉使能；


		DATAA = b(00000010);	//0：设置为输出低；1：设置为输出高；
		TRISA = b(00000000);	//0：设置为输出；1：设置为输入；	
		PU_PA = b(00000000);	//0：设置为上拉不使能；1：设置为上拉使能；
		
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
//函数名称： void Function_Init(void)
//函数功能： 功能模块初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Function_Init(void)
{
		
	#if (TRACEMODE == TRUE)
			XS16TK06X_Trace_Mode_Init(0);//调试模式初始化
	#endif
	
	#ifdef Timer0_EN
		#if Timer0_EN

			Timer0_Init(1000);//定时器0初始化

		#endif
	#endif
	
	#ifdef Timer1_EN
		#if Timer1_EN

			Timer1_Init(c_timer1US);//定时器1初始化

		#endif
	#endif
	
	#ifdef Timer2_EN
		#if Timer2_EN
		
			Timer2_Init(1000);//定时器2初始化

		#endif
	#endif
	
	#ifdef IDLE_MODE
		#if IDLE_MODE
			Idle_Wake_Up_Init(5000,3);//Idle初始化
		#endif 
	#endif
	
	#ifdef UART0_EN
		#if(UART0_EN == 1)
			UART0_Init();//UART0初始化
		#endif
	#endif
	
	#ifdef UART1_EN
		#if(UART1_EN == 1)
			UART1_Init();//UART1初始化
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
			//CTK初始化	
			CTK_Init();
		#endif
	#endif
}

//-----------------------------------------------------------------//
//函数名称： void MCU_Init(void)
//函数功能:		MUC初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void MCU_Init(void)
{	 
	//掉电复位初始化
	Bor_Init();
	
	//看门狗初始化
	WDT_Init();

	//配置核工作时钟
	Set_Sys_Clk();
	

	//配置字对比判断
	CFG_Check();

	//IO口默认设置
	Default_Set_IO();
	
	//IO口初始化
	Init_IO();

	//功能函数初始化
	Function_Init(); 
	
}