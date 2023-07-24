#ifndef	__KEY_H__
#define __KEY_H__
/*************************************************************
***********************外部函数申明***************************
*************************************************************/
extern void		key_deal();
extern  unsigned char	xdata	b_key_value;

extern  uchar	xdata	Target_wendu_mode_1;  //左目标温度灯
extern  uchar	xdata	Target_wendu_mode_2;  //左目标温度灯


extern  uchar	xdata	set_time_1_hour; //左定时灯
extern  uchar	xdata	set_time_1_min; //
extern  uchar	xdata	set_time_1_sec;  //
extern  uchar	xdata	set_time_2_hour; //右定时灯
extern  uchar	xdata	set_time_2_min;  //
extern  uchar	xdata	set_time_2_sec;  //

extern  uchar	xdata   b_stop_1_sec;  //左暂停时间
extern  uchar	xdata   b_stop_1_min;  //左暂停时间
extern  uchar	xdata   b_stop_2_sec;  //右暂停时间
extern  uchar	xdata   b_stop_2_min;  //右暂停时间


extern	uchar	xdata	b_force_flash_cnt;	//强制闪烁计数
extern	bit				f_clock_key	;	//1:锁键,0:解锁,可改变时间档位
extern	uchar	xdata	b_clock_key ; //运行过程中,无按键按下,1s后锁键



#if	c_key_mode
//  按键置输入
extern	void  sw_scan_in();
//  按键检测
extern	void  sw_scan();
#endif

/*************************************************************
***********************外部变量申明***************************
*************************************************************/


/*************************************************************
***********************宏定义***************************
*************************************************************/

#if   c_key_mode
#define		c_k1		0x01
#define		c_k2		0x02
#define		c_k3		0x04
#define		c_k4		0x08
#define		c_k5		0x10
#define		c_k6		0x20
#define		c_k7		0x40
#define		c_k8		0x80
#else
//		键值：SNS+1
#define		c_k1		1
#define		c_k2		2
#define		c_k3		3
#define		c_k4		4
#define		c_k5		5
#define		c_k6		6
#define		c_k7		7
#define		c_k8		8
#endif


//#define		key_input	{p_k1in;p_k2in;p_k3in;p_k4in;p_k5in;p_k6in;p_k7in;p_k8in;}
#define		key_input	{p_k1in;p_k2in;}
//#define		key_output {p_k1out;p_k2out;p_k3out;p_k4out;p_k5out;p_k6out;p_k7out;p_k8out;}
#define		key_output {p_k1out;p_k2out;}
//#define		key_pull	{p_k1_pull;p_k2_pull;p_k3_pull;p_k4_pull;p_k5_pull;p_k6_pull;p_k7_pull;p_k8_pull;}
#define		key_pull	{p_k1_pull;p_k2_pull;}


#define   _p_k1_h(x)                   SET_##x##_H
#define   __p_k1_h(x)                  _p_k1_h(x)
#define   p_k1h                       __p_k1_h(p_k1)

#define   _p_k1_l(x)                   SET_##x##_L
#define   __p_k1_l(x)                  _p_k1_l(x)
#define   p_k1l                       __p_k1_l(p_k1)

#define   _p_k1_in(x)                   SET_##x##_IO_IN
#define   __p_k1_in(x)                  _p_k1_in(x)
#define   p_k1in                       __p_k1_in(p_k1)

#define   _p_k1_out(x)                   SET_##x##_IO_OUT
#define   __p_k1_out(x)                  _p_k1_out(x)
#define   p_k1out                       __p_k1_out(p_k1)

#define		_p_k1_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k1_pull(x)		_p_k1_pull(x)
#define		p_k1_pull			__p_k1_pull(p_k1)


#define   _p_k1_get(x)                 GET_##x
#define   __p_k1_get(x)                _p_k1_get(x)
#define   p_k1_get                     __p_k1_get(p_k1)

#define   _p_k2_h(x)                   SET_##x##_H
#define   __p_k2_h(x)                  _p_k2_h(x)
#define   p_k2h                       __p_k2_h(p_k2)

#define   _p_k2_l(x)                   SET_##x##_L
#define   __p_k2_l(x)                  _p_k2_l(x)
#define   p_k2l                       __p_k2_l(p_k2)

#define   _p_k2_in(x)                   SET_##x##_IO_IN
#define   __p_k2_in(x)                  _p_k2_in(x)
#define   p_k2in                       __p_k2_in(p_k2)

#define   _p_k2_out(x)                   SET_##x##_IO_OUT
#define   __p_k2_out(x)                  _p_k2_out(x)
#define   p_k2out                       __p_k2_out(p_k2)


#define		_p_k2_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k2_pull(x)		_p_k2_pull(x)
#define		p_k2_pull			__p_k2_pull(p_k2)

#define   _p_k2_get(x)                 GET_##x
#define   __p_k2_get(x)                _p_k2_get(x)
#define   p_k2_get                     __p_k2_get(p_k2)

#define   _p_k3_h(x)                   SET_##x##_H
#define   __p_k3_h(x)                  _p_k3_h(x)
#define   p_k3h                       __p_k3_h(p_k3)

#define   _p_k3_l(x)                   SET_##x##_L
#define   __p_k3_l(x)                  _p_k3_l(x)
#define   p_k3l                       __p_k3_l(p_k3)

#define   _p_k3_in(x)                   SET_##x##_IO_IN
#define   __p_k3_in(x)                  _p_k3_in(x)
#define   p_k3in                       __p_k3_in(p_k3)

#define   _p_k3_out(x)                   SET_##x##_IO_OUT
#define   __p_k3_out(x)                  _p_k3_out(x)
#define   p_k3out                       __p_k3_out(p_k3)


#define		_p_k3_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k3_pull(x)		_p_k3_pull(x)
#define		p_k3_pull			__p_k3_pull(p_k3)

#define   _p_k3_get(x)                 GET_##x
#define   __p_k3_get(x)                _p_k3_get(x)
#define   p_k3_get                     __p_k3_get(p_k3)

#define   _p_k4_h(x)                   SET_##x##_H
#define   __p_k4_h(x)                  _p_k4_h(x)
#define   p_k4h                       __p_k4_h(p_k4)

#define   _p_k4_l(x)                   SET_##x##_L
#define   __p_k4_l(x)                  _p_k4_l(x)
#define   p_k4l                       __p_k4_l(p_k4)

#define   _p_k4_in(x)                   SET_##x##_IO_IN
#define   __p_k4_in(x)                  _p_k4_in(x)
#define   p_k4in                       __p_k4_in(p_k4)

#define   _p_k4_out(x)                   SET_##x##_IO_OUT
#define   __p_k4_out(x)                  _p_k4_out(x)
#define   p_k4out                       __p_k4_out(p_k4)


#define		_p_k4_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k4_pull(x)		_p_k4_pull(x)
#define		p_k4_pull			__p_k4_pull(p_k4)

#define   _p_k4_get(x)                 GET_##x
#define   __p_k4_get(x)                _p_k4_get(x)
#define   p_k4_get                     __p_k4_get(p_k4)

#define   _p_k5_h(x)                   SET_##x##_H
#define   __p_k5_h(x)                  _p_k5_h(x)
#define   p_k5h                       __p_k5_h(p_k5)

#define   _p_k5_l(x)                   SET_##x##_L
#define   __p_k5_l(x)                  _p_k5_l(x)
#define   p_k5l                       __p_k5_l(p_k5)

#define   _p_k5_in(x)                   SET_##x##_IO_IN
#define   __p_k5_in(x)                  _p_k5_in(x)
#define   p_k5in                       __p_k5_in(p_k5)

#define   _p_k5_out(x)                   SET_##x##_IO_OUT
#define   __p_k5_out(x)                  _p_k5_out(x)
#define   p_k5out                       __p_k5_out(p_k5)


#define		_p_k5_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k5_pull(x)		_p_k5_pull(x)
#define		p_k5_pull			__p_k5_pull(p_k5)

#define   _p_k5_get(x)                 GET_##x
#define   __p_k5_get(x)                _p_k5_get(x)
#define   p_k5_get                     __p_k5_get(p_k5)

#define   _p_k6_h(x)                   SET_##x##_H
#define   __p_k6_h(x)                  _p_k6_h(x)
#define   p_k6h                       __p_k6_h(p_k6)

#define   _p_k6_l(x)                   SET_##x##_L
#define   __p_k6_l(x)                  _p_k6_l(x)
#define   p_k6l                       __p_k6_l(p_k6)

#define   _p_k6_in(x)                   SET_##x##_IO_IN
#define   __p_k6_in(x)                  _p_k6_in(x)
#define   p_k6in                       __p_k6_in(p_k6)

#define   _p_k6_out(x)                   SET_##x##_IO_OUT
#define   __p_k6_out(x)                  _p_k6_out(x)
#define   p_k6out                       __p_k6_out(p_k6)


#define		_p_k6_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k6_pull(x)		_p_k6_pull(x)
#define		p_k6_pull			__p_k6_pull(p_k6)

#define   _p_k6_get(x)                 GET_##x
#define   __p_k6_get(x)                _p_k6_get(x)
#define   p_k6_get                     __p_k6_get(p_k6)

#define   _p_k7_h(x)                   SET_##x##_H
#define   __p_k7_h(x)                  _p_k7_h(x)
#define   p_k7h                       __p_k7_h(p_k7)

#define   _p_k7_l(x)                   SET_##x##_L
#define   __p_k7_l(x)                  _p_k7_l(x)
#define   p_k7l                       __p_k7_l(p_k7)

#define   _p_k7_in(x)                   SET_##x##_IO_IN
#define   __p_k7_in(x)                  _p_k7_in(x)
#define   p_k7in                       __p_k7_in(p_k7)

#define   _p_k7_out(x)                   SET_##x##_IO_OUT
#define   __p_k7_out(x)                  _p_k7_out(x)
#define   p_k7out                       __p_k7_out(p_k7)


#define		_p_k7_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k7_pull(x)		_p_k7_pull(x)
#define		p_k7_pull			__p_k7_pull(p_k7)

#define   _p_k7_get(x)                 GET_##x
#define   __p_k7_get(x)                _p_k7_get(x)
#define   p_k7_get                     __p_k7_get(p_k7)

#define   _p_k8_h(x)                   SET_##x##_H
#define   __p_k8_h(x)                  _p_k8_h(x)
#define   p_k8h                       __p_k8_h(p_k8)

#define   _p_k8_l(x)                   SET_##x##_L
#define   __p_k8_l(x)                  _p_k8_l(x)
#define   p_k8l                       __p_k8_l(p_k8)

#define   _p_k8_in(x)                   SET_##x##_IO_IN
#define   __p_k8_in(x)                  _p_k8_in(x)
#define   p_k8in                       __p_k8_in(p_k8)

#define   _p_k8_out(x)                   SET_##x##_IO_OUT
#define   __p_k8_out(x)                  _p_k8_out(x)
#define   p_k8out                       __p_k8_out(p_k8)


#define		_p_k8_pull(x)		SET_##x##_PU_ON		//开上拉
#define		__p_k8_pull(x)		_p_k8_pull(x)
#define		p_k8_pull			__p_k8_pull(p_k8)

#define   _p_k8_get(x)                 GET_##x
#define   __p_k8_get(x)                _p_k8_get(x)
#define   p_k8_get                     __p_k8_get(p_k8)


/*************************************************************
***********************常量定义*******************************
*************************************************************/
#if	c_key_mode
#define		c_shortKey_cnt		2	//按下消抖次数	建议值：触摸为0（单位为20ms），轻触为2（单位为扫描次数）
#else
#define		c_shortKey_cnt		0	//按下消抖次数	建议值：触摸为0（单位为20ms），轻触为2（单位为扫描次数）
#endif




#endif







