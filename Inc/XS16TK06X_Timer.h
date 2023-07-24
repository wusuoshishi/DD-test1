#ifndef __XS16TK06X_TIMER_H__
#define __XS16TK06X_TIMER_H__


#define	Timer0_EN				1	//Timer0ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	Timer1_EN				1	//Timer1ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	Timer2_EN				0	//Timer2ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���

#define	TIMER2_CLK_SEL	1	//Timer2ѡ��ʱ��Դѡ�����ã�		0Ϊ�ڲ�LIRC32K,1Ϊ�ⲿ����32768Hz,2Ϊ�ⲿ����4MHz

#define T0_IE_SET  IEN0 |= 0x02//��Timer0�ж�ʹ�� 
#define T0_IE_CLR  IEN0 &= ~0x02//��Timer0�ж�ʹ��
#define T0_IP_SET  IPL0 |= 0x02//����Timer0�ж��ż�Ϊ��
#define T0_IP_CLR  IPL0 &= ~0X02//����Timer0�ж��ż�Ϊ��

#define T0_MODE_SET(x) {TMOD &= ~(0x03);TMOD |= (0x03&(x<<0));}//Timer0��ʱģʽѡ��0��13bit��ʱ��1��16bit��ʱ��2��8bit���ض�ʱ��3������8λ��ʱ�Ĵ��� tiemr0_clk=(1/12)*sys_clk
#define T0_INT_FLAG_CLR TCON  &= ~0X20//���Timer0�жϱ�־
#define T0_RUN TCON |= 0X10// 1Ϊ����Timer0
#define T0_STOP TCON &= ~0X10//0ΪֹͣTimer0

#define T1_IE_SET  IEN0 |= 0x08//��Timer1�ж�ʹ�� 
#define T1_IE_CLR IEN0 &= ~0x08//��Timer1�ж�ʹ��
#define T1_IP_SET  IPL0  |= 0x08//����Timer1�ж��ż�Ϊ��
#define T1_IP_CLR  IPL0 &= ~0X08//����Timer1�ж��ż�Ϊ��

#define T1_MODE_SET(x) {TMOD &= ~(0x30);TMOD |= (0x30&(x<<4));}//Timer1��ʱģʽѡ��0��13bit��ʱ��1��16bit��ʱ��2��8bit���ض�ʱ��3������8λ��ʱ�Ĵ��� tiemr1_clk=(1/12)*sys_clk
#define T1_INT_FLAG_CLR TCON  &= ~0X80//���Timer1�жϱ�־
#define T1_RUN TCON |= 0X40//1Ϊ���� Timer1
#define T1_STOP TCON &= ~0X40//0ΪֹͣTimer1

#define T2_MODE 0x02
#define T2_SART 0x02
#define T2_CLK  0x04 
#define T2_XTAL_SET(x) {PD_ANA &= ~(0x04);PD_ANA |= (0x04&(x<<2));}//Timer2 �ⲿ����ģ�鿪��,1Ϊ�أ�0Ϊ����Ĭ�Ϲر�
#define T2_CLK_SET(x) {TIMER2_CFG &= ~(0x04);TIMER2_CFG |= (0x04&(x<<2));}//Timer2��ʱʱ��ѡ��0���ڲ�RC32KHz��1���ⲿ����
#define XTAL_CLK_SEL(x) {REG_ADDR=0x20;REG_DATA &= ~(0x01);REG_DATA|=(0x01&(x<<0));}//�ⲿ����ѡ�� 1���ⲿ4MHz��0���ⲿ32768Hz	
#define T2_IE_SET IEN1 |= 0x80//��Timer2�ж�ʹ�� 
#define T2_IE_CLR IEN1 &= ~0x80//��Timer2�ж�ʹ��
#define T2_IP_SET IPL1  |= 0x80//����Timer2�ж��ż�Ϊ��
#define T2_IP_CLR IPL1 &= ~0X80//����Timer2�ж��ż�Ϊ��
#define T2_MODE_SET(x) {TIMER2_CFG &= ~(0x02);TIMER2_CFG |= (0x02&(x<<1));}//Timer2��ʱģʽѡ��0���ֶ�����ģʽ��1���Զ�����ģʽ
#define T2_INT_FLAG_CLR INT_PE_STAT &= ~0x01;IRCON1 &= ~0x80 // ���Timer2�жϱ�־λ
#define T2_RUN  TIMER2_CFG |= 0X01//1Ϊ����Timer2
#define T2_STOP TIMER2_CFG &= ~0X01//0ΪֹͣTimer2

#if Timer0_EN
extern void Timer0_Init(uint Timer0Us);
extern uint xdata ctk_soft_reset_max_count;
extern uint xdata sclen_soft_reset_count;
extern uint xdata sclen_soft_reset_max_count;
#endif

#if Timer1_EN
extern void Timer1_Init(uint Timer1Us);
#endif

#if Timer2_EN
#define TIMER2_CLK_RC32K 0 //Timer2ʱ��ѡ���ڲ�RC32K
#define TIMER2_CLK_XTAL 1 //Timer2ʱ��ѡ���ⲿ����
extern void Timer2_Init(unsigned int Timer2Ms);
#endif

#endif