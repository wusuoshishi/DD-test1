#include 	"..\Application_Library\Global.h"








uchar	xdata   b_NOW_or_Target_cnt=0;//0:目标温度,5:现在温度
uchar	xdata   b_NOW_or_Target_cnt2=0;//0:目标温度,5:现在温度
//bit f_test_abc=0; //测试用


uchar	data	b_tbcheck=0;


bit		gf_check=0;
//uchar	xdata	b_checkTime=0;

#if test_en       

bit		f_send_code=0;
uchar	xdata	b_send=0;
uint	xdata	b_code=0;
uchar	xdata	b_code_num=0;

#endif


void	time_deal(void);



/****************************************************************/
//函数名：void Project(void)
//功  能：项目项目功能函数
//参  数：无
//返回值：无
/****************************************************************/
void Project(void)
{
   	if(gb_20ms>=20)
	{
        gb_20ms-=20;   //20ms基准
  
        if(gf_check)
        {
            key_deal();
            work_deal();
            warning_check();
        }
		#if   buz_en
          	buz_deal();
		#endif
          	check_deal();

          //==hore_check(); //按钮自检
  
		#if   ad_en
          	lab_ad_fun();//OK
		#endif
          	//codingSwitch_deal1(); //编码开关1处理
          	//codingSwitch_deal2(); //编码开关2处理
          	time_deal();
          	display_deal();
          
		#if	(c_TM1628_EN || c_TM1629_EN)	
          	TM1628_sendData();
		#endif	


    }
	
}


/*-----------------------------------------------------------------
函数名称： void	time_deal(void)
函数功能： 时间处理函数，处理所有的时间变量
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/

void	time_deal()
{
  
	/*闪烁计时*/
    if(++gb_flashTime>=25)
    {
        gb_flashTime=0;
        gf_flash = !gf_flash;
    }


	if(b_force_flash_cnt<250)
		b_force_flash_cnt++;	//强制闪烁计数


	if(b_clock_key<250)	//运行过程中,无按键按下,1s后锁键
		b_clock_key++;
	if(f_mjs_set || !b_mode)
	{
		b_clock_key=0;
		f_clock_key=0;
	}
		
	if(b_clock_key>=60)	//上锁时间
		f_clock_key=1;
	
	if(f_clock_key==1)
	{
		if(f_mjs_yuyue)
		{
			f_disp_yuyue=1;
		}

		/*保温模式上锁的时候,时间为零,自动退出*/
		if(b_mode==0x80 && f_mjs_power)
		{
			if((b_dingshi_hour==0) && (b_dingshi_min==0) )
			{
				quit_work();	
				/*特殊处理*/
				/*大于200说明已经是倒计时结束关机的,而不是手动关机的*/
				if(b_clock_key>=200)
				{
					open_buz(3);	//工作完成音
				}
			}	




		}
	}


	///*测试计时*/
    //gb_200ms++;
    //if(gb_200ms>=25)
    //{
    //    gb_200ms=0;
    //    if(b_test<0xff)
    //      b_test++;
    //    if(b_test>=5)
    //      b_test=0;
    //}

    if(b_checkTime<0xff)
      b_checkTime++;

	/*继电器驱动计时*/
    gb_100ms++;
    if(gb_100ms>=5)     
    {
        gb_100ms=0;
		#if test_en        
    	    f_send_code=1;
    	    b_send=0;
    	    b_code_num=0;
    	    b_code=b_disp_test*256+b_disp_test2;
		#endif

		#if out_en
    	    relay_deal();   //继电器驱动
		#endif

    }

	
	/*1s执行一次*/
    gb_1s++;
    if(gb_1s>=50)
    {
        gb_1s=0;        //1s基准




        b_led_slide1 ++;			 //显示流水计时
        if(b_led_slide1 >= 10)
            b_led_slide1 = 0;

		/*设置计数*/
        if(b_mjs_set_sec<0xff)
            b_mjs_set_sec++; 			//工作流程计时

		/*工作流程计数*/	
        if(b_ctrl_sec_3<0xff)
            b_ctrl_sec_3++;
        if(b_ctrl_sec_2<800)
            b_ctrl_sec_2++;
        if(b_ctrl_sec_1<0xff)
            b_ctrl_sec_1++;
        
        //目标温度,现在温度转换时间累加
        b_NOW_or_Target_cnt++;
        if(b_NOW_or_Target_cnt>=c_NOW_or_Target_cnt_MAX)
          b_NOW_or_Target_cnt=0;


		/*报错相关计时*/
        if(b_error_sec<0xff)
          b_error_sec++;
        if(b_error_sec_1<0xff)  
          b_error_sec_1++;
        if(b_error_e3<0xff)
            b_error_e3++;



	#if double_ad_channel
        if(b_temp_1_ref_sec<0xff)
            b_temp_1_ref_sec++;
	#endif


		/*保温计时*/
		if((b_mode&0x80) && (f_mjs_power))
        b_baowen_sec++;							 //保温时间
        if(b_baowen_sec>=60)    //缩时60 2
        {
            b_baowen_sec=0;
            b_baowen_min++;
            if(b_baowen_min>=60)	//缩时60 2
            {
                b_baowen_min=0;
                b_baowen_hour++;
            }
        }

		// /*预约计时*/
         b_yuyue_sec++;							 //预约时间
         if(b_yuyue_sec>=60)  //缩时60
         {
             b_yuyue_sec=0;
             if(b_yuyue_min||b_yuyue_hour)
             {
                 if(b_yuyue_min)
                     b_yuyue_min--;
                 else
                 {
                     b_yuyue_min=59;
                     b_yuyue_hour--;
                 }
             }
         }

		///*预约计时*/
        //b_yuyue_sec++;							 //预约时间
        //if(b_yuyue_sec>=60)  //缩时60 2
        //{
        //    b_yuyue_sec=0;
		//	b_yuyue_min++;
		//	if (b_yuyue_min>=60)	//缩时60 2
		//	{
		//		b_yuyue_min=0;
		//		if (b_yuyue_hour>0)
		//		{
		//			b_yuyue_hour--;
		//		}
		//
		//	}
        //}


	if(b_mode!=5)
	{
		/*定时计时*/
		if(f_mjs_power)
        	b_dingshi_sec++;							   //定时时间
        if(b_dingshi_sec>=60)   //缩时60 2
        {
            b_dingshi_sec=0;
            if(b_dingshi_min||b_dingshi_hour)
            {
                if(b_dingshi_min)
                    b_dingshi_min--;
                else
                {
                    b_dingshi_min=59;	//缩时59
                    b_dingshi_hour--;
                }
            }
        }
	}
	
	else
	{
		/*定时计时*/
		
        b_dingshi_sec++;							   //定时时间
        if(!f_mjs_power)
			b_dingshi_sec=0;	
		if(b_dingshi_sec>=1)   //缩时60 2
        {
            b_dingshi_sec=0;
            if(b_dingshi_min||b_dingshi_hour)
            {
                if(b_dingshi_min)
                    b_dingshi_min--;
                else
                {
                    b_dingshi_min=59;	//缩时59
                    b_dingshi_hour--;
                }
            }
        }
	}


		/**/
//		b_time_grade_cnt++;	//0:档位,5:时间
//		if(b_time_grade_cnt>=10)
//		{
//			/*定时闪烁完后,如定时时间为0,则关闭定时模式*/
//			if(f_disp_dingshi)
//			{
//				open_buz(4);	//工作开始音
//				f_dingshi_begin=1;//开始计时
//				/*启动计时,时间为0,则取消计时*/
//				if(!b_dingshi_min)
//				{
//					f_mjs_dingshi=0;	//退出定时状态
//					f_dingshi_begin=0;//关闭倒计时
//				}
//			}
//
//			b_time_grade_cnt=0;	//0:档位,5:时间
//			f_disp_dingshi=0;	//关定时显示
//			
//		}

//		//预约倒计时进行中时
//		if(f_mjs_yuyue  && !f_mjs_set)
//		{
//			if(b_yuyue_run_cnt<10)
//				b_yuyue_run_cnt++;	
//			if(b_yuyue_run_cnt==2)
//			{
//				f_disp_yuyue=1;
//			}
//		}






    }
}




