#ifndef __XS16TK06X_LVDT_H__
#define __XS16TK06X_LVDT_H__


#define	VolDet_EN				1	//��ѹ���ʹ������	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���

#if	(EEPROM_LVD_WORK&&EEPROM_EN)
	#undef	VolDet_EN
	#define	VolDet_EN			1
#endif

//�͵�ѹ�жϴ����ĵ�ѹ������
#define	c_volDet_powerDown_vol	(6)	//(0-����)-(1-2.7V)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(5-3.9V)-(6/7-4.2V)	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���


#define LVDT_IE_SET IEN2 |= 0x01												//��LVDT�ж�ʹ��
#define LVDT_IE_CLR IEN2 &= ~0x01												//��LVDT�ж�ʹ��
#define LVDT_IP_SET IPL2  |= 0x01												//����LVDT�ж����ȼ�Ϊ��
#define LVDT_IP_CLR IPL2 &= ~0x01												//����LVDT�ж����ȼ�Ϊ��
#define LVDT_INT_FLAG_CLR 			IRCON2 &= ~0x01					//����͵�ѹ����жϱ�־λ
#define LVDT_INT_DOWN_FLAG_CLR 	INT_POBO_STAT &= ~0x01	//���LVDT�½��жϱ�־λ
#define LVDT_INT_UP_FLAG_CLR 		INT_POBO_STAT &= ~0x02	//���LVDT�����жϱ�־λ
#define LVDT_ON {PD_ANA &= ~0x10;}				   						//�����͵�ѹ���ģ��
#define LVDT_OFF {PD_ANA |= 0x10;}			   							//�رյ͵�ѹ���ģ��
#define V_LVDT_SET(x) {BOR_LVDT_VTH &= ~(0x07);BOR_LVDT_VTH |= (0x07&(x<<0));}//���õ͵�ѹ������:(0-����)-(1-2.7V)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(5-3.9V)-(6/7-4.2V)


extern bit Low_Volotage_Flag;
extern bit low_power;
extern bit Low_Volotage_Flag_Confirm;
extern bit Low_Volotage_Flag_First;
extern uint xdata Low_Volotage_Flag_Count;
extern uint xdata Low_Volotage_Flag_Confirm_count;
extern void LVDT_Init(void);

#endif