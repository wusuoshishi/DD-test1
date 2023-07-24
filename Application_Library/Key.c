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
unsigned char	xdata	b_key_cnt=0;	//��������
unsigned char	xdata	b_key_noCnt=0;	//�ͷ�����
unsigned char	xdata	b_key_longcnt=0;

uchar	xdata	Target_wendu_mode_1=0;  //��Ŀ���¶ȵ� 0:��,1:80�棬2:100�棬3:120��
uchar	xdata	Target_wendu_mode_2=0;  //��Ŀ���¶ȵ� 0:��,1:80�棬2:100�棬3:120��
uchar	xdata	set_time_1_hour=0; //��ʱ��
uchar	xdata	set_time_1_min=0;  //
uchar	xdata	set_time_1_sec=0;  //
uchar	xdata	set_time_2_hour=0; //�Ҷ�ʱ��
uchar	xdata	set_time_2_min=0;  //
uchar	xdata	set_time_2_sec=0;  //

uchar	xdata   b_stop_1_sec=0;  //����ͣʱ��
uchar	xdata   b_stop_1_min=0;  //����ͣʱ��
uchar	xdata   b_stop_2_sec=0;  //����ͣʱ��
uchar	xdata   b_stop_2_min=0;  //����ͣʱ��


uchar	xdata	b_force_flash_cnt=0;	//ǿ����˸����
bit	f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
uchar	xdata	b_clock_key =0; //���й�����,�ް�������,1s������


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
    unsigned char	hour_int;	//Сʱ��ʼֵ
    unsigned char	min_int;	//���ӳ�ʼֵ
    unsigned char	hour_max;	//���Сʱ
    unsigned char	min_max;	//������
    unsigned char	hour_min;	//��ССʱ
    unsigned char	min_min;	//��С����
    unsigned char	chg_num;	//����������
	unsigned char	chg_num_1;	//�ݼ�������
	unsigned char	grade_int;	//��λ
	unsigned char	grade_max;	//���λ
	unsigned char	grade_min;	//��С��λ


} str_setscan;


str_setscan		const	code	tab_set[]=
{
	//��ʼʱ��  /���ʱ�� /��Сʱ��   /�ݽ�   /��λ
    {1, 0,   1, 0,	  1, 0,     5, 1,	3,5,1},	//����1 ���� ��λ�ɵ�		
    {0, 5,   1, 0,	  0, 5,     5, 1,	1,1,1},	//����2 ���� ʱ��ɵ�		 
    {0, 5,   1, 0,	  0, 5,     5, 1,	1,1,1},	//����3 ���� ʱ��ɵ�		 
    {0,20,   3, 0,	  0, 5,    20, 5,	1,1,1},  //����4 ���� ʱ��ɵ� 		 
	{3,30 ,  60, 0,	  1, 0,    30,30,	1,1,1},  //����5 ţ�� ʱ��ɵ� ����Ƚ�����,
	{1, 0,   1, 0,	  1, 0,     5, 1,	5,5,1}  //����6 ��� ��λ�ɵ�		 
};

////����
//str_setscan		const	code	tab_set[]=
//{
//	//��ʼʱ��/���ʱ��/��Сʱ��/�ݽ�/��λ
//    {0,20,    1, 0,	  0,15,    5,	5,5,1},	//����1 ���� ʱ��ɵ�
//    {0,30,    1,10,	  0,15,    5,	5,5,1},	//����2 �峴 ��λ�ɵ�
//    {0,30,    0,30,	  0,30,    5,	1,1,1},	//����3 �� ���ɵ�
//    {0,2,    1,30,	  0,15,    5,	5,5,1}  //����4 ���� ʱ��ɵ�
//};



void	key_deal();		//��������,20MSִ��һ��
void	key_scan();		//�������

void	mode_key();		//ģʽ��
void	add_key();		//�Ӽ�
void	dec_key();		//����
void	baowen_yuyu_key();	//����ԤԼ��ť(���������ԤԼ��ť������ͬһ������֮��)

void	mode_init();	//����ģʽ��ʼ��


void	dingshi_add_fun();	//��ʱʱ��ӹ���
void	dingshi_dec_fun();	//��ʱʱ�������
void    baowen_add_fun();	//����ʱ��ӹ���
void    baowen_dec_fun();	//����ʱ�������

void	yuyue_add_fun();	//ԤԼʱ��ӹ���
void	yuyue_dec_fun();	//ԤԼʱ�������
void	grade_add_fun();	//��λ�ӹ���
void	grade_dec_fun();	//��λ������
void	baowen_fun();		//���¹���

void	quit_work();	//�˳�����
void	action_work();	//��ʼ����
void	key_clr_sec();	//ˢ����ʾ�����������
/*-----------------------------------------------------------------
�������ƣ� void	baowen_yuyu_key(void)
�������ܣ� ����ԤԼ��ť
��������� ��
�� �� ֵ�� ��
˵��:���������ԤԼ��ť������ͬһ������֮��
-----------------------------------------------------------------*/
void	baowen_yuyu_key()
{
	baowen_fun();
}


#if	c_key_mode
//�ᴥ����������������������ʾɨ����

//  ����������
void  sw_scan_in()
{
    key_input;
    key_pull;
}

//  �������
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
�������ƣ� void	key_scan(void)
�������ܣ� �������
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	key_scan()
{

    uchar i=0;

#if	c_key_mode

#pragma message "�ᴥ����"
    b_key_value = keysFlagQC;

#else

#pragma message "��������"

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
    //�ް���
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
            /*-----------------------------�˴����ð���----------------------------*/
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
�������ƣ� void	yuyue_add_fun(void)
�������ܣ� ԤԼʱ���
��������� ��
�� �� ֵ�� ��
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
�������ƣ� void	yuyue_dec_fun(void)
�������ܣ� ԤԼʱ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void    yuyue_dec_fun()
{
	//b_yuyue_min=0;
//
    //if(b_yuyue_hour>1)	//��СֵΪ1
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
�������ƣ� void	mode_init(void)
�������ܣ� ����ģʽ��ʼ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void mode_init()
{
	b_mode=1;
	/*��ȡĬ��ʱ��*/
	b_dingshi_hour = tab_set[b_mode-1].hour_int;
    b_dingshi_min  = tab_set[b_mode-1].min_int;


	/*��ȡĬ�ϵ�λ*/
	b_grade=tab_set[b_mode-1].grade_int;

	/*���ö�Ӧ��״̬*/
	f_mjs_set=1;
	f_mjs_dingshi=1;
	//f_mjs_power;
	//f_mjs_yuyue;
	//f_mjs_down;
	//f_dingshi_begin;

	//f_disp_dingshi=0;
	//f_disp_yuyue=0;

	//ʱ����3��
	b_time_grade_cnt =7	;	//0:��λ,5:ʱ��
}


/*-----------------------------------------------------------------
�������ƣ� void	baowen_fun(void)
�������ܣ� ���¹���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	baowen_fun()
{

	f_mjs_set=1;
	f_mjs_dingshi=1;
	//f_mjs_power=0;
	//f_mjs_yuyue=0;

	f_dingshi_begin=1;

	b_mode	|= 0x80;
	
	/*����Ĭ��ʱ��*/
	b_dingshi_hour=24;
	b_dingshi_min=0;
	b_dingshi_sec=0;

	/*����Ĭ���¶�*/
	b_set_wendu=60;	//60��





	///*����Ĭ��ʱ��*/
	////Ĭ��6��Сʱ
	//b_baowen_hour=6;
	//b_baowen_min=0;
	//b_baowen_sec=0;
	//action_work();
}


/*-----------------------------------------------------------------
�������ƣ� void	dingshi_add_fun(void)
�������ܣ� ��ʱʱ��ӹ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void    dingshi_add_fun()
{
	uchar	i=0;

	////��ʾʱ��,ʱ����3��
	//b_time_grade_cnt=7;//;0:��λ,5:ʱ��



	
	/*��ȡÿ�εݽ���ʱ��*/
    if(b_key_longcnt==0)
        i=tab_set[b_mode-1].chg_num;
    else
        i=tab_set[b_mode-1].chg_num;


		/*����ֵ�����ֵ���бȽ�*/
    	if((b_dingshi_hour*60+b_dingshi_min)>=(tab_set[b_mode-1].hour_max*60+tab_set[b_mode-1].min_max))
    	{
			/*���ڵ������ֵ,��ֵ���ֵ*/
    	    key_clr_sec();
    	    b_dingshi_hour=tab_set[b_mode-1].hour_max;
    	    b_dingshi_min=tab_set[b_mode-1].min_max;
    	}
    	else
    	{
			/*��ʱ��,Ȼ����з�Χ�ж�*/
    		key_clr_sec();
    	    b_dingshi_min+=i;
    	    if(b_dingshi_min>=60)
    	    {
    	        b_dingshi_min-=60;
    	        b_dingshi_hour++;
    	    }
			/*����ֵ�����ֵ���бȽ�*/
    	    if((b_dingshi_hour*60+b_dingshi_min)>=(tab_set[b_mode-1].hour_max*60+tab_set[b_mode-1].min_max))
    	    {
				/*���ڵ������ֵ,��ֵ���ֵ*/
    	        key_clr_sec();
    	        b_dingshi_hour=tab_set[b_mode-1].hour_max;
    	        b_dingshi_min=tab_set[b_mode-1].min_max;
    	    }
    	}

}


/*-----------------------------------------------------------------
�������ƣ� void	baowen_add_fun(void)
�������ܣ� ����ʱ��ӹ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void    baowen_add_fun()
{
	uchar	i=0;
	b_dingshi_sec=0;
	i=30;
	key_clr_sec();

	/*����ֵ�����ֵ���бȽ�*/
    if((b_dingshi_hour*60+b_dingshi_min)>=(24*60+0))
    {
		/*���ڵ������ֵ,��ֵ���ֵ*/
        b_dingshi_hour=24;
        b_dingshi_min=0;
    }
    else
    {
		/*��ʱ��,Ȼ����з�Χ�ж�*/
        b_dingshi_min+=i;
        if(b_dingshi_min>=60)
        {
            b_dingshi_min-=60;
            b_dingshi_hour++;
        }
		/*����ֵ�����ֵ���бȽ�*/
        if((b_dingshi_hour*60+b_dingshi_min)>=(24*60+0))
        {
					/*���ڵ������ֵ,��ֵ���ֵ*/
            b_dingshi_hour=24;
            b_dingshi_min=0;
        }
    }

}






/*-----------------------------------------------------------------
�������ƣ� void	dingshi_dec_fun(void)
�������ܣ� ��ʱʱ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	dingshi_dec_fun()
{
	uchar	i=0;
	////��ʾʱ��,ʱ����3��
	//b_time_grade_cnt=7;//;0:��λ,5:ʱ��


	//��ȡÿ�εݽ���ʱ��
    if(b_key_longcnt==0)
    	i=tab_set[b_mode-1].chg_num_1;
    else
        i=tab_set[b_mode-1].chg_num_1;

    key_clr_sec();	//ˢ����ʾ�����������

    if((b_dingshi_hour*60+b_dingshi_min)>=i)	//�ж��ܲ��ܼ�����
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
	/*������,ֱ�Ӹ�ֵֵ֮*/
    else
    {
        b_dingshi_hour=tab_set[b_mode-1].hour_min;
        b_dingshi_min=tab_set[b_mode-1].min_min;
    }

}


/*-----------------------------------------------------------------
�������ƣ� void	baowen_dec_fun(void)
�������ܣ� ����ʱ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	baowen_dec_fun()
{
	uchar	i=0;
	////��ʾʱ��,ʱ����3��
	//b_time_grade_cnt=7;//;0:��λ,5:ʱ��
	b_dingshi_sec=0;
	
	//��ȡÿ�εݽ���ʱ��
    i=30;

    key_clr_sec();	//ˢ����ʾ�����������

    if((b_dingshi_hour*60+b_dingshi_min)>=i)	//�ж��ܲ��ܼ�����
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
	/*������,ֱ�Ӹ�ֵֵ֮*/
    else
    {
        b_dingshi_hour=0;
        b_dingshi_min=0;
    }

}



/*-----------------------------------------------------------------
�������ƣ� void	grade_dec_fun(void)
�������ܣ� ��λ������
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	grade_dec_fun()
{


	b_time_grade_cnt=0;//;0:��λ,5:ʱ��


	#if 1 //����ѭ��
		if(b_grade>tab_set[b_mode-1].grade_min)
			b_grade--;
	#endif

	#if 0 //��ѭ��
		b_grade--;
		/*�ﵽ��Сֵ->���ֵ*/
		if(b_grade<tab_set[b_mode-1].grade_min)
			b_grade=tab_set[b_mode-1].grade_max;
	#endif



	/*����֮����,�Ͳ����Զ�����*/
	if(f_mjs_power)
		f_NO_jiangdang=1;	//������־λ 0:�ɽ��� 1:���ɽ���

}


/*-----------------------------------------------------------------
�������ƣ� void	grade_add_fun(void)
�������ܣ� ��λ�ӹ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	grade_add_fun()
{
	//b_time_grade_cnt=0;//;0:��λ,5:ʱ��

	#if 1 //������ѭ��
	if (b_grade<tab_set[b_mode-1].grade_max)
	{
		b_grade++;
	}
	#endif

	#if 0 //��ѭ��
		b_grade++;
		/*�������ֵ->��Сֵ*/
		if (b_grade>tab_set[b_mode-1].grade_max)
			b_grade=tab_set[b_mode-1].grade_min;
	#endif 


	/*����֮����,�Ͳ����Զ�����*/
	if(f_mjs_power)
		f_NO_jiangdang=1;	//������־λ 0:�ɽ��� 1:���ɽ���

}


/*-----------------------------------------------------------------
�������ƣ� void	key_yuyue(void)
�������ܣ� ԤԼ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void  key_yuyue()
{
	/*��״̬*/
    f_mjs_set=1;
	f_mjs_yuyue=1;
	
	/*��ʾ*/
    f_disp_yuyue=1;
    f_disp_dingshi=0;

	/*Ĭ��ʱ��*/
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
//	/*Ĭ��ԤԼʱ�� 30����*/
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
�������ƣ� void	add_key(void)
�������ܣ� �Ӽ�
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	add_key()
{
    if(f_disp_yuyue && f_mjs_set)
    {
		/*��ԤԼʱ������*/
        //f_mjs_set=1;
        yuyue_add_fun();
    }
    else
    {
		/*����1 6��������*/
        if(b_mode==1 || b_mode==6)
        {
			if(f_clock_key)
			{
				b_force_flash_cnt=0;	//ǿ����˸����
				f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
				b_clock_key =0; //���й�����,�ް�������,1s������
				key_clr_sec();
			}
			else
			{
				b_force_flash_cnt=0;	//ǿ����˸����
				f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
				b_clock_key =0; //���й�����,�ް�������,1s������
				grade_add_fun();	//��λ�ӹ���
			}
		}
        else if(b_mode==2 || b_mode==3 ||b_mode==4 || b_mode==5)
		{
			
			if(f_disp_yuyue)
			{			
				f_disp_yuyue=0;
				b_yuyue_run_cnt=0;
				b_force_flash_cnt=0;	//ǿ����˸����
				f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
				b_clock_key =0; //���й�����,�ް�������,1s������
				key_clr_sec();
			}
			else
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					key_clr_sec();
				}
				else
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������	
					dingshi_add_fun();	//��ʱʱ��ӹ���
				}
				
			}

		}
		else if(b_mode==0x80)
		{	
			/*����ʱ,��ʱ��*/
			if(f_mjs_power)
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					key_clr_sec();
				}
				else
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					baowen_add_fun();	
				}	
			}
			/*������ʱ,���¶�*/
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
�������ƣ� void	dec_key(void)
�������ܣ� �Ӽ�
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	dec_key()
{
    if(f_disp_yuyue && f_mjs_set)
    {
        //f_mjs_set=1;
        yuyue_dec_fun();	//ԤԼʱ���
    }
    else
    {
		/*����1 6��������*/
        if(b_mode==1 || b_mode==6)
        {
			if(f_clock_key)
			{
				b_force_flash_cnt=0;	//ǿ����˸����
				f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
				b_clock_key =0; //���й�����,�ް�������,1s������
				key_clr_sec();
			}
			else
			{	
				b_force_flash_cnt=0;	//ǿ����˸����
				f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
				b_clock_key =0; //���й�����,�ް�������,1s������
				grade_dec_fun();	//��λ�ӹ���	
			}	
        }
        else if(b_mode==2 || b_mode==3 || b_mode==4|| b_mode==5)
		{	if(f_disp_yuyue)
			{			
				f_disp_yuyue=0;
				b_yuyue_run_cnt=0;
				b_force_flash_cnt=0;	//ǿ����˸����
				f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
				b_clock_key =0; //���й�����,�ް�������,1s������
				key_clr_sec();
			}
			else
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					key_clr_sec();
				}
				else
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					dingshi_dec_fun();	//��ʱʱ�������
				}
				
				
			}
			
		}
		else if(b_mode==0x80)
		{	
			/*����ʱ,��ʱ��*/
			if(f_mjs_power)
			{
				if(f_clock_key)
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					key_clr_sec();
				}		
				else
				{
					b_force_flash_cnt=0;	//ǿ����˸����
					f_clock_key	=0;	//1:����,0:����,�ɸı�ʱ�䵵λ
					b_clock_key =0; //���й�����,�ް�������,1s������
					baowen_dec_fun();
				}		
				
			}
			/*������ʱ,���¶�*/
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
�������ƣ� void	mode_key(void)
�������ܣ� ģʽ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	mode_key()
{

	/*���һ��ʼû���κ�״̬,��ģʽ���ܳ�ʼ��*/
	if(!f_mjs_dingshi && !f_mjs_power && !f_mjs_yuyue && !f_mjs_down && !f_mjs_set)
	{
		mode_init();	//����ģʽ��ʼ��
		key_clr_sec();	//ˢ����ʾ�����������
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
		if(b_mode>=7)	//�����4
			b_mode=1;	//ѭ��


		//if (b_mode==3)
		//{
			f_mjs_dingshi=1;
			//f_disp_dingshi=1;
		//}

		/*��ȡĬ��ʱ��*/
    	b_dingshi_hour = tab_set[b_mode-1].hour_int;
    	b_dingshi_min  = tab_set[b_mode-1].min_int;

		/*��ȡĬ�ϵ�λ*/
		b_grade = tab_set[b_mode-1].grade_int;
		key_clr_sec();	//ˢ����ʾ�����������



	}



}




/*-----------------------------------------------------------------
�������ƣ� void	key_clr_sec(void)
�������ܣ� ˢ����ʾ�����������
��������� ��
�� �� ֵ�� ��
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
        open_buz(1);	//������
		//open_buz(2);	//������
		//open_buz(3);	//������
		//open_buz(4);	//������ʼ��
		//open_buz(5);	//���������
}




/*-----------------------------------------------------------------
�������ƣ� void	key_deal(void)
�������ܣ� ��������,20MSִ��һ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	key_deal()
{
    key_scan();

    b_key_double++;   //˫����ʱ����
    if(b_key_double >= 50)
    {
        //	�˳�˫��ʱ��
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
            /*-----------------------------�˴���������----------------------------*/
            switch(b_key_value)
            {
            case c_k1:  //ԤԼ/����
            {	
				/*�ڴ���״̬��,����,�����ֶ�����*/
				if(!f_mjs_set&& !f_mjs_power && !f_mjs_yuyue && !b_mode)
				{
					key_clr_sec();	//ˢ����ʾ�����������
					baowen_fun();	//���¹���
				}
				/*����״̬��,ģʽ2,3,4�ɽ���*/
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
            case c_k2:  //����/ȡ��
            {
				/*�����˰���->�ػ�*/
				if (f_mjs_power)
				{	
					/*�̰�*/
					if(b_key_longcnt==0)
					{
						quit_work();	//�˳�����
						key_clr_sec();	//ˢ����ʾ�����������
						open_buz(1);	//������
					}
				}
				/*ԤԼ����ʱ����->�ػ�*/
				else if (f_mjs_yuyue && !f_mjs_set)
				{	
					/*�̰�*/
					if(b_key_longcnt==0)
					{
						quit_work();	//�˳�����
						key_clr_sec();	//ˢ����ʾ�����������
					}

				}
				else
				{						/*�̰�*/
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


            case c_k3:  //��
            {
                if(b_warning)
                    break;
                //�й��ܲŰ��ö�   
                if(b_mode==0)
                    break;  

				////���¹��ܰ�����
				//if(b_mode&0x80)
				//	break;

				////����3(��)������
				//if(b_mode==3)
				//	break;
				
				////���к�,���˹���2(�峴)��������
				//if(f_mjs_power && (b_mode!=2))
				//	break;


                //key_clr_sec();	//ˢ����ʾ�����������

				//�̰�������������Ӧ
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
            case c_k4:  //��
            {
				//������,������
                if(b_warning)
                    break;

                //�й��ܲŰ��ö�   
                if(b_mode==0)
                    break;  

				////���¹��ܰ�����
				//if(b_mode&0x80)
				//	break;

				////����3(��)������
				//if(b_mode==3)
				//	break;

				////���к�,���˹���2(�峴)��������
				//if(f_mjs_power && (b_mode!=2))
				//	break;

				
                //key_clr_sec();	//ˢ����ʾ�����������

				//�̰�������
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
            //�������
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
//		���ð����������ʹ��ʱֱ�ӽ��临�Ƶ������������У�������ʵ�������Ӧ�޸�
//				�Ӽ�
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


//		����
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

//		ģʽ����ֱ����Ч
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue)))
{
    key_clr_sec();
    mode_key();
    action_work();
}

//		ģʽ����ģʽ+1
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue)))
{
    key_clr_sec();
    mode_key();
}

//		����/ȡ����
key_clr_sec();
if(!f_mjs_power&&(!(!f_mjs_set&&f_mjs_yuyue))&&(!f_mjs_set))
{
    quit_work();
    baowen_yuyu_key();
}
else
    quit_work();

//		��ʼ��
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

//		ԤԼ��
if(((!f_mjs_set)&&(!f_mjs_yuyue)&&(!f_mjs_power)) || f_mjs_set)		//
{
    key_yuyue();
    key_clr_sec();
}


//		ȡ����
if(f_mjs_power || f_mjs_set || f_mjs_yuyue)
{
    key_clr_sec();
    quit_work();
}

#endif




