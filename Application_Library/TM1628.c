	#include 	"..\Application_Library\Global.h"

#if	(c_TM1628_EN|| c_TM1629_EN)

	void	delayus_1628();
	void	sendData(unsigned char dat);
	void	TM1628_initSet();
	void	TM1628_disON(unsigned char i);
	void	TM1628_sendAddrData(unsigned char addr,unsigned char dat);
	unsigned char	xdata	gb_disIcData[c_1628_dataNum];


/*-----------------------------------------------------------------
�������ƣ� void	TM1628_send14Data(void)
�������ܣ� ����ʾ�����͵�1628����ʾ����
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
	void	TM1628_sendData()
	{
		unsigned char	i;

		TM1628_initSet();

		for(i=0;i<c_1628_dataNum;i++)
		{
			sendData(gb_disIcData[i]);
		}

		TM1628_disON(c_1628_lightGrade);	
	}



/*-----------------------------------------------------------------
�������ƣ� void	TM1628_initSet(void)
�������ܣ� ����1628��ʹ�ò���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
	void	TM1628_initSet()
	{
		p_1628stb_h;
		sendData(c_1628_lightMode);

		p_1628stb_h;
		sendData(c_1628_dataWrite);

		p_1628stb_h;
		sendData(c_1628_initAddr);

	}


/*-----------------------------------------------------------------
�������ƣ� void	TM1628_disON(unsigned char i)
�������ܣ� ��1628��ʾ������������
��������� ����ֵ
�� �� ֵ�� ��
-----------------------------------------------------------------*/
	void	TM1628_disON(unsigned char i)
	{
		p_1628stb_h;
		sendData(i);
		p_1628stb_h;
	}


/*-----------------------------------------------------------------
�������ƣ� void	TM1628_sendAddrData(unsigned char	addr,unsigned char	dat)
�������ܣ� ��1628���ض���ַ������
��������� ��ֵַ������
�� �� ֵ�� ��
-----------------------------------------------------------------*/
/*
	void	TM1628_sendAddrData(unsigned char	addr,unsigned char	dat)
	{
		p_1628stb_h;
		sendData(addr);
		delayus_1628();
		sendData(dat);
	}
*/	


/*-----------------------------------------------------------------
�������ƣ� void	sendData(unsigned char dat)
�������ܣ� ��8λ��������1628
��������� ����1628��8λ����
�� �� ֵ�� ��
-----------------------------------------------------------------*/
	void	sendData(unsigned char dat)
	{
		unsigned char	i;
		p_1628clk_l;
		delayus_1628();
		p_1628stb_l;

		for(i=0x01;i!=0;i<<=1)
		{
			delayus_1628();
			if(dat&i)
			{
				p_1628dio_h;
			}
			else
			{
				p_1628dio_l;
			}
			p_1628clk_h;
			delayus_1628();
			p_1628clk_l;

		}
	}


/*-----------------------------------------------------------------
�������ƣ� void	delayus_1628(void)
�������ܣ� ��ʱ
��������� ��ʱʱ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
	void	delayus_1628()
	{
		unsigned char	t=12;
		
		while(t>0)
		{
			t--;
		}
	}
	

#endif




















