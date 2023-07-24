#ifndef __XS16TK06X_API_PWM_H__
#define __XS16TK06X_API_PWM_H__

//PWM0 周期只能有一个值,占空比可以独立调节


//PWM0的CHX映射两个管脚只能选择一个管脚，不可同时选中
#define PWM0_CH0_PB0_EN			0	
#define PWM0_CH0_PB5_EN			0
#define PWM0_CH1_PB1_EN			0	
#define PWM0_CH1_PC0_EN			0	
#define PWM0_CH2_PB2_EN			0	
#define PWM0_CH2_PC3_EN			0	
#define PWM0_CH3_PB3_EN			0	
#define PWM0_CH3_PC5_EN			0

#if	(PWM0_CH0_PB5_EN||PWM0_CH1_PC0_EN||PWM0_CH2_PC3_EN||PWM0_CH3_PC5_EN)
#define PWM0_IO_SEL     		1 //0：PB0/1/2/3 口选择 PWM0_A/B/C/D 功能；1：PB5/PC0/PC3/PC5 口选择 PWM0_A1/B1/C1/D1 功能
#else
#define PWM0_IO_SEL     		0
#endif

#define	PWM0_CH1_CMOD			0	//0:选择自身通道自身比 1:选择通道0占空比
#define	PWM0_CH2_CMOD			0	//0:选择自身通道自身比 1:选择通道0占空比
#define	PWM0_CH3_CMOD			0	//0:选择自身通道自身比 1:选择通道0占空比

#define PWM0_CH0_POLO_SEL 		0//bit[4]-PWM0A_CH0，对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高
#define PWM0_CH1_POLO_SEL 		0//bit[5]-PWM0B_CH1，对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高
#define PWM0_CH2_POLO_SEL 		0//bit[6]-PWM0C_CH2，对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高
#define PWM0_CH3_POLO_SEL 		0//bit[7]-PWM0D_CH3，对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高

#define	PWM0_CH0_EN				(PWM0_CH0_PB0_EN|PWM0_CH0_PB5_EN)
#define	PWM0_CH1_EN				(PWM0_CH1_PB1_EN|PWM0_CH1_PC0_EN)
#define	PWM0_CH2_EN				(PWM0_CH2_PB2_EN|PWM0_CH2_PC3_EN)
#define	PWM0_CH3_EN				(PWM0_CH3_PB3_EN|PWM0_CH3_PC5_EN)

#define	PWM0_EN					(PWM0_CH0_EN|PWM0_CH1_EN|PWM0_CH2_EN|PWM0_CH3_EN)


#define PWM1_PD0_EN				0	
#define PWM1_PC6_EN				0
#define	PWM1_EN					(PWM1_PD0_EN|PWM1_PC6_EN)


#define PWM2_PD1_EN				0	
#define PWM2_PC7_EN				0
#define	PWM2_EN					(PWM2_PD1_EN|PWM2_PC7_EN)

#define	PWM_REG_dataBuf_en	0		//缓存pwm周期频率的控制参数 0=缓存 1=不缓存


#define PWM0_IO_SET(x)     {REG_ADDR=0x28;REG_DATA&=(~0x01);REG_DATA|=(0x01&(x<<0));}//0：设置PB0/1/2/3 口选择 PWM0_A/B/C/D 功能；1：设置PB5/PC0/PC3/PC5 口选择 PWM0_A1/B1/C1/D1 功能
#define PWM1_IO_SET(x)     {REG_ADDR=0x28;REG_DATA&=(~0x02);REG_DATA|=(0x02&(x<<1));}//0：设置PD0 口选择 PWM1_A 功能；1：设置 PC6 口选择 PWM1_A1 功能
#define PWM2_IO_SET(x)     {REG_ADDR=0x28;REG_DATA&=(~0x04);REG_DATA|=(0x04&(x<<2));}//0：PD1 口选择 PWM2_A 功能；1：PC7 口选择 PWM2_A1 功能



#if (PWM0_EN == 1)
	extern 	void PWM0_Init(void);

#if (PWM0_CH3_EN)
	extern void PWM0D_Set(ulong pwm0a_fre,uchar per);
#endif

#if (PWM0_CH2_EN)
	extern void PWM0C_Set(ulong pwm0a_fre,uchar per);
#endif

#if (PWM0_CH1_EN)
	extern void PWM0B_Set(ulong pwm0a_fre,uchar per);
#endif

#if (PWM0_CH0_EN)
	extern void PWM0A_Set(ulong pwm0a_fre,uchar per);
#endif

#endif



#if (PWM1_EN == 1)
	extern void PWM1_Init(void);
	extern void PWM1_Set(bit pwm1_switch,ulong pwm1_fre,uchar per);
#endif

#if (PWM2_EN == 1)
	extern void PWM2_Init(void);
	extern void PWM2_Set(bit pwm2_switch,ulong pwm2_fre,uchar per);
#endif



#if	(PWM_REG_dataBuf_en)
	extern	uchar	xdata	b_pwm_buf1_l;
	extern	uchar	xdata	b_pwm_buf1_h;
	extern	uchar	xdata	b_pwm_buf2_l;
	extern	uchar	xdata	b_pwm_buf2_h;
	
	#if	(PWM0_EN)
extern	void PWM0_get_config(void);
#endif

#if	(PWM1_EN)
extern	void PWM1_get_config(void);
#endif

#if	(PWM2_EN)
extern	void PWM2_get_config(void);
#endif
#endif



#endif