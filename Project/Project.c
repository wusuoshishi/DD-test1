#include 	"..\Application_Library\Global.h"








uchar	xdata   b_NOW_or_Target_cnt=0;//0:Ŀ���¶�,5:�����¶�
uchar	xdata   b_NOW_or_Target_cnt2=0;//0:Ŀ���¶�,5:�����¶�
//bit f_test_abc=0; //������


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
//��������void Project(void)
//��  �ܣ���Ŀ��Ŀ���ܺ���
//��  ������
//����ֵ����
/****************************************************************/
void Project(void)
{
   	if(gb_20ms>=20)
	{
        gb_20ms-=20;   //20ms��׼
  
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

          //==hore_check(); //��ť�Լ�
  
		#if   ad_en
          	lab_ad_fun();//OK
		#endif
          	//codingSwitch_deal1(); //���뿪��1����
          	//codingSwitch_deal2(); //���뿪��2����
          	time_deal();
          	display_deal();
          
		#if	(c_TM1628_EN || c_TM1629_EN)	
          	TM1628_sendData();
		#endif	


    }
	
}


/*-----------------------------------------------------------------
�������ƣ� void	time_deal(void)
�������ܣ� ʱ�䴦�������������е�ʱ�����
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/

void	time_deal()
{
  
	/*��˸��ʱ*/
    if(++gb_flashTime>=25)
    {
        gb_flashTime=0;
        gf_flash = !gf_flash;
    }


	if(b_force_flash_cnt<250)
		b_force_flash_cnt++;	//ǿ����˸����


	if(b_clock_key<250)	//���й�����,�ް�������,1s������
		b_clock_key++;
	if(f_mjs_set || !b_mode)
	{
		b_clock_key=0;
		f_clock_key=0;
	}
		
	if(b_clock_key>=60)	//����ʱ��
		f_clock_key=1;
	
	if(f_clock_key==1)
	{
		if(f_mjs_yuyue)
		{
			f_disp_yuyue=1;
		}

		/*����ģʽ������ʱ��,ʱ��Ϊ��,�Զ��˳�*/
		if(b_mode==0x80 && f_mjs_power)
		{
			if((b_dingshi_hour==0) && (b_dingshi_min==0) )
			{
				quit_work();	
				/*���⴦��*/
				/*����200˵���Ѿ��ǵ���ʱ�����ػ���,�������ֶ��ػ���*/
				if(b_clock_key>=200)
				{
					open_buz(3);	//���������
				}
			}	




		}
	}


	///*���Լ�ʱ*/
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

	/*�̵���������ʱ*/
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
    	    relay_deal();   //�̵�������
		#endif

    }

	
	/*1sִ��һ��*/
    gb_1s++;
    if(gb_1s>=50)
    {
        gb_1s=0;        //1s��׼




        b_led_slide1 ++;			 //��ʾ��ˮ��ʱ
        if(b_led_slide1 >= 10)
            b_led_slide1 = 0;

		/*���ü���*/
        if(b_mjs_set_sec<0xff)
            b_mjs_set_sec++; 			//�������̼�ʱ

		/*�������̼���*/	
        if(b_ctrl_sec_3<0xff)
            b_ctrl_sec_3++;
        if(b_ctrl_sec_2<800)
            b_ctrl_sec_2++;
        if(b_ctrl_sec_1<0xff)
            b_ctrl_sec_1++;
        
        //Ŀ���¶�,�����¶�ת��ʱ���ۼ�
        b_NOW_or_Target_cnt++;
        if(b_NOW_or_Target_cnt>=c_NOW_or_Target_cnt_MAX)
          b_NOW_or_Target_cnt=0;


		/*������ؼ�ʱ*/
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


		/*���¼�ʱ*/
		if((b_mode&0x80) && (f_mjs_power))
        b_baowen_sec++;							 //����ʱ��
        if(b_baowen_sec>=60)    //��ʱ60 2
        {
            b_baowen_sec=0;
            b_baowen_min++;
            if(b_baowen_min>=60)	//��ʱ60 2
            {
                b_baowen_min=0;
                b_baowen_hour++;
            }
        }

		// /*ԤԼ��ʱ*/
         b_yuyue_sec++;							 //ԤԼʱ��
         if(b_yuyue_sec>=60)  //��ʱ60
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

		///*ԤԼ��ʱ*/
        //b_yuyue_sec++;							 //ԤԼʱ��
        //if(b_yuyue_sec>=60)  //��ʱ60 2
        //{
        //    b_yuyue_sec=0;
		//	b_yuyue_min++;
		//	if (b_yuyue_min>=60)	//��ʱ60 2
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
		/*��ʱ��ʱ*/
		if(f_mjs_power)
        	b_dingshi_sec++;							   //��ʱʱ��
        if(b_dingshi_sec>=60)   //��ʱ60 2
        {
            b_dingshi_sec=0;
            if(b_dingshi_min||b_dingshi_hour)
            {
                if(b_dingshi_min)
                    b_dingshi_min--;
                else
                {
                    b_dingshi_min=59;	//��ʱ59
                    b_dingshi_hour--;
                }
            }
        }
	}
	
	else
	{
		/*��ʱ��ʱ*/
		
        b_dingshi_sec++;							   //��ʱʱ��
        if(!f_mjs_power)
			b_dingshi_sec=0;	
		if(b_dingshi_sec>=1)   //��ʱ60 2
        {
            b_dingshi_sec=0;
            if(b_dingshi_min||b_dingshi_hour)
            {
                if(b_dingshi_min)
                    b_dingshi_min--;
                else
                {
                    b_dingshi_min=59;	//��ʱ59
                    b_dingshi_hour--;
                }
            }
        }
	}


		/**/
//		b_time_grade_cnt++;	//0:��λ,5:ʱ��
//		if(b_time_grade_cnt>=10)
//		{
//			/*��ʱ��˸���,�綨ʱʱ��Ϊ0,��رն�ʱģʽ*/
//			if(f_disp_dingshi)
//			{
//				open_buz(4);	//������ʼ��
//				f_dingshi_begin=1;//��ʼ��ʱ
//				/*������ʱ,ʱ��Ϊ0,��ȡ����ʱ*/
//				if(!b_dingshi_min)
//				{
//					f_mjs_dingshi=0;	//�˳���ʱ״̬
//					f_dingshi_begin=0;//�رյ���ʱ
//				}
//			}
//
//			b_time_grade_cnt=0;	//0:��λ,5:ʱ��
//			f_disp_dingshi=0;	//�ض�ʱ��ʾ
//			
//		}

//		//ԤԼ����ʱ������ʱ
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




