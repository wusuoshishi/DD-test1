#ifndef __TOUCH_MCU_INIT_H__
#define __TOUCH_MCU_INIT_H__

/*各模块功能预编译配置*/
#define	SYSCLK_SEL			0//系统时钟选择0-12MHz,1-6MHZ,2-4MHZ,3-1MHz


#define DELAY_MS_EN 		0//ms延时函数，			 			1:使能编译，0:不使能编译
#define DELAY_US_EN 		1//us延时函数，			 			1:使能编译，0:不使能编译
#define POW_UP_DELAY 		0//上电延时函数，		 			1:使能编译，0:不使能编译


#if (SYSCLK_SEL == 0)
	#define SYSCLK SYS_12M //SYS-12Mhz
#elif (SYSCLK_SEL == 1)
	#define SYSCLK SYS_06M //SYS-06Mhz
#elif (SYSCLK_SEL == 2)
	#define SYSCLK SYS_04M //SYS-04Mhz
#elif (SYSCLK_SEL == 3)
	#define SYSCLK SYS_01M //SYS-01Mhz
#else

#endif

#define SYS_12M  		12//SYS-12Mhz
#define SYS_06M  		6//SYS-06Mhz
#define SYS_04M  		4//SYS-04Mhz
#define SYS_01M  		1//SYS-01Mhz

//建议操作二级总线寄存器前，关EA，等二级总线操作完成再开EA，防止操作过程中二级总线的地址或数据被中断,
//如果中断中操作二级总线寄存器时，建议先读取二级总线寄存器地址，保存在临时变量中，操作级总线完成后,
//再将二级总线寄存器地址从临时变量中还原。
#define Write_REG(reg_addr,reg_data) {REG_ADDR = reg_addr;REG_DATA =  reg_data;}//写二级总线寄存器
#define REG_SET(reg_addr,reg_data) 	 {REG_ADDR = reg_addr;REG_DATA |= reg_data;}//写1
#define REG_CLR(reg_addr,reg_data) 	 {REG_ADDR = reg_addr;REG_DATA &= reg_data;}//清0
#define Read_REG(reg_addr,reg_data)  {REG_ADDR = reg_addr;reg_data =  REG_DATA;}//读


#define SYS_CLK_SET(x)			{SYS_CLK_CFG &= ~(0x03);SYS_CLK_CFG |= (0x03&(x<<0));}//(0--12Mhz,1--6Mhz,2--04Mhz,3--1MHz)
#define SYS_CLK_WAIT_SET(x) {SYS_CLK_CFG &= ~(0x04);SYS_CLK_CFG |= (0x04&(x<<2));}//0退出WAIT模式，1进入WAIT模式。

#define SYS_CLK_ADJUST_EN(x)										{EA = 0;REG_ADDR = 0x29;REG_DATA &= ~(0x03);REG_DATA |= (0x03&(x<<0));EA = 1;}//(2:使能系统时钟从ADJ_OSC微调；其它：不使能)
#define SYS_CLK_OSC_CFG_READ(reg_data)					{EA = 0;REG_ADDR = 0x06;reg_data =  REG_DATA;EA = 1;}//读OSC CFG6_REG配置
#define SYS_CLK_ADJUST_SET(x)										{EA = 0;REG_ADDR = 0x2A;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));EA = 1;}//0~255,系统时钟微调


#define BOR_ON {PD_ANA &= ~(0x08);}				   							//开掉电复位
#define BOR_OFF {PD_ANA |= (0x08);}			   							  //关掉电复位
#define V_BOR_SET(x) {BOR_LVDT_VTH &= ~(0x38);BOR_LVDT_VTH |= (0x38&(x<<3));}//设置掉电复位点:(0/1-保留）-(2-2.8V)-(3-3.3V)-(4-3.7V)-(5/6/7-4.2V)，默认为 2.1V
#define BOR_DELAY_SET(x) {REG_ADDR = 0x2E;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}//0延时1，1延时2;(延时参数见规格书)

#define WDT_TIMER(x) 			WDT_CTRL = x	 	//设置WDT溢出时间(0~7--18ms~2.304S)7--2.304S
#define WDT_ON_OFF(x)   	WDT_EN = x			//仅等于0x55时关闭看门狗
#define WDT_IE_SET   			IEN1 |= 0x80 		//开WDT中断使能
#define WDT_IE_CLR   			IEN1 &= ~0x80 	//关WDT中断使能
#define WDT_IP_SET   			IPL1  |= 0x80 	//设置WDT中断优级为高
#define WDT_IP_CLR   			IPL1 &= ~0x80 	//设置WDT中断优级为低
#define WDT_INT_FLAG_CLR 	INT_PE_STAT &= ~0x02;IRCON1 &= ~0x80 // 清除WDT中断标志位

extern void Bor_Init(void);
extern void Set_Sys_Clk(void);
extern void WDT_Init(void);
extern void CFG_Check(void);


#ifdef DELAY_MS_EN
	#if (DELAY_MS_EN == 1)
	extern void Delay_Ms(uint ms);//1-1ms
	#endif
#endif

#ifdef SLEEP_MODE
	#if (SLEEP_MODE == 0)
	extern void Delay_Ms(uint ms);//1-1ms
	#endif
#endif


#if (DELAY_US_EN == 1)
extern void Delay_Us(uint us);
#endif

#if (POW_UP_DELAY == 1)
extern void Pow_Up_Delay(uint ms);
#endif


extern void WDT_Init(void);
extern void Init_IO(void);
extern void Default_Set_IO(void);

extern void Function_Init(void);
extern void MCU_Init(void);




#endif  
