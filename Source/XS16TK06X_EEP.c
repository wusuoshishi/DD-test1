#include 	"Config.h"
#include 	"..\Application_Library\Global.h"
		
	#if (EEPROM_EN == 1)
		#pragma message "����,EEPROM����"
		#if	(EEPROM_LVD_WORK)	
			#pragma message "����,����ʱдEEPROM����"
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
�������ƣ� void eeprom_writeEn(void)
�������ܣ� дEEPROMʹ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void eeprom_writeEn(void)
{
	f_eeprom_writeEn=1; 				
}
#endif



/***********************************************************
;��������:void	eeprom_userInitDate(void)
;��������:�����ϵ��ʼ��
;�������:
;�������:
;ʹ��ע��:�ϵ��ȡ����ʧ�ܺ���������ݵĳ�ֵ
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
;��������:void	eeprom_userWriteDate(void)
;��������:���ݸ���
;�������:
;�������:
;ʹ��ע��:
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
;��������:void eeprom_userReadDate(void)
;��������:�����ļ������ݸ�ʹ����
;�������:
;�������:
;ʹ��ע��:
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
;��������:void eeprom_chkCal(void)
;��������:У�������
;�������:��
;�������:��
;ʹ��ע��:��
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
		//�������ƣ� void Eeprom_Init(void)
		//�������ܣ� Eeprom_Init��дʱ���ʼ��
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Eeprom_Init(void)
		{
			EA = 0;//�����ж�
			REG_ADDR = 0x23;
			eep_addr_offset = ((uint)REG_DATA)<<8;
			REG_ADDR = 0x22;
			eep_addr_offset |= REG_DATA;
			/*cubic*/
			// EEPROM_ERASE_TIMER_SET(26);//ҳ����ʱ�䣺(0~25:1ms~51ms,>25:10.013ms),Ĭ��10.013ms,����Ϊ2ms
			EEPROM_ERASE_TIMER_SET(2);//ҳ����ʱ�䣺(0~25:1ms~51ms,>25:10.013ms),Ĭ��10.013ms,����Ϊ2ms
			EEPROM_WRITE_TIMER_SET(0);//дʱ��(0~7:100us~30us),Ĭ��63.125us,(100-(n+1)*10) + 13.125us,n=0~7
			EA = 1;//�����ж�	
			#if	(EEPROM_LVD_WORK==0)
				b_eeprom_layer=c_eeprom_init;	
				f_eeprom_writeEn=0;
			#else
				b_eeprom_layer=1;
				eeprom_read_deal();
			#endif
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� void Eeprom_Block_Erase(void)
		//�������ܣ� Eeprom�����
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Eeprom_Block_Erase(void)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;//ѡ��Block��ַ
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 1;//�����ж�
		}
	//-----------------------------------------------------------------//
	//�������ƣ� bit Eeprom_Block_Write_Word(uint addr,uint write_word)
	//�������ܣ� Eeprom Block д����
	//��������� uint addr:��ǰBlock��Ӧ�ĵ�ַ(0~511)��uint write_word����Ҫд�������;
	//��������� ��
	//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
	//-----------------------------------------------------------------//
	
		
		bit Eeprom_Block_Write_Word(uint addr,uint write_word)
		{	
			bit Write_OK = 0;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00; 
			SPROG_ADDR_L = addr<<1;
			SPROG_ADDR_H |= (addr>>7)&0x03;//ѡ��Ҫ���ַ
			
			SPROG_DATA = write_word>>8;	//׼��д������ݸ߰�λ
			SPROG_DATA = write_word;//׼��д������ݵͰ�λ
			
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC����ʹ�ܹر�
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
			EA = 1;//�����ж�
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Eeprom_Block_Read_Word(uint addr)
		//�������ܣ� Eeprom����block������
		//��������� uint addr(0~511)����ȡblock��addr ˫�ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�block��addr˫�ֽڵ����ݣ�
		//-----------------------------------------------------------------//
		uint Eeprom_Block_Read_Word(uint addr)
		{	
			uint code  * p;
			p = 0x8000 + (addr<<1) - eep_addr_offset;
			
		  return	*p; 
		}
		
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Eeprom_Block_Read_Byte(uint addr)
		//�������ܣ� Eeprom����block������
		//��������� uint addr(0~1023)����ȡblock��addr �ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�block��addr�ֽڵ����ݣ�
		//-----------------------------------------------------------------//
		uchar Eeprom_Block_Read_Byte(uint addr)
		{	
			uchar code  * p;
			p = 0x8000 + (addr) - eep_addr_offset;
			
		  return	*p; 
		}
		
		
		
		//-----------------------------------------------------------------//
		//�������ƣ� Eeprom_Sector_Erase(uchar sector)
		//�������ܣ� Eeprom sector����
		//��������� uchar sector��ѡ��������� 0~1
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Eeprom_Sector_Erase(uchar sector)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			if(sector == 1)
			{
					SPROG_ADDR_H |= 0x02;//ѡ��sector��ַ
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 1;//�����ж�
		}
		
	//-----------------------------------------------------------------//
	//�������ƣ� bit Eeprom_Sector_Write_Word(uchar sector,uint addr,uint write_word)
	//�������ܣ� Eeprom Sector д����
	//��������� uchar sector(0~1):ѡ��������uint addr:��ǰSector��Ӧ�ĵ�ַ(0~255)��uint write_word����Ҫд�������;
	//��������� ��
	//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
	//-----------------------------------------------------------------//		
		bit Eeprom_Sector_Write_Word(uchar sector,uint addr,uint write_word)
		{	
			bit Write_OK = 0;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			if(sector == 1)
			{
				SPROG_ADDR_H |= 0x02;//ѡ��sector��ַ
			}
			
			SPROG_ADDR_H |= addr>>7&0x01;
			SPROG_ADDR_L = addr<<1&0xFF;//ѡ��д��ַ  
			
			
			SPROG_DATA = write_word>>8;	//׼��д������ݸ߰�λ
			SPROG_DATA = write_word;//׼��д������ݵͰ�λ
		
			
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC����ʹ�ܹر�
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
			EA = 1;//�����ж�
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Eeprom_Sector_Read_Word(uchar sector,uint addr)
		//�������ܣ� Eeprom����sector������
		//��������� uchar sector:0~1,ѡ��sector0~secor1;uint addr(0~255)����ȡsector��addr ˫�ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�sector��addr ˫�ֽ� �����ݣ�
		//-----------------------------------------------------------------//
		uint Eeprom_Sector_Read_Word(uchar sector,uint addr)
		{	
			uint code  * p;
			p = 0x8000+(sector*512 + (addr<<1)) - eep_addr_offset;
			return *p;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Eeprom_Sector_Read_Byte(uchar sector,uint addr)
		//�������ܣ� Eeprom����sector������
		//��������� uchar sector:0~1,ѡ��sector0~secor1;uint addr(0~511)����ȡsector��addr���ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�sector��addr���ֽڵ����ݣ�
		//-----------------------------------------------------------------//
		uchar Eeprom_Sector_Read_Byte(uchar sector,uint addr)
		{	
			uchar code  * p;
			p = 0x8000+(sector*512 + (addr)) - eep_addr_offset;
			return *p;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� Eeprom_Page_Erase(uchar page)
		//�������ܣ� Eeprom page����
		//��������� uchar page 0~7
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Eeprom_Page_Erase(uchar page)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			
			/*cubic ��ַ=page*128,һҳΪ128byte*/
			SPROG_ADDR_L = (page<<7)&0x80;
			SPROG_ADDR_H |= (page>>1)&0x03;//ѡ��Ҫҳ��ַ
			
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			if(!gf_ea_close)
				EA = 1;//�����ж�		
		}
		
		//-----------------------------------------------------------------//
	//�������ƣ� bit Eeprom_Page_Write_Word(uchar page,uint addr,uint write_word)
	//�������ܣ� Eeprom Sector д����
	//��������� uchar page(0~7):ѡ��ҳ��uint addr:(0~63)��uint write_word����Ҫд�������;
	//��������� ��
	//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
	//-----------------------------------------------------------------//
	
		
		bit Eeprom_Page_Write_Word(uchar page,uint addr,uint write_word)
		{	
			bit Write_OK = 0;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			
			/*cubic ��ַ=page*128,һҳΪ128byte*/
			SPROG_ADDR_L = (page<<7)&0x80;
			SPROG_ADDR_H |= (page>>1)&0x03;//ѡ��page��ַ
			
			/*cubic дΪ�ֽ�д����ַ����Ϊż������ԭ�����õĵ�ַ��Ϊԭ����һ��*/
			SPROG_ADDR_L |= (addr<<1)&0x7F;//ѡ��д��ַ
			
			
			SPROG_DATA = write_word>>8;	//׼��д������ݸ߰�λ
			SPROG_DATA = write_word;//׼��д������ݵͰ�λ
			
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC����ʹ�ܹر�
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
				EA = 1;//�����ж�
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Eeprom_Page_Read_Word(uchar page,uint addr)
		//�������ܣ� Eeprom����page������
		//��������� uchar page:0~7,ѡ��page0~page7;uint addr(0~63)����ȡpage��addr ˫�ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�page��addr ˫�ֽ� �����ݣ�
		//-----------------------------------------------------------------//
		uint Eeprom_Page_Read_Word(uchar page,uint addr)
		{	
			uint code  * p;
			/*cubic дΪ�ֽ�д����ַ����Ϊż������ԭ�����õĵ�ַ��Ϊԭ����һ��*/
			p = 0x8000 + (page*128 + (addr<<1)) - eep_addr_offset;
			return *p;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Eeprom_Page_Read_Byte(uchar page,uint addr)
		//�������ܣ� Eeprom����page������
		//��������� uchar page:0~7,ѡ��page0~page7;uint addr(0~127)����ȡpage��addr���ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�page��addr���ֽڵ����ݣ�
		//-----------------------------------------------------------------//
		uchar Eeprom_Page_Read_Byte(uchar page,uint addr)
		{	
			uchar code  * p;
			p = 0x8000 + (page*128 + (addr)) - eep_addr_offset;
			return *p;
		}


#if	(EEPROM_LVD_WORK)
/*-----------------------------------------------------------------
�������ƣ� void eeprom_read_deal(void)
�������ܣ� EEPROM�ϵ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/	
	void	eeprom_read_deal(void)
	{
		uchar	i;
		uchar	len;

		//��
		len=c_eeprom_dataLength;
		i=0;
		EA = 0;//�����жϣ�

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
		//��д
		b_eeprom_layer=2;		
		b_eeprom_waitTime=0;
		EA = 1;//�����ж�
		
	}


/*-----------------------------------------------------------------
�������ƣ� void eeprom_erase_deal(void)
�������ܣ� EEPROM�ϵ��
��������� ��
�� �� ֵ�� ��
ʹ��ע��:  ��ѹʱ���²�д�����û����ѹ�ж�����д���ݺ��500ms~1000ms
���ٴβ��գ���ֹ�����д��������˵��ǵ�ѹ�����»ָ��������������
�´ε�ѹ�ٴ��½�ʱ����д����Ч
-----------------------------------------------------------------*/	
	void eeprom_erase_deal(void)
	{
		if(b_eeprom_layer!=2)	return;
		Eeprom_Page_Erase(0);
		b_eeprom_layer=4;

	}




/*-----------------------------------------------------------------
�������ƣ� void eeprom_write_deal(void)
�������ܣ� EEPROM����д
��������� ��
�� �� ֵ�� ��
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
				//���ֽ��ڵ�λ�����ֽ��ڸ�λ
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
�������ƣ� void eeprom_deal(void)
�������ܣ� EEPROM����-�ǵ���д
��������� ��
�� �� ֵ�� ��
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
					//д֮ǰ�Ȳ�
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
						//���ֽ��ڵ�λ�����ֽ��ڸ�λ
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
