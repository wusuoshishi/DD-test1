#include 	"Config.h"
#include 	"..\Application_Library\Global.h"
		
	#if (EEPROM_EN == 1)
		#pragma message "编译,EEPROM功能"
		#if	(EEPROM_LVD_WORK)	
			#pragma message "编译,掉电时写EEPROM功能"
		#endif

		uint eep_addr_offset = 0;
		void Eeprom_Init(void);
		void Eeprom_Erase_Page(void);
		bit Eeprom_Block_Write_Word(uint addr,uint write_word);
		bit Eeprom_Sector_Write_Word(uchar sector,uint addr,uint write_word);
		bit Eeprom_Page_Write_Word(uchar page,uint addr,uint write_word);
		
		

		uchar	xdata	gb_eeprom_dataBuf[c_eeprom_dataLength];
		
	#if	(EEPROM_LVD_WORK)
		uchar	xdata	b_eeprom_layer=0;
		uint	xdata	b_eeprom_waitTime=0;
		bit		gf_eeprom_powerStatus=1;
	#else
		uchar	xdata	b_eeprom_layer;
		bit		f_eeprom_writeEn;
	#endif
		bit	gf_ea_close=0;


#if	(EEPROM_LVD_WORK==0)			
/*-----------------------------------------------------------------
函数名称： void eeprom_writeEn(void)
函数功能： 写EEPROM使能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void eeprom_writeEn(void)
{
	f_eeprom_writeEn=1; 				
}
#endif



/***********************************************************
;函数名称:void	eeprom_userInitDate(void)
;函数功能:数据上电初始化
;输入参数:
;输出参数:
;使用注意:上电读取记忆失败后给记忆数据的初值
;---------
;---------
;**********************************************************/
void	eeprom_userInitDate(void)
{
//	gb_keyPress_num=0;
//	gb_eeprom_num1=0;
//	gb_eeprom_num2=0;
//	gb_eeprom_num3=0;
}




/***********************************************************
;函数名称:void	eeprom_userWriteDate(void)
;函数功能:数据更新
;输入参数:
;输出参数:
;使用注意:
;---------
;---------
;**********************************************************/
void	eeprom_userWriteDate(void)
{
//	gb_eeprom_dataBuf[0]=gb_eeprom_num1;
//	gb_eeprom_dataBuf[1]=gb_eeprom_num2;
//	gb_eeprom_dataBuf[2]=gb_eeprom_num3;
//	gb_eeprom_dataBuf[3]=gb_keyPress_num;


}


/***********************************************************
;函数名称:void eeprom_userReadDate(void)
;函数功能:读出的记忆数据给使用者
;输入参数:
;输出参数:
;使用注意:
;---------
;---------
;**********************************************************/
void	eeprom_userReadDate(void)
{
//	gb_eeprom_num1=gb_eeprom_dataBuf[0];
//	gb_eeprom_num2=gb_eeprom_dataBuf[1];
//	gb_eeprom_num3=gb_eeprom_dataBuf[2];
//	gb_keyPress_num=gb_eeprom_dataBuf[3];

}



/***********************************************************
;函数名称:void eeprom_chkCal(void)
;函数功能:校验码计算
;输入参数:无
;输出参数:无
;使用注意:无
;---------
;---------
;**********************************************************/
void	eeprom_chkCal(void)
{
	uint i;
	uchar	sum=0;
	
	for(i=0;i<c_eeprom_saveNum;i++)
	{
		sum +=gb_eeprom_dataBuf[i];
	}	
	gb_eeprom_dataBuf[c_eeprom_saveNum]=0xaa;
	gb_eeprom_dataBuf[c_eeprom_saveNum+1]=0x55;
	gb_eeprom_dataBuf[c_eeprom_saveNum+2]=sum;
	gb_eeprom_dataBuf[c_eeprom_saveNum+3]=sum^0xff;	
}



		//-----------------------------------------------------------------//
		//函数名称： void Eeprom_Init(void)
		//函数功能： Eeprom_Init擦写时间初始化
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Init(void)
		{
			EA = 0;//关总中断
			REG_ADDR = 0x23;
			eep_addr_offset = ((uint)REG_DATA)<<8;
			REG_ADDR = 0x22;
			eep_addr_offset |= REG_DATA;
			/*cubic*/
			// EEPROM_ERASE_TIMER_SET(26);//页擦除时间：(0~25:1ms~51ms,>25:10.013ms),默认10.013ms,步进为2ms
			EEPROM_ERASE_TIMER_SET(2);//页擦除时间：(0~25:1ms~51ms,>25:10.013ms),默认10.013ms,步进为2ms
			EEPROM_WRITE_TIMER_SET(0);//写时间(0~7:100us~30us),默认63.125us,(100-(n+1)*10) + 13.125us,n=0~7
			EA = 1;//开总中断	
			#if	(EEPROM_LVD_WORK==0)
				b_eeprom_layer=c_eeprom_init;	
				f_eeprom_writeEn=0;
			#else
				b_eeprom_layer=1;
				eeprom_read_deal();
			#endif
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void Eeprom_Block_Erase(void)
		//函数功能： Eeprom块擦除
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Block_Erase(void)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;//选择Block地址
			SPROG_CMD = 0x94;
			
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			
			SPROG_CMD = 0x00;
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 1;//开总中断
		}
	//-----------------------------------------------------------------//
	//函数名称： bit Eeprom_Block_Write_Word(uint addr,uint write_word)
	//函数功能： Eeprom Block 写数据
	//输入参数： uint addr:当前Block对应的地址(0~511)；uint write_word：将要写入的数据;
	//输出参数： 无
	//返 回 值： 0:写成功；1：写失败；
	//-----------------------------------------------------------------//
	
		
		bit Eeprom_Block_Write_Word(uint addr,uint write_word)
		{	
			bit Write_OK = 0;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00; 
			SPROG_ADDR_L = addr<<1;
			SPROG_ADDR_H |= (addr>>7)&0x03;//选择要入地址
			
			SPROG_DATA = write_word>>8;	//准备写入的数据高八位
			SPROG_DATA = write_word;//准备写入的数据低八位
			
			SPROG_CMD = 0x69;
		
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			
			SPROG_CMD = 0x00;
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			if(Eeprom_Block_Read_Word(addr)== write_word)
			{
					Write_OK = 0;
			}
			else
			{
					Write_OK = 1;
			}
			EA = 1;//开总中断
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uint Eeprom_Block_Read_Word(uint addr)
		//函数功能： Eeprom按照block读数据
		//输入参数： uint addr(0~511)：读取block第addr 双字节;
		//输出参数： 无
		//返 回 值： 返回读block第addr双字节的内容；
		//-----------------------------------------------------------------//
		uint Eeprom_Block_Read_Word(uint addr)
		{	
			uint code  * p;
			p = 0x8000 + (addr<<1) - eep_addr_offset;
			
		  return	*p; 
		}
		
		
		//-----------------------------------------------------------------//
		//函数名称： uint Eeprom_Block_Read_Byte(uint addr)
		//函数功能： Eeprom按照block读数据
		//输入参数： uint addr(0~1023)：读取block第addr 字节;
		//输出参数： 无
		//返 回 值： 返回读block第addr字节的内容；
		//-----------------------------------------------------------------//
		uchar Eeprom_Block_Read_Byte(uint addr)
		{	
			uchar code  * p;
			p = 0x8000 + (addr) - eep_addr_offset;
			
		  return	*p; 
		}
		
		
		
		//-----------------------------------------------------------------//
		//函数名称： Eeprom_Sector_Erase(uchar sector)
		//函数功能： Eeprom sector擦除
		//输入参数： uchar sector：选择擦除扇区 0~1
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Sector_Erase(uchar sector)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			if(sector == 1)
			{
					SPROG_ADDR_H |= 0x02;//选择sector地址
			}
			SPROG_CMD = 0x96;
			
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			
			SPROG_CMD = 0x00;
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 1;//开总中断
		}
		
	//-----------------------------------------------------------------//
	//函数名称： bit Eeprom_Sector_Write_Word(uchar sector,uint addr,uint write_word)
	//函数功能： Eeprom Sector 写数据
	//输入参数： uchar sector(0~1):选择扇区，uint addr:当前Sector对应的地址(0~255)；uint write_word：将要写入的数据;
	//输出参数： 无
	//返 回 值： 0:写成功；1：写失败；
	//-----------------------------------------------------------------//		
		bit Eeprom_Sector_Write_Word(uchar sector,uint addr,uint write_word)
		{	
			bit Write_OK = 0;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			if(sector == 1)
			{
				SPROG_ADDR_H |= 0x02;//选择sector地址
			}
			
			SPROG_ADDR_H |= addr>>7&0x01;
			SPROG_ADDR_L = addr<<1&0xFF;//选择写地址  
			
			
			SPROG_DATA = write_word>>8;	//准备写入的数据高八位
			SPROG_DATA = write_word;//准备写入的数据低八位
		
			
			SPROG_CMD = 0x69;
		
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			
			SPROG_CMD = 0x00;
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			if(Eeprom_Sector_Read_Word(sector,addr)== write_word)
			{
					Write_OK = 0;
			}
			else
			{
					Write_OK = 1;
			}
			EA = 1;//开总中断
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uint Eeprom_Sector_Read_Word(uchar sector,uint addr)
		//函数功能： Eeprom按照sector读数据
		//输入参数： uchar sector:0~1,选择sector0~secor1;uint addr(0~255)：读取sector第addr 双字节;
		//输出参数： 无
		//返 回 值： 返回读sector第addr 双字节 的内容；
		//-----------------------------------------------------------------//
		uint Eeprom_Sector_Read_Word(uchar sector,uint addr)
		{	
			uint code  * p;
			p = 0x8000+(sector*512 + (addr<<1)) - eep_addr_offset;
			return *p;
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uint Eeprom_Sector_Read_Byte(uchar sector,uint addr)
		//函数功能： Eeprom按照sector读数据
		//输入参数： uchar sector:0~1,选择sector0~secor1;uint addr(0~511)：读取sector第addr个字节;
		//输出参数： 无
		//返 回 值： 返回读sector第addr个字节的内容；
		//-----------------------------------------------------------------//
		uchar Eeprom_Sector_Read_Byte(uchar sector,uint addr)
		{	
			uchar code  * p;
			p = 0x8000+(sector*512 + (addr)) - eep_addr_offset;
			return *p;
		}
		
		//-----------------------------------------------------------------//
		//函数名称： Eeprom_Page_Erase(uchar page)
		//函数功能： Eeprom page擦除
		//输入参数： uchar page 0~7
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Page_Erase(uchar page)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			
			/*cubic 地址=page*128,一页为128byte*/
			SPROG_ADDR_L = (page<<7)&0x80;
			SPROG_ADDR_H |= (page>>1)&0x03;//选择要页地址
			
			SPROG_CMD = 0x95;
			
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			
			SPROG_CMD = 0x00;
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			
			if(!gf_ea_close)
				EA = 1;//开总中断		
		}
		
		//-----------------------------------------------------------------//
	//函数名称： bit Eeprom_Page_Write_Word(uchar page,uint addr,uint write_word)
	//函数功能： Eeprom Sector 写数据
	//输入参数： uchar page(0~7):选择页，uint addr:(0~63)；uint write_word：将要写入的数据;
	//输出参数： 无
	//返 回 值： 0:写成功；1：写失败；
	//-----------------------------------------------------------------//
	
		
		bit Eeprom_Page_Write_Word(uchar page,uint addr,uint write_word)
		{	
			bit Write_OK = 0;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			
			/*cubic 地址=page*128,一页为128byte*/
			SPROG_ADDR_L = (page<<7)&0x80;
			SPROG_ADDR_H |= (page>>1)&0x03;//选择page地址
			
			/*cubic 写为字节写，地址必须为偶数，则原本可用的地址变为原来的一半*/
			SPROG_ADDR_L |= (addr<<1)&0x7F;//选择写地址
			
			
			SPROG_DATA = write_word>>8;	//准备写入的数据高八位
			SPROG_DATA = write_word;//准备写入的数据低八位
			
			SPROG_CMD = 0x69;
		
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			
			SPROG_CMD = 0x00;
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			if(Eeprom_Page_Read_Word(page,addr)== write_word)
			{
					Write_OK = 0;
			}
			else
			{
					Write_OK = 1;
			}
			if(!gf_ea_close)
				EA = 1;//开总中断
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uint Eeprom_Page_Read_Word(uchar page,uint addr)
		//函数功能： Eeprom按照page读数据
		//输入参数： uchar page:0~7,选择page0~page7;uint addr(0~63)：读取page第addr 双字节;
		//输出参数： 无
		//返 回 值： 返回读page第addr 双字节 的内容；
		//-----------------------------------------------------------------//
		uint Eeprom_Page_Read_Word(uchar page,uint addr)
		{	
			uint code  * p;
			/*cubic 写为字节写，地址必须为偶数，则原本可用的地址变为原来的一半*/
			p = 0x8000 + (page*128 + (addr<<1)) - eep_addr_offset;
			return *p;
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uint Eeprom_Page_Read_Byte(uchar page,uint addr)
		//函数功能： Eeprom按照page读数据
		//输入参数： uchar page:0~7,选择page0~page7;uint addr(0~127)：读取page第addr个字节;
		//输出参数： 无
		//返 回 值： 返回读page第addr个字节的内容；
		//-----------------------------------------------------------------//
		uchar Eeprom_Page_Read_Byte(uchar page,uint addr)
		{	
			uchar code  * p;
			p = 0x8000 + (page*128 + (addr)) - eep_addr_offset;
			return *p;
		}


#if	(EEPROM_LVD_WORK)
/*-----------------------------------------------------------------
函数名称： void eeprom_read_deal(void)
函数功能： EEPROM上电读
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/	
	void	eeprom_read_deal(void)
	{
		uchar	i;
		uchar	len;

		//读
		len=c_eeprom_dataLength;
		i=0;
		EA = 0;//关总中断；

		while(len)
		{
			gb_eeprom_dataBuf[i]=Eeprom_Page_Read_Byte(0,i);	
			len--;
			i++;
		}		

		len=0;
		for(i=0;i<c_eeprom_saveNum;i++)
	    {
	    	len +=gb_eeprom_dataBuf[i];
	    }
	    if((gb_eeprom_dataBuf[c_eeprom_saveNum]==0xaa)&&(gb_eeprom_dataBuf[c_eeprom_saveNum+1]==0x55)
	    	&&(len==gb_eeprom_dataBuf[c_eeprom_saveNum+2])&&(len==(gb_eeprom_dataBuf[c_eeprom_saveNum+3]^0xff)))
	    {
			eeprom_userReadDate();
	    }
	    else
	    {
			eeprom_userInitDate();					
	    }
		//擦写
		b_eeprom_layer=2;		
		b_eeprom_waitTime=0;
		EA = 1;//开总中断
		
	}


/*-----------------------------------------------------------------
函数名称： void eeprom_erase_deal(void)
函数功能： EEPROM上电擦
输入参数： 无
返 回 值： 无
使用注意:  升压时重新擦写，如果没有升压中断则再写数据后的500ms~1000ms
后再次擦空，防止掉电后写数据完成了但是电压又重新恢复的情况，这样当
下次电压再次下降时重新写才有效
-----------------------------------------------------------------*/	
	void eeprom_erase_deal(void)
	{
		if(b_eeprom_layer!=2)	return;
		Eeprom_Page_Erase(0);
		b_eeprom_layer=4;

	}




/*-----------------------------------------------------------------
函数名称： void eeprom_write_deal(void)
函数功能： EEPROM掉电写
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/ 
	void	eeprom_write_deal(void)
	{
		uchar	i,errCnt;
		uint	datbuf;
		uchar	fail=0;

		if(b_eeprom_layer!=4)	return;

		eeprom_userWriteDate();
		eeprom_chkCal();	
		errCnt=2;

		while(errCnt)
		{
			for(i=0;i<c_eeprom_dataLength;i+=2)
			{
				//高字节在低位，低字节在高位
				datbuf=((uint)gb_eeprom_dataBuf[i]<<8)+(uint)gb_eeprom_dataBuf[i+1];
				if(Eeprom_Page_Write_Word(0,i/2,datbuf))
				{
					fail=1;
					break;
				}
			}
			if(fail&&errCnt)
			{
				fail=0;
				errCnt--;
				if(errCnt==0)
				{
					fail=1;
				}
				Eeprom_Page_Erase(0);
			}	
			else
			{
				errCnt=0;
			}
		}	
		b_eeprom_layer=2;

	}

#else
/*-----------------------------------------------------------------
函数名称： void eeprom_deal(void)
函数功能： EEPROM处理-非掉电写
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/	
	void eeprom_deal(void)
	{
		uchar	i,fail;
		uint 	datbuf;
		uchar	 errCnt;	
		uchar	len;
		switch(b_eeprom_layer)	
		{
			case	c_eeprom_init:
				len=c_eeprom_dataLength;
				i=0;
				while(len)
				{
					gb_eeprom_dataBuf[i]=Eeprom_Page_Read_Byte(0,i);
					len--;
					i++;
				}
				len=0;
				for(i=0;i<c_eeprom_saveNum;i++)
			    {
			    	len +=gb_eeprom_dataBuf[i];
			    }
			    b_eeprom_layer=c_eeprom_free;
			    if((gb_eeprom_dataBuf[c_eeprom_saveNum]==0xaa)&&(gb_eeprom_dataBuf[c_eeprom_saveNum+1]==0x55)
			    	&&(len==gb_eeprom_dataBuf[c_eeprom_saveNum+2])&&(len==(gb_eeprom_dataBuf[c_eeprom_saveNum+3]^0xff)))
			    {
					eeprom_userReadDate();
			    }
			    else
			    {
					eeprom_userInitDate();
					eeprom_writeEn();
					
			    }
				break;	
			case	c_eeprom_free:
				if(f_eeprom_writeEn)					
				{
					f_eeprom_writeEn=0;
					b_eeprom_layer=c_eeprom_write;
					//写之前先擦
					Eeprom_Page_Erase(0);				
					eeprom_userWriteDate();
					eeprom_chkCal();
				}
				break;
			case	c_eeprom_write:
				errCnt=2;
				fail=0;
				while(errCnt)
				{
					for(i=0;i<c_eeprom_dataLength;i+=2)
					{
						//高字节在低位，低字节在高位
						datbuf=((uint)gb_eeprom_dataBuf[i]<<8)+(uint)gb_eeprom_dataBuf[i+1];
						if(Eeprom_Page_Write_Word(0,i/2,datbuf))
						{
							fail=1;
							break;
						}
					}
					if(fail&&errCnt)
					{
						fail=0;
						errCnt--;
						Eeprom_Page_Erase(0);
						if(errCnt==0)
						{
							fail=1;
						}
					}	
					else
					{
						errCnt=0;					
					}
				}
				if(fail)
				{
					b_eeprom_layer=c_eeprom_stop;
				}
				else
				{
					b_eeprom_layer=c_eeprom_free;
					
				}				
				break;	
			case	c_eeprom_stop:
				break;			
		}	
	}
#endif

#endif
