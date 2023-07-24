#include "Config.h"

//----------------------------------------------------------------//
//�������ƣ� void ExtInt0_Init(uchar TriggerMode)
//�������ܣ� �ⲿ�ж�0��ʼ��
//���������
//�ⲿ�ж�0������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ˫���ش���
//			 TriggerMode = 1��������ʽΪ�½��ش���
//			 TriggerMode = 2��������ʽΪ�����ش���
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt0_EN
#pragma message "���룬void ExtInt0_Init(uchar TriggerMode)����"
void ExtInt0_Init(uchar TriggerMode)
{

	EA = 0;//�����жϣ�

	INT0_FUN_SET(1)//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	INT0_IP_SET;//����IN0�ж��ż�Ϊ��
	INT0_INT_FLAG_CLR;//���INT0�жϱ�־������ʵ��Ӧ���������ȼ�
	
	switch(TriggerMode)
	{
		case 0:	
								
			EXT_INT_CON |= 0X01;	//����Ϊ�½��ش��� 
			
		break;

		case 1:						
			EXT_INT_CON &= ~0X01;	
			EXT_INT_CON |= 0X02;  	//����Ϊ�����ش���
		break;
							 
		case 2:						
			EXT_INT_CON |= 0X03;	//����Ϊ˫���ش���
		
		break;
							

		default:
			EXT_INT_CON |= 0X01;	//����Ϊ�½��ش���
		break;	
	}
	INT0_IE_SET;//ʹ���ⲿINT0�ж� 
	EA = 1;//�����ж�	
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext0_ISR() interrupt 0
//�������ܣ� �ⲿ�ж�0�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext0_ISR() interrupt 0 
{
	
	INT0_INT_FLAG_CLR;//���INT0�жϱ�־


} 
#endif

//-----------------------------------------------------------------//
//�������ƣ� void ExtInt1_Init(uchar TriggerMode)
//�������ܣ� �ⲿ�ж�1��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ˫���ش���
//			 TriggerMode = 1��������ʽΪ�½��ش���
//			 TriggerMode = 2��������ʽΪ�����ش��� 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt1_EN
#pragma message "���룬void ExtInt1_Init(uchar TriggerMode)����"
void ExtInt1_Init(uchar TriggerMode)
{
	EA = 0;//�����жϣ�
	INT1_FUN_SET(1)//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	INT1_INT_FLAG_CLR;//���INT1�жϱ�־
	INT1_IP_SET;//����INT1�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	switch(TriggerMode)
	{
		case 0:	
								
			EXT_INT_CON |= 0X04;	//����Ϊ�½��ش��� 
			
		break;

		case 1:						
			EXT_INT_CON &= ~0X04;	
			EXT_INT_CON |= 0X08;  	//����Ϊ�����ش���
		break;
							 
		case 2:						
			EXT_INT_CON |= 0X0C;	//����Ϊ˫���ش���
		
		break;
							

		default:
			EXT_INT_CON |= 0X04;	//����Ϊ�½��ش���
		break;	
	}
	INT1_IE_SET;//ʹ���ⲿINT1�ж� 
	EA = 1;//�����ж�	
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext1_ISR() interrupt 2
//�������ܣ� �ⲿ�ж�1�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext1_ISR() interrupt 2 
{
	
	INT1_INT_FLAG_CLR;//���INT1�жϱ�־
	
	
}
#endif


//-----------------------------------------------------------------//
//�������ƣ� void ExtInt2_Init(uchar TriggerMode)
//�������ܣ� �ⲿ�ж�2��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ˫���ش���
//			 TriggerMode = 1��������ʽΪ�½��ش���
//			 TriggerMode = 2��������ʽΪ�����ش���
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt2_EN
#pragma message "���룬void ExtInt2_Init(uchar TriggerMode)����"
void ExtInt2_Init(uchar TriggerMode)
{
	EA = 0;//�����жϣ�
	INT2_FUN_SET(1)//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	INT2_INT_FLAG_CLR;//���INT2�жϱ�־
	INT2_IP_SET;//����INT2�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	switch(TriggerMode)
	{
		case 0:	
								
			EXT_INT_CON |= 0X10;	//����Ϊ�½��ش��� 
			
		break;

		case 1:						
			EXT_INT_CON &= ~0X10;	
			EXT_INT_CON |= 0X20;  	//����Ϊ�����ش���
		break;
							 
		case 2:						
			EXT_INT_CON |= 0X30;	//����Ϊ˫���ش���
		
		break;
							

		default:
			EXT_INT_CON |= 0X10;	//����Ϊ�½��ش���
		break;	
	}
	INT2_IE_SET;//ʹ���ⲿINT2�ж� 
	EA = 1;//�����ж�	
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext2_ISR() interrupt 9
//�������ܣ� �ⲿ�ж�2�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext2_ISR() interrupt 9 
{
	INT2_INT_FLAG_CLR;//���INT2�жϱ�־	
	
}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel)
//�������ܣ� �ⲿ�ж�3��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ�½��ش���
//			 TriggerMode = 1��������ʽΪ�����ش���
//��������� ��
//�� �� ֵ�� ��
//ע���������INT3_X�ж�ʱ��ͬһʱ��ֻ����Ӧһ���жϣ���Ҫ�ͷź����Ӧ��һ��INT3_X
//-----------------------------------------------------------------// 
#if ExtInt3_EN
#pragma message "���룬void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel)����"
void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel)
{
	EA = 0;//�����жϣ�
	REG_ADDR=0x25;
	REG_DATA = (uchar)(Int3_X_Sel>>16);
	TRISD |= ((uchar)(Int3_X_Sel>>15))&(0x3E);
	TRISA |= ((uchar)(Int3_X_Sel>>21))&(0x03);

	REG_ADDR=0x26;
	REG_DATA  = (uchar)(Int3_X_Sel>>8);
	TRISC |= (uchar)(Int3_X_Sel>>8);
	
	REG_ADDR=0x27;
	REG_DATA = (uchar)(Int3_X_Sel);
	TRISB |= (uchar)(Int3_X_Sel);
	INT3_INT_FLAG_CLR;//���INT2�жϱ�־
	INT3_IP_SET;//����INT2�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	switch(TriggerMode)
	{
		case 0:									
			EXT_INT_CON &= ~0X40;	//����Ϊ�½��ش��� 			
		break;

		case 1:						
			EXT_INT_CON |= 0X40;  	//����Ϊ�����ش���
		break;
							 
		default:
			EXT_INT_CON &= ~0X40;	//����Ϊ�½��ش��� 
		break;	
	}
	INT3_IE_SET;//ʹ���ⲿINT3�ж� 
	EA = 1;//�����ж�	
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext3_ISR() interrupt 18
//�������ܣ� �ⲿ�ж�3�ж��Ӻ�����ͬһʱ��ֻ����Ӧһ���ⲿ�ж������źţ�INT3_X����������ż��ʱ����ƽ״̬��Ҫ�ͷŲź������Ӧ��
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext3_ISR() interrupt 18 
{
	INT3_INT_FLAG_CLR;//���INT2�жϱ�־
	
	if((DATAB&0x01))//PB0�����غ󣬶�IO��ƽ״̬
	{
				
	}
	else//�½��غ󣬶�IO��ƽ״̬
	{
			
	}
	if((DATAB&0x02))//PB1�����󣬶�IO��ƽ״̬
	{
			
	}
	else//�½��غ󣬶�IO��ƽ״̬
	{
				
	}

}
#endif
