#include "Config.h"
#if (CS_SW == 1)
	#include "DataDeal.h"
#endif


#if SNS_NUM

unsigned char code 	SNS[26]	={SCAN_00,SCAN_01,SCAN_02,SCAN_03,SCAN_04,SCAN_05,SCAN_06,SCAN_07,SCAN_08,SCAN_09,SCAN_10,SCAN_11,SCAN_12,SCAN_13,SCAN_14,SCAN_15,SCAN_16,SCAN_17,SCAN_18,SCAN_19,SCAN_20,SCAN_21,SCAN_22,SCAN_23,SCAN_24,SCAN_25};
unsigned int 	code  FTH[26]	={FTH00,FTH01,FTH02,FTH03,FTH04,FTH05,FTH06,FTH07,FTH08,FTH09,FTH10,FTH11,FTH12,FTH13,FTH14,FTH15,FTH16,FTH17,FTH18,FTH19,FTH20,FTH21,FTH22,FTH23,FTH24,FTH25};
unsigned int 	code 	PUIV[26]={PUIV00,PUIV01,PUIV02,PUIV03,PUIV04,PUIV05,PUIV06,PUIV07,PUIV08,PUIV09,PUIV10,PUIV11,PUIV12,PUIV13,PUIV14,PUIV15,PUIV16,PUIV17,PUIV18,PUIV19,PUIV20,PUIV21,PUIV22,PUIV23,PUIV24,PUIV25};

unsigned char xdata pull_i_step[SNS_NUM] 	= {7};
unsigned int 	xdata pull_i_value[SNS_NUM] = {300};
unsigned char xdata sensor_open[SNS_NUM] 	= {0};
unsigned char xdata sns_next_count = 0;



//-----------------------------------------------------------------//
//�������ƣ� void CTK_Set_Para(void)
//�������ܣ� ����CTKɨ����������߸��²���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void CTK_Set_Para(void)
{

		unsigned char i = 0;
		for (i = 0; i < SNS_NUM; i++)
		{
			open_sns |= ((ulong)0x01)<<SNS[i];
			sensor_open[i] = SNS[i];
			pull_i_value[i] = PUIV[i];
			//��ʼ������Դ����
			raw_data[i] = 0;
			n_base_line[i] = base_line[i] = 0x0001;
			
		}
	
}

uchar Sns_Count = 0;
unsigned char xdata i;
unsigned char xdata touch_confirm_count[SNS_NUM] = {0};
unsigned char xdata touch_left_count[SNS_NUM] = {0};

unsigned char xdata over_p_noise_count[SNS_NUM] = {0};
unsigned char xdata under_p_noise_count[SNS_NUM] = {0};
unsigned char xdata over_n_noise_count[SNS_NUM] =  {0};
unsigned char xdata under_n_noise_count[SNS_NUM] = {0};
unsigned char xdata under_nn_noise_count[SNS_NUM] = {0};
unsigned char xdata n_base_line_reno_count[SNS_NUM] = {0};

#if UN_NORMAL_CHECK
		unsigned char xdata un_normal_count = 0;
		unsigned char xdata un_normal_recover_count = 0;
		bit un_normal_flag = 0;
		unsigned long xdata adjust_flag = 0;


//-----------------------------------------------------------------//
//�������ƣ� void Rawdata_Un_Normal(uchar sns_num)
//�������ܣ� Rawdata�쳣�жϣ�ע������ʶ�������쳣������˹��ܸ���ʵ����Ŀ�����ӡ�
//��������� uchar sns_num��ͨ������
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Rawdata_Un_Normal(uchar sns_num)
{
	if(un_normal_flag == 0)
	{
			if(raw_data[sns_num] >= (((unsigned long)(((unsigned long)0x0001)<<(((SNS_SCAN_CFG3>>4)&0x07) + 9)))*8/10))	
			{
					
					un_normal_count++;
					if(un_normal_count >= UN_NORMAL_MAX_COUNT)
					{
							un_normal_count = 0;
							if(un_normal_recover_count < UN_NORMAL_RECOVER_MAX_COUNT)//�����쳣�жϻָ�un_normal_recover_max_count��
							{

									EA = 0;											//�����ж�
									adjust_done_flag = 0;
									un_normal_recover_count++;
									CTK_IE_SET;
									CTK_ADDR_SET(sensor_open[0]);
									CTK_START;
									EA = 1;											//�����ж�

							}
					}
			}
		
	}	

}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void CTK_Init(void)
//�������ܣ� CTK��ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//

void CTK_Init(void)
{
	EA = 0;											//�����ж�
	//����CTKɨ����������߸��²���
	CTK_Set_Para();
	
	CTK_IE_SET;
	CTK_IP_CLR;
	
	TRISB |= ((open_sns >> 0)  & 0xFF);
	TRISC |= ((open_sns >> 8)  & 0xFF);
	TRISD |= ((open_sns >> 16) & 0xFF);
	TRISA |= ((open_sns >> 24) & 0x03);

	SNS_IO_SEL1 |= ((open_sns)&0xFF);
	SNS_IO_SEL2 |= ((open_sns>>8)&0xFF);
	SNS_IO_SEL3 |= ((open_sns>>16)&0xFF);
	SNS_IO_SEL4 |= ((open_sns>>24)&0x03);//SNS��IOѡ��
	
	CTK_PRS_SW_SET(0);					//ǰ�˳�ŵ翪��,1Ϊ�أ�0Ϊ��
	CTK_RESO_SET(CTK_RESO);   	//0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ��
	CTK_PRS_SET(CTK_PRS); 			//PRS(��ŵ�Ƶ��) = 48/2/(x+4),62:��̬�ֲ�(1~1.5~3)MHz,63:���ȷֲ�(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz
	CTK_DS_SET(CTK_DS); 				//����ٶ�0:24MHz,1:12MHz,2:6MHz,3:4MHz
	CTK_PAR_SET(Mode); 					//0Ϊ��ͨ��ģʽ��1Ϊ��ͨ������ģʽ
	CTK_RB_SET(CTK_RB);					//ѡ��RB�����С4:60K 5:80K ��������
	CTK_VTH_SET(CTK_REF);				//�ο���ѹ(0:1.5V),(1:2.1V),(2:2.5V),(3:2.9V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);ע��VCC-VTH>0.5V
	CTK_PULL_I_SET(pull_i_value[0]);//���õ���Դ����
	CTK_PRE_CH_SET(1);					//Ԥ���ʱ�䣺0Ϊ20us,1Ϊ40us
	CTK_PRE_DISCH_SET(1);				//Ԥ�ŵ�ʱ�䣺0Ϊ2us,1Ϊ10us

	CTK_PD_SET(0);							//0ΪCTK����1ΪCTK��
	CTK_STOP;										//ֹͣɨ��

	CTK_ADDR_SET(sensor_open[0]);
	
	CTK_START;
	EA = 1;											//�����ж�
	
}
#endif
//-----------------------------------------------------------------//
//�������ƣ� void XS16TK06X_Set_Touch_Flag(void)
//�������ܣ� �����жϲ���λ�������������־λ
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void XS16TK06X_Set_Touch_Flag(void)
{
	#if SNS_NUM	
		#ifdef IDLE_MODE
			#if (IDLE_MODE == 1)
			if(parallel_mode == 0)
			{
				if(ctk_circle_done == 1)//�ж�ģʽ
				{
					ctk_circle_done = 0;
					CTK_IE_CLR;//��CTK�ж�
				
					for(Sns_Count = 0; Sns_Count < SNS_NUM; Sns_Count++)
					{
						if(SNS[Sns_Count] != 255)
						{
							
							CTK_SNS_Renovate(Sns_Count,((ulong)FTH[Sns_Count]*((ulong)CFG_Rb*1000/CTK_RB_ADJ))/1000);
							
							#if TRACEMODE
							
								if(keys_flag & ((long)0x01 << SNS[Sns_Count]))
								{
									keys_flag_Tracemode |= ((long)0x01 << Sns_Count);
								}
								else
								{
									keys_flag_Tracemode &= ~((long)0x01 << Sns_Count);
								}
							
							#endif
							
							#if UN_NORMAL_CHECK
								Rawdata_Un_Normal(Sns_Count);
							#endif
						}
						
					}
					CTK_IE_SET;//��CTK�ж�
				}
			}
			else
			{
					Idle();	
			}
			#else
					if(ctk_circle_done == 1)//�ж�ģʽ
					{
						ctk_circle_done = 0;
						CTK_IE_CLR;//��CTK�ж�

						for(Sns_Count = 0; Sns_Count < SNS_NUM; Sns_Count++)
						{
							if(SNS[Sns_Count] != 255)
							{
								
								CTK_SNS_Renovate(Sns_Count,((ulong)FTH[Sns_Count]*((ulong)CFG_Rb*1000/CTK_RB_ADJ))/1000);
							
								#if TRACEMODE
									if(keys_flag & ((long)0x01 << SNS[Sns_Count]))
									{
										keys_flag_Tracemode |= ((long)0x01 << Sns_Count);
									}
									else
									{
										keys_flag_Tracemode &= ~((long)0x01 << Sns_Count);
									}
								#endif
								
								#if UN_NORMAL_CHECK
									Rawdata_Un_Normal(Sns_Count);
								#endif
							}
							
						}
						CTK_IE_SET;//��CTK�ж�
					}
			#endif
		#endif
		
		#ifndef IDLE_MODE
		if(ctk_circle_done == 1)//�ж�ģʽ
		{
			ctk_circle_done = 0;
			CTK_IE_CLR;//��CTK�ж�

			for(Sns_Count = 0; Sns_Count < SNS_NUM; Sns_Count++)
			{
				if(SNS[Sns_Count] != 255)
				{
					
					CTK_SNS_Renovate(Sns_Count,((ulong)FTH[Sns_Count]*((ulong)CFG_Rb*1000/CTK_RB_ADJ))/1000);
				
					#if TRACEMODE
						if(keys_flag & ((long)0x01 << SNS[Sns_Count]))
						{
							keys_flag_Tracemode |= ((long)0x01 << Sns_Count);
						}
						else
						{
							keys_flag_Tracemode &= ~((long)0x01 << Sns_Count);
						}
					#endif
					
					#if UN_NORMAL_CHECK
						Rawdata_Un_Normal(Sns_Count);
					#endif
				}
				
			}
			CTK_IE_SET;//��CTK�ж�
		}
		#endif
	#endif
	
	#ifdef SLEEP_MODE
		#if (SLEEP_MODE == 1)
			Sleep();
		#endif
	#endif	
}	

//////////TK////////////

#if CH_MAX
unsigned int  xdata raw_data[CH_MAX] ={0};
unsigned int  xdata base_line[CH_MAX] = {1};
#endif

#if SNS_NUM
	unsigned char xdata Mode = 0;
	unsigned char sns_next = 0;
	static unsigned char xdata adjust_count = 0;

	#if (CS_SW == 1)
		uint cs_noise = 0;
	#endif

	bit adjust_done_flag = 0;
	bit base_line_int_flag = 0;
	bit ctk_circle_done = 0;
	

	unsigned int xdata pull_i_value_parallel = 100;
	unsigned long xdata open_sns = 0;
	unsigned long xdata open_sns_tem = 0;
	bit parallel_mode = 0;
	bit parallel_init_flag = 1;
	bit ctk_para_done = 0;
	

	unsigned int  xdata n_base_line[SNS_NUM] = {1};

	unsigned long xdata muli_key_flag = 0;
	unsigned long xdata keys_flag = 0;	
	unsigned long xdata mode_flag = 0;
		
	unsigned int  xdata long_key_clear_count = 0;		

	unsigned char xdata multi_key_count = 0;
	unsigned char xdata multi_key_reset_cnt = 0;

	#if (RENOVATE_MODE == 1)
	bit water_flow_flag = 0;	
	unsigned int 	xdata water_flow_left_count = 0;	
	unsigned char xdata water_flow_key_count = 0;	
	unsigned char xdata water_flow_key_reset_cnt = 0;
	#endif
	
	void CTK_XS16TK06X_Adjust_Int(void);
	void CTK_XS16TK06X_Para_Adjust_Int(void);
	void Base_Line_Init();
	void Set_Next_SNS(void);
	
	#ifdef IDLE_MODE
		#if IDLE_MODE
		
		//-----------------------------------------------------------------//
		//�������ƣ� void Set_Para_SNS(void)
		//�������ܣ� ���ò���ģʽͨ��
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//	
		void Set_Para_SNS(void)
		{
				CTK_PAR_SET(1); 					//0Ϊ��ͨ��ģʽ��1Ϊ��ͨ������ģʽ
				CTK_PULL_I_SET(pull_i_value_parallel);//���ü���
				CTK_RESO_SET(CTK_PARA_RESO); 
				CTK_PRS_SET(CTK_PARA_PRS);
				CTK_RB_SET(CTK_PARA_RB);	
				CTK_VTH_SET(CTK_PARA_REF);	
				CTK_ADDR_SET(sensor_open[0]);
				CTK_START;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� void CTK_XS16TK06X_Para_Adjust_Int(void)
		//�������ܣ�����ģʽͨ������Դ����Ӧ
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//        

		void CTK_XS16TK06X_Para_Adjust_Int(void)
		{
			if(adjust_count < 3)
			{
				while(1)
				{
					WDT_CTRL = 7;
					
					if((raw_data_parallel[0] >= ADJUST_PARA_LINE))
					{
						if(pull_i_value_parallel < (511 - ADJUST_STE))
						{
							pull_i_value_parallel += (1 + ADJUST_STE);
							
							
							Set_Para_SNS();
							return;
						}	
						else
						{
							parallel_init_flag = 1;
							base_line_parallel[0] = raw_data_parallel[0];						
							Set_Next_SNS();
							return;
						}
					}
					else
					{	
							if(adjust_count < 3)
							{
								adjust_count++;
							}

							if(pull_i_value_parallel > (0))
							{
								pull_i_value_parallel-= (1);
								
								Set_Para_SNS();
								
								return;
							}
							else
							{
									Set_Para_SNS();
									return;
							}	
					}
				}
			}
			
			if(adjust_count >= 3)
			{
				while(1)
				{
					WDT_CTRL = 7;
					
					if((raw_data_parallel[0] <= ADJUST_PARA_LINE))
					{
						if(pull_i_value_parallel > (0))
						{
							pull_i_value_parallel -= (1);
						
							Set_Para_SNS();
							return;
						}	
						else
						{
							parallel_init_flag = 1;
							base_line_parallel[0] = raw_data_parallel[0];
							Set_Next_SNS();
							return;
						}
					}
					else
					{	
							if(adjust_count < 6)
							{
								adjust_count++;
							}
							if(adjust_count >= 6)
							{
								adjust_count = 0;
								parallel_init_flag = 1;
								base_line_parallel[0] = raw_data_parallel[0];						
								Set_Next_SNS();
								return;
							}

							if(pull_i_value_parallel < (511 - ADJUST_STE))
							{
								pull_i_value_parallel += (1 + ADJUST_STE);

								Set_Para_SNS();
								return;
							}
							else
							{
									Set_Para_SNS();
									return;
							}	
					}
				}
			}
		}
		#endif
	#endif
	//-----------------------------------------------------------------//
	//�������ƣ� void Set_Next_SNS(void)
	//�������ܣ� ������һ��ͨ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//	
	void Set_Next_SNS(void)
	{

		CTK_PULL_I_SET(pull_i_value[sns_next]);//���õ���Դ����
		CTK_ADDR_SET(sensor_open[sns_next]);
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
				CTK_PAR_SET(0); 					//0Ϊ��ͨ��ģʽ��1Ϊ��ͨ������ģʽ
				CTK_RESO_SET(CTK_RESO); 
				CTK_PRS_SET(CTK_PRS); 
				CTK_VTH_SET(CTK_REF);	
				CTK_RB_SET(CTK_RB);	
			#endif
		#endif

		CTK_START;
	}
	
	//-----------------------------------------------------------------//
	//�������ƣ� void CTK_ISR() interrupt 12
	//�������ܣ� CTK�жϷ�����
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//	
	void CTK_ISR() interrupt 12
	{
		
			CTK_INT_FLAG_CLR;//���CTK�жϱ�־λ

			CTK_STOP;	
		
			#ifdef Timer0_EN
				#if Timer0_EN
					ctk_soft_reset_count = 0;
				#endif
			#endif
		
			if(parallel_mode == 0)
			{
					#if (CS_SW == 1)
					if(adjust_done_flag == 0)
					#endif
					{							
							EA = 0;
							raw_data[sns_next] = ((unsigned int)CSD_RAWDATAH << 8) | (unsigned int)CSD_RAWDATAL;//��ȡCTK����
							EA = 1;							
					}
					
					if(adjust_done_flag == 0)
					{
						#ifdef IDLE_MODE
							#if IDLE_MODE
								parallel_init_flag = 0;
							#endif
						#endif
						CTK_XS16TK06X_Adjust_Int();
						
					}
					else
					{
							if(parallel_init_flag == 1)
							{

								#if (CS_SW == 1)	
									cs_noise = Data_Deal(CS_F_NUM,0,SNS_NUM); 
									Set_Next_SNS();
								#else
								
								
								sns_next++;
								while(sensor_open[sns_next] == 0xFF)
								{
										CTK_STOP;	
										sns_next++;
										if(sns_next >= SNS_NUM)
										{
												sns_next = 0;
												ctk_circle_done = 1;
												break;
										}
								}
								if(sns_next >= SNS_NUM)
								{
										sns_next = 0;
										
										ctk_circle_done = 1;
								}
								
								Set_Next_SNS();
								#endif
							}
							#ifdef IDLE_MODE
								#if IDLE_MODE
								else
								{
											EA = 0;
											raw_data_parallel[0] = ((unsigned int)CSD_RAWDATAH << 8) | (unsigned int)CSD_RAWDATAL;//��ȡCTK����
											EA = 1;
											
											CTK_XS16TK06X_Para_Adjust_Int();
								}
								#endif
							#endif
					}
			}
			#ifdef IDLE_MODE
				#if IDLE_MODE
				else
				{
						EA = 0;
						raw_data_parallel[0] = ((unsigned int)CSD_RAWDATAH << 8) | (unsigned int)CSD_RAWDATAL;//��ȡCTK����
						EA = 1;
					
						ctk_para_done = 1;
						Set_Para_SNS();
						
				}
				#endif
			#endif
	}

	//-----------------------------------------------------------------//
	//�������ƣ� void Base_Line_Init()
	//�������ܣ� ���߳�ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void Base_Line_Init()
	{   
			unsigned char xdata i;
			for (i = 0; i < SNS_NUM; i++) 
			{
				#if KEYS_RENOVATE_FLAG
				if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[i]))
				{
					EA = 0;
					base_line[i] = raw_data[i];
					EA = 1;
				}
				#endif
			}	
	}



	//-----------------------------------------------------------------//
	//�������ƣ� void CTK_Long_TK_Count(void)
	//�������ܣ� ����������
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void CTK_Long_TK_Count(void)
	{
				#if LONG_KEY_COUNT
				if(long_key_clear_count >= LONG_KEY_COUNT)
				{
						long_key_clear_count = 0;
						keys_flag = 0;
						Base_Line_Init();
				}
				#endif
	}


	//-----------------------------------------------------------------//
	//�������ƣ� void CTK_TK_Left_Count(uchar addr)
	//�������ܣ� ��ָ�뿪�жϼ���
	//��������� addr��ͨ����
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void CTK_TK_Left_Count(uchar addr)
	{
			touch_left_count[addr]++;
			touch_confirm_count[addr] = 0;
			if(touch_left_count[addr] >= TK_LEFT_COUNT)
			{
				touch_left_count[addr] = 0;
				keys_flag &= ~(((unsigned long)0x01) << sensor_open[addr]);
			}
	}

	//-----------------------------------------------------------------//
	//�������ƣ� void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
	//�������ܣ� SNS���߸���
	//��������� unsigned char addr��SNSͨ��;unsigned int fth:��ָ��ֵ
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
	{
		long differ = 0;
		
		#if (RENOVATE_MODE == 1)
			long differ_mode1 = 0;
		#endif
		#if (MULTI_KEY_MAX_COUNT != 0)
		unsigned char i = 0;
		#endif
		long fth_tem = 0;
		fth_tem = fth;
		
		differ = (long)base_line[addr] - (long)raw_data[addr];

		
		#if (CS_SW == 1)
			if(cs_noise >= CS_NOISE)
			{
				fth_tem = (CS_FTH_RATE*fth_tem)/10;
			}
			if((keys_flag & ((ulong)0x01 << sensor_open[addr])))
			{
				fth_tem = (FTHD_HY_RATE*fth_tem)/10;
			}

		#endif
			
		
		
		if((keys_flag & ((ulong)0x01 << sensor_open[addr])))
		{
			fth_tem = (TK_RATE_HY*fth_tem)/10;
		}
			
		if(adjust_done_flag == 1)
		{
			if(base_line_int_flag == 0)
			{
				base_line_int_flag = 1;
			
				Base_Line_Init();
				
			}
		}
		
		CTK_Long_TK_Count();
		
		#if TK_EOT
			if(differ >= 0)
			{
				if(differ >= (fth_tem*TK_EOT))
				{
						touch_left_count[addr] = 0;
						touch_confirm_count[addr] = 0;
						keys_flag &= ~(((unsigned long)0x01) << sensor_open[addr]);
						Base_Line_Init();
				}
			}
		#endif
		
		#if (MULTI_KEY_MAX_COUNT != 0)
		if(differ >= 0)
		{
			if(differ >= (((int)fth)*RENOVATE_NTH_RATE/10))//�ఴ����־�ж�
			{
					muli_key_flag |= ((long)0x01 << sensor_open[addr]);	
			}
			else
			{
					muli_key_flag &= ~((long)0x01 << sensor_open[addr]);	
			}
		}
		else
		{
				muli_key_flag &= ~((long)0x01 << sensor_open[addr]);	
		}
		
		multi_key_count = 0;
		for(i = 0; i < SNS_NUM;i++)//ģʽ1�ఴ���ж�
		{
			if((muli_key_flag & (((unsigned long)0x01) << sensor_open[i])))
			{
				multi_key_count++;//ģʽ1�ఴ������
			}
		}

		if(multi_key_count > MULTI_KEY_MAX_COUNT)
		{
				multi_key_count = 0;
				multi_key_reset_cnt++;
				if(multi_key_reset_cnt >= MULTI_KEY_RST_COUNT)
				{
					multi_key_reset_cnt = 0;
					
					keys_flag= 0;
					Base_Line_Init();
				
				}
		}
		else
		{
				multi_key_reset_cnt = 0;
		}
		#endif
			#if (RENOVATE_MODE == 1)	
			differ_mode1 = (long)n_base_line[addr] - (long)base_line[addr];
			if(differ_mode1 >= 0)//ģʽ1differ�ж�
			{
				if(differ_mode1 >= (((int)fth)*WATER_FLOW_RATE/10))//ģʽ1��־�ж�
				{
						mode_flag |= ((long)0x01 << sensor_open[addr]);	
						n_base_line_reno_count[addr] = 0;
				}
				else
				{
						n_base_line_reno_count[addr]++;
						if(n_base_line_reno_count[addr] >= N_BASE_LINE_RENO_MAX_COUNT)
						{
								n_base_line[addr] -= differ_mode1/10;
								n_base_line_reno_count[addr] = 0;
								if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									mode_flag &= ~((long)0x01 << sensor_open[addr]);
								}								
						}
				}
			}
			else
			{
					if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
					{
						
						n_base_line[addr] -= differ_mode1/10;
						
					}
					mode_flag &= ~((long)0x01 << sensor_open[addr]);	
			}
			
	
			water_flow_key_count = 0;
			for(i = 0; i < SNS_NUM;i++)//ģʽ1�ఴ���ж�
			{
				if((mode_flag & (((unsigned long)0x01) << sensor_open[i])))
				{
					water_flow_key_count++;//ģʽ1��ˮ����
				}
				
			}
			
		
			if(water_flow_key_count > WATER_FLOW_MAX_COUNT)//ģʽ1��ˮ�ж�
			{
					
					water_flow_key_count = 0;
					water_flow_key_reset_cnt++;		
					if(water_flow_key_reset_cnt >= WATER_FLOW_RST_COUNT)
					{
						water_flow_key_reset_cnt = 0;
						water_flow_left_count = 0;
						if(water_flow_flag == 0)
						{
							keys_flag= 0;
							Base_Line_Init();	
							water_flow_flag = 1;
							
						}
					}
					
			}
			else
			{
				if(water_flow_flag == 1)//ģʽ1��ˮ��־�жϼ������
				{
						water_flow_left_count++;
						if(water_flow_left_count >= WATER_FLOW_LEFT_MAX_COUNT)
						{
							water_flow_flag = 0;
							water_flow_left_count = 0;
						}
				}
				else
				{
					water_flow_left_count = 0;
				}
			}
		#endif

		if(differ > 0)//differ����0���
		{

			#if (RENOVATE_MODE == 1)
			//ģʽ1
			if(water_flow_flag == 1)
			{
				if((mode_flag & (((unsigned long)0x01) << sensor_open[addr])))
				{
						fth_tem = (fth_tem*RENOVATE_MODE1_FTH_RATE/10);//ģʽ1��ָ��ֵ	
				}
			}
			#endif
			
			if(differ >= (fth_tem*RENOVATE_FTH_RATE/10))
			{
					//�д������������߸���
					touch_confirm_count[addr]++;
					touch_left_count[addr] = 0;
					if(touch_confirm_count[addr] >= TK_COMFIRM_COUNT)
					{
							keys_flag |= (((unsigned long)0x01) << sensor_open[addr]);
							touch_confirm_count[addr] = 0;
					}
					else
					{
						
					}
					
			}
			else if(differ >= (((int)fth)*RENOVATE_NTH_RATE/10))//>=p_noise���߸���
			{
					#if (RENOVATE_MODE == 0)//ģʽ0���߸���
							
							CTK_TK_Left_Count(addr);
				
							over_p_noise_count[addr]++;
							
							under_p_noise_count[addr] = 0;
							over_n_noise_count[addr] = 0;
							under_n_noise_count[addr] = 0;
							under_nn_noise_count[addr] = 0;
				
							if(over_p_noise_count[addr] >= OVER_P_NOISE_MAX_COUNT)
							{
								over_p_noise_count[addr] = 0;
								#if KEYS_RENOVATE_FLAG
								if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									
									#if	(c_xs_cs)
										base_line[addr] -= c_xs_baseLindChangNum;
									#else
										base_line[addr] -= differ/5;
									#endif
									
								}
								#endif
							}
					
					#endif				
					
			}
			else//differ<=p_noise���߸���
			{
					#if (RENOVATE_MODE == 0)//ģʽ0���߸���
							CTK_TK_Left_Count(addr);
							
							over_p_noise_count[addr] = 0;
							under_p_noise_count[addr]++;
							over_n_noise_count[addr] = 0;
							under_n_noise_count[addr] = 0;
							under_nn_noise_count[addr] = 0;
							if(under_p_noise_count[addr] >= UNDER_P_NOISE_MAX_COUNT)
							{
								under_p_noise_count[addr] = 0;
								#if KEYS_RENOVATE_FLAG
								if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									#if	(c_xs_cs)
										base_line[addr] -= c_xs_baseLindChangNum;
									#else
										base_line[addr] = raw_data[addr];
									#endif
								}
								#endif
							}
					
					#endif
					#if (RENOVATE_MODE == 1)
					//ģʽ1���߸���
							CTK_TK_Left_Count(addr);
							over_p_noise_count[addr] = 0;
							under_p_noise_count[addr]++;
							over_n_noise_count[addr] = 0;
							under_n_noise_count[addr] = 0;
							under_nn_noise_count[addr] = 0;
							if(under_p_noise_count[addr] >= UNDER_P_NOISE_MAX_COUNT)
							{
								under_p_noise_count[addr] = 0;
								if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
								{								
									base_line[addr] = raw_data[addr];							
								}
							}
					
					#endif
			}
		}
		else//differ<0�����
		{
			CTK_TK_Left_Count(addr);
			if(differ >= (-(((int)fth)*RENOVATE_NTH_RATE/10)))//>= n_poise���
			{
					#if (RENOVATE_MODE == 0)//ģʽ0���߸���
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr]++;
						under_n_noise_count[addr] = 0;
						under_nn_noise_count[addr] = 0;
						if(over_n_noise_count[addr] >= OVER_N_NOISE_MAX_COUNT)
						{
							over_n_noise_count[addr] = 0;
							#if KEYS_RENOVATE_FLAG
							if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
							{
							
								#if	(c_xs_cs)
									base_line[addr] += c_xs_baseLindChangNum;
								#else
									base_line[addr] = raw_data[addr];
								#endif	
							
							}
							#endif
						}
				
					#endif
						
					#if (RENOVATE_MODE == 1)
					//ģʽ1���߸���
					
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr]++;
						under_n_noise_count[addr] = 0;
						under_nn_noise_count[addr] = 0;
						if(over_n_noise_count[addr] >= OVER_N_NOISE_MAX_COUNT)
						{
							over_n_noise_count[addr] = 0;
							#if KEYS_RENOVATE_FLAG
							if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
							{
							
								base_line[addr] = raw_data[addr];
							
							}
							#endif
						}
					
					#endif
			}
			else if((differ >= -(UNDER_N*((int)fth)*RENOVATE_FTH_RATE/10)))
			{
					#if (RENOVATE_MODE == 0)//ģʽ0���߸���
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr]++;
						under_nn_noise_count[addr] = 0;
				
						if(under_n_noise_count[addr] >= UNDER_N_NOISE_MAX_COUNT)
						{
							under_n_noise_count[addr] = 0;
							#if KEYS_RENOVATE_FLAG
							if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
							{
								#if	(c_xs_cs)
										base_line[addr] += c_xs_baseLindChangNum;
								#else
										base_line[addr] -= differ/2;	
								#endif						
							}
							#endif					
							
						}
				#endif
					
				#if (RENOVATE_MODE == 1)//ģʽ1���߸���
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr]++;
						under_nn_noise_count[addr] = 0;
				
						if(under_n_noise_count[addr] >= UNDER_N_NOISE_MAX_COUNT)
						{
							under_n_noise_count[addr] = 0;
							#if KEYS_RENOVATE_FLAG
							if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
							{
									base_line[addr] -= differ/2;				
							}
							#endif					
							
						}
				#endif
			}
			else
			{
					#if (RENOVATE_MODE == 0)//ģʽ0���߸���
					over_p_noise_count[addr] = 0;
					under_p_noise_count[addr] = 0;
					over_n_noise_count[addr] = 0;
			    under_n_noise_count[addr] = 0;
					under_nn_noise_count[addr]++;			
					if(under_nn_noise_count[addr] >= UNDER_NN_NOISE_MAX_COUNT)
					{
						under_nn_noise_count[addr] = 0;
						
						#if KEYS_RENOVATE_FLAG
						if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
						{
							#if	(c_xs_cs)
								base_line[addr] += c_xs_baseLindChangNum;
							#else
								base_line[addr] -= differ/5;	
							#endif							
						}
						#endif
					}	
					#endif
					
					#if (RENOVATE_MODE == 1)//ģʽ1���߸���
					over_p_noise_count[addr] = 0;
					under_p_noise_count[addr] = 0;
					over_n_noise_count[addr] = 0;
			    under_n_noise_count[addr] = 0;
					under_nn_noise_count[addr]++;			
					if(under_nn_noise_count[addr] >= UNDER_NN_NOISE_MAX_COUNT)
					{
						under_nn_noise_count[addr] = 0;
						
						#if KEYS_RENOVATE_FLAG
							if(KEYS_RENOVATE_FLAG &(((unsigned long)0x01)<<sensor_open[addr]))
							{
								base_line[addr] -= differ/5;					
							}
						#endif
					}	
					#endif
			}
		}
	}
	
	//-----------------------------------------------------------------//
	//�������ƣ� void CTK_XS16TK06X_Adjust_Int(void)
	//�������ܣ�ͨ������Դ����Ӧ
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//        

	void CTK_XS16TK06X_Adjust_Int(void)
	{
		if(adjust_count < 3)
		{
			while(1)
			{
				WDT_CTRL = 7;
				
				if((raw_data[sns_next] >= ADJUST_LINE))
				{
					if(pull_i_value[sns_next] < (511 - ADJUST_STE))
					{
						pull_i_value[sns_next] += (1 + ADJUST_STE);
						Set_Next_SNS();
						return;
					}	
					else
					{
						
						sns_next++;
						if(sns_next >= SNS_NUM)
						{
								sns_next = 0;
								adjust_count = 0;
								adjust_done_flag = 1;//����Ӧ���
								
						}
						
						Set_Next_SNS();
						return;
					}
				}
				else
				{	
						n_base_line[sns_next] = base_line[sns_next] = raw_data[sns_next];
						sns_next++;
						if(sns_next >= SNS_NUM)
						{
								if(adjust_count < 3)
								{
									adjust_count++;
								}

								sns_next = 0;
								if(pull_i_value[sns_next] > (0))
								{
									pull_i_value[sns_next] -= (1);
									Set_Next_SNS();
									return;
								}
							
								Set_Next_SNS();
								break;
						}

						if(pull_i_value[sns_next] > (0))
						{
							pull_i_value[sns_next] -= (1);
							Set_Next_SNS();
							return;
						}
						else
						{
								Set_Next_SNS();
								return;
						}	
				}
			}
		}
		
		if(adjust_count >= 3)
		{
			while(1)
			{
				WDT_CTRL = 7;
				
				if((raw_data[sns_next] <= ADJUST_LINE))
				{
					if(pull_i_value[sns_next] > (0))
					{
						pull_i_value[sns_next] -= (1);
						Set_Next_SNS();
						return;
					}	
					else
					{
						sns_next++;
						if(sns_next >= SNS_NUM)
						{
								sns_next = 0;
								adjust_count = 0;
								adjust_done_flag = 1;
								
						}
						
						Set_Next_SNS();
						
						return;
					}
					
				}
				else
				{	
						n_base_line[sns_next] = base_line[sns_next] = raw_data[sns_next];
						sns_next++;
						if(sns_next >= SNS_NUM)
						{
								sns_next = 0;
							
								if(adjust_count < 6)
								{
									adjust_count++;
								}
								if(adjust_count >= 6)
								{
									adjust_count = 0;
									adjust_done_flag = 1;
								}
								Set_Next_SNS();
								break;
						}
	
						if(pull_i_value[sns_next] < (511 - ADJUST_STE))
						{
							pull_i_value[sns_next] += (1 + ADJUST_STE);
							Set_Next_SNS();
							return;
						}
						else
						{
								Set_Next_SNS();
								return;
						}	
				}
			}
		}
	}
	
#endif
//////////TK////////////
