#ifndef	__OTHER_H__
#define	__OTHER_H__



/*************************************************************
***********************��������*******************************
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


/*--------------------------��NλΪ1*/
#define         c_bit0              	0x01
#define         c_bit1              	0x02
#define         c_bit2              	0x04
#define         c_bit3              	0x08
#define         c_bit4              	0x10
#define         c_bit5              	0x20
#define         c_bit6              	0x40
#define         c_bit7              	0x80



#define			c_timer1US				125			//�жϻ�׼ʱ��
#define			c_time_1ms				(1000/c_timer1US)
#define			c_time_20ms				20
#define			c_time_100ms			5	



#define			c_on					(1)			//��
#define			c_off					(0)			//��




/*----------------------------����������----------------------------*/
/*
��һ��:
һ��program

��ʼ�� 						c_layer1_init
�Լ�						c_layer1_check
�ػ�						c_layer1_powerOff
����						c_layer1_standby
����						c_layer1_powerOn
ѡ����					c_layer1_selectMenu
ѡ��ԤԼ					c_layer1_selectOrder
��ʼԤԼ					c_layer1_startOrder
ֹͣԤԼ					c_layer1_stopOrder
����ԤԼ				    c_layer1_endOrder
��ʼ����					c_layer1_startMenu
��ͣ����					c_layer1_stopMenu
��������					c_layer1_endMenu

�ڶ���:
����program

ѡ����:
ѡ�����¶�				c_layer2_selectTemper
ѡ����ʱ��				c_layer2_selectTime
ѡ���ܵ�λ				c_layer2_selectGrade
ѡ��������				c_layer2_selectKind

ѡ��ԤԼ:
ԤԼ����Сʱ				c_layer2_selectHour
ԤԼ���ڷ���				c_layer2_selectMin

��ʼ����:
δ��ʼ��ʱ					c_layer2_noStartCD					
��ʼ��ʱ					c_layer2_startCD


*/
//��һ��
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
           		

//�ڶ���	

//ѡ����:
#define	    c_layer2_selectTemper 				1
#define     c_layer2_selectTime   				c_layer2_selectTemper+1
#define     c_layer2_selectGrade  				c_layer2_selectTime+1
#define     c_layer2_selectKind  				c_layer2_selectGrade+1

//ѡ��ԤԼ:
#define	    c_layer2_selectHour 				1
#define     c_layer2_selectMin   				c_layer2_selectHour+1
	
//��ʼ����
#define		c_layer2_noStartCD					0
#define		c_layer2_startCD					c_layer2_noStartCD+1
	

/*************************************************************
***********************�ⲿ��������***************************
*************************************************************/
	extern	void	delay_1us();
	extern	void	delay_2us();
	extern	void	delay_5us();
	extern	void	MCU_other_Init();	
	extern	void	ledFlash_init();
	extern	void	check_deal();
	//extern	void	time_deal();	


/*************************************************************
***********************�ⲿ��������***************************
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
		uint	min;		//Сʱת�ɷ�����ʽ ��ʾ��ת��Сʱ
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

