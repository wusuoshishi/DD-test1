
#include 	"..\Application_Library\Global.h"



typedef	struct
{
    unsigned char	on;	 	//��ʱ��(��λ20ms)
    unsigned char	all;	//��ʱ�� (��λ20ms)
    unsigned char	cnt;	//�����
	//unsigned char	type;	//����
} str_buz;


unsigned char	b_buzKind=0;	//����������������
unsigned char	xdata	b_buzNum=0;
unsigned char	xdata	b_buzTable=0;
unsigned char	xdata	b_buzCnt=0;	//��Ĵ���
unsigned char	xdata	b_buzType=0;//���������������

unsigned char	xdata	b_buz_SP_cnt=0;	//�γ�100ms
unsigned char	xdata	b_SP_n=0;	//����ռ�ձ�




bit		f_buzFre=0;
bit		f_buzRun=0;	//0:�������������
bit		f_buzOn=0;


//str_buz  const	code	tab_buz[]=
//{
//	//��λ20ms
//   //ON  ALL CNT	//�˴���������
//    { 4, 6,  1,1},	//1.������ ռ�ձ�8%ʱ��80ms
//	{ 12, 16, 4,2},	//2.������ 4�� ռ�ձ�15% ʱ�� 240ms >> ͣ 80ms 
//	{33, 57,  1,3},	//3.������ ռ�ձ�:��8%�仯��0%ʱ666ms ͣ480ms
//	{ 4, 6,  2,4},	//4.���빤���� ռ�ձ�8%ʱ��80ms >>ͣ40ms >>�� 8%�仯�� 0% ʱ�� 666ms
//    { 4, 6,  8,4},	//5.����� 4�� ռ�ձ�8%ʱ��80ms + ͣ 40ms + �� 8%�仯�� 0% ʱ�� 600ms >> 480ms
//    
//    { 5, 25, 10,0},
//    {10, 50, 10,0},
//    {10, 50, 10,6},
//    { 5, 25, 10,6}
//};


str_buz  const	code	tab_buz[]=
{
	//��λ20ms
	/*���ʱ��,��ʱ��,����*/
    {8,16,1},	//������					 //�˴���������
    {26,50,1}, //�ϵ糤��
    {8,25,5},	//�������
    {5,10,3},
    {5,10,3},
    {10,50,10},
    {10,50,10},
    {10,50,10},
    {5,25,10}
};



/*-----------------------------------------------------------------
�������ƣ� void	buz_ring(void)
�������ܣ� �������,���ж�
��������� ��
�� �� ֵ�� ��
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
�������ƣ� void	open_buz(unsigned char i)
�������ܣ� ����������������ѡ��
��������� ��������
�� �� ֵ�� ��
-----------------------------------------------------------------*/

void	open_buz(unsigned char i)
{
    b_buzKind=i;
}



/*-----------------------------------------------------------------
�������ƣ� void	buz_deal(void)
�������ܣ� ����������������
��������� ��
�� �� ֵ�� ��
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
        ADC_PD(1);//�ر�ADCģ��
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



/*���⴦��,��PWM����*/
//void	buz_deal()
//{
//    if(b_buzKind)
//    {
//		/*��ȡ�����������Ϣ*/
//        b_buzTable=b_buzKind-1;
//        b_buzKind=0;
//        b_buzCnt=tab_buz[b_buzTable].cnt;	//��������Ĵ���
//		b_buzType=tab_buz[b_buzTable].type;//���������������
//        b_buzNum=0;
//        f_buzOn=0;
//        f_buzRun=1;	//0:�������������
//
//		//���>=3ʱ,�ػ���ʱ
//		if(b_buzType>=3)
//		{
//			//��ʼ��ռ�ձ�
//			b_SP_n=7;	
//			b_buz_SP_cnt=0;	//��ʼ���������
//		}
//
//		#if   c_ad_buz_com
//        ADC_PD(1);//�ر�ADCģ��
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
//			/*��������ʱ��*/
//        	if(b_buzNum<=tab_buz[b_buzTable].on)
//        	{
//        	    f_buzOn=1;
//        	    p_buz_out;
//        	}
//        	else
//        	{
//        	    f_buzOn=0;
//        	    //buz_disEN;
//				//��
//				PWM0C_Set(2000,100);	//(Ƶ��,ռ�ձ�)
//
//        	}
//
//			/*������*/
//        	if(b_buzNum==tab_buz[b_buzTable].all)
//        	{
//        	    b_buzCnt--;
//        	    b_buzNum=0;
//        	    if(b_buzCnt==0)
//        	    {
//        	        f_buzRun=0;	//0:�������������
//        	        f_buzOn=0;
//        	        //buz_disEN;
//					//��
//					PWM0C_Set(2000,100);	//(Ƶ��,ռ�ձ�)
//					
//        	    }
//			}
//
//		}	
//		else
//		{
//			if(b_buzCnt==8)
//				b_buzTable=0;//(1-1)	//��ť��ʱ��
//			else if(b_buzCnt==7)
//				b_buzTable=2;//(3-1)	//������ʱ��
//			else if(b_buzCnt==6)
//				b_buzTable=0;//(1-1)	//��ť��ʱ��
//			else if(b_buzCnt==5)
//				b_buzTable=2;//(3-1)	//������ʱ��
//			else if(b_buzCnt==4)
//				b_buzTable=0;//(1-1)	//��ť��ʱ��							
//			else if(b_buzCnt==3)
//				b_buzTable=2;//(3-1)	//������ʱ��
//			else if(b_buzCnt==2)
//				b_buzTable=0;//(1-1)	//��ť��ʱ��
//			else if(b_buzCnt==1)
//				b_buzTable=2;//(4-1)	//������ʱ��		
//			else
//				b_buzTable=0;//(1-1)	//��ť��ʱ��
//
//	        b_buzNum++;
//			/*��������ʱ��*/
//        	if(b_buzNum<=tab_buz[b_buzTable].on)
//        	{
//        	    f_buzOn=1;
//        	    p_buz_out;
//        	}
//        	else
//        	{
//        	    f_buzOn=0;
//        	    //buz_disEN;
//				//��
//				PWM0C_Set(2000,100);	//(Ƶ��,ռ�ձ�)
//        	}
//
//			/*������*/
//        	if(b_buzNum>=tab_buz[b_buzTable].all)
//        	{
//        	    b_buzCnt--;
//        	    b_buzNum=0;
//        	    if(b_buzCnt==0)
//        	    {
//        	        f_buzRun=0;	//0:�������������
//        	        f_buzOn=0;
//        	        //buz_disEN;
//        	    }
//				//��ʼ��ռ�ձ�
//				b_SP_n=7;	
//				b_buz_SP_cnt=0;	//��ʼ���������
//
//
//			}		
//		}
//
//    
//    }
//
//
//	/*���⴦��*/
//	if(f_buzOn)
//	{
//		if(b_buzType==1)	//������
//			PWM0C_Set(2000,(100-7));	//(Ƶ��,ռ�ձ�)
//		else if(b_buzType==2)//������
//			PWM0C_Set(2000,(100-15));	//(Ƶ��,ռ�ձ�)
//		else if(b_buzType==3)//������
//		{
//			b_buz_SP_cnt++;	//�������,�γ�100ms
//			if(b_buz_SP_cnt>=6)
//			{
//				b_buz_SP_cnt=0;
//				/*100ms����һ��*/
//				if(b_SP_n>0)
//				{
//					b_SP_n--;
//				}
//						
//			}
//				if(b_SP_n>0)
//				{
//					PWM0C_Set(2000,(100-b_SP_n));	//(Ƶ��,ռ�ձ�)
//				}
//				else
//				{
//					PWM0C_Set(2000,100);	//(Ƶ��,ռ�ձ�)
//				}
//		}
//		else if(b_buzType==4)//������
//		{
//			//3-1 ������
//			//1-1 ��ť��
//			if(b_buzTable==0)
//			{
//				//��ť��ʱ��
//				PWM0C_Set(2000,(100-7));	//(Ƶ��,ռ�ձ�)	
//			}
//			else if(b_buzTable==2)
//			{
//				b_buz_SP_cnt++;	//�������,�γ�100ms
//				if(b_buz_SP_cnt>=5)
//				{
//					b_buz_SP_cnt=0;
//					/*100ms����һ��*/
//					if(b_SP_n>0)
//					{
//						b_SP_n--;
//					}
//				}
//
//				if(b_SP_n>0)
//				{
//					PWM0C_Set(2000,(100-b_SP_n));	//(Ƶ��,ռ�ձ�)
//				}
//				else
//				{
//					PWM0C_Set(2000,100);	//(Ƶ��,ռ�ձ�)
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
//		//��
//		PWM0C_Set(2000,100);	//(Ƶ��,ռ�ձ�)
//
//		//PWM0C_Set(2000,0);	//(Ƶ��,ռ�ձ�)
//		b_buz_SP_cnt=0;	//�������,�γ�100ms
//			//��ʼ��ռ�ձ�
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







