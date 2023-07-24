#include 	"..\Application_Library\Global.h"
//#include    <intrins.h>

//����ʱ��ʾ
uchar	xdata	b_disp_test=0;
uchar	xdata	b_disp_test2=0;

uchar	data	b_dis_r18=0;
uchar	data	b_dis_r28=0;
uchar	data	b_dis_r38=0;
uchar	data	b_dis_r48=0;
uchar	data	b_dis_r58=0;
uchar	data	b_dis_r68=0;
uchar	data	b_dis_r78=0;
uchar	data	b_dis_r88=0;

uchar	xdata	b_r18=0;
uchar	xdata	b_r28=0;
uchar	xdata	b_r38=0;
uchar	xdata	b_r48=0;
uchar	xdata	b_r58=0;
uchar	xdata	b_r68=0;
uchar	xdata	b_r78=0;
uchar	xdata	b_r88=0;

bit		f_fanzhuan=0;

bit		f_disp_yuyue=0;	 	//��ʾԤԼʱ��
bit		f_disp_dingshi=0;		//��ʾ����ʱ��
bit		gf_flash=0;			//��˸��500ms
bit		f_dp=0;				//��ʾ������м�ð��
bit     f_dp_2=0;           //��ʾ������м�ð��
bit		f_dgtn=0;		   //ת��ѡ��λ��Ϊ1�򲻲�tab_num��
uchar	xdata	gb_flashTime=0;

uchar	xdata	b_led_slide1=0;

uchar	data	b_disp_status=0;
uchar	data	b_disp_rl=0;

uchar	b_time_grade_cnt=0;//		0:��λ,5:ʱ��

uchar	const code	tab_num[]=
{
    c_num0_n,	//0
    c_num1_n,	//1
    c_num2_n,	//2
    c_num3_n,	//3
    c_num4_n,	//4
    c_num5_n,	//5
    c_num6_n,	//6
    c_num7_n,	//7
    c_num8_n,	//8
    c_num9_n,	//9
    c_numA_n,	//A 10
    c_numb_n,	//B 11
    c_numC_n,	//C 12
    c_numd_n,	//D 13
    c_numE_n,	//E 14
    c_numF_n,	//F 15
    c_num10_n, //10 16
    c_nump_n,	//11 17
    c_numc_n,  //18 18
    c_numc_ding_n, // 19
    c_numH_n      //20
};


#if   c_disp_liushui
void	liushui_liucheng1(void);
#endif

#if   c_disp_change
uchar	change(uchar);	//����ӳ��
#endif


/*�������ʾ���*/
void  	smg_deal();	//����ܴ���
void	smg_deal_dingshi_1();	//����ܶ�ʱ��ʾ1
void	smg_deal_dingshi_2();	//����ܶ�ʱ��ʾ2	
void	smg_deal_yuyue_1();		//�����ԤԼ��ʾ1

/*LED����ʾ���*/
void  	led_deal();	//LED�ƴ���
void	led_deal_mode_one();//��Ӧ�����µ�LED����ʾ
void	led_deal_ALL_OFF();	//LED��ȫ��
void	led_deal_ALL_ON();	//LED��ȫ��



void  	dispdata_clr();

void 	dispdata_mov();

void  	dispdata_set();




/*-----------------------------------------------------------------
�������ƣ� void	display_deal(void)
�������ܣ� ��ʾ����,ʱ���׼10ms
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	display_deal()
{
    dispdata_clr();		//��ʾ��0
    
    if(!gf_check)
      dispdata_set();   //�Լ���ʾȫ��
    else
    {

        //��ʾ����
        smg_deal();   //�������ʾ����
        led_deal();   //LED����ʾ����





        #if 0		 	//��ʾ����ֵ��������Ҫ����ʾ���������˱���
        {
            if(gf_flash)
            {
                f_led1_h; 
                f_led2_h;
            }
			else
			{
                f_led3_h;
				f_led4_h;
			}

            //b_r18=b_disp_test/16;
            //b_r28=b_disp_test%16;
            //b_r38=b_disp_test2/16;
            //b_r48=b_disp_test2%16;
            
            #if 0 //��ʾ�¶�
                if(gb_wendu>99)
                {
                    b_r18=gb_wendu/100;
                    b_r28=gb_wendu/10%10;
                    b_r38=gb_wendu%10;
                }
                else
                {
                    b_r18=gb_wendu/10;
                    b_r28=gb_wendu%10;
                    b_r38=25;   //��ʾ����c   
                }

            #endif    

            #if 0    //��ʾ�¶�AD
                b_r18=b_temp/100;
                b_r28=b_temp/10%10;
                b_r38=b_temp%10;

                b_r48=b_temp_1/100;
                b_r58=b_temp_1/10%10;
                b_r68=b_temp_1%10;
            #endif


            #if 0   //��ת������ʾ
            b_r18=b_key_value;
            b_r28=codingSwitch_get();   //��ʾ����ֵ
            b_r38=codingSwitch_get2();   //H

            b_r18=Target_wendu_1/10;
            b_r28=Target_wendu_1%10;
            b_r38=25;   //��ʾ����c 

            b_r48=Target_wendu_2/10;
            b_r58=Target_wendu_2%10;
            b_r68=25;   //��ʾ����c 

            #endif

			#if 1 //��ʾ��������ֵֵ

				    b_r18=b_mode;
					b_r28= b_key_value;

					


			#endif


        }
		#endif

        if(!f_dgtn)	//ת��ѡ��λ��Ϊ1�򲻲�tab_num��
        {
            //b_r18=tab_num[b_r18];
            //b_r28=tab_num[b_r28];
            //b_r38=tab_num[b_r38];
            //b_r48=tab_num[b_r48];

			/*����ܷ��ſ�*/
            b_r18=tab_num[b_r18];
            b_r28=tab_num[b_r28];
            b_r38=tab_num[b_r38];
            b_r48=tab_num[b_r48];


            //b_r58=tab_num[b_r58];
            //b_r68=tab_num[b_r68];       
			//b_r78=tab_num[b_r78];   
			//b_r88=tab_num[b_r88]; 
        }
		    if(f_dp)
           		b_r38|=0x80;	//�����ڸ���
		
        	//if(f_dp)
            //b_r28|=0x80;
            //if(f_dp_2)
                //b_r58|=0x80;

    }

    dispdata_mov();
}

void  dispdata_set()
{
#if	(c_TM1628_EN|| c_TM1629_EN)
    uchar i,j;
#if c_TM1629_EN
    j=16;
#endif
#if c_TM1628_EN
    j=14;
#endif
    for(i=0; i<j; i++)
       gb_disIcData[i]=0xff;
#endif
    b_r18=0xff;
    b_r28=0xff;
    b_r38=0xff;
    b_r48=0xff;
    b_r58=0xff;
    b_r68=0xff;
    b_r78=0xff;
    b_r88=0xff;
}


/*��ʾ��0*/
void  dispdata_clr()
{
#if	(c_TM1628_EN|| c_TM1629_EN)
    uchar i,j;
#if c_TM1629_EN
    j=16;
#endif
#if c_TM1628_EN
    j=14;
#endif
    for(i=0; i<j; i++)
       gb_disIcData[i]=0;
#endif
    b_r18=0;
    b_r28=0;
    b_r38=0;
    b_r48=0;
    b_r58=0;
    b_r68=0;
    b_r78=0;
    b_r88=0;
    f_dgtn=0;
    f_dp=0;
    f_dp_2=0;
}

void  dispdata_mov()
{
	/*���ڷ�ת�������*/
    b_dis_r18=b_r48;
    b_dis_r28=b_r38;
    b_dis_r38=b_r28;
    b_dis_r48=b_r18;

    b_dis_r58=b_r58;
    b_dis_r68=b_r68;
    b_dis_r78=b_r78;
    b_dis_r88=b_r88;
    
#if	(c_TM1628_EN|| c_TM1629_EN)
    if(gf_check)
    {
      gb_disIcData[9]=change(b_r48);
      gb_disIcData[1]=change(b_r38);
      gb_disIcData[3]=change(b_r28);
      gb_disIcData[5]=change(b_r18);
      if(f_dp)
        gb_disIcData[9]|=c_bit0;
      
      if(b_r58&0x01)
          gb_disIcData[6]|=c_bit0;
      if(b_r58&0x02)
          gb_disIcData[6]|=c_bit1;
      if(b_r58&0x04)
          gb_disIcData[6]|=c_bit2;
      if(b_r58&0x08)
          gb_disIcData[6]|=c_bit6;
      if(b_r58&0x10)
          gb_disIcData[6]|=c_bit7;
      if(b_r58&0x20)
          gb_disIcData[7]|=c_bit0;
      if(b_r58&0x40)
          gb_disIcData[7]|=c_bit1;
      if(b_r58&0x80)
          gb_disIcData[6]|=c_bit3;
    }    
#endif
}

/*LED����ʾ����*/
void  led_deal()
{	
	/*������LED����ʾ*/
	if(b_warning)
	{
		/*LED����˸*/
		if(gf_flash)
			led_deal_ALL_ON();//LED��ȫ��
	}
	else
	{	
		/*����ģʽ�µ�LED��ʾ*/
		if(f_mjs_set)
		{
			/*LED����˸*/
			if(gf_flash || b_mjs_set_sec<1)
				led_deal_mode_one();	//��Ӧ�����µ�LED����ʾ
		}
		/*���������µ�LED��ʾ*/
		else
		{
			if(b_force_flash_cnt<50)
			{
				if(gf_flash)
					led_deal_mode_one();	//��Ӧ�����µ�LED����ʾ
				else
				{
					b_r58=0;
				}
			}
			else
			{
				led_deal_mode_one();	//��Ӧ�����µ�LED����ʾ
			}
			
		}
		
	}
}


/*��Ӧ�����µ�LED����ʾ*/
void	led_deal_mode_one()
{
	/*����LED��ʾ*/
	switch(b_mode)
    {
    case 1:
        f_led1_h;
        break;
    case 2:
        f_led2_h;
        break;
    case 3:
        f_led3_h;
        break;
    case 4:
	    f_led4_h;
        break;
    case 5:
        f_led5_h;
        break;
    case 6:
	    f_led6_h;
        break;


    default:
        break;
    }
}

/*LED��ȫ��*/
void led_deal_ALL_ON()
{
	f_led1_h;
	f_led2_h;
	f_led3_h;
	f_led4_h;
	f_led5_h;
	f_led6_h;
}

/*LED��ȫ��*/
void led_deal_ALL_OFF()
{
	;
	//f_led1_l;
	//f_led2_l;
	//f_led3_l;
	//f_led4_l;
}


/*�������ʾ����*/
void  smg_deal()
{
	////����ʾ
    b_r18=0x10;
    b_r28=0x10;
    b_r38=0x10;
	b_r48=0x10;
    //b_r58=0x10;
    //b_r68=0x10;
    //b_r78=0x10;
	//b_r88=0x10;
//
	//f_dp=0;
	//f_dgtn=1;	//ת��ѡ��λ��Ϊ1�򲻲�tab_num��
	/***������ʾ***/
  	if(b_warning)
   	{
        //������ʾ
		b_r18=0x10;
        b_r28=0x0e;	//E
		if(b_warning & 0x01)
       		b_r38=1;	//��·
		if(b_warning & 0x02)
       		b_r38=2;	//��·
		if(b_warning & 0x04)
       		b_r38=3;	//����		
		b_r48=0x10;				
   }
   /*����״̬����ʾ*/
   else if(!f_mjs_set && !f_mjs_dingshi && !f_mjs_yuyue && !f_mjs_down && !f_mjs_power)
   {
		//����״̬����ʾ00
		b_r18=0;
        b_r28=0;
        b_r38=0;
		b_r48=0;
		f_dp=1;  //��ʾС����
   }
   else
   {
		/*����״̬����ʾ*/
		if(f_mjs_set)
		{	
			/*����״̬�µ�ԤԼ��ʾ*/
			if(f_disp_yuyue)
			{
				smg_deal_yuyue_1();	//ԤԼ��ʾ
			}
			/*����״̬��,��������״̬*/
			else
			{
				smg_deal_dingshi_1();	//��ʱ��ʾ1
			}

		}
		/*������״̬����ʾ*/
		else
		{
			/*������״̬�µ�ԤԼ��ʾ*/
			if(f_disp_yuyue)
			{
				smg_deal_yuyue_1();	//ԤԼ��ʾ
			}
			else
			{
				if(b_force_flash_cnt<50)
				{
					if(gf_flash)
						smg_deal_dingshi_2();//��ʱ��ʾ2
					else
					{
						b_r18=0x10;
						b_r28=0x10;
						b_r38=0x10;
						b_r48=0x10;
					}
				}
				else
				{
					smg_deal_dingshi_2();//��ʱ��ʾ2
				}
				
				/*���⴦��*/
				if(f_mjs_yuyue && f_clock_key==0&&gf_flash)
					f_dp=1;  //��ʾС����

			}
		}

/*
        if(f_sys_power_1)
        {
            if(b_NOW_or_Target_cnt>=c_IS_disp_NOW) //0:Ŀ���¶�,5:�����¶�
            {
                //��ʾ�����¶�
                b_r18=gb_wendu/10;
                b_r28=gb_wendu%10;
                b_r38=25;   //��ʾ����c
                if(gf_flash)
                    f_dp=1;  
            }
            else
            {
                //��ʾĿ���¶�  
                b_r18=Target_wendu_1/10;
                b_r28=Target_wendu_1%10;
                b_r38=25;   //��ʾ����c
            }
 
        }
        else
        {
            //��ʾ---
            b_r18=0x11;
            b_r28=0x11;
            b_r38=0x11;
        }   */
    }

}


#if   c_disp_change

uchar	change(uchar change_data)
{
    uchar	buffer=0;
    if(change_data & 0x01)
        buffer |= 0x80;
    if(change_data & 0x02)
        buffer |= 0x40;
	  if(change_data & 0x04)
	      buffer |= 0x20;
    if(change_data & 0x08)
        buffer |= 0x10;
    if(change_data & 0x10)
        buffer |= 0x08;
    if(change_data & 0x20)
        buffer |= 0x04;
    if(change_data & 0x40)
        buffer |= 0x02;
	  if(change_data & 0x80)
      	buffer |= 0x01;
    return (buffer);
}

#endif



#if   c_disp_liushui
/*-----------------------------------------------------------------
�������ƣ� void	liushui_liucheng1(void)
�������ܣ� ��ˮ�ƴ���
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/
void	liushui_liucheng1()
{
    uchar	xdata	b_share_cnt1=0;
    uchar	xdata	b_share_cnt2=0;
    uchar	xdata	b_share_cnt3=0;
    b_share_cnt1 = 0x0f;
    b_share_cnt2 = 0x00;
    for(b_share_cnt3 = 0x00; b_share_cnt3 < b_led_slide1; b_share_cnt3 ++)  	//b_led_slide1
    {
        b_share_cnt2 <<= 0x01;
        if(b_share_cnt1 & 0x80)
            b_share_cnt2 |= 0x01;
        b_share_cnt1 <<= 0x01;
        if(b_share_cnt2 & 0x10)
            b_share_cnt1 |= 0x01;
    }
    if(b_share_cnt1 & 0x01)
        b_r18 |= 0x01;
    if(b_share_cnt1 & 0x02)
        b_r28 |= 0x01;
    if(b_share_cnt1 & 0x04)
        b_r38 |= 0x01;
    if(b_share_cnt1 & 0x08)
        b_r48 |= 0x01;
    if(b_share_cnt1 & 0x10)
        b_r48 |= 0x02;
    if(b_share_cnt1 & 0x20)
        b_r48 |= 0x04;
    if(b_share_cnt1 & 0x40)
        b_r48 |= 0x08;
    if(b_share_cnt1 & 0x80)
        b_r38 |= 0x08;
    if(b_share_cnt2 & 0x01)
        b_r28 |= 0x08;
    if(b_share_cnt2 & 0x02)
        b_r18 |= 0x08;
    if(b_share_cnt2 & 0x04)
        b_r18 |= 0x10;
    if(b_share_cnt2 & 0x08)
        b_r18 |= 0x20;
}
#endif


/*-----------------------------------------------------------------
�������ƣ� void led_scan(void)
�������ܣ� LEDɨ��
��������� ��
�� �� ֵ�� ��
-----------------------------------------------------------------*/

void led_scan()
{

#if		c_disp_com

    unsigned char b_disp_tmp=0;

    p_com1in;
    p_com2in;
    p_com3in;
    p_com4in;
    p_com5in;
    p_com6in;
    p_com7in;
    p_com8in;

    p_seg1in;
    p_seg2in;
    p_seg3in;
    p_seg4in;
    p_seg5in;
    p_seg6in;
    p_seg7in;
    p_seg8in;


    b_disp_status++;
    if(b_disp_status>=12)  
    {
      b_disp_status=0;
    }

    if(b_disp_status<=9)
    {
    
    switch(b_disp_status)
    {
    case 0:
        b_disp_tmp=b_dis_r18;
        p_com1l;
        p_com1out;
        p_com1l;
        break;
    case 1:
        b_disp_tmp=b_dis_r28;
        p_com2l;
        p_com2out;
        p_com2l;
        break;
    case 2:
        b_disp_tmp=b_dis_r38;
        p_com3l;
        p_com3out;
        p_com3l;
        break;
    case 3:
        b_disp_tmp=b_dis_r48;
        p_com4l;
        p_com4out;
        p_com4l;
        break;
    case 4:
        b_disp_rl=0x01;
        p_seg1l;
        p_seg1out;
        p_seg1l;
        break;
    case 5:
        b_disp_rl=0x08;
        p_seg4l;
        p_seg4out;
        p_seg4l;
        break;
    case 6:
        b_disp_rl=0x10;
        p_seg5l;
        p_seg5out;
        p_seg5l;
        break;
    case 7:
        b_disp_rl=0x20;
        p_seg6l;
        p_seg6out;
        p_seg6l;
        break;
    default:
        b_disp_tmp=0x00;
        break;
    }
    

    if(b_disp_status==8)
    {
        if(b_dis_r18&c_bit7)
        {
            p_seg8h;
            p_seg8out;
            p_seg8h;
            p_com1l;
            p_com1out;
            p_com1l;
        }
    }
    else if(b_disp_status<=3)
    {
      if(b_disp_tmp&c_bit1)
      {
          p_seg2h;
          p_seg2out;
          p_seg2h;
      }
      if(b_disp_tmp&c_bit2)
      {
          p_seg3h;
          p_seg3out;
          p_seg3h;
      }
      if(b_disp_tmp&c_bit6)
      {
          p_seg7h;
          p_seg7out;
          p_seg7h;
      }
    }
    else
    {
      if(b_dis_r18&b_disp_rl)
      {
          p_com1h;
          p_com1out;
          p_com1h;
      }
      if(b_dis_r28&b_disp_rl)
      {
          p_com2h;
          p_com2out;
          p_com2h;
      }
      if(b_dis_r38&b_disp_rl)
      {
          p_com3h;
          p_com3out;
          p_com3h;
      }
      if(b_dis_r48&b_disp_rl)
      {
          p_com4h;
          p_com4out;
          p_com4h;
      }
    }

    }

    
#endif

//������COM�ڣ�һ��ɨ8��COM��
#if		c_disp_seg

    unsigned char b_disp_tmp=0;

    disp_comh;
    disp_segl;

    b_disp_rl=b_disp_rl<<0x01;

    b_disp_status++;
    if(b_disp_status>=c_ledScan_cnt)
    {
        b_disp_status=0;
        b_disp_rl=0x01;
    }


    switch(b_disp_status)
    {
    case 0:
        //p_seg1h;
        p_seg4h;
        break;
    case 1:
        //p_seg2h;    
        p_seg5h;
        break;
    case 2:
        //p_seg3h;
        p_seg6h;       
        break;
    case 3:
        //p_seg4h;
        p_seg1h;        
        break;
    case 4:
        //p_seg5h;
        p_seg2h;        
        break;
    case 5:
        //p_seg6h;
        p_seg3h;        
        break;
    case 6:
        //p_seg7h;
        p_seg7h;        
        break;
    case 7:
        p_seg8h;
        break;
    default:
        break;
    }

    if(b_dis_r18&b_disp_rl)
        //p_com1l;
        p_com4l;
    if(b_dis_r28&b_disp_rl)
        //p_com2l;
        p_com3l;
    if(b_dis_r38&b_disp_rl)
        //p_com3l;
        p_com2l;
    if(b_dis_r48&b_disp_rl)
        //p_com4l;
        p_com1l;
    if(b_dis_r58&b_disp_rl)
        p_com5l;
    if(b_dis_r68&b_disp_rl)
        p_com6l;
    if(b_dis_r78&b_disp_rl)
        p_com7l;
    if(b_dis_r88&b_disp_rl)
        p_com8l;
#endif


#if	c_disp_comcom

    unsigned char b_disp_buf=0;

    //p_com1in;
    //p_com2in;
    //p_com3in;
    //p_com4in;
    //p_com5in;
    //p_com6in;
    //p_com7in;
    //p_com8in;

    p_segA1in;
    p_segA2in;
    p_segA3in;
    p_segA4in;
    p_segA5in;
    p_segA6in;
    p_segA7in;

    p_segB1in;
    p_segB2in;
    p_segB3in;
    p_segB4in;
    p_segB5in;
    p_segB6in;
    p_segB7in;


    b_disp_status ++;
    if(b_disp_status>=c_ledScan_cnt)
        b_disp_status=0;

    f_fanzhuan = 0;   //f_fanzhuan = 1 com h seg l
    //f_fanzhuan = 0 com l seg h

    b_disp_buf = (b_disp_status >> 0x03) & 0x07;
    if(b_disp_buf>=4)
        f_fanzhuan = 1;
    if(b_disp_status<0x40)
    {

        switch((b_disp_status >> 0x03) & 0x07)
        {
        case 0x00 :
            if(f_fanzhuan)
                p_com1h;
            else
                p_com1l;
            p_com1out;
            if(f_fanzhuan)
                p_com1h;
            else
                p_com1l;
            b_disp_buf = b_dis_r18;
            break;
        case 0x01 :
            if(f_fanzhuan)
                p_com2h;
            else
                p_com2l;
            p_com2out;
            if(f_fanzhuan)
                p_com2h;
            else
                p_com2l;
            b_disp_buf = b_dis_r28;
            break;
        case 0x02 :
            if(f_fanzhuan)
                p_com3h;
            else
                p_com3l;
            p_com3out;
            if(f_fanzhuan)
                p_com3h;
            else
                p_com3l;
            b_disp_buf = b_dis_r38;
            break;
        case 0x03 :
            if(f_fanzhuan)
                p_com4h;
            else
                p_com4l;
            p_com4out;
            if(f_fanzhuan)
                p_com4h;
            else
                p_com4l;
            b_disp_buf = b_dis_r48;
            break;
        case 0x04 :
            if(f_fanzhuan)
                p_com5h;
            else
                p_com5l;
            p_com5out;
            if(f_fanzhuan)
                p_com5h;
            else
                p_com5l;
            b_disp_buf = b_dis_r58;
            break;
        case 0x05 :
            if(f_fanzhuan)
                p_com6h;
            else
                p_com6l;
            p_com6out;
            if(f_fanzhuan)
                p_com6h;
            else
                p_com6l;
            b_disp_buf = b_dis_r68;
            break;
        case 0x06 :
            if(f_fanzhuan)
                p_com7h;
            else
                p_com7l;
            p_com7out;
            if(f_fanzhuan)
                p_com7h;
            else
                p_com7l;
            b_disp_buf = b_dis_r78;
            break;
        case 0x07 :
            if(f_fanzhuan)
                p_com8h;
            else
                p_com8l;
            p_com8out;
            if(f_fanzhuan)
                p_com8h;
            else
                p_com8l;
            b_disp_buf = b_dis_r88;
            break;
        default :
            b_disp_buf = 0x00;
            break;
        }

        switch(b_disp_status & 0x07)
        {
        case 0x00 :
            if(f_fanzhuan)
                p_seg1h;
            else
                p_seg1l;
            p_seg1out;
            if(b_disp_buf & 0x01)
            {
                if(f_fanzhuan)
                    p_seg1l;
                else
                    p_seg1h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg1h;
                else
                    p_seg1l;
            }
            break;
        case 0x01 :
            if(f_fanzhuan)
                p_seg2h;
            else
                p_seg2l;
            p_seg2out;
            if(b_disp_buf & 0x02)
            {
                if(f_fanzhuan)
                    p_seg2l;
                else
                    p_seg2h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg2h;
                else
                    p_seg2l;
            }
            break;
        case 0x02 :
            if(f_fanzhuan)
                p_seg3h;
            else
                p_seg3l;
            p_seg3out;
            if(b_disp_buf & 0x04)
            {
                if(f_fanzhuan)
                    p_seg3l;
                else
                    p_seg3h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg3h;
                else
                    p_seg3l;
            }
            break;
        case 0x03 :
            if(f_fanzhuan)
                p_seg4h;
            else
                p_seg4l;
            p_seg4out;
            if(b_disp_buf & 0x08)
            {
                if(f_fanzhuan)
                    p_seg4l;
                else
                    p_seg4h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg4h;
                else
                    p_seg4l;
            }
            break;
        case 0x04 :
            if(f_fanzhuan)
                p_seg5h;
            else
                p_seg5l;
            p_seg5out;
            if(b_disp_buf & 0x10)
            {
                if(f_fanzhuan)
                    p_seg5l;
                else
                    p_seg5h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg5h;
                else
                    p_seg5l;
            }
            break;
        case 0x05 :
            if(f_fanzhuan)
                p_seg6h;
            else
                p_seg6l;
            p_seg6out;
            if(b_disp_buf & 0x20)
            {
                if(f_fanzhuan)
                    p_seg6l;
                else
                    p_seg6h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg6h;
                else
                    p_seg6l;
            }
            break;
        case 0x06 :
            if(f_fanzhuan)
                p_seg7h;
            else
                p_seg7l;
            p_seg7out;
            if(b_disp_buf & 0x40)
            {
                if(f_fanzhuan)
                    p_seg7l;
                else
                    p_seg7h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg7h;
                else
                    p_seg7l;
            }
            break;
        case 0x07 :
            if(f_fanzhuan)
                p_seg8h;
            else
                p_seg8l;
            p_seg8out;
            if(b_disp_buf & 0x80)
            {
                if(f_fanzhuan)
                    p_seg8l;
                else
                    p_seg8h;
            }
            else
            {
                if(f_fanzhuan)
                    p_seg8h;
                else
                    p_seg8l;
            }
            break;
        default :
            break;
        }
    }


#endif

#if	c_disp_comseg

    unsigned char b_disp_buf=0;

    p_com1h;
    p_com2h;
    p_com3h;
    p_com4h;
    p_com5h;
    p_com6h;
    p_com7h;
    p_com8h;

    p_seg1l;
    p_seg2l;
    p_seg3l;
    p_seg4l;
    p_seg5l;
    p_seg6l;
    p_seg8l;
    p_seg7l;


    b_disp_status ++;
    if(b_disp_status>=c_ledScan_cnt)
        b_disp_status=0;

    if(b_disp_status < 0x40)
    {
        switch((b_disp_status >> 0x03) & 0x07)
        {
        case 0x00 :
            p_com1l;
            b_disp_buf = b_dis_r18;
            break;
        case 0x01 :
            p_com2l;
            b_disp_buf = b_dis_r28;
            break;
        case 0x02 :
            p_com3l;
            b_disp_buf = b_dis_r38;
            break;
        case 0x03 :
            p_com4l;
            b_disp_buf = b_dis_r48;
            break;
        case 0x04 :
            p_com5l;
            b_disp_buf = b_dis_r58;
            break;
        case 0x05 :
            p_com6l;
            b_disp_buf = b_dis_r68;
            break;
        case 0x06 :
            p_com7l;
            b_disp_buf = b_dis_r78;
            break;
        case 0x07 :
            p_com8l;
            b_disp_buf = b_dis_r88;
            break;
        default :
            b_disp_buf = 0x00;
            break;
        }

        switch(b_disp_status & 0x07)
        {
        case 0x00 :
            if(b_disp_buf & 0x01)
                p_seg1h;
            break;
        case 0x01 :
            if(b_disp_buf & 0x02)
                p_seg2h;
            break;
        case 0x02 :
            if(b_disp_buf & 0x04)
                p_seg3h;
            break;
        case 0x03 :
            if(b_disp_buf & 0x08)
                p_seg4h;
            break;
        case 0x04 :
            if(b_disp_buf & 0x10)
                p_seg5h;
            break;
        case 0x05 :
            if(b_disp_buf & 0x20)
                p_seg6h;
            break;
        case 0x06 :
            if(b_disp_buf & 0x40)
                p_seg7h;
            break;
        case 0x07 :
            if(b_disp_buf & 0x80)
                p_seg8h;
            break;
        default :
            break;
        }
    }

#endif



#if	c_disp_comcom_qi


    unsigned char b_disp_buf=0;

//    p_com1l;
//    p_com2l;
//    p_com3l;
//    p_com4l;
//    p_com5l;
//    p_com6l;
//    p_com7l;
//    p_com8l;

    //p_seg1l;
    //p_seg2l;
    //p_seg3l;
    //p_seg4l;
    //p_seg5l;
    //p_seg6l;
    //p_seg7l;
    //p_seg8l;
    //p_seg9l;
    //p_seg10l;

 
    //�õ��Ŀڶ���Ϊ����
    p_segA1in;
    p_segA2in;
    p_segA3in;
    p_segA4in;
    p_segA5in;
    p_segA6in;
    p_segA7in;

    p_segB1in;
    p_segB2in;
    p_segB3in;
    p_segB4in;
    p_segB5in;
    p_segB6in;
    p_segB7in;

    p_com1in;
    b_disp_status ++;
    if(b_disp_status>=c_ledScan_cnt)
        b_disp_status=0;


    switch (b_disp_status)
    {
        case 0 :    //51
            if(b_dis_r18 & 0x01)
            {
                p_segA5out;
                p_segA5h;
                p_segA1out;
                p_segA1l;
            }
            if(b_dis_r48 & 0x01)
            {
                p_segB5out;
                p_segB5h;
                p_segB1out;
                p_segB1l;
            }
            break;
        case 1 :    //52
            if(b_dis_r18 & 0x02)
            {
                p_segA5out;
                p_segA5h;
                p_segA2out;
                p_segA2l;
            }
            if(b_dis_r48 & 0x02)
            {
                p_segB5out;
                p_segB5h;
                p_segB2out;
                p_segB2l;
            }
            break;
        case 2 :    //53
            if(b_dis_r18 & 0x04)
            {
                p_segA5out;
                p_segA5h;
                p_segA3out;
                p_segA3l;
            }
            if(b_dis_r48 & 0x04)
            {
                p_segB5out;
                p_segB5h;
                p_segB3out;
                p_segB3l;
            }
            break;
        case 3 :    //54
            if(b_dis_r18 & 0x08)
            {
                p_segA5out;
                p_segA5h;
                p_segA4out;
                p_segA4l;
            }
            if(b_dis_r48 & 0x08)
            {
                p_segB5out;
                p_segB5h;
                p_segB4out;
                p_segB4l;
            }            
            break;
        case 4 :    //15
            if(b_dis_r18 & 0x10)
            {
                p_segA1out;
                p_segA1h;
                p_segA5out;
                p_segA5l;
            }
            if(b_dis_r48 & 0x10)
            {
                p_segB1out;
                p_segB1h;
                p_segB5out;
                p_segB5l;
            }            
            break;
        case 5 :    //25
            if(b_dis_r18 & 0x20)
            {
                p_segA2out;
                p_segA2h;
                p_segA5out;
                p_segA5l;
            }
            if(b_dis_r48 & 0x20)
            {
                p_segB2out;
                p_segB2h;
                p_segB5out;
                p_segB5l;
            }            
            break;
        case 6 :    //35
            if(b_dis_r18 & 0x40)
            {
                p_segA3out;
                p_segA3h;
                p_segA5out;
                p_segA5l;
            }
            if(b_dis_r48 & 0x40)
            {
                p_segB3out;
                p_segB3h;
                p_segB5out;
                p_segB5l;
            }            
            break;
        case 7 :    //45
            if(b_dis_r18 & 0x80)
            {
                p_segA4out;
                p_segA5out;
                p_segA4h;
                p_segA5l;
            }
            if(b_dis_r48 & 0x80)
            {
                p_segB4out;
                p_segB5out;
                p_segB4h;
                p_segB5l;
            }            
            break;
        //�ڶ�λ�����
        case 8 :    //61
            if(b_dis_r28 & 0x01)
            {
                p_segA6out;
                p_segA6h;
                p_segA1out;
                p_segA1l;
            }
            if(b_dis_r58 & 0x01)
            {
                p_segB6out;
                p_segB6h;
                p_segB1out;
                p_segB1l;
            }            
            break;
        case 9 :    //62
            if(b_dis_r28 & 0x02)
            {
                p_segA6out;
                p_segA6h;                
                p_segA2out;
                p_segA2l;
            }
            if(b_dis_r58 & 0x02)
            {
                p_segB6out;
                p_segB6h;                
                p_segB2out;
                p_segB2l;
            }            
            break;
        case 10 :    //63
            if(b_dis_r28 & 0x04)
            {
                p_segA6out;
                p_segA6h;
                p_segA3out;
                p_segA3l;
            }
            if(b_dis_r58 & 0x04)
            {
                p_segB6out;
                p_segB6h;
                p_segB3out;
                p_segB3l;
            }            
            break;
        case 11 :    //64
            if(b_dis_r28 & 0x08)
            {
                p_segA6out;
                p_segA6h;
                p_segA4out;
                p_segA4l;
            }
            if(b_dis_r58 & 0x08)
            {
                p_segB6out;
                p_segB6h;
                p_segB4out;
                p_segB4l;
            }            
            break;
        case 12 :    //16
            if(b_dis_r28 & 0x10)
            {
                p_segA1out;
                p_segA1h;
                p_segA6out;
                p_segA6l;
            }
            if(b_dis_r58 & 0x10)
            {
                p_segB1out;
                p_segB1h;
                p_segB6out;
                p_segB6l;
            }            
            break;
        case 13 :    //26
            if(b_dis_r28 & 0x20)
            {
                p_segA2out;
                p_segA2h;
                p_segA6out;
                p_segA6l;
            }
            if(b_dis_r58 & 0x20)
            {
                p_segB2out;
                p_segB2h;
                p_segB6out;
                p_segB6l;
            }
            break;
        case 14 :    //36
            if(b_dis_r28 & 0x40)
            {
                p_segA3out;
                p_segA3h;
                p_segA6out;
                p_segA6l; 
            }
            if(b_dis_r58 & 0x40)
            {
                p_segB3out;
                p_segB3h;
                p_segB6out;
                p_segB6l; 
            }            
            break;
        case 15 :    //46
            if(b_dis_r28 & 0x80)
            {
                p_segA4out;
                p_segA4h;
                p_segA6out;
                p_segA6l;
            }
            if(b_dis_r58 & 0x80)
            {
                p_segB4out;
                p_segB4h;
                p_segB6out;
                p_segB6l;
            }            
            break;
        //����λ�����
        case 16 :    //71
            if(b_dis_r38 & 0x01)
            {
                p_segA7out;
                p_segA7h;
                p_segA1out;
                p_segA1l;
            }
            if(b_dis_r68 & 0x01)
            {
                p_segB7out;
                p_segB7h;
                p_segB1out;
                p_segB1l;
            }
            break;
        case 17 :    //72
            if(b_dis_r38 & 0x02)
            {
                p_segA7out;
                p_segA7h;
                p_segA2out;
                p_segA2l;
            }
            if(b_dis_r68 & 0x02)
            {
                p_segB7out;
                p_segB7h;
                p_segB2out;
                p_segB2l;
            }            
            break;
        case 18 :    //73
            if(b_dis_r38 & 0x04)
            {
                p_segA7out;
                p_segA7h;
                p_segA3out;
                p_segA3l;
            }
            if(b_dis_r68 & 0x04)
            {
                p_segB7out;
                p_segB7h;
                p_segB3out;
                p_segB3l;
            }            
            break;
        case 19 :    //74
            if(b_dis_r38 & 0x08)
            {
                p_segA7out;
                p_segA7h;
                p_segA4out;
                p_segA4l;
            }
            if(b_dis_r68 & 0x08)
            {
                p_segB7out;
                p_segB7h;
                p_segB4out;
                p_segB4l;
            }                        
            break;
        case 20 :    //17
            if(b_dis_r38 & 0x10)
            {
                p_segA1out;
                p_segA1h;
                p_segA7out;
                p_segA7l;
            }
            if(b_dis_r68 & 0x10)
            {
                p_segB1out;
                p_segB1h;
                p_segB7out;
                p_segB7l;
            }            
            break;
        case 21 :    //27
            if(b_dis_r38 & 0x20)
            {
                p_segA2out;
                p_segA2h;
                p_segA7out;
                p_segA7l;
            }
            if(b_dis_r68 & 0x20)
            {
                p_segB2out;
                p_segB2h;
                p_segB7out;
                p_segB7l;
            }            
            break;
        case 22 :    //37
            if(b_dis_r38 & 0x40)
            {
                p_segA3out;
                p_segA3h;
                p_segA7out;
                p_segA7l;
            }
            if(b_dis_r68 & 0x40)
            {
                p_segB3out;
                p_segB3h;
                p_segB7out;
                p_segB7l;
            }            
            break;
        case 23 :    //47
            if(b_dis_r38 & 0x80)
            {
                p_segA4out;
                p_segA4h;
                p_segA7out;
                p_segA7l;
            }
            if(b_dis_r68 & 0x80)
            {
                p_segB4out;
                p_segB4h;
                p_segB7out;
                p_segB7l;
            }            
            break;
        case 24 :    //LED1
            if(b_dis_r78 & 0x01)
            {
                p_com1out;
                p_com1h;
                p_segA5out;
                p_segA5l;
            }       
            break;
        case 25 :    //LED2
            if(b_dis_r78 & 0x02)
            {
                p_segA6out;
                p_segA6h;
                p_com1out;
                p_com1l;
            }       
            break;        
        case 26 :    //LED3
            if(b_dis_r78 & 0x04)
            {
                p_com1out;
                p_com1h;
                p_segB5out;
                p_segB5l;
            }       
            break; 
        case 27 :    //LED4
            if(b_dis_r78 & 0x08)
            {
                p_segB4out;
                p_segB4h;
                p_com1out;
                p_com1l;
            }       
            break; 
        case 28 :   //����������
            sw_scan_in();
            break;
        case 29 :   //�������
            sw_scan();
            break;        

        default :
            b_disp_buf = 0x00;
            break;
    }
		
#endif	



#if	0


    unsigned char b_disp_buf=0;

//    p_com1l;
//    p_com2l;
//    p_com3l;
//    p_com4l;
//    p_com5l;
//    p_com6l;
//    p_com7l;
//    p_com8l;

    //p_seg1l;
    //p_seg2l;
    //p_seg3l;
    //p_seg4l;
    //p_seg5l;
    //p_seg6l;
    //p_seg7l;
    //p_seg8l;
    //p_seg9l;
    //p_seg10l;

 
    //�õ��Ŀڶ���Ϊ����
    p_seg1in;
    p_seg2in;
    p_seg3in;
    p_seg4in;
    p_seg5in;
    p_seg6in;
    p_seg7in;

    b_disp_status ++;
    if(b_disp_status>=c_ledScan_cnt)
        b_disp_status=0;


    switch (b_disp_status)
    {
        //case 0 :    //LED1 14
        //case 1 :    //LED2 15
		case 0 :    
            if(b_dis_r18 & 0x01)
            {
                p_seg1out;
                p_seg1h;
                p_seg4out;
                p_seg4l;
            }
			//LED_POWER();
        	//break;
        //case 1 :    //LED2 15
            if(b_dis_r18 & 0x02)
            {
                p_seg1out;
                p_seg1h;
                p_seg5out;
                p_seg5l;
            }
			LED_POWER();
            break;
        //case 2 :    //LED3 51
        //case 3 :    //LED4 41
		case 1 :
            if(b_dis_r18 & 0x04)
            {
                p_seg5out;
                p_seg5h;
                p_seg1out;
                p_seg1l;
            }
			//LED_POWER();
            //break;
        //case 3 :    //LED4 41
            if(b_dis_r18 & 0x08)
            {
                p_seg4out;
                p_seg4h;
                p_seg1out;
                p_seg1l;
            }
			//LED_POWER();
            break;         
        //case 4 :    //LED5 24
        //case 5 :    //LED6 25
		case 2 :
            if(b_dis_r18 & 0x10)
            {
                p_seg2out;
                p_seg2h;
                p_seg4out;
                p_seg4l;
            }
			//LED_POWER();
        //    break;    
        //case 5 :    //LED6 25
            if(b_dis_r18 & 0x20)
            {
                p_seg2out;
                p_seg2h;
                p_seg5out;
                p_seg5l;
            }
			LED_POWER();
            break;   
        //case 6 :    //LED7 42
        //case 7 :    //LED8 52
		case 3 :
            if(b_dis_r18 & 0x40)
            {
                p_seg4out;
                p_seg4h;
                p_seg2out;
                p_seg2l;
            }
			LED_POWER();
        //    break;   
        //case 7 :    //LED8 52
            if(b_dis_r18 & 0x80)
            {
                p_seg5out;
                p_seg5h;
                p_seg2out;
                p_seg2l;
            }
			LED_POWER();
            break;   
        //case 8 :    //LED9 34
        //case 9 :    //LED10 35
		case 4 :
            if(b_dis_r28 & 0x01)
            {
                p_seg3out;
                p_seg3h;
                p_seg4out;
                p_seg4l;
            }
			LED_POWER();
        //    break; 
        //case 9 :    //LED10 35
            if(b_dis_r28 & 0x02)
            {
                p_seg3out;
                p_seg3h;
                p_seg5out;
                p_seg5l;
            }
			LED_POWER();
            break; 
        //case 10 :    //LED11 43
        //case 11 :    //LED12 53
		case 5 :
            if(b_dis_r28 & 0x04)
            {
                p_seg4out;
                p_seg4h;
                p_seg3out;
                p_seg3l;
            }
			LED_POWER();
        //    break; 
        //case 11 :    //LED12 53
            if(b_dis_r28 & 0x08)
            {
                p_seg5out;
                p_seg5h;
                p_seg3out;
                p_seg3l;
            }
			LED_POWER();
			
            break; 
        case 12 :    //LED13 X6
        //case 13 :    //LED14 X7
            if(b_dis_r28 & 0x10)
            {
                //p_seg5out;
                //p_seg5h;
                p_seg6out;
                p_seg6l;
            }
			if(b_dis_r28 & 0x20)
            {
                //p_seg5out;
                //p_seg5h;
                p_seg7out;
                p_seg7l;
            }    


			break; 
        case 13 :    //LED14 X7
            if(b_dis_r28 & 0x20)
            {
                //p_seg5out;
                //p_seg5h;
                p_seg7out;
                p_seg7l;
            }        
			if(b_dis_r28 & 0x10)
            {
                //p_seg5out;
                //p_seg5h;
                p_seg6out;
                p_seg6l;
            }

            break; 

        default :
            b_disp_buf = 0x00;
            break;
    }
#endif



#if	c_disp_comcom2_qi


    unsigned char b_disp_buf=0;

    //�õ��Ŀڶ���Ϊ����
    p_seg1in;
    p_seg2in;
    p_seg3in;
    p_seg4in;
    p_seg5in;
    p_seg6in;
    p_seg7in;
    p_seg8in;
    p_seg9in;
    p_seg10in;	

    b_disp_status ++;
    if(b_disp_status>=c_ledScan_cnt)
        b_disp_status=0;


    switch (b_disp_status)
    {
		/*SMG1*/
		case 0 :    //A 51
            if(b_dis_r18 & 0x01)
            {
                p_seg5out;
                p_seg5h;
                p_seg1out;
                p_seg1l;
            }
			break;
		case 1:		//B 52
            if(b_dis_r18 & 0x02)
            {
                p_seg5out;
                p_seg5h;
                p_seg2out;
                p_seg2l;
            }
            break;
		case 2 :	//C 53 
            if(b_dis_r18 & 0x04)
            {
                p_seg5out;
                p_seg5h;
                p_seg3out;
                p_seg3l;
            }
			break;
		case 3 :	//D 54
            if(b_dis_r18 & 0x08)
            {
                p_seg5out;
                p_seg5h;
                p_seg4out;
                p_seg4l;
            }
            break;         

		case 4 :	//E 15  
            if(b_dis_r18 & 0x10)
            {
                p_seg1out;
                p_seg1h;
                p_seg5out;
                p_seg5l;
            }
			break;
		case 5 :	//F 25
            if(b_dis_r18 & 0x20)
            {
                p_seg2out;
                p_seg2h;
                p_seg5out;
                p_seg5l;
            }
            break;   
		case 6 :	//G 35	
            if(b_dis_r18 & 0x40)
            {
                p_seg3out;
                p_seg3h;
                p_seg5out;
                p_seg5l;
            }
			break;
		case 7 :	//H 45
            if(b_dis_r18 & 0x80)
            {
                p_seg4out;
                p_seg4h;
                p_seg5out;
                p_seg5l;
            }
            break;   

		/*�����2*/
		case 8:		//A	61
            if(b_dis_r28 & 0x01)
            {
                p_seg6out;
                p_seg6h;
                p_seg1out;
                p_seg1l;
            }
			break;
		case 9:		//B 62
            if(b_dis_r28 & 0x02)
            {
                p_seg6out;
                p_seg6h;
                p_seg2out;
                p_seg2l;
            }
            break; 
		case 10 :	//C 63	
            if(b_dis_r28 & 0x04)
            {		
                p_seg6out;
                p_seg6h;
                p_seg3out;
                p_seg3l;
            }
			break;
		case 11:	//D 64
            if(b_dis_r28 & 0x08)
            {
                p_seg6out;
                p_seg6h;
                p_seg4out;
                p_seg4l;
            }
            break; 
		case 12:	//E 16
            if(b_dis_r28 & 0x10)
            {
                p_seg1out;
                p_seg1h;
                p_seg6out;
                p_seg6l;
            }
            break; 
		case 13:	//F 26
            if(b_dis_r28 & 0x20)
            {
                p_seg2out;
                p_seg2h;
                p_seg6out;
                p_seg6l;
            }
            break; 
		case 14:	//G 36
            if(b_dis_r28 & 0x40)
            {
                p_seg3out;
                p_seg3h;
                p_seg6out;
                p_seg6l;
            }
            break; 
		case 15:	//H 46
            if(b_dis_r28 & 0x80)
            {
                p_seg4out;
                p_seg4h;
                p_seg6out;
                p_seg6l;
            }
            break; 
		/*�����3*/
		case 16:		//A	71
            if(b_dis_r38 & 0x01)
            {
                p_seg7out;
                p_seg7h;
                p_seg1out;
                p_seg1l;
            }
			break;
		case 17:		//B 72
            if(b_dis_r38 & 0x02)
            {
                p_seg7out;
                p_seg7h;
                p_seg2out;
                p_seg2l;
            }
            break; 
		case 18 :	//C 73
            if(b_dis_r38 & 0x04)
            {		
                p_seg7out;
                p_seg7h;
                p_seg3out;
                p_seg3l;
            }
			break;
		case 19:	//D 74
            if(b_dis_r38 & 0x08)
            {
                p_seg7out;
                p_seg7h;
                p_seg4out;
                p_seg4l;
            }
            break; 
		case 20:	//E 17
            if(b_dis_r38 & 0x10)
            {
                p_seg1out;
                p_seg1h;
                p_seg7out;
                p_seg7l;
            }
            break; 
		case 21:	//F 27
            if(b_dis_r38 & 0x20)
            {
                p_seg2out;
                p_seg2h;
                p_seg7out;
                p_seg7l;
            }
            break; 
		case 22:	//G 37
            if(b_dis_r38 & 0x40)
            {
                p_seg3out;
                p_seg3h;
                p_seg7out;
                p_seg7l;
            }
            break; 
		case 23:	//H 47
            if(b_dis_r38 & 0x80)
            {
                p_seg4out;
                p_seg4h;
                p_seg7out;
                p_seg7l;
            }
            break; 
		/*�����4*/
		case 24:		//A	81
            if(b_dis_r48 & 0x01)
            {
                p_seg8out;
                p_seg8h;
                p_seg1out;
                p_seg1l;
            }
			break;
		case 25:		//B 82
            if(b_dis_r48 & 0x02)
            {
                p_seg8out;
                p_seg8h;
                p_seg2out;
                p_seg2l;
            }
            break; 
		case 26 :	//C 83
            if(b_dis_r48 & 0x04)
            {		
                p_seg8out;
                p_seg8h;
                p_seg3out;
                p_seg3l;
            }
			break;
		case 27:	//D 84
            if(b_dis_r48 & 0x08)
            {
                p_seg8out;
                p_seg8h;
                p_seg4out;
                p_seg4l;
            }
            break; 
		case 28:	//E 18
            if(b_dis_r48 & 0x10)
            {
                p_seg1out;
                p_seg1h;
                p_seg8out;
                p_seg8l;
            }
            break; 
		case 29:	//F 28
            if(b_dis_r48 & 0x20)
            {
                p_seg2out;
                p_seg2h;
                p_seg8out;
                p_seg8l;
            }
            break; 
		case 30:	//G 38
            if(b_dis_r48 & 0x40)
            {
                p_seg3out;
                p_seg3h;
                p_seg8out;
                p_seg8l;
            }
            break; 
		case 31:	//H 48
            if(b_dis_r48 & 0x80)
            {
                p_seg4out;
                p_seg4h;
                p_seg8out;
                p_seg8l;
            }
            break; 

		/*LED��*/
		case 32:	//LED1 89
            if(b_dis_r58 & 0x01)
            {
                p_seg8out;
                p_seg8h;
                p_seg9out;
                p_seg9l;
            }
            break; 
		case 33:	//LED2 3A
            if(b_dis_r58 & 0x02)
            {
                p_seg3out;
                p_seg3h;
                p_seg10out;
                p_seg10l;
            }
            break; 
		case 34:	//LED3 59
            if(b_dis_r58 & 0x04)
            {
                p_seg5out;
                p_seg5h;
                p_seg9out;
                p_seg9l;
            }
            break; 
		case 35:	//LED4 79
            if(b_dis_r58 & 0x08)
            {
                p_seg7out;
                p_seg7h;
                p_seg9out;
                p_seg9l;
            }
            break; 
		case 36:	//LED5 2A
            if(b_dis_r58 & 0x10)
            {
                p_seg2out;
                p_seg2h;
                p_seg10out;
                p_seg10l;
            }
            break; 
		case 37:	//LED6 69
            if(b_dis_r58 & 0x20)
            {
                p_seg6out;
                p_seg6h;
                p_seg9out;
                p_seg9l;
            }
            break; 


        default :
            b_disp_buf = 0x00;
            break;
    }
#endif

}


/*����ܶ�ʱ��ʾ1*/
void	smg_deal_dingshi_1()
{
	/*����״̬����˸*/
	/*��һ�벻��*/
	if(gf_flash || b_mjs_set_sec<1)	
	{
		//��ʾ���ڵ�λ��ʱ��
		//����1 6��ʾ��λ,����2 3 4 5��ʾʱ��
		if(b_mode==1 || b_mode==6)
		{
			//��ʾ��λ
			b_r18=0;
			b_r28=0;
			b_r38=17;	//P
			b_r48=b_grade;
			f_dp=1;  //��ʾС����
		}
		/*����2 3 ���ֵ1Сʱ,��ʾ60����*/
		else if(b_mode==2 || b_mode==3)
		{
			uchar b_temp1=	b_dingshi_min+b_dingshi_hour*60;
			
			//��ʾʱ��
			b_r18 = 0;
			b_r28 = 0;			
			b_r38 = b_temp1/10;
			b_r48 = b_temp1%10;
			f_dp  = 1;  //��ʾС����
		}
		/*����4 ��Сʱ,������ʾ*/
		else if(b_mode==4)
		{
			//��ʾʱ��
			b_r18 = b_dingshi_hour/10;;
			b_r28 = b_dingshi_hour%10;			
			b_r38 = b_dingshi_min/10;
			b_r48 = b_dingshi_min%10;
			f_dp  = 1;  //��ʾС����
		}
		/*����5 �����ʱ���60s=1min */
		else if(b_mode==5)
		{
			b_r18 = b_dingshi_hour/10;;
			b_r28 = b_dingshi_hour%10;			
			b_r38 = b_dingshi_min/10;
			b_r48 = b_dingshi_min%10;
			f_dp  = 1;  //��ʾС����
		}
		//��ʾ����
		else if(b_mode == 0x80)
		{
			////��ʾbb
			//b_r18=0x0b;
			//b_r28=0x0b;

			if (b_set_wendu<100)
			{
				//����״̬��,��ʾ�¶�
				b_r18 = 0x10;	//����ʾ
				b_r28 =	b_set_wendu/10;
				b_r38 =	b_set_wendu%10;
				b_r48 =	0x0c;
			}
			else
			{
				//����״̬��,��ʾ�¶�
				b_r18 = b_set_wendu/100;
				b_r28 =	b_set_wendu/10%10;
				b_r38 =	b_set_wendu%10;
				b_r48 =	0x0c;
			}
			

		}
	}
}


/*����ܶ�ʱ��ʾ2*/
void	smg_deal_dingshi_2()
{
	
	//��ʾ���ڵ�λ��ʱ��
	//����1 6��ʾ��λ,����2 3 4 5��ʾʱ��
	if(b_mode==1 || b_mode==6)
	{
		//��ʾ��λ
		b_r18=0;
		b_r28=0;
		b_r38=17;	//P
		b_r48=b_grade;
		//if(gf_flash)
			f_dp=1;  //��ʾС����

		///*����*/
		//if(b_mode==1)
		//{
		//	b_r18 = gb_wendu/16;
		//	b_r28 =	gb_wendu%16;
		//	b_r38 =	b_kkg_buf/10;
		//	b_r48 =	b_kkg_buf%10;
		//	if(gf_flash)
		//		b_r48 = b_wendu_ok;
		//}



	}
	/*����2 3 ���ֵ1Сʱ,��ʾ60����*/
	else if(b_mode==2 || b_mode==3)
	{
		uchar b_temp1=	b_dingshi_min+b_dingshi_hour*60;
		
		//��ʾʱ��
		b_r18 = 0;
		b_r28 = 0;			
		b_r38 = b_temp1/10;
		b_r48 = b_temp1%10;

		if (f_dingshi_begin && gf_flash)
		{
			f_dp  = 1;  //��ʾС����
		}
		
		
	}
	/*����4 ��Сʱ,������ʾ*/
	else if(b_mode==4)
	{
		//��ʾʱ��
		b_r18 = b_dingshi_hour/10;;
		b_r28 = b_dingshi_hour%10;			
		b_r38 = b_dingshi_min/10;
		b_r48 = b_dingshi_min%10;
		f_dp  = 1;  //��ʾС����

		if (f_dingshi_begin && gf_flash)
		{
			f_dp  = 1;  //��ʾС����
		}
	}
	/*����5 �����ʱ���60s=1min */
	else if(b_mode==5)
	{
		b_r18 = b_dingshi_hour/10;;
		b_r28 = b_dingshi_hour%10;			
		b_r38 = b_dingshi_min/10;
		b_r48 = b_dingshi_min%10;

		if (f_dingshi_begin && gf_flash)
		{
			f_dp  = 1;  //��ʾС����
		}
	}
	//��ʾ����
	//��ʾ����
	else if(b_mode == 0x80)
	{
		////��ʾbb
		//b_r18=0x0b;
		//b_r28=0x0b;

		//����״̬��,��ʾʱ��
		b_r18 = b_dingshi_hour/10;	
		b_r28 =	b_dingshi_hour%10;
		b_r38 =	b_dingshi_min/10;
		b_r48 =	b_dingshi_min%10;
	
		if(gf_flash)
			f_dp=1;  //��ʾС����

		//����
		//if(gf_flash)
		//{
		//	b_r18=gb_wendu/100;
		//	b_r28=gb_wendu/10%10;
		//	b_r38=gb_wendu%10;
		//	b_r48=0x0c;
		//}

//		if (gb_wendu<100)
//		{
//			//����״̬��,��ʾ�¶�
//			b_r18 = 0x10;	//����ʾ
//			b_r28 =	gb_wendu/10;
//			b_r38 =	gb_wendu%10;
//			b_r48 =	0x0c;
//			if(gf_flash)
//				b_r48 = b_wendu_ok;
//		}
//		else
//		{
//			b_r18 = gb_wendu/100;
//			b_r28 =	gb_wendu/10%10;
//			b_r38 =	gb_wendu%10;
//			b_r48 =	0x0c;
//			if(gf_flash)
//				b_r48 = b_wendu_ok;
//		}


	}
	
}

/*�����ԤԼ��ʾ1*/
void	smg_deal_yuyue_1()
{
	//��������״̬,��˸ʱ���
	//������ת̬,����ʱ���
	if(f_mjs_set)
	{	
		if(gf_flash)
		{
			//��ʾԤԼʱ��
    		b_r18=b_yuyue_hour/10;
    		b_r28=b_yuyue_hour%10; 	
			b_r38=b_yuyue_min/10;
			b_r48=b_yuyue_min%10; //H
			f_dp=1; 
		}
	}	
	else
	{
		////��ʾԤԼʱ��
    	//b_r18=b_yuyue_hour/10;
    	//b_r28=b_yuyue_hour%10;
    	//if(gf_flash)
    	//    f_dp=1;  

		//��ʾԤԼʱ��
    	b_r18=b_yuyue_hour/10;
    	b_r28=b_yuyue_hour%10; 	
		b_r38=b_yuyue_min/10;
		b_r48=b_yuyue_min%10; //H

		/*ԤԼ����ʱʱ,����˸*/
		if(gf_flash)
			f_dp=1; 
	}
}