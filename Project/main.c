#include 	".\Application_Library\Global.h"

void main(void)
{
	
	//MCU_Init()��ʼ�����������ú�����WDT_Init()��Default_Set_IO()��Init_IO()��Function_Init()��
	MCU_Init();
	MCU_other_Init();
	//p_buz_out;
	while(1)
	{
		//�忴�Ź���
		WDT_CTRL = 7;

		#if SNS_NUM	
			#ifdef VolDet_EN
				#if VolDet_EN
				if(low_power == 0)//����͵�ѹ�ж�ʱ��ǣ�low_power = 1ʱ,�����������͵�ѹ�������ʵ����Ŀ����
				#endif
			#endif
			{
				//��ȡ������־λ
				XS16TK06X_Set_Touch_Flag();	
				
			}
		#endif
			
		//while (1)
		//{
		//	//�忴�Ź���
		//	WDT_CTRL = 7;
		//	//PWM0C_Set(38000,100);
		//	PWM0C_Set(2000,1);	//(Ƶ��,ռ�ձ�) 
		//}
			
		//���齫��Ŀ���ܺ���������Project.c�л��½�c�ļ���
		Project();
			
	}			
}