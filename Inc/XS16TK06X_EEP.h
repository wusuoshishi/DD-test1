#ifndef __XS16TK06X_API_EEP_H__
#define __XS16TK06X_API_EEP_H__


#define EEPROM_EN		0	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���


#define	EEPROM_LVD_WORK		0	//1:���͵�ѹ����д 0:����д	

//ע��۲�vcc�Ĳ����Ƿ��������õĵ͵�ѹ���㣬Ҫ��֤����ʱ�ĵ�ѹ�������õ�
//�͵�ѹ����ѹ

#define		c_eeprom_saveNum			(4)						//��Ҫ����ı����ֽ������������Ϊ128-4
#define		c_eeprom_dataLength			(c_eeprom_saveNum+4)	//ʵ��һ֡���ݳ���


#define		c_eeprom_eraseWaitTime	(200)					//1��λ:1ms  ��Χ��200~60000 �ϵ����������ʱ�����Բ���eeprom��eeprom����ʱ����д	
//�ϵ�������ʱc_eeprom_eraseWaitTime*1.3�ٿ���ʾ�Ϳɱ�����ʾ��������


#define		c_eeprom_init		(0)
#define		c_eeprom_free		(c_eeprom_init+1)
#define		c_eeprom_write		(c_eeprom_free+1)
#define		c_eeprom_stop		(c_eeprom_write+1)



#if EEPROM_EN
	#define EEPROM_ERASE_TIMER_SET(x)  		{SPROG_TIM &= (~0x1F);SPROG_TIM |= (0x1F&(x<<0));}//ҳ����ʱ�䣺(0~25:1ms~51ms,>25:10.013ms),Ĭ��10.013ms,����Ϊ2ms
	#define EEPROM_WRITE_TIMER_SET(x)  		{SPROG_TIM &= (~0xE0);SPROG_TIM |= (0xE0&(x<<5));}//дʱ��(0~7:100us~30us),Ĭ��63.125us,(100-(n+1)*10) + 13.125us,n=0~7
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
	#if	(EEPROM_LVD_WORK)	//����д���������û������κκ���
		extern	uchar	xdata	b_eeprom_layer;
		extern	uint	xdata	b_eeprom_waitTime;
		extern	bit		gf_eeprom_powerStatus;
		extern	bit	gf_ea_close;
		extern	void	eeprom_read_deal(void);
		extern	void 	eeprom_erase_deal(void);
		extern	void	eeprom_write_deal(void);
	#else
		extern	void eeprom_deal(void);		//���������
		extern	void eeprom_writeEn(void);	//Ҫ��д����ʱ����һ�Σ�д�������cpuֹͣ	
	#endif	
#endif	



#endif