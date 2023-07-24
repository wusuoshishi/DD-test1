#ifndef	__WORK_H__
#define	__WORK_H__


extern void work_deal(void);
extern	void	relay_deal();


extern	void	action_work(void);  //开始工作
extern	void	quit_work(void);    //退出工作

#if   kkg_en
extern	void	kkg_work_api();
#endif

//工作模式
extern	uchar	xdata	b_mode;

extern	uchar	xdata	b_set_wendu;	//设定的温度
extern	uchar	xdata	b_grade;	//档位

//工作流程时间变量
extern	uchar	xdata	b_ctrl_sec_1;
extern	uint	xdata	b_ctrl_sec_2;
extern	uchar	xdata	b_ctrl_sec_3;

#if	double_ad_channel
extern	uchar	xdata	b_temp_1_ref_sec;
#endif

//设置时间变量
extern	uchar	xdata	b_mjs_set_sec;

extern	uchar xdata b_yuyue_run_cnt ;	//预约倒计时进行时长计数

extern	uchar xdata	b_wendu_ok;	//达到目标温度的次数
extern	uchar	xdata	b_kkg_buf;

//保温时间变量
extern	uchar	xdata	b_baowen_hour;
extern	uchar	xdata	b_baowen_min;
extern	uchar	xdata	b_baowen_sec;

//预约时间变量
extern	uchar	xdata	b_yuyue_hour;
extern	uchar	xdata	b_yuyue_min;
extern	uchar	xdata	b_yuyue_sec;

//工作时间变量
extern	uchar	xdata	b_dingshi_hour;
extern	uchar	xdata	b_dingshi_min;
extern	uchar	xdata	b_dingshi_sec;

//工作状态标识位:set 设置，odoff 定时，power工作中，odon预约，odoff_begin工作倒计时
extern	bit		f_mjs_set;
extern	bit		f_mjs_dingshi;
extern	bit		f_mjs_power;
extern	bit		f_mjs_yuyue;
extern	bit		f_mjs_down;
extern	bit		f_dingshi_begin;

extern	bit	f_NO_jiangdang;	//降档标志位 0:可降档 1:不可降档



extern  bit     f_stop_1;
extern  bit     f_stop_2;

/*暖菜机定义*/
extern	bit		f_sys_power_1;  //左边(A) 0:关,1:开
extern	bit		f_sys_power_2;  //右边(B) 0:关,1:开

extern  bit     f_sys_on_1;     //左边(A) 0:待机,1:开机
extern  bit     f_sys_on_2;     //左边(A) 0:待机,1:开机

extern	bit		f_test;
extern	uchar	xdata	b_test;
extern	uchar	xdata	b_test_out_time;
extern	uchar	xdata	b_test_mode;

#define   _p_out1_h(x)                   SET_##x##_H
#define   __p_out1_h(x)                  _p_out1_h(x)
#define   p_out1h                       __p_out1_h(p_out1)

#define   _p_out1_l(x)                   SET_##x##_L
#define   __p_out1_l(x)                  _p_out1_l(x)
#define   p_out1l                       __p_out1_l(p_out1)

#define   _p_out2_h(x)                   SET_##x##_H
#define   __p_out2_h(x)                  _p_out2_h(x)
#define   p_out2h                       __p_out2_h(p_out2)

#define   _p_out2_l(x)                   SET_##x##_L
#define   __p_out2_l(x)                  _p_out2_l(x)
#define   p_out2l                       __p_out2_l(p_out2)

#define   _p_out3_h(x)                   SET_##x##_H
#define   __p_out3_h(x)                  _p_out3_h(x)
#define   p_out3h                       __p_out3_h(p_out3)

#define   _p_out3_l(x)                   SET_##x##_L
#define   __p_out3_l(x)                  _p_out3_l(x)
#define   p_out3l                       __p_out3_l(p_out3)

#define   _p_kkg_h(x)                   SET_##x##_H
#define   __p_kkg_h(x)                  _p_kkg_h(x)
#define   p_kkgh                       __p_kkg_h(p_kkg)

#define   _p_kkg_l(x)                   SET_##x##_L
#define   __p_kkg_l(x)                  _p_kkg_l(x)
#define   p_kkgl                       __p_kkg_l(p_kkg)


#define   _p_kkg_B_h(x)                   SET_##x##_H
#define   __p_kkg_B_h(x)                  _p_kkg_B_h(x)
#define   p_kkg_Bh                       __p_kkg_B_h(p_kkg_B)

#define   _p_kkg_B_l(x)                   SET_##x##_L
#define   __p_kkg_B_l(x)                  _p_kkg_B_l(x)
#define   p_kkg_Bl                       __p_kkg_B_l(p_kkg_B)

#endif


////		按键参数设置
//#define		c_key_mode		0	//1为轻触，0为触摸
//#define		c_shortKey_noCnt		1	//释放消抖次数	
//#define		c_shortKey_cnt		2	//按下消抖次数	建议值：触摸为2（单位为10ms），轻触为5（单位为扫描次数）
//#define		c_mode_add		1	//1为模式+键 0为模式快速键，需要去程序中设置键值
//#define		c_yuyue_loop		1	//预约加减时间循环 
//#define		c_odon_minstr	 	0	//设置起始预约时间 
//#define		c_odon_hourstr	  	2	//设置起始预约时间
//#define		c_odon_hour_max	 	8	//设置最大预约时间	
//#define		c_odon_min_max	 	0	//设置最大预约时间	 
//#define		c_odon_hour_min	 	0	//设置最小预约时间	 
//#define		c_odon_min_min	 	30	//设置最小预约时间	
//#define		c_yyyc			0	//为1则预约时间为完成时间
//#define		c_yuyueset		0	//为1则预约键可以调预约时间
//#define		c_odon_minadd		30	//预约键自加数
//#define		c_odon_mindec		0	//预约减数
//
//#define		c_mode_num		4	//功能数	  
//#define		c_odoff_loop		1	//功能时间加减时间循环

