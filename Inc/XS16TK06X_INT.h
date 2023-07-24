#ifndef __XS16TK06X_INT_H__
#define __XS16TK06X_INT_H__

#define	ExtInt012_upTodown	0	//�½��أ��͹���ģʽ�µ͵�ƽ����
#define	ExtInt012_downToUp	1	//������  �͹���ģʽ�¸ߵ�ƽ����
#define	ExtInt012_downAndUp	2	//˫��    �͹���ģʽ�µ͵�ƽ����

/*���ϣ��ʹ���ⲿ�ж�3����������ʣ������ڴ����жϺ󲻶ϱ仯������ʽ��
�½��ؽ��ж����´ε��жϷ�ʽ�л�Ϊ�����أ���֮*/
#define	ExtInt3_upTodown	0	//�½��أ��͹���ģʽ�µ͵�ƽ����
#define	ExtInt3_downToUp	1	//������  �͹���ģʽ�¸ߵ�ƽ���� 

#define	ExtInt0_EN			0	//�ⲿ�ж�0ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt0_MODE		ExtInt012_upTodown	//�ⲿ�ж�0������ʽ

#define	ExtInt1_EN			0	//�ⲿ�ж�1ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt1_MODE		ExtInt012_upTodown	//�ⲿ�ж�1������ʽ

#define	ExtInt2_EN			0	//�ⲿ�ж�2ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt2_MODE		ExtInt012_upTodown	//�ⲿ�ж�2������ʽ

#define	ExtInt3_EN			0	//�ⲿ�ж�3ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define  ExtInt3_SEL			((ulong)0x01<<19)//0x00000000//INT3_X��Ӧ��bit0~bit26λΪ1ѡ��Ϊ�жϹ��ܣ�INT3_X����һ���ж�������ͬһʱ��ֻ��һ���ж������ź���Ч��ʹ�ú���Ҫ�ͷš�
#define	ExtInt3_MODE		ExtInt3_upTodown	//�ⲿ�ж�3������ʽ


#define INT0_FUN_SET(x) {TRISD |= 0x01;PERIPH_IO_SEL &= ~(0x01);PERIPH_IO_SEL |= (0x01&(x<<0));}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_IE_SET 	IEN0 |= 0x01//��INT0�ж�ʹ�� 
#define INT0_IE_CLR 	IEN0 &= ~0x01//��INT0�ж�ʹ��
#define INT0_IP_SET 	IPL0  |= 0x01//����INT0�ж��ż�Ϊ��
#define INT0_IP_CLR 	IPL0 &= ~0X01//����INT0�ж��ż�Ϊ��
#define INT0_INT_FLAG_CLR TCON  &= ~0X02//���INT0�жϱ�־


#define INT1_FUN_SET(x) {TRISD |= 0x40;PERIPH_IO_SEL &= ~(0x02);PERIPH_IO_SEL |= (0x02&(x<<1));}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT1_IE_SET 	IEN0 |= 0x04//��INT1�ж�ʹ�� 
#define INT1_IE_CLR 	IEN0 &= ~0x04//��INT1�ж�ʹ��
#define INT1_IP_SET 	IPL0  |= 0x04//����INT1�ж��ż�Ϊ��
#define INT1_IP_CLR 	IPL0 &= ~0X04//����INT1�ж��ż�Ϊ��
#define INT1_INT_FLAG_CLR TCON  &= ~0X08//���INT1�жϱ�־


#define INT2_FUN_SET(x) {TRISD |= 0x80;PERIPH_IO_SEL &= ~(0x04);PERIPH_IO_SEL |= (0x04&(x<<2));}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT2_IE_SET 	IEN1 |= 0x04//��INT2�ж�ʹ�� 
#define INT2_IE_CLR 	IEN1 &= ~0x04//��INT2�ж�ʹ��
#define INT2_IP_SET 	IPL1  |= 0x04//����INT2�ж��ż�Ϊ��
#define INT2_IP_CLR 	IPL1 &= ~0X04//����INT2�ж��ż�Ϊ��
#define INT2_INT_FLAG_CLR IRCON1  &= ~0X04//���INT2�жϱ�־



#define INT3_IE_SET 	IEN2 |= 0x08//��INT3�ж�ʹ�� 
#define INT3_IE_CLR 	IEN2 &= ~0x08//��INT3�ж�ʹ��
#define INT3_IP_SET 	IPL2  |= 0x08//����INT3�ж��ż�Ϊ��
#define INT3_IP_CLR 	IPL2 &= ~0x08//����INT3�ж��ż�Ϊ��
#define INT3_INT_FLAG_CLR IRCON2  &= ~0x08//���INT3�жϱ�־

#if ExtInt0_EN
extern void ExtInt0_Init(uchar TriggerMode);
#endif

#if ExtInt1_EN
extern void ExtInt1_Init(uchar TriggerMode);
#endif

#if ExtInt2_EN
extern void ExtInt2_Init(uchar TriggerMode);
#endif

#if ExtInt3_EN
extern void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel);
#endif

#endif