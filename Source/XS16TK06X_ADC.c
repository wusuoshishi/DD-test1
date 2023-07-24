#include "Config.h"
#ifdef ADC_IS_OPEN		
#if ADC_IS_OPEN

	#if (ADC_MODE == 1)//ADC查询模式

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
		//函数名称： void ADC_Delay_us(unsigned int us)
		//函数功能： 延时函数
		//输入参数： uint us：1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms*2
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void ADC_Delay_us(unsigned int us)
		{
			for (; us > 0; us--)
			{	
				WDT_CTRL = 0x07;
			}		
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void ADC_Reset_Count()
		//函数功能： ADC超时计数器累加函数
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
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
	//函数名称： uint Get_ADC(uchar adc_ch)
	//函数功能： 查询模式下获取ADC adc_ch的数据；
	//输入参数： uchar adc_ch:ADC通道
	//输出参数： uint：返回ADC数据
	//返 回 值： 无
	//-----------------------------------------------------------------// 
	#if (ADC_MODE == 1)		
	// uint Get_ADC(uchar adc_ch)
	// {
	// 	ADC_IE_CLR;//关闭ADC中断使能
	
	//	ADC_IO_CGF((((ulong)(0x01))<< adc_ch));
	
	// 	if(OPENADC & (((ulong)(0x01))<< (adc_ch)))
	// 	{
	// 		ADC_ADDR_SET(adc_ch);
	// 	}
	// 	else
	// 	{
	// 		return 0;
	// 	}
		
	// 	ADC_PD(0);//开启ADC模块
	// 	ADC_Delay_us(20);
	// 	ADC_SCAN_EN;//开启ADC扫描
		
	// 	ADC_Start_Flag = 1;
	// 	while(!(IRCON1&0x10));
	// 	ADC_Start_Count = 0;
	// 	ADC_Start_Flag = 0;
		
	// 	ADC_INT_FLAG_CLR;
	// 	ADC_PD(1);//关闭ADC模块
		
	// 	return ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;
	// }

	uchar Get_ADC(uchar adc_ch)
	{
		ADC_IE_CLR;//关闭ADC中断使能
		
		ADC_IO_CGF((((ulong)(0x01))<< adc_ch));
	
		if(OPENADC & (((ulong)(0x01))<< (adc_ch)))
		{
			ADC_ADDR_SET(adc_ch);
		}
		else
		{
			return 0;
		}
		
		ADC_PD(0);//开启ADC模块
		ADC_Delay_us(20);
		ADC_SCAN_EN;//开启ADC扫描
		
		ADC_Start_Flag = 1;
		while(!(IRCON1&0x10));
		ADC_Start_Count = 0;
		ADC_Start_Flag = 0;
		
		ADC_INT_FLAG_CLR;
		ADC_PD(1);//关闭ADC模块
		
		return ((ADC_RDATAH<<4)|(ADC_RDATAL>>4));
	}

	#endif	
	//-----------------------------------------------------------------//
	//函数名称： void ADC_Init(void)
	//函数功能： ADC初始化,在SetAccessIndexes()之后初始化;
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//        
	void ADC_Init(void)
	{
		#if (ADC_MODE == 0)
		uchar i = 0;
		uchar j = 0;
		#endif
		
		EA = 0;//关总中断；
		ADC_IP_SET;//设置ADC中断优级为高，根据实际应运设置优先级
		ADC_INT_FLAG_CLR;//清除ADC中断标志位
		ADC_IO_CGF(OPENADC);//ADC与IO功能选择，对应的位为1为ADC功能，0为IO功能
	
		ADC_SAMP_SET(ADC_SAMPT);//ADC采样时间设置bit[7:0],(0~255)采样时间为(ADC_SPT+1)*4*ADC_CLK
		ADC_WNUM_SET(ADC_WNUM);//采样完毕距离转换时间选择2~31(x+3)*ADC_CLK
		ADC_SAMPBG_SET(ADC_SAMBG);//采样时序与比较时序间隔选择，0为间隔0，1为间隔1(ADC_CLK)
		ADC_SAMPDEL_SET(ADC_SAMDEL);//采样延时选择，0为间隔0(ADC_CLK)，1为2(ADC_CLK)，2为4(ADC_CLK)，3为8(ADC_CLK)
		ADC_FILTER_SET(ADC_FILTER);//输入信号滤波选择，0为不加RC滤波，1为加RC滤波
		ADC26_VIN_SET(ADC26_VIN);//ADC26内部输入电压选择，0:为1.362V,1为2.253V，2为3.111V,3为4.082V
		ADC_I_SET(ADC_OFFSETI);//ADC偏置电流大小选择，ADC_OFFSETI[0]比较器偏置电流大小:0为1uA，1为2uA；ADC_OFFSETI[1]运放偏置电流大小:0为1uA，1为2uA；
		ADC_CTRL_SET(ADC_CTRL);//ADC比较器失调消除选择，ADC比较器失调消除选择，0为先采样再失调消除，1为所有开关一起断开,默认为1
		
		ADC_DCLK_SET(ADC_DCLK);//ADC分频选择，bit[1:0],(0~3)-(3MHz,2MhHz,1.5MHz,1MHz)
		ADC_VREF_SET(ADC_VREF);//参考源电压选择：0：VCC;1:ADC_VREF
		ADC_VREF_VOL_SEL(ADC_VREF_VOL);//参考电压选择ADC_VREF：0：2V;1:4V


		#if (ADC_MODE == 1)
			ADC_SCAN_CLR;//关闭ADC扫描
			ADC_IE_CLR;//关闭ADC中断使能
		#endif
		
		EA = 1;//开总中断
		 
	}
	

//-----------------------------------------------------------------//
//函数名称： uint Get_VOL(uchar adc_ch_num)
//函数功能： 读取内部ADC_IN(ADC26)的电压校准值，计算ADC输入电压
//输入参数： uchar adc_ch_num:ADC通道
//输出参数： uint：返回ADC输入电压mV
//返 回 值： 无
//获取所选择通道的电压，读26通道获取一个到真正的电源电压，再根据
//此计算出通道的电压才是准确的(VCC可能不是5V)
//假设电源电压为V5,26通道读取ad为ad26，测量输入电压ad读取ad为adin
//26通道基准电压为Vb，测量通道电压为Vin，
//1:通过26通道计算出V5=Vb*255/ad26
//2:通过输入电压ad则Vin=V5*adin/255
//3:将1的V5代入2中则Vin=Vb*adin/ad26
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
//函数名称： uchar ADC_Obtain(uchar adc_ch)
//函数功能： 获取AD转换结果，经过简单处理
//输入参数： adc_ch:ad转换通道
//输出参数： 处理后的ad值
//返 回 值： 无
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
		//将最小的值移到最后
		for(i=0;i<2;i++)
		{
			if(ad_val[i]<ad_val[i+1])
			{
				j=ad_val[i];
				ad_val[i]=ad_val[i+1];
				ad_val[i+1]=j;
			}
		}
		//取出较小的值即为中间值
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

