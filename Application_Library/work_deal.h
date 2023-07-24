#ifndef	__WORK_H__
#define	__WORK_H__


extern void work_deal(void);
extern	void	relay_deal();


extern	void	action_work(void);  //��ʼ����
extern	void	quit_work(void);    //�˳�����

#if   kkg_en
extern	void	kkg_work_api();
#endif

//����ģʽ
extern	uchar	xdata	b_mode;

extern	uchar	xdata	b_set_wendu;	//�趨���¶�
extern	uchar	xdata	b_grade;	//��λ

//��������ʱ�����
extern	uchar	xdata	b_ctrl_sec_1;
extern	uint	xdata	b_ctrl_sec_2;
extern	uchar	xdata	b_ctrl_sec_3;

#if	double_ad_channel
extern	uchar	xdata	b_temp_1_ref_sec;
#endif

//����ʱ�����
extern	uchar	xdata	b_mjs_set_sec;

extern	uchar xdata b_yuyue_run_cnt ;	//ԤԼ����ʱ����ʱ������

extern	uchar xdata	b_wendu_ok;	//�ﵽĿ���¶ȵĴ���
extern	uchar	xdata	b_kkg_buf;

//����ʱ�����
extern	uchar	xdata	b_baowen_hour;
extern	uchar	xdata	b_baowen_min;
extern	uchar	xdata	b_baowen_sec;

//ԤԼʱ�����
extern	uchar	xdata	b_yuyue_hour;
extern	uchar	xdata	b_yuyue_min;
extern	uchar	xdata	b_yuyue_sec;

//����ʱ�����
extern	uchar	xdata	b_dingshi_hour;
extern	uchar	xdata	b_dingshi_min;
extern	uchar	xdata	b_dingshi_sec;

//����״̬��ʶλ:set ���ã�odoff ��ʱ��power�����У�odonԤԼ��odoff_begin��������ʱ
extern	bit		f_mjs_set;
extern	bit		f_mjs_dingshi;
extern	bit		f_mjs_power;
extern	bit		f_mjs_yuyue;
extern	bit		f_mjs_down;
extern	bit		f_dingshi_begin;

extern	bit	f_NO_jiangdang;	//������־λ 0:�ɽ��� 1:���ɽ���



extern  bit     f_stop_1;
extern  bit     f_stop_2;

/*ů�˻�����*/
extern	bit		f_sys_power_1;  //���(A) 0:��,1:��
extern	bit		f_sys_power_2;  //�ұ�(B) 0:��,1:��

extern  bit     f_sys_on_1;     //���(A) 0:����,1:����
extern  bit     f_sys_on_2;     //���(A) 0:����,1:����

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


////		������������
//#define		c_key_mode		0	//1Ϊ�ᴥ��0Ϊ����
//#define		c_shortKey_noCnt		1	//�ͷ���������	
//#define		c_shortKey_cnt		2	//������������	����ֵ������Ϊ2����λΪ10ms�����ᴥΪ5����λΪɨ�������
//#define		c_mode_add		1	//1Ϊģʽ+�� 0Ϊģʽ���ټ�����Ҫȥ���������ü�ֵ
//#define		c_yuyue_loop		1	//ԤԼ�Ӽ�ʱ��ѭ�� 
//#define		c_odon_minstr	 	0	//������ʼԤԼʱ�� 
//#define		c_odon_hourstr	  	2	//������ʼԤԼʱ��
//#define		c_odon_hour_max	 	8	//�������ԤԼʱ��	
//#define		c_odon_min_max	 	0	//�������ԤԼʱ��	 
//#define		c_odon_hour_min	 	0	//������СԤԼʱ��	 
//#define		c_odon_min_min	 	30	//������СԤԼʱ��	
//#define		c_yyyc			0	//Ϊ1��ԤԼʱ��Ϊ���ʱ��
//#define		c_yuyueset		0	//Ϊ1��ԤԼ�����Ե�ԤԼʱ��
//#define		c_odon_minadd		30	//ԤԼ���Լ���
//#define		c_odon_mindec		0	//ԤԼ����
//
//#define		c_mode_num		4	//������	  
//#define		c_odoff_loop		1	//����ʱ��Ӽ�ʱ��ѭ��

