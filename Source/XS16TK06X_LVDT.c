#include "Config.h"

	
#if	VolDet_EN
bit Low_Volotage_Flag = 0;
bit low_power = 0;
bit Low_Volotage_Flag_Confirm = 0;
bit Low_Volotage_Flag_First = 0;
uint xdata Low_Volotage_Flag_Count = 0;
uint xdata Low_Volotage_Flag_Confirm_count;
#endif

#if ((VolDet_EN == 1))

//-----------------------------------------------------------------//
//�������ƣ� void LVDT_Init(void)
//�������ܣ� ��ѹ��ѹ����ʼ��
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if ((VolDet_EN == 1))
void LVDT_Init(void)
{
	EA = 0;//�����жϣ�
	LVDT_IP_SET;//���ý�ѹ��ѹ���ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	LVDT_INT_FLAG_CLR;//����͵�ѹ����жϱ�־λ
	LVDT_INT_DOWN_FLAG_CLR;//�����ѹ�½��жϱ�־λ	
	LVDT_INT_UP_FLAG_CLR;//�����ѹ�����жϱ�־λ
	
	LVDT_ON;//������ѹ��ѹ���ģ��
	V_LVDT_SET(c_volDet_powerDown_vol);//���õ͵�ѹ������:(0-����)-(1-2.7V)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(5-3.9V)-(6/7-4.2V)
	
	LVDT_IE_SET;//ʹ�ܽ�ѹ��ѹ���ж�
	EA = 1;//�����ж�	   
}
#endif
//-----------------------------------------------------------------//
//�������ƣ� void LVDT_ISR() interrupt 15
//�������ܣ� ��ѹ��ѹ����ж�
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//	
void LVDT_ISR() interrupt 15
{	
	LVDT_INT_FLAG_CLR;//�����ѹ��ѹ�жϱ�־λ
	if(INT_POBO_STAT&0x01)
	{
		Low_Volotage_Flag = 1;
		low_power = 1;
		LVDT_INT_DOWN_FLAG_CLR;//�����ѹ�½��жϱ�־λ	
		#if	(EEPROM_EN&&EEPROM_LVD_WORK)
			gf_ea_close=1;		//д�����������̲����ж�
			eeprom_write_deal();	//����д
			b_eeprom_waitTime=0;
			gf_eeprom_powerStatus=0;
			gf_ea_close=0;
			EA=1;	//�ָ��ж�
		#endif		
	}
	if(INT_POBO_STAT&0x02)
	{
		LVDT_INT_UP_FLAG_CLR;//�����ѹ�����жϱ�־λ	
		Low_Volotage_Flag = 0;
		low_power = 0; 
		Low_Volotage_Flag_Confirm = 0;
		Low_Volotage_Flag_Count = 0;
		#if	(EEPROM_EN&&EEPROM_LVD_WORK)
			gf_eeprom_powerStatus=1;
		#endif	
		
	}
		
}
	 
#endif
