#ifndef __XS16TK06X_ADC_H__
#define __XS16TK06X_ADC_H__

/******************************************ADC��������************************************/
#define	ADC_FILTER_EN		0		//1:ÿ��ȡ����ֵȻ��ȡ���м�ֵ��Ϊ��Чֵ 0:������ȡ
/*********ADC�����ر� OPEN-CLOSE********/
#define ADC_00 CLOSE
#define ADC_01 CLOSE
#define ADC_02 CLOSE
#define ADC_03 CLOSE
#define ADC_04 CLOSE
#define ADC_05 CLOSE
#define ADC_06 CLOSE
#define ADC_07 CLOSE

#define ADC_08 CLOSE
#define ADC_09 CLOSE
#define ADC_10 OPEN
#define ADC_11 CLOSE
#define ADC_12 CLOSE
#define ADC_13 CLOSE
#define ADC_14 CLOSE
#define ADC_15 CLOSE

#define ADC_16 CLOSE
#define ADC_17 CLOSE
#define ADC_18 CLOSE
#define ADC_19 CLOSE
#define ADC_20 CLOSE
#define ADC_21 CLOSE
#define ADC_22 CLOSE
#define ADC_23 CLOSE

#define ADC_24 CLOSE
#define ADC_25 CLOSE
#define ADC_IN CLOSE


#define	ADC_MODE	 1	//ADC��ȡ����ģʽ	1:��ѯģʽ��0:�ж�ģʽ
#define ADC_SAMPT	 255//ADC����ʱ������ѡ��,bit[7:0],(0~255)����ʱ��Ϊ(ADC_SPT+1)*4*ADC_CLK
#define ADC_WNUM	 8	//������Ͼ���ת��ʱ��ѡ��2~31��(x+3)*ADC_CLK
#define ADC_SAMBG	 1	//����ʱ����Ƚ�ʱ����ѡ��0Ϊ���0��1Ϊ���1(ADC_CLK)
#define ADC_SAMDEL	 3	//������ʱѡ��0Ϊ���0(ADC_CLK)��1Ϊ2(ADC_CLK)��2Ϊ4(ADC_CLK)��3Ϊ8(ADC_CLK)
#define ADC_FILTER	 0	//�����ź��˲�ѡ��0Ϊ����RC�˲���1Ϊ��RC�˲�
#define ADC26_VIN	 1	//ADC26�ڲ������ѹѡ��0:Ϊ1.362V,1Ϊ2.253V��2Ϊ3.111V,3Ϊ4.082V,ʹ����Ҫ��ȡADCУ׼ֵ,Vin = (ADC_Data/ADC30_Data)*V_ADC30,����V_ADC30��Ҫ��оƬ��У׼��ѹֵ
#define ADC_OFFSETI	 3	//ADCƫ�õ�����Сѡ��ADC_OFFSETI[1��0]��ADC_OFFSETI[0]�Ƚ���ƫ�õ�����С:0Ϊ1uA��1Ϊ2uA��ADC_OFFSETI[1]�˷�ƫ�õ�����С:0Ϊ1uA��1Ϊ2uA��
#define ADC_CTRL	 0	//ADC�Ƚ���ʧ������ѡ��0Ϊ�Ȳ�����ʧ��������1Ϊ���п���һ��Ͽ�,Ĭ��Ϊ1

#define ADC_DCLK	 2	//ADC��Ƶѡ��					bit[1:0],(0~3)-(3MHz,2MHz,1.5MHz,1MHz)
#define ADC_VREF	 0	//�ο�Դ��ѹѡ��0��VCC;1:ADC_VREF
#define ADC_VREF_VOL 1	//�ο���ѹѡ��ADC_VREF��0��2V;1:4V

/******************************************ADC��������************************************/


#define ADC_IE_SET IEN1 |= 0x10																	//��ADC�ж�ʹ��
#define ADC_IE_CLR IEN1 &= ~0x10																//��ADC�ж�ʹ��
#define ADC_IP_SET IPL1 |= 0x10																	//����ADC�ж����ȼ�Ϊ��
#define ADC_IP_CLR IPL1 &= ~0x10																//����ADC�ж����ȼ�Ϊ��
#define ADC_INT_FLAG_CLR IRCON1 &= ~0x10												// ���ADC�жϱ�־λ


#define ADC_IO_CGF(x)	 		{ADC_IO_SEL1 = (uchar)(x);ADC_IO_SEL2 = (uchar)(x>>8);ADC_IO_SEL3 = (uchar)(x>>16);ADC_IO_SEL4 = (uchar)(x>>24);}	//��Ӧ��λΪ1ѡ��ΪADC����																		
#define ADC_IO_CGF_CLR(x)	 	{ADC_IO_SEL1 &= ~((uchar)(x));ADC_IO_SEL2 &= ~((uchar)(x>>8));ADC_IO_SEL3 &= ~((uchar)(x>>16));ADC_IO_SEL4 &= ~((uchar)(x>>24));}	//��Ӧ��λΪ0��ѡ��ADC����																		

#define ADC_SAMP_SET(x) 	ADC_SPT = x																					//ADC����ʱ������ѡ��     bit[7:0]��(0~255)����ʱ��Ϊ(ADC_SPT+1)*4*ADC_CLK
#define ADC_WNUM_SET(x) 	{ADC_CFG1 &= ~(0xF8);ADC_CFG1 |= (0xF8&(x<<3));}		//������Ͼ���ת��ʱ��ѡ��2~31��bit[7:3],(x+3)*ADC_CLK 

#define ADC_SAMPDEL_SET(x){ADC_CFG1 &= ~(0x03);ADC_CFG1 |= (0x03&(x<<0));}		//������ʱѡ��0Ϊ���0(ADC_CLK)��1Ϊ2(ADC_CLK)��2Ϊ4(ADC_CLK)��3Ϊ8(ADC_CLK)
#define ADC_FILTER_SET(x) {ADC_CFG2 &= ~(0x40);ADC_CFG2 |= (0x40&(x<<6));}		//�����ź��˲�ѡ��0Ϊ�����˲���1Ϊ��10k�����˲�

#define ADC26_VIN_SET(x)  {ADC_CFG2 &= ~(0x30);ADC_CFG2 |= (0x30&(x<<4));}		//ADC26�ڲ������ѹѡ��0:Ϊ1.362V,1Ϊ2.253V��2Ϊ3.111V,3Ϊ4.082V,ʹ����Ҫ��ȡADCУ׼ֵ

#define ADC_I_SET(x) 			{ADC_CFG2 &= ~(0x0C);ADC_CFG2 |= (0x0C&(x<<2));}		//ADCƫ�õ�����Сѡ��ADC_CFG2[3;2]��ADC_CFG2[2]�Ƚ���ƫ�õ�����С:0Ϊ1uA��1Ϊ2uA��ADC_CFG2[3]�˷�ƫ�õ�����С:0Ϊ1uA��1Ϊ2uA��
#define ADC_CTRL_SET(x)   {ADC_CFG2 &= ~(0x02);ADC_CFG2 |= (0x02&(x<<1));}		//ADC�Ƚ���ʧ������ѡ��ADC�Ƚ���ʧ������ѡ��0Ϊ�Ȳ�����ʧ��������1Ϊ���п���һ��Ͽ�,Ĭ��Ϊ1


#define ADC_DCLK_SET(x) 	{ADCCKC &= ~(0x03);ADCCKC |= (0x03&(x<<0));}				//ADC��Ƶѡ��				bit[1:0],(0~3)-(3MHz,2MHz,1.5MHz,1MHz)
#define ADC_PD(x) 			{PD_ANA &= ~(0x01);PD_ANA |= (0x01&(x<<0));}					//ADCģ�鿪��0Ϊ������1Ϊ�ر�
#define ADC_SAMPBG_SET(x) {ADC_CFG1 &= ~(0x04);ADC_CFG1 |= (0x04&(x<<2));}		//����ʱ����Ƚ�ʱ����ѡ��0Ϊ���0��1Ϊ���1(ADC_CLK)

#define ADC_VREF_SET(x)   	{REG_ADDR = 0x2D;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}	//�ο�Դ��ѹѡ��0��VCC;1:ADC_RREF
#define ADC_VREF_VOL_SEL(x)  {REG_ADDR = 0x2D;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}	////�ο���ѹѡ��0��2V;1:4V
#define ADC_ADDR_SET(x)	 {ADC_SCAN_CFG &= ~(0x3E);ADC_SCAN_CFG |= (0x3E&(x<<1));}//ADCͨ����ַѡ��			bit[5:1],(0~26)-(ADC0~ADC26) 
#define ADC_SCAN_EN	 	 	 {ADC_SCAN_CFG &= ~0x01;ADC_SCAN_CFG |= 0x01;}					//ADCģ�鿪���ӵ�0��1
#define ADC_SCAN_CLR	 	  ADC_SCAN_CFG &= ~0x01																	//ADCɨ��رգ�bit[0],0Ϊ�رգ�Ӳ������ 

#define ADC_IS_OPEN ((ADC_00 == TRUE) || (ADC_01 == TRUE) || (ADC_02 == TRUE) || (ADC_03 == TRUE) || (ADC_04 == TRUE)  || (ADC_05 == TRUE) || (ADC_06 == TRUE) || \
										 (ADC_07 == TRUE) || (ADC_08 == TRUE) || (ADC_09 == TRUE) || (ADC_10 == TRUE) || (ADC_11 == TRUE)  || (ADC_12 == TRUE) || (ADC_13 == TRUE) || \
										 (ADC_14 == TRUE) || (ADC_15 == TRUE) || (ADC_16 == TRUE) || (ADC_17 == TRUE) || (ADC_18 == TRUE)  || (ADC_19 == TRUE) || (ADC_20 == TRUE) || \
										 (ADC_21 == TRUE) || (ADC_22 == TRUE) || (ADC_23 == TRUE) || (ADC_24 == TRUE) || (ADC_25 == TRUE)  || (ADC_IN == TRUE))

#define OPENADC (((ulong)ADC_00)<<0	|((ulong)ADC_01)<<1	|((ulong)ADC_02)<<2	|((ulong)ADC_03)<<3	|((ulong)ADC_04)<<4	|\
								 ((ulong)ADC_05)<<5 |((ulong)ADC_06)<<6 |((ulong)ADC_07)<<7 |((ulong)ADC_08)<<8 |((ulong)ADC_09)<<9 |\
								 ((ulong)ADC_10)<<10|((ulong)ADC_11)<<11|((ulong)ADC_12)<<12|((ulong)ADC_13)<<13|((ulong)ADC_14)<<14|\
								 ((ulong)ADC_15)<<15|((ulong)ADC_16)<<16|((ulong)ADC_17)<<17|((ulong)ADC_18)<<18|((ulong)ADC_19)<<19|\
								 ((ulong)ADC_20)<<20|((ulong)ADC_21)<<21|((ulong)ADC_22)<<22|((ulong)ADC_23)<<23|((ulong)ADC_24)<<24|((ulong)ADC_25)<<25|((ulong)ADC_IN)<<26)
				 
#define OPENADC_NUM (ADC_00 + ADC_01 + ADC_02 + ADC_03 + ADC_04 + ADC_05 + ADC_06 + ADC_07 + ADC_08 + ADC_09 + ADC_10 \
									 + ADC_11 + ADC_12 + ADC_13 + ADC_14 + ADC_15 + ADC_16 + ADC_17 + ADC_18 + ADC_19 + ADC_20 + ADC_21 \
									 + ADC_22 + ADC_23 + ADC_24 + ADC_25 + ADC_IN )  

#if ADC_IS_OPEN
	extern void ADC_Init(void);

	#if (ADC_MODE == 1)	
	extern uchar ADC_Obtain(uchar adc_ch);
	#endif
	
	#if	(ADC_IN)
	extern	uint Get_VOL(uchar adc_ch_num);
	#endif
	
#endif

#if ADC_IS_OPEN
	#if ADC_MODE
	extern bit ADC_Start_Flag;
	extern uint  ADC_Rest_Max_Count;
	extern uint  ADC_Start_Count;
	extern void  ADC_Reset_Count(void);
	extern void ADC_Delay_us(unsigned int us);
	#endif
#endif

#endif