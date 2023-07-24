#include 	".\Application_Library\Global.h"

void main(void)
{
	
	//MCU_Init()初始化函数，调用函数有WDT_Init()、Default_Set_IO()、Init_IO()、Function_Init()。
	MCU_Init();
	MCU_other_Init();
	//p_buz_out;
	while(1)
	{
		//清看门狗。
		WDT_CTRL = 7;

		#if SNS_NUM	
			#ifdef VolDet_EN
				#if VolDet_EN
				if(low_power == 0)//进入低电压中断时标记，low_power = 1时,不处理按键，低电压检测点根据实际项目配置
				#endif
			#endif
			{
				//获取按键标志位
				XS16TK06X_Set_Touch_Flag();	
				
			}
		#endif
			
		//while (1)
		//{
		//	//清看门狗。
		//	WDT_CTRL = 7;
		//	//PWM0C_Set(38000,100);
		//	PWM0C_Set(2000,1);	//(频率,占空比) 
		//}
			
		//建议将项目功能函数定义在Project.c中或新建c文件。
		Project();
			
	}			
}