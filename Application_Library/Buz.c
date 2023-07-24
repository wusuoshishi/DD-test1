
#include 	"..\Application_Library\Global.h"



typedef	struct
{
    unsigned char	on;	 	//打开时间(单位20ms)
    unsigned char	all;	//总时间 (单位20ms)
    unsigned char	cnt;	//响次数
	//unsigned char	type;	//种类
} str_buz;


unsigned char	b_buzKind=0;	//蜂鸣器响声的种类
unsigned char	xdata	b_buzNum=0;
unsigned char	xdata	b_buzTable=0;
unsigned char	xdata	b_buzCnt=0;	//响的次数
unsigned char	xdata	b_buzType=0;//蜂鸣器响声的类别

unsigned char	xdata	b_buz_SP_cnt=0;	//形成100ms
unsigned char	xdata	b_SP_n=0;	//特殊占空比




bit		f_buzFre=0;
bit		f_buzRun=0;	//0:蜂鸣器播放完成
bit		f_buzOn=0;


//str_buz  const	code	tab_buz[]=
//{
//	//单位20ms
//   //ON  ALL CNT	//此处定义种类
//    { 4, 6,  1,1},	//1.按键音 占空比8%时长80ms
//	{ 12, 16, 4,2},	//2.报警音 4组 占空比15% 时长 240ms >> 停 80ms 
//	{33, 57,  1,3},	//3.开机音 占空比:从8%变化到0%时666ms 停480ms
//	{ 4, 6,  2,4},	//4.进入工作音 占空比8%时长80ms >>停40ms >>从 8%变化到 0% 时长 666ms
//    { 4, 6,  8,4},	//5.完成音 4组 占空比8%时长80ms + 停 40ms + 从 8%变化到 0% 时长 600ms >> 480ms
//    
//    { 5, 25, 10,0},
//    {10, 50, 10,0},
//    {10, 50, 10,6},
//    { 5, 25, 10,6}
//};


str_buz  const	code	tab_buz[]=
{
	//单位20ms
	/*响的时间,总时间,次数*/
    {8,16,1},	//按键音					 //此处定义种类
    {26,50,1}, //上电长鸣
    {8,25,5},	//功能完成
    {5,10,3},
    {5,10,3},
    {10,50,10},
    {10,50,10},
    {10,50,10},
    {5,25,10}
};



/*-----------------------------------------------------------------
函数名称： void	buz_ring(void)
函数功能： 响蜂鸣器,放中断
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/
void	buz_ring()
{
#if	buz2K
    if(f_buzOn)
    {
        f_buzFre=~f_buzFre;
        if(f_buzFre)
        {
            if(p_buz_get)
            {
                p_buz_l;
            }
            else
            {
                p_buz_h;
            }
        }
    }
#else
    if(f_buzOn)
    {
        if(p_buz_get)
        {
            p_buz_l;
        }
        else
        {
            p_buz_h;
        }
    }
#endif
}

/*-----------------------------------------------------------------
函数名称： void	open_buz(unsigned char i)
函数功能： 蜂鸣器响声音种类选择
输入参数： 声音类型
返 回 值： 无
-----------------------------------------------------------------*/

void	open_buz(unsigned char i)
{
    b_buzKind=i;
}



/*-----------------------------------------------------------------
函数名称： void	buz_deal(void)
函数功能： 蜂鸣器响声音处理
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/

void	buz_deal()
{
    if(b_buzKind)
    {
        b_buzTable=b_buzKind-1;
        b_buzKind=0;
        b_buzCnt=tab_buz[b_buzTable].cnt;
        b_buzNum=0;
        f_buzOn=0;
        f_buzRun=1;

		#if   c_ad_buz_com
        ADC_PD(1);//关闭ADC模块
        ADC_SCAN_CLR;
        ADC_IE_CLR;
        ADC_IO_SEL1=0;
        ADC_IO_SEL2=0;
        ADC_IO_SEL3=0;
        ADC_IO_SEL4=0;
		#endif
    }

    if(f_buzRun)
    {
        b_buzNum++;
        if(b_buzNum<=tab_buz[b_buzTable].on)
        {
            f_buzOn=1;
            p_buz_out;

        }
        else
        {
            f_buzOn=0;
            buz_disEN;
        }

        if(b_buzNum==tab_buz[b_buzTable].all)
        {
            b_buzCnt--;
            b_buzNum=0;
            if(b_buzCnt==0)
            {
                f_buzRun=0;
                f_buzOn=0;
                buz_disEN;
            }
        }
    }

}



/*特殊处理,用PWM驱动*/
//void	buz_deal()
//{
//    if(b_buzKind)
//    {
//		/*获取该种种类的信息*/
//        b_buzTable=b_buzKind-1;
//        b_buzKind=0;
//        b_buzCnt=tab_buz[b_buzTable].cnt;	//蜂鸣器响的次数
//		b_buzType=tab_buz[b_buzTable].type;//蜂鸣器响声的类别
//        b_buzNum=0;
//        f_buzOn=0;
//        f_buzRun=1;	//0:蜂鸣器播放完成
//
//		//类别>=3时,关机音时
//		if(b_buzType>=3)
//		{
//			//初始化占空比
//			b_SP_n=7;	
//			b_buz_SP_cnt=0;	//初始化特殊计数
//		}
//
//		#if   c_ad_buz_com
//        ADC_PD(1);//关闭ADC模块
//        ADC_SCAN_CLR;
//        ADC_IE_CLR;
//        ADC_IO_SEL1=0;
//        ADC_IO_SEL2=0;
//        ADC_IO_SEL3=0;
//        ADC_IO_SEL4=0;
//		#endif
//    }
//
//    if(f_buzRun)
//    {	
//
//		if(b_buzType!=4)
//		{
//        	b_buzNum++;
//
//			/*开启的总时间*/
//        	if(b_buzNum<=tab_buz[b_buzTable].on)
//        	{
//        	    f_buzOn=1;
//        	    p_buz_out;
//        	}
//        	else
//        	{
//        	    f_buzOn=0;
//        	    //buz_disEN;
//				//关
//				PWM0C_Set(2000,100);	//(频率,占空比)
//
//        	}
//
//			/*总周期*/
//        	if(b_buzNum==tab_buz[b_buzTable].all)
//        	{
//        	    b_buzCnt--;
//        	    b_buzNum=0;
//        	    if(b_buzCnt==0)
//        	    {
//        	        f_buzRun=0;	//0:蜂鸣器播放完成
//        	        f_buzOn=0;
//        	        //buz_disEN;
//					//关
//					PWM0C_Set(2000,100);	//(频率,占空比)
//					
//        	    }
//			}
//
//		}	
//		else
//		{
//			if(b_buzCnt==8)
//				b_buzTable=0;//(1-1)	//按钮音时间
//			else if(b_buzCnt==7)
//				b_buzTable=2;//(3-1)	//开机音时间
//			else if(b_buzCnt==6)
//				b_buzTable=0;//(1-1)	//按钮音时间
//			else if(b_buzCnt==5)
//				b_buzTable=2;//(3-1)	//开机音时间
//			else if(b_buzCnt==4)
//				b_buzTable=0;//(1-1)	//按钮音时间							
//			else if(b_buzCnt==3)
//				b_buzTable=2;//(3-1)	//开机音时间
//			else if(b_buzCnt==2)
//				b_buzTable=0;//(1-1)	//按钮音时间
//			else if(b_buzCnt==1)
//				b_buzTable=2;//(4-1)	//开机音时间		
//			else
//				b_buzTable=0;//(1-1)	//按钮音时间
//
//	        b_buzNum++;
//			/*开启的总时间*/
//        	if(b_buzNum<=tab_buz[b_buzTable].on)
//        	{
//        	    f_buzOn=1;
//        	    p_buz_out;
//        	}
//        	else
//        	{
//        	    f_buzOn=0;
//        	    //buz_disEN;
//				//关
//				PWM0C_Set(2000,100);	//(频率,占空比)
//        	}
//
//			/*总周期*/
//        	if(b_buzNum>=tab_buz[b_buzTable].all)
//        	{
//        	    b_buzCnt--;
//        	    b_buzNum=0;
//        	    if(b_buzCnt==0)
//        	    {
//        	        f_buzRun=0;	//0:蜂鸣器播放完成
//        	        f_buzOn=0;
//        	        //buz_disEN;
//        	    }
//				//初始化占空比
//				b_SP_n=7;	
//				b_buz_SP_cnt=0;	//初始化特殊计数
//
//
//			}		
//		}
//
//    
//    }
//
//
//	/*特殊处理*/
//	if(f_buzOn)
//	{
//		if(b_buzType==1)	//按键音
//			PWM0C_Set(2000,(100-7));	//(频率,占空比)
//		else if(b_buzType==2)//报警音
//			PWM0C_Set(2000,(100-15));	//(频率,占空比)
//		else if(b_buzType==3)//开机音
//		{
//			b_buz_SP_cnt++;	//特殊计数,形成100ms
//			if(b_buz_SP_cnt>=6)
//			{
//				b_buz_SP_cnt=0;
//				/*100ms进入一次*/
//				if(b_SP_n>0)
//				{
//					b_SP_n--;
//				}
//						
//			}
//				if(b_SP_n>0)
//				{
//					PWM0C_Set(2000,(100-b_SP_n));	//(频率,占空比)
//				}
//				else
//				{
//					PWM0C_Set(2000,100);	//(频率,占空比)
//				}
//		}
//		else if(b_buzType==4)//工作音
//		{
//			//3-1 开机音
//			//1-1 按钮音
//			if(b_buzTable==0)
//			{
//				//按钮音时间
//				PWM0C_Set(2000,(100-7));	//(频率,占空比)	
//			}
//			else if(b_buzTable==2)
//			{
//				b_buz_SP_cnt++;	//特殊计数,形成100ms
//				if(b_buz_SP_cnt>=5)
//				{
//					b_buz_SP_cnt=0;
//					/*100ms进入一次*/
//					if(b_SP_n>0)
//					{
//						b_SP_n--;
//					}
//				}
//
//				if(b_SP_n>0)
//				{
//					PWM0C_Set(2000,(100-b_SP_n));	//(频率,占空比)
//				}
//				else
//				{
//					PWM0C_Set(2000,100);	//(频率,占空比)
//				}
//
//			}
//			
//		
//		
//		
//		}
//	
//	}
//	else
//	{	
//		//关
//		PWM0C_Set(2000,100);	//(频率,占空比)
//
//		//PWM0C_Set(2000,0);	//(频率,占空比)
//		b_buz_SP_cnt=0;	//特殊计数,形成100ms
//			//初始化占空比
//			b_SP_n=7;
//	}
//
//
//
//
//	
//
//
//
//
//}







