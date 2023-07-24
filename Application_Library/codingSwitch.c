
#include 	"..\Application_Library\Global.h"

#include    <intrins.h>
#include 	"codingSwitch.h"	
#include	"codingSwitch_user.h"	

#if	(c_codingSwitch_en&&c_codingSwitch_user_en)	

	typedef	struct
	{
		uchar	status;			//���ڴ洢һ���������ֵ,��ʼ��Ϊ0x03
		uchar	order;			//��������,һ��������4��
		uchar	value;			//0:�޶���,1:��ת,2:��ת
		uchar	getOne;			//1:��ȡ����תֵ
		uchar	io_differCnt;	//��������
	}str_codingSwitch;

	str_codingSwitch	idata	bs_codingSwitch;
	str_codingSwitch	idata	bs_codingSwitch2;


/***********************************************************
;��������:void	codingSwitch_init(void)
;��������:IO�ڼ�������ʼ��
;�������:��
;�������:��	
;ʹ��ע��:
;--------
;---------
;---------
;**********************************************************/
	void	codingSwitch_init(void)
	{	
		/*�õ���IO�ڶ���Ϊ��������*/
		/*��ת���뿪��1 A*/
		p_codingSwitch_io1_in;
		p_codingSwitch_io1_pull;
		p_codingSwitch_io1_h;

		/*��ת���뿪��1 B*/
		p_codingSwitch_io2_in;
		p_codingSwitch_io2_pull;
		p_codingSwitch_io2_h;

		/*��ת���뿪��2 A*/
		p_codingSwitch_io3_in;
		p_codingSwitch_io3_pull;
		p_codingSwitch_io3_h;

		/*��ת���뿪��2 B*/
		p_codingSwitch_io4_in;
		p_codingSwitch_io4_pull;
		p_codingSwitch_io4_h;




		/*�ṹ���ʼ��*/
		//memset(&bs_codingSwitch,0,sizeof(str_codingSwitch));
		bs_codingSwitch.status=0;		
		bs_codingSwitch.order=0;		
		bs_codingSwitch.value=0;		
		bs_codingSwitch.getOne=0;		
		bs_codingSwitch.io_differCnt=0;

		bs_codingSwitch2.status=0;		
		bs_codingSwitch2.order=0;		
		bs_codingSwitch2.value=0;		
		bs_codingSwitch2.getOne=0;		
		bs_codingSwitch2.io_differCnt=0;



		bs_codingSwitch.status=0x03;
		bs_codingSwitch2.status=0x03;
	}




/***********************************************************
;��������:void	codingSwitch_distinguish(uchar cmd)
;��������:���ñ��뿪�ع���״̬
;�������:cmd
		 0:disable
		 1:enable
;�������:		
;ʹ��ע��:���ڶ�ʱ�ж�
;--------
;---------
;---------
;**********************************************************/
	void	codingSwitch_distinguish(uchar cmd)
	{			
		static	uchar	i;		//���жϻ�ȡ�ı���ֵ
		static	uchar	buf;	//��һ���жϻ�ȡ�ı���ֵ

		/*�����ʹ�ܱ��뿪�ع���,��Ĭ��AB��Ϊ��*/
		if(cmd==0)
		{
			i=0x03;
			buf=0x03;
			bs_codingSwitch.order=0;
			bs_codingSwitch.status=0x03;	
			bs_codingSwitch.value=0;		//0�޶���
	
			bs_codingSwitch.io_differCnt=0;		//��������
			return;
		}

		/*�����io1�������A,io2�������B*/
		if(p_codingSwitch_io1_get)
		{
			i |=0x02;					
		}
		else
		{
			i &=~0x02;
		}
		
		if(p_codingSwitch_io2_get)
		{
			i |=0x01;	
		}
		else
		{
			i &=~0x01;			
		}

		if((bs_codingSwitch.status&0x03)!=i)	//��ȡ��ֵ,�Ա�ǰһ���������ֵ�иı������
		{
			if(i==buf)	//���λ�ȡ�ı���ֵ���ϴλ�ȡ�ı���ֵһ��,˵��û�ж���
			{
				if(++bs_codingSwitch.io_differCnt>=c_codingSwitch_ioShake)		//��������
				{	
					bs_codingSwitch.io_differCnt=0;		//�� ��������
					/*************�������,i�洢���ǿ��õ�����******************/
					/*����������λ,����λ�����洢��ǰ1�α���ֵ*/
					bs_codingSwitch.status <<=2;		
					bs_codingSwitch.status +=i;	
					if(++bs_codingSwitch.order==4)
					{
						/*������˵,���bs_codingSwitch.status��ֵΪ 
						˳:
						01001011 
						ABABABAB
						
						��
						10000111
						ABABABAB
						
						*/
					#if	(c_codingSwitch_strengthenMode==0)		//���ǿ�ȵȼ�0~2��ֵԽ�󿹸�����Խǿ��Ҳ���˳���С���ʵ�©��
						bs_codingSwitch.status=bs_codingSwitch.status&0xf0;
						if(bs_codingSwitch.status==b(01000000))
						{				
							bs_codingSwitch.value=1;
						}
						else if(bs_codingSwitch.status==b(10000000))
						{
							bs_codingSwitch.value=2;
						}
						else
						{
							bs_codingSwitch.value=0;
						}
					#elif	(c_codingSwitch_strengthenMode==1)	//���ǿ�ȵȼ�0~2��ֵԽ�󿹸�����Խǿ��Ҳ���˳���С���ʵ�©��
						bs_codingSwitch.status=bs_codingSwitch.status&0xfc;	//1111 1100
						if(bs_codingSwitch.status==b(01001000))
						{				
							bs_codingSwitch.value=1;	//1:��ת
						}
						else if(bs_codingSwitch.status==b(10000100))
						{
							bs_codingSwitch.value=2;	//2:��ת
						}
						else
						{
							bs_codingSwitch.value=0;	//0:�޶���
						}
					#else										//���ǿ�ȵȼ�0~2��ֵԽ�󿹸�����Խǿ��Ҳ���˳���С���ʵ�©��
						if(bs_codingSwitch.status==b(01001011))
						{				
							bs_codingSwitch.value=1;
						}
						else if(bs_codingSwitch.status==b(10000111))
						{
							bs_codingSwitch.value=2;
						}
						else
						{
							bs_codingSwitch.value=0;
						}	
					#endif		
						bs_codingSwitch.order=0;		//��������,һ��������4��
						bs_codingSwitch.status=0x03;	//���ڴ洢һ���������ֵ,��ʼ��Ϊ0x03
						bs_codingSwitch.getOne=1;		//1:��ȡ����תֵ
							
					}
					else
					{
						//���ǵ�4��ȴ����11����Ϊ�������¿�ʼ��ȡ
						if(i==0x03)
						{
							bs_codingSwitch.order=0;
							bs_codingSwitch.status=0x03;	
						}

					}
				}
			}
			else
			{
				buf=i;
				bs_codingSwitch.io_differCnt=0;		//��������
			}
		}
		else
		{
			bs_codingSwitch.io_differCnt=0;			//��������
			buf=i;
		}
					
	}



/***********************************************************
;��������:void	codingSwitch_distinguish2(uchar cmd)
;��������:���ñ��뿪�ع���״̬(��ת���뿪��2)
;�������:cmd
		 0:disable
		 1:enable
;�������:		
;ʹ��ע��:���ڶ�ʱ�ж�
;--------
;---------
;---------
;**********************************************************/
	void	codingSwitch_distinguish2(uchar cmd)
	{			
		static	uchar	i;		//���жϻ�ȡ�ı���ֵ
		static	uchar	buf;	//��һ���жϻ�ȡ�ı���ֵ

		/*�����ʹ�ܱ��뿪�ع���,��Ĭ��AB��Ϊ��*/
		if(cmd==0)
		{
			i=0x03;
			buf=0x03;
			bs_codingSwitch2.order=0;
			bs_codingSwitch2.status=0x03;	
			bs_codingSwitch2.value=0;		//0�޶���
	
			bs_codingSwitch2.io_differCnt=0;		//��������
			return;
		}

		/*�����io3�������A,io4�������B*/
		if(p_codingSwitch_io3_get)
		{
			i |=0x02;					
		}
		else
		{
			i &=~0x02;
		}
		
		if(p_codingSwitch_io4_get)
		{
			i |=0x01;	
		}
		else
		{
			i &=~0x01;			
		}

		if((bs_codingSwitch2.status&0x03)!=i)	//��ȡ��ֵ,�Ա�ǰһ���������ֵ�иı������
		{
			if(i==buf)	//���λ�ȡ�ı���ֵ���ϴλ�ȡ�ı���ֵһ��,˵��û�ж���
			{
				if(++bs_codingSwitch2.io_differCnt>=c_codingSwitch_ioShake)		//��������
				{	
					bs_codingSwitch2.io_differCnt=0;		//�� ��������
					/*************�������,i�洢���ǿ��õ�����******************/
					/*����������λ,����λ�����洢��ǰ1�α���ֵ*/
					bs_codingSwitch2.status <<=2;		
					bs_codingSwitch2.status +=i;	
					if(++bs_codingSwitch2.order==4)
					{
						/*������˵,���bs_codingSwitch.status��ֵΪ 
						˳:
						01001011 
						ABABABAB
						
						��
						10000111
						ABABABAB
						
						*/
					#if	(c_codingSwitch_strengthenMode==0)		//���ǿ�ȵȼ�0~2��ֵԽ�󿹸�����Խǿ��Ҳ���˳���С���ʵ�©��
						bs_codingSwitch2.status=bs_codingSwitch2.status&0xf0;
						if(bs_codingSwitch2.status==b(01000000))
						{				
							bs_codingSwitch2.value=1;
						}
						else if(bs_codingSwitch2.status==b(10000000))
						{
							bs_codingSwitch2.value=2;
						}
						else
						{
							bs_codingSwitch2.value=0;
						}
					#elif	(c_codingSwitch_strengthenMode==1)	//���ǿ�ȵȼ�0~2��ֵԽ�󿹸�����Խǿ��Ҳ���˳���С���ʵ�©��
						bs_codingSwitch2.status=bs_codingSwitch2.status&0xfc;	//1111 1100
						if(bs_codingSwitch2.status==b(01001000))
						{				
							bs_codingSwitch2.value=1;	//1:��ת
						}
						else if(bs_codingSwitch2.status==b(10000100))
						{
							bs_codingSwitch2.value=2;	//2:��ת
						}
						else
						{
							bs_codingSwitch2.value=0;	//0:�޶���
						}
					#else										//���ǿ�ȵȼ�0~2��ֵԽ�󿹸�����Խǿ��Ҳ���˳���С���ʵ�©��
						if(bs_codingSwitch2.status==b(01001011))
						{				
							bs_codingSwitch2.value=1;
						}
						else if(bs_codingSwitch2.status==b(10000111))
						{
							bs_codingSwitch2.value=2;
						}
						else
						{
							bs_codingSwitch2.value=0;
						}	
					#endif		
						bs_codingSwitch2.order=0;		//��������,һ��������4��
						bs_codingSwitch2.status=0x03;	//���ڴ洢һ���������ֵ,��ʼ��Ϊ0x03
						bs_codingSwitch2.getOne=1;		//1:��ȡ����תֵ
							
					}
					else
					{
						//���ǵ�4��ȴ����11����Ϊ�������¿�ʼ��ȡ
						if(i==0x03)
						{
							bs_codingSwitch2.order=0;
							bs_codingSwitch2.status=0x03;	
						}

					}
				}
			}
			else
			{
				buf=i;
				bs_codingSwitch2.io_differCnt=0;		//��������
			}
		}
		else
		{
			bs_codingSwitch2.io_differCnt=0;			//��������
			buf=i;
		}
					
	}

/***********************************************************
;��������:uchar	codingSwitch_get(void)
;��������:��ȡ���뿪��״̬
;�������:��
;�������:		
		 0:�޶���
		 1:��ת
		 2:��ת
;ʹ��ע��:
;--------
;---------
;---------
;**********************************************************/
	uchar	codingSwitch_get(void)
	{						
		uchar	i=0;		
		if(bs_codingSwitch.getOne)
		{
			bs_codingSwitch.getOne=0;
			i=bs_codingSwitch.value;
			bs_codingSwitch.value=0;				
		}
		return	i;		
	}



/***********************************************************
;��������:uchar	codingSwitch_get2(void)
;��������:��ȡ���뿪��״̬(��ת���뿪��2)
;�������:��
;�������:		
		 0:�޶���
		 1:��ת
		 2:��ת
;ʹ��ע��:
;--------
;---------
;---------
;**********************************************************/
	uchar	codingSwitch_get2(void)
	{						
		uchar	i=0;		
		if(bs_codingSwitch2.getOne)
		{
			bs_codingSwitch2.getOne=0;
			i=bs_codingSwitch2.value;
			bs_codingSwitch2.value=0;				
		}
		return	i;		
	}








#endif
