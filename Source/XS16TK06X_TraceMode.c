#include "Config.h"

#if (TRACEMODE == TRUE)
void TraceMode_Master_Read_Data(unsigned int *p_rawData,unsigned int *p_baseline,unsigned long t_keysFlagSN);   
unsigned char data ReadCnt = 0;
unsigned char data ReceData = 0;
unsigned char data DataNum = 0;
bit OddCheck = 0,NeedCheckOdd = 0;
unsigned int xdata raw = 0;
unsigned int xdata bas = 0;


//-----------------------------------------------------------------//
//�������ƣ� void TraceMode_Master_Write_Data(void)  
//�������ܣ� ��IICBUF��ȡ����
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#pragma disable
void TraceMode_Master_Write_Data(void) 
{   
	ReceData = IICBUF;
}


//#pragma message "����,TRACEMODE����"
unsigned long xdata keys_flag_Tracemode = 0;	

//-----------------------------------------------------------------//
//�������ƣ� void Trace_Mode_IIC_ISR_PA() interrupt 10 
//�������ܣ� PA��IIC�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Trace_Mode_IIC_ISR_PA() interrupt 10
{
		uchar tmp;
		IRCON1 &= ~0x08;//IIC_INT_FLAG_CLR;//���IIC�жϱ�־λ

		if (IICSTAT & 0x02)//IICS_WCOL//д��ͻ��־λ
		{ 
				IICSTAT &= ~0x02;//IICS_WCOL_CLR;
		}
		if (IICSTAT & 0x01)//IICS_RECOV//����ͻ��־λ  
		{
				IICSTAT &= ~0x01;//IICS_RECOV_CLR;
				tmp = IICBUF;
		}
		if ((IICSTAT & 0x10)==0)//(IICS_AD == 0)//�ǵ�ַ
		{	 
		
				if (IICSTAT & 0x20)//IICS_RW//������ 
				{
						ReadCnt = 0;
						OddCheck = 0;
						DataNum = 0;
						TraceMode_Master_Read_Data(raw_data,base_line,keys_flag_Tracemode);
						IICCON |= 0x04;//SCLEN_SET; 
				}
				else //����д
				{
						tmp = IICBUF;
				}   
			}
			else 
			{
				if (IICSTAT & 0x20)//IICS_RW//������ 
				{     
					TraceMode_Master_Read_Data(raw_data,base_line,keys_flag_Tracemode);
					IICCON |= 0x04;//SCLEN_SET; 	  
				}
				else//����д  
				{   
			
					if (IICSTAT & 0x08)//IICS_BF 
					{ 
						TraceMode_Master_Write_Data();
					}
				}
		}
		IICCON |= 0x04;//SCLEN_SET; 	
}

//-----------------------------------------------------------------//
//�������ƣ� void XS16TK06X_Trace_Mode_Init(uchar iic_port)   
//�������ܣ� XS16TK06X_Trace_Mode_Init��ʼ��
//��������� uchar iic_port,IIC�˿�ӳ��ѡ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void XS16TK06X_Trace_Mode_Init(uchar iic_port)
{
	
		EA = 0;//�����жϣ� 
		IPL1 |= 0x08; //����IIC�ж����ȼ�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
		IRCON1 &= ~0x08;//���IIC�жϱ�־λ 
	
		if(iic_port == 0)
		{
			TRISA |= 0x03;//����SDA��SCLΪ���룻(PA1/PA0-SDA0_A/SCL0_A)
		}
		else if(iic_port == 1)
		{
				TRISC |= 0x01;
				TRISB |= 0x20;//����SDA��SCLΪ���룻(PC0/PB5-SDA0_B/SCL0_B)
		}
		else if(iic_port == 2)
		{
				TRISD |= 0x40;
				TRISA |= 0x02;//����SDA��SCLΪ���룻(PD6/PA1-SDA0_C/SCL0_C)
					
		}
		
		IICADD = 0x54;//����IIC�ӻ���ַ��
	
		IICCON |= 0x01;//IIC����ʹ��
		IICCON |= (0x02);//IICת��������Ӧ100K
		IICCON |= 0x04;//SCLʱ����������
		IICCON &= (~0x08);//��ʹ��д����,����IIC������дʱ������
		IICCON |= (0x10);//ʹ�ܶ����ͣ�����IIC������дʱ������
	
		PERIPH_IO_SEL &= ~(0x60);
		PERIPH_IO_SEL |= (0x60&(1<<5));//bit[6:5];//1:Ϊ�����˲�(Sleepģʽ���޻��ѹ���)��2Ϊģ���˲���3Ϊģ��������˲�
		REG_ADDR = 0x2C;REG_DATA = (0x03&(iic_port));//bit[1:0]:0:ӳ�䵽SDA0_A/SCL0_A��1:ӳ�䵽SDA0_B/SCL0_B��2:ӳ�䵽SDA0_C/SCL0_C��
		REG_ADDR = 0;
		IEN1 |= 0x08; //��IIC�ж�ʹ��
		EA = 1;//�����жϣ�
	
}
//-----------------------------------------------------------------//
//�������ƣ� void TraceMode_Master_Read_Data(uint *p_rawData,uint *p_baseline,ulong t_keysFlagSN)   
//�������ܣ� �����͵�����д��IICBUF
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//

#pragma disable
void TraceMode_Master_Read_Data(unsigned int *p_rawData,unsigned int *p_baseline,unsigned long t_keysFlagSN)    
{   
	unsigned char data tmp = 0;

	if(ReceData == 0xb2)
	{
		if(ReadCnt == 0)
			tmp = 0xae;
		else if(ReadCnt == 1)
			tmp = CH_MAX;		
	}
	else if(ReceData == 0xb3)
	{
		if(ReadCnt < 1)			//����ͷ��0XAE
		{
			tmp = 0xae;			
		}
		else if(ReadCnt < ((CH_MAX<<1) + 1))	//����RAWDATA
		{
			NeedCheckOdd = 1;
			if(ReadCnt % 2)	
			{
				raw = *(p_rawData + DataNum);
				tmp = (raw >> 8);
			}
			else
			{
				tmp = raw;
				DataNum ++;	
			}
		}
		else if(ReadCnt == ((CH_MAX << 1) + 1))  //����BASELINE[0]��8λ
		{
			NeedCheckOdd = 1;
			DataNum = 0;
			bas = *(p_baseline + DataNum);
			tmp = (bas >> 8);
		}
		else if(ReadCnt < ((CH_MAX << 2) + 1))		//����BASELINE
		{
			
			NeedCheckOdd = 1;
			if(ReadCnt % 2)	
			{
				bas = *(p_baseline + DataNum);
				tmp = (bas >> 8);
			}
			else
			{
				tmp = bas;  
				DataNum++;	
			}
			
		} 
		else if(ReadCnt == ((CH_MAX << 2) + 1))		//������żУ��λ
		{
			tmp = OddCheck;
			
		}
		else if(ReadCnt == ((CH_MAX << 2) + 2))		//������Ч���ݳ���
		{						
			tmp = (CH_MAX << 2);
		}				
		else if(ReadCnt == ((CH_MAX << 2) + 2))		//������Ч���ݳ���
		{						
			tmp = (CH_MAX << 2);
		}				
		else if(ReadCnt == ((CH_MAX << 2) + 3))		//������־λbit31:17
		{ 						
			tmp = (unsigned char )(t_keysFlagSN >> 24);
		}
		else if(ReadCnt == ((CH_MAX << 2) + 4))		//������־λbit23:16
		{ 						
			tmp = (unsigned char )(t_keysFlagSN >> 16);
		}
		else if(ReadCnt == ((CH_MAX << 2) + 5))		//������־λbit15:8
		{						 
			tmp = (unsigned char )(t_keysFlagSN >> 8);
			
		}
		else if(ReadCnt == ((CH_MAX << 2) + 6))		//������־λbit7:0
		{						
			tmp = (unsigned char )t_keysFlagSN;						
		}									
		else																		//���ͽ�����0xff��0xff
		{						
			tmp = 0xff;	
		}
	}

	IICBUF = tmp;
	
	if(NeedCheckOdd)		//��ǰ�����Ƿ���Ҫ������żУ��
	{
		NeedCheckOdd = 0;
		
		ACC = tmp;
		if((PSW & 0x01))
			OddCheck = !OddCheck;
	}
	ReadCnt ++;
}

#endif