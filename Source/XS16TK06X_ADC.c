#include "Config.h"
#ifdef ADC_IS_OPEN		
#if ADC_IS_OPEN

	#if (ADC_MODE == 1)//ADC��ѯģʽ

		bit ADC_Start_Flag = 0;
		uint  ADC_Rest_Max_Count = 0;
		uint  ADC_Start_Count = 0;	
		
		#if	(ADC_IN==OPEN)
			uint Adc26 = 0;
			uint Adc26_count = 0;
			ulong Adc26_AVG = 0;

			uint Adc_ch = 0;
			uint Adc_ch_count = 0;
			ulong Adc_ch_AVG = 0;
			uint vol = 0;
		#endif
		
		//-----------------------------------------------------------------//
		//�������ƣ� void ADC_Delay_us(unsigned int us)
		//�������ܣ� ��ʱ����
		//��������� uint us��1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms*2
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void ADC_Delay_us(unsigned int us)
		{
			for (; us > 0; us--)
			{	
				WDT_CTRL = 0x07;
			}		
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� void ADC_Reset_Count()
		//�������ܣ� ADC��ʱ�������ۼӺ���
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		#ifdef Timer0_EN
			#if Timer0_EN
				#if ADC_IS_OPEN
					#if ADC_MODE
					void ADC_Reset_Count(void)
					{
						if(ADC_Start_Flag == 1)
						{
							ADC_Start_Count++;
							if(ADC_Start_Count >= ADC_Rest_Max_Count)
							{
								SOFT_RST = 0x55;	
								ADC_Start_Count = 0;
								ADC_Start_Flag = 0;
							}
						}
					}
					#endif
				#endif
			#endif
		#endif		
				
	#endif
#endif
	

	#if ADC_IS_OPEN
	//-----------------------------------------------------------------//
	//�������ƣ� uint Get_ADC(uchar adc_ch)
	//�������ܣ� ��ѯģʽ�»�ȡADC adc_ch�����ݣ�
	//��������� uchar adc_ch:ADCͨ��
	//��������� uint������ADC����
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------// 
	#if (ADC_MODE == 1)		
	// uint Get_ADC(uchar adc_ch)
	// {
	// 	ADC_IE_CLR;//�ر�ADC�ж�ʹ��
	
	//	ADC_IO_CGF((((ulong)(0x01))<< adc_ch));
	
	// 	if(OPENADC & (((ulong)(0x01))<< (adc_ch)))
	// 	{
	// 		ADC_ADDR_SET(adc_ch);
	// 	}
	// 	else
	// 	{
	// 		return 0;
	// 	}
		
	// 	ADC_PD(0);//����ADCģ��
	// 	ADC_Delay_us(20);
	// 	ADC_SCAN_EN;//����ADCɨ��
		
	// 	ADC_Start_Flag = 1;
	// 	while(!(IRCON1&0x10));
	// 	ADC_Start_Count = 0;
	// 	ADC_Start_Flag = 0;
		
	// 	ADC_INT_FLAG_CLR;
	// 	ADC_PD(1);//�ر�ADCģ��
		
	// 	return ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;
	// }

	uchar Get_ADC(uchar adc_ch)
	{
		ADC_IE_CLR;//�ر�ADC�ж�ʹ��
		
		ADC_IO_CGF((((ulong)(0x01))<< adc_ch));
	
		if(OPENADC & (((ulong)(0x01))<< (adc_ch)))
		{
			ADC_ADDR_SET(adc_ch);
		}
		else
		{
			return 0;
		}
		
		ADC_PD(0);//����ADCģ��
		ADC_Delay_us(20);
		ADC_SCAN_EN;//����ADCɨ��
		
		ADC_Start_Flag = 1;
		while(!(IRCON1&0x10));
		ADC_Start_Count = 0;
		ADC_Start_Flag = 0;
		
		ADC_INT_FLAG_CLR;
		ADC_PD(1);//�ر�ADCģ��
		
		return ((ADC_RDATAH<<4)|(ADC_RDATAL>>4));
	}

	#endif	
	//-----------------------------------------------------------------//
	//�������ƣ� void ADC_Init(void)
	//�������ܣ� ADC��ʼ��,��SetAccessIndexes()֮���ʼ��;
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//        
	void ADC_Init(void)
	{
		#if (ADC_MODE == 0)
		uchar i = 0;
		uchar j = 0;
		#endif
		
		EA = 0;//�����жϣ�
		ADC_IP_SET;//����ADC�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
		ADC_INT_FLAG_CLR;//���ADC�жϱ�־λ
		ADC_IO_CGF(OPENADC);//ADC��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����
	
		ADC_SAMP_SET(ADC_SAMPT);//ADC����ʱ������bit[7:0],(0~255)����ʱ��Ϊ(ADC_SPT+1)*4*ADC_CLK
		ADC_WNUM_SET(ADC_WNUM);//������Ͼ���ת��ʱ��ѡ��2~31(x+3)*ADC_CLK
		ADC_SAMPBG_SET(ADC_SAMBG);//����ʱ����Ƚ�ʱ����ѡ��0Ϊ���0��1Ϊ���1(ADC_CLK)
		ADC_SAMPDEL_SET(ADC_SAMDEL);//������ʱѡ��0Ϊ���0(ADC_CLK)��1Ϊ2(ADC_CLK)��2Ϊ4(ADC_CLK)��3Ϊ8(ADC_CLK)
		ADC_FILTER_SET(ADC_FILTER);//�����ź��˲�ѡ��0Ϊ����RC�˲���1Ϊ��RC�˲�
		ADC26_VIN_SET(ADC26_VIN);//ADC26�ڲ������ѹѡ��0:Ϊ1.362V,1Ϊ2.253V��2Ϊ3.111V,3Ϊ4.082V
		ADC_I_SET(ADC_OFFSETI);//ADCƫ�õ�����Сѡ��ADC_OFFSETI[0]�Ƚ���ƫ�õ�����С:0Ϊ1uA��1Ϊ2uA��ADC_OFFSETI[1]�˷�ƫ�õ�����С:0Ϊ1uA��1Ϊ2uA��
		ADC_CTRL_SET(ADC_CTRL);//ADC�Ƚ���ʧ������ѡ��ADC�Ƚ���ʧ������ѡ��0Ϊ�Ȳ�����ʧ��������1Ϊ���п���һ��Ͽ�,Ĭ��Ϊ1
		
		ADC_DCLK_SET(ADC_DCLK);//ADC��Ƶѡ��bit[1:0],(0~3)-(3MHz,2MhHz,1.5MHz,1MHz)
		ADC_VREF_SET(ADC_VREF);//�ο�Դ��ѹѡ��0��VCC;1:ADC_VREF
		ADC_VREF_VOL_SEL(ADC_VREF_VOL);//�ο���ѹѡ��ADC_VREF��0��2V;1:4V


		#if (ADC_MODE == 1)
			ADC_SCAN_CLR;//�ر�ADCɨ��
			ADC_IE_CLR;//�ر�ADC�ж�ʹ��
		#endif
		
		EA = 1;//�����ж�
		 
	}
	

//-----------------------------------------------------------------//
//�������ƣ� uint Get_VOL(uchar adc_ch_num)
//�������ܣ� ��ȡ�ڲ�ADC_IN(ADC26)�ĵ�ѹУ׼ֵ������ADC�����ѹ
//��������� uchar adc_ch_num:ADCͨ��
//��������� uint������ADC�����ѹmV
//�� �� ֵ�� ��
//��ȡ��ѡ��ͨ���ĵ�ѹ����26ͨ����ȡһ���������ĵ�Դ��ѹ���ٸ���
//�˼����ͨ���ĵ�ѹ����׼ȷ��(VCC���ܲ���5V)
//�����Դ��ѹΪV5,26ͨ����ȡadΪad26�����������ѹad��ȡadΪadin
//26ͨ����׼��ѹΪVb������ͨ����ѹΪVin��
//1:ͨ��26ͨ�������V5=Vb*255/ad26
//2:ͨ�������ѹad��Vin=V5*adin/255
//3:��1��V5����2����Vin=Vb*adin/ad26
//-----------------------------------------------------------------// 
#if	(ADC_IN==OPEN)
uint Get_VOL(uchar adc_ch_num)
{
	
	ulong tem = 0;
	uint vol_adc26 = 0;

	Adc26 = ADC_Obtain(26);
	Adc_ch = ADC_Obtain(adc_ch_num);
	Adc26_AVG += Adc26;
	Adc_ch_AVG += Adc_ch;
	Adc26_count++;

	if(Adc26_count >= GET_VOL_AVG_NUM)
	{
		Adc26_count = 0;
		Adc26_AVG /= GET_VOL_AVG_NUM;
		Adc_ch_AVG /= GET_VOL_AVG_NUM;
		tem = (ulong)Adc_ch_AVG*10000;
	#if	(ADC26_VIN==0)	
		vol_adc26 = (((uint)CBYTE[0x4040]) << 8) + CBYTE[0x4041];	//1.362v
	#elif (ADC26_VIN==1)
		vol_adc26 = (((uint)CBYTE[0x4042]) << 8) + CBYTE[0x4043];	//2.253v
	#elif (ADC26_VIN==2)
		vol_adc26 = (((uint)CBYTE[0x4044]) << 8) + CBYTE[0x4045];	//3.111v
	#elif (ADC26_VIN==3)
		vol_adc26 = (((uint)CBYTE[0x4046]) << 8) + CBYTE[0x4047];	//4.082v
	#else
		vol_adc26 = (((uint)CBYTE[0x4040]) << 8) + CBYTE[0x4041];
	#endif	
		vol = ((tem/Adc26_AVG))*vol_adc26/10000;
		
		Adc_ch_AVG = 0;
		Adc26_AVG = 0;
	}
	return vol;
}
#endif


//-----------------------------------------------------------------//
//�������ƣ� uchar ADC_Obtain(uchar adc_ch)
//�������ܣ� ��ȡADת������������򵥴���
//��������� adc_ch:adת��ͨ��
//��������� ������adֵ
//�� �� ֵ�� ��
//-----------------------------------------------------------------//  
#if	ADC_FILTER_EN
	uchar ADC_Obtain(uchar adc_ch)
	{
		uchar	ad_val[3]={0,0,0};
		uchar	i,j;
		
		for(i=0;i<3;i++)
		{
			ad_val[i]=Get_ADC(adc_ch);
		}
		//����С��ֵ�Ƶ����
		for(i=0;i<2;i++)
		{
			if(ad_val[i]<ad_val[i+1])
			{
				j=ad_val[i];
				ad_val[i]=ad_val[i+1];
				ad_val[i+1]=j;
			}
		}
		//ȡ����С��ֵ��Ϊ�м�ֵ
		if(ad_val[0]<ad_val[1])
		{
			i=ad_val[0];
		}
		else
		{
			i=ad_val[1];
		}

		return	i;
			
	}
#else	
	uchar ADC_Obtain(uchar adc_ch)
	{
		uchar	i;
		i=Get_ADC(adc_ch);
		return	i;		
	}		
#endif	


#endif
#endif

