#include "Config.h"
#include 	".\Application_Library\Global.h"

#if Timer0_EN
uchar TH0_Reload = 0;
uchar TL0_Reload = 0;

#ifdef SNS_NUM
	#if SNS_NUM
	unsigned int 	xdata ctk_soft_reset_count = 0;
	uint xdata ctk_soft_reset_max_count = 30000;
	#endif
	void Reset_Cnt_Add(void);
#endif

#ifdef IICS_EN
	#if IICS_EN
	uint xdata sclen_soft_reset_count = 0;
	uint xdata sclen_soft_reset_max_count = 0;
	void Set_SCLEN(void);
	#endif
#endif




#endif 

#if Timer1_EN
	uchar TH1_Reload = 0;
	uchar TL1_Reload = 0;
#endif


//-----------------------------------------------------------------//
//�������ƣ� void Timer0_Init(uint Timer0Us)
//�������ܣ� ��ʱ��0��ʼ��
//��������� uint Timer0Us:��ʱTimer0Us usʱ�䣬Timer0Usȡֵ��Χ1~10000 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer0_EN

	#pragma message "���룬void Timer0_Init(uint Timer0Us)����"
	void Timer0_Init(uint Timer0Us)
	{
		EA = 0;//�����жϣ�
	
		T0_IP_CLR;//����ʵ��Ӧ���������ȼ�
		T0_INT_FLAG_CLR;//���Timer0�жϱ�־

		T0_MODE_SET(1); //Timer0��ʱģʽѡ��0��13bit��ʱ��1��16bit��ʱ��2��8bit���ض�ʱ��3������8λ��ʱ�Ĵ��� tiemr0_clk=(1/12)*sys_clk
		
		TH0 = (65536 - ((uint)((Timer0Us*1.0)*((SYS_12M*1.0)/12.0))))>>8;//SYSCLK=12MHz
		TL0 = (65536 - ((uint)((Timer0Us*1.0)*((SYS_12M*1.0)/12.0))));//SYSCLK=12MHz
	
		
		TH0_Reload = TH0;
		TL0_Reload = TL0;
		
		#ifdef SNS_NUM
			#if SNS_NUM
				ctk_soft_reset_max_count = (500000 / Timer0Us);//���㶨ʱ500ms�Ĵ���
			#endif
		#endif
		
		#ifdef IICS_EN
			#if IICS_EN
				sclen_soft_reset_max_count = (500000 / Timer0Us);//���㶨ʱ500ms�Ĵ���
			#endif
		#endif
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
				Idle_Time_Count =  (1000 / Timer0Us);//���㶨ʱ1ms�Ĵ���
			#endif
		#endif
		
		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
					#if ADC_MODE
					ADC_Rest_Max_Count = (100000 / Timer0Us);//���㶨ʱ100ms�Ĵ���
					#endif
			#endif
		#endif
		
		T0_IE_SET;//ʹ��Timer0�ж� 
		T0_RUN;//����Timer0
		EA = 1;//�����ж�	  
	}
//-----------------------------------------------------------------//
//�������ƣ� void Timer0_ISR() interrupt 1
//�������ܣ� ��ʱ��0�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer0_ISR() interrupt 1
{
	TH0 = TH0+TH0_Reload;   
	TL0 = TL0+TL0_Reload;
	T0_INT_FLAG_CLR;//���Timer0�жϱ�־

	#ifdef SNS_NUM
		#if SNS_NUM
			Reset_Cnt_Add();
			if(keys_flag != 0)
			{
				long_key_clear_count++;	
			}
			else
			{
				long_key_clear_count = 0;
			}
			
			#ifdef IDLE_MODE
				#if IDLE_MODE
					if(keys_flag == 0)
					{
						
						if(Idle_Flag == 0)
						{
							Idle_Time_Count1++;
							if(Idle_Time_Count1 >= Idle_Time_Count)
							{
								Idle_Time_Count1 = 0;
								Idle_Wait_Count++;
								if(Idle_Wait_Count > (Step_In_Idle_Time-50))
								{
										parallel_mode = 1;
										
								}
								if(Idle_Wait_Count > Step_In_Idle_Time)
								{
									
									Idle_Wait_Count = 0;
									
									Idle_Flag = 1;
																													
								}
							}
						}
						else
						{
								
						}
					}
					else
					{
							Idle_Flag = 0;
							Idle_Time_Count1 = 0;
							Idle_Wait_Count = 0;
					}
				
				#endif
			#endif
		#endif
	#endif
		
	#ifdef IICS_EN
		#if IICS_EN
			Set_SCLEN();
		#endif
	#endif
	
	#ifdef ADC_IS_OPEN
		#if ADC_IS_OPEN
			#if ADC_MODE
				ADC_Reset_Count();
			#endif
		#endif
	#endif
	
	
	
	#ifdef VolDet_EN
		#if(VolDet_EN == 1)
		if(Low_Volotage_Flag == 1)
		{
			if(Low_Volotage_Flag_Count < 10000)
			{
				Low_Volotage_Flag_Count++;
				if(Low_Volotage_Flag_Count > 10)//����ʵ����Ŀ����ȷ�ϴ���
				{
					Low_Volotage_Flag = 0;
					Low_Volotage_Flag_Count = 0;
					Low_Volotage_Flag_Confirm = 1;//VolDet_COUNT*(timer0��ʱ)
				}
			}	
		}
		if(Low_Volotage_Flag_Confirm == 1)
		{
			Low_Volotage_Flag_Confirm_count++;
			if(Low_Volotage_Flag_Confirm_count >= 30000)//����ʱ����ʱΪ1ms��30000��Ӧ30s�������㣬Low_Volotage_Flag_Confirm��0������ʵ����Ŀ����
			{
				Low_Volotage_Flag_Confirm_count = 0;
				Low_Volotage_Flag_Confirm = 0;
				low_power = 0;
			}
		}
		#endif
		
		#if	(EEPROM_EN&&EEPROM_LVD_WORK)
	/*
		��Щ��Ʒ�ϵ�Ƚ������ڶ��������ܻ����͵�ѹ�жϵ�
		��ѹ������дһ�Σ�����ѹ֮���ֲ���������ʱ���ϵ�һС
		��ʱ�����������͵�ѹ�ж�д����
	*/
		if(b_eeprom_layer==2)
			{
				if(++b_eeprom_waitTime>=c_eeprom_eraseWaitTime)
				{
					b_eeprom_waitTime=0;
					EA=0;
					eeprom_erase_deal();
					EA=1;				
				}
			}
		if(!gf_eeprom_powerStatus)
		{
			b_eeprom_waitTime=0;
		}
		#endif
		
		
	#endif
}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void Timer1_Init(uint Timer1Us)
//�������ܣ� ��ʱ��1��ʼ��
//��������� uint Timer1Us:��ʱTimer1Us usʱ�䣬Timer1Usȡֵ��Χ1~10000 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if ((Timer1_EN == 1))
#pragma message "���룬void Timer1_Init(uint Timer1Us)����"
void Timer1_Init(uint Timer1Us)
{
	EA = 0;//�����жϣ�
	T1_IP_SET;//����ʵ��Ӧ���������ȼ�
	T1_INT_FLAG_CLR;//���Timer1�жϱ�־
	
	T1_MODE_SET(2); //����Ϊ8λ��������tiemr1_clk=(1/12)*sys_clk
	
	TH1 = 256 -(Timer1Us>>SYSCLK_SEL);   
	TL1 = 256 -(Timer1Us>>SYSCLK_SEL);
	

	T1_IE_SET;//��Timer1�ж�ʹ�� 
	T1_RUN;//����Timer1
	EA = 1;//�����ж�	  
}
//-----------------------------------------------------------------//
//�������ƣ� void Timer1_ISR() interrupt 3
//�������ܣ� ��ʱ��1�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer1_ISR() interrupt 3
{	
	T1_INT_FLAG_CLR;//���Timer1�жϱ�־
	if(++gb_1ms>=c_time_1ms)	
	{	
		gb_1ms=0;	
		gb_20ms++;	
	}
	
	#if   buz_en
        buz_ring();
	#endif


	led_scan();

	#if   kkg_en
		if(gf_check)
		{
        	kkg_work_api();
		}
	#endif

#if	c_codingSwitch_en	//��ת���뿪��
	codingSwitch_distinguish(1);
	codingSwitch_distinguish2(1);
#endif
			
} 

#endif



//-----------------------------------------------------------------//
//�������ƣ� void Timer2_Init(unsigned int Timer2Ms)
//�������ܣ� ��ʱ��2��ʼ��
//��������� unsigned int Timer2Ms:��ʱTimer2Ms msʱ�䣬Timer2Msȡֵ��Χ1~1999@32.768KHz,1~16@4MHz
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer2_EN

	#pragma message "���룬void Timer2_Init(uint Timer2Ms)����"
	void Timer2_Init(unsigned int Timer2Ms)
	{
		unsigned int data dat;
				
		EA = 0;//�����жϣ�
		
		T2_IP_SET;//����ʵ��Ӧ���������ȼ�
		T2_INT_FLAG_CLR;//���Timer2�жϱ�־
		T2_STOP;//bit0Ϊ0ʱֹͣ��ʱ��bit0Ϊ1ʱ������ʱ
		#if (TIMER2_CLK_SEL == 2)//XTAL 4MHz
			dat = (Timer2Ms * 4000)-1;
		#else//0Ϊ�ڲ�LIRC32K/XTAL 32768Hz
			dat = (Timer2Ms * 32.768)-1;//�ڲ�LIRC32K
		#endif
		
		TIMER2_SET_H = dat/256;
		TIMER2_SET_L = dat%256;
		
		T2_MODE_SET(1);//bit1Ϊ0ʱ�ֶ�����ģʽ��bit[1] Ϊ1ʱ�Զ�����ģʽ  	

		
		#if (TIMER2_CLK_SEL == 0)//0Ϊ�ڲ�LIRC32K
			T2_XTAL_SET(1);//Timer2 �ⲿ���񿪹�,1Ϊ�أ�0Ϊ��
			T2_CLK_SET(0);//Timer2��ʱʱ��ѡ��0���ڲ�LIRC32K��1���ⲿ����
		#else//�ⲿ����32768Hz/4MHz
			TRISD |= 0x0C;
			T2_XTAL_SET(0);//Timer2 �ⲿ����ģ�鿪��,1Ϊ�أ�0Ϊ��	
			T2_CLK_SET(1);//Timer2��ʱʱ��ѡ��0���ڲ�LIRC32K��1���ⲿ����
			#if (TIMER2_CLK_SEL == 1)
				XTAL_CLK_SEL(0);//�ⲿ����ѡ�� 1���ⲿ����4MHz��0���ⲿ����32768Hz
			#elif (TIMER2_CLK_SEL == 2)
				XTAL_CLK_SEL(1);//�ⲿ����ѡ�� 1���ⲿ����4MHz��0���ⲿ����32768Hz
			#else
			
			#endif

		#endif
		
		T2_IE_SET;//����Timer2�ж�ʹ��
		T2_RUN;//����Timer2
		EA = 1;//�����ж�	
	
	}
#endif
//-----------------------------------------------------------------//
//�������ƣ� void Timer2_WDT_ISR() interrupt 14
//�������ܣ� Timer2_WDT_ISR�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer2_WDT_ISR() interrupt 14
{
	if(INT_PE_STAT & 0x02)
	{
			INT_PE_STAT &= ~0x02;IRCON1 &= ~0x80;//������Ź��жϱ�־	
			
	}
	if(INT_PE_STAT & 0x01)
	{
			
			T2_INT_FLAG_CLR;//���Timer2�жϱ�־λ
			
	}

}


//-----------------------------------------------------------------//
//�������ƣ� void Reset_Cnt_Add()
//�������ܣ� CTK/IIC/�ⲿ�жϳ���������ۼӺ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
	#if Timer0_EN
	#ifdef SNS_NUM
		#if SNS_NUM
		void Reset_Cnt_Add()
		{
				ctk_soft_reset_count++;
		
				if(ctk_soft_reset_count >= ctk_soft_reset_max_count)
				{
					ctk_soft_reset_count = 0;
					SOFT_RST = 0x55;
				}
		}
		#endif
	#endif
	#endif

//-----------------------------------------------------------------//
//�������ƣ� void Set_SCLEN(void)
//�������ܣ� �����жϻָ�SCLEN����ʱ��0������Ч�����鶨ʱʱ������Ϊ1Ms
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer0_EN
#ifdef IICS_EN
	#if IICS_EN
	void Set_SCLEN(void)
	{

			if(SCLEN == 0)
			{
				sclen_soft_reset_count++;//SCLENδ�ͷż���
				if(sclen_soft_reset_count >= sclen_soft_reset_max_count)
				{
					SCLEN_SET;
					sclen_soft_reset_count = 0;							
				}					
			}
			else
			{
				sclen_soft_reset_count = 0;	
			}
			
	}
	#endif
#endif
#endif

