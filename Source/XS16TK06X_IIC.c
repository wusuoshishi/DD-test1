#include "Config.h"

#if IICS_EN
	uint data  IICS_PA_Soft_Cnt = 0;
	uint xdata SCLEN_SoftCnt = 0; 
#endif


	#if IICS_EN
		#if (TRACEMODE==0)
		
		//-----------------------------------------------------------------//
		//�������ƣ� void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		//�������ܣ� IIC�ӻ���ʼ��
		//��������� uchar IICSlaveAddr:IIC�ӻ���ַ,iic_port:0:(PA1/PA0-SDA0_A/SCL0_A),1:(PC0/PB5-SDA0_B/SCL0_B),2:(PD6/PA1-SDA0_C/SCL0_C)
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//

		void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		{
			EA = 0;//�����ж�;
			IIC_IP_SET; //����IIC�ж����ȼ�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			IIC_INT_FLAG_CLR;//���IIC�жϱ�־λ 
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
			
			IICADD = IICSlaveAddr;//����IIC�ӻ���ַ��
			
			IICCON |= IIC_EN;//IIC����ʹ��
			IICCON |= (IIC_SR);//IICת��������Ӧ100K
			IICCON |= IIC_SCLEN;//SLCʱ����������
			IICCON &= (~IIC_W_SCL_EN);//��ʹ��д����,����IIC������дʱ������
			IICCON |= (IIC_R_SCL_EN);//ʹ�ܶ����ͣ�����IIC������дʱ������
			IIC_FIL_SEL(1);//1:Ϊ�����˲�(�������˲���Sleepģʽ���޻��ѹ���)��2Ϊģ���˲���3Ϊģ��������˲�(�������˲���Sleepģʽ���޻��ѹ���);
			IIC_IO_MAP(iic_port);//0:ӳ�䵽SDA0_A/SCL0_A��1:ӳ�䵽SDA0_B/SCL0_B��2:ӳ�䵽SDA0_C/SCL0_C��
			IIC_IE_SET; //��IIC�ж�ʹ��
			EA = 1;//�����жϣ�
		}
		//-----------------------------------------------------------------//
		//�������ƣ� void Master_Read_Data()  
		//�������ܣ� �����͵�����д��IICBUF
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Master_Read_Data()    
		{   
			uchar tmp;
			IICBUF = tmp;
			SCLEN_SET;
		}
		//-----------------------------------------------------------------//
		//�������ƣ� void Master_Write_Data()  
		//�������ܣ� ��IICBUF��ȡ����
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Master_Write_Data() 
		{   
			uchar tmp;
			tmp = IICBUF;
		} 
		//-----------------------------------------------------------------//
		//�������ƣ� void IIC_ISR_PA() interrupt 10 
		//�������ܣ� PA��IIC�ж��Ӻ���
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void IIC_ISR_PA() interrupt 10
		{
				uchar tmp;
				IIC_INT_FLAG_CLR;//���IIC�жϱ�־λ
				if((IICCON & 0x10) == 0)
				{
					IICCON |= (IIC_R_SCL_EN);//ʹ�ܶ����ͣ�����IIC������дʱ������
				}
				
				if (IICS_WCOL)//д��ͻ��־λ
				{ 
						IICS_WCOL_CLR;
				}
				if (IICS_RECOV)//����ͻ��־λ  
				{
						IICS_RECOV_CLR;
						tmp = IICBUF;
				}
				if (IICS_AD == 0)//�ǵ�ַ
				{	 
				
						if (IICS_RW)//������ 
						{
				
								Master_Read_Data();
								SCLEN_SET; 
						}
						else //����д
						{
								tmp = IICBUF;
						}   
					}
					else 
					{
						if (IICS_RW)//������ 
						{        
								Master_Read_Data();
								SCLEN_SET;	  
						}
						else//����д  
						{   
							if (IICS_BF) 
							{ 
								Master_Write_Data();
							}
						}
				}
				SCLEN_SET;
		}
		
		#endif
	#endif//PA_SLAVE
