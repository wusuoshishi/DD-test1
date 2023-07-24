#ifndef	__OTHER_H__
#define	__OTHER_H__



/*************************************************************
***********************常量定义*******************************
*************************************************************/

#define LongToBin(n) \
(                    \
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >>  9) & 0x08) | \
((n >>  6) & 0x04) | \
((n >>  3) & 0x02) | \
((n      ) & 0x01)   \
)
#define b(n) LongToBin(0x##n##l)	//write binary charactor set,exsample : b(11111111) = 0xff


/*--------------------------第N位为1*/
#define         c_bit0              	0x01
#define         c_bit1              	0x02
#define         c_bit2              	0x04
#define         c_bit3              	0x08
#define         c_bit4              	0x10
#define         c_bit5              	0x20
#define         c_bit6              	0x40
#define         c_bit7              	0x80



#define			c_timer1US				125			//中断基准时间
#define			c_time_1ms				(1000/c_timer1US)
#define			c_time_20ms				20
#define			c_time_100ms			5	



#define			c_on					(1)			//开
#define			c_off					(0)			//关




/*----------------------------程序整体框架----------------------------*/
/*
第一层:
一级program

初始化 						c_layer1_init
自检						c_layer1_check
关机						c_layer1_powerOff
待机						c_layer1_standby
开机						c_layer1_powerOn
选择功能					c_layer1_selectMenu
选择预约					c_layer1_selectOrder
开始预约					c_layer1_startOrder
停止预约					c_layer1_stopOrder
结束预约				    c_layer1_endOrder
开始工作					c_layer1_startMenu
暂停工作					c_layer1_stopMenu
结束工作					c_layer1_endMenu

第二层:
二级program

选择功能:
选择功能温度				c_layer2_selectTemper
选择功能时间				c_layer2_selectTime
选择功能档位				c_layer2_selectGrade
选择功能种类				c_layer2_selectKind

选择预约:
预约调节小时				c_layer2_selectHour
预约调节分钟				c_layer2_selectMin

开始工作:
未开始计时					c_layer2_noStartCD					
开始计时					c_layer2_startCD


*/
//第一层
#define		c_layer1_init						0
#define		c_layer1_check						c_layer1_init+1		
#define		c_layer1_powerOff					c_layer1_check+1     				
#define		c_layer1_standby           			c_layer1_powerOff+1
#define		c_layer1_powerOn  					c_layer1_standby+1

#define		c_layer1_selectMenu  				c_layer1_powerOn+1
#define		c_layer1_selectOrder 				c_layer1_selectMenu+1

#define		c_layer1_startOrder 				c_layer1_selectOrder+1
#define		c_layer1_stopOrder					c_layer1_startOrder+1
#define		c_layer1_endOrder 					c_layer1_stopOrder+1

#define		c_layer1_startMenu  				c_layer1_endOrder+1
#define		c_layer1_stopMenu 					c_layer1_startMenu+1
#define		c_layer1_endMenu      				c_layer1_stopMenu+1
           		

//第二层	

//选择功能:
#define	    c_layer2_selectTemper 				1
#define     c_layer2_selectTime   				c_layer2_selectTemper+1
#define     c_layer2_selectGrade  				c_layer2_selectTime+1
#define     c_layer2_selectKind  				c_layer2_selectGrade+1

//选择预约:
#define	    c_layer2_selectHour 				1
#define     c_layer2_selectMin   				c_layer2_selectHour+1
	
//开始工作
#define		c_layer2_noStartCD					0
#define		c_layer2_startCD					c_layer2_noStartCD+1
	

/*************************************************************
***********************外部函数申明***************************
*************************************************************/
	extern	void	delay_1us();
	extern	void	delay_2us();
	extern	void	delay_5us();
	extern	void	MCU_other_Init();	
	extern	void	ledFlash_init();
	extern	void	check_deal();
	//extern	void	time_deal();	


/*************************************************************
***********************外部变量申明***************************
*************************************************************/
	typedef union
	{
	    unsigned char 	allBits;	    	
	    struct
	    {
	        unsigned char	b0:1;
	        unsigned char	b1:1;
	        unsigned char	b2:1;
	        unsigned char	b3:1;
	        unsigned char	b4:1;
	        unsigned char	b5:1;
	        unsigned char	b6:1;
	        unsigned char	b7:1;
	    }oneBits;
	    
	}union_bitFlag;

	typedef	struct
	{
		uchar	ms;
		uchar	sec;			
	}str_timeSec;
	
	typedef	struct
	{
		uchar	ms;
		uchar	sec;	
		uchar	min;		
	}str_timeMin;
	
	typedef	struct
	{
		uchar	ms;
		uchar	sec;	
		uint	min;		//小时转成分钟形式 显示再转回小时
	}str_timeHour;
	
	typedef	struct
	{
		uchar	layer1;
		uchar	layer2;	
		uchar	layer3;	
		uchar	layer4;	
		uchar	layer5;
	}str_pa;


	extern	uchar	gb_1ms;
	extern	uchar	data gb_20ms;
	extern	uchar	gb_100ms;	
	extern	uchar	gb_200ms;
	extern uchar	gb_1s;
	//
	extern uchar xdata b_checkTime;
	//extern	bit		gf_flash;
	//
	extern	str_pa	data	gbs_paLayer;



#endif

