#ifndef	__AD_h__
#define	__AD_h__


/*************************************************************
***********************��������*******************************
*************************************************************/
#if   tab_100k_27k
#define		c_open_error	0x03	//��·AD ע�� ����·AD��Ӧ�¶ȱ�����-20������
#define		c_short_error	0xfd	//��·AD	ע�⣺��·AD��Ӧ�¶ȱ�����250������
#define   c_over_error       251//0xf8   //����AD	ע�⣺����AD��Ӧ�¶ȱ�����180������
#endif

#if   tab_50k_10k
#define		c_open_error	0x05	//��·AD ע�� ����·AD��Ӧ�¶ȱ�����-20������
#define		c_short_error	0xFC	//��·AD	ע�⣺��·AD��Ӧ�¶ȱ�����250������
#define   c_over_error 0xF6   //����AD	ע�⣺����AD��Ӧ�¶ȱ�����180������
#endif

#if   tab_100k_10k
#define		c_open_error	0x02	//��·AD ע�� ����·AD��Ӧ�¶ȱ�����-20������
#define		c_short_error	0xfa	//��·AD	ע�⣺��·AD��Ӧ�¶ȱ�����250������
#define   c_over_error 0xec   //����AD	ע�⣺����AD��Ӧ�¶ȱ�����180������
#endif

#if   tab_50k_27k
#define		c_open_error	0x05	//��·AD ע�� ����·AD��Ӧ�¶ȱ�����-20������
#define		c_short_error	0xFE	//��·AD	ע�⣺��·AD��Ӧ�¶ȱ�����250������
#define   c_over_error 0xFD   //����AD	ע�⣺����AD��Ӧ�¶ȱ�����180������
#endif

#if   tab_other
#define		c_open_error	3	//��·AD ע�� ����·AD��Ӧ�¶ȱ�����-20������
#define		c_short_error	248	//��·AD	ע�⣺��·AD��Ӧ�¶ȱ�����250������
#define   c_over_error 243   //�¶ȱ���AD
#endif


#define		c_temp_fast	0	//�������캯��

/*************************************************************
***********************�ⲿ��������***************************
*************************************************************/
extern	void	lab_ad_fun();
extern	void	warning_check();


/*************************************************************
***********************�ⲿ��������***************************
*************************************************************/
extern	unsigned char	data	b_warning;
extern	unsigned char	xdata	b_error_sec;
extern	unsigned char	xdata	b_error_sec_1;
extern	unsigned char	xdata	b_error_e3;

extern	unsigned char data	gb_wendu;
extern	unsigned char 	xdata	b_temp;
extern  unsigned char   xdata   Target_wendu_1;   //Ŀ���¶�
extern  unsigned char   xdata   Target_wendu_2;   //Ŀ���¶�
#if			 double_ad_channel
extern	unsigned char data	gb_wendu2;	//adͨ��2
extern	unsigned char 	xdata	b_temp_1;			//adͨ��2
#endif



#endif
