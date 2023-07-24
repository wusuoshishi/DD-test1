#ifndef	__DISPLAY_H__
#define	__DISPLAY_H__



#define		c_disp_change	0	//转换函数,适用于显示驱动IC变量的快速转换
#define		c_disp_liushui	1	//流水灯处理

/*************************************************************
***********************外部函数申明***************************
*************************************************************/
extern	void	display_deal();   //显示处理函数
extern	void	led_scan();     //显示扫描函数

/*************************************************************
***********************外部变量申明***************************
*************************************************************/

extern	bit		gf_flash;
extern	uchar	xdata	gb_flashTime;
extern	bit		f_disp_dingshi;
extern	bit		f_disp_yuyue;
extern	bit		f_disp_wendu;
extern	uchar	xdata	b_led_slide1;

extern	uchar	xdata	b_disp_test;
extern	uchar	xdata	b_disp_test2;

extern	uchar	b_time_grade_cnt;//		0:档位,5:时间
/*************************************************************
***********************常量定义*******************************
*************************************************************/
//-------------------------------------------------------------------------------
//数码管图形应对应段位
//	      A
//	     ____
//   F	| G	 |B
//		|____|
//   E  |	 |C
//		|____|.H
//	      D
//
//--------------------------数码管段码定义
#define   	c_segA   	c_bit0
#define   	c_segB   	c_bit1
#define   	c_segC   	c_bit2
#define   	c_segD   	c_bit3
#define   	c_segE   	c_bit4
#define   	c_segF   	c_bit5
#define   	c_segG   	c_bit6
#define   	c_segH   	c_bit7


#define		disp_comh	{p_com1h; p_com2h; p_com3h; p_com4h; p_com5h; p_com6h; p_com7h; p_com8h;}
#define		disp_segl	{p_segA1l; p_seg2l; p_seg3l; p_seg4l; p_seg5l; p_seg6l; p_seg7l; p_seg8l;}


//**************************************************************
//数码管显示图形定义
//**************************************************************
#define         c_num0       c_segA+c_segB+c_segC+c_segD+c_segE+c_segF
#define         c_num1       c_segB+c_segC
#define         c_num2       c_segA+c_segB+c_segD+c_segE+c_segG
#define         c_num3       c_segA+c_segB+c_segC+c_segD+c_segG
#define         c_num4       c_segB+c_segC+c_segF+c_segG
#define         c_num5       c_segA+c_segC+c_segD+c_segF+c_segG
#define         c_num6       c_segA+c_segC+c_segD+c_segE+c_segF+c_segG
#define         c_num7       c_segA+c_segB+c_segC
#define         c_num8       c_segA+c_segB+c_segC+c_segD+c_segE+c_segF+c_segG
#define         c_num9       c_segA+c_segB+c_segC+c_segD+c_segF+c_segG
#define         c_num10      00
#define         c_numL       c_segE+c_segF+c_segD
#define         c_numR       c_segA+c_segB+c_segC+c_segE+c_segF+c_segG
#define         c_nump       c_segA+c_segB+c_segE+c_segF+c_segG
#define         c_numA       c_segA+c_segB+c_segC+c_segE+c_segF+c_segG
#define         c_numb       c_segC+c_segD+c_segE+c_segF+c_segG
#define         c_numc       c_segA+c_segF+c_segG
#define         c_numC       c_segA+c_segB+c_segC+c_segD+c_segF+c_segG
#define         c_numd       c_segB+c_segC+c_segD+c_segE+c_segG
#define         c_numE       c_segA+c_segD+c_segE+c_segF+c_segG
#define         c_numF       c_segA+c_segE+c_segF+c_segG
#define         c_numc_ding       c_segA+c_segF+c_segG
#define         c_numH      c_segB+c_segC+c_segE+c_segF+c_segG


/*反着看*/
#define         c_num0_n       c_segA+c_segB+c_segC+c_segD+c_segE+c_segF
#define         c_num1_n       c_segF+c_segE
#define         c_num2_n       c_segA+c_segB+c_segD+c_segE+c_segG
#define         c_num3_n       0x079
#define         c_num4_n       0x074
#define         c_num5_n       0x06d
#define         c_num6_n       0x06f
#define         c_num7_n       0x038
#define         c_num8_n       c_segA+c_segB+c_segC+c_segD+c_segE+c_segF+c_segG
#define         c_num9_n       0x07d
#define         c_num10_n      0x00
#define         c_numL_n       0x007
#define         c_numR_n       0x003
#define         c_nump_n       0x05e
#define         c_numA_n       0x07e
#define         c_numb_n       0x067
#define         c_numc_n       0x043
#define         c_numC_n       0x00f
#define         c_numd_n       0x073
#define         c_numE_n       0x04f
#define         c_numF_n       0x04e
#define         c_numc_ding_n       0x04c
#define         c_numH_n      0x076





#define   _p_seg1_h(x)                   SET_##x##_H
#define   __p_seg1_h(x)                  _p_seg1_h(x)
#define   p_seg1h                       __p_seg1_h(p_seg1)

#define   _p_seg1_l(x)                   SET_##x##_L
#define   __p_seg1_l(x)                  _p_seg1_l(x)
#define   p_seg1l                       __p_seg1_l(p_seg1)

#define   _p_seg1_in(x)                   SET_##x##_IO_IN
#define   __p_seg1_in(x)                  _p_seg1_in(x)
#define   p_seg1in                       __p_seg1_in(p_seg1)

#define   _p_seg1_out(x)                   SET_##x##_IO_OUT
#define   __p_seg1_out(x)                  _p_seg1_out(x)
#define   p_seg1out                       __p_seg1_out(p_seg1)

#define   _p_seg2_h(x)                   SET_##x##_H
#define   __p_seg2_h(x)                  _p_seg2_h(x)
#define   p_seg2h                       __p_seg2_h(p_seg2)

#define   _p_seg2_l(x)                   SET_##x##_L
#define   __p_seg2_l(x)                  _p_seg2_l(x)
#define   p_seg2l                       __p_seg2_l(p_seg2)

#define   _p_seg2_in(x)                   SET_##x##_IO_IN
#define   __p_seg2_in(x)                  _p_seg2_in(x)
#define   p_seg2in                       __p_seg2_in(p_seg2)

#define   _p_seg2_out(x)                   SET_##x##_IO_OUT
#define   __p_seg2_out(x)                  _p_seg2_out(x)
#define   p_seg2out                       __p_seg2_out(p_seg2)

#define   _p_seg3_h(x)                   SET_##x##_H
#define   __p_seg3_h(x)                  _p_seg3_h(x)
#define   p_seg3h                       __p_seg3_h(p_seg3)

#define   _p_seg3_l(x)                   SET_##x##_L
#define   __p_seg3_l(x)                  _p_seg3_l(x)
#define   p_seg3l                       __p_seg3_l(p_seg3)

#define   _p_seg3_in(x)                   SET_##x##_IO_IN
#define   __p_seg3_in(x)                  _p_seg3_in(x)
#define   p_seg3in                       __p_seg3_in(p_seg3)

#define   _p_seg3_out(x)                   SET_##x##_IO_OUT
#define   __p_seg3_out(x)                  _p_seg3_out(x)
#define   p_seg3out                       __p_seg3_out(p_seg3)

#define   _p_seg4_h(x)                   SET_##x##_H
#define   __p_seg4_h(x)                  _p_seg4_h(x)
#define   p_seg4h                       __p_seg4_h(p_seg4)

#define   _p_seg4_l(x)                   SET_##x##_L
#define   __p_seg4_l(x)                  _p_seg4_l(x)
#define   p_seg4l                       __p_seg4_l(p_seg4)

#define   _p_seg4_in(x)                   SET_##x##_IO_IN
#define   __p_seg4_in(x)                  _p_seg4_in(x)
#define   p_seg4in                       __p_seg4_in(p_seg4)

#define   _p_seg4_out(x)                   SET_##x##_IO_OUT
#define   __p_seg4_out(x)                  _p_seg4_out(x)
#define   p_seg4out                       __p_seg4_out(p_seg4)

#define   _p_seg5_h(x)                   SET_##x##_H
#define   __p_seg5_h(x)                  _p_seg5_h(x)
#define   p_seg5h                       __p_seg5_h(p_seg5)

#define   _p_seg5_l(x)                   SET_##x##_L
#define   __p_seg5_l(x)                  _p_seg5_l(x)
#define   p_seg5l                       __p_seg5_l(p_seg5)

#define   _p_seg5_in(x)                   SET_##x##_IO_IN
#define   __p_seg5_in(x)                  _p_seg5_in(x)
#define   p_seg5in                       __p_seg5_in(p_seg5)

#define   _p_seg5_out(x)                   SET_##x##_IO_OUT
#define   __p_seg5_out(x)                  _p_seg5_out(x)
#define   p_seg5out                       __p_seg5_out(p_seg5)

#define   _p_seg6_h(x)                   SET_##x##_H
#define   __p_seg6_h(x)                  _p_seg6_h(x)
#define   p_seg6h                       __p_seg6_h(p_seg6)

#define   _p_seg6_l(x)                   SET_##x##_L
#define   __p_seg6_l(x)                  _p_seg6_l(x)
#define   p_seg6l                       __p_seg6_l(p_seg6)

#define   _p_seg6_in(x)                   SET_##x##_IO_IN
#define   __p_seg6_in(x)                  _p_seg6_in(x)
#define   p_seg6in                       __p_seg6_in(p_seg6)

#define   _p_seg6_out(x)                   SET_##x##_IO_OUT
#define   __p_seg6_out(x)                  _p_seg6_out(x)
#define   p_seg6out                       __p_seg6_out(p_seg6)

#define   _p_seg7_h(x)                   SET_##x##_H
#define   __p_seg7_h(x)                  _p_seg7_h(x)
#define   p_seg7h                       __p_seg7_h(p_seg7)

#define   _p_seg7_l(x)                   SET_##x##_L
#define   __p_seg7_l(x)                  _p_seg7_l(x)
#define   p_seg7l                       __p_seg7_l(p_seg7)

#define   _p_seg7_in(x)                   SET_##x##_IO_IN
#define   __p_seg7_in(x)                  _p_seg7_in(x)
#define   p_seg7in                       __p_seg7_in(p_seg7)

#define   _p_seg7_out(x)                   SET_##x##_IO_OUT
#define   __p_seg7_out(x)                  _p_seg7_out(x)
#define   p_seg7out                       __p_seg7_out(p_seg7)

#define   _p_seg8_h(x)                   SET_##x##_H
#define   __p_seg8_h(x)                  _p_seg8_h(x)
#define   p_seg8h                       __p_seg8_h(p_seg8)

#define   _p_seg8_l(x)                   SET_##x##_L
#define   __p_seg8_l(x)                  _p_seg8_l(x)
#define   p_seg8l                       __p_seg8_l(p_seg8)

#define   _p_seg8_in(x)                   SET_##x##_IO_IN
#define   __p_seg8_in(x)                  _p_seg8_in(x)
#define   p_seg8in                       __p_seg8_in(p_seg8)

#define   _p_seg8_out(x)                   SET_##x##_IO_OUT
#define   __p_seg8_out(x)                  _p_seg8_out(x)
#define   p_seg8out                       __p_seg8_out(p_seg8)

//==========================
#define   _p_seg9_h(x)                   SET_##x##_H
#define   __p_seg9_h(x)                  _p_seg9_h(x)
#define   p_seg9h                       __p_seg9_h(p_seg9)

#define   _p_seg9_l(x)                   SET_##x##_L
#define   __p_seg9_l(x)                  _p_seg9_l(x)
#define   p_seg9l                       __p_seg9_l(p_seg9)

#define   _p_seg9_in(x)                   SET_##x##_IO_IN
#define   __p_seg9_in(x)                  _p_seg9_in(x)
#define   p_seg9in                       __p_seg9_in(p_seg9)

#define   _p_seg9_out(x)                   SET_##x##_IO_OUT
#define   __p_seg9_out(x)                  _p_seg9_out(x)
#define   p_seg9out                       __p_seg9_out(p_seg9)

#define   _p_seg10_h(x)                   SET_##x##_H
#define   __p_seg10_h(x)                  _p_seg10_h(x)
#define   p_seg10h                       __p_seg10_h(p_seg10)

#define   _p_seg10_l(x)                   SET_##x##_L
#define   __p_seg10_l(x)                  _p_seg10_l(x)
#define   p_seg10l                       __p_seg10_l(p_seg10)

#define   _p_seg10_in(x)                   SET_##x##_IO_IN
#define   __p_seg10_in(x)                  _p_seg10_in(x)
#define   p_seg10in                       __p_seg10_in(p_seg10)

#define   _p_seg10_out(x)                   SET_##x##_IO_OUT
#define   __p_seg10_out(x)                  _p_seg10_out(x)
#define   p_seg10out                       __p_seg10_out(p_seg10)











#define   _p_com1_h(x)                   SET_##x##_H
#define   __p_com1_h(x)                  _p_com1_h(x)
#define   p_com1h                       __p_com1_h(p_com1)

#define   _p_com1_l(x)                   SET_##x##_L
#define   __p_com1_l(x)                  _p_com1_l(x)
#define   p_com1l                       __p_com1_l(p_com1)

#define   _p_com1_in(x)                   SET_##x##_IO_IN
#define   __p_com1_in(x)                  _p_com1_in(x)
#define   p_com1in                       __p_com1_in(p_com1)

#define   _p_com1_out(x)                   SET_##x##_IO_OUT
#define   __p_com1_out(x)                  _p_com1_out(x)
#define   p_com1out                       __p_com1_out(p_com1)

#define   _p_com2_h(x)                   SET_##x##_H
#define   __p_com2_h(x)                  _p_com2_h(x)
#define   p_com2h                       __p_com2_h(p_com2)

#define   _p_com2_l(x)                   SET_##x##_L
#define   __p_com2_l(x)                  _p_com2_l(x)
#define   p_com2l                       __p_com2_l(p_com2)

#define   _p_com2_in(x)                   SET_##x##_IO_IN
#define   __p_com2_in(x)                  _p_com2_in(x)
#define   p_com2in                       __p_com2_in(p_com2)

#define   _p_com2_out(x)                   SET_##x##_IO_OUT
#define   __p_com2_out(x)                  _p_com2_out(x)
#define   p_com2out                       __p_com2_out(p_com2)

#define   _p_com3_h(x)                   SET_##x##_H
#define   __p_com3_h(x)                  _p_com3_h(x)
#define   p_com3h                       __p_com3_h(p_com3)

#define   _p_com3_l(x)                   SET_##x##_L
#define   __p_com3_l(x)                  _p_com3_l(x)
#define   p_com3l                       __p_com3_l(p_com3)

#define   _p_com3_in(x)                   SET_##x##_IO_IN
#define   __p_com3_in(x)                  _p_com3_in(x)
#define   p_com3in                       __p_com3_in(p_com3)

#define   _p_com3_out(x)                   SET_##x##_IO_OUT
#define   __p_com3_out(x)                  _p_com3_out(x)
#define   p_com3out                       __p_com3_out(p_com3)

#define   _p_com4_h(x)                   SET_##x##_H
#define   __p_com4_h(x)                  _p_com4_h(x)
#define   p_com4h                       __p_com4_h(p_com4)

#define   _p_com4_l(x)                   SET_##x##_L
#define   __p_com4_l(x)                  _p_com4_l(x)
#define   p_com4l                       __p_com4_l(p_com4)

#define   _p_com4_in(x)                   SET_##x##_IO_IN
#define   __p_com4_in(x)                  _p_com4_in(x)
#define   p_com4in                       __p_com4_in(p_com4)

#define   _p_com4_out(x)                   SET_##x##_IO_OUT
#define   __p_com4_out(x)                  _p_com4_out(x)
#define   p_com4out                       __p_com4_out(p_com4)

#define   _p_com5_h(x)                   SET_##x##_H
#define   __p_com5_h(x)                  _p_com5_h(x)
#define   p_com5h                       __p_com5_h(p_com5)

#define   _p_com5_l(x)                   SET_##x##_L
#define   __p_com5_l(x)                  _p_com5_l(x)
#define   p_com5l                       __p_com5_l(p_com5)

#define   _p_com5_in(x)                   SET_##x##_IO_IN
#define   __p_com5_in(x)                  _p_com5_in(x)
#define   p_com5in                       __p_com5_in(p_com5)

#define   _p_com5_out(x)                   SET_##x##_IO_OUT
#define   __p_com5_out(x)                  _p_com5_out(x)
#define   p_com5out                       __p_com5_out(p_com5)

#define   _p_com6_h(x)                   SET_##x##_H
#define   __p_com6_h(x)                  _p_com6_h(x)
#define   p_com6h                       __p_com6_h(p_com6)

#define   _p_com6_l(x)                   SET_##x##_L
#define   __p_com6_l(x)                  _p_com6_l(x)
#define   p_com6l                       __p_com6_l(p_com6)

#define   _p_com6_in(x)                   SET_##x##_IO_IN
#define   __p_com6_in(x)                  _p_com6_in(x)
#define   p_com6in                       __p_com6_in(p_com6)

#define   _p_com6_out(x)                   SET_##x##_IO_OUT
#define   __p_com6_out(x)                  _p_com6_out(x)
#define   p_com6out                       __p_com6_out(p_com6)

#define   _p_com7_h(x)                   SET_##x##_H
#define   __p_com7_h(x)                  _p_com7_h(x)
#define   p_com7h                       __p_com7_h(p_com7)

#define   _p_com7_l(x)                   SET_##x##_L
#define   __p_com7_l(x)                  _p_com7_l(x)
#define   p_com7l                       __p_com7_l(p_com7)

#define   _p_com7_in(x)                   SET_##x##_IO_IN
#define   __p_com7_in(x)                  _p_com7_in(x)
#define   p_com7in                       __p_com7_in(p_com7)

#define   _p_com7_out(x)                   SET_##x##_IO_OUT
#define   __p_com7_out(x)                  _p_com7_out(x)
#define   p_com7out                       __p_com7_out(p_com7)

#define   _p_com8_h(x)                   SET_##x##_H
#define   __p_com8_h(x)                  _p_com8_h(x)
#define   p_com8h                       __p_com8_h(p_com8)

#define   _p_com8_l(x)                   SET_##x##_L
#define   __p_com8_l(x)                  _p_com8_l(x)
#define   p_com8l                       __p_com8_l(p_com8)

#define   _p_com8_in(x)                   SET_##x##_IO_IN
#define   __p_com8_in(x)                  _p_com8_in(x)
#define   p_com8in                       __p_com8_in(p_com8)

#define   _p_com8_out(x)                   SET_##x##_IO_OUT
#define   __p_com8_out(x)                  _p_com8_out(x)
#define   p_com8out                       __p_com8_out(p_com8)







/*==========================================================*/

#define   _p_segA1_h(x)                   SET_##x##_H
#define   __p_segA1_h(x)                  _p_segA1_h(x)
#define   p_segA1h                       __p_segA1_h(p_segA1)

#define   _p_segA1_l(x)                   SET_##x##_L
#define   __p_segA1_l(x)                  _p_segA1_l(x)
#define   p_segA1l                       __p_segA1_l(p_segA1)

#define   _p_segA1_in(x)                   SET_##x##_IO_IN
#define   __p_segA1_in(x)                  _p_segA1_in(x)
#define   p_segA1in                       __p_segA1_in(p_segA1)

#define   _p_segA1_out(x)                   SET_##x##_IO_OUT
#define   __p_segA1_out(x)                  _p_segA1_out(x)
#define   p_segA1out                       __p_segA1_out(p_segA1)
//----------------------------------------------------------------

#define   _p_segA2_h(x)                   SET_##x##_H
#define   __p_segA2_h(x)                  _p_segA2_h(x)
#define   p_segA2h                       __p_segA2_h(p_segA2)

#define   _p_segA2_l(x)                   SET_##x##_L
#define   __p_segA2_l(x)                  _p_segA2_l(x)
#define   p_segA2l                       __p_segA2_l(p_segA2)

#define   _p_segA2_in(x)                   SET_##x##_IO_IN
#define   __p_segA2_in(x)                  _p_segA2_in(x)
#define   p_segA2in                       __p_segA2_in(p_segA2)

#define   _p_segA2_out(x)                   SET_##x##_IO_OUT
#define   __p_segA2_out(x)                  _p_segA2_out(x)
#define   p_segA2out                       __p_segA2_out(p_segA2)
//---------------------------------------------------------------

#define   _p_segA3_h(x)                   SET_##x##_H
#define   __p_segA3_h(x)                  _p_segA3_h(x)
#define   p_segA3h                       __p_segA3_h(p_segA3)

#define   _p_segA3_l(x)                   SET_##x##_L
#define   __p_segA3_l(x)                  _p_segA3_l(x)
#define   p_segA3l                       __p_segA3_l(p_segA3)

#define   _p_segA3_in(x)                   SET_##x##_IO_IN
#define   __p_segA3_in(x)                  _p_segA3_in(x)
#define   p_segA3in                       __p_segA3_in(p_segA3)

#define   _p_segA3_out(x)                   SET_##x##_IO_OUT
#define   __p_segA3_out(x)                  _p_segA3_out(x)
#define   p_segA3out                       __p_segA3_out(p_segA3)
//---------------------------------------------------------------

#define   _p_segA4_h(x)                   SET_##x##_H
#define   __p_segA4_h(x)                  _p_segA4_h(x)
#define   p_segA4h                       __p_segA4_h(p_segA4)

#define   _p_segA4_l(x)                   SET_##x##_L
#define   __p_segA4_l(x)                  _p_segA4_l(x)
#define   p_segA4l                       __p_segA4_l(p_segA4)

#define   _p_segA4_in(x)                   SET_##x##_IO_IN
#define   __p_segA4_in(x)                  _p_segA4_in(x)
#define   p_segA4in                       __p_segA4_in(p_segA4)

#define   _p_segA4_out(x)                   SET_##x##_IO_OUT
#define   __p_segA4_out(x)                  _p_segA4_out(x)
#define   p_segA4out                       __p_segA4_out(p_segA4)
//---------------------------------------------------------------

#define   _p_segA5_h(x)                   SET_##x##_H
#define   __p_segA5_h(x)                  _p_segA5_h(x)
#define   p_segA5h                       __p_segA5_h(p_segA5)

#define   _p_segA5_l(x)                   SET_##x##_L
#define   __p_segA5_l(x)                  _p_segA5_l(x)
#define   p_segA5l                       __p_segA5_l(p_segA5)

#define   _p_segA5_in(x)                   SET_##x##_IO_IN
#define   __p_segA5_in(x)                  _p_segA5_in(x)
#define   p_segA5in                       __p_segA5_in(p_segA5)

#define   _p_segA5_out(x)                   SET_##x##_IO_OUT
#define   __p_segA5_out(x)                  _p_segA5_out(x)
#define   p_segA5out                       __p_segA5_out(p_segA5)
//---------------------------------------------------------------

#define   _p_segA6_h(x)                   SET_##x##_H
#define   __p_segA6_h(x)                  _p_segA6_h(x)
#define   p_segA6h                       __p_segA6_h(p_segA6)

#define   _p_segA6_l(x)                   SET_##x##_L
#define   __p_segA6_l(x)                  _p_segA6_l(x)
#define   p_segA6l                       __p_segA6_l(p_segA6)

#define   _p_segA6_in(x)                   SET_##x##_IO_IN
#define   __p_segA6_in(x)                  _p_segA6_in(x)
#define   p_segA6in                       __p_segA6_in(p_segA6)

#define   _p_segA6_out(x)                   SET_##x##_IO_OUT
#define   __p_segA6_out(x)                  _p_segA6_out(x)
#define   p_segA6out                       __p_segA6_out(p_segA6)
//---------------------------------------------------------------

#define   _p_segA7_h(x)                   SET_##x##_H
#define   __p_segA7_h(x)                  _p_segA7_h(x)
#define   p_segA7h                       __p_segA7_h(p_segA7)

#define   _p_segA7_l(x)                   SET_##x##_L
#define   __p_segA7_l(x)                  _p_segA7_l(x)
#define   p_segA7l                       __p_segA7_l(p_segA7)

#define   _p_segA7_in(x)                   SET_##x##_IO_IN
#define   __p_segA7_in(x)                  _p_segA7_in(x)
#define   p_segA7in                       __p_segA7_in(p_segA7)

#define   _p_segA7_out(x)                   SET_##x##_IO_OUT
#define   __p_segA7_out(x)                  _p_segA7_out(x)
#define   p_segA7out                       __p_segA7_out(p_segA7)
//---------------------------------------------------------------
//---------------------------------------------------------------

/*==========================================================*/

#define   _p_segB1_h(x)                   SET_##x##_H
#define   __p_segB1_h(x)                  _p_segB1_h(x)
#define   p_segB1h                       __p_segB1_h(p_segB1)

#define   _p_segB1_l(x)                   SET_##x##_L
#define   __p_segB1_l(x)                  _p_segB1_l(x)
#define   p_segB1l                       __p_segB1_l(p_segB1)

#define   _p_segB1_in(x)                   SET_##x##_IO_IN
#define   __p_segB1_in(x)                  _p_segB1_in(x)
#define   p_segB1in                       __p_segB1_in(p_segB1)

#define   _p_segB1_out(x)                   SET_##x##_IO_OUT
#define   __p_segB1_out(x)                  _p_segB1_out(x)
#define   p_segB1out                       __p_segB1_out(p_segB1)
//----------------------------------------------------------------

#define   _p_segB2_h(x)                   SET_##x##_H
#define   __p_segB2_h(x)                  _p_segB2_h(x)
#define   p_segB2h                       __p_segB2_h(p_segB2)

#define   _p_segB2_l(x)                   SET_##x##_L
#define   __p_segB2_l(x)                  _p_segB2_l(x)
#define   p_segB2l                       __p_segB2_l(p_segB2)

#define   _p_segB2_in(x)                   SET_##x##_IO_IN
#define   __p_segB2_in(x)                  _p_segB2_in(x)
#define   p_segB2in                       __p_segB2_in(p_segB2)

#define   _p_segB2_out(x)                   SET_##x##_IO_OUT
#define   __p_segB2_out(x)                  _p_segB2_out(x)
#define   p_segB2out                       __p_segB2_out(p_segB2)
//---------------------------------------------------------------

#define   _p_segB3_h(x)                   SET_##x##_H
#define   __p_segB3_h(x)                  _p_segB3_h(x)
#define   p_segB3h                       __p_segB3_h(p_segB3)

#define   _p_segB3_l(x)                   SET_##x##_L
#define   __p_segB3_l(x)                  _p_segB3_l(x)
#define   p_segB3l                       __p_segB3_l(p_segB3)

#define   _p_segB3_in(x)                   SET_##x##_IO_IN
#define   __p_segB3_in(x)                  _p_segB3_in(x)
#define   p_segB3in                       __p_segB3_in(p_segB3)

#define   _p_segB3_out(x)                   SET_##x##_IO_OUT
#define   __p_segB3_out(x)                  _p_segB3_out(x)
#define   p_segB3out                       __p_segB3_out(p_segB3)
//---------------------------------------------------------------

#define   _p_segB4_h(x)                   SET_##x##_H
#define   __p_segB4_h(x)                  _p_segB4_h(x)
#define   p_segB4h                       __p_segB4_h(p_segB4)

#define   _p_segB4_l(x)                   SET_##x##_L
#define   __p_segB4_l(x)                  _p_segB4_l(x)
#define   p_segB4l                       __p_segB4_l(p_segB4)

#define   _p_segB4_in(x)                   SET_##x##_IO_IN
#define   __p_segB4_in(x)                  _p_segB4_in(x)
#define   p_segB4in                       __p_segB4_in(p_segB4)

#define   _p_segB4_out(x)                   SET_##x##_IO_OUT
#define   __p_segB4_out(x)                  _p_segB4_out(x)
#define   p_segB4out                       __p_segB4_out(p_segB4)
//---------------------------------------------------------------

#define   _p_segB5_h(x)                   SET_##x##_H
#define   __p_segB5_h(x)                  _p_segB5_h(x)
#define   p_segB5h                       __p_segB5_h(p_segB5)

#define   _p_segB5_l(x)                   SET_##x##_L
#define   __p_segB5_l(x)                  _p_segB5_l(x)
#define   p_segB5l                       __p_segB5_l(p_segB5)

#define   _p_segB5_in(x)                   SET_##x##_IO_IN
#define   __p_segB5_in(x)                  _p_segB5_in(x)
#define   p_segB5in                       __p_segB5_in(p_segB5)

#define   _p_segB5_out(x)                   SET_##x##_IO_OUT
#define   __p_segB5_out(x)                  _p_segB5_out(x)
#define   p_segB5out                       __p_segB5_out(p_segB5)
//---------------------------------------------------------------

#define   _p_segB6_h(x)                   SET_##x##_H
#define   __p_segB6_h(x)                  _p_segB6_h(x)
#define   p_segB6h                       __p_segB6_h(p_segB6)

#define   _p_segB6_l(x)                   SET_##x##_L
#define   __p_segB6_l(x)                  _p_segB6_l(x)
#define   p_segB6l                       __p_segB6_l(p_segB6)

#define   _p_segB6_in(x)                   SET_##x##_IO_IN
#define   __p_segB6_in(x)                  _p_segB6_in(x)
#define   p_segB6in                       __p_segB6_in(p_segB6)

#define   _p_segB6_out(x)                   SET_##x##_IO_OUT
#define   __p_segB6_out(x)                  _p_segB6_out(x)
#define   p_segB6out                       __p_segB6_out(p_segB6)
//---------------------------------------------------------------

#define   _p_segB7_h(x)                   SET_##x##_H
#define   __p_segB7_h(x)                  _p_segB7_h(x)
#define   p_segB7h                       __p_segB7_h(p_segB7)

#define   _p_segB7_l(x)                   SET_##x##_L
#define   __p_segB7_l(x)                  _p_segB7_l(x)
#define   p_segB7l                       __p_segB7_l(p_segB7)

#define   _p_segB7_in(x)                   SET_##x##_IO_IN
#define   __p_segB7_in(x)                  _p_segB7_in(x)
#define   p_segB7in                       __p_segB7_in(p_segB7)

#define   _p_segB7_out(x)                   SET_##x##_IO_OUT
#define   __p_segB7_out(x)                  _p_segB7_out(x)
#define   p_segB7out                       __p_segB7_out(p_segB7)
//---------------------------------------------------------------
//---------------------------------------------------------------





#endif

