#ifndef		__Global_H__
#define		__Global_H__

	
/*************************************************/
/*****************ϵͳ��ͷ�ļ�********************/
/*************************************************/	
#include 	"Config.h"
#include 	"intrins.h"
#include 	"string.h"

//------------------------------------------------------------------------------------------
//		���²��ֲ�������
/*==========================================================================================     
˵��:
����AD��ͨ��������AD�����ԣ������¶ȱ�
==========================================================================================*/
#define   ad_en   1     //AD����ʹ��

#define		double_ad_channel	0	//�Ƿ�˫ͨ��
#define		c_ad_channel	10	//ADͨ��1
#define		c_ad_up_pull	1	//AD�������ο���������1��ADֵȡ����������	
#define		c_ad_mode 	0	//o�¶�  1��ͨAD

#if	double_ad_channel
	#define		c_ad_channel_1	8	//ADͨ��2
	#define		c_ad_up_pull_1	1	//AD�������ο���������1��ADֵȡ����������	
	#define		c_ad_mode_1 	0	//o�¶�  1��ͨAD

#endif
	#define		c_bjhf_1	0	 //��·�����ɻָ�
	#define		c_bjhf_2	0   //��·�����ɻָ�
	#define		c_kltime		3	//��·����ʱ�䣨��λ�룩�����ſ�ʼ��ʱ��Ϊ0��ֱ�ӱ���




#define		c_ntc_e1_return  0 //��·����ɻָ�
#define		c_ntc_e2_return  0 //��·����ɻָ�

//	�¶ȱ� �ɲ�0-136��	
#define		tab_50k_10k	0	//50K̽ͷ�ο�10K����
#define		tab_50k_27k	0	//50K̽ͷ�ο�27K����
#define		tab_100k_10k	0	//100K̽ͷ�ο�10K����
#define		tab_100k_27k	0	//100K̽ͷ�ο�27K����
#define		tab_other		1	//���϶�����������ad.c����ӱ��
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
//		��������������
/*==========================================================================================     
˵��:
���÷�����IO�ڣ�Ƶ��
==========================================================================================*/
#define   buz_en  1    //����������ʹ��
#define		c_ad_buz_com	1		//AD�����������
#define		buz2K		0		//������Ƶ�� 1 2k  0 4k
#define		p_buz		PC2
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
//		������ֲ�������
/*==========================================================================================     
˵��:
�������IO�ڣ�����
�̵���100ms�л���Ĭ�ϸ����������ڼ̵��������Ͳ�������Ŀɿع�����
�ɿع�Ĭ��ʹ�ö�����ʽ����ǰ�����ɹ�EMC��Ĭ�ϸ���
==========================================================================================*/
#define     out_en  1   //�̵�����������ʹ�� 
#define		p_out1		PC5
#define		p_out2		PC5
#define		p_out3		PC5


#define   kkg_en   1  //�ɿع�������������ʹ��
#if   kkg_en
#define		p_zero		PC3     //�����
#define		p_kkg		 PA1      //�ɿع������_A
#define		p_kkg_B		 PA1      //�ɿع������_B
#define		c_high_drive  0   //����1   ����0
#endif
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
//		������������
/*==========================================================================================     
˵��:
���ð���Ϊ�ᴥ���ߴ���
�ᴥ�������ڴ˴����ã���������������������������
==========================================================================================*/
#define		c_key_mode		0	//1Ϊ�ᴥ��0Ϊ����

#if   c_key_mode
//		IO�ڶ���,����Ϊ1
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
//		��ʾ��������
/*==========================================================================================     
˵��:
������ʾ������ʽ��������ʾIO�ڣ�����LED�ƵĶ�Ӧλ��
==========================================================================================*/
  
#define			c_disp_com		0		//������SEG�ڣ�һ��ɨ8��SEG��
#define			c_disp_seg		0		//������COM�ڣ�һ��ɨ8��COM��
#define			c_disp_comseg		0		//�޵���ɨ ��ÿ��ɨ1���ƣ�������ɨ
#define			c_disp_comcom		0		//�޵���ɨ ��ÿ��ɨ1���ƣ���������ɨ
#define			c_TM1628_EN		0   //1668/1628
#define			c_TM1629_EN		0   //1629

#define			c_disp_comcom_qi		0		//�޵���ɨ ��ÿ��ɨ1���ƣ���������ɨ
#define			c_disp_comcom2_qi		1		//�޵���ɨ ��ÿ��ɨ1���ƣ���������ɨ


#if (c_TM1628_EN || c_TM1629_EN)
//  ��1�����ùܽ�
#define	p_1628dio	PXX
#define	p_1628clk	PXX	
#define	p_1628stb	PXX
  
//  ��2�����������������
#define	c_1628_lightGrade	0x8a	//���ȵȼ�
#define	c_1628_lightMode	0x03	//��ʾģʽ	
/*
��ʾģʽ	
00:4bit-13part	01:5bit-12part
10:6bit-11part  11:7bit-10part
*/
#else	

#define			c_ledScan_cnt		38//6//12//15//13//30//31//0x08		//ɨ���������������
//		��λ���壬���õĽŶ�PXX

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

//		led�ƶ��壬����ʵ�����ѡ����Ӧ��λ
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
//���Խ���������ʾ����ܵ������ͨ������ͨѶ�������ݵ���ʾ���԰壬Ҫ�����ʾ���԰�ʹ�ã�������ɹر�ʹ��
#define   test_en   0       //�������ʹ��
#define   p_test  PA7       //��������źŽ�
//------------------------------------------------------------------------------------------



/*�궨��*/

#define		c_yyyc			0	//Ϊ1��ԤԼʱ��Ϊ���ʱ��
#define		c_yuyueset		0	//Ϊ1��ԤԼ�����Ե�ԤԼʱ��


//		���ܱ���ѡ��

#define		c_s_zf		1	//˫̽ͷ��
#define		c_s_zz		1	//˫̽ͷ����
#define		c_s_bt		0	//˫̽ͷ����
#define		c_s_zg		0	//˫̽ͷ��
#define		c_s_ts		0	//˫̽ͷ��ˮ	

#define		c_d_zf		0	//��̽ͷ��
#define		c_d_zz		0	//��̽ͷ����/ϡ��
#define		c_d_bt		0	//��̽ͷ����
#define		c_d_dt		0	//��̽ͷ��
#define		c_d_sgc		0	//ˮ����

#define		c_a_zh		0	//��

#define		c_a_sn		0	//����	
#define		c_suannai_mode	0	//����ģʽ������������0

#define		c_a_rf		0	//�ȷ�
#define		c_a_dg		0	//����
#define		c_a_ss		0	//��ˮ
#define		c_a_gsd		0	//��ˮ��

//		������ѡ
#define		c_baowen_h	70	//�����¶�	ԭ��2��
#define		c_baowen_l	68
#define		c_baowen_g	0x04   //���¹���











/*************************************************/
/*****************�û�ʹ��ͷ�ļ�******************/
/*************************************************/
#include 	"Other.h"

////�˴�����useͷ�ļ�////




/*************************************************/
/*****************��������ͷ�ļ�******************/
/*************************************************/
//#include 	"24C02.h"
////�˴�����appͷ�ļ�////



/*************************************************/
/*****************����ģ���ļ�********************/
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

