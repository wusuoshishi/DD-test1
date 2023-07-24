#include 	"..\Application_Library\Global.h"


uchar	xdata	b_mode=0;
uchar	xdata	b_ctrl_status=0;
uchar f_out_out =0;
uchar xdata	b_wendu_ok=0;	//�ﵽĿ���¶ȵĴ���
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


uchar	xdata	b_grade=0;	//��λ
uchar	xdata	b_set_wendu=0;	//�趨���¶�

uchar xdata b_yuyue_run_cnt =0;	//ԤԼ����ʱ����ʱ������



/*ů�˻�����*/
bit		f_sys_power_1=0;  //���(A) 0:��,1:��
bit		f_sys_power_2=0;  //�ұ�(B) 0:��,1:��
//
bit     f_sys_on_1=0;     //���(A) 0:����,1:����
bit     f_sys_on_2=0;     //���(A) 0:����,1:����



uchar	tab_huo_guo_9[] = {5,10,15,20,25,30,35,40,45};
uchar	tab_huo_guo_5[] = {25,30,35,40,45};



#if	double_ad_channel
uchar	xdata	b_temp_1_ref_sec=0;
uchar	xdata	b_temp_1_ref=0;
#endif



bit	f_power_power=0;

//��״̬
bit	f_mjs_set=0;
bit	f_mjs_dingshi=0;
bit	f_mjs_yuyue=0;
bit	f_mjs_power=0;
bit	f_mjs_down=0;
bit	f_dingshi_begin=0;


bit	f_NO_jiangdang=0;	//������־λ 0:�ɽ��� 1:���ɽ���


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
uchar	xdata	b_high_level=0; //��ɿع�,�ߵ�ƽʱ��1

uchar	xdata	gb_kkg=0;
uchar	xdata	b_kkg_buf=0;
bit		f_delay_kkg=0;
bit		f_high_time=0;  //��ɿع� 0:�ر�,1:���
#endif


void	work_deal();	//��������

void	next_step();	//��һ����
void	shutdown_power();
void	gaoyuan_heat(uchar b_para);
void	heat_hdle(uchar	b_parameter);	//����Լ���
void	intermittent(uint b_on,uint b_all);	//����Լ���

void	baowen_hdle(uchar b_temp1,uchar b_temp2,uchar b_para);	//��ָ���¶���,��ռ�ձȼ���
void	three_heat(uchar b_wdvalue,uchar heat1,uchar tmp1,uchar heat2,uchar tmp2,uchar heat3,uchar tmp3,uchar heat4);
void	action_work();
void	quit_work();



#if 1	//��������
void	zhu_mode_0();	//����1
void	zhu_mode_1();	//����1

void	zhu_mode_4();	//����4


void	zhu_mode_chao();	//����,��� ����1,6
void	zhu_mode_dunzhu();	//����		����2
void	zhu_mode_qingzheng();//����		����3
void	zhu_mode_mandun();	//����		����4
void	zhu_mode_niupai();	//ţ��      ����5
void	zhu_mode_bb();	//����
void	zhu_mode_chao_SP()	;


void	baowen_mode_hdle();	//��������
void	zhufan_hdle_ONE();	//������





#endif


//	��������
#if 0	//���� ˫̽ͷ����
/*˫̽ͷ����*/
void	tang_hdle_TWO();	//��������
void	zhuzhou_hdle_TWO();	//��������
void	tangshui_hdle_TWO();//��ˮ����
void	zhufan_hdle_TWO();	//������
void	zheng_hdle_TWO();	//������
#endif

#if 0	//���� ��̽ͷ����
/*��̽ͷ����*/
void	tang_hdle_ONE();	//��������
void	zheng_hdle_ONE();	//������
void	zhuzhou_hdle_ONE();	//������
void	zhufan_hdle_ONE();	//������
void	dangao_hdle_ONE();	//��������
void	suannai_hdle_ONE(); //��������
void	dun_hdle_ONE();		//������
void	refan_hdle_ONE();	//�ȷ�����
#endif



/*-----------------------------------------------------------------
�������ƣ� void	work_deal(void)
�������ܣ� ��������
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	work_deal()
{
    //uint b_share_cnt1,b_share_cnt2;
    uchar   b_jdq_buf_1=0;    //�ɿع����������
    f_jdq=0;	//�̵��� ��
	b_kkg_buf=0;	//�ɿع��

	/*���ڱ���,��*/
	if(b_mode!=1)
		b_wendu_ok=0;	//�ﵽĿ���¶ȵĴ���




	/*����״̬��,��ģʽ*/
    if(!(f_mjs_set||f_mjs_yuyue||f_mjs_dingshi||f_mjs_power))
    {
		b_mode=0;

	}    
		
	/*��������״̬,���ܵ���ʱ��־λ*/
    if(!f_mjs_power)
        f_dingshi_begin=0;
	/*������״̬,��ԤԼ��*/
	/*����ԤԼ״̬,��ԤԼ��*/
    if(f_mjs_set||(!f_mjs_yuyue))
        b_yuyue_sec=0;
	/*������״̬,�嶨ʱ��*/
	/*���ڶ�ʱ״̬,�嶨ʱ��*/
	/*��ԤԼ״̬,�嶨ʱ��*/
	/*����ʱ��־λû��,�嶨ʱ��*/
    if(f_mjs_set||(!f_mjs_dingshi)||f_mjs_yuyue||(!f_dingshi_begin))
        b_dingshi_sec=0;
	/*���ڱ���ģʽ,�屣��ʱ��*/
    if(b_mode!=0x80)
    {
        b_baowen_sec=0;
        b_baowen_min=0;
        b_baowen_hour=0;
    }



    if(!b_warning)
    {
		/*����״̬*/
        if(f_mjs_set)
        {
            if(b_mjs_set_sec>=5)
           {
              	if(b_mode)
				{
					action_work();	//��ʼ����
					b_time_grade_cnt=0;//;0:��λ,5:ʱ��
				}
                else
                    shutdown_power();//�ر����й���
                //quit_work();
            }
        }


		/*ԤԼ״̬*/
        if(f_mjs_yuyue)
        {
            if(!f_mjs_set)
            {
			#if	c_yyyc	//Ϊ1��ԤԼʱ��Ϊ���ʱ��
                b_share_cnt1=b_odon_hour*60+b_odon_min;
                b_share_cnt2=b_odoff_hour*60+b_odoff_min;
                if(b_share_cnt2>=b_share_cnt1)
			#else
				/*ԤԼʱ������,���ʾԤԼ���*/
                if(b_yuyue_hour==0 && b_yuyue_min==0)
			#endif
                {
                    f_mjs_yuyue=0;
					f_mjs_dingshi=1;
					f_mjs_power=1;

					f_disp_yuyue=0;
                    
                    next_step();	//��һ����
                    b_ctrl_status=0;
                    open_buz(1);	//������ʼ��	
                }
            }
		}

        //	����ʱ��
        if(f_mjs_dingshi&&f_dingshi_begin)
        {
            if(!f_mjs_set)
            {
                if((b_dingshi_hour==0) && (b_dingshi_min==0) &&(b_mode!=0x80))
                {

                    quit_work();
                    //if(b_mode!=4)
                    open_buz(3);	//���������
					
                    if(b_mode==2 || b_mode==3 ||b_mode==4||b_mode==5)	//����1,3,4��ת��������,������ʱ��Ҫ�޸Ĵ˴�
                    {
                        f_mjs_power=1;
						f_mjs_dingshi=1;
						f_dingshi_begin=1;
                        //b_mode=0xff;
						b_mode=0x80;	//����ģʽ
						/*����Ĭ���¶�*/
						b_set_wendu=60;	//60��
	
						/*��ʼ��ʱ��*/
						b_dingshi_hour=24;
						b_dingshi_min=0;
						b_dingshi_sec=0;			




						////��ʼ������ʱ��
						//b_baowen_hour=0;
						//b_baowen_min=0;
						//b_baowen_sec=0;

						 
                        next_step();	//��һ����
                        b_ctrl_status=0;
                    }
                }

            }
        }


        //	��������
        if(f_mjs_power)
        {
            switch(b_mode)
            {
            	case 1://����
            	    zhu_mode_chao_SP();	//����,��� OK
            	    break;
           		case 2://����
					zhu_mode_dunzhu();	//����	OK
                	break;
            	case 3://����
                	//zhufan_hdle_ONE();//������
					zhu_mode_qingzheng();	//���� OK
                	break;
            	case 4://����
            	    zhu_mode_mandun();
            	    break;
            	case 5:
					//ţ��
            	    zhu_mode_niupai();
            	    break;
            	case 6://���
            	    zhu_mode_chao();	//OK
            	    break;

            	case 0x80://����
            	{
					zhu_mode_bb();	//����ģʽ
				  	break;
            	}
            default:
                shutdown_power();
                break;
            }
        }		


		/*���±���*/
        if(gb_wendu>=220)
		{
			f_jdq=0;
			b_kkg_buf=0;
		}




	}


#if   kkg_en
    ///*��ɿع�*/
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
�������ƣ� void	three_heat(void)
�������ܣ� ���μ���	 ����ԭ��
��������� b_wdvalue   heat1  tmp1  heat2  tmp2  heat3 tmp3  heat4
�� �� ֵ�� ��
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
�������ƣ� void	gaoyuan_heat(void)
�������ܣ� ��ԭ����
��������� b_para �����¶�
�� �� ֵ�� ��
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
�������ƣ� void	baowen_hdle(void)
�������ܣ� ��ָ���¶���,��ռ�ձȼ���
��������� b_temp1 ����		b_temp2 ����	  b_para ռ�ձ�
�� �� ֵ�� ��
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
�������ƣ� void	heat_hdle(void)
�������ܣ� ����Լ���	   ����Ϊ40��
��������� ����ʱ��
�� �� ֵ�� ��
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
�������ƣ� void	intermittent(uchar b_all,uchar b_on)
�������ܣ� ����Լ���	   ����Ϊ40��
��������� ����ʱ��
�� �� ֵ�� ��
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
�������ƣ� void	shutdown_power(void)
�������ܣ� �ر����й���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	shutdown_power()
{
    //open_buz(1);
	open_buz(3);	//�����
    quit_work();
}


/*-----------------------------------------------------------------
�������ƣ� void	next_step(void)
�������ܣ� ��һ����
��������� ��
�� �� ֵ�� ��
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
�������ƣ� void	quit_work(void)
�������ܣ� �˳�����
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	quit_work()
{	
	/*��ʾ*/
    f_disp_yuyue=0;
    f_disp_dingshi=0;

	/*��״̬*/
    f_mjs_dingshi=0;
    f_mjs_yuyue=0;
    f_mjs_set=0;
    f_mjs_power=0;
    f_mjs_down=0;

	f_dingshi_begin=0;

    f_jdq=0;
}

/*-----------------------------------------------------------------
�������ƣ� void	action_work(void)
�������ܣ� ��ʼ����
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	action_work()
{
    //open_buz(4);	//������ʼ��
    f_mjs_set=0;	//�ر�����״̬

	b_wendu_ok=1;
    //b_led_slide1=5;
    //f_disp_yuyue=0;
    //f_disp_dingshi=0;

	/*��ԤԼ״̬��,����*/
    if(!f_mjs_yuyue)
    {
        next_step();
        f_mjs_power=1;
        b_ctrl_status=0;
    }
}



#if out_en
/*-----------------------------------------------------------------
�������ƣ� void	relay_deal(void)
�������ܣ� �̵����������,100ms��׼
��������� ��
�� �� ֵ�� ��
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
        
        /*��ɿع�*/
        if(b_kkg_count<gb_kkg)
            f_high_time=1;
        else
            f_high_time=0;
        b_high_level=0;     //�ߵ�ƽʱ��1
        

        b_kkg_count++;
        if(b_kkg_count>=100)   //96  //��EMC��ѹ��˸�Ӵ�˶������ڣ���ͨ������Ӧ�Ӵ�
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

    if(b_out_ctrl>=24000)    //2s�޹�����Ͽ��������
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
        
        /*��ɿع�*/
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




#if 1 //��������

void	zhu_mode_0()	//����,һֱȫ���ʼ���,ֱ�ӽ���
{
	f_dingshi_begin=1;
	f_jdq=1;

}



void	zhu_mode_1()	
{
	
    uchar temp=0;
	f_dingshi_begin=1;
	/*��ʱ*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }



	/*15���Ӻ󽵹���*/
	if((b_ctrl_cnt >= 15))	
	{
		temp=13;
		intermittent((uint)temp,45);	//��Ъ�Լ���
	}   
	else
	{
		//һ��ʼȫ����
		temp=45;
		intermittent((uint)temp,45);	//��Ъ�Լ���
	}

}	


void	zhu_mode_chao()	//�峴,һֱ��,ָ���ֶ��ر�
{
	uchar	temp=0;

	//f_dingshi_begin=1;
	/*��ʱ*/
    if(b_ctrl_sec_1>=200)
    {
        b_ctrl_sec_1=200;
    }

	/*����ģʽ,û��6��P3.����ֱ�ӿ��Ե�����*/
	if(b_mode==1)
	{
		b_ctrl_sec_1=200;
	}


	/*ǰ118s,��10ͣ8*/
	/*���水�յ�λ��*/
	if(b_ctrl_sec_1<112)
	{
		intermittent(10,18);	//��Ъ�Լ���
	}
	else
	{
		//��Ъ�Լ���
		temp=tab_huo_guo_5[b_grade-1];
		intermittent((uint)temp,18);	//��Ъ�Լ���
	}

}

//�峴,�е�����
void	zhu_mode_chao_SP()	
{
	//static uchar b_wendu_ok=0;	//�ﵽĿ���¶ȵĴ���
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

			//��Ъ�Լ���
			temp=tab_huo_guo_5[b_grade-1];
			intermittent(temp,45);	//��Ъ�Լ���
			
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

		/*������һ����*/
		if(b_ctrl_cnt>=b_i)
		{
			b_wendu_ok=2;
		}

		/*ǰ5��ǰ����150���,ֱ������һ����*/
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
			b_ctrl_sec_2=10;	//��һ�����ȹ�
			b_wendu_ok=3;
		}
		else if(gb_wendu < b_set_wendu-10)	//20
		{
			b_kkg_buf=0;
			intermittent(10,22);	//��Ъ�Լ���
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





/*����*/
void	zhu_mode_dunzhu()	
{
	f_dingshi_begin=1;

	//f_dingshi_begin=1;
	/*��ʱ*/
    if(b_ctrl_sec_1>=200)
    {
        b_ctrl_sec_1=200;
    }


	/*ǰ118s,��10ͣ8*/
	/*���濪7ͣ11*/
	if(b_ctrl_sec_1<112)
	{
		intermittent(10,18);	//��Ъ�Լ���
	}
	else
	{
		intermittent(7,18);	//��Ъ�Լ���
	}
}





/*����*/
void	zhu_mode_qingzheng()
{
    uint temp=0;
	f_dingshi_begin=1;
	/*��ʱ*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	temp=b_ctrl_cnt*60+b_ctrl_sec_1;

	/*ǰ112s,��10ͣ8*/
	/*��ȫ����3��10s*/
	/*֮��7ͣ11*/
	if(temp<112)
	{
		intermittent(10,18);	//��Ъ�Լ���
	}
	else if(temp<302)
	{
		intermittent(18,18);	//��Ъ�Լ���
	}
	else
	{
		intermittent(7,18);	//��Ъ�Լ���
	}
}

/*����,*/
void	zhu_mode_mandun()	
{
	
    uint temp=0;
	f_dingshi_begin=1;
	/*��ʱ*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	temp=b_ctrl_cnt*60+b_ctrl_sec_1;

	/*ǰ112s,��10ͣ8*/
	/*112-295,ȫ��*/
	/*��4ͣ14*/
	if(temp<112)
	{
		intermittent(10,18);	//��Ъ�Լ���
	}
	else if(temp<295)
	{
		intermittent(18,18);	//��Ъ�Լ���
	}
	else
	{
		intermittent(4,18);	//��Ъ�Լ���
	}

}	


/*ţ��*/
void	zhu_mode_niupai()	
{
	
    uint temp=0;
	f_dingshi_begin=1;
	/*��ʱ*/
    if(b_ctrl_sec_1>=60)
    {
        b_ctrl_sec_1=0;
		if(b_ctrl_cnt<255)
        	b_ctrl_cnt++;
    }

	temp=b_ctrl_cnt*60+b_ctrl_sec_1;

	/*ǰ112s,��10ͣ8*/
	/*���濪6ͣ6*/
	if(temp<112)
	{
		intermittent(10,18);	//��Ъ�Լ���
	}
	else
	{
		intermittent(6,12);	//��Ъ�Լ���
	}

}	






/*�Զ�����*/
void	zhu_mode_bb()
{
	bit f_out_temp=0;	//1:��� 0:�����

	f_dingshi_begin=1;
	//intermittent(2,18);	//��Ъ�Լ���
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
		//static uchar b_wendu_ok=0;	//�ﵽĿ���¶ȵĴ���
		
		
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
				b_ctrl_sec_2=10;	//��һ�����ȹ�
				b_wendu_ok=3;
			}
			else if(gb_wendu < b_set_wendu-10)	//20
			{
				b_kkg_buf=0;
				intermittent(10,22);	//��Ъ�Լ���
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






/*�������̴���*/
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




	
//	/*��ʱ*/
//    if(b_ctrl_sec_1>=60)
//    {
//        b_ctrl_sec_1=0;
//		if(b_ctrl_cnt<255)
//        	b_ctrl_cnt++;
//    }
//
//	/*0-5����,��14s��31s*/
//	/*5-10����,��*/
//	/*10���Ӻ�,���տ�150s��570sһֱѭ��*/
//
//	if(b_ctrl_cnt<5)
//	{
//		intermittent(14,45);	//��Ъ�Լ���
//
//	}
//	else if (b_ctrl_cnt>=5 && b_ctrl_cnt<10)
//	{
//		f_jdq=0;
//		b_ctrl_sec_2=0;
//	}
//	/*�����ְ���,ͣ9�ְ����*/
//	/*��150s ��570s*/
//	else if(b_ctrl_cnt>=10)
//	{
//		intermittent(150,720);	//��Ъ�Լ���
//	}	
	
	/*Ĭ�ϱ���ʱ��2h*/
	if(b_baowen_hour>=6)
    {
        shutdown_power();
        open_buz(5);	//���������
    }
}


void	zhufan_hdle_ONE()
{
    f_dingshi_begin = 1;
    switch(b_ctrl_status)
    {
    case 0:
		/*��ʱ*/
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
		/*��ʱ*/
        if(b_ctrl_sec_3>=60)
        {
            b_ctrl_sec_3=0;
            b_ctrl_cnt2++;
        }

		/*ת��һ���̵�����*/
		/*1.����50min��,ת��һ����*/
		/*2.��������120��,60s������һ����*/
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












#if 0 //��̽ͷ����


//---------------------����----------------------
void	suannai_hdle_ONE()
{
    f_dingshi_begin = 1;
    three_heat(gb_wendu,0x14,30,0x0a,35,0x05,40,0x00);
}


//---------------------��̽ͷ����----------------------
void	dun_hdle_ONE()
{
    f_dingshi_begin = 1;
    three_heat(gb_wendu,0xff,85,0x1e,90,0x0f,95,0x05);
}


//---------------------��,��ˮ��----------------------
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

//---------------------��̽ͷ����----------------------
void	tang_hdle_ONE()
{
    f_dingshi_begin = 1;
    three_heat(gb_wendu,0xff,85,0x1e,90,0x14,95,0x0a);
}

//---------------------��̽ͷ����/ϡ��----------------------
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
            b_tmp = 93;	//�趨�¶�

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



//---------------------��̽ͷ��----------------------
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



//---------------------����----------------------
void	dangao_hdle_ONE()
{
    f_dingshi_begin=1;
    if(gb_wendu >= 80)
        baowen_hdle(129,130,0x0f);
    else
        heat_hdle(0xff);
}


//---------------------�ȷ�----------------------
void	refan_hdle_ONE()
{
    f_dingshi_begin=1;
    if(gb_wendu >= 80)
        baowen_hdle(105,110,0x14);
    else
        heat_hdle(0xff);
}


#endif










#if 0	//��Ҫ˫̽ͷ������

//---------------------˫̽ͷ��----------------------
void	zheng_hdle_TWO()
{
    f_dingshi_begin=1;
    three_heat(gb_wendu2,0xff,60,0x14,95,0x0f,98,0x0a);
}



//---------------------˫̽ͷ����----------------------
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


//---------------------˫̽ͷ����----------------------
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

//---------------------˫̽ͷ��ˮ----------------------
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

//---------------------˫̽ͷ��----------------------
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


