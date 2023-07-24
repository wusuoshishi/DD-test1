#include "Config.h"


#if IDLE_MODE
	uint Idle_Cnt = 0;
	bit Idle_Flag = 0;
	uint Idle_Wait_Count = 0;
	uint xdata Idle_Time_Count = 0;
	uint xdata Idle_Time_Count1 = 0;
	uint xdata Step_In_Idle_Time = 0;
	uint xdata Idle_Wake_Up_Time = 0;
	
	unsigned int  xdata raw_data_parallel[1] =  {0};
	unsigned int  xdata base_line_parallel[1] = {0};	
	unsigned char xdata Cnt_Par[4] = 0;
#endif

#if IDLE_MODE

	#pragma message "���룬Idle������غ���"

	//-----------------------------------------------------------------//
	//�������ƣ� Idle_IORecovrey()
	//�������ܣ� ���Ѻ󣬽�ʹ�õ�Ӧ�õ�IO�����ó���Ҫ��״̬
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void Idle_IORecovrey()
	{
	//����Ӧ�û�ԭIO��״̬
	}
	//-----------------------------------------------------------------//
	//�������ƣ� void Idle_Delay_Us(uint us)
	//�������ܣ� ��ʱΪ��us
	//��������� us
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void Idle_Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
	{
		for (; us > 0; us--)
		{	
			WDT_CTRL = 0x07;
		}		
	}

	//-----------------------------------------------------------------//
	//�������ƣ� Idle_IO_Init()
	//�������ܣ� Idleģʽ��ʼ��IO,���齫δ�õ���IO������Ϊ���Ϊ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void Idle_IO_Init()
	{

	}

	//-----------------------------------------------------------------//
	//�������ƣ� void Idle_Wake_Up_Init(uint _Step_In_Idle_Time,uint _Idle_Wake_Up_Time)
	//�������ܣ� Idleģʽ��ʼ������
	//��������� uint _Step_In_Idle_TimeΪ�����ް�������_Step_In_Idle_Time��������˯��ģʽ(����>=5000),��ֵ�������һ��keysFlagSN��λ��ʱ��
	//			 			uint _Idle_Wake_Up_Time,WDT����ʱ��0~7
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void Idle_Wake_Up_Init(uint _Step_In_Idle_Time,uint _Idle_Wake_Up_Time)
	{
		Idle_IO_Init();
		Step_In_Idle_Time = _Step_In_Idle_Time;//����Time0��Timer0�жϺ�����ʹ�á�
		Idle_Wake_Up_Time = _Idle_Wake_Up_Time;

	}
	//-----------------------------------------------------------------//
	//�������ƣ� void Idle()
	//�������ܣ� ����Idleģʽ����������ʵ��Ӧ����������жϵĿ��ؼ�IO���ã�
	//��������ָ���������˯�ߵ�ʱ���Լ�Ϊ����ʱɨ�谴����ʱ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void Idle()
	{
		long differ_para = 0;
		if(Idle_Flag == 1)
		{
			#if SNS_NUM
			if(ctk_para_done == 1)//�ж�ɨ����һ��
			{
					
						CTK_IE_CLR;//��CTK�ж�
						differ_para = ((long)base_line_parallel[0] - (long)raw_data_parallel[0]);
					
						if(differ_para >= 0)
						{
							if(differ_para >= FTH_PARA)
							{
								

									Cnt_Par[0]++;
									if(Cnt_Par[0] >= 0)
									{
											
											Cnt_Par[0]= 0; 
										
											Idle_Flag = 0;
											parallel_mode = 0;
											
										
											differ_para = 0;
											Idle_Time_Count1 = 0;
											Idle_Wait_Count = 0;
												
									}
									Cnt_Par[1] = 0;
									Cnt_Par[2] = 0;
									Cnt_Par[3] = 0;
									
							}
							else if(differ_para >= FTH_PARA/5)
							{
									Cnt_Par[1]++;
									if(Cnt_Par[1] >= PAR_PnoiseRenMaxCnt)
									{
											Cnt_Par[1]= 0; 
											base_line_parallel[0] -= 5;
									}
									Cnt_Par[0] = 0;
									Cnt_Par[2] = 0;
									Cnt_Par[3] = 0;
								
								
							}
							
							else if(differ_para >= 0)
							{
									Cnt_Par[2]++;
									if(Cnt_Par[2] >= PAR_PnoiseRenMaxCnt)
									{
											Cnt_Par[2]= 0; 
											base_line_parallel[0]--;
									}
									Cnt_Par[0] = 0;
									Cnt_Par[1] = 0;
									Cnt_Par[3] = 0;
									
							}
						}
						else
						{

								Cnt_Par[3]++;
								if(Cnt_Par[3] >= PAR_NnoiseRenMaxCnt)
								{
										Cnt_Par[3]= 0; 
										base_line_parallel[0] = raw_data_parallel[0];
								}
								Cnt_Par[0] = 0;
								Cnt_Par[1] = 0;
								Cnt_Par[2] = 0;
						}
					
						
						CTK_IE_SET;//��CTK�ж�
					
					
					#if (TRACEMODE == 0)
						if(Idle_Flag == 1)
						{

							Idle_IO_Init();

							CTK_STOP;
							CTK_IE_CLR;//��CTK�ж�
							CTK_PD_SET(1);//0ΪCTK����1ΪCTK��
			
							Idle_Delay_Us(100);//ִ��PCON = 0x01ǰ��ʱ>=100us
							
							WDT_CTRL = Idle_Wake_Up_Time;//���ÿ��Ź����ʱ��
							PCON = 0x01;//����ʡ��ģʽ�ȴ�����,�ڽ���ʡ��ģʽ֮ǰ������ʵ��Ӧ��������ر�/����ģ�鼰�жϣ����Ѻ����ʵ��Ӧ��������ָ�ģ��
							
							
							BOR_ON;//�����縴λ����
							CTK_PD_SET(0);//0ΪCTK����1ΪCTK��
							CTK_IE_SET;//��CTK�ж�
							CTK_START;
					
						
							Idle_IORecovrey();

						}
					#endif	
					
					ctk_para_done = 0;
			}
			
				#if TRACEMODE
			
							raw_data[25] = raw_data_parallel[0];
							base_line[25] = base_line_parallel[0];//�鿴����ģʽ����ʱ��raw_data[25]��Ӧ��SNS�ر�
						
				#endif
			#endif
			
		}//IDLE
		else
		{
				#if TRACEMODE
		
						raw_data[25] = raw_data_parallel[0];
						base_line[25] = base_line_parallel[0];//�鿴����ģʽ����ʱ��raw_data[25]��Ӧ��SNS�ر�
					
				#endif
		}
	}	
#endif	
		