	#include 	"..\Application_Library\Global.h"

#if	(c_TM1628_EN|| c_TM1629_EN)

	void	delayus_1628();
	void	sendData(unsigned char dat);
	void	TM1628_initSet();
	void	TM1628_disON(unsigned char i);
	void	TM1628_sendAddrData(unsigned char addr,unsigned char dat);
	unsigned char	xdata	gb_disIcData[c_1628_dataNum];


/*-----------------------------------------------------------------
函数名称： void	TM1628_send14Data(void)
函数功能： 将显示数据送到1628内显示出来
输入参数： 无
返 回 值： 无
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
函数名称： void	TM1628_initSet(void)
函数功能： 配置1628的使用参数
输入参数： 无
返 回 值： 无
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
函数名称： void	TM1628_disON(unsigned char i)
函数功能： 开1628显示并且配置亮度
输入参数： 亮度值
返 回 值： 无
-----------------------------------------------------------------*/
	void	TM1628_disON(unsigned char i)
	{
		p_1628stb_h;
		sendData(i);
		p_1628stb_h;
	}


/*-----------------------------------------------------------------
函数名称： void	TM1628_sendAddrData(unsigned char	addr,unsigned char	dat)
函数功能： 往1628的特定地址送数据
输入参数： 地址值和数据
返 回 值： 无
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
函数名称： void	sendData(unsigned char dat)
函数功能： 将8位数据送入1628
输入参数： 送入1628的8位数据
返 回 值： 无
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
函数名称： void	delayus_1628(void)
函数功能： 延时
输入参数： 延时时间
返 回 值： 无
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




















