#ifndef __XS16TK06X_TK_H__
#define __XS16TK06X_TK_H__

/////////////////////////////////////////TK//////////////////////////////////////////////
#define CTK_START 					{CSD_START &= ~0X01;CSD_START |= 0X01;}//CTKģ�鿪���ӵ�0��1
#define CTK_STOP 						(CSD_START &= ~0X01)//CTKģ��ֹͣ
#define CTK_PULL_I_SET(x) 	{PULL_I_SELA_L = x;SNS_SCAN_CFG2 &= (~0x40);SNS_SCAN_CFG2 |= ((0x100&x)>>2);}//��������Դ����
#define CTK_PRS_SW_SET(x) 	{SNS_SCAN_CFG1 &= ~(0x40);SNS_SCAN_CFG1 |= (0x40&(((unsigned char)x)<<6));}//ǰ�˳�ŵ翪��,1Ϊ�أ�0Ϊ��
#define CTK_PRS_SET(x) 			{SNS_SCAN_CFG1 &= ~(0x3F);SNS_SCAN_CFG1 |= (0x3F&(x<<0));}//PRS(��ŵ�Ƶ��) = 48/2/(x+4),62:��̬�ֲ�(1~1.5~3)MHz,63:���ȷֲ�(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz

#define CTK_PAR_SET(x) 				{SNS_SCAN_CFG2 &= ~(0x20);SNS_SCAN_CFG2 |= (0x20&(x<<5));}//1:Ϊ��ͨ������ģʽ��0��Ϊ��ͨ��ģʽ
#define CTK_ADDR_SET(x) 			{SNS_SCAN_CFG2 &= ~(0x1F);SNS_SCAN_CFG2 |= (0x1F&(x<<0));}//����ͨ����ַ0~25
#define CTK_RESO_SET(x) 			{SNS_SCAN_CFG3 &= ~(0x70);SNS_SCAN_CFG3 |= (0x70&(x<<4));}//0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ��
#define CTK_DS_SET(x) 				{SNS_SCAN_CFG3 &= ~(0x0C);SNS_SCAN_CFG3 |= (0x0C&(x<<2));}//����ٶ�0:24MHz,1:12MHz,2:6MHz,3:4MHz
#define CTK_PRE_CH_SET(x) 		{SNS_SCAN_CFG3 &= ~(0x02);SNS_SCAN_CFG3 |= (0x02&(x<<1));}//Ԥ���ʱ�䣺0Ϊ20us,1Ϊ40us
#define CTK_PRE_DISCH_SET(x) 	{SNS_SCAN_CFG3 &= ~(0x01);SNS_SCAN_CFG3 |= (0x01&(x<<0));}//Ԥ�ŵ�ʱ�䣺0Ϊ2us,1Ϊ10us

#define CTK_PD_SET(x) 				{PD_ANA &= ~0x02;PD_ANA |= (0x02&(x<<1));}//0ΪCTK����1ΪCTK��
#define CTK_RB_SET(x) 				{SNS_ANA_CFG &= (~0x38);SNS_ANA_CFG |= (0x38&(x<<3));}//ѡ��RB�����С4:60K 5:80K ��������
#define CTK_VTH_SET(x) 				{SNS_ANA_CFG &= (~0x07);SNS_ANA_CFG |= (0x07&(x<<0));}//�ο���ѹ(0:1.5V),(1:2.1V),(2:2.5V),(3:2.9V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);ע��VCC-VTH>0.5V


#define CTK_INT_FLAG_CLR IRCON1 &= ~0X20//���CTK�жϱ�־λ

#define CTK_IE_SET IEN1 |= 0X20//��CTK�ж�ʹ��
#define CTK_IE_CLR IEN1 &= ~0X20//��CTK�ж�ʹ

#define CTK_IP_SET IPL1 |= 0X20//����CTK�ж��ż�Ϊ��
#define CTK_IP_CLR IPL1 &= ~0X20//����CTK�ж��ż�Ϊ��


#if SNS_NUM

extern unsigned char xdata sensor_open[];				//0~26	
extern unsigned char sns_next;
extern unsigned char xdata Mode;								//0Ϊ��ͨ��ģʽ��1Ϊ��ͨ������ģʽ
extern unsigned int  xdata pull_i_value[];//����Դ����;

#if (CS_SW == 1)
extern	uint cs_noise;
#endif

extern bit adjust_done_flag;
extern bit base_line_int_flag;
extern bit ctk_circle_done;//0Ϊctkɨ���У�1Ϊɨ��һ�����


extern unsigned int xdata pull_i_value_parallel;

extern bit parallel_init_flag;


extern unsigned long xdata open_sns;

/***********5-25**********************/
extern unsigned long xdata open_sns_tem;
/***********5-25**********************/

extern unsigned long xdata adjust_flag;



extern unsigned int  xdata n_base_line[];
extern unsigned char xdata n_base_line_reno_count[];
extern unsigned char xdata touch_confirm_count[];
	

extern unsigned long xdata mode_flag;
extern unsigned long xdata muli_key_flag;

extern unsigned char xdata touch_left_count[];	


extern unsigned char  xdata over_p_noise_count[];
extern unsigned char  xdata under_p_noise_count[];
extern unsigned char  xdata over_n_noise_count[];
extern unsigned char  xdata under_n_noise_count[];
extern unsigned char  xdata under_nn_noise_count[];

#if (RENOVATE_MODE == 1)
extern bit water_flow_flag;	
extern unsigned int 	xdata water_flow_left_count;	
extern unsigned char  xdata water_flow_key_count;
extern unsigned char  xdata water_flow_key_reset_cnt;
extern unsigned char xdata touch_confirm_count[];
extern unsigned char xdata i;
#endif
extern unsigned char 	xdata multi_key_count;
extern unsigned char  xdata multi_key_reset_cnt;



//-----------------------------------------------------------------//
//�������ƣ� void Base_Line_Init()
//�������ܣ� ���߳�ʼ��
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void Base_Line_Init();



//-----------------------------------------------------------------//
//�������ƣ� void CTK_TK_Left_Count(void)
//�������ܣ� ��ָ�뿪�жϼ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void CTK_TK_Left_Count(uchar addr);


//-----------------------------------------------------------------//
//�������ƣ� void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
//�������ܣ� SNS���߸���
//��������� unsigned char addr��SNSͨ��;unsigned int fth:��ָ��ֵ
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void CTK_SNS_Renovate(unsigned char addr,unsigned int fth);

/////////////////////////////////////////TK//////////////////////////////////////////////


extern void XS16TK06X_Set_Touch_Flag(void);
extern uchar Sns_Count;



extern void CTK_Set_Para(void);
extern unsigned int   code 	FTH[];
extern unsigned char  code 	SNS[];
extern unsigned int   code 	PUIV[]; 
extern unsigned char  xdata sensor_open[];
extern unsigned int   xdata pull_i_value[];
extern unsigned char  xdata touch_left_count[];
extern unsigned char  xdata over_p_noise_count[];
extern unsigned char  xdata under_p_noise_count[];
extern unsigned char  xdata over_n_noise_count[];
extern unsigned char  xdata under_n_noise_count[];
extern unsigned char  xdata n_base_line_reno_count[];
extern unsigned int   xdata n_base_line[];
extern unsigned char  xdata touch_confirm_count[];


#if UN_NORMAL_CHECK
extern unsigned char xdata un_normal_count;
extern unsigned char xdata un_normal_recover_count;
extern bit un_normal_flag;
extern unsigned long xdata adjust_flag;
extern void Rawdata_Un_Normal(uchar sns_num);
#endif

extern void CTK_Init(void);

#endif


#endif  