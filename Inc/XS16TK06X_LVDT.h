#ifndef __XS16TK06X_LVDT_H__
#define __XS16TK06X_LVDT_H__


#define	VolDet_EN				1	//降压检测使能配置	 				1:使能编译，0:不使能编译

#if	(EEPROM_LVD_WORK&&EEPROM_EN)
	#undef	VolDet_EN
	#define	VolDet_EN			1
#endif

//低电压中断触发的电压点设置
#define	c_volDet_powerDown_vol	(6)	//(0-保留)-(1-2.7V)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(5-3.9V)-(6/7-4.2V)	 				1:使能编译，0:不使能编译


#define LVDT_IE_SET IEN2 |= 0x01												//开LVDT中断使能
#define LVDT_IE_CLR IEN2 &= ~0x01												//关LVDT中断使能
#define LVDT_IP_SET IPL2  |= 0x01												//设置LVDT中断优先级为高
#define LVDT_IP_CLR IPL2 &= ~0x01												//设置LVDT中断优先级为低
#define LVDT_INT_FLAG_CLR 			IRCON2 &= ~0x01					//清除低电压检测中断标志位
#define LVDT_INT_DOWN_FLAG_CLR 	INT_POBO_STAT &= ~0x01	//清除LVDT下降中断标志位
#define LVDT_INT_UP_FLAG_CLR 		INT_POBO_STAT &= ~0x02	//清除LVDT上升中断标志位
#define LVDT_ON {PD_ANA &= ~0x10;}				   						//开启低电压检测模块
#define LVDT_OFF {PD_ANA |= 0x10;}			   							//关闭低电压检测模块
#define V_LVDT_SET(x) {BOR_LVDT_VTH &= ~(0x07);BOR_LVDT_VTH |= (0x07&(x<<0));}//设置低电压升检测点:(0-保留)-(1-2.7V)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(5-3.9V)-(6/7-4.2V)


extern bit Low_Volotage_Flag;
extern bit low_power;
extern bit Low_Volotage_Flag_Confirm;
extern bit Low_Volotage_Flag_First;
extern uint xdata Low_Volotage_Flag_Count;
extern uint xdata Low_Volotage_Flag_Confirm_count;
extern void LVDT_Init(void);

#endif