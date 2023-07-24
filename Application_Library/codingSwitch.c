
#include 	"..\Application_Library\Global.h"

#include    <intrins.h>
#include 	"codingSwitch.h"	
#include	"codingSwitch_user.h"	

#if	(c_codingSwitch_en&&c_codingSwitch_user_en)	

	typedef	struct
	{
		uchar	status;			//用于存储一个周期里的值,初始化为0x03
		uchar	order;			//次数计数,一个周期有4次
		uchar	value;			//0:无动作,1:正转,2:反转
		uchar	getOne;			//1:获取了旋转值
		uchar	io_differCnt;	//消抖计数
	}str_codingSwitch;

	str_codingSwitch	idata	bs_codingSwitch;
	str_codingSwitch	idata	bs_codingSwitch2;


/***********************************************************
;函数名称:void	codingSwitch_init(void)
;函数功能:IO口及变量初始化
;输入参数:无
;输出参数:无	
;使用注意:
;--------
;---------
;---------
;**********************************************************/
	void	codingSwitch_init(void)
	{	
		/*用到的IO口都设为上拉输入*/
		/*旋转编码开关1 A*/
		p_codingSwitch_io1_in;
		p_codingSwitch_io1_pull;
		p_codingSwitch_io1_h;

		/*旋转编码开关1 B*/
		p_codingSwitch_io2_in;
		p_codingSwitch_io2_pull;
		p_codingSwitch_io2_h;

		/*旋转编码开关2 A*/
		p_codingSwitch_io3_in;
		p_codingSwitch_io3_pull;
		p_codingSwitch_io3_h;

		/*旋转编码开关2 B*/
		p_codingSwitch_io4_in;
		p_codingSwitch_io4_pull;
		p_codingSwitch_io4_h;




		/*结构体初始化*/
		//memset(&bs_codingSwitch,0,sizeof(str_codingSwitch));
		bs_codingSwitch.status=0;		
		bs_codingSwitch.order=0;		
		bs_codingSwitch.value=0;		
		bs_codingSwitch.getOne=0;		
		bs_codingSwitch.io_differCnt=0;

		bs_codingSwitch2.status=0;		
		bs_codingSwitch2.order=0;		
		bs_codingSwitch2.value=0;		
		bs_codingSwitch2.getOne=0;		
		bs_codingSwitch2.io_differCnt=0;



		bs_codingSwitch.status=0x03;
		bs_codingSwitch2.status=0x03;
	}




/***********************************************************
;函数名称:void	codingSwitch_distinguish(uchar cmd)
;函数功能:设置编码开关工作状态
;输入参数:cmd
		 0:disable
		 1:enable
;输出参数:		
;使用注意:放于定时中断
;--------
;---------
;---------
;**********************************************************/
	void	codingSwitch_distinguish(uchar cmd)
	{			
		static	uchar	i;		//本中断获取的编码值
		static	uchar	buf;	//上一个中断获取的编码值

		/*如果不使能编码开关工作,则默认AB都为高*/
		if(cmd==0)
		{
			i=0x03;
			buf=0x03;
			bs_codingSwitch.order=0;
			bs_codingSwitch.status=0x03;	
			bs_codingSwitch.value=0;		//0无动作
	
			bs_codingSwitch.io_differCnt=0;		//消抖计数
			return;
		}

		/*这里的io1代表的是A,io2代表的是B*/
		if(p_codingSwitch_io1_get)
		{
			i |=0x02;					
		}
		else
		{
			i &=~0x02;
		}
		
		if(p_codingSwitch_io2_get)
		{
			i |=0x01;	
		}
		else
		{
			i &=~0x01;			
		}

		if((bs_codingSwitch.status&0x03)!=i)	//获取的值,对比前一个消抖后的值有改变则进入
		{
			if(i==buf)	//本次获取的编码值和上次获取的编码值一样,说明没有抖动
			{
				if(++bs_codingSwitch.io_differCnt>=c_codingSwitch_ioShake)		//消抖计数
				{	
					bs_codingSwitch.io_differCnt=0;		//清 消抖计数
					/*************消抖完成,i存储的是可用的数据******************/
					/*整体右移两位,低两位用来存储当前1次编码值*/
					bs_codingSwitch.status <<=2;		
					bs_codingSwitch.status +=i;	
					if(++bs_codingSwitch.order==4)
					{
						/*正常来说,测得bs_codingSwitch.status数值为 
						顺:
						01001011 
						ABABABAB
						
						逆
						10000111
						ABABABAB
						
						*/
					#if	(c_codingSwitch_strengthenMode==0)		//检测强度等级0~2，值越大抗干扰性越强但也许会此出现小概率的漏检
						bs_codingSwitch.status=bs_codingSwitch.status&0xf0;
						if(bs_codingSwitch.status==b(01000000))
						{				
							bs_codingSwitch.value=1;
						}
						else if(bs_codingSwitch.status==b(10000000))
						{
							bs_codingSwitch.value=2;
						}
						else
						{
							bs_codingSwitch.value=0;
						}
					#elif	(c_codingSwitch_strengthenMode==1)	//检测强度等级0~2，值越大抗干扰性越强但也许会此出现小概率的漏检
						bs_codingSwitch.status=bs_codingSwitch.status&0xfc;	//1111 1100
						if(bs_codingSwitch.status==b(01001000))
						{				
							bs_codingSwitch.value=1;	//1:正转
						}
						else if(bs_codingSwitch.status==b(10000100))
						{
							bs_codingSwitch.value=2;	//2:反转
						}
						else
						{
							bs_codingSwitch.value=0;	//0:无动作
						}
					#else										//检测强度等级0~2，值越大抗干扰性越强但也许会此出现小概率的漏检
						if(bs_codingSwitch.status==b(01001011))
						{				
							bs_codingSwitch.value=1;
						}
						else if(bs_codingSwitch.status==b(10000111))
						{
							bs_codingSwitch.value=2;
						}
						else
						{
							bs_codingSwitch.value=0;
						}	
					#endif		
						bs_codingSwitch.order=0;		//次数计数,一个周期有4次
						bs_codingSwitch.status=0x03;	//用于存储一个周期里的值,初始化为0x03
						bs_codingSwitch.getOne=1;		//1:获取了旋转值
							
					}
					else
					{
						//不是第4次却读到11则认为错误重新开始读取
						if(i==0x03)
						{
							bs_codingSwitch.order=0;
							bs_codingSwitch.status=0x03;	
						}

					}
				}
			}
			else
			{
				buf=i;
				bs_codingSwitch.io_differCnt=0;		//消抖计数
			}
		}
		else
		{
			bs_codingSwitch.io_differCnt=0;			//消抖计数
			buf=i;
		}
					
	}



/***********************************************************
;函数名称:void	codingSwitch_distinguish2(uchar cmd)
;函数功能:设置编码开关工作状态(旋转编码开关2)
;输入参数:cmd
		 0:disable
		 1:enable
;输出参数:		
;使用注意:放于定时中断
;--------
;---------
;---------
;**********************************************************/
	void	codingSwitch_distinguish2(uchar cmd)
	{			
		static	uchar	i;		//本中断获取的编码值
		static	uchar	buf;	//上一个中断获取的编码值

		/*如果不使能编码开关工作,则默认AB都为高*/
		if(cmd==0)
		{
			i=0x03;
			buf=0x03;
			bs_codingSwitch2.order=0;
			bs_codingSwitch2.status=0x03;	
			bs_codingSwitch2.value=0;		//0无动作
	
			bs_codingSwitch2.io_differCnt=0;		//消抖计数
			return;
		}

		/*这里的io3代表的是A,io4代表的是B*/
		if(p_codingSwitch_io3_get)
		{
			i |=0x02;					
		}
		else
		{
			i &=~0x02;
		}
		
		if(p_codingSwitch_io4_get)
		{
			i |=0x01;	
		}
		else
		{
			i &=~0x01;			
		}

		if((bs_codingSwitch2.status&0x03)!=i)	//获取的值,对比前一个消抖后的值有改变则进入
		{
			if(i==buf)	//本次获取的编码值和上次获取的编码值一样,说明没有抖动
			{
				if(++bs_codingSwitch2.io_differCnt>=c_codingSwitch_ioShake)		//消抖计数
				{	
					bs_codingSwitch2.io_differCnt=0;		//清 消抖计数
					/*************消抖完成,i存储的是可用的数据******************/
					/*整体右移两位,低两位用来存储当前1次编码值*/
					bs_codingSwitch2.status <<=2;		
					bs_codingSwitch2.status +=i;	
					if(++bs_codingSwitch2.order==4)
					{
						/*正常来说,测得bs_codingSwitch.status数值为 
						顺:
						01001011 
						ABABABAB
						
						逆
						10000111
						ABABABAB
						
						*/
					#if	(c_codingSwitch_strengthenMode==0)		//检测强度等级0~2，值越大抗干扰性越强但也许会此出现小概率的漏检
						bs_codingSwitch2.status=bs_codingSwitch2.status&0xf0;
						if(bs_codingSwitch2.status==b(01000000))
						{				
							bs_codingSwitch2.value=1;
						}
						else if(bs_codingSwitch2.status==b(10000000))
						{
							bs_codingSwitch2.value=2;
						}
						else
						{
							bs_codingSwitch2.value=0;
						}
					#elif	(c_codingSwitch_strengthenMode==1)	//检测强度等级0~2，值越大抗干扰性越强但也许会此出现小概率的漏检
						bs_codingSwitch2.status=bs_codingSwitch2.status&0xfc;	//1111 1100
						if(bs_codingSwitch2.status==b(01001000))
						{				
							bs_codingSwitch2.value=1;	//1:正转
						}
						else if(bs_codingSwitch2.status==b(10000100))
						{
							bs_codingSwitch2.value=2;	//2:反转
						}
						else
						{
							bs_codingSwitch2.value=0;	//0:无动作
						}
					#else										//检测强度等级0~2，值越大抗干扰性越强但也许会此出现小概率的漏检
						if(bs_codingSwitch2.status==b(01001011))
						{				
							bs_codingSwitch2.value=1;
						}
						else if(bs_codingSwitch2.status==b(10000111))
						{
							bs_codingSwitch2.value=2;
						}
						else
						{
							bs_codingSwitch2.value=0;
						}	
					#endif		
						bs_codingSwitch2.order=0;		//次数计数,一个周期有4次
						bs_codingSwitch2.status=0x03;	//用于存储一个周期里的值,初始化为0x03
						bs_codingSwitch2.getOne=1;		//1:获取了旋转值
							
					}
					else
					{
						//不是第4次却读到11则认为错误重新开始读取
						if(i==0x03)
						{
							bs_codingSwitch2.order=0;
							bs_codingSwitch2.status=0x03;	
						}

					}
				}
			}
			else
			{
				buf=i;
				bs_codingSwitch2.io_differCnt=0;		//消抖计数
			}
		}
		else
		{
			bs_codingSwitch2.io_differCnt=0;			//消抖计数
			buf=i;
		}
					
	}

/***********************************************************
;函数名称:uchar	codingSwitch_get(void)
;函数功能:获取编码开关状态
;输入参数:无
;输出参数:		
		 0:无动作
		 1:正转
		 2:反转
;使用注意:
;--------
;---------
;---------
;**********************************************************/
	uchar	codingSwitch_get(void)
	{						
		uchar	i=0;		
		if(bs_codingSwitch.getOne)
		{
			bs_codingSwitch.getOne=0;
			i=bs_codingSwitch.value;
			bs_codingSwitch.value=0;				
		}
		return	i;		
	}



/***********************************************************
;函数名称:uchar	codingSwitch_get2(void)
;函数功能:获取编码开关状态(旋转编码开关2)
;输入参数:无
;输出参数:		
		 0:无动作
		 1:正转
		 2:反转
;使用注意:
;--------
;---------
;---------
;**********************************************************/
	uchar	codingSwitch_get2(void)
	{						
		uchar	i=0;		
		if(bs_codingSwitch2.getOne)
		{
			bs_codingSwitch2.getOne=0;
			i=bs_codingSwitch2.value;
			bs_codingSwitch2.value=0;				
		}
		return	i;		
	}








#endif
