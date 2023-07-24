#ifndef __XS16TK06X_API_EEP_H__
#define __XS16TK06X_API_EEP_H__


#define EEPROM_EN		0	// 1:使能编译，0:不使能编译


#define	EEPROM_LVD_WORK		0	//1:开低电压掉电写 0:正常写	

//注意观察vcc的波动是否会低于设置的低电压检测点，要保证工作时的电压高于设置的
//低电压检测电压

#define		c_eeprom_saveNum			(4)						//需要记忆的变量字节数，最大允许为128-4
#define		c_eeprom_dataLength			(c_eeprom_saveNum+4)	//实际一帧数据长度


#define		c_eeprom_eraseWaitTime	(200)					//1单位:1ms  范围：200~60000 上电或者升电多久时间后可以擦除eeprom让eeprom掉电时可以写	
//上电至少延时c_eeprom_eraseWaitTime*1.3再开显示就可避免显示抖动问题


#define		c_eeprom_init		(0)
#define		c_eeprom_free		(c_eeprom_init+1)
#define		c_eeprom_write		(c_eeprom_free+1)
#define		c_eeprom_stop		(c_eeprom_write+1)



#if EEPROM_EN
	#define EEPROM_ERASE_TIMER_SET(x)  		{SPROG_TIM &= (~0x1F);SPROG_TIM |= (0x1F&(x<<0));}//页擦除时间：(0~25:1ms~51ms,>25:10.013ms),默认10.013ms,步进为2ms
	#define EEPROM_WRITE_TIMER_SET(x)  		{SPROG_TIM &= (~0xE0);SPROG_TIM |= (0xE0&(x<<5));}//写时间(0~7:100us~30us),默认63.125us,(100-(n+1)*10) + 13.125us,n=0~7
	extern void Eeprom_Init(void);

	extern void Eeprom_Block_Erase(void);
	extern bit 	Eeprom_Block_Write_Word(uint addr,uint write_word);
	extern uint Eeprom_Block_Read_Word(uint addr);
	extern uchar Eeprom_Block_Read_Byte(uint addr);

	extern void Eeprom_Sector_Erase(uchar sector);
	extern bit 	Eeprom_Sector_Write_Word(uchar sector,uint addr,uint write_word);
	extern uint Eeprom_Sector_Read_Word(uchar sector,uint addr);
	extern uchar Eeprom_Sector_Read_Byte(uchar sector,uint addr);

	extern void Eeprom_Page_Erase(uchar);
	extern bit 	Eeprom_Page_Write_Word(uchar page,uint addr,uint write_word);
	extern uint Eeprom_Page_Read_Word(uchar page,uint addr);
	extern uchar Eeprom_Page_Read_Byte(uchar page,uint addr);	
#endif

#if EEPROM_EN
	#if	(EEPROM_LVD_WORK)	//掉电写记忆无需用户调用任何函数
		extern	uchar	xdata	b_eeprom_layer;
		extern	uint	xdata	b_eeprom_waitTime;
		extern	bit		gf_eeprom_powerStatus;
		extern	bit	gf_ea_close;
		extern	void	eeprom_read_deal(void);
		extern	void 	eeprom_erase_deal(void);
		extern	void	eeprom_write_deal(void);
	#else
		extern	void eeprom_deal(void);		//主程序调用
		extern	void eeprom_writeEn(void);	//要求写记忆时调用一次，写记忆过程cpu停止	
	#endif	
#endif	



#endif