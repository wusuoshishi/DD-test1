#include	"..\Project\Project.h"
#include 	"..\Application_Library\Global.h"
#include <intrins.h>



#if	c_key_mode
unsigned	char			keysFlagQC=0;
#endif

unsigned char	xdata	b_key_value=0;
unsigned char	xdata	b_key_double=0;
unsigned char	xdata	b_key_old=0;
unsigned char	xdata	b_key_num=0;
unsigned char	xdata	b_key_cnt=0;	//按下消抖
unsigned char	xdata	b_key_noCnt=0;	//释放消抖
unsigned char	xdata	b_key_longcnt=0;

uchar	xdata	Target_wendu_mode_1=0;  //左目标温度灯 0:无,1:80℃，2:100℃，3:120℃
uchar	xdata	Target_wendu_mode_2=0;  //左目标温度灯 0:无,1:80℃，2:100℃，3:120℃
uchar	xdata	set_time_1_hour=0; //左定时灯
uchar	xdata	set_time_1_min=0;  //
uchar	xdata	set_time_1_sec=0;  //
uchar	xdata	set_time_2_hour=0; //右定时灯
uchar	xdata	set_time_2_min=0;  //
uchar	xdata	set_time_2_sec=0;  //

uchar	xdata   b_stop_1_sec=0;  //左暂停时间
uchar	xdata   b_stop_1_min=0;  //左暂停时间
uchar	xdata   b_stop_2_sec=0;  //右暂停时间
uchar	xdata   b_stop_2_min=0;  //右暂停时间


uchar	xdata	b_force_flash_cnt=0;	//强制闪烁计数
bit	f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
uchar	xdata	b_clock_key =0; //运行过程中,无按键按下,1s后锁键


bit		f_readKey_over=0;
bit		f_longKey=0;
bit		f_firstKey=0;
bit		f_key_done=0;
bit		f_lamp_long=0;
bit		f_power_long=0;
bit		f_key_double=0;



bit   f_k1_down=0;

typedef	struct
{
    unsigned char	hour_int;	//小时初始值
    unsigned char	min_int;	//分钟初始值
    unsigned char	hour_max;	//最大小时
    unsigned char	min_max;	//最大分钟
    unsigned char	hour_min;	//最小小时
    unsigned char	min_min;	//最小分钟
    unsigned char	chg_num;	//递增分钟数
	unsigned char	chg_num_1;	//递减分钟数
	unsigned char	grade_int;	//档位
	unsigned char	grade_max;	//最大档位
	unsigned char	grade_min;	//最小档位


} str_setscan;


str_setscan		const	code	tab_set[]=
{
	//初始时间  /最大时间 /最小时间   /递进   /档位
    {1, 0,   1, 0,	  1, 0,     5, 1,	3,5,1},	//功能1 爆炒 档位可调		
    {0, 5,   1, 0,	  0, 5,     5, 1,	1,1,1},	//功能2 炖煮 时间可调		 
    {0, 5,   1, 0,	  0, 5,     5, 1,	1,1,1},	//功能3 清蒸 时间可调		 
    {0,20,   3, 0,	  0, 5,    20, 5,	1,1,1},  //功能4 慢炖 时间可调 		 
	{3,30 ,  60, 0,	  1, 0,    30,30,	1,1,1},  //功能5 牛排 时间可调 这个比较特殊,
	{1, 0,   1, 0,	  1, 0,     5, 1,	5,5,1}  //功能6 火锅 档位可调		 
};

////测试
//str_setscan		const	code	tab_set[]=
//{
//	//初始时间/最大时间/最小时间/递进/档位
//    {0,20,    1, 0,	  0,15,    5,	5,5,1},	//功能1 蒸煮 时间可调
//    {0,30,    1,10,	  0,15,    5,	5,5,1},	//功能2 煎炒 档位可调
//    {0,30,    0,30,	  0,30,    5,	1,1,1},	//功能3 煮饭 不可调
//    {0,2,    1,30,	  0,15,    5,	5,5,1}  //功能4 焖煮 时间可调
//};



void	key_deal();		//按键处理,20MS执行一次
void	key_scan();		//按键检测

void	mode_key();		//模式键
void	add_key();		//加键
void	dec_key();		//减键
void	baowen_yuyu_key();	//保温预约按钮(大多数保温预约按钮都会在同一个按键之上)

void	mode_init();	//功能模式初始化


void	dingshi_add_fun();	//定时时间加功能
void	dingshi_dec_fun();	//定时时间减功能
void    baowen_add_fun();	//保温时间加功能
void    baowen_dec_fun();	//保温时间减功能

void	yuyue_add_fun();	//预约时间加功能
void	yuyue_dec_fun();	//预约时间减功能
void	grade_add_fun();	//档位加功能
void	grade_dec_fun();	//档位减功能
void	baowen_fun();		//保温功能

void	quit_work();	//退出工作
void	action_work();	//开始工作
void	key_clr_sec();	//刷新显示并且响蜂鸣器
/*-----------------------------------------------------------------
函数名称： void	baowen_yuyu_key(void)
函数功能： 保温预约按钮
输入参数： 无
返 回 值： 无
说明:大多数保温预约按钮都会在同一个按键之上
-----------------------------------------------------------------*/
void	baowen_yuyu_key()
{
	baowen_fun();
}


#if	c_key_mode
//轻触按键将此两个函数插入显示扫描中

//  按键置输入
void  sw_scan_in()
{
    key_input;
    key_pull;
}

//  按键检测
void  sw_scan()
{
    keysFlagQC = 0;
    if(!p_k1)
        keysFlagQC = 1;
    if(!p_k2)
        keysFlagQC = 2;
    //if(!p_k3)
    //    keysFlagQC = 3;
    //if(!p_k4)
    //    keysFlagQC = 4;
    //if(!p_k5)
    //    keysFlagQC = 5;
    //if(!p_k6)
    //    keysFlagQC = 6;
    //if(!p_k7)
    //    keysFlagQC = 7;
    //if(!p_k8)
    //    keysFlagQC = 8;
    key_output;
}
#endif



/*-----------------------------------------------------------------
函数名称： void	key_scan(void)
函数功能： 按键检测
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	key_scan()
{

    uchar i=0;

#if	c_key_mode

#pragma message "轻触按键"
    b_key_value = keysFlagQC;

#else

#pragma message "触摸按键"

    b_key_value=0;
    for(i = 0; i < SNS_NUM; i++)
    {
        if((keys_flag) & (((ulong)0x01)<<SNS[i]))
        {
            b_key_value = i;
            b_key_value++;
            b_disp_test=b_key_value;
        }
    }

#endif

    if(b_key_value)
    {
        b_key_noCnt=0;
        if(b_key_value==b_key_old)
        {
            b_key_cnt++;
            if(b_key_cnt>=c_shortKey_cnt)
            {
                b_key_cnt=0;
                if(f_readKey_over==0)
                {
                    f_readKey_over=1;
                    f_key_done=1;
                }
            }
        }
        else
        {
            b_key_old=b_key_value;
            b_key_cnt=0;
        }
    }
    //无按键
    else
    {

        b_key_cnt=0;
        b_key_noCnt++;
        if(b_key_noCnt>=1)
        {
            b_key_value=0;
            b_key_noCnt=0;
            f_readKey_over=0;
            f_firstKey=0;
            b_key_longcnt=0;
            b_key_old=0;
            /*-----------------------------此处复用按键----------------------------*/
            //if(f_k1_down)
            //{
            //  f_k1_down=0;
            //  if(b_mode!=2)
            //  {
            //    b_mode=2;
            //    mode_key();
            //    f_disp_dingshi=1;
            //    key_clr_sec();
            //    open_buz(1);
            //  }
            //}
            /*--------------------------------------------------------------------*/
        }
    }

}

/*-----------------------------------------------------------------
函数名称： void	yuyue_add_fun(void)
函数功能： 预约时间加
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void    yuyue_add_fun()
{
	b_yuyue_sec=0;

	b_yuyue_min+=30;

	if(b_yuyue_hour >=24 && b_yuyue_min >0)
	{
		b_yuyue_hour=24;
		b_yuyue_min=0;
	}
	else
	{
		if(b_yuyue_min>=60)
		{
			b_yuyue_min=0;
			b_yuyue_hour++;
			if(b_yuyue_hour >=24)
			{
				b_yuyue_hour=24;	
			}
		}
	}




}


/*-----------------------------------------------------------------
函数名称： void	yuyue_dec_fun(void)
函数功能： 预约时间减
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void    yuyue_dec_fun()
{
	//b_yuyue_min=0;
//
    //if(b_yuyue_hour>1)	//最小值为1
    //  b_yuyue_hour--;



	
	b_yuyue_sec=0;	

	if(b_yuyue_hour>=1)
	{
		if(b_yuyue_min>=30)
			b_yuyue_min-=30;
		else
		{
			b_yuyue_hour--;
			b_yuyue_min=60+b_yuyue_min-30;
		}
	}



}




/*-----------------------------------------------------------------
函数名称： void	mode_init(void)
函数功能： 功能模式初始化
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void mode_init()
{
	b_mode=1;
	/*获取默认时间*/
	b_dingshi_hour = tab_set[b_mode-1].hour_int;
    b_dingshi_min  = tab_set[b_mode-1].min_int;


	/*获取默认档位*/
	b_grade=tab_set[b_mode-1].grade_int;

	/*设置对应的状态*/
	f_mjs_set=1;
	f_mjs_dingshi=1;
	//f_mjs_power;
	//f_mjs_yuyue;
	//f_mjs_down;
	//f_dingshi_begin;

	//f_disp_dingshi=0;
	//f_disp_yuyue=0;

	//时间闪3秒
	b_time_grade_cnt =7	;	//0:档位,5:时间
}


/*-----------------------------------------------------------------
函数名称： void	baowen_fun(void)
函数功能： 保温功能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	baowen_fun()
{

	f_mjs_set=1;
	f_mjs_dingshi=1;
	//f_mjs_power=0;
	//f_mjs_yuyue=0;

	f_dingshi_begin=1;

	b_mode	|= 0x80;
	
	/*设置默认时间*/
	b_dingshi_hour=24;
	b_dingshi_min=0;
	b_dingshi_sec=0;

	/*设置默认温度*/
	b_set_wendu=60;	//60℃





	///*设置默认时间*/
	////默认6个小时
	//b_baowen_hour=6;
	//b_baowen_min=0;
	//b_baowen_sec=0;
	//action_work();
}


/*-----------------------------------------------------------------
函数名称： void	dingshi_add_fun(void)
函数功能： 定时时间加功能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void    dingshi_add_fun()
{
	uchar	i=0;

	////显示时间,时间闪3秒
	//b_time_grade_cnt=7;//;0:档位,5:时间



	
	/*获取每次递进的时间*/
    if(b_key_longcnt==0)
        i=tab_set[b_mode-1].chg_num;
    else
        i=tab_set[b_mode-1].chg_num;


		/*现在值和最大值进行比较*/
    	if((b_dingshi_hour*60+b_dingshi_min)>=(tab_set[b_mode-1].hour_max*60+tab_set[b_mode-1].min_max))
    	{
			/*大于等于最大值,赋值最大值*/
    	    key_clr_sec();
    	    b_dingshi_hour=tab_set[b_mode-1].hour_max;
    	    b_dingshi_min=tab_set[b_mode-1].min_max;
    	}
    	else
    	{
			/*加时间,然后进行范围判断*/
    		key_clr_sec();
    	    b_dingshi_min+=i;
    	    if(b_dingshi_min>=60)
    	    {
    	        b_dingshi_min-=60;
    	        b_dingshi_hour++;
    	    }
			/*现在值和最大值进行比较*/
    	    if((b_dingshi_hour*60+b_dingshi_min)>=(tab_set[b_mode-1].hour_max*60+tab_set[b_mode-1].min_max))
    	    {
				/*大于等于最大值,赋值最大值*/
    	        key_clr_sec();
    	        b_dingshi_hour=tab_set[b_mode-1].hour_max;
    	        b_dingshi_min=tab_set[b_mode-1].min_max;
    	    }
    	}

}


/*-----------------------------------------------------------------
函数名称： void	baowen_add_fun(void)
函数功能： 保温时间加功能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void    baowen_add_fun()
{
	uchar	i=0;
	b_dingshi_sec=0;
	i=30;
	key_clr_sec();

	/*现在值和最大值进行比较*/
    if((b_dingshi_hour*60+b_dingshi_min)>=(24*60+0))
    {
		/*大于等于最大值,赋值最大值*/
        b_dingshi_hour=24;
        b_dingshi_min=0;
    }
    else
    {
		/*加时间,然后进行范围判断*/
        b_dingshi_min+=i;
        if(b_dingshi_min>=60)
        {
            b_dingshi_min-=60;
            b_dingshi_hour++;
        }
		/*现在值和最大值进行比较*/
        if((b_dingshi_hour*60+b_dingshi_min)>=(24*60+0))
        {
					/*大于等于最大值,赋值最大值*/
            b_dingshi_hour=24;
            b_dingshi_min=0;
        }
    }

}






/*-----------------------------------------------------------------
函数名称： void	dingshi_dec_fun(void)
函数功能： 定时时间减
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	dingshi_dec_fun()
{
	uchar	i=0;
	////显示时间,时间闪3秒
	//b_time_grade_cnt=7;//;0:档位,5:时间


	//获取每次递进的时间
    if(b_key_longcnt==0)
    	i=tab_set[b_mode-1].chg_num_1;
    else
        i=tab_set[b_mode-1].chg_num_1;

    key_clr_sec();	//刷新显示并且响蜂鸣器

    if((b_dingshi_hour*60+b_dingshi_min)>=i)	//判断能不能减的下
    {
        if((b_dingshi_hour*60+b_dingshi_min)<=(tab_set[b_mode-1].hour_min*60+tab_set[b_mode-1].min_min))
        {
            b_dingshi_hour=tab_set[b_mode-1].hour_min;
            b_dingshi_min=tab_set[b_mode-1].min_min;
        }
        else
        {
        	if(b_dingshi_min<i)
        	{
        		b_dingshi_min+=60;
        	    b_dingshi_hour--;
        	}
            b_dingshi_min-=i;
            if((b_dingshi_hour*60+b_dingshi_min)<(tab_set[b_mode-1].hour_min*60+tab_set[b_mode-1].min_min))
            {
                b_dingshi_hour=tab_set[b_mode-1].hour_min;
                b_dingshi_min=tab_set[b_mode-1].min_min;
            }
        }
    }
	/*不够减,直接赋值之值*/
    else
    {
        b_dingshi_hour=tab_set[b_mode-1].hour_min;
        b_dingshi_min=tab_set[b_mode-1].min_min;
    }

}


/*-----------------------------------------------------------------
函数名称： void	baowen_dec_fun(void)
函数功能： 保温时间减
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	baowen_dec_fun()
{
	uchar	i=0;
	////显示时间,时间闪3秒
	//b_time_grade_cnt=7;//;0:档位,5:时间
	b_dingshi_sec=0;
	
	//获取每次递进的时间
    i=30;

    key_clr_sec();	//刷新显示并且响蜂鸣器

    if((b_dingshi_hour*60+b_dingshi_min)>=i)	//判断能不能减的下
    {
        if((b_dingshi_hour*60+b_dingshi_min)<=(0))
        {
            b_dingshi_hour=0;
            b_dingshi_min=0;
        }
        else
        {
        	if(b_dingshi_min<i)
        	{
        		b_dingshi_min+=60;
        	    b_dingshi_hour--;
        	}
            b_dingshi_min-=i;
            if((b_dingshi_hour*60+b_dingshi_min)<(0))
            {
                b_dingshi_hour=0;
                b_dingshi_min=0;
            }
        }
    }
	/*不够减,直接赋值之值*/
    else
    {
        b_dingshi_hour=0;
        b_dingshi_min=0;
    }

}



/*-----------------------------------------------------------------
函数名称： void	grade_dec_fun(void)
函数功能： 档位减功能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	grade_dec_fun()
{


	b_time_grade_cnt=0;//;0:档位,5:时间


	#if 1 //不可循环
		if(b_grade>tab_set[b_mode-1].grade_min)
			b_grade--;
	#endif

	#if 0 //可循环
		b_grade--;
		/*达到最小值->最大值*/
		if(b_grade<tab_set[b_mode-1].grade_min)
			b_grade=tab_set[b_mode-1].grade_max;
	#endif



	/*运行之后按下,就不会自动降档*/
	if(f_mjs_power)
		f_NO_jiangdang=1;	//降档标志位 0:可降档 1:不可降档

}


/*-----------------------------------------------------------------
函数名称： void	grade_add_fun(void)
函数功能： 档位加功能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	grade_add_fun()
{
	//b_time_grade_cnt=0;//;0:档位,5:时间

	#if 1 //不可以循环
	if (b_grade<tab_set[b_mode-1].grade_max)
	{
		b_grade++;
	}
	#endif

	#if 0 //可循环
		b_grade++;
		/*超过最大值->最小值*/
		if (b_grade>tab_set[b_mode-1].grade_max)
			b_grade=tab_set[b_mode-1].grade_min;
	#endif 


	/*运行之后按下,就不会自动降档*/
	if(f_mjs_power)
		f_NO_jiangdang=1;	//降档标志位 0:可降档 1:不可降档

}


/*-----------------------------------------------------------------
函数名称： void	key_yuyue(void)
函数功能： 预约键
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void  key_yuyue()
{
	/*主状态*/
    f_mjs_set=1;
	f_mjs_yuyue=1;
	
	/*显示*/
    f_disp_yuyue=1;
    f_disp_dingshi=0;

	/*默认时间*/
	b_yuyue_sec=0;
    b_yuyue_min=30;
    b_yuyue_hour=0;



//    if(f_mjs_yuyue)
//    {
//		//       yuyue_add_fun();
//        f_mjs_yuyue=0;
//        f_disp_yuyue=0;
//        f_disp_dingshi=1;
//        if(!b_mode)
//        {
//            f_mjs_set=0;
//            f_disp_dingshi=0;
//        }
//    }
//	/*默认预约时间 30分钟*/
//    else
//    {
//        f_mjs_yuyue=1;
//		f_disp_yuyue=1;
//		f_disp_dingshi=0;	
//
//        b_yuyue_min=30;
//        b_yuyue_hour=0;
//    }





}



/*-----------------------------------------------------------------
函数名称： void	add_key(void)
函数功能： 加键
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	add_key()
{
    if(f_disp_yuyue && f_mjs_set)
    {
		/*对预约时间增加*/
        //f_mjs_set=1;
        yuyue_add_fun();
    }
    else
    {
		/*功能1 6调整功率*/
        if(b_mode==1 || b_mode==6)
        {
			if(f_clock_key)
			{
				b_force_flash_cnt=0;	//强制闪烁计数
				f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
				b_clock_key =0; //运行过程中,无按键按下,1s后锁键
				key_clr_sec();
			}
			else
			{
				b_force_flash_cnt=0;	//强制闪烁计数
				f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
				b_clock_key =0; //运行过程中,无按键按下,1s后锁键
				grade_add_fun();	//档位加功能
			}
		}
        else if(b_mode==2 || b_mode==3 ||b_mode==4 || b_mode==5)
		{
			
			if(f_disp_yuyue)
			{			
				f_disp_yuyue=0;
				b_yuyue_run_cnt=0;
				b_force_flash_cnt=0;	//强制闪烁计数
				f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
				b_clock_key =0; //运行过程中,无按键按下,1s后锁键
				key_clr_sec();
			}
			else
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					key_clr_sec();
				}
				else
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键	
					dingshi_add_fun();	//定时时间加功能
				}
				
			}

		}
		else if(b_mode==0x80)
		{	
			/*运行时,加时间*/
			if(f_mjs_power)
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					key_clr_sec();
				}
				else
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					baowen_add_fun();	
				}	
			}
			/*非运行时,加温度*/
			else
			{
				b_set_wendu+=5;
				if(b_set_wendu>=90)
				{
					b_set_wendu=90;
				}

//				b_set_wendu+=5;
//
//				//if(b_set_wendu>100)
//				//	b_set_wendu +=5;
//
//				if(b_set_wendu>=225)
//				{
//					b_set_wendu=150;
//				}
//




			}
		}
			
        //  b_led_slide1=5;
	

    }
}


/*-----------------------------------------------------------------
函数名称： void	dec_key(void)
函数功能： 加键
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	dec_key()
{
    if(f_disp_yuyue && f_mjs_set)
    {
        //f_mjs_set=1;
        yuyue_dec_fun();	//预约时间减
    }
    else
    {
		/*功能1 6调整功率*/
        if(b_mode==1 || b_mode==6)
        {
			if(f_clock_key)
			{
				b_force_flash_cnt=0;	//强制闪烁计数
				f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
				b_clock_key =0; //运行过程中,无按键按下,1s后锁键
				key_clr_sec();
			}
			else
			{	
				b_force_flash_cnt=0;	//强制闪烁计数
				f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
				b_clock_key =0; //运行过程中,无按键按下,1s后锁键
				grade_dec_fun();	//档位加功能	
			}	
        }
        else if(b_mode==2 || b_mode==3 || b_mode==4|| b_mode==5)
		{	if(f_disp_yuyue)
			{			
				f_disp_yuyue=0;
				b_yuyue_run_cnt=0;
				b_force_flash_cnt=0;	//强制闪烁计数
				f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
				b_clock_key =0; //运行过程中,无按键按下,1s后锁键
				key_clr_sec();
			}
			else
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					key_clr_sec();
				}
				else
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					dingshi_dec_fun();	//定时时间减功能
				}
				
				
			}
			
		}
		else if(b_mode==0x80)
		{	
			/*运行时,加时间*/
			if(f_mjs_power)
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					key_clr_sec();
				}		
				else
				{
					b_force_flash_cnt=0;	//强制闪烁计数
					f_clock_key	=0;	//1:锁键,0:解锁,可改变时间档位
					b_clock_key =0; //运行过程中,无按键按下,1s后锁键
					baowen_dec_fun();
				}		
				
			}
			/*非运行时,加温度*/
			else
			{
				b_set_wendu-=5;
				if(b_set_wendu<=40)
				{
					b_set_wendu=40;
				}






			}
		}
    }
}


/*-----------------------------------------------------------------
函数名称： void	mode_key(void)
函数功能： 模式键
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	mode_key()
{

	/*如果一开始没有任何状态,则模式功能初始化*/
	if(!f_mjs_dingshi && !f_mjs_power && !f_mjs_yuyue && !f_mjs_down && !f_mjs_set)
	{
		mode_init();	//功能模式初始化
		key_clr_sec();	//刷新显示并且响蜂鸣器
	}
	else if (f_mjs_set)
	{
		f_mjs_yuyue=0;
		f_mjs_dingshi=1;
		f_mjs_set=1;
		//f_mjs_power=0;

    	f_disp_dingshi=0;
    	f_disp_yuyue=0;
    	f_dingshi_begin=0;


		

		b_mode++;
		if(b_mode>=7)	//最大功能4
			b_mode=1;	//循环


		//if (b_mode==3)
		//{
			f_mjs_dingshi=1;
			//f_disp_dingshi=1;
		//}

		/*获取默认时间*/
    	b_dingshi_hour = tab_set[b_mode-1].hour_int;
    	b_dingshi_min  = tab_set[b_mode-1].min_int;

		/*获取默认档位*/
		b_grade = tab_set[b_mode-1].grade_int;
		key_clr_sec();	//刷新显示并且响蜂鸣器



	}



}




/*-----------------------------------------------------------------
函数名称： void	key_clr_sec(void)
函数功能： 刷新显示并且响蜂鸣器
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	key_clr_sec()
{
    b_key_double=0;
    b_led_slide1=0;
    b_mjs_set_sec=0;
    gb_flashTime=0;
    gf_flash=1;
    gb_1s=0;
    if(b_key_longcnt==0)
        open_buz(1);	//按键音
		//open_buz(2);	//报警音
		//open_buz(3);	//开机音
		//open_buz(4);	//工作开始音
		//open_buz(5);	//工作完成音
}




/*-----------------------------------------------------------------
函数名称： void	key_deal(void)
函数功能： 按键动作,20MS执行一次
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	key_deal()
{
    key_scan();

    b_key_double++;   //双击计时变量
    if(b_key_double >= 50)
    {
        //	退出双击时间
        f_key_double = 0;
        b_key_double = 0;
    }

    if(f_key_done==1)
    {
        f_key_done=0;
        if(!b_warning)
        {
        	if(f_test)
        	{
        	  open_buz(1);
        	}
        	else
        	{
            /*-----------------------------此处按键处理----------------------------*/
            switch(b_key_value)
            {
            case c_k1:  //预约/保温
            {	
				/*在待机状态下,按下,进入手动保温*/
				if(!f_mjs_set&& !f_mjs_power && !f_mjs_yuyue && !b_mode)
				{
					key_clr_sec();	//刷新显示并且响蜂鸣器
					baowen_fun();	//保温功能
				}
				/*设置状态下,模式2,3,4可进入*/
				else if(f_mjs_set )
				{
					if ((b_mode==2) || (b_mode == 3) ||(b_mode == 4))
					{
				    	key_yuyue();
				    	key_clr_sec();
					}
				}

                break;

            }
            case c_k2:  //功能/取消
            {
				/*运行了按下->关机*/
				if (f_mjs_power)
				{	
					/*短按*/
					if(b_key_longcnt==0)
					{
						quit_work();	//退出工作
						key_clr_sec();	//刷新显示并且响蜂鸣器
						open_buz(1);	//按键音
					}
				}
				/*预约倒计时按下->关机*/
				else if (f_mjs_yuyue && !f_mjs_set)
				{	
					/*短按*/
					if(b_key_longcnt==0)
					{
						quit_work();	//退出工作
						key_clr_sec();	//刷新显示并且响蜂鸣器
					}

				}
				else
				{						/*短按*/
					if(b_key_longcnt==0)
					{
						mode_key();	
					}
				}


				f_readKey_over=0;
				if(b_key_longcnt<50)
				{
					b_key_longcnt++;
				}



                break;				
			}


            case c_k3:  //减
            {
                if(b_warning)
                    break;
                //有功能才按得动   
                if(b_mode==0)
                    break;  

				////保温功能按不动
				//if(b_mode&0x80)
				//	break;

				////功能3(煮饭)按不动
				//if(b_mode==3)
				//	break;
				
				////运行后,除了功能2(煎炒)都按不动
				//if(f_mjs_power && (b_mode!=2))
				//	break;


                //key_clr_sec();	//刷新显示并且响蜂鸣器

				//短按跟长按连续响应
				if((b_key_longcnt==0)||(b_key_longcnt>=50))
				{
					key_clr_sec();	
					dec_key();
				}
				f_readKey_over=0;
				b_key_longcnt++;
				if(b_key_longcnt>50)
				{
					b_key_longcnt=45;
				}
                break;
            }
            case c_k4:  //加
            {
				//报错了,按不动
                if(b_warning)
                    break;

                //有功能才按得动   
                if(b_mode==0)
                    break;  

				////保温功能按不动
				//if(b_mode&0x80)
				//	break;

				////功能3(煮饭)按不动
				//if(b_mode==3)
				//	break;

				////运行后,除了功能2(煎炒)都按不动
				//if(f_mjs_power && (b_mode!=2))
				//	break;

				
                //key_clr_sec();	//刷新显示并且响蜂鸣器

				//短按跟长按
				if((b_key_longcnt==0)||(b_key_longcnt>=50))
				{
					key_clr_sec();	
					add_key();
				}
				f_readKey_over=0;
				b_key_longcnt++;
				if(b_key_longcnt>50)
				{
					b_key_longcnt=45;
				}
                break;
            }    



			
            default:
                break;
            }
          }
            /*--------------------------------------------------------------------*/
        }
        else
        {
            //清除报警
    			if(b_key_value == c_k2)
    			{
    				key_clr_sec();
    				quit_work();
    				b_warning=0;
    			}
        }

    }
}

#if	0
//		常用按键处理程序，使用时直接将其复制到按键处理函数中，并根据实际情况相应修改
//				加键
if(f_disp_yuyue||(f_disp_dingshi&&(b_mode!=1)))
{
    if((b_key_longcnt==0)||(b_key_longcnt>=50))
    {
        key_clr_sec();
        add_key();
    }
    f_readKey_over=0;
    b_key_longcnt++;
    if(b_key_longcnt>50)
    {
        b_key_longcnt=40;
    }
}


//		减键
if(f_disp_yuyue||(f_disp_dingshi&&(b_mode!=1)))
{
    if((b_key_longcnt==0)||(b_key_longcnt>=50))
    {
        key_clr_sec();
        dec_key();
    }
    f_readKey_over=0;
    b_key_longcnt++;
    if(b_key_longcnt>50)
    {
        b_key_longcnt=40;
    }
}

//		模式键：直接生效
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue)))
{
    key_clr_sec();
    mode_key();
    action_work();
}

//		模式键：模式+1
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue)))
{
    key_clr_sec();
    mode_key();
}

//		保温/取消键
key_clr_sec();
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue))&&(!f_mjs_set))
{
    quit_work();
    baowen_yuyu_key();
}
else
    quit_work();

//		开始键
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue)))
{
    if(b_mode)
        action_work();
    else
    {
        mode_key();
        action_work();
    }
}

//		预约键
if(((!f_mjs_set)&&(!f_mjs_yuyue)&&(!f_mjs_power)) || f_mjs_set)		//
{
    key_yuyue();
    key_clr_sec();
}


//		取消键
if(f_mjs_power || f_mjs_set || f_mjs_yuyue)
{
    key_clr_sec();
    quit_work();
}

#endif




