#include "Config.h"


//#if ((UART0_EN == 1)||(UART1_EN == 1))
///****************************************************************/
////��������uchar UART_Rece_Check(uchar n,uchar *nSendByte)  
////��  �ܣ�UART����У��
////��  ����uchar n:����У���ֽ�����uchar *nCheckByte1,uchar *nCheckByte2
////����ֵ��1:У�鲻ͨ����0:У��ͨ��
///****************************************************************/
//uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2)  
//{
//	uchar i = 0;
//	for(i = 0; i < n; i++)
//	{
//		if((*(nCheckByte1 + i)) != (*(nCheckByte2 + i)))
//		{
//				return 1;
//		}
//	}	
//	return 0;
//}
//#endif

#if (UART0_EN == 1)


	
	//-----------------------------------------------------------------//
	//�������ƣ� void UART0_Init(void)  
	//�������ܣ� UART0��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void UART0_Init(void) 
	{ 
			EA = 0;//�����жϣ�
			UART0_IP_SET;//����UART0�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�

			UART0_INT_FLAG_CLR;//���UART0�жϱ�־
		
			UART0_RX_EN_SET(1);//������ʹ�� ,1Ϊʹ�ܣ�0Ϊ��ֹ
			UART0_MULTI_SET(0);//�ദ����ͨ��ʹ��,1Ϊʹ�ܣ�0Ϊ��ֹ
			UART0_SEND_MODE_SET(0);//��������ģʽbit[3]��0��8λģʽ��1��9λģʽģʽ
			UART0_STOP_MODE_SET(0);//STOPλ ,1Ϊ2λSTOP��0Ϊ1λSTOP
			UART0_OD_EN_SET(0);//��żУ��ʹ�� ,1Ϊʹ�ܣ�ʹ����żУ��ʱ�迪��9λ����ģʽ����0Ϊ��ʹ��
			UART0_OD_SET(0);//��żУ��ѡ�� ,1Ϊ��У�飬0ΪżУ��
		
			UART0_RX_FUN_SET(0);//UART0���Ž��չ���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ
			UART0_TX_FUN_SET(0);//UART0���ŷ��͹���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ
		
			UART0_PC_SET(UART0_PAD_CHANGE);//TX/RX���Ź��ܻ���,1Ϊ���ܻ�����0Ϊ���ܲ�����

			UART0_BDL = (uchar)M_HEX_OF_BR(UART0_CFG_BAUD_RATE);//���ò�����=BUSCLK/(16*(UART_BDH[0:1],UART_BDL))
			UART0_CON2 |= (((((uint)(M_HEX_OF_BR(UART0_CFG_BAUD_RATE)))>>8)&0x03));//����UART0_BDH[0:1]����λ
			UART0_TX_IE_SET(1);//UART0�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			UART0_RX_IE_SET(1);//UART0�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			
			UART0_PORT_SET(UART0_PORT);//UART0 RX/TXӳ��ѡ��,0:PA0/PA1;1:PB3/PB4��2/3:PC0/PC1;4:PD6/PA1,5:PD7/PA0��6/7��PD4/PD5
	
		#if(UART0_PORT == UART0_MAP_A) //0
			#if UART0_PAD_CHANGE
			TRISA |=  0x02;//����TXΪ����
			TRISA &= ~0x01;//����RXΪ���
			SET_PA1_PU_ON; //������
			#else 
			TRISA &= ~0x02;//����TXΪ���
			TRISA |= 0x01;//����RXΪ����
			SET_PA0_PU_ON; //������
			#endif
		#elif(UART0_PORT == UART0_MAP_B)//1
			#if UART0_PAD_CHANGE
			TRISB |=  0x10;//����TXΪ����
			TRISB &= ~0x08;//����RXΪ���
			SET_PB4_PU_ON; //������;
			#else 
			TRISB &= ~0x10;//����TXΪ���
			TRISB |=  0x08;//����RXΪ����
			SET_PB3_PU_ON; //������;
			#endif
		#elif(UART0_PORT == UART0_MAP_C)//6
			#if	(UART0_PAD_CHANGE)
				TRISD |= 0x20;//����RXΪ����	
				TRISD &= ~0x10;//����TXΪ���
				SET_PD5_PU_ON; //������
			#else			
				TRISD &= ~0x20;//����TXΪ���
				TRISD |= 0x10;//����RXΪ����
				SET_PD4_PU_ON; //������
			#endif
		#elif(UART0_PORT == UART0_MAP_D)//2
			#if UART0_PAD_CHANGE
			TRISC |=  0x02;//����TXΪ����
			TRISC &= ~0x01;//����RXΪ���
			SET_PC1_PU_ON; //������
			#else 
			TRISC &= ~0x02;//����TXΪ���
			TRISC |= 0x01;//����RXΪ����
			SET_PC0_PU_ON; //������
			#endif
		#elif(UART0_PORT == UART0_MAP_E)//4
			#if UART0_PAD_CHANGE
			TRISA |=  0x02;//����TXΪ����
			TRISD &= ~0x40;//����RXΪ���
			SET_PA1_PU_ON; //������
			#else 
			TRISA &= ~0x02;//����TXΪ���
			TRISD |= 0x40;//����RXΪ����
			SET_PD6_PU_ON; //������
			#endif
		#elif(UART0_PORT == UART0_MAP_F) //5
			#if UART0_PAD_CHANGE
			TRISA |=  0x01;//����TXΪ����
			TRISD &= ~0x80;//����RXΪ���
			SET_PA0_PU_ON; //������
			#else 
			TRISA &= ~0x01;//����TXΪ���
			TRISD |= 0x80;//����RXΪ����
			SET_PD7_PU_ON; //������
			#endif
		#else

		#endif
	

		TI0 = 0;//��������жϱ�־λ
		RI0 = 0;//��������жϱ�־λ
		UART0_IE_SET;//��UART�ж�ʹ��	
		UART0_MODULE_SET(1);//UAERT0ģ�鿪��,1Ϊ����0Ϊ��
		
		EA = 1;//�����ж�
	}
	
	// #pragma disable 
	void UART0_Send_Word(uint willSendWord)   
	{
			UART0_Send_Byte(willSendWord>>8);
			UART0_Send_Byte(willSendWord);
	}
		#pragma message "����,UART0����"
		/****************************************************************/
		//��������void UART0_Send_NByte(uchar n,uchar *nSendByte)  
		//��  �ܣ�UART0����N BYTES
		//��  ����uchar n:�����ֽ�����uchar *nSendByte����������ָ��
		//����ֵ����
		/****************************************************************/
	// #pragma disable 
		void UART0_Send_NByte(uchar n,uchar *nSendByte)  
		{
				uchar i = 0;
				for(i = 0; i < n; i++)
				{
					UART0_Send_Byte(*(nSendByte + i));
				}		
		}	
	// #pragma disable 
	void UART0_Send_Byte(uchar willSendByte)  
	{
			UART0_STATE = 0x0F;//��������жϱ�־λ
			UART0_TX_IE_SET(0);//UART0�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			UART0_BUF = willSendByte;
			if(UART0_CON1 & 0x40)
			{
				while(TI0 == 0);
				UART0_STATE = 0x0F;//��������жϱ�־λ
			}
	}
	
	
	/* ����0�жϷ����ӳ��� */
	void UART0_ISR() interrupt 16
	{    
			unsigned char temp;	
			UART0_INT_FLAG_CLR;//���UART0�жϱ�־	
			if(RI0 == 1)
			{
					UART0_STATE = 0x17;//��������жϱ�־λ
					temp = UART0_BUF;
			} 

			if(TI0 == 1)
			{
					UART0_STATE = 0x0F;//��������жϱ�־λ
					
			}   
	}

#endif
	
#if (UART1_EN == 1)

	// #pragma disable 
	void UART1_Send_Word(uint willSendWord)   
	{
			UART1_Send_Byte(willSendWord>>8);
			UART1_Send_Byte(willSendWord);
	}
	
	#pragma message "����,UART0����"
	/****************************************************************/
	//��������void UART1_Send_NByte(uchar n,uchar *nSendByte)  
	//��  �ܣ�UART1����N BYTES
	//��  ����uchar n:�����ֽ�����uchar *nSendByte����������ָ��
	//����ֵ����
	/****************************************************************/
	// #pragma disable 
	void UART1_Send_NByte(uchar n,uchar *nSendByte)  
	{
			uchar i = 0;
			for(i = 0; i < n; i++)
			{
				UART1_Send_Byte(*(nSendByte + i));
			}		
	}
	// #pragma disable 
	void UART1_Send_Byte(uchar willSendByte)  
	{
			UART1_STATE = 0x0F;//��������жϱ�־λ
			UART1_TX_IE_SET(0);//UART0�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			UART1_BUF = willSendByte;
			if(UART1_CON1 & 0x40)
			{
				while(TI1 == 0);
				UART1_STATE = 0x0F;//��������жϱ�־λ
			}
	}

	//-----------------------------------------------------------------//
	//�������ƣ� void UART1_Init(void)  
	//�������ܣ� UART1��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void UART1_Init(void) 
	{ 
			EA = 0;//�����жϣ�
			UART1_IP_SET;//����UART1�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			UART1_INT_FLAG_CLR;//���UART1�жϱ�־
	
			UART1_RX_EN_SET(1);//������ʹ�� ,1Ϊʹ�ܣ�0Ϊ��ֹ
			UART1_MULTI_SET(0);//�ദ����ͨ��ʹ��,1Ϊʹ�ܣ�0Ϊ��ֹ
			UART1_SEND_MODE_SET(0);//��������ģʽbit[3]��0����λģʽ��1��9λģʽģʽ
			UART1_STOP_MODE_SET(0);//STOPλ ,1Ϊ2λSTOP��0Ϊ1λSTOP
			UART1_OD_EN_SET(0);//��żУ��ʹ�� ,1Ϊʹ�ܣ�ʹ����żУ��ʱ�迪��9λ����ģʽ����0Ϊ��ʹ��
			UART1_OD_SET(0);//��żУ��ѡ�� ,1Ϊ��У�飬0ΪżУ��
		
			UART1_RX_FUN_SET(0);//UART1���Ž��չ���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ
			UART1_TX_FUN_SET(0);//UART1���ŷ��͹���ʹ��,0Ϊʹ�ܣ�1Ϊ��ֹ
		
			UART1_PC_SET(UART1_PAD_CHANGE);//TX/RX���Ź��ܻ���,1Ϊ���ܻ�����0Ϊ���ܲ�����
	
			UART1_BDL = (uchar)M_HEX_OF_BR(UART1_CFG_BAUD_RATE);//���ò�����=BUSCLK/(16*(UART_BDH[0:1],UART_BDL))
			UART1_CON2 |= (((((uint)(M_HEX_OF_BR(UART1_CFG_BAUD_RATE)))>>8)&0x03));//����UART1_BDH[0:1]����λ
		
			UART1_TX_IE_SET(1);//UART1�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			UART1_RX_IE_SET(1);//UART1�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			
			UART1_PORT_SET(UART1_PORT);//UART1 RX/TXӳ��ѡ��,0:PB1/PB2;1:PB6/PB7
			
		#if(UART1_PORT == UART1_MAP_A) //0
			#if UART1_PAD_CHANGE
				TRISB |=  0x04;//����TXΪ����
				TRISB &= ~0x02;//����RXΪ���
				SET_PB2_PU_ON; //������
			#else
				TRISB &= ~0x04;//����TXΪ���
				TRISB |= 0x02;//����RXΪ����
				SET_PB1_PU_ON; //������
			#endif
		#elif(UART1_PORT == UART1_MAP_B)//1
			#if UART1_PAD_CHANGE
			TRISB |=  0x80;//����TXΪ����
			TRISB &= ~0x40;//����RXΪ���
			SET_PB7_PU_ON; //������
			#else
			TRISB &= ~0x80;//����TXΪ���
			TRISB |= 0x40;//����RXΪ����
			SET_PB6_PU_ON; //������
			#endif
		#else

		#endif
		
		TI1 = 0;//��������жϱ�־λ
		RI1 = 0;//��������жϱ�־λ

		UART1_IE_SET;//��UART�ж�ʹ��	
		UART1_MODULE_SET(1);//UAERT1ģ�鿪��,1Ϊ����0Ϊ��
		
		EA = 1;//�����ж�
	}
	
	/* ����1�жϷ����ӳ��� */
	void UART1_ISR() interrupt 17
	{    
			unsigned char temp;	
			
			UART1_INT_FLAG_CLR;//���UART1�жϱ�־		
			if(RI1 == 1)
			{
					UART1_STATE = 0x17;//��������жϱ�־λ
					temp = UART1_BUF;
			} 

			if(TI1 == 1)
			{
					UART1_STATE = 0x0F;//��������жϱ�־λ
			}   
	}

#endif

