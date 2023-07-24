#include 	"..\Application_Library\Global.h"
#include    <intrins.h>

#if	(c_codingSwitch_user_en)	



//codingSwitch_get();
/***********************************************************
;函数名称:void	codingSwitch_deal1(void)
;函数功能:旋转编码开关处理1
;输入参数:无
;输出参数:无	
;使用注意:
;--------
;---------
;---------
;**********************************************************/
void    codingSwitch_deal1()
{
    uchar i=0;
    i=codingSwitch_get();
    if(i==c_codingSwitch_s) //顺时针转动返回参数值
    {
        b_NOW_or_Target_cnt=c_IS_disp_Target;//显示目标值
        //增加目标温度,最大80℃
        Target_wendu_1++;
        if(Target_wendu_1>80)
            Target_wendu_1=80;
    }
    else if (i==c_codingSwitch_n) //逆时针转动返回参数值
    {
        b_NOW_or_Target_cnt=c_IS_disp_Target;//显示目标值
        //减少目标温度,最小40℃
        Target_wendu_1--;
        if(Target_wendu_1<35)
            Target_wendu_1=35;
    }
}

/***********************************************************
;函数名称:void	codingSwitch_deal1(void)
;函数功能:旋转编码开关处理2
;输入参数:无
;输出参数:无	
;使用注意:
;--------
;---------
;---------
;**********************************************************/
void    codingSwitch_deal2()
{
    uchar i=0;
    i=codingSwitch_get2();
    if(i==c_codingSwitch_s) //顺时针转动返回参数值
    {
        b_NOW_or_Target_cnt2=c_IS_disp_Target;//显示目标值
        //增加目标温度,最大80℃
        Target_wendu_2++;
        if(Target_wendu_2>80)
            Target_wendu_2=80;
    }
    else if (i==c_codingSwitch_n) //逆时针转动返回参数值
    {
        b_NOW_or_Target_cnt2=c_IS_disp_Target;//显示目标值
        //减少目标温度,最小40℃
        Target_wendu_2--;
        if(Target_wendu_2<35)
            Target_wendu_2=35;
    }
}


#endif
