#include "Config.h"


#if	(PWM_REG_dataBuf_en)
	uchar	xdata	b_pwm_buf1_l;
	uchar	xdata	b_pwm_buf1_h;
	uchar	xdata	b_pwm_buf2_l;
	uchar	xdata	b_pwm_buf2_h;
#endif

#if (PWM0_EN == 1)
	#pragma message "���룬void PWM0_Init(void)����"
	
	//��������PWM0_Init(void)
	//��  �ܣ���ʼ��PWM0
	//��  ������
	//����ֵ����

	void PWM0_Init(void)
	{ 
			
		EA = 0;
		#if	(PWM0_CH0_PB0_EN)
			TRISB &= ~0x01;
		#endif
		
		#if	(PWM0_CH0_PB5_EN)
			TRISB &= ~0x20;
		#endif

		#if	(PWM0_CH1_PB1_EN)
			TRISB &= ~0x02;
		#endif
		
		#if	(PWM0_CH1_PC0_EN)
			TRISC&= ~0x01;
		#endif

		#if	(PWM0_CH2_PB2_EN)
			TRISB &= ~0x04;
		#endif
		
		#if	(PWM0_CH2_PC3_EN)
			TRISC&= ~0x08;
		#endif
		
		#if	(PWM0_CH3_PB3_EN)
			TRISB &= ~0x08;
		#endif
		
		#if	(PWM0_CH3_PC5_EN)
			TRISC&= ~0x20;
		#endif	
	
		PWM0_CH_CTRL |= ((PWM0_CH0_EN<<0)+(PWM0_CH1_EN<<1)+(PWM0_CH2_EN<<2)+(PWM0_CH3_EN<<3));
		PWM0_CH_CTRL |= ((PWM0_CH0_POLO_SEL<<4)+(PWM0_CH1_POLO_SEL<<5)+(PWM0_CH2_POLO_SEL<<6)+(PWM0_CH3_POLO_SEL<<7));
		
		PWM_EN |= ((PWM0_CH1_CMOD<<3)+(PWM0_CH2_CMOD<<4)+(PWM0_CH3_CMOD<<5));
		PWM_EN |= 0x01;
		PWM0_IO_SET(PWM0_IO_SEL);//0������PB0/1/2/3 ��ѡ�� PWM0_A/B/C/D ���ܣ�1������PB5/PC0/PC3/PC5 ��ѡ�� PWM0_A1/B1/C1/D1 ����
		PWM0_CH0_CNT_L = 0x00;
		PWM0_CH0_CNT_H = 0x00;
		PWM0_CH1_CNT_L = 0x00;
		PWM0_CH1_CNT_H = 0x00;
		PWM0_CH2_CNT_L = 0x00;
		PWM0_CH2_CNT_H = 0x00;
		PWM0_CH3_CNT_L = 0x00;
		PWM0_CH3_CNT_H = 0x00;
		PWM0_MOD_L = 0x00;
		PWM0_MOD_H = 0x00;
		EA = 1;
		
	}
	
	//��������void PWM0A_Set(ulong pwm0a_fre, ulong pwm0a_rank)
	//��  �ܣ�����PWM0A
	//��  ����pwm0a_freƵ�ʣ����� =��PWM0_MOD+1��
	//��  ����pwm0a_rankռ�ձ�,pwm0a_cnt =(24.0*1000000)/(pwm0a_fre*1000.0),pwm0a_rank Ӧ<= pwm0a_cnt();
	//[pwm0a_fre,pwm0a_rank]-[4000,6000]--4KHz 100%duty,[pwm0a_fre,pwm0a_rank]-[2000,12000]--4KHz 100%duty
	//����ֵ����
	#if (PWM0_CH0_EN)
	void PWM0A_Set(ulong pwm0a_fre, uchar per)
	{ 
		uint pwm0a_cnt = 0;
		uint	i;
	
		pwm0a_cnt = (24.0*1000000)/(pwm0a_fre*1.0)-1;
		
		if(per>=100)
		{
			PWM0_CH0_CNT_L = 0xFF;
			PWM0_CH0_CNT_H = 0xFF;
		}
		else if(per==0)
		{
			PWM0_CH0_CNT_L = 0x00;
			PWM0_CH0_CNT_H = 0x00;
		}
		else
		{
			i=(ulong)pwm0a_cnt*per/100;
			PWM0_CH0_CNT_L=(uchar)(i);
			PWM0_CH0_CNT_H=(uchar)(i>>8);
		}
		PWM0_MOD_L = (uchar)pwm0a_cnt;
		PWM0_MOD_H = (uchar)(pwm0a_cnt>>8);	
		#if	(PWM_REG_dataBuf_en)
			b_pwm_buf1_l=PWM0_CH0_CNT_L;
			b_pwm_buf1_h=PWM0_CH0_CNT_H;
			b_pwm_buf2_l=PWM0_MOD_L;
			b_pwm_buf2_h=PWM0_MOD_H;	
		#endif	
	}  
	#endif
	
	//��������void PWM0B_Set(ulong pwm0b_fre, ulong pwm0b_rank)
	//��  �ܣ�����PWM0B
	//��  ����pwm0b_freƵ�ʣ����� =��PWM0_MOD+1��
	//��  ����pwm0b_rankռ�ձ�,pwm0b_cnt =(24.0*1000000)/(pwm0b_fre*1000.0),pwm0b_rank Ӧ<= pwm0b_cnt();
	//[pwm0b_fre,pwm0b_rank]-[4000,6000]--4KHz 100%duty,[pwm0b_fre,pwm0b_rank]-[2000,12000]--4KHz 100%duty
	//����ֵ����
	#if (PWM0_CH1_EN)
	void PWM0B_Set(ulong pwm0a_fre, uchar per)
	{ 
		uint pwm0a_cnt = 0;
		uint	i;
	
		pwm0a_cnt = (24.0*1000000)/(pwm0a_fre*1.0)-1;
		
		if(per>=100)
		{
			PWM0_CH1_CNT_L = 0xFF;
			PWM0_CH1_CNT_H = 0xFF;
		}
		else if(per==0)
		{
			PWM0_CH1_CNT_L = 0x00;
			PWM0_CH1_CNT_H = 0x00;
		}
		else
		{
			i=(ulong)pwm0a_cnt*per/100;
			PWM0_CH1_CNT_L=(uchar)(i);
			PWM0_CH1_CNT_H=(uchar)(i>>8);
		}
		PWM0_MOD_L = (uchar)pwm0a_cnt;
		PWM0_MOD_H = (uchar)(pwm0a_cnt>>8);	
		
		#if	(PWM_REG_dataBuf_en)
			b_pwm_buf1_l=PWM0_CH1_CNT_L;
			b_pwm_buf1_h=PWM0_CH1_CNT_H;
			b_pwm_buf2_l=PWM0_MOD_L;
			b_pwm_buf2_h=PWM0_MOD_H;	
		#endif	
	}
	#endif
	
	//��������void PWM0C_Set(ulong pwm0c_fre, ulong pwm0c_rank)
	//��  �ܣ�����PWM0C
	//��  ����pwm0c_freƵ�ʣ����� =��PWM0_MOD+1��
	//��  ����pwm0c_rankռ�ձ�,pwm0c_cnt =(24.0*1000000)/(pwm0c_fre*1000.0),pwm0c_rank Ӧ<= pwm0c_cnt();
	//[pwm0c_fre,pwm0c_rank]-[4000,6000]--4KHz 100%duty,[pwm0c_fre,pwm0c_rank]-[2000,12000]--4KHz 100%duty
	//����ֵ����
	#if (PWM0_CH2_EN)
	void PWM0C_Set(ulong pwm0a_fre, uchar per)
	{ 
		uint pwm0a_cnt = 0;
		uint	i;
	
		pwm0a_cnt = (24.0*1000000)/(pwm0a_fre*1.0)-1;
		
		if(per>=100)
		{
			PWM0_CH2_CNT_L = 0xFF;
			PWM0_CH2_CNT_H = 0xFF;
		}
		else if(per==0)
		{
			PWM0_CH2_CNT_L = 0x00;
			PWM0_CH2_CNT_H = 0x00;
		}
		else
		{
			i=(ulong)pwm0a_cnt*per/100;
			PWM0_CH2_CNT_L=(uchar)(i);
			PWM0_CH2_CNT_H=(uchar)(i>>8);
		}
		PWM0_MOD_L = (uchar)pwm0a_cnt;
		PWM0_MOD_H = (uchar)(pwm0a_cnt>>8);	
		
		#if	(PWM_REG_dataBuf_en)
			b_pwm_buf1_l=PWM0_CH2_CNT_L;
			b_pwm_buf1_h=PWM0_CH2_CNT_H;
			b_pwm_buf2_l=PWM0_MOD_L;
			b_pwm_buf2_h=PWM0_MOD_H;	
		#endif	
	} 
	#endif
	//��������void PWM0D_Set(ulong pwm0d_fre, ulong pwm0d_rank)
	//��  �ܣ�����PWM0D
	//��  ����pwm0d_freƵ�ʣ����� =��PWM0_MOD+1��
	//��  ����pwm0d_rankռ�ձ�,pwm0d_cnt =(24.0*1000000)/(pwm0d_fre*1000.0),pwm0d_rank Ӧ<= pwm0d_cnt();
	//[pwm0d_fre,pwm0d_rank]-[4000,6000]--4KHz 100%duty,[pwm0d_fre,pwm0d_rank]-[2000,12000]--4KHz 100%duty
	//����ֵ����
	#if (PWM0_CH3_EN)
	void PWM0D_Set(ulong pwm0a_fre, uchar per)
	{ 
		uint pwm0a_cnt = 0;
		uint	i;
	
		pwm0a_cnt = (24.0*1000000)/(pwm0a_fre*1.0)-1;
		
		if(per>=100)
		{
			PWM0_CH3_CNT_L = 0xFF;
			PWM0_CH3_CNT_H = 0xFF;
		}
		else if(per==0)
		{
			PWM0_CH3_CNT_L = 0x00;
			PWM0_CH3_CNT_H = 0x00;
		}
		else
		{
			i=(ulong)pwm0a_cnt*per/100;
			PWM0_CH3_CNT_L=(uchar)(i);
			PWM0_CH3_CNT_H=(uchar)(i>>8);
		}
		PWM0_MOD_L = (uchar)pwm0a_cnt;
		PWM0_MOD_H = (uchar)(pwm0a_cnt>>8);	
		
		#if	(PWM_REG_dataBuf_en)
			b_pwm_buf1_l=PWM0_CH3_CNT_L;
			b_pwm_buf1_h=PWM0_CH3_CNT_H;
			b_pwm_buf2_l=PWM0_MOD_L;
			b_pwm_buf2_h=PWM0_MOD_H;	
		#endif	
	}
	#endif
#endif
	
#if (PWM1_EN == 1)
	#pragma message "���룬void PWM1_Init(void)����"
	
	//��������PWM1_Init(void)
	//��  �ܣ���ʼ��PWM1
	//��  ������
	//����ֵ����

	void PWM1_Init(void)
	{ 
		EA = 0;

		#if (PWM1_PD0_EN)
			TRISD &= ~0x01;
			PWM1_IO_SET(0);//0������PD0 ��ѡ�� PWM1_A ���ܣ�1������ PC6 ��ѡ�� PWM1_A1 ����
		#else
			TRISC &= ~0x40;
			PWM1_IO_SET(1);//0������PD0 ��ѡ�� PWM1_A ���ܣ�1������ PC6 ��ѡ�� PWM1_A1 ����
		#endif
		PWM_EN |= 0x02;//ͨ��ʹ��
		PWM1_L_L = 0x00;
		PWM1_L_H = 0x00;
		PWM1_H_L = 0x00;
		PWM1_H_H = 0x00;

		EA = 1;
	}
	
	
	#pragma message "����?vvoid PWM1_Set(bit pwm1_switch,ulong pwm1_fre,ulong pwm1_duty)����"
	//��������void PWM1_Set(bit pwm1_switch,ulong pwm1_fre,ulong pwm1_duty);
	//��  �ܣ�PWM1����
	//������ڣ�TPWM1/2_data = (PWM1/2_H + PWM1/2_L)* T_CLK_24MHz(us)��
	//���ռ�ձȣ�DPWM1/2_data = PWM1/2_H/(PWM1/2_L + PWM1/2_H)��
	//��  ����bit pwm1_switch:PWM1����ģ�鿪�ؿ��ƣ�0Ϊ�أ�1Ϊ����ulong pwm1_freƵ��(Hz);ulong pwm1_duty:PWM�ߵ�ƽ���� (0 <= pwm1_duty <= pwm1_h_l);
	//����ֵ����
	//[pwm1_fre,pwm1_duty]-[4000-6000]-[4K,100%];[pwm1_fre,pwm1_duty]-[2000-12000]-[2K,100%];
	void PWM1_Set(bit pwm2_switch,ulong pwm2_fre,uchar per)
	{	
		uint xdata pwm2_h = 0X00;
		uint xdata pwm2_l = 0X00;	
		ulong xdata pwm2_h_l = ((24.0*1000000*1.0) / (pwm2_fre*1.0));
		if(pwm2_switch == 1)
		{
			#if (PWM1_PD0_EN)
				TRISD &= ~0x01;
			#else
				TRISC &= ~0x40;
			#endif
			PWM_EN |= 0x02;
			if(per>=100)
			{
				pwm2_h = (uint)pwm2_h_l;
				pwm2_l = 0;
			}
			else if(per==0)
			{
				pwm2_h =0;
				pwm2_l =(uint)pwm2_h_l;
			}
			else
			{
				pwm2_h=pwm2_h_l*per/100;
				pwm2_l=pwm2_h_l - (ulong)pwm2_h;
			}
				
			PWM1_L_L = (uchar)(pwm2_l);
			PWM1_L_H = (uchar)(pwm2_l >> 8);
			PWM1_H_L = (uchar)(pwm2_h);
			PWM1_H_H = (uchar)(pwm2_h >> 8);
		}
		else
		{
				PWM1_L_L = 0x00;
				PWM1_L_H = 0x00;
				PWM1_H_L = 0x00;
				PWM1_H_H = 0x00;
				PWM_EN &= ~0x02;
				#if (PWM1_PD0_EN)
					TRISD |= 0x01;
				#else
					TRISC |= 0x40;
				#endif
		}
		#if	(PWM_REG_dataBuf_en)
			b_pwm_buf1_l=PWM1_L_L;
			b_pwm_buf1_h=PWM1_L_H;
			b_pwm_buf2_l=PWM1_H_L;
			b_pwm_buf2_h=PWM1_H_H;
		#endif
	}
	#endif
	
	#if (PWM2_EN == 1)
	#pragma message "���룬void PWM2_Init(void)����"
	
	//��������PWM2_Init(void)
	//��  �ܣ���ʼ��PWM2
	//��  ������
	//����ֵ����

	void PWM2_Init(void)
	{ 
		EA = 0;
		
		#if PWM2_PC7_EN
			SET_PC7_IO_OUT;
			PWM2_IO_SET(1);//0��PD1 ��ѡ�� PWM2_A ���ܣ�1��PC7 ��ѡ�� PWM2_A1 ����
		#else 
			SET_PD1_IO_OUT;
			PWM2_IO_SET(0);//0��PD1 ��ѡ�� PWM2_A ���ܣ�1��PC7 ��ѡ�� PWM2_A1 ����
		#endif	
		
		PWM_EN |= 0x04; //ͨ��ʹ��
		
		PWM2_L_L = 0x00;
		PWM2_L_H = 0x00;
		PWM2_H_L = 0x00;
		PWM2_H_H = 0x00;

		EA = 1;
	}
	
	
	#pragma message "����?vvoid PWM2_Set(bit pwm2_switch,ulong pwm2_fre,ulong pwm2_duty)����"
	//��������void PWM2_Set(bit pwm2_switch,ulong pwm2_fre,ulong pwm2_duty)
	//��  �ܣ�PWM2����
	//������ڣ�TPWM1/2_data = (PWM1/2_H + PWM1/2_L)* T_CLK_24MHz(us)��
	//���ռ�ձȣ�DPWM1/2_data = PWM1/2_H/(PWM1/2_L + PWM1/2_H)��
	//��  ����bit pwm2_switch:PWM2����ģ�鿪�ؿ��ƣ�0Ϊ�أ�1Ϊ����ulong pwm2_freƵ��(Hz);ulong pwm2_duty:PWM�ߵ�ƽ���� (0 <= pwm2_duty <= pwm2_h_l);
	//����ֵ����
	//[pwm1_fre,pwm1_duty]-[4000-6000]-[4K,100%];[pwm1_fre,pwm1_duty]-[2000-12000]-[2K,100%];
	void PWM2_Set(bit pwm2_switch,ulong pwm2_fre,uchar per)
	{	
		uint xdata pwm2_h = 0X00;
		uint xdata pwm2_l = 0X00;	
		ulong xdata pwm2_h_l = ((24.0*1000000*1.0) / (pwm2_fre*1.0));
		if(pwm2_switch == 1)
		{
			#if (PWM2_PD1_EN)
				TRISD &= ~0x02;
			#else
				TRISC &= ~0x80;
			#endif
			PWM_EN |= 0x04;
			if(per>=100)
			{
				pwm2_h = (uint)pwm2_h_l;
				pwm2_l = 0;
			}
			else if(per==0)
			{
				pwm2_h =0;
				pwm2_l =(uint)pwm2_h_l;
			}
			else
			{
				pwm2_h=pwm2_h_l*per/100;
				pwm2_l=pwm2_h_l - (ulong)pwm2_h;
			}
				
			PWM2_L_L = (uchar)(pwm2_l);
			PWM2_L_H = (uchar)(pwm2_l >> 8);
			PWM2_H_L = (uchar)(pwm2_h);
			PWM2_H_H = (uchar)(pwm2_h >> 8);
		}
		else
		{
				PWM2_L_L = 0x00;
				PWM2_L_H = 0x00;
				PWM2_H_L = 0x00;
				PWM2_H_H = 0x00;
				PWM_EN &= ~0x04;
				#if (PWM2_PD1_EN)
					TRISD |= 0x02;
				#else
					TRISC |= 0x80;
				#endif
		}
		#if	(PWM_REG_dataBuf_en)
			b_pwm_buf1_l=PWM2_L_L;
			b_pwm_buf1_h=PWM2_L_H;			
			b_pwm_buf2_l=PWM2_H_L;
			b_pwm_buf2_h=PWM2_H_H;
		#endif
	}  
	#endif



#if	(PWM_REG_dataBuf_en)	
#if	(PWM0_EN)
	void PWM0_get_config(void)
	{
	#if	(PWM0_CH0_EN)
		PWM0_CH0_CNT_L=b_pwm_buf1_l;
		PWM0_CH0_CNT_H=b_pwm_buf1_h;
	#elif	(PWM0_CH1_EN)	
		PWM0_CH1_CNT_L=b_pwm_buf1_l;
		PWM0_CH1_CNT_H=b_pwm_buf1_h;
	#elif	(PWM0_CH2_EN)	
		PWM0_CH2_CNT_L=b_pwm_buf1_l;
		PWM0_CH2_CNT_H=b_pwm_buf1_h;	
	#elif	(PWM0_CH3_EN)	
		PWM0_CH3_CNT_L=b_pwm_buf1_l;
		PWM0_CH3_CNT_H=b_pwm_buf1_h;
	#endif	
		PWM0_MOD_L=b_pwm_buf2_l;
		PWM0_MOD_H=b_pwm_buf2_h;
	
	}
#endif


#if	(PWM1_EN)
	void PWM1_get_config(void)
	{
		PWM1_L_L=b_pwm_buf1_l;
		PWM1_L_H=b_pwm_buf1_h;
		PWM1_H_L=b_pwm_buf2_l;
		PWM1_H_H=b_pwm_buf2_h;	
	}
#endif


#if	(PWM2_EN)
	void PWM2_get_config(void)
	{
		PWM2_L_L=b_pwm_buf1_l;
		PWM2_L_H=b_pwm_buf1_h;
		PWM2_H_L=b_pwm_buf2_l;
		PWM2_H_H=b_pwm_buf2_h;	
	}
#endif
#endif
	