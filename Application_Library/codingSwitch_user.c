#include 	"..\Application_Library\Global.h"
#include    <intrins.h>

#if	(c_codingSwitch_user_en)	



//codingSwitch_get();
/***********************************************************
;��������:void	codingSwitch_deal1(void)
;��������:��ת���뿪�ش���1
;�������:��
;�������:��	
;ʹ��ע��:
;--------
;---------
;---------
;**********************************************************/
void    codingSwitch_deal1()
{
    uchar i=0;
    i=codingSwitch_get();
    if(i==c_codingSwitch_s) //˳ʱ��ת�����ز���ֵ
    {
        b_NOW_or_Target_cnt=c_IS_disp_Target;//��ʾĿ��ֵ
        //����Ŀ���¶�,���80��
        Target_wendu_1++;
        if(Target_wendu_1>80)
            Target_wendu_1=80;
    }
    else if (i==c_codingSwitch_n) //��ʱ��ת�����ز���ֵ
    {
        b_NOW_or_Target_cnt=c_IS_disp_Target;//��ʾĿ��ֵ
        //����Ŀ���¶�,��С40��
        Target_wendu_1--;
        if(Target_wendu_1<35)
            Target_wendu_1=35;
    }
}

/***********************************************************
;��������:void	codingSwitch_deal1(void)
;��������:��ת���뿪�ش���2
;�������:��
;�������:��	
;ʹ��ע��:
;--------
;---------
;---------
;**********************************************************/
void    codingSwitch_deal2()
{
    uchar i=0;
    i=codingSwitch_get2();
    if(i==c_codingSwitch_s) //˳ʱ��ת�����ز���ֵ
    {
        b_NOW_or_Target_cnt2=c_IS_disp_Target;//��ʾĿ��ֵ
        //����Ŀ���¶�,���80��
        Target_wendu_2++;
        if(Target_wendu_2>80)
            Target_wendu_2=80;
    }
    else if (i==c_codingSwitch_n) //��ʱ��ת�����ز���ֵ
    {
        b_NOW_or_Target_cnt2=c_IS_disp_Target;//��ʾĿ��ֵ
        //����Ŀ���¶�,��С40��
        Target_wendu_2--;
        if(Target_wendu_2<35)
            Target_wendu_2=35;
    }
}


#endif
