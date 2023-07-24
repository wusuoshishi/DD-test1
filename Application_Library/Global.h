#ifndef		__Global_H__
#define		__Global_H__

	
/*************************************************/
/*****************系统库头文件********************/
/*************************************************/	
#include 	"Config.h"
#include 	"intrins.h"
#include 	"string.h"

//------------------------------------------------------------------------------------------
//		检温部分参数设置
/*==========================================================================================     
说明:
配置AD口通道，配置AD口属性，配置温度表
==========================================================================================*/
#define   ad_en   1     //AD函数使能

#define		double_ad_channel	0	//是否双通道
#define		c_ad_channel	10	//AD通道1
#define		c_ad_up_pull	1	//AD口上拉参考电阻则置1，AD值取反便于运算	
#define		c_ad_mode 	0	//o温度  1普通AD

#if	double_ad_channel
	#define		c_ad_channel_1	8	//AD通道2
	#define		c_ad_up_pull_1	1	//AD口上拉参考电阻则置1，AD值取反便于运算	
	#define		c_ad_mode_1 	0	//o温度  1普通AD

#endif
	#define		c_bjhf_1	0	 //开路报警可恢复
	#define		c_bjhf_2	0   //短路报警可恢复
	#define		c_kltime		3	//开路报警时间（单位秒）工作才开始计时，为0则直接报警




#define		c_ntc_e1_return  0 //开路报错可恢复
#define		c_ntc_e2_return  0 //短路报错可恢复

//	温度表 可查0-136度	
#define		tab_50k_10k	0	//50K探头参考10K电阻
#define		tab_50k_27k	0	//50K探头参考27K电阻
#define		tab_100k_10k	0	//100K探头参考10K电阻
#define		tab_100k_27k	0	//100K探头参考27K电阻
#define		tab_other		1	//以上都无则自行至ad.c中添加表格
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
//		蜂鸣器参数设置
/*==========================================================================================     
说明:
配置蜂鸣器IO口，频率
==========================================================================================*/
#define   buz_en  1    //蜂鸣器函数使能
#define		c_ad_buz_com	1		//AD与蜂鸣器复用
#define		buz2K		0		//蜂鸣器频率 1 2k  0 4k
#define		p_buz		PC2
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
//		输出部分参数设置
/*==========================================================================================     
说明:
配置输出IO口，驱动
继电器100ms切换，默认高驱，适用于继电器驱动和不检测过零的可控硅驱动
可控硅默认使用丢波方式，提前开，可过EMC，默认高驱
==========================================================================================*/
#define     out_en  1   //继电器驱动函数使能 
#define		p_out1		PC5
#define		p_out2		PC5
#define		p_out3		PC5


#define   kkg_en   1  //可控硅驱动驱动函数使能
#if   kkg_en
#define		p_zero		PC3     //过零口
#define		p_kkg		 PA1      //可控硅输出口_A
#define		p_kkg_B		 PA1      //可控硅输出口_B
#define		c_high_drive  0   //高驱1   低驱0
#endif
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
//		按键参数设置
/*==========================================================================================     
说明:
配置按键为轻触或者触摸
轻触按键口在此处设置，触摸按键口请至触摸库中设置
==========================================================================================*/
#define		c_key_mode		0	//1为轻触，0为触摸

#if   c_key_mode
//		IO口定义,无则为1
#define		p_k1	PB1
#define		p_k2	PD3
#define		p_k3	1
#define		p_k4	1
#define		p_k5	1
#define		p_k6	1
#define		p_k7	1
#define		p_k8	1
#endif


//------------------------------------------------------------------------------------------
//		显示参数设置
/*==========================================================================================     
说明:
配置显示驱动方式，配置显示IO口，配置LED灯的对应位置
==========================================================================================*/
  
#define			c_disp_com		0		//电阻在SEG口，一次扫8个SEG口
#define			c_disp_seg		0		//电阻在COM口，一次扫8个COM口
#define			c_disp_comseg		0		//无电阻扫 ，每次扫1个灯，可正反扫
#define			c_disp_comcom		0		//无电阻扫 ，每次扫1个灯，共阴共阳扫
#define			c_TM1628_EN		0   //1668/1628
#define			c_TM1629_EN		0   //1629

#define			c_disp_comcom_qi		0		//无电阻扫 ，每次扫1个灯，共阴共阳扫
#define			c_disp_comcom2_qi		1		//无电阻扫 ，每次扫1个灯，共阴共阳扫


#if (c_TM1628_EN || c_TM1629_EN)
//  （1）配置管脚
#define	p_1628dio	PXX
#define	p_1628clk	PXX	
#define	p_1628stb	PXX
  
//  （2）配置亮度与输出口
#define	c_1628_lightGrade	0x8a	//亮度等级
#define	c_1628_lightMode	0x03	//显示模式	
/*
显示模式	
00:4bit-13part	01:5bit-12part
10:6bit-11part  11:7bit-10part
*/
#else	

#define			c_ledScan_cnt		38//6//12//15//13//30//31//0x08		//扫描次数，决定亮度
//		脚位定义，不用的脚定PXX

#define			p_segA1			PB7
#define			p_segA2			PB6
#define			p_segA3			PB5
#define			p_segA4			PC3
#define			p_segA5			PC0
#define			p_segA6			PC1
#define			p_segA7			PC2

#define			p_segB1			PD7
#define			p_segB2			PA0
#define			p_segB3			PA1
#define			p_segB4			PC6
#define			p_segB5			PD1
#define			p_segB6			PD0
#define			p_segB7			PC7

#define			p_com1			PD2



#define			p_seg1			PD2
#define			p_seg2			PD3
#define			p_seg3			PD5
#define			p_seg4			PD6
#define			p_seg5			PD0
#define			p_seg6			PD1
#define			p_seg7			PD7
#define			p_seg8			PA0
#define			p_seg9			PC4
#define			p_seg10			PD4


#define			p_com2			PXX
#define			p_com3			PXX
#define			p_com4			PXX
#define			p_com5			PXX
#define			p_com6			PXX
#define			p_com7			PXX
#define			p_com8			PXX
#endif

//		led灯定义，根据实际情况选择相应的位
#define			f_led1_h			b_r58|=c_bit0	//
#define			f_led2_h			b_r58|=c_bit1	//
#define			f_led3_h			b_r58|=c_bit2	//
#define			f_led4_h			b_r58|=c_bit3	//
#define			f_led5_h			b_r58|=c_bit4	//
#define			f_led6_h			b_r58|=c_bit5	//

#define			f_led7_h			b_r88|=c_bit6	//
#define			f_led8_h			b_r88|=c_bit7	//
#define			f_led9_h			b_r88|=c_bit0	//
#define			f_led10_h			b_r88|=c_bit1	//
#define			f_led11_h			b_r88|=c_bit2	//
#define			f_led12_h			b_r88|=c_bit3	//
#define			f_led13_h			b_r88|=c_bit4	//
#define			f_led14_h			b_r88|=c_bit5	//
#define			f_led15_h			b_r88|=c_bit6	//
#define			f_led16_h			b_r88|=c_bit7	//
#define			f_led17_h			b_r88|=c_bit0	//
#define			f_led18_h			b_r88|=c_bit1	//
#define			f_led19_h			b_r88|=c_bit2	//
#define			f_led20_h			b_r88|=c_bit3	//








//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
//测试脚用于无显示数码管的情况下通过单线通讯输送数据到显示测试板，要配合显示测试板使用，无需求可关闭使能
#define   test_en   0       //测试输出使能
#define   p_test  PA7       //测试输出信号脚
//------------------------------------------------------------------------------------------



/*宏定义*/

#define		c_yyyc			0	//为1则预约时间为完成时间
#define		c_yuyueset		0	//为1则预约键可以调预约时间


//		功能编译选择

#define		c_s_zf		1	//双探头煮饭
#define		c_s_zz		1	//双探头煮粥
#define		c_s_bt		0	//双探头煲汤
#define		c_s_zg		0	//双探头蒸
#define		c_s_ts		0	//双探头糖水	

#define		c_d_zf		0	//单探头煮饭
#define		c_d_zz		0	//单探头煮粥/稀饭
#define		c_d_bt		0	//单探头煲汤
#define		c_d_dt		0	//单探头炖
#define		c_d_sgc		0	//水果茶

#define		c_a_zh		0	//蒸

#define		c_a_sn		0	//酸奶	
#define		c_suannai_mode	0	//酸奶模式，无酸奶请填0

#define		c_a_rf		0	//热饭
#define		c_a_dg		0	//蛋糕
#define		c_a_ss		0	//烧水
#define		c_a_gsd		0	//隔水炖

//		功能详选
#define		c_baowen_h	70	//保温温度	原差2度
#define		c_baowen_l	68
#define		c_baowen_g	0x04   //保温功率











/*************************************************/
/*****************用户使用头文件******************/
/*************************************************/
#include 	"Other.h"

////此处插入use头文件////




/*************************************************/
/*****************驱动程序头文件******************/
/*************************************************/
//#include 	"24C02.h"
////此处插入app头文件////



/*************************************************/
/*****************功能模块文件********************/
/*************************************************/

#include 	"..\Application_Library\AD.h"
#include 	"..\Application_Library\buz.h"
#include 	"..\Application_Library\key.h"
#include 	"..\Application_Library\display.h"
#include 	"..\Application_Library\work_deal.h"
#include 	"..\Application_Library\codingSwitch.h"	
#include	"..\Application_Library\codingSwitch_user.h"	
#if	(c_TM1628_EN|| c_TM1629_EN)
#include 	"..\user\TM1628.h"
#endif

















































#endif

