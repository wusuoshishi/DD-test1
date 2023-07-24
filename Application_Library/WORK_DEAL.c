#include 	"..\Application_Library\Global.h"


uchar	xdata	b_mode=0;
uchar	xdata	b_ctrl_status=0;
uchar f_out_out =0;
uchar xdata	b_wendu_ok=0;	//达到目标温度的次数
uchar	xdata	b_wendu_min=0;

uchar	xdata	b_mjs_set_sec=0;

uchar	xdata	b_baowen_hour=0;
uchar	xdata	b_baowen_min=0;
uchar	xdata	b_baowen_sec=0;

uchar	xdata	b_yuyue_hour=0;
uchar	xdata	b_yuyue_min=0;
uchar	xdata	b_yuyue_sec=0;

uchar	xdata	b_dingshi_hour=0;
uchar	xdata	b_dingshi_min=0;
uchar	xdata	b_dingshi_sec=0;

uchar	xdata	b_ctrl_sec_1=0;
uchar	xdata	b_ctrl_cnt=0;
uchar	xdata	b_ctrl_cnt1=0;
uchar	xdata	b_ctrl_cnt2=0;
uint	xdata	b_ctrl_sec_2=0;
uchar	xdata	b_ctrl_sec_3=0;


uchar	xdata	b_grade=0;	//档位
uchar	xdata	b_set_wendu=0;	//设定的温度

uchar xdata b_yuyue_run_cnt =0;	//预约倒计时进行时长计数



/*暖菜机定义*/
bit		f_sys_power_1=0;  //左边(A) 0:关,1:开
bit		f_sys_power_2=0;  //右边(B) 0:关,1:开
//
bit     f_sys_on_1=0;     //左边(A) 0:待机,1:开机
bit     f_sys_on_2=0;     //左边(A) 0:待机,1:开机



uchar	tab_huo_guo_9[] = {5,10,15,20,25,30,35,40,45};
uchar	tab_huo_guo_5[] = {25,30,35,40,45};



#if	double_ad_channel
uchar	xdata	b_temp_1_ref_sec=0;
uchar	xdata	b_temp_1_ref=0;
#endif



bit	f_power_power=0;

//主状态
bit	f_mjs_set=0;
bit	f_mjs_dingshi=0;
bit	f_mjs_yuyue=0;
bit	f_mjs_power=0;
bit	f_mjs_down=0;
bit	f_dingshi_begin=0;


bit	f_NO_jiangdang=0;	//降档标志位 0:可降档 1:不可降档


bit		f_relay_change=0;
bit		f_jdq=0;
bit		f_jdq2=0;
bit		f_jdq3=0;

bit		f_test=0;
uchar	xdata	b_test=0;
uchar	xdata	b_test_out_time=0;
uchar	xdata	b_test_mode=0;

#if   kkg_en
uchar	xdata	b_zeor_pre=0;
uchar	xdata	b_delay_kkg=0;
uint	xdata	b_out_ctrl=0;
uint	xdata	b_out_ctrl2=0;


uchar	xdata	b_kkg_count=0;
uchar	xdata	b_high_level=0; //左可控硅,高电平时间1

uchar	xdata	gb_kkg=0;
uchar	xdata	b_kkg_buf=0;
bit		f_delay_kkg=0;
bit		f_high_time=0;  //左可控硅 0:关闭,1:输出
#endif


void	work_deal();	//工作处理

void	next_step();	//下一流程
void	shutdown_power();
void	gaoyuan_heat(uchar b_para);
void	heat_hdle(uchar	b_parameter);	//间断性加热
void	intermittent(uint b_on,uint b_all);	//间断性加热

void	baowen_hdle(uchar b_temp1,uchar b_temp2,uchar b_para);	//在指定温度内,按占空比加热
void	three_heat(uchar b_wdvalue,uchar heat1,uchar tmp1,uchar heat2,uchar tmp2,uchar heat3,uchar tmp3,uchar heat4);
void	action_work();
void	quit_work();



#if 1	//其他流程
void	zhu_mode_0();	//流程1
void	zhu_mode_1();	//流程1

void	zhu_mode_4();	//流程4


void	zhu_mode_chao();	//爆炒,火锅 流程1,6
void	zhu_mode_dunzhu();	//炖煮		流程2
void	zhu_mode_qingzheng();//清蒸		流程3
void	zhu_mode_mandun();	//慢炖		流程4
void	zhu_mode_niupai();	//牛排      流程5
void	zhu_mode_bb();	//保温
void	zhu_mode_chao_SP()	;


void	baowen_mode_hdle();	//保温流程
void	zhufan_hdle_ONE();	//煮饭流程





#endif


//	流程声明
#if 0	//饭煲 双探头流程
/*双探头流程*/
void	tang_hdle_TWO();	//煲汤流程
void	zhuzhou_hdle_TWO();	//煮粥流程
void	tangshui_hdle_TWO();//糖水流程
void	zhufan_hdle_TWO();	//煮饭流程
void	zheng_hdle_TWO();	//蒸流程
#endif

#if 0	//饭煲 单探头流程
/*单探头流程*/
void	tang_hdle_ONE();	//煲汤流程
void	zheng_hdle_ONE();	//蒸流程
void	zhuzhou_hdle_ONE();	//煮饭流程
void	zhufan_hdle_ONE();	//煮饭流程
void	dangao_hdle_ONE();	//蛋糕流程
void	suannai_hdle_ONE(); //酸奶流程
void	dun_hdle_ONE();		//炖流程
void	refan_hdle_ONE();	//热饭流程
#endif



/*-----------------------------------------------------------------
函数名称： void	work_deal(void)
函数功能： 工作处理
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	work_deal()
{
    //uint b_share_cnt1,b_share_cnt2;
    uchar   b_jdq_buf_1=0;    //可控硅输出缓存左
    f_jdq=0;	//继电器 关
	b_kkg_buf=0;	//可控硅关

	/*不在爆炒,清*/
	if(b_mode!=1)
		b_wendu_ok=0;	//达到目标温度的次数




	/*待机状态下,清模式*/
    if(!(f_mjs_set||f_mjs_yuyue||f_mjs_dingshi||f_mjs_power))
    {
		b_mode=0;

	}    
		
	/*不在运行状态,不能倒计时标志位*/
    if(!f_mjs_power)
        f_dingshi_begin=0;
	/*在设置状态,清预约秒*/
	/*不在预约状态,清预约秒*/
    if(f_mjs_set||(!f_mjs_yuyue))
        b_yuyue_sec=0;
	/*在设置状态,清定时秒*/
	/*不在定时状态,清定时秒*/
	/*在预约状态,清定时秒*/
	/*倒计时标志位没打开,清定时秒*/
    if(f_mjs_set||(!f_mjs_dingshi)||f_mjs_yuyue||(!f_dingshi_begin))
        b_dingshi_sec=0;
	/*不在保温模式,清保温时间*/
    if(b_mode!=0x80)
    {
        b_baowen_sec=0;
        b_baowen_min=0;
        b_baowen_hour=0;
    }



    if(!b_warning)
    {
		/*设置状态*/
        if(f_mjs_set)
        {
            if(b_mjs_set_sec>=5)
           {
              	if(b_mode)
				{
					action_work();	//开始工作
					b_time_grade_cnt=0;//;0:档位,5:时间
				}
                else
                    shutdown_power();//关闭所有功能
                //quit_work();
            }
        }


		/*预约状态*/
        if(f_mjs_yuyue)
        {
            if(!f_mjs_set)
            {
			#if	c_yyyc	//为1则预约时间为完成时间
                b_share_cnt1=b_odon_hour*60+b_odon_min;
                b_share_cnt2=b_odoff_hour*60+b_odoff_min;
                if(b_share_cnt2>=b_share_cnt1)
			#else
				/*预约时间清零,则表示预约完成*/
                if(b_yuyue_hour==0 && b_yuyue_min==0)
			#endif
                {
                    f_mjs_yuyue=0;
					f_mjs_dingshi=1;
					f_mjs_power=1;

					f_disp_yuyue=0;
                    
                    next_step();	//下一流程
                    b_ctrl_status=0;
                    open_buz(1);	//工作开始音	
                }
            }
		}

        //	工作时间
        if(f_mjs_dingshi&&f_dingshi_begin)
        {
            if(!f_mjs_set)
            {
                if((b_dingshi_hour==0) && (b_dingshi_min==0) &&(b_mode!=0x80))
                {

                    quit_work();
                    //if(b_mode!=4)
                    open_buz(3);	//工作完成音
					
                    if(b_mode==2 || b_mode==3 ||b_mode==4||b_mode==5)	//功能1,3,4可转保温条件,有酸奶时需要修改此处
                    {
                        f_mjs_power=1;
						f_mjs_dingshi=1;
						f_dingshi_begin=1;
                        //b_mode=0xff;
						b_mode=0x80;	//保温模式
						/*设置默认温度*/
						b_set_wendu=60;	//60℃
	
						/*初始化时间*/
						b_dingshi_hour=24;
						b_dingshi_min=0;
						b_dingshi_sec=0;			




						////初始化保温时间
						//b_baowen_hour=0;
						//b_baowen_min=0;
						//b_baowen_sec=0;

						 
                        next_step();	//下一流程
                        b_ctrl_status=0;
                    }
                }

            }
        }


        //	工作流程
        if(f_mjs_power)
        {
            switch(b_mode)
            {
            	case 1://爆炒
            	    zhu_mode_chao_SP();	//爆炒,火锅 OK
            	    break;
           		case 2://炖煮
					zhu_mode_dunzhu();	//炖煮	OK
                	break;
            	case 3://清蒸
                	//zhufan_hdle_ONE();//煮饭流程
					zhu_mode_qingzheng();	//清蒸 OK
                	break;
            	case 4://慢炖
            	    zhu_mode_mandun();
            	    break;
            	case 5:
					//牛排
            	    zhu_mode_niupai();
            	    break;
            	case 6://火锅
            	    zhu_mode_chao();	//OK
            	    break;

            	case 0x80://保温
            	{
					zhu_mode_bb();	//保温模式
				  	break;
            	}
            default:
                shutdown_power();
                break;
            }
        }		


		/*超温保护*/
        if(gb_wendu>=220)
		{
			f_jdq=0;
			b_kkg_buf=0;
		}




	}


#if   kkg_en
    ///*左可控硅*/
    //if(f_jdq)
    //{
    //  if(f_test)
    //    gb_kkg=10;
    //  else
    //  {
    //      gb_kkg=b_jdq_buf_1;
    //  }
    //}
    //else
    //  gb_kkg=0;


	gb_kkg = b_kkg_buf;


#endif

}





/*-----------------------------------------------------------------
函数名称： void	three_heat(void)
函数功能： 三段加热	 右移原则
输入参数： b_wdvalue   heat1  tmp1  heat2  tmp2  heat3 tmp3  heat4
返 回 值： 无
-----------------------------------------------------------------*/
void	three_heat(uchar b_wdvalue,uchar heat1,uchar tmp1,uchar heat2,uchar tmp2,uchar heat3,uchar tmp3,uchar heat4)
{
    if(b_wdvalue<tmp1)
        heat_hdle(heat1);
    else if(b_wdvalue<tmp2)
        heat_hdle(heat2);
    else if(b_wdvalue<tmp3)
        heat_hdle(heat3);
    else
        heat_hdle(heat4);
}


#if	double_ad_channel
/*-----------------------------------------------------------------
函数名称： void	gaoyuan_heat(void)
函数功能： 高原加热
输入参数： b_para 加热温度
返 回 值： 无
-----------------------------------------------------------------*/
void	gaoyuan_heat(uchar b_para)
{
    if(gb_wendu2>=b_para)
        next_step();

    if(gb_wendu2>=80)
    {
        if((gb_wendu2<(b_temp_1_ref+2)) && (gb_wendu2>(b_temp_1_ref-2)))
        {
            if(b_temp_1_ref_sec>=120)
                next_step();
        }
        else
        {
            b_temp_1_ref=gb_wendu2;
            b_temp_1_ref_sec=0;
        }
    }
    else
    {
        b_temp_1_ref=gb_wendu2;
        b_temp_1_ref_sec=0;
    }

}
#endif


/*-----------------------------------------------------------------
函数名称： void	baowen_hdle(void)
函数功能： 在指定温度内,按占空比加热
输入参数： b_temp1 低温		b_temp2 高温	  b_para 占空比
返 回 值： 无
-----------------------------------------------------------------*/
void	baowen_hdle(uchar b_temp1,uchar b_temp2,uchar b_para)
{
    if(gb_wendu<b_temp1)
        f_power_power=1;
    if(gb_wendu>b_temp2)
        f_power_power=0;
    if(f_power_power)
        heat_hdle(b_para);
}

/*-----------------------------------------------------------------
函数名称： void	heat_hdle(void)
函数功能： 间断性加热	   周期为40秒
输入参数： 加热时间
返 回 值： 无
-----------------------------------------------------------------*/
void	heat_hdle(uchar	b_parameter)
{
    if(b_ctrl_sec_2>=40)
        b_ctrl_sec_2=0;
    if(b_ctrl_sec_2>=b_parameter)
        f_jdq=0;
    else
        f_jdq=1;
}


/*-----------------------------------------------------------------
函数名称： void	intermittent(uchar b_all,uchar b_on)
函数功能： 间断性加热	   周期为40秒
输入参数： 加热时间
返 回 值： 无
-----------------------------------------------------------------*/
void	intermittent(uint b_on,uint b_all)
{
    if(b_ctrl_sec_2>=b_all)
        b_ctrl_sec_2=0;
    if(b_ctrl_sec_2>=b_on)
        f_jdq=0;
    else
        f_jdq=1;
}



/*-----------------------------------------------------------------
函数名称： void	shutdown_power(void)
函数功能： 关闭所有功能
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	shutdown_power()
{
    //open_buz(1);
	open_buz(3);	//完成音
    quit_work();
}


/*-----------------------------------------------------------------
函数名称： void	next_step(void)
函数功能： 下一流程
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	next_step()
{
    f_power_power=0;
    b_ctrl_cnt=0;
    b_ctrl_cnt1=0;
    b_ctrl_cnt2=0;

    b_ctrl_sec_1=0;
    b_ctrl_sec_2=0;
    b_ctrl_sec_3=0;

    b_ctrl_status++;
    b_wendu_min=0xff;

#if   double_ad_channel
    b_temp_1_ref_sec=0;
    b_temp_1_ref=gb_wendu2;
#endif
}


/*-----------------------------------------------------------------
函数名称： void	quit_work(void)
函数功能： 退出工作
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	quit_work()
{	
	/*显示*/
    f_disp_yuyue=0;
    f_disp_dingshi=0;

	/*主状态*/
    f_mjs_dingshi=0;
    f_mjs_yuyue=0;
    f_mjs_set=0;
    f_mjs_power=0;
    f_mjs_down=0;

	f_dingshi_begin=0;

    f_jdq=0;
}

/*-----------------------------------------------------------------
函数名称： void	action_work(void)
函数功能： 开始工作
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	action_work()
{
    //open_buz(4);	//工作开始音
    f_mjs_set=0;	//关闭设置状态

	b_wendu_ok=1;
    //b_led_slide1=5;
    //f_disp_yuyue=0;
    //f_disp_dingshi=0;

	/*非预约状态下,运行*/
    if(!f_mjs_yuyue)
    {
        next_step();
        f_mjs_power=1;
        b_ctrl_status=0;
    }
}



#if out_en
/*-----------------------------------------------------------------
函数名称： void	relay_deal(void)
函数功能： 继电器输出控制,100ms基准
输入参数： 无
返 回 值： 无
-------------------------------------------------------------------*/
void	relay_deal()
{
    if(f_relay_change)
    {
        f_relay_change=0;

        if(f_jdq)
        {
            p_out1h;
        }
        //if(f_jdq2)
        //{
        //    p_out2h;
        //}
        //if(f_jdq3)
        //{
        //    p_out3h;
        //}
    }
    else
    {
        f_relay_change=1;

        if(!f_jdq)
        {
            p_out1l;
        }
        //if(!f_jdq2)
        //{
        //    p_out2l;
        //}
        //if(!f_jdq3)
        //{
        //    p_out3l;
        //}
    }
}
#endif


#if   kkg_en

void	kkg_work_api()
{
    if(p_zero!=b_zeor_pre)
    {

      if(p_zero!=b_zeor_pre)
      {
        
        b_out_ctrl=0;
        b_zeor_pre=p_zero;
        b_delay_kkg=0;
        f_delay_kkg=1;
        
        /*左可控硅*/
        if(b_kkg_count<gb_kkg)
            f_high_time=1;
        else
            f_high_time=0;
        b_high_level=0;     //高电平时间1
        

        b_kkg_count++;
        if(b_kkg_count>=100)   //96  //过EMC电压闪烁加大此丢波周期，开通周期相应加大
            b_kkg_count=0;
        

      }
      else
      {
          /*
          if(b_out_ctrl<=30000)
              b_out_ctrl++;
         */
      }
    }
    else
    {
        /*
        if(b_out_ctrl<=30000)
            b_out_ctrl++;
        */
    }

    if(b_out_ctrl>=24000)    //2s无过零则断开所有输出
    {
      
      if(!b_warning&&gb_kkg)
      {
        //quit_work();
        //b_warning|=0x01;
        //b_error_sec=0;
        //open_buz(2);
      }
        #if   c_high_drive
                p_kkgl;
                p_kkg_Bl;
        #else
                p_kkgh;
                p_kkg_Bh;
        #endif
    }
    else
    {
        
        /*左可控硅*/
        if(f_high_time)
        {
            #if   c_high_drive
                p_kkgh;
            #else
                p_kkgl;
            #endif

            if(b_high_level>=48)
            {
                #if   c_high_drive
                    p_kkgl;
                #else
                    p_kkgh;
                #endif
                    f_high_time=0;
            }
            b_high_level++;
        }
        else
        {
            #if   c_high_drive
                p_kkgl;
            #else
                p_kkgh;
            #endif
        }

    }
}
#endif




#if 1 //其他流程

void	zhu_mode_0()	//蒸煮,一直全功率加热,直接结束
{
	f_dingshi_begin=1;
	f_jdq=1;

}



void	zhu_mode_1()	
{
	
    uchar temp=0;
	f_dingshi_begin=1;
	/*计时*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }



	/*15分钟后降功率*/
	if((b_ctrl_cnt >= 15))	
	{
		temp=13;
		intermittent((uint)temp,45);	//间歇性加热
	}   
	else
	{
		//一开始全功率
		temp=45;
		intermittent((uint)temp,45);	//间歇性加热
	}

}	


void	zhu_mode_chao()	//煎炒,一直煮,指导手动关闭
{
	uchar	temp=0;

	//f_dingshi_begin=1;
	/*计时*/
    if(b_ctrl_sec_1>=200)
    {
        b_ctrl_sec_1=200;
    }

	/*爆炒模式,没有6次P3.而是直接可以调功率*/
	if(b_mode==1)
	{
		b_ctrl_sec_1=200;
	}


	/*前118s,开10停8*/
	/*后面按照档位来*/
	if(b_ctrl_sec_1<112)
	{
		intermittent(10,18);	//间歇性加热
	}
	else
	{
		//间歇性加热
		temp=tab_huo_guo_5[b_grade-1];
		intermittent((uint)temp,18);	//间歇性加热
	}

}

//煎炒,有点特殊
void	zhu_mode_chao_SP()	
{
	//static uchar b_wendu_ok=0;	//达到目标温度的次数
	uchar	temp=0;	
	uchar	b_i=0;
	b_set_wendu =200;

    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }


	if(b_wendu_ok==1)
	{
		if (gb_wendu < b_set_wendu-80)
		{
			//f_jdq=1;
			b_kkg_buf=0;

			//间歇性加热
			temp=tab_huo_guo_5[b_grade-1];
			intermittent(temp,45);	//间歇性加热
			
		}		
		else
		{
			f_jdq=0;
			b_kkg_buf=((b_set_wendu-gb_wendu)/6);
		}
		if(gb_wendu>=b_set_wendu)
		{
			b_wendu_ok=2;
		}
		
		if(b_grade>=4)
			b_i=2;
		else if(b_grade>=2)	
		{
			b_i=3;
		}
		else
		{
			b_i=4;	
		}

		/*进入下一流程*/
		if(b_ctrl_cnt>=b_i)
		{
			b_wendu_ok=2;
		}

		/*前5秒前超过150℃的,直接跳下一流程*/
		if(b_ctrl_cnt==0 && b_ctrl_sec_1<5)
		{
			if(gb_wendu>150)
			{
				b_wendu_ok=2;
			}
		}
	}
	else if(b_wendu_ok>=2)
	{
		if (gb_wendu < b_set_wendu-50)
		{
			f_jdq=1;
			b_kkg_buf=0;
			b_ctrl_sec_2=10;	//下一流程先关
			b_wendu_ok=3;
		}
		else if(gb_wendu < b_set_wendu-10)	//20
		{
			b_kkg_buf=0;
			intermittent(10,22);	//间歇性加热
			b_wendu_ok=4;
		}		
		else
		{
			if(gb_wendu>=b_set_wendu)
			{
				f_jdq=0;
				b_kkg_buf=0;
				b_wendu_ok=6;
			}
			else
			{
				f_jdq=0;
				b_kkg_buf=((b_set_wendu-gb_wendu))*3;
				b_wendu_ok=5;
			}					
		}			
	}

}





/*炖煮*/
void	zhu_mode_dunzhu()	
{
	f_dingshi_begin=1;

	//f_dingshi_begin=1;
	/*计时*/
    if(b_ctrl_sec_1>=200)
    {
        b_ctrl_sec_1=200;
    }


	/*前118s,开10停8*/
	/*后面开7停11*/
	if(b_ctrl_sec_1<112)
	{
		intermittent(10,18);	//间歇性加热
	}
	else
	{
		intermittent(7,18);	//间歇性加热
	}
}





/*清蒸*/
void	zhu_mode_qingzheng()
{
    uint temp=0;
	f_dingshi_begin=1;
	/*计时*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	temp=b_ctrl_cnt*60+b_ctrl_sec_1;

	/*前112s,开10停8*/
	/*后全功率3分10s*/
	/*之后开7停11*/
	if(temp<112)
	{
		intermittent(10,18);	//间歇性加热
	}
	else if(temp<302)
	{
		intermittent(18,18);	//间歇性加热
	}
	else
	{
		intermittent(7,18);	//间歇性加热
	}
}

/*慢炖,*/
void	zhu_mode_mandun()	
{
	
    uint temp=0;
	f_dingshi_begin=1;
	/*计时*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	temp=b_ctrl_cnt*60+b_ctrl_sec_1;

	/*前112s,开10停8*/
	/*112-295,全开*/
	/*开4停14*/
	if(temp<112)
	{
		intermittent(10,18);	//间歇性加热
	}
	else if(temp<295)
	{
		intermittent(18,18);	//间歇性加热
	}
	else
	{
		intermittent(4,18);	//间歇性加热
	}

}	


/*牛排*/
void	zhu_mode_niupai()	
{
	
    uint temp=0;
	f_dingshi_begin=1;
	/*计时*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	temp=b_ctrl_cnt*60+b_ctrl_sec_1;

	/*前112s,开10停8*/
	/*后面开6停6*/
	if(temp<112)
	{
		intermittent(10,18);	//间歇性加热
	}
	else
	{
		intermittent(6,12);	//间歇性加热
	}

}	






/*自动保温*/
void	zhu_mode_bb()
{
	bit f_out_temp=0;	//1:输出 0:不输出

	f_dingshi_begin=1;
	//intermittent(2,18);	//间歇性加热
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	if(b_set_wendu<100)
	{
		if (gb_wendu < b_set_wendu-5)
		{
			f_jdq=1;
		}
		else if (gb_wendu < b_set_wendu)
		{
			f_jdq=0;
			b_kkg_buf=20;
		}
		else
		{
			f_jdq=0;
			b_kkg_buf=0;
		}
	}
	else
	{
		//static uchar b_wendu_ok=0;	//达到目标温度的次数
		
		
		if(b_wendu_ok==1)
		{
			if (gb_wendu < b_set_wendu-80)
			{
				f_jdq=1;
				b_kkg_buf=0;
				
			}		
			else
			{
				f_jdq=0;
				b_kkg_buf=((b_set_wendu-gb_wendu)/6);

			}

			if(gb_wendu>=b_set_wendu)
			{
				b_wendu_ok=2;
			}

			if(b_ctrl_cnt>=2)
			{
				b_wendu_ok=2;
			}
		}
		else if(b_wendu_ok>=2)
		{
			if (gb_wendu < b_set_wendu-50)
			{
				f_jdq=1;
				b_kkg_buf=0;
				b_ctrl_sec_2=10;	//下一流程先关
				b_wendu_ok=3;
			}
			else if(gb_wendu < b_set_wendu-10)	//20
			{
				b_kkg_buf=0;
				intermittent(10,22);	//间歇性加热
				b_wendu_ok=4;
			}		
			else
			{
				if(gb_wendu>=b_set_wendu)
				{
					f_jdq=0;
					b_kkg_buf=0;
					b_wendu_ok=6;
				}
				else
				{
					f_jdq=0;
					b_kkg_buf=((b_set_wendu-gb_wendu))*3;


					b_wendu_ok=5;
				}					
			}			
		}

	}

}






/*保温流程处理*/
void	baowen_mode_hdle()
{
	

	if(gb_wendu<45)
	{
		f_out_out=1;
	}

	if (gb_wendu>55)
	{
		f_out_out=0;
	}


	if(f_out_out)
	{
		f_jdq=1;
	}
	else
	{
		f_jdq=0;
	}




	
//	/*计时*/
//    if(b_ctrl_sec_1>=60)
//    {
//        b_ctrl_sec_1=0;
//		if(b_ctrl_cnt<255)
//        	b_ctrl_cnt++;
//    }
//
//	/*0-5分钟,开14s关31s*/
//	/*5-10分钟,关*/
//	/*10分钟后,按照开150s关570s一直循环*/
//
//	if(b_ctrl_cnt<5)
//	{
//		intermittent(14,45);	//间歇性加热
//
//	}
//	else if (b_ctrl_cnt>=5 && b_ctrl_cnt<10)
//	{
//		f_jdq=0;
//		b_ctrl_sec_2=0;
//	}
//	/*开两分半钟,停9分半分钟*/
//	/*开150s 关570s*/
//	else if(b_ctrl_cnt>=10)
//	{
//		intermittent(150,720);	//间歇性加热
//	}	
	
	/*默认保温时间2h*/
	if(b_baowen_hour>=6)
    {
        shutdown_power();
        open_buz(5);	//工作完成音
    }
}


void	zhufan_hdle_ONE()
{
    f_dingshi_begin = 1;
    switch(b_ctrl_status)
    {
    case 0:
		/*计时*/
        if(b_ctrl_sec_1>=60)
        {
            b_ctrl_sec_1=0;
            b_ctrl_cnt++;
        }


        if((b_ctrl_cnt >= 5)||(gb_wendu >= 125))
            next_step();

        baowen_hdle(58,60,0x14);
        break;
    case 1:
        next_step();
        break;
    case 2:
        next_step();
        break;
    case 3:
		/*计时*/
        if(b_ctrl_sec_3>=60)
        {
            b_ctrl_sec_3=0;
            b_ctrl_cnt2++;
        }

		/*转下一流程的条件*/
		/*1.超过50min后,转下一流程*/
		/*2.超过连续120℃,60s进入下一流程*/
		/*3.*/
        if(b_ctrl_cnt2>=50)
            next_step();
        else
        {
            if(gb_wendu>=120)
            {
                b_ctrl_cnt1=0x01;
                if(b_ctrl_cnt>=10)
                    next_step();
                else if(b_ctrl_sec_1>=60)
                    next_step();
            }
            else
            {
                if(b_ctrl_cnt1==0x01)
                {
                    b_ctrl_cnt1=0;
                    b_ctrl_cnt++;
                }
                b_ctrl_sec_1=0;

                //if(b_ctrl_cnt2>=15)	
                //    heat_hdle(0xff);
                //else if(b_ctrl_cnt2>=10)
                //    heat_hdle(0x20);
                //else
                //    heat_hdle(0x19);	

                if(b_ctrl_cnt2>=15)	
                    heat_hdle(25);
                else if(b_ctrl_cnt2>=10)
                    heat_hdle(28);
                else
                    heat_hdle(20);	

            }
        }
        break;
    case 4:
        if(gb_wendu <= 105)
            b_ctrl_cnt = 0x01;
        if(b_ctrl_cnt == 0x01)
        {
            if(gb_wendu >= 107)
                next_step();
            heat_hdle(0x0f);
        }
        break;
    case 5:
        baowen_hdle(100,103,10);//0x0f
        break;
    default:
        shutdown_power();
        break;
    }

}

#endif












#if 0 //单探头流程


//---------------------酸奶----------------------
void	suannai_hdle_ONE()
{
    f_dingshi_begin = 1;
    three_heat(gb_wendu,0x14,30,0x0a,35,0x05,40,0x00);
}


//---------------------单探头炖汤----------------------
void	dun_hdle_ONE()
{
    f_dingshi_begin = 1;
    three_heat(gb_wendu,0xff,85,0x1e,90,0x0f,95,0x05);
}


//---------------------蒸,隔水炖----------------------
void	zheng_hdle_ONE()
{
    f_dingshi_begin = 1;
    if(gb_wendu >= 95)
    {
        heat_hdle(0x0f);
    }
    else
    {
        heat_hdle(0xff);
    }
}

//---------------------单探头煲汤----------------------
void	tang_hdle_ONE()
{
    f_dingshi_begin = 1;
    three_heat(gb_wendu,0xff,85,0x1e,90,0x14,95,0x0a);
}

//---------------------单探头煮粥/稀饭----------------------
void	zhuzhou_hdle_ONE()
{
    uchar	b_tmp=0;
    f_dingshi_begin = 1;

    switch(b_ctrl_status)
    {
    case 0:
        if(gb_wendu <= 90)
            next_step();
        break;
    case 1:
        if(b_ctrl_sec_3>=60)
        {
            b_ctrl_sec_3=0;
            b_ctrl_cnt2++;
        }
        if(b_ctrl_cnt2>=50)
            next_step();
        else
        {
            b_tmp = 93;	//设定温度

            if(gb_wendu < b_wendu_min)
                b_wendu_min = gb_wendu;

            if((b_ctrl_cnt==0)||(!f_power_power))
                b_wendu_min = 255;

            if((!f_power_power)&&(gb_wendu>b_tmp))
                b_ctrl_cnt |= 0x01;

            if((b_ctrl_cnt!=0)&&(f_power_power)&&(gb_wendu>b_tmp+1))
            {
                if(b_wendu_min<255)
                {
                    if(b_tmp<b_wendu_min+3)
                        next_step();
                }
            }
            if(b_wendu_min>b_tmp-3)
                baowen_hdle(b_tmp,b_tmp+2,0xff);
            else
                baowen_hdle(b_tmp,b_tmp+5,0xff);

            if((!f_power_power)||(gb_wendu<b_tmp+2))
                b_ctrl_sec_1=0;

            if(b_ctrl_sec_1>120)
                f_power_power=0;
        }
        break;
    case 2:
        b_tmp=150;
        b_tmp+=b_ctrl_cnt*8;
        if(b_tmp>=177)
            b_tmp=177;

        if(b_ctrl_sec_1>=210)
        {
            b_ctrl_sec_1=0;
            b_ctrl_cnt++;
        }
        if(b_ctrl_sec_1>=b_tmp)
            f_jdq=1;
        break;
    default:
        break;

    }
}



//---------------------单探头煮饭----------------------
void	zhufan_hdle_ONE()
{
    f_dingshi_begin = 1;
    switch(b_ctrl_status)
    {
    case 0:
        if(b_ctrl_sec_1>=60)
        {
            b_ctrl_sec_1=0;
            b_ctrl_cnt++;
        }
        if((b_ctrl_cnt >= 5)||(gb_wendu >= 125))
            next_step();

        baowen_hdle(58,60,0x14);
        break;
    case 1:
        next_step();
        break;
    case 2:
        next_step();
        break;
    case 3:
        if(b_ctrl_sec_3>=60)
        {
            b_ctrl_sec_3=0;
            b_ctrl_cnt2++;
        }
        if(b_ctrl_cnt2>=50)
            next_step();
        else
        {
            if(gb_wendu>=120)
            {
                b_ctrl_cnt1=0x01;
                if(b_ctrl_cnt>=10)
                    next_step();
                else if(b_ctrl_sec_1>=60)
                    next_step();
            }
            else
            {
                if(b_ctrl_cnt1==0x01)
                {
                    b_ctrl_cnt1=0;
                    b_ctrl_cnt++;
                }
                b_ctrl_sec_1=0;

                if(b_ctrl_cnt2>=15)
                    heat_hdle(0xff);
                else if(b_ctrl_cnt2>=10)
                    heat_hdle(0x20);
                else
                    heat_hdle(0x19);
            }
        }
        break;
    case 4:
        if(gb_wendu <= 105)
            b_ctrl_cnt = 0x01;
        if(b_ctrl_cnt == 0x01)
        {
            if(gb_wendu >= 107)
                next_step();
            heat_hdle(0x0f);
        }
        break;
    case 5:
        baowen_hdle(100,103,0x0f);
        break;
    default:
        shutdown_power();
        break;
    }

}



//---------------------蛋糕----------------------
void	dangao_hdle_ONE()
{
    f_dingshi_begin=1;
    if(gb_wendu >= 80)
        baowen_hdle(129,130,0x0f);
    else
        heat_hdle(0xff);
}


//---------------------热饭----------------------
void	refan_hdle_ONE()
{
    f_dingshi_begin=1;
    if(gb_wendu >= 80)
        baowen_hdle(105,110,0x14);
    else
        heat_hdle(0xff);
}


#endif










#if 0	//需要双探头的流程

//---------------------双探头蒸----------------------
void	zheng_hdle_TWO()
{
    f_dingshi_begin=1;
    three_heat(gb_wendu2,0xff,60,0x14,95,0x0f,98,0x0a);
}



//---------------------双探头煮粥----------------------
void	zhuzhou_hdle_TWO()
{
    f_dingshi_begin=1;
    switch(b_ctrl_status)
    {
    case 0:
        if(gb_wendu < 110)
            heat_hdle(0xff);
        if(gb_wendu2 >= 80)
            next_step();
        break;
    case 1:
        heat_hdle(0x14);

        if(gb_wendu2 >= 90)
            next_step();
        break;
    case 2:
        three_heat(gb_wendu2,0x0f,90,0x08,95,0x05,99,0x03);
        break;
    default:
        shutdown_power();
        break;
    }
}


//---------------------双探头煲汤----------------------
void	tang_hdle_TWO()
{
    f_dingshi_begin=1;
    switch(b_ctrl_status)
    {
    case 0:
        next_step();
        break;
    case 1:
        if(gb_wendu2>=80)
            next_step();
        baowen_hdle(105,110,0xff);
        break;
    case 2:
        three_heat(gb_wendu2,0x14,90,0x0f,95,0x0a,99,0x06);
        break;
    default:
        shutdown_power();
        break;
    }
}

//---------------------双探头糖水----------------------
void	tangshui_hdle_TWO()
{
    f_dingshi_begin=1;
    switch(b_ctrl_status)
    {
    case 0:
        next_step();
        break;
    case 1:
        if((b_ctrl_cnt>=20)||(gb_wendu2>=80))
            next_step();
        baowen_hdle(100,105,0x20);
        break;
    case 2:
        three_heat(gb_wendu2,0x0f,90,0x0c,95,0x0a,99,0x08);
        break;
    default:
        shutdown_power();
        break;
    }
}

//---------------------双探头煮饭----------------------
void	zhufan_hdle_TWO()
{
//		f_dingshi_begin=1;
    switch(b_ctrl_status)
    {
    case 0:
        if(b_mode==0x02)
            next_step();

        if(b_ctrl_sec_1>=60)
        {
            b_ctrl_sec_1=0;
            b_ctrl_cnt++;
        }
        if((b_ctrl_cnt>=7)||(gb_wendu>=120))
            next_step();
        baowen_hdle(58,60,0x20);
        break;
    case 1:
        if(gb_wendu >= 130)
            next_step();
        else if(gb_wendu2 >= 80)
            next_step();
        heat_hdle(0xff);
        break;
    case 2:
        if(gb_wendu >= 130)
            next_step();
        heat_hdle(0xff);
        gaoyuan_heat(95);
        break;
    case 3:
        if(gb_wendu<=115)
            next_step();
        break;
    case 4:
        if(gb_wendu>=116)
            next_step();
        heat_hdle(0x19);
        break;
    case 5:
        next_step();
        break;
    case 6:
        next_step();
        break;
    case 7:
        f_dingshi_begin = 1;
        baowen_hdle(103,105,0x0a);
        break;
    default:
        shutdown_power();
        break;
    }
}

#endif


